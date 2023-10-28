/**
  ******************************************************************************
  * @author         : Liu
  * @file           : lcd.c
  * @brief          : lcd通用控制驱动，驱动18PIN大LCD
  * @time           : 2022/5/12
  ******************************************************************************
  * @attention
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "spi_lcd.h"
#include "string.h"
#include "esp_types.h"
#include "driver/spi_master.h"
#include "driver/gpio.h"
#include "driver/ledc.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
/* Private typedef -----------------------------------------------------------*/

#define PIN_NUM_MISO 11
#define PIN_NUM_MOSI 13
#define PIN_NUM_CLK  12
#define PIN_NUM_CS   10
#define PIN_NUM_DC   9
#define PIN_NUM_RST  14
#define PIN_NUM_BCKL 21
#define PARALLEL_LINES 16
#define LCD_HOST   SPI2_HOST

spi_device_handle_t spi;

//This function is called (in irq context!) just before a transmission starts. It will
//set the D/C line to the value indicated in the user field.
void lcd_spi_pre_transfer_callback(spi_transaction_t *t)
{
    int dc=(int)t->user;
    gpio_set_level(PIN_NUM_DC, dc);
}

#define LEDC_TIMER              LEDC_TIMER_0
#define LEDC_MODE               LEDC_LOW_SPEED_MODE
#define LEDC_OUTPUT_IO          (PIN_NUM_BCKL) // Define the output GPIO
#define LEDC_CHANNEL            LEDC_CHANNEL_0
#define LEDC_DUTY_RES           LEDC_TIMER_7_BIT // Set duty resolution to 13 bits
#define LEDC_DUTY               (128) // Set duty to 50%. ((2 ** 8) - 1) * 50% = 128
#define LEDC_FREQUENCY          (5000) // Frequency in Hertz. Set frequency at 5 kHz

static void LCD_BCKLInit(void)
{
    // Prepare and then apply the LEDC PWM timer configuration
    ledc_timer_config_t ledc_timer = {
        .speed_mode       = LEDC_MODE,
        .timer_num        = LEDC_TIMER,
        .duty_resolution  = LEDC_DUTY_RES,
        .freq_hz          = LEDC_FREQUENCY,  // Set output frequency at 5 kHz
        .clk_cfg          = LEDC_AUTO_CLK
    };
    ESP_ERROR_CHECK(ledc_timer_config(&ledc_timer));

    // Prepare and then apply the LEDC PWM channel configuration
    ledc_channel_config_t ledc_channel = {
        .speed_mode     = LEDC_MODE,
        .channel        = LEDC_CHANNEL,
        .timer_sel      = LEDC_TIMER,
        .intr_type      = LEDC_INTR_DISABLE,
        .gpio_num       = LEDC_OUTPUT_IO,
        .duty           = 0, // Set duty to 0%
        .hpoint         = 0
    };
    ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, LEDC_DUTY);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void LCD_SetBlck(uint8_t brightness)
{
    brightness += 20;
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, brightness);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void LCD_Off()
{
    ledc_set_duty(LEDC_MODE, LEDC_CHANNEL, 0);
    ledc_update_duty(LEDC_MODE, LEDC_CHANNEL);
}

void LCD_HALInit()
{
    esp_err_t ret;
    spi_bus_config_t buscfg={
        .miso_io_num=PIN_NUM_MISO,
        .mosi_io_num=PIN_NUM_MOSI,
        .sclk_io_num=PIN_NUM_CLK,
        .quadwp_io_num=-1,
        .quadhd_io_num=-1,
        .max_transfer_sz=253700
    };
    spi_device_interface_config_t devcfg={
#ifdef CONFIG_LCD_OVERCLOCK
        .clock_speed_hz=26*1000*1000,           //Clock out at 26 MHz
#else
        .clock_speed_hz=80*1000*1000,           //Clock out at 10 MHz
#endif
        .mode=0,                                //SPI mode 0
        .spics_io_num=PIN_NUM_CS,               //CS pin
        .queue_size=7,                          //We want to be able to queue 7 transactions at a time
        .pre_cb=lcd_spi_pre_transfer_callback,  //Specify pre-transfer callback to handle D/C line
    };
    //Initialize the SPI bus
    ret=spi_bus_initialize(LCD_HOST, &buscfg, SPI_DMA_CH_AUTO);
    ESP_ERROR_CHECK(ret);
    //Attach the LCD to the SPI bus
    ret=spi_bus_add_device(LCD_HOST, &devcfg, &spi);
    ESP_ERROR_CHECK(ret);

    //Initialize non-SPI GPIOs
    gpio_config_t io_conf = {};
    io_conf.pin_bit_mask = ((1ULL<<PIN_NUM_DC) | (1ULL<<PIN_NUM_RST));
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pull_up_en = true;
    gpio_config(&io_conf);


    //Reset the display
    gpio_set_level(PIN_NUM_RST, 0);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    gpio_set_level(PIN_NUM_RST, 1);
    vTaskDelay(100 / portTICK_PERIOD_MS);
    LCD_BCKLInit();
//    gpio_set_level(PIN_NUM_BCKL, 1);
}
void LCD_WriteReg(uint8_t reg)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                     //Command is 8 bits
    t.tx_buffer=&reg;               //The data is the cmd itself
    t.user=(void*)0;                //D/C needs to be set to 0
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

void LCD_WriteData(uint8_t data)
{
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=8;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=&data;               //Data
    t.user=(void*)1;                //D/C needs to be set to 1
    ret=spi_device_polling_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}


void LCD_WriteData_16Bits(uint16_t data16)
{
    uint8_t h,l;
	h = data16 >> 8;
	l = (uint8_t)data16;
    uint8_t data[2] = {h, l};
    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=16;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=data;               //Data
    t.user=(void*)1;                //D/C needs to be set to 1

    ret=spi_device_transmit(spi, &t);  //Transmit!
//    spi_device_transmit(spi, &t);
    assert(ret==ESP_OK);            //Should have had no issues.[2] = {h, l};
}

void LCD_WriteData_16BitsLen(const uint16_t *data16, uint16_t len)
{
    for (int i = 0; i < len; i++){
        LCD_WriteData_16Bits(*data16);
        data16++;
    }
}


void LCD_WriteDataLen(const uint8_t* data, uint32_t len)
{
    esp_err_t ret;
    spi_transaction_t t;
    if (len==0) return;             //no need to send anything
    memset(&t, 0, sizeof(t));       //Zero out the transaction
    t.length=len*8;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=data;               //Data
    t.user=(void*)1;                //D/C needs to be set to 1
    ret=spi_device_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

void LCD_WriteRegData(uint8_t reg, uint16_t data){
    LCD_WriteReg(reg);
    LCD_WriteData_16Bits(data);
}

void LCD_Delay(uint32_t ms)
{
	vTaskDelay(ms);
}
/* Private define ------------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/

/* Private user code ---------------------------------------------------------*/

/**
  * @brief  set the cursor position and draw window
  * @param  Star:开始
  * @param  Width:大小
  * @retval None
  */
void LCD_SetWindows(uint16_t xStar, uint16_t yStar,uint16_t xWidth,uint16_t yHeight)
{
	LCD_WriteRegData(0x02, (xStar) >> 8);
	LCD_WriteRegData(0x03, (xStar) & 0xFF); //Column End
	LCD_WriteRegData(0x04, (xStar + xWidth - 1) >> 8);
	LCD_WriteRegData(0x05, (xStar + xWidth - 1) & 0xFF); //Column End

	LCD_WriteRegData(0x06, (yStar) >> 8);
	LCD_WriteRegData(0x07, (yStar) & 0xFF); //Row End
	LCD_WriteRegData(0x08, (yStar + yHeight - 1) >> 8);
	LCD_WriteRegData(0x09, (yStar + yHeight - 1) & 0xFF); //Row End
	LCD_WriteReg(0x22); //准备开始写入GRAM
}

void LCD_SendColor(const uint16_t *color, size_t color_size)
{

    esp_err_t ret;
    spi_transaction_t t;
    memset(&t, 0, sizeof(t));       //Zero out the transaction

    if (color_size==0) return;             //no need to send anything
    t.length=color_size*16;                 //Len is in bytes, transaction length is in bits.
    t.tx_buffer=color;               //Data
    t.user=(void*)1;                //D/C needs to be set to 1
    ret = spi_device_transmit(spi, &t);  //Transmit!
    assert(ret==ESP_OK);            //Should have had no issues.
}

void LCD_Flush(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t * color_map)
{
//	uint32_t size = lv_area_get_width(area) * lv_area_get_height(area);
	LCD_WriteRegData(0x02, x1 >> 8);
	LCD_WriteRegData(0x03, x1 & 0xFF); //Column End
	LCD_WriteRegData(0x04, x2 >> 8);
	LCD_WriteRegData(0x05, x2 & 0xFF); //Column End

	LCD_WriteRegData(0x06, y1 >> 8);
	LCD_WriteRegData(0x07, y1 & 0xFF); //Row End
	LCD_WriteRegData(0x08, y2 >> 8);
	LCD_WriteRegData(0x09, y2 & 0xFF); //Row End
	LCD_WriteReg(0x22); //准备开始写入GRAM
    LCD_SendColor(color_map, (x2-x1+1)*(y2-y1+1));
//    LCD_WriteData_16BitsLen(color_map, (x2-x1+1)*(y2-y1+1));
}
/**
  * @brief  set the cursor position
  * @param  x:横坐标
  * @param  y:纵坐标
  * @retval None
  */
void LCD_SetCusor(uint16_t x, uint16_t y)
{
	LCD_WriteRegData(0x02, x >> 8);
	LCD_WriteRegData(0x03, x & 0xFF); //Column Start
	LCD_WriteRegData(0x06, y >> 8);
	LCD_WriteRegData(0x07, y & 0xFF); //Row Start
	LCD_WriteReg(0x22); //准备开始写入GRAM
}

/**
  * @brief  draw a point
  * @param  x:横坐标
  * @param  y:纵坐标
  * @param  color:颜色
  * @retval None
  */
void LCD_DrawPoint(uint16_t x, uint16_t y, uint16_t color)
{
	LCD_SetCusor(x, y);
	LCD_WriteData_16Bits(color);
}

/**
  * @brief  draw a line
  * @param  x1:横坐标1
  * @param  y1:纵坐标1
  * @param  x2:横坐标2
  * @param  y2:纵坐标2
  * @param  color:颜色
  * @retval None
  */
void LCD_ColorFill(uint16_t sx,uint16_t sy, uint16_t ex, uint16_t ey, uint16_t *color)
{
	uint16_t height,width;
	uint16_t i,j;
	width = ex-sx+1; 			//得到填充的宽度
	height = ey-sy+1;			//高度
	LCD_SetWindows(sx, sy, width, height);
	for(i=0;i<height;i++)
	{
		for(j=0;j<width;j++)
		{
			LCD_WriteData_16Bits(color[i*width+j]);
		}
	}
}

/**
  * @brief  draw a line
  * @param  x1:横坐标1
  * @param  y1:纵坐标1
  * @param  x2:横坐标2
  * @param  y2:纵坐标2
  * @param  color:颜色
  * @retval None
  */
void LCD_SetDirection(uint8_t direction)
{
    direction = LCD_RGBMODE | LCD_MV | LCD_MY;
	LCD_WriteRegData(0x16, direction);
}

uint16_t colors[7680] = {};
/**
  * @brief  draw a line
  * @param  x1:横坐标1
  * @param  y1:纵坐标1
  * @param  x2:横坐标2
  * @param  y2:纵坐标2
  * @param  color:颜色
  * @retval None
  */
void LCD_clear(uint16_t color)
{
	LCD_SetCusor(0,0);
    for (int i = 0; i < 7680; ++i) {
        colors[i] = color;
    }

    for (int k = 0; k < 10; ++k) {
        LCD_SendColor(colors, 7680);
    }
}

/**
 * @brief Init LCD Reference https://www.waveshare.net/w/upload/0/09/HX8347-D_DS_T_preliminary_v01_081129.pdf
 */
void LCD_Init()
{
    LCD_HALInit();
	//HX8347
	LCD_WriteRegData(0xEA,0x00); // Command page 0
	LCD_WriteRegData(0xEB,0x00); // SUB_SEL=0xF6
	// Power saving for HX8357-A
	LCD_WriteRegData(0xEC,0x3C); // Command page 0
	LCD_WriteRegData(0xED,0xC4); // GENON=0x00
	LCD_WriteRegData(0xE8,0x48); // EQVCI_M1=0x00
	LCD_WriteRegData(0xE9,0x38); // EQGND_M1=0x1C
	LCD_WriteRegData(0xF1,0x01); // EQVCI_M0=0x1C
	LCD_WriteRegData(0xF2,0x00); // EQGND_M0=0x1C
	LCD_WriteRegData(0x27,0xA3); // For GRAM read/write speed
	LCD_WriteRegData(0x2E,0x76); //For Gate timing, prevent the display abnormal in RGB I/F
	LCD_WriteRegData(0x60,0x08);
	LCD_WriteRegData(0x29,0x01);
	LCD_WriteRegData(0x2B,0x02);
	LCD_WriteRegData(0x36,0x09); // mode
	// Gamma
	LCD_WriteRegData(0x40,0x00);
	LCD_WriteRegData(0x41,0x01);
	LCD_WriteRegData(0x42,0x01);
	LCD_WriteRegData(0x43,0x12);
	LCD_WriteRegData(0x44,0x10);
	LCD_WriteRegData(0x45,0x24);
	LCD_WriteRegData(0x46,0x05);
	LCD_WriteRegData(0x47,0x5B);
	LCD_WriteRegData(0x48,0x03);
	LCD_WriteRegData(0x49,0x11);
	LCD_WriteRegData(0x4A,0x17);
	LCD_WriteRegData(0x4B,0x18);
	LCD_WriteRegData(0x4C,0x19);
	LCD_WriteRegData(0x50,0x1B);
	LCD_WriteRegData(0x51,0x2F);
	LCD_WriteRegData(0x52,0x2D);
	LCD_WriteRegData(0x53,0x3E);
	LCD_WriteRegData(0x54,0x3E);
	LCD_WriteRegData(0x55,0x3F);
	LCD_WriteRegData(0x56,0x30);
	LCD_WriteRegData(0x57,0x6E);
	LCD_WriteRegData(0x58,0x06);
	LCD_WriteRegData(0x59,0x07);
	LCD_WriteRegData(0x5A,0x08);
	LCD_WriteRegData(0x5B,0x0E);
	LCD_WriteRegData(0x5C,0x1C);
	LCD_WriteRegData(0x5D,0xCC);
	// Set GRAM area 320x240
	LCD_WriteRegData(0x02,0x00);
	LCD_WriteRegData(0x03,0x00);
	LCD_WriteRegData(0x04,0x00);
	LCD_WriteRegData(0x05,0xEF);
	LCD_WriteRegData(0x06,0x00);
	LCD_WriteRegData(0x07,0x00);
	LCD_WriteRegData(0x08,0x01);
	LCD_WriteRegData(0x09,0x3F);
	// Power Setting
	LCD_WriteRegData(0xE2,0x03);
	LCD_WriteRegData(0x1B,0x1D);
	LCD_WriteRegData(0x1A,0x01);
	LCD_WriteRegData(0x24,0x37); // Set VCOMH voltage, VHH=0x64
	LCD_WriteRegData(0x25,0x4F); // Set VCOML voltage, VML=0x71
	LCD_WriteRegData(0x23,0x6A); // Set VCOM offset, VMF=0x52	  ////////////60
	// Power on Setting
	LCD_WriteRegData(0x18,0x3A); // OSC_EN=1, Start to Oscillate
	LCD_WriteRegData(0x19,0x01); // AP=011

    LCD_SetDirection(3);//设置LCD显示方向

	LCD_WriteRegData(0x01,0x00); // Normal display(Exit Deep standby mode)
	LCD_WriteRegData(0x1F,0x88); // Exit standby mode and Step-up circuit 1 enable
	// GAS_EN=1, VCOMG=0, PON=0, DK=0, XDK=0, DDVDH_TRI=0, STB=0
	LCD_Delay(6);
	LCD_WriteRegData(0x1F,0x80); // Step-up circuit 2 enable
	// GAS_EN=1, VCOMG=0, PON=1, DK=0, XDK=0, DDVDH_TRI=0, STB=0
	LCD_Delay(6);
	LCD_WriteRegData(0x1F,0x90);
	LCD_Delay(6);
	LCD_WriteRegData(0x1F,0xD0);
	// GAS_EN=1, VCOMG=1, PON=1, DK=0, XDK=1, DDVDH_TRI=0, STB=0
	LCD_Delay(6);
	// Display ON Setting
	LCD_WriteRegData(0x17,0x05); // GON=1, DTE=1, D[1:0]=10
	LCD_Delay(6);
	LCD_WriteRegData(0x28,0x38); // GON=1, DTE=1, D[1:0]=11
	LCD_WriteRegData(0x28,0x3C); // 16-bit/pixel
    LCD_SetWindows(0, 0, 320, 240);
    LCD_clear(BLUE);
//    LCD_DrawPoint(10, 10, 0x00DD);
//    LCD_DrawPoint(20, 10, 0xFFDD);
}

//void LCD_FillColor()

void LCD_ShowImage(const uint8_t * img, uint16_t width, uint16_t height)
{
    uint16_t i,j, k;
    k = 0;
    LCD_SetWindows(0, 0, width, height);
    for(i=0;i<height;i++)
    {
        for(j=0;j<width;j++)
        {
            LCD_WriteData_16Bits(img[2*k] | img[2*k+1]<<8);
            k++;
        }
    }
}
