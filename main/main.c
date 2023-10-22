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
//        vTaskDelay(pdMS_TO_TICKS(50));
//    }
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
//    WIFI_StaInit();
//    WEATHER_HttpInit();
    while (1) {
        if (WiFi_GetConnectStatus() == 1)
            WEATHER_HttpGet();

        vTaskDelay(pdMS_TO_TICKS(5000));
    }
}

int16_t id = 0; // id in 0 to 2
void KEY_UpHandler(KEY_Event event)
{
    if (event == PRESS_DOWN){
        printf("k1 press down\n");
        id--;
        if (id < 0)
            id = 18;
//        lv_obj_set_tile(guider_ui.screen_tileview_1, guider_ui.screen_tileview_1_tile_1, LV_ANIM_ON);
//        lv_obj_set_tile(guider_ui.screen_tileview_1, lv_obj_get_child(guider_ui.screen_tileview_1, id), LV_ANIM_ON);
        lv_obj_scroll_to_view(lv_obj_get_child(cont, id), LV_ANIM_ON);
    }

}

int16_t brightness = 100;
void KEY_DownHandler(KEY_Event event)
{
    if (event == PRESS_DOWN) {
        id++;
        if (id > 18)
            id= 0;
        printf("k2 press down\n");
//        lv_obj_set_tile(guider_ui.screen_tileview_1, lv_obj_get_child(guider_ui.screen_tileview_1, id), LV_ANIM_ON);
        lv_obj_scroll_to_view(lv_obj_get_child(cont, id), LV_ANIM_ON);
    }
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
//    lv_indev_t *indev = lv_indev_get_next(NULL);

//    if ((lv_indev_get_type(indev) == LV_INDEV_TYPE_KEYPAD) ||
//            lv_indev_get_type(indev) == LV_INDEV_TYPE_ENCODER) {
//        ESP_LOGI(TAG, "Input device type is keypad");
//        lv_indev_set_group(indev, g_btn_op_group);
//    }
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

//        p_dirent = readdir(p_dir_stream);
        char fn[64];
        lv_fs_dir_read(&dir, fn);
        printf("fn::%s\n", fn);
        lv_obj_t * btn = NULL;
        if ('\0' != fn[0]) {
//            lv_obj_t *btn = lv_list_add_btn(list, LV_SYMBOL_IMAGE, p_dirent->d_name);
            if (fn[0] == '/') {
                btn = lv_list_add_btn(list, LV_SYMBOL_DIRECTORY, &fn[1]);
            }
            else {
                btn = lv_list_add_btn(list, LV_SYMBOL_IMAGE, fn);
            }
            lv_group_add_obj(g_btn_op_group, btn);
            lv_obj_add_event_cb(btn, btn_event_cb, LV_EVENT_CLICKED, (void *) img);
        } else {
//            closedir(p_dir_stream);
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
    lv_obj_t * img = lv_img_create(lv_scr_act());
//    lv_img_set_src(img, "S:/bg.png");

    image_display();
//    lv_fs_file_t f;
//    lv_res_t res;
//    res = lv_fs_open(&f, "S:/tell5.jpg", LV_FS_MODE_RD);
//    if (res != LV_FS_RES_OK) printf("open file error, res == %d\n", res);
//
//    uint32_t num;
//    uint8_t buf[256];
//    res = lv_fs_read(&f, buf, 20, &num);
//
//    printf("read %ld bytes, file %s\n", num, buf);
//    if (num > 2)
//        buf[num - 1] = '\0';
//
//    lv_fs_close(&f);
//    setup_ui(&guider_ui)
//    custom_init(&guider_ui);
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
    while (1) {

        vTaskDelay(pdMS_TO_TICKS(10));
    }
}