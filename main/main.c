#include <nvs_flash.h>
#include "stdio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <freertos/event_groups.h>
#include "lvgl.h"
#include "spi_lcd.h"
#include "lv_port_disp.h"
#include "lv_port_fs.h"
#include "led_strip.h"
#include "driver/gpio.h"
#include "lv_demos.h"
#include "cJSON.h"
#include "esp_log.h"
#include "wific.h"
#include "weather_get.h"
#include "audio_element.h"
#include "audio_pipeline.h"

//#include "esp_gatt_common_api.h"
#include "ble_gatts_module.h"
//#include "board.h"
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "gpio_key.h"
#include "sd_card.h"

//#include "ui.h"
#include "gui_guider.h"
#define TAG "main"

/**
 * @brief 任务列表
 */
void LVTickTask(void *par);
void LVHandlerTask(void *pa);
void NETTask(void *par);
void LVUpStatusTask(void *par);

/**
 * @brief 主函数，初始化其他任务，完成后删除
 */
void app_main(void)
{
    esp_err_t ret = nvs_flash_init();
    if (ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND) {
        ESP_ERROR_CHECK(nvs_flash_erase());
        ret = nvs_flash_init();
    }
    ESP_ERROR_CHECK(ret);

//    #ifndef LV_USE_GUIDER_SIMULATOR // or LV_USE_GUIDER_SIMULATOR == 0...
//    // (MCU specific Code)
//    #endif
    xTaskCreatePinnedToCore(LVTickTask, "lv_tick_task", 4096, NULL, 5, NULL, 1);
    xTaskCreatePinnedToCore(LVHandlerTask, "lv_handler", 4096, NULL, 2, NULL, 1);
    xTaskCreatePinnedToCore(LVUpStatusTask, "lv_update_task", 4096, NULL, 4, NULL, 1);
    xTaskCreatePinnedToCore(NETTask, "net_task", 4096, NULL, 3, NULL, 0);

    // it will be deleted
//    while (1) {
//
//
//        vTaskDelay(pdMS_TO_TICKS(50));
//    }
}


extern WeatherInfo_t weather_info;

/**
 * @brief 网络任务，连接WIFI，蓝牙等，更新数据
 * @param par
 */
void NETTask(void *par)
{
//    ble_init();
//    WIFI_StaInit();
//    WEATHER_HttpInit();
    while (1) {
        if (WiFi_GetConnectStatus() == 1)
            WEATHER_HttpGet();

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

void KEY_UpHandler(KEY_Event event)
{
    if (event == PRESS_DOWN)
        printf("k1 press down\n");

}

int16_t brightness = 100;
void KEY_DownHandler(KEY_Event event)
{
    if (event == PRESS_DOWN)
        printf("k2 press down\n");
}
void KEY_SUpHandler(KEY_Event event)
{
    if (event == PRESS_DOWN){
        printf("k3 press down\n");
        brightness += 20;
        if (brightness > 255)
            brightness = 255;
        LCD_SetBlck(brightness);
    } else if (event == LONG_PRESS_HOLD) {
        brightness++;
        if (brightness > 255)
            brightness = 255;
        LCD_SetBlck(brightness);
    }
}
void KEY_SDownHandler(KEY_Event event)
{
    if (event == PRESS_DOWN){
        brightness -= 20;
        if (brightness < 10)
            brightness = 10;
        LCD_SetBlck(brightness);
        printf("k4 press down\n");
    } else if (event == LONG_PRESS_HOLD) {
        brightness --;
        if (brightness < 10)
            brightness = 10;
        LCD_SetBlck(brightness);
    }

}

void KEY_SMidHandler(KEY_Event event)
{
    if (event == PRESS_DOWN){
        printf("k5 press down\n");
    }
}
KEY_Dev key_up;
KEY_Dev key_down;
KEY_Dev key_sup;
KEY_Dev key_smid;
KEY_Dev key_sdown;
/**
 * @brief LVGL任务，LVGL_Tick和Handle
 * @param None
 */
void LVTickTask(void *par)
{
    KEYC_Init();
    KEYC_Rigister(&key_up, KEYC_GetKeyLevel, 0, 0);
    KEYC_Attach(&key_up, KEY_UpHandler);
    KEYC_Start(&key_up);

    KEYC_Rigister(&key_down, KEYC_GetKeyLevel, 0, 1);
    KEYC_Attach(&key_down, KEY_DownHandler);
    KEYC_Start(&key_down);

    KEYC_Rigister(&key_sup, KEYC_GetKeyLevel, 0, 2);
    KEYC_Attach(&key_sup, KEY_SUpHandler);
    KEYC_Start(&key_sup);

    KEYC_Rigister(&key_sdown, KEYC_GetKeyLevel, 0, 3);
    KEYC_Attach(&key_sdown, KEY_SDownHandler);
    KEYC_Start(&key_sdown);

    KEYC_Rigister(&key_smid, KEYC_GetKeyLevel, 0, 4);
    KEYC_Attach(&key_smid, KEY_SMidHandler);
    KEYC_Start(&key_smid);

    while (1) {
        static TickType_t run_times = 0;
        run_times = xTaskGetTickCount();
        KEYC_TickInc();
        lv_tick_inc(10);
        vTaskDelayUntil(&run_times, pdMS_TO_TICKS(10));
    }
}
lv_ui guider_ui;
void LVHandlerTask(void *pa)
{
    lv_init();
    lv_port_disp_init();
    lv_port_fs_init();
    setup_ui(&guider_ui);
//    ui_init();
    while (1) {
        lv_timer_handler();
        vTaskDelay(pdMS_TO_TICKS(10));
    }

}
/**
 * @brief 更新状态任务，刷新UI逻辑
 * @param NONE
 */
void LVUpStatusTask(void *par)
{
    static uint8_t set_flag = 0;
    vTaskDelay(pdMS_TO_TICKS(1000));
    while (1) {

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}