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
#include "esp_bt.h"
#include "esp_bt_main.h"
#include "esp_bt_device.h"
#include "gpio_key.h"
#include "sd_card.h"
#include "lvgl.h"
#include "time.h"

#include "esp_wifi.h"
#include "net_time.h"
//#include "ui.h"
#include "gui_guider.h"
#include "custom.h"
#define TAG "main"

#include "dirent.h"

typedef struct {
  uint8_t is_wifi_connected;
  uint8_t is_wifi_scaining;
  uint8_t wait_wifi_list_update;
    uint8_t wait_time_update;
    uint8_t time_update;
    uint8_t day_update;

    uint8_t wait_weather_update; // 2h更新一次
    uint8_t weather_update; // 2h更新一次
}sys_status_t;

extern uint8_t wifi_connect_status;
sys_status_t sys_status = {
  .is_wifi_connected = 0,
  .is_wifi_scaining = 0,
  .wait_wifi_list_update = 0,
  .wait_time_update = 0,
  .time_update = 0,
    .day_update = 0,
    .wait_weather_update = 0,
    .weather_update = 0,
};

/**
 * @brief 任务列表
 */
void LVTickTask(void *par);
void LVHandlerTask(void *pa);
void NETTask(void *par);
void LVUpStatusTask(void *par);
void KeyTask(void * par);
void WIFI_ScanTask(void *p);

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
    xTaskCreatePinnedToCore(KeyTask, "key_task", 4096, NULL, 4, NULL, 1);
    xTaskCreatePinnedToCore(LVHandlerTask, "lv_handler", 4096, NULL, 3, NULL, 1);

    xTaskCreatePinnedToCore(NETTask, "net_task", 8192, NULL, 2, NULL, 0);
    xTaskCreatePinnedToCore(WIFI_ScanTask, "wifi_scan_task", 4096, NULL, 6, NULL, 0); //scan 不要被打断

}


lv_cus_item_t lv_cus_wifi_item = {
    .id = 0,
    .id_max = 1,
    .id_min = 0,
    .is_child_focus = 0
};

extern char wifi_ssid[20][40];
SemaphoreHandle_t scan_semp = NULL;
void WIFI_ScanTask(void *p)
{
    WIFI_StaInit(); // 开机默认去找FLASH
    scan_semp = xSemaphoreCreateBinary();
    while (1) {
        xSemaphoreTake(scan_semp, portMAX_DELAY);
        sys_status.is_wifi_scaining = 1;
        uint16_t num = WIFI_Scan(); //scan的时候不能stop
        if(num == 0) num = 1;
        lv_obj_clean(guider_ui.screen_setting_list_wifi);
        lv_cus_wifi_item.id_max = num - 1;
        lv_cus_wifi_item.is_child_focus = 1;
        sys_status.is_wifi_scaining = 0;
        sys_status.wait_wifi_list_update = 1;
    }
}

void WIFI_ListAdd(uint8_t id)
{
    lv_style_t style;
    lv_style_set_bg_color(&style, lv_color_hex(0xd49292));

    lv_obj_t *btn = lv_list_add_btn(guider_ui.screen_setting_list_wifi, NULL, wifi_ssid[id]);
    lv_obj_add_style(btn, &style, LV_PART_MAIN|LV_STATE_FOCUSED);
    lv_group_remove_obj(btn);

}

extern lv_obj_t * cont;
/**
 * @brief 网络任务，连接WIFI，蓝牙等，更新数据
 * @param par
 */
void NETTask(void *par)
{
    WEATHER_HttpInit();
    static uint32_t run_times = 0;
    while (1) {

        if (sys_status.wait_time_update && sys_status.is_wifi_connected) {
            uint8_t is_update = SNTP_TimeUpdate();
            if (is_update) {
                sys_status.wait_time_update = 0;
                sys_status.time_update = 1; //表示开机后已经更新时间
                run_times = 0;
                lv_obj_t * item = lv_obj_get_child(guider_ui.screen_setting_list_wifi, lv_cus_wifi_item.id);
                lv_obj_set_style_bg_color(item, lv_color_hex(0x00ff00), LV_PART_MAIN|LV_STATE_FOCUSED);
            }
        }

        if (sys_status.time_update && sys_status.is_wifi_connected) {
            if (run_times % 100 == 0) {
                WEATHER_HttpGet(); //1分钟20次
                sys_status.weather_update = 1;
            }
        }

        run_times++;
        sys_status.is_wifi_connected = wifi_connect_status;
//        if (sys_status.wait_weather_update) {
//            uint8_t is_update = WEATHER_HttpGet();
//            if (is_update) {
//                sys_status.wait_weather_update = 0;
//                sys_status.weather_update = 1;
//            }
//        }
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

// 0是btn selected
lv_cus_item_t lv_cus_cont_item = {
    .id = 1,
    .id_max = 5,
    .id_min = 1,
    .is_child_focus = 0
};

lv_cus_item_t lv_cus_tile_set = {
    .id = 0,
    .id_max = 3,
    .id_min = 0,
    .is_child_focus = 0 //是否在子项目下
};

lv_cus_item_t lv_cus_list_main = {
    .id = 0,
    .id_max = 3,
    .id_min = 0,
    .is_child_focus = 0
};


// back
void KEY_UpHandler(KEY_Event event)
{
    switch (event) {
        case SINGLE_CLICK:
            if (lv_scr_act() == guider_ui.screen_main) {
                if (lv_cus_is_display(guider_ui.screen_main_cont_app) == 1)
                    lv_cus_toggle(guider_ui.screen_main_cont_app);
            } else if (lv_scr_act() == guider_ui.screen_setting) {
                if (lv_cus_tile_set.is_child_focus == 0)
                    lv_scr_load_anim(guider_ui.screen_main, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
                else {
                    if (lv_cus_wifi_item.is_child_focus == 1) {
                        lv_cus_focus_none(guider_ui.screen_setting_list_wifi, &lv_cus_wifi_item);
                        lv_cus_wifi_item.is_child_focus = 0;
                    } else {
                        lv_obj_set_tile(guider_ui.screen_setting_tileview_setting, guider_ui.screen_setting_tileview_setting_tile_main, LV_ANIM_ON);
                        lv_cus_tile_set.is_child_focus = 0;
                    }
                }
            } else if (lv_scr_act() == guider_ui.screen_image) {
                lv_scr_load_anim(guider_ui.screen_main, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
            }

            break;
        default:
            break;

    }
}

int16_t brightness = 50;
void KEY_DownHandler(KEY_Event event)
{
    switch (event) {
        case SINGLE_CLICK:
            if (lv_scr_act() == guider_ui.screen_main) {
                if (lv_cus_is_display(guider_ui.screen_main_cont_app) == 0) {
                    lv_cus_toggle(guider_ui.screen_main_cont_app);
                } else {
                    switch (lv_cus_cont_item.id) {
                        case 1:lv_cus_toggle(guider_ui.screen_main_cont_app);
                            break;
                        case 2:
                            lv_scr_load_anim(guider_ui.screen_image, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
                            break;
                        case 3:break;
                        case 4:
                            lv_scr_load_anim(guider_ui.screen_setting, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
                            lv_cus_focus_now(guider_ui.screen_setting_list_setting, &lv_cus_list_main);
                            lv_cus_tile_set.is_child_focus = 0; // focus main
                            break;
                        case 5:
                            lv_cus_disp_time(guider_ui.screen_main_slider_light, 1500);
                            lv_cus_toggle(guider_ui.screen_main_cont_app);
                            break;
                    }
                }
            } else if (lv_scr_act() == guider_ui.screen_setting) {
                if (lv_cus_tile_set.is_child_focus == 0) {
                    int8_t id = lv_cus_list_main.id + 1;
                    lv_obj_set_tile(guider_ui.screen_setting_tileview_setting, lv_obj_get_child(guider_ui.screen_setting_tileview_setting, id), LV_ANIM_ON);
                    lv_cus_tile_set.is_child_focus = 1;
                    lv_cus_tile_set.id = id;
                    // get child id
                } else {
                    switch (lv_cus_tile_set.id) {
                        case 1:
                            if (lv_cus_wifi_item.is_child_focus == 0) {
                                if (lv_obj_has_state(guider_ui.screen_setting_sw_wifi, LV_STATE_CHECKED)){
                                    lv_obj_clear_state(guider_ui.screen_setting_sw_wifi, LV_STATE_CHECKED);
                                    if (sys_status.is_wifi_scaining == 0) {
                                        esp_wifi_stop(); // 扫描的时候不能关闭
                                        lv_obj_clean(guider_ui.screen_setting_list_wifi);
                                        lv_cus_wifi_item.is_child_focus = 0;
                                        sys_status.is_wifi_connected = 0;
                                    }
                                }
                                else {
                                    lv_obj_add_state(guider_ui.screen_setting_sw_wifi, LV_STATE_CHECKED);
                                    lv_list_add_btn(guider_ui.screen_setting_list_wifi, NULL, "WIFI IS Scanning.........");
                                    xSemaphoreGive(scan_semp); // scan once cant stop
                                }
                            } else {
                                // wifi connect
                                if (sys_status.is_wifi_connected == 0) {
                                    char *ssid = wifi_ssid[lv_cus_wifi_item.id];
//                                    strcpy(ssid, wifi_ssid[lv_cus_wifi_item.id]);
                                    wifi_config_t wifi_config = { };
//                                    strcpy(wifi_config.sta.password,"123456788");
                                    memcpy(wifi_config.sta.ssid, ssid, strlen(ssid));
                                    memcpy(wifi_config.sta.password, "123456788", 10);
                                    esp_err_t  err;
                                    ESP_ERROR_CHECK(esp_wifi_set_mode(WIFI_MODE_STA) );
                                    ESP_ERROR_CHECK(esp_wifi_set_config(WIFI_IF_STA, &wifi_config) );
                                    err = esp_wifi_connect();
                                    // 尝试连接
                                    if (err == ESP_OK) {
//                                        ESP_LOGI(TAG, "wifi connect success");
//                                        sys_status.is_wifi_connected = 1;
                                        lv_obj_t * item = lv_obj_get_child(guider_ui.screen_setting_list_wifi, lv_cus_wifi_item.id);
                                        lv_obj_set_style_bg_color(item, lv_color_hex(0xffff00), LV_PART_MAIN|LV_STATE_FOCUSED);
                                        lv_cus_wifi_item.is_child_focus = 0;
                                        sys_status.wait_time_update = 1;
                                    } else {
                                        ESP_LOGI(TAG, "wifi connect failed");
//                                        sys_status.is_wifi_connected = 0;
                                        sys_status.wait_time_update = 0;
                                    }
                                }

                            }
                            break;
                        case 2:break;
                        case 3:break;
                        default:break;

                    }
                }
            }
            break;
        default:
            break;

    }
}

void KEY_SUpHandler(KEY_Event event)
{
    switch (event) {
        case PRESS_DOWN:
            if (lv_scr_act() == guider_ui.screen_main) {
                if (lv_cus_is_display(guider_ui.screen_main_cont_app)) {
                    lv_coord_t x = lv_obj_get_x(lv_obj_get_child(guider_ui.screen_main_cont_app, lv_cus_to_prev(&lv_cus_cont_item))) - 2;
                    lv_cus_set_x(guider_ui.screen_main_btn_select, x);
                } else{
                    brightness += 10;
                    if (brightness > 100)
                        brightness = 100;
                    LCD_SetBlck(brightness);
                    lv_cus_disp_time(guider_ui.screen_main_slider_light, 1500);
                    lv_slider_set_value(guider_ui.screen_main_slider_light, brightness, LV_ANIM_ON);
                }
            } else if (lv_scr_act() == guider_ui.screen_setting) {
                if (lv_cus_tile_set.is_child_focus == 0) {
                    lv_cus_focus_prev(guider_ui.screen_setting_list_setting, &lv_cus_list_main);
                } else {
                    if (lv_cus_wifi_item.is_child_focus == 1)
                        lv_cus_focus_prev(guider_ui.screen_setting_list_wifi, &lv_cus_wifi_item);
                }
            }
            break;
        default:
            break;
    }
}

void KEY_SDownHandler(KEY_Event event)
{
    switch (event) {
        case PRESS_DOWN:
            if (lv_scr_act() == guider_ui.screen_main) {
                if (lv_cus_is_display(guider_ui.screen_main_cont_app)) {
                    lv_coord_t x = lv_obj_get_x(lv_obj_get_child(guider_ui.screen_main_cont_app, lv_cus_to_next(&lv_cus_cont_item))) - 2;
                    lv_cus_set_x(guider_ui.screen_main_btn_select, x);
                } else {
                    brightness -= 10;
                    if (brightness < 0)
                        brightness = 0;
                    LCD_SetBlck(brightness);
                    lv_cus_disp_time(guider_ui.screen_main_slider_light, 1500);
                    lv_slider_set_value(guider_ui.screen_main_slider_light, brightness, LV_ANIM_ON);
                }
            } else if (lv_scr_act() == guider_ui.screen_setting) {
                if (lv_cus_tile_set.is_child_focus == 0) {
                    lv_cus_focus_next(guider_ui.screen_setting_list_setting, &lv_cus_list_main);
                } else {
                    if (lv_cus_wifi_item.is_child_focus == 1)
                        lv_cus_focus_next(guider_ui.screen_setting_list_wifi, &lv_cus_wifi_item);
                }
            }
            printf("k4 single click\n");
            break;
        default:
            break;
    }
}

void KEY_SMidHandler(KEY_Event event)
{
    switch (event) {
        case SINGLE_CLICK:
            // 软件切换确认
            switch (lv_cus_cont_item.id ) {
                case 1: // main
                    break;
                case 2: // picture
                    lv_scr_load_anim(guider_ui.screen_image, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
                    break;
                case 3: // reader
                    break;
                case 4: // setting
                    lv_scr_load_anim(guider_ui.screen_setting, LV_SCR_LOAD_ANIM_NONE, 10, 0, false);
                    break;
                case 5:
                    lv_cus_toggle(guider_ui.screen_main_cont_app);
                default:break;
            }
        default:
            break;

    }
}

SemaphoreHandle_t lv_semp = NULL;
void KeyTask(void * par)
{
    lv_semp = xSemaphoreCreateMutex();

    KEYC_Init();
    while (1) {
        xSemaphoreTake(lv_semp, portMAX_DELAY);
        KEYC_TickInc();
        xSemaphoreGive(lv_semp);
        vTaskDelay(pdMS_TO_TICKS(10));
    }
}

/**
 * @brief LVGL任务，LVGL_Tick和Handle
 * @param None
 */
void LVTickTask(void *par)
{
    while (1) {
        static TickType_t run_times = 0;
        run_times = xTaskGetTickCount();
        lv_tick_inc(10);
        vTaskDelayUntil(&run_times, pdMS_TO_TICKS(10));
    }
}

static lv_group_t *g_btn_op_group = NULL;
static void btn_event_cb(lv_event_t *event)
{
    lv_obj_t *img = (lv_obj_t *) event->user_data;
    const char *file_name = lv_list_get_btn_text(lv_obj_get_parent(event->target), event->target);
    char *file_name_with_path = (char *) heap_caps_malloc(256, MALLOC_CAP_INTERNAL | MALLOC_CAP_8BIT);

    if (NULL != file_name_with_path) {
        /* Get full file name with mount point and folder path */
        strcpy(file_name_with_path, "S:/spiffs/");
        strcat(file_name_with_path, file_name);

        /* Set src of image with file name */
        lv_img_set_src(img, file_name_with_path);

        /* Align object */
        lv_obj_align(img, LV_ALIGN_CENTER, 80, 0);

        /* Only for debug */
        ESP_LOGI(TAG, "Display image file : %s", file_name_with_path);

        /* Don't forget to free allocated memory */
        free(file_name_with_path);
    }
}
static void image_display(void)
{
    g_btn_op_group = lv_group_create();

    lv_obj_t *list = lv_list_create(lv_scr_act());
    lv_obj_set_size(list, 170, 220);
    lv_obj_set_style_border_width(list, 0, LV_STATE_DEFAULT);
    lv_obj_align(list, LV_ALIGN_LEFT_MID, -15, 0);

    lv_obj_t *img = lv_img_create(lv_scr_act());
    /* Get file name in storage */
    lv_fs_dir_t dir;
    lv_fs_dir_open(&dir, "S:/");
    /* Scan files in storage */
    while (true) {
        char fn[64];
        lv_fs_dir_read(&dir, fn);
        lv_obj_t * btn = NULL;
        if ('\0' != fn[0]) {
            if (fn[0] == '/') {
                btn = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, &fn[1]);
            }
            else {
                btn = lv_list_add_btn(list, LV_SYMBOL_IMAGE, fn);
            }
            lv_group_add_obj(g_btn_op_group, btn);
            lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, (void *) img);
        } else {
            lv_fs_dir_close(&dir);
            break;
        }
    }
}

lv_ui guider_ui;

void LVHandlerTask(void *pa)
{
    lv_init();
    lv_port_disp_init();
    lv_port_fs_init();
    setup_ui(&guider_ui);
    setup_scr_screen_image(&guider_ui);
    setup_scr_screen_setting(&guider_ui);
    lv_obj_add_flag(guider_ui.screen_main_list_musics, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(guider_ui.screen_main_cont_app, LV_OBJ_FLAG_HIDDEN);
    lv_obj_del(guider_ui.screen_setting_list_wifi_item0);

    vTaskDelay(pdMS_TO_TICKS(100));
    static uint32_t run_times = 0; // 40ms左右
    while (1) {
        xSemaphoreTake(lv_semp, portMAX_DELAY);
        char buf[30];
        if (sys_status.is_wifi_connected) {

        }

        static int i = 0;
        if (sys_status.wait_wifi_list_update == 1) {
            WIFI_ListAdd(i);

            if (sys_status.wait_wifi_list_update == 1) {
                lv_cus_wifi_item.id = 0;
                lv_cus_focus_now(guider_ui.screen_setting_list_wifi, &lv_cus_wifi_item); //不要发送event，发送event和建立冲突
                lv_cus_wifi_item.is_child_focus = 1;
            }
            if (i == lv_cus_wifi_item.id_max) {
                lv_cus_wifi_item.id = 0;
                lv_cus_focus_now(guider_ui.screen_setting_list_wifi, &lv_cus_wifi_item);
                sys_status.wait_wifi_list_update = 0;
                i = -1;
            }
            i++;
        }

        if (sys_status.time_update == 1 && sys_status.day_update == 0) {
            time(&now);
            localtime_r(&now, &timeinfo);
//            printf("day:%d,hour:%d,min:%d,sec:%d,Mon:%d,week:%d\n", timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_mon, timeinfo.tm_wday);
            sprintf(buf, "%2d", timeinfo.tm_hour);
            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 0), buf); // spend lot time
            sprintf(buf, "%02d", timeinfo.tm_min);
            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 2), buf);
            sprintf(buf, "%02d", timeinfo.tm_sec);
            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 4), buf);

            if (run_times % 1000 == 0) {
                sys_status.day_update = 1;
                vTaskDelay(pdMS_TO_TICKS(20));
            }

            if (timeinfo.tm_sec % 2) {
                lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 3), ":");
            } else {
                lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 3), " ");
            }
            run_times++;
        }

        if (sys_status.day_update == 1) {
            sys_status.day_update = 0;
//            run_times = 0;
            uint16_t year = timeinfo.tm_year+1900;
            sprintf(buf, "%4d年", year);
            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_day, 0), buf);
            sprintf(buf, "星期%d", timeinfo.tm_wday);
            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_day, 2), buf);
            uint16_t mon = timeinfo.tm_mon+1;
            sprintf(buf, "%2d月%2d日", mon, timeinfo.tm_mday);
            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_day, 3), buf);
        }

        if (sys_status.weather_update == 1) {
            lv_label_set_text(guider_ui.screen_main_label_weather, weather_info.day_weather);
            lv_chart_series_t * screen_main_chart_temp_0 = lv_chart_get_series_next(guider_ui.screen_main_chart_temp, NULL);
            lv_chart_set_next_value(guider_ui.screen_main_chart_temp, screen_main_chart_temp_0, weather_info.temp_low);
            lv_chart_set_next_value(guider_ui.screen_main_chart_temp, screen_main_chart_temp_0, weather_info.temp_high);
            sys_status.weather_update = 0;
        }

        lv_timer_handler();
        xSemaphoreGive(lv_semp);
        vTaskDelay(pdMS_TO_TICKS(20));
    }
}
/**
 * @brief 更新状态任务，刷新UI逻辑
 * @param NONE
 */
void LVUpStatusTask(void *par)
{
    while (1) {

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}