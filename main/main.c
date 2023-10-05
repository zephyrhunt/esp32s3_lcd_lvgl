#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "lvgl.h"
#include "spi_lcd.h"
#include "lv_port_disp.h"

void example_lvgl_demo_ui(lv_disp_t *disp);

void app_main(void)
{
    lv_disp_t *disp = NULL;
    lv_init();
    LCD_Init();
    lv_port_disp_init();
    example_lvgl_demo_ui(disp);
    while (1) {
        printf("Hello world!\n");
        lv_tick_inc(5);
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
}
