#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "spi_lcd.h"
#include "lv_port_disp.h"
#include "led_strip.h"
#include "ui.h"
#include "driver/gpio.h"


#define LED_NUMS    (LED_HEIGHT * LED_WIDTH)

void example_lvgl_demo_ui(lv_disp_t *disp);

uint16_t LED_GetXYNumber(uint16_t x, uint16_t y);
#define BLINK_GPIO 40

//void led_clear_all(led_strip_handle_t strip)
//{
//    uint16_t i, j;
//    uint16_t k =0 ;
//    for (i = 0; i < LED_WIDTH; ++i) {
//        for (j = 0; j < LED_HEIGHT; ++j) {
//            k++;
//            led_strip_set_pixel(strip, k, 0, 0, 0);
//        }
//    }
//}


void led_rmt_refresh_rectangle(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t *color);
extern  led_strip_handle_t led_strip;

void app_main(void)
{
    lv_disp_t *disp = NULL;
    lv_init();
    LCD_Init();
    lv_port_disp_init();
    example_lvgl_demo_ui(disp);

    gpio_config_t io_conf = {};
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_INPUT;
    //bit mask of the pins that you want to set,e.g.GPIO18/19
    io_conf.pin_bit_mask = (1ULL<<0);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);

    /* LED strip initialization with the GPIO and pixels number*/
    led_strip_config_t strip_config = {
        .strip_gpio_num = BLINK_GPIO, // The GPIO that connected to the LED strip's data line
        .max_leds = 16*8, // The number of LEDs in the strip,
        .led_pixel_format = LED_PIXEL_FORMAT_GRB, // Pixel format of your LED strip
        .led_model = LED_MODEL_WS2812, // LED strip model
        .flags.invert_out = false, // whether to invert the output signal (useful when your hardware has a level inverter)
    };

    led_strip_rmt_config_t rmt_config = {
        .clk_src = RMT_CLK_SRC_DEFAULT, // different clock source can lead to different power consumption
        .resolution_hz = 10 * 1000 * 1000, // 10MHz
        .flags.with_dma = true, // whether to enable the DMA feature
    };
    ESP_ERROR_CHECK(led_strip_new_rmt_device(&strip_config, &rmt_config, &led_strip));
    ui_init();


    uint16_t color[128] = {0};
    for (int i = 0; i < 128; ++i) {
        color[i] = 0xAAAA;
    }

    while (1) {
//        ESP_ERROR_CHECK(led_strip_set_pixel(led_strip, 0, 5, 5, 5));
//        led_rmt_refresh_rectangle(5, 5, 2, 7, color);
        static uint8_t press_flag = 0;

         led_strip_refresh(led_strip);
        if (gpio_get_level(0) == 0 && press_flag == 0)
        {
            printf("Hello world!\n");
            lv_event_send(ui_Switch1, LV_EVENT_RELEASED, NULL);
            press_flag = 1;
        } else if (gpio_get_level(0) == 1){
//            lv_event_send(ui_Switch1, LV_EVENT_RELEASED, NULL);
            press_flag = 0;
        }
        lv_tick_inc(5);
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
