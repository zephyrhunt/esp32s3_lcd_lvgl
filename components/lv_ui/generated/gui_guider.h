/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef GUI_GUIDER_H
#define GUI_GUIDER_H
#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl.h"

typedef struct
{
  
	lv_obj_t *screen_main;
	bool screen_main_del;
	lv_obj_t *screen_main_cont_timer;
	lv_obj_t *screen_main_cont_days;
	lv_obj_t *screen_main_text_day;
	lv_obj_t *screen_main_cont_time;
	lv_obj_t *screen_main_text_time;
	lv_obj_t *screen_main_cont_weather;
	lv_obj_t *screen_main_list_weatehr;
	lv_obj_t *screen_main_list_weatehr_item0;
	lv_obj_t *screen_main_list_weatehr_item1;
	lv_obj_t *screen_main_list_weatehr_item2;
	lv_obj_t *screen_main_list_weatehr_item3;
	lv_obj_t *screen_main_label_2;
	lv_obj_t *screen_main_chart_temp;
	lv_obj_t *screen_main_label_3;
	lv_obj_t *screen_main_label_4;
	lv_obj_t *screen_main_label_temp_high;
	lv_obj_t *screen_main_label_nichijou;
	lv_obj_t *screen_main_cont_music;
	lv_obj_t *screen_main_img_music;
	lv_obj_t *screen_main_line_1;
	lv_obj_t *screen_main_img_play_last;
	lv_obj_t *screen_main_img_play_next;
	lv_obj_t *screen_main_img_play;
	lv_obj_t *screen_main_img_love;
	lv_obj_t *screen_main_bar_play;
	lv_obj_t *screen_main_img_voice;
	lv_obj_t *screen_main_img_mute;
	lv_obj_t *screen_main_label_music;
	lv_obj_t *screen_main_label_art;
	lv_obj_t *screen_main_label_time;
	lv_obj_t *screen_main_btn_app1;
	lv_obj_t *screen_main_btn_app1_label;
	lv_obj_t *screen_main_img_menu1;
	lv_obj_t *screen_main_list_musics;
	lv_obj_t *screen_main_list_musics_item0;
	lv_obj_t *screen_main_cont_app;
	lv_obj_t *screen_main_btn_select;
	lv_obj_t *screen_main_btn_select_label;
	lv_obj_t *screen_main_img_main;
	lv_obj_t *screen_main_img_img_read;
	lv_obj_t *screen_main_img_reader;
	lv_obj_t *screen_main_img_setting;
	lv_obj_t *screen_main_img_light;
	lv_obj_t *screen_main_slider_light;
	lv_obj_t *screen_setting;
	bool screen_setting_del;
	lv_obj_t *screen_setting_tileview_setting;
	lv_obj_t *screen_setting_tileview_setting_tile_main;
	lv_obj_t *screen_setting_tileview_setting_tile_wifi;
	lv_obj_t *screen_setting_tileview_setting_tile_ble;
	lv_obj_t *screen_setting_tileview_setting_tile_uart;
	lv_obj_t *screen_setting_list_1;
	lv_obj_t *screen_setting_list_1_item0;
	lv_obj_t *screen_setting_list_1_item1;
	lv_obj_t *screen_setting_img_menu2;
	lv_obj_t *screen_setting_img_home2;
}lv_ui;

void ui_init_style(lv_style_t * style);
void init_scr_del_flag(lv_ui *ui);
void setup_ui(lv_ui *ui);
extern lv_ui guider_ui;

void setup_scr_screen_main(lv_ui *ui);
void setup_scr_screen_setting(lv_ui *ui);
LV_IMG_DECLARE(_5729377_forecast_windy_weather_storm_climate_alpha_64x64);
LV_IMG_DECLARE(_5729383_forecast_rain_cloud_weather_raining_alpha_64x64);
LV_IMG_DECLARE(_5729378_sunny_sun_weather_climate_forecast_alpha_64x64);
LV_IMG_DECLARE(_5729385_forecast_moon_weather_night_crescent_climate_alpha_64x64);
LV_IMG_DECLARE(_music2_alpha_70x70);
LV_IMG_DECLARE(_play_last_alpha_15x15);
LV_IMG_DECLARE(_play_next_alpha_15x15);
LV_IMG_DECLARE(_play_alpha_15x15);
LV_IMG_DECLARE(_love_alpha_15x15);
LV_IMG_DECLARE(_voice_alpha_15x15);
LV_IMG_DECLARE(_voice_mute_alpha_15x15);
LV_IMG_DECLARE(_menu_alpha_20x20);
LV_IMG_DECLARE(_love_alpha_30x30);
LV_IMG_DECLARE(_picture_alpha_30x30);
LV_IMG_DECLARE(_reader_alpha_30x30);
LV_IMG_DECLARE(_setting1_alpha_30x30);
LV_IMG_DECLARE(_nichijoubg_alpha_30x30);

LV_IMG_DECLARE(_nichijoubg_52x52);
LV_IMG_DECLARE(_wifi1_alpha_20x20);
LV_IMG_DECLARE(_bluetooth30_30_alpha_20x20);
LV_IMG_DECLARE(_menu_alpha_20x20);
LV_IMG_DECLARE(_home_alpha_20x20);

LV_FONT_DECLARE(lv_font_simsun_28)
LV_FONT_DECLARE(lv_font_Abel_regular_28)
LV_FONT_DECLARE(lv_font_YournameD7CentralNarrow_28)
LV_FONT_DECLARE(lv_font_YournameD7CentralNarrow_40)
LV_FONT_DECLARE(lv_font_montserratMedium_12)
LV_FONT_DECLARE(lv_font_simsun_24)
LV_FONT_DECLARE(lv_font_montserratMedium_16)
LV_FONT_DECLARE(lv_font_Abel_regular_12)
LV_FONT_DECLARE(lv_font_simsun_12)


#ifdef __cplusplus
}
#endif
#endif
