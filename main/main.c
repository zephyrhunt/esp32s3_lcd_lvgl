#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "spi_lcd.h"
#include "lv_port_disp.h"
#include "led_strip.h"
#include "ui.h"
#include "driver/gpio.h"
#include "lv_demos.h"


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


void LED_Flush(uint16_t x1, uint16_t x2, uint16_t y1, uint16_t y2, uint16_t *color);
extern  led_strip_handle_t led_strip;

void app_main(void)
{
    lv_disp_t *disp = NULL;
    lv_init();
    LCD_Init();
    lv_port_disp_init();
//    example_lvgl_demo_ui(disp);

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


//    ui_init();
//    lv_demo_benchmark();
    lv_demo_music();
//    lv_demo_benchmark();
//    lv_demo_benchmark_set_max_speed(1);

    while (1) {
        static uint8_t press_flag = 0;
        static uint8_t bar_val = 0;
        static uint8_t inc_flag = 1;
        static int16_t pos_x = 0;

//         led_strip_refresh(led_strip);
//        if (gpio_get_level(0) == 0 && press_flag == 0)
//        {
//            printf("Hello world!\n");
//
//            lv_event_send(ui_Button1, LV_EVENT_PRESSED, NULL);
//            press_flag = 1;
//        } else if (gpio_get_level(0) == 1){
//            lv_event_send(ui_Button1, LV_EVENT_RELEASED, NULL);
//            press_flag = 0;
//        }
////
//        if (bar_val %20 == 0)pos_x--;
//        if (pos_x == -160 )pos_x = 0;
//        if (inc_flag == 1)
//            bar_val++;
//        else
//            bar_val--;
////        lv_bar_set_value(ui_Bar1, bar_val, LV_ANIM_ON);
//
//        if (bar_val == 100) {
//            inc_flag = 0;
//        }
//        if (bar_val == 0){
//            inc_flag = 1;
//        }
        lv_tick_inc(20);
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
