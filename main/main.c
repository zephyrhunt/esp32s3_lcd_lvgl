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
#include "ui.h"
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
void LVHandlerTask(void *pa)
{
    lv_init();
    lv_port_disp_init();
    lv_port_fs_init();
    ui_init();
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
        if (WiFi_GetConnectStatus() == 1 && set_flag == 0){
            lv_obj_set_style_img_recolor_opa(ui_ImageWifi, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(ui_ImageWifi1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(ui_ImageWifi2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(ui_ImageWifi3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
            set_flag = 1;
        }
        else if (set_flag == 1 && WiFi_GetConnectStatus() == 0) {
            lv_obj_set_style_img_recolor_opa(ui_ImageWifi, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(ui_ImageWifi1, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(ui_ImageWifi2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
            lv_obj_set_style_img_recolor_opa(ui_ImageWifi3, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
            set_flag = 0;
        }

        lv_label_set_text_fmt(ui_Weather, "Weather:%s", weather_info.weather);
        lv_fs_file_t f;
        lv_res_t res;

        res = lv_fs_open(&f, "S:/nihao.txt", LV_FS_MODE_RD);
        if (res != LV_FS_RES_OK) printf("open file error, res == %d\n", res);

        uint32_t num;
        uint8_t buf[20];
        res = lv_fs_read(&f, buf, 20, &num);

        printf("read %ld bytes, file %s\n", num, buf);
        if (num > 2)
            buf[num - 1] = '\0';

        lv_fs_close(&f);

        lv_label_set_text_fmt(ui_LabelDate, "Date:%s", buf);
        lv_label_set_text_fmt(ui_LabelReport, "The highest temperature is %s°, the lowest is %s°.\n The journey of a thousand miles begins with a single step.\n", weather_info.temp_high, weather_info.temp_low);

        static int16_t slider_value = 0;
        static uint8_t press_flag = 0;
        static uint8_t is_inc = 1;
        if (gpio_get_level(1) == 0 && press_flag == 0)
        {
            if (lv_scr_act() == ui_ScreenMain)
                lv_scr_load_anim(ui_ScreenMain1, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
            else if (lv_scr_act() == ui_ScreenMain1)
                lv_scr_load_anim(ui_ScreenMain2, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
            else if (lv_scr_act() == ui_ScreenMain2)
                lv_scr_load_anim(ui_ScreenMain3, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
            else if (lv_scr_act() == ui_ScreenMain3)
                lv_scr_load_anim(ui_ScreenMain, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
            press_flag = 1;
        } else if (gpio_get_level(1) == 1){
//            lv_event_send(ui_ImgBtnPlay, LV_EVENT_RELEASED, 0);
            press_flag = 0;
        }
//
        if (lv_scr_act() == ui_ScreenMain2) {
            lv_slider_set_value(ui_Slider1, slider_value*3, LV_ANIM_ON);
        } else if (lv_scr_act() == ui_ScreenMain3) {
            lv_obj_scroll_to_y(ui_Group, slider_value*2, LV_ANIM_ON);
        }

        if (is_inc)
            slider_value++;
        else
            slider_value--;

        if (slider_value >= 30) {
            is_inc = 0;
        } else if (slider_value <= 0)
            is_inc = 1;

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}