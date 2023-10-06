/**
 * @file lv_port_disp_templ.c
 *
 */

/*Copy this file as "lv_port_disp.c" and set this value to "1" to enable content*/
#if 1

/*********************
 *      INCLUDES
 *********************/
#include "lv_port_disp.h"
#include "spi_lcd.h"
#include "led_strip.h"
#include <stdbool.h>

#ifdef USE_LCD
#define MY_DISP_HOR_RES    320
#define MY_DISP_VER_RES    240
#else
#define MY_DISP_HOR_RES    16
#define MY_DISP_VER_RES    8
#endif


/*********************
 *      DEFINES
 *********************/
#ifndef MY_DISP_HOR_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen width, default value 320 is used for now.
    #define MY_DISP_HOR_RES    320
#endif

#ifndef MY_DISP_VER_RES
    #warning Please define or replace the macro MY_DISP_HOR_RES with the actual screen height, default value 240 is used for now.
    #define MY_DISP_VER_RES    240
#endif

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/
static void disp_init(void);

static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p);
//static void gpu_fill(lv_disp_drv_t * disp_drv, lv_color_t * dest_buf, lv_coord_t dest_width,
//        const lv_area_t * fill_area, lv_color_t color);

/**********************
 *  STATIC VARIABLES
 **********************/

/**********************
 *      MACROS
 **********************/

/**********************
 *   GLOBAL FUNCTIONS
 **********************/

void lv_port_disp_init(void)
{
    /*-------------------------
     * Initialize your display
     * -----------------------*/
    disp_init();

    /*-----------------------------
     * Create a buffer for drawing
     *----------------------------*/

    /**
     * LVGL requires a buffer where it internally draws the widgets.
     * Later this buffer will passed to your display driver's `flush_cb` to copy its content to your display.
     * The buffer has to be greater than 1 display row
     *
     * There are 3 buffering configurations:
     * 1. Create ONE buffer:
     *      LVGL will draw the display's content here and writes it to your display
     *
     * 2. Create TWO buffer:
     *      LVGL will draw the display's content to a buffer and writes it your display.
     *      You should use DMA to write the buffer's content to the display.
     *      It will enable LVGL to draw the next part of the screen to the other buffer while
     *      the data is being sent form the first buffer. It makes rendering and flushing parallel.
     *
     * 3. Double buffering
     *      Set 2 screens sized buffers and set disp_drv.full_refresh = 1.
     *      This way LVGL will always provide the whole rendered screen in `flush_cb`
     *      and you only need to change the frame buffer's address.
     */

    /* Example for 1) */
//    static lv_disp_draw_buf_t draw_buf_dsc_1;
//    static lv_color_t buf_1[MY_DISP_HOR_RES * 240];                          /*A buffer for 10 rows*/
//    lv_disp_draw_buf_init(&draw_buf_dsc_1, buf_1, NULL, MY_DISP_HOR_RES * 240);   /*Initialize the display buffer*/

//    /* Example for 2) */
//    static lv_disp_draw_buf_t draw_buf_dsc_2;
//    static lv_color_t buf_2_1[MY_DISP_HOR_RES * 10];                        /*A buffer for 10 rows*/
//    static lv_color_t buf_2_2[MY_DISP_HOR_RES * 10];                        /*An other buffer for 10 rows*/
//    lv_disp_draw_buf_init(&draw_buf_dsc_2, buf_2_1, buf_2_2, MY_DISP_HOR_RES * 10);   /*Initialize the display buffer*/

    /* Example for 3) also set disp_drv.full_refresh = 1 below*/
    static lv_disp_draw_buf_t draw_buf_dsc_3;
    EXT_RAM_BSS_ATTR static lv_color_t buf_3_1[MY_DISP_HOR_RES * MY_DISP_VER_RES] = {0};            /*A screen sized buffer*/
    EXT_RAM_BSS_ATTR static lv_color_t buf_3_2[MY_DISP_HOR_RES * MY_DISP_VER_RES] = {0};            /*Another screen sized buffer*/
    lv_disp_draw_buf_init(&draw_buf_dsc_3, buf_3_1, buf_3_2,
                          MY_DISP_VER_RES * 60);   /*Initialize the display buffer*/

    /*-----------------------------------
     * Register the display in LVGL
     *----------------------------------*/

    static lv_disp_drv_t disp_drv;                         /*Descriptor of a display driver*/
    lv_disp_drv_init(&disp_drv);                    /*Basic initialization*/

    /*Set up the functions to access to your display*/

    /*Set the resolution of the display*/
    disp_drv.hor_res = MY_DISP_HOR_RES;
    disp_drv.ver_res = MY_DISP_VER_RES;

    /*Used to copy the buffer's content to the display*/
    disp_drv.flush_cb = disp_flush;

    /*Set a display buffer*/
    disp_drv.draw_buf = &draw_buf_dsc_3;

    /*Required for Example 3)*/
    disp_drv.full_refresh = 1;

    /* Fill a memory array with a color if you have GPU.
     * Note that, in lv_conf.h you can enable GPUs that has built-in support in LVGL.
     * But if you have a different GPU you can use with this callback.*/
    //disp_drv.gpu_fill_cb = gpu_fill;

    /*Finally register the driver*/
    lv_disp_drv_register(&disp_drv);
}

/**********************
 *   STATIC FUNCTIONS
 **********************/

/*Initialize your display and the required peripherals.*/
static void disp_init(void)
{
    /*You code here*/
}

volatile bool disp_flush_enabled = true;

/* Enable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_enable_update(void)
{
    disp_flush_enabled = true;
}

/* Disable updating the screen (the flushing process) when disp_flush() is called by LVGL
 */
void disp_disable_update(void)
{
    disp_flush_enabled = false;
}

void LED_BGR565ToRGB(uint16_t rgb565, uint8_t *r, uint8_t *g, uint8_t *b)
{
    *r = (rgb565 >> 11) & 0x1f;
    *g = (rgb565 >> 5) & 0x3f;
    *b = rgb565 & 0x1f;
    *r <<= 3;
    *g <<= 2;
    *b <<= 3;
}
// 获取坐标对应的LED编号
uint16_t LED_GetXYNumber(uint16_t x, uint16_t y)
{
    // x < LED_WIDTH and y < LED_HEIGHT
    y = MY_DISP_VER_RES - y - 1;
    uint16_t num = 0;
    if (y % 2 == 0){
        num = y * MY_DISP_HOR_RES + x;
    } else {
        num = (y + 1) * MY_DISP_HOR_RES - x - 1;
    }
    return num;
}

led_strip_handle_t led_strip;
void LED_Flush(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t *color)
{
    uint16_t i, j;
    uint16_t k = 0;
    uint16_t c = 0;
    uint8_t r, g, b;

    for (i = y1; i <= y2; i++) {
        for (j = x1; j <= x2; j++) {
            LED_BGR565ToRGB(color[c], &r, &g, &b);
            c++;
            k = LED_GetXYNumber(j, i);
            led_strip_set_pixel(led_strip, k, r, g, b);
        }
    }
}
/*Flush the content of the internal buffer the specific area on the display
 *You can use DMA or any hardware acceleration to do this operation in the background but
 *'lv_disp_flush_ready()' has to be called when finished.*/
static void disp_flush(lv_disp_drv_t * disp_drv, const lv_area_t * area, lv_color_t * color_p)
{
    if(disp_flush_enabled) {
        /*The most simple case (but also the slowest) to put all pixels to the screen one-by-one*/
#ifdef USE_LCD
        LCD_Flush(area->x1, area->x2, area->y1, area->y2, (uint16_t *)color_p);
#else
        LED_Flush(area->x1, area->x2, area->y1, area->y2, (uint16_t *) color_p);
#endif
    }

    /*IMPORTANT!!!
     *Inform the graphics library that you are ready with the flushing*/
    lv_disp_flush_ready(disp_drv);
}



#else /*Enable this file at the top*/

/*This dummy typedef exists purely to silence -Wpedantic.*/
typedef int keep_pedantic_happy;
#endif
