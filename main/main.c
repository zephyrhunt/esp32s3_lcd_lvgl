#include <nvs_flash.h>
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <freertos/event_groups.h>
#include "lvgl.h"
#include "spi_lcd.h"
#include "lv_port_disp.h"
#include "led_strip.h"
#include "ui.h"
#include "driver/gpio.h"
#include "lv_demos.h"
#include "cJSON.h"
#include "esp_log.h"
#include "wific.h"
#include "weather_get.h"

#define TAG "main"

void LVTask(void *par);
void NETTask(void *par);
void LVUpStatusTask(void *par);
void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

    lv_init();
    LCD_Init();
    gpio_config_t io_conf = {};
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = (1ULL<<0);
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    xTaskCreatePinnedToCore(LVTask, "lv_task", 4096, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(LVUpStatusTask, "lv_update_task", 4096, NULL, 4, NULL, 1);
    xTaskCreatePinnedToCore(NETTask, "net_task", 4096, NULL, 3, NULL, 0);

    while (1) {

        static uint8_t press_flag = 0;
        if (gpio_get_level(0) == 0 && press_flag == 0)
        {
            printf("Hello world!\n");
            if (lv_scr_act() == ui_ScreenMain1)
                lv_scr_load(ui_ScreenMain);
//                lv_event_send(ui_ImgBtnWeather2, LV_EVENT_CLICKED, 0);
            else
                lv_scr_load(ui_ScreenMain1);
//                lv_event_send(ui_ImgBtnControl, LV_EVENT_CLICKED, 0);

            press_flag = 1;
        } else if (gpio_get_level(0) == 1){
//            lv_event_send(ui_ImgBtnPlay, LV_EVENT_RELEASED, 0);
            press_flag = 0;
        }

        vTaskDelay(pdMS_TO_TICKS(50));
    }
}

void NETTask(void *par)
{
    WIFI_StaInit();
    WEATHER_HttpInit();
    while (1) {
        WEATHER_HttpGet();
        vTaskDelay(pdMS_TO_TICKS(10000));
    }
}

void LVTask(void *par)
{
    lv_port_disp_init();
    ui_init();
    while (1) {
        static TickType_t run_times = 0;
        run_times = xTaskGetTickCount();
        lv_tick_inc(10);
        lv_timer_handler();
        vTaskDelayUntil(&run_times, pdMS_TO_TICKS(10));
//        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

void LVUpStatusTask(void *par)
{
    while (1) {

        vTaskDelay(pdMS_TO_TICKS(100));

    }
}