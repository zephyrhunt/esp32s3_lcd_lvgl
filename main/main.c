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
#include "lvgl.h"
#include "time.h"
#include "esp_netif_sntp.h"
#include "esp_sntp.h"

//#include "ui.h"
#include "gui_guider.h"
#include "custom.h"
#define TAG "main"

#include "dirent.h"
/**
 * @brief 任务列表
 */
void LVTickTask(void *par);
void LVHandlerTask(void *pa);
void NETTask(void *par);
void LVUpStatusTask(void *par);
void KeyTask(void * par);

void time_sync_notification_cb(struct timeval *tv)
{
    ESP_LOGI(TAG, "Notification of a time synchronization event");
}

static void print_servers(void)
{
    ESP_LOGI(TAG, "List of configured NTP servers:");

    for (uint8_t i = 0; i < SNTP_MAX_SERVERS; ++i){
        if (esp_sntp_getservername(i)){
            ESP_LOGI(TAG, "server %d: %s", i, esp_sntp_getservername(i));
        } else {
            // we have either IPv4 or IPv6 address, let's print it
            char buff[48];
            ip_addr_t const *ip = esp_sntp_getserver(i);
            if (ipaddr_ntoa_r(ip, buff, 48) != NULL)
                ESP_LOGI(TAG, "server %d: %s", i, buff);
        }
    }
}

static void obtain_time(void)
{
    ESP_LOGI(TAG, "Initializing and starting SNTP");
    /*
     * This is the basic default config with one server and starting the service
     */
    esp_sntp_config_t config = ESP_NETIF_SNTP_DEFAULT_CONFIG("pool.ntp.org");
    config.sync_cb = time_sync_notification_cb;     // Note: This is only needed if we want

    esp_netif_sntp_init(&config);
    print_servers();

    // wait for time to be set
    time_t now = 0;
    struct tm timeinfo = { 0 };
    int retry = 0;
    const int retry_count = 30;
    while (esp_netif_sntp_sync_wait(200 / portTICK_PERIOD_MS) == ESP_ERR_TIMEOUT && ++retry < retry_count) {
        ESP_LOGI(TAG, "Waiting for system time to be set... (%d/%d)", retry, retry_count);
    }
    time(&now);
    localtime_r(&now, &timeinfo);

//    ESP_ERROR_CHECK( example_disconnect() );
    esp_netif_sntp_deinit();
}

time_t now;
struct tm timeinfo;
char strftime_buf[64];
void ntp_init()
{
    time(&now);
    localtime_r(&now, &timeinfo);
    // Is time set? If not, tm_year will be (1970 - 1900).
    if (timeinfo.tm_year < (2016 - 1900)) {
        ESP_LOGI(TAG, "Time is not set yet. Connecting to WiFi and getting time over NTP.");
        obtain_time();
        // update 'now' variable with current time
        time(&now);
    }
    // Set timezone to China Standard Time
    setenv("TZ", "CST-8", 1);
    tzset();
    localtime_r(&now, &timeinfo);
    strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
    ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);

    if (sntp_get_sync_mode() == SNTP_SYNC_MODE_SMOOTH) {
        struct timeval outdelta;
        while (sntp_get_sync_status() == SNTP_SYNC_STATUS_IN_PROGRESS) {
            adjtime(NULL, &outdelta);
            ESP_LOGI(TAG, "Waiting for adjusting time ... outdelta = %jd sec: %li ms: %li us",
                     (intmax_t)outdelta.tv_sec,
                     outdelta.tv_usec/1000,
                     outdelta.tv_usec%1000);
            vTaskDelay(2000 / portTICK_PERIOD_MS);
        }
    }
    const int deep_sleep_sec = 10;
    ESP_LOGI(TAG, "Entering deep sleep for %d seconds", deep_sleep_sec);
//    esp_deep_sleep(1000000LL * deep_sleep_sec);
}
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
    xTaskCreatePinnedToCore(KeyTask, "key_task", 4096, NULL, 3, NULL, 1);
    xTaskCreatePinnedToCore(LVHandlerTask, "lv_handler", 4096, NULL, 2, NULL, 1);

    xTaskCreatePinnedToCore(LVUpStatusTask, "lv_update_task", 4096, NULL, 4, NULL, 1);
    xTaskCreatePinnedToCore(NETTask, "net_task", 8192, NULL, 3, NULL, 0);

}


extern WeatherInfo_t weather_info;

extern lv_obj_t * cont;
/**
 * @brief 网络任务，连接WIFI，蓝牙等，更新数据
 * @param par
 */
void NETTask(void *par)
{
//    ble_init();
    WIFI_StaInit();
    WEATHER_HttpInit();
//    ntp_init();

    while (1) {

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
                    lv_obj_set_tile(guider_ui.screen_setting_tileview_setting, guider_ui.screen_setting_tileview_setting_tile_main, LV_ANIM_ON);
                    lv_cus_tile_set.is_child_focus = 0;
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
                            if (lv_obj_has_state(guider_ui.screen_setting_sw_wifi, LV_STATE_CHECKED)){
                                lv_obj_clear_state(guider_ui.screen_setting_sw_wifi, LV_STATE_CHECKED);
                            }
                            else {
                                lv_obj_add_state(guider_ui.screen_setting_sw_wifi, LV_STATE_CHECKED);
                                WIFI_Scan(); //添加到后台任务扫描
                                // scan once
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
        static TickType_t run_times = 0;
        run_times = xTaskGetTickCount();
        KEYC_TickInc();
        xSemaphoreGive(lv_semp);
        vTaskDelay(pdMS_TO_TICKS(10));
//        vTaskDelayUntil(&run_times, pdMS_TO_TICKS(10));
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

    vTaskDelay(pdMS_TO_TICKS(100));
//    custom_init(&guider_ui);
    while (1) {
        xSemaphoreTake(lv_semp, portMAX_DELAY);
//        uint8_t buf[20];
//        if (WiFi_GetConnectStatus() == 1) {
//            time(&now);
//            localtime_r(&now, &timeinfo);
//            strftime(strftime_buf, sizeof(strftime_buf), "%c", &timeinfo);
//            printf("day:%d,hour:%d,min:%d,sec:%d,Mon:%d,week:%d\n", timeinfo.tm_mday, timeinfo.tm_hour, timeinfo.tm_min, timeinfo.tm_sec, timeinfo.tm_mon, timeinfo.tm_wday);
//            ESP_LOGI(TAG, "The current date/time in Shanghai is: %s", strftime_buf);
//            sprintf(buf, "%2d", timeinfo.tm_hour);
//            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 0), buf);
//            sprintf(buf, "%02d", timeinfo.tm_min);
//            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 2), buf);
//            sprintf(buf, "%02d", timeinfo.tm_sec);
//            lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 4), buf);
//
//            if (timeinfo.tm_sec % 2) {
//                lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 1), ":");
//                lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 3), ":");
//            } else {
//                lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 1), " ");
//                lv_span_set_text(lv_spangroup_get_child(guider_ui.screen_main_text_time, 3), " ");
//            }
//        }
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