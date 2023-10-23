/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "lvgl.h"
#include <stdio.h>
#include "gui_guider.h"
#include "events_init.h"
#include "widgets_init.h"
#include "custom.h"


void setup_scr_screen_main(lv_ui *ui)
{
	//Write codes screen_main
	ui->screen_main = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_main, 320, 240);

	//Write style for screen_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main, lv_color_hex(0x26B08C), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_cont_timer
	ui->screen_main_cont_timer = lv_obj_create(ui->screen_main);
	lv_obj_set_pos(ui->screen_main_cont_timer, 10, 5);
	lv_obj_set_size(ui->screen_main_cont_timer, 185, 120);
	lv_obj_set_scrollbar_mode(ui->screen_main_cont_timer, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main_cont_timer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_cont_timer, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_main_cont_timer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_main_cont_timer, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_main_cont_timer, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_cont_timer, 7, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_cont_timer, 116, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_cont_timer, lv_color_hex(0xcefffc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_cont_days
	ui->screen_main_cont_days = lv_obj_create(ui->screen_main_cont_timer);
	lv_obj_set_pos(ui->screen_main_cont_days, 5, 56);
	lv_obj_set_size(ui->screen_main_cont_days, 200, 60);
	lv_obj_set_scrollbar_mode(ui->screen_main_cont_days, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main_cont_days, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_cont_days, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_main_cont_days, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_main_cont_days, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_main_cont_days, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_cont_days, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_cont_days, 83, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_cont_days, lv_color_hex(0xf52cc3), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_text_day
	ui->screen_main_text_day = lv_spangroup_create(ui->screen_main_cont_days);
	lv_spangroup_set_align(ui->screen_main_text_day, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_main_text_day, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_main_text_day, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_main_text_day_span;
	screen_main_text_day_span = lv_spangroup_new_span(ui->screen_main_text_day);
	lv_span_set_text(screen_main_text_day_span, "2023年\n");
	lv_style_set_text_color(&screen_main_text_day_span->style, lv_color_hex(0xaa379d));
	lv_style_set_text_decor(&screen_main_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_day_span->style, &lv_font_simsun_28);
	screen_main_text_day_span = lv_spangroup_new_span(ui->screen_main_text_day);
	lv_span_set_text(screen_main_text_day_span, "  ");
	lv_style_set_text_color(&screen_main_text_day_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_main_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_day_span->style, &lv_font_Abel_regular_28);
	screen_main_text_day_span = lv_spangroup_new_span(ui->screen_main_text_day);
	lv_span_set_text(screen_main_text_day_span, "星期一");
	lv_style_set_text_color(&screen_main_text_day_span->style, lv_color_hex(0x15604c));
	lv_style_set_text_decor(&screen_main_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_day_span->style, &lv_font_simsun_28);
	screen_main_text_day_span = lv_spangroup_new_span(ui->screen_main_text_day);
	lv_span_set_text(screen_main_text_day_span, "10月21日");
	lv_style_set_text_color(&screen_main_text_day_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_main_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_day_span->style, &lv_font_simsun_28);
	screen_main_text_day_span = lv_spangroup_new_span(ui->screen_main_text_day);
	lv_span_set_text(screen_main_text_day_span, " HUST");
	lv_style_set_text_color(&screen_main_text_day_span->style, lv_color_hex(0x343434));
	lv_style_set_text_decor(&screen_main_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_day_span->style, &lv_font_YournameD7CentralNarrow_28);
	lv_obj_set_pos(ui->screen_main_text_day, -3, 1);
	lv_obj_set_size(ui->screen_main_text_day, 181, 59);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_text_day_main_main_default
	static lv_style_t style_screen_main_text_day_main_main_default;
	ui_init_style(&style_screen_main_text_day_main_main_default);
	
	lv_style_set_border_width(&style_screen_main_text_day_main_main_default, 0);
	lv_style_set_radius(&style_screen_main_text_day_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_main_text_day_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_text_day_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_text_day_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_text_day_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_text_day_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_main_text_day_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_text_day, &style_screen_main_text_day_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_main_text_day);

	//Write codes screen_main_cont_time
	ui->screen_main_cont_time = lv_obj_create(ui->screen_main_cont_timer);
	lv_obj_set_pos(ui->screen_main_cont_time, -20, -1);
	lv_obj_set_size(ui->screen_main_cont_time, 200, 40);
	lv_obj_set_scrollbar_mode(ui->screen_main_cont_time, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main_cont_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_cont_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_main_cont_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_main_cont_time, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_main_cont_time, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_cont_time, 12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_cont_time, 110, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_cont_time, lv_color_hex(0x134aa8), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_text_time
	ui->screen_main_text_time = lv_spangroup_create(ui->screen_main_cont_time);
	lv_spangroup_set_align(ui->screen_main_text_time, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_main_text_time, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_main_text_time, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_main_text_time_span;
	screen_main_text_time_span = lv_spangroup_new_span(ui->screen_main_text_time);
	lv_span_set_text(screen_main_text_time_span, "00");
	lv_style_set_text_color(&screen_main_text_time_span->style, lv_color_hex(0xaa379d));
	lv_style_set_text_decor(&screen_main_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_time_span->style, &lv_font_YournameD7CentralNarrow_40);
	screen_main_text_time_span = lv_spangroup_new_span(ui->screen_main_text_time);
	lv_span_set_text(screen_main_text_time_span, ":");
	lv_style_set_text_color(&screen_main_text_time_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_main_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_time_span->style, &lv_font_YournameD7CentralNarrow_40);
	screen_main_text_time_span = lv_spangroup_new_span(ui->screen_main_text_time);
	lv_span_set_text(screen_main_text_time_span, "00");
	lv_style_set_text_color(&screen_main_text_time_span->style, lv_color_hex(0xff6500));
	lv_style_set_text_decor(&screen_main_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_time_span->style, &lv_font_YournameD7CentralNarrow_40);
	screen_main_text_time_span = lv_spangroup_new_span(ui->screen_main_text_time);
	lv_span_set_text(screen_main_text_time_span, ":");
	lv_style_set_text_color(&screen_main_text_time_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_main_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_time_span->style, &lv_font_YournameD7CentralNarrow_28);
	screen_main_text_time_span = lv_spangroup_new_span(ui->screen_main_text_time);
	lv_span_set_text(screen_main_text_time_span, "00");
	lv_style_set_text_color(&screen_main_text_time_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&screen_main_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_main_text_time_span->style, &lv_font_YournameD7CentralNarrow_28);
	lv_obj_set_pos(ui->screen_main_text_time, 31, -2);
	lv_obj_set_size(ui->screen_main_text_time, 200, 40);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_text_time_main_main_default
	static lv_style_t style_screen_main_text_time_main_main_default;
	ui_init_style(&style_screen_main_text_time_main_main_default);
	
	lv_style_set_border_width(&style_screen_main_text_time_main_main_default, 0);
	lv_style_set_radius(&style_screen_main_text_time_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_main_text_time_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_main_text_time_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_text_time_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_text_time_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_text_time_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_main_text_time_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_text_time, &style_screen_main_text_time_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_main_text_time);

	//Write codes screen_main_cont_weather
	ui->screen_main_cont_weather = lv_obj_create(ui->screen_main);
	lv_obj_set_pos(ui->screen_main_cont_weather, 200, 5);
	lv_obj_set_size(ui->screen_main_cont_weather, 110, 120);
	lv_obj_set_scrollbar_mode(ui->screen_main_cont_weather, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_main_cont_weather, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_main_cont_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_cont_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_main_cont_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_main_cont_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_main_cont_weather, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_cont_weather, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_cont_weather, 116, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_cont_weather, lv_color_hex(0xcefffc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_list_weatehr
	ui->screen_main_list_weatehr = lv_list_create(ui->screen_main_cont_weather);
	ui->screen_main_list_weatehr_item0 = lv_list_add_btn(ui->screen_main_list_weatehr, &_5729377_forecast_windy_weather_storm_climate_alpha_64x64, "windy");
	ui->screen_main_list_weatehr_item1 = lv_list_add_btn(ui->screen_main_list_weatehr, &_5729383_forecast_rain_cloud_weather_raining_alpha_64x64, "rain");
	ui->screen_main_list_weatehr_item2 = lv_list_add_btn(ui->screen_main_list_weatehr, &_5729378_sunny_sun_weather_climate_forecast_alpha_64x64, "sun");
	ui->screen_main_list_weatehr_item3 = lv_list_add_btn(ui->screen_main_list_weatehr, &_5729385_forecast_moon_weather_night_crescent_climate_alpha_64x64, "moon");
	lv_obj_set_pos(ui->screen_main_list_weatehr, 40, 5);
	lv_obj_set_size(ui->screen_main_list_weatehr, 64, 64);
	lv_obj_set_scrollbar_mode(ui->screen_main_list_weatehr, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_list_weatehr_main_main_default
	static lv_style_t style_screen_main_list_weatehr_main_main_default;
	ui_init_style(&style_screen_main_list_weatehr_main_main_default);
	
	lv_style_set_pad_top(&style_screen_main_list_weatehr_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_list_weatehr_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_list_weatehr_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_list_weatehr_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_main_list_weatehr_main_main_default, 0);
	lv_style_set_border_width(&style_screen_main_list_weatehr_main_main_default, 0);
	lv_style_set_radius(&style_screen_main_list_weatehr_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_main_list_weatehr_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_list_weatehr, &style_screen_main_list_weatehr_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_list_weatehr_main_scrollbar_default
	static lv_style_t style_screen_main_list_weatehr_main_scrollbar_default;
	ui_init_style(&style_screen_main_list_weatehr_main_scrollbar_default);
	
	lv_style_set_radius(&style_screen_main_list_weatehr_main_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_main_list_weatehr_main_scrollbar_default, 0);
	lv_obj_add_style(ui->screen_main_list_weatehr, &style_screen_main_list_weatehr_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_list_weatehr_extra_btns_main_default
	static lv_style_t style_screen_main_list_weatehr_extra_btns_main_default;
	ui_init_style(&style_screen_main_list_weatehr_extra_btns_main_default);
	
	lv_style_set_pad_top(&style_screen_main_list_weatehr_extra_btns_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_list_weatehr_extra_btns_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_list_weatehr_extra_btns_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_list_weatehr_extra_btns_main_default, 0);
	lv_style_set_border_width(&style_screen_main_list_weatehr_extra_btns_main_default, 0);
	lv_style_set_text_color(&style_screen_main_list_weatehr_extra_btns_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_main_list_weatehr_extra_btns_main_default, &lv_font_montserratMedium_12);
	lv_style_set_radius(&style_screen_main_list_weatehr_extra_btns_main_default, 0);
	lv_style_set_bg_opa(&style_screen_main_list_weatehr_extra_btns_main_default, 0);
	lv_obj_add_style(ui->screen_main_list_weatehr_item3, &style_screen_main_list_weatehr_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_main_list_weatehr_item2, &style_screen_main_list_weatehr_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_main_list_weatehr_item1, &style_screen_main_list_weatehr_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_main_list_weatehr_item0, &style_screen_main_list_weatehr_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_list_weatehr_extra_texts_main_default
	static lv_style_t style_screen_main_list_weatehr_extra_texts_main_default;
	ui_init_style(&style_screen_main_list_weatehr_extra_texts_main_default);
	
	lv_style_set_pad_top(&style_screen_main_list_weatehr_extra_texts_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_list_weatehr_extra_texts_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_list_weatehr_extra_texts_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_list_weatehr_extra_texts_main_default, 0);
	lv_style_set_border_width(&style_screen_main_list_weatehr_extra_texts_main_default, 0);
	lv_style_set_text_color(&style_screen_main_list_weatehr_extra_texts_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_main_list_weatehr_extra_texts_main_default, &lv_font_montserratMedium_12);
	lv_style_set_radius(&style_screen_main_list_weatehr_extra_texts_main_default, 3);
	lv_style_set_bg_opa(&style_screen_main_list_weatehr_extra_texts_main_default, 0);

	//Write codes screen_main_label_2
	ui->screen_main_label_2 = lv_label_create(ui->screen_main_cont_weather);
	lv_label_set_text(ui->screen_main_label_2, "刮风");
	lv_label_set_long_mode(ui->screen_main_label_2, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_main_label_2, -4, 25);
	lv_obj_set_size(ui->screen_main_label_2, 60, 24);

	//Write style for screen_main_label_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_2, lv_color_hex(0x480a92), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_2, &lv_font_simsun_24, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_2, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_chart_temp
	ui->screen_main_chart_temp = lv_chart_create(ui->screen_main_cont_weather);
	lv_chart_set_type(ui->screen_main_chart_temp, LV_CHART_TYPE_BAR);
	lv_chart_set_div_line_count(ui->screen_main_chart_temp, 0, 0);
	lv_chart_set_point_count(ui->screen_main_chart_temp, 2);
	lv_chart_set_range(ui->screen_main_chart_temp, LV_CHART_AXIS_PRIMARY_Y, 0, 40);
	lv_chart_set_range(ui->screen_main_chart_temp, LV_CHART_AXIS_SECONDARY_Y, 0, 2);
	lv_chart_set_zoom_x(ui->screen_main_chart_temp, 256);
	lv_chart_set_zoom_y(ui->screen_main_chart_temp, 256);
	lv_chart_series_t * screen_main_chart_temp_0 = lv_chart_add_series(ui->screen_main_chart_temp, lv_color_hex(0x8d666c), LV_CHART_AXIS_PRIMARY_Y);
	lv_chart_set_next_value(ui->screen_main_chart_temp, screen_main_chart_temp_0, 12);
	lv_chart_set_next_value(ui->screen_main_chart_temp, screen_main_chart_temp_0, 28);
	lv_obj_set_pos(ui->screen_main_chart_temp, 5, 44);
	lv_obj_set_size(ui->screen_main_chart_temp, 75, 61);
	lv_obj_set_scrollbar_mode(ui->screen_main_chart_temp, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main_chart_temp, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_chart_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_main_chart_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_chart_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->screen_main_chart_temp, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->screen_main_chart_temp, lv_color_hex(0xe73131), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->screen_main_chart_temp, 176, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_chart_temp, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_main_chart_temp, Part: LV_PART_TICKS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_text_color(ui->screen_main_chart_temp, lv_color_hex(0x5a2424), LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_chart_temp, &lv_font_montserratMedium_12, LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_line_width(ui->screen_main_chart_temp, 2, LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->screen_main_chart_temp, lv_color_hex(0x8f2020), LV_PART_TICKS|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->screen_main_chart_temp, 255, LV_PART_TICKS|LV_STATE_DEFAULT);

	//Write codes screen_main_label_3
	ui->screen_main_label_3 = lv_label_create(ui->screen_main_cont_weather);
	lv_label_set_text(ui->screen_main_label_3, "Temp");
	lv_label_set_long_mode(ui->screen_main_label_3, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_main_label_3, 68, 76);
	lv_obj_set_size(ui->screen_main_label_3, 45, 16);

	//Write style for screen_main_label_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_3, lv_color_hex(0x990303), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_3, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_3, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_label_4
	ui->screen_main_label_4 = lv_label_create(ui->screen_main_cont_weather);
	lv_label_set_text(ui->screen_main_label_4, "12");
	lv_label_set_long_mode(ui->screen_main_label_4, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_main_label_4, 14, 105);
	lv_obj_set_size(ui->screen_main_label_4, 18, 15);

	//Write style for screen_main_label_4, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_4, lv_color_hex(0x626262), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_4, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_4, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_4, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_4, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_label_temp_high
	ui->screen_main_label_temp_high = lv_label_create(ui->screen_main_cont_weather);
	lv_label_set_text(ui->screen_main_label_temp_high, "28");
	lv_label_set_long_mode(ui->screen_main_label_temp_high, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_main_label_temp_high, 52, 105);
	lv_obj_set_size(ui->screen_main_label_temp_high, 18, 15);

	//Write style for screen_main_label_temp_high, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_temp_high, lv_color_hex(0x5c5c5c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_temp_high, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_temp_high, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_temp_high, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_temp_high, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_label_nichijou
	ui->screen_main_label_nichijou = lv_label_create(ui->screen_main);
	lv_label_set_text(ui->screen_main_label_nichijou, "我们所经历的每一个日常，也许都是不断发生的奇迹！");
	lv_label_set_long_mode(ui->screen_main_label_nichijou, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_set_pos(ui->screen_main_label_nichijou, 10, 208);
	lv_obj_set_size(ui->screen_main_label_nichijou, 300, 29);

	//Write style for screen_main_label_nichijou, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_nichijou, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_main_label_nichijou, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_main_label_nichijou, lv_color_hex(0x6bb8c0), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_main_label_nichijou, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_nichijou, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_nichijou, lv_color_hex(0x595959), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_nichijou, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_nichijou, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_nichijou, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_nichijou, 110, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_label_nichijou, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_nichijou, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_cont_music
	ui->screen_main_cont_music = lv_obj_create(ui->screen_main);
	lv_obj_set_pos(ui->screen_main_cont_music, 10, 130);
	lv_obj_set_size(ui->screen_main_cont_music, 300, 74);
	lv_obj_set_scrollbar_mode(ui->screen_main_cont_music, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main_cont_music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_cont_music, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_cont_music, 104, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_cont_music, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_cont_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_music
	ui->screen_main_img_music = lv_img_create(ui->screen_main_cont_music);
	lv_obj_add_flag(ui->screen_main_img_music, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_music, &_music2_alpha_70x70);
	lv_img_set_pivot(ui->screen_main_img_music, 50,50);
	lv_img_set_angle(ui->screen_main_img_music, 0);
	lv_obj_set_pos(ui->screen_main_img_music, 10, 0);
	lv_obj_set_size(ui->screen_main_img_music, 70, 70);

	//Write style for screen_main_img_music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_main_img_music, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_line_1
	ui->screen_main_line_1 = lv_line_create(ui->screen_main_cont_music);
	static lv_point_t screen_main_line_1[] ={{0, 0},{0, 60},};
	lv_line_set_points(ui->screen_main_line_1, screen_main_line_1, 2);
	lv_obj_set_pos(ui->screen_main_line_1, 90, 5);
	lv_obj_set_size(ui->screen_main_line_1, 6, 60);

	//Write style for screen_main_line_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_line_width(ui->screen_main_line_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_color(ui->screen_main_line_1, lv_color_hex(0x14b319), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_opa(ui->screen_main_line_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_line_rounded(ui->screen_main_line_1, true, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_play_last
	ui->screen_main_img_play_last = lv_img_create(ui->screen_main_cont_music);
	lv_obj_add_flag(ui->screen_main_img_play_last, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_play_last, &_play_last_alpha_15x15);
	lv_img_set_pivot(ui->screen_main_img_play_last, 0,0);
	lv_img_set_angle(ui->screen_main_img_play_last, 0);
	lv_obj_set_pos(ui->screen_main_img_play_last, 151, 51);
	lv_obj_set_size(ui->screen_main_img_play_last, 15, 15);

	//Write style for screen_main_img_play_last, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_main_img_play_last, 235, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->screen_main_img_play_last, lv_color_hex(0x246700), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_main_img_play_last, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_play_next
	ui->screen_main_img_play_next = lv_img_create(ui->screen_main_cont_music);
	lv_obj_add_flag(ui->screen_main_img_play_next, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_play_next, &_play_next_alpha_15x15);
	lv_img_set_pivot(ui->screen_main_img_play_next, 0,0);
	lv_img_set_angle(ui->screen_main_img_play_next, 0);
	lv_obj_set_pos(ui->screen_main_img_play_next, 217, 51);
	lv_obj_set_size(ui->screen_main_img_play_next, 15, 15);

	//Write style for screen_main_img_play_next, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_main_img_play_next, 235, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->screen_main_img_play_next, lv_color_hex(0x246700), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_main_img_play_next, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_play
	ui->screen_main_img_play = lv_img_create(ui->screen_main_cont_music);
	lv_obj_add_flag(ui->screen_main_img_play, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_play, &_play_alpha_15x15);
	lv_img_set_pivot(ui->screen_main_img_play, 8,8);
	lv_img_set_angle(ui->screen_main_img_play, 0);
	lv_obj_set_pos(ui->screen_main_img_play, 184, 51);
	lv_obj_set_size(ui->screen_main_img_play, 15, 15);

	//Write style for screen_main_img_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_main_img_play, 235, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->screen_main_img_play, lv_color_hex(0x246700), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_main_img_play, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_love
	ui->screen_main_img_love = lv_img_create(ui->screen_main_cont_music);
	lv_obj_add_flag(ui->screen_main_img_love, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_love, &_love_alpha_15x15);
	lv_img_set_pivot(ui->screen_main_img_love, 0,0);
	lv_img_set_angle(ui->screen_main_img_love, 0);
	lv_obj_set_pos(ui->screen_main_img_love, 103, 51);
	lv_obj_set_size(ui->screen_main_img_love, 15, 15);

	//Write style for screen_main_img_love, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_main_img_love, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_bar_play
	ui->screen_main_bar_play = lv_bar_create(ui->screen_main_cont_music);
	lv_obj_set_style_anim_time(ui->screen_main_bar_play, 1000, 0);
	lv_bar_set_mode(ui->screen_main_bar_play, LV_BAR_MODE_NORMAL);
	lv_bar_set_value(ui->screen_main_bar_play, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_main_bar_play, 95, 44);
	lv_obj_set_size(ui->screen_main_bar_play, 200, 4);

	//Write style for screen_main_bar_play, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_bar_play, 70, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_bar_play, lv_color_hex(0x007fff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_bar_play, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_bar_play, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_main_bar_play, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_bar_play, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_bar_play, lv_color_hex(0xfa6300), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_bar_play, LV_GRAD_DIR_HOR, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_main_bar_play, lv_color_hex(0xb70adf), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_bar_play, 10, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write codes screen_main_img_voice
	ui->screen_main_img_voice = lv_img_create(ui->screen_main_cont_music);
	lv_obj_add_flag(ui->screen_main_img_voice, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_voice, &_voice_alpha_15x15);
	lv_img_set_pivot(ui->screen_main_img_voice, 0,0);
	lv_img_set_angle(ui->screen_main_img_voice, 0);
	lv_obj_set_pos(ui->screen_main_img_voice, 275, 51);
	lv_obj_set_size(ui->screen_main_img_voice, 15, 15);

	//Write style for screen_main_img_voice, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_main_img_voice, 235, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->screen_main_img_voice, lv_color_hex(0x246700), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_main_img_voice, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_mute
	ui->screen_main_img_mute = lv_img_create(ui->screen_main_cont_music);
	lv_obj_add_flag(ui->screen_main_img_mute, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_mute, &_voice_mute_alpha_15x15);
	lv_img_set_pivot(ui->screen_main_img_mute, 0,0);
	lv_img_set_angle(ui->screen_main_img_mute, 0);
	lv_obj_set_pos(ui->screen_main_img_mute, 275, 51);
	lv_obj_set_size(ui->screen_main_img_mute, 15, 15);
	lv_obj_add_flag(ui->screen_main_img_mute, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_main_img_mute, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_recolor_opa(ui->screen_main_img_mute, 235, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_recolor(ui->screen_main_img_mute, lv_color_hex(0x246700), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_img_opa(ui->screen_main_img_mute, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_label_music
	ui->screen_main_label_music = lv_label_create(ui->screen_main_cont_music);
	lv_label_set_text(ui->screen_main_label_music, "By my side");
	lv_label_set_long_mode(ui->screen_main_label_music, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_set_pos(ui->screen_main_label_music, 100, 10);
	lv_obj_set_size(ui->screen_main_label_music, 125, 14);

	//Write style for screen_main_label_music, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_music, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_music, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_music, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_music, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_music, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_label_art
	ui->screen_main_label_art = lv_label_create(ui->screen_main_cont_music);
	lv_label_set_text(ui->screen_main_label_art, "Radwimps");
	lv_label_set_long_mode(ui->screen_main_label_art, LV_LABEL_LONG_CLIP);
	lv_obj_set_pos(ui->screen_main_label_art, 100, 25);
	lv_obj_set_size(ui->screen_main_label_art, 140, 14);

	//Write style for screen_main_label_art, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_art, lv_color_hex(0x5b5b5b), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_art, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_art, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_art, LV_TEXT_ALIGN_LEFT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_art, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_label_time
	ui->screen_main_label_time = lv_label_create(ui->screen_main_cont_music);
	lv_label_set_text(ui->screen_main_label_time, "02:00/4:50");
	lv_label_set_long_mode(ui->screen_main_label_time, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_main_label_time, 204, 25);
	lv_obj_set_size(ui->screen_main_label_time, 90, 12);

	//Write style for screen_main_label_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_label_time, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_label_time, &lv_font_Abel_regular_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_main_label_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_label_time, LV_TEXT_ALIGN_RIGHT, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_label_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_btn_app1
	ui->screen_main_btn_app1 = lv_btn_create(ui->screen_main);
	ui->screen_main_btn_app1_label = lv_label_create(ui->screen_main_btn_app1);
	lv_label_set_text(ui->screen_main_btn_app1_label, "");
	lv_label_set_long_mode(ui->screen_main_btn_app1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_main_btn_app1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_main_btn_app1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_main_btn_app1, 310, 207);
	lv_obj_set_size(ui->screen_main_btn_app1, 10, 30);

	//Write style for screen_main_btn_app1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_btn_app1, 58, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_btn_app1, lv_color_hex(0xa50000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_main_btn_app1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_btn_app1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_btn_app1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_btn_app1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_btn_app1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_btn_app1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_menu1
	ui->screen_main_img_menu1 = lv_img_create(ui->screen_main);
	lv_obj_add_flag(ui->screen_main_img_menu1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_menu1, &_menu_alpha_20x20);
	lv_img_set_pivot(ui->screen_main_img_menu1, 50,50);
	lv_img_set_angle(ui->screen_main_img_menu1, 0);
	lv_obj_set_pos(ui->screen_main_img_menu1, 300, 117);
	lv_obj_set_size(ui->screen_main_img_menu1, 20, 20);
	lv_obj_add_flag(ui->screen_main_img_menu1, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_main_img_menu1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_main_img_menu1, 93, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_list_musics
	ui->screen_main_list_musics = lv_list_create(ui->screen_main);
	ui->screen_main_list_musics_item0 =lv_list_add_text(ui->screen_main_list_musics, "Musics");
	lv_obj_set_pos(ui->screen_main_list_musics, 247, 25);
	lv_obj_set_size(ui->screen_main_list_musics, 73, 182);
	lv_obj_set_scrollbar_mode(ui->screen_main_list_musics, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_main_list_musics, LV_OBJ_FLAG_HIDDEN);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_list_musics_main_main_default
	static lv_style_t style_screen_main_list_musics_main_main_default;
	ui_init_style(&style_screen_main_list_musics_main_main_default);
	
	lv_style_set_pad_top(&style_screen_main_list_musics_main_main_default, 5);
	lv_style_set_pad_left(&style_screen_main_list_musics_main_main_default, 5);
	lv_style_set_pad_right(&style_screen_main_list_musics_main_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_main_list_musics_main_main_default, 5);
	lv_style_set_bg_opa(&style_screen_main_list_musics_main_main_default, 215);
	lv_style_set_bg_color(&style_screen_main_list_musics_main_main_default, lv_color_hex(0xd86700));
	lv_style_set_bg_grad_dir(&style_screen_main_list_musics_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_grad_color(&style_screen_main_list_musics_main_main_default, lv_color_hex(0x35a605));
	lv_style_set_border_width(&style_screen_main_list_musics_main_main_default, 0);
	lv_style_set_radius(&style_screen_main_list_musics_main_main_default, 3);
	lv_style_set_shadow_width(&style_screen_main_list_musics_main_main_default, 0);
	lv_obj_add_style(ui->screen_main_list_musics, &style_screen_main_list_musics_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_list_musics_main_scrollbar_default
	static lv_style_t style_screen_main_list_musics_main_scrollbar_default;
	ui_init_style(&style_screen_main_list_musics_main_scrollbar_default);
	
	lv_style_set_radius(&style_screen_main_list_musics_main_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_main_list_musics_main_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_main_list_musics_main_scrollbar_default, lv_color_hex(0xffffff));
	lv_obj_add_style(ui->screen_main_list_musics, &style_screen_main_list_musics_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_list_musics_extra_btns_main_default
	static lv_style_t style_screen_main_list_musics_extra_btns_main_default;
	ui_init_style(&style_screen_main_list_musics_extra_btns_main_default);
	
	lv_style_set_pad_top(&style_screen_main_list_musics_extra_btns_main_default, 0);
	lv_style_set_pad_left(&style_screen_main_list_musics_extra_btns_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_list_musics_extra_btns_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_list_musics_extra_btns_main_default, 0);
	lv_style_set_border_width(&style_screen_main_list_musics_extra_btns_main_default, 0);
	lv_style_set_text_color(&style_screen_main_list_musics_extra_btns_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_main_list_musics_extra_btns_main_default, &lv_font_montserratMedium_12);
	lv_style_set_radius(&style_screen_main_list_musics_extra_btns_main_default, 3);
	lv_style_set_bg_opa(&style_screen_main_list_musics_extra_btns_main_default, 144);
	lv_style_set_bg_color(&style_screen_main_list_musics_extra_btns_main_default, lv_color_hex(0x340000));

	//Write style state: LV_STATE_DEFAULT for &style_screen_main_list_musics_extra_texts_main_default
	static lv_style_t style_screen_main_list_musics_extra_texts_main_default;
	ui_init_style(&style_screen_main_list_musics_extra_texts_main_default);
	
	lv_style_set_pad_top(&style_screen_main_list_musics_extra_texts_main_default, 5);
	lv_style_set_pad_left(&style_screen_main_list_musics_extra_texts_main_default, 0);
	lv_style_set_pad_right(&style_screen_main_list_musics_extra_texts_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_main_list_musics_extra_texts_main_default, 5);
	lv_style_set_border_width(&style_screen_main_list_musics_extra_texts_main_default, 2);
	lv_style_set_border_opa(&style_screen_main_list_musics_extra_texts_main_default, 255);
	lv_style_set_border_color(&style_screen_main_list_musics_extra_texts_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_main_list_musics_extra_texts_main_default, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_text_color(&style_screen_main_list_musics_extra_texts_main_default, lv_color_hex(0xeaeaea));
	lv_style_set_text_font(&style_screen_main_list_musics_extra_texts_main_default, &lv_font_Abel_regular_12);
	lv_style_set_radius(&style_screen_main_list_musics_extra_texts_main_default, 2);
	lv_style_set_bg_opa(&style_screen_main_list_musics_extra_texts_main_default, 0);
	lv_obj_add_style(ui->screen_main_list_musics_item0, &style_screen_main_list_musics_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_cont_app
	ui->screen_main_cont_app = lv_obj_create(ui->screen_main);
	lv_obj_set_pos(ui->screen_main_cont_app, 0, 205);
	lv_obj_set_size(ui->screen_main_cont_app, 320, 35);
	lv_obj_set_scrollbar_mode(ui->screen_main_cont_app, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_main_cont_app, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_main_cont_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_cont_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_main_cont_app, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_cont_app, lv_color_hex(0x7ab957), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_cont_app, LV_GRAD_DIR_HOR, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_main_cont_app, lv_color_hex(0x8c8a85), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_main_cont_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_main_cont_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_main_cont_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_main_cont_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_cont_app, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_btn_select
	ui->screen_main_btn_select = lv_btn_create(ui->screen_main_cont_app);
	ui->screen_main_btn_select_label = lv_label_create(ui->screen_main_btn_select);
	lv_label_set_text(ui->screen_main_btn_select_label, "");
	lv_label_set_long_mode(ui->screen_main_btn_select_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_main_btn_select_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_main_btn_select, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_main_btn_select, 3, 1);
	lv_obj_set_size(ui->screen_main_btn_select, 35, 32);

	//Write style for screen_main_btn_select, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_btn_select, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_btn_select, lv_color_hex(0x66c5ac), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_main_btn_select, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_btn_select, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_btn_select, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_main_btn_select, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_main_btn_select, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_main_btn_select, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_main
	ui->screen_main_img_main = lv_img_create(ui->screen_main_cont_app);
	lv_obj_add_flag(ui->screen_main_img_main, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_main, &_love_alpha_30x30);
	lv_img_set_pivot(ui->screen_main_img_main, 50,50);
	lv_img_set_angle(ui->screen_main_img_main, 0);
	lv_obj_set_pos(ui->screen_main_img_main, 5, 2);
	lv_obj_set_size(ui->screen_main_img_main, 30, 30);

	//Write style for screen_main_img_main, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_main_img_main, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_img_read
	ui->screen_main_img_img_read = lv_img_create(ui->screen_main_cont_app);
	lv_obj_add_flag(ui->screen_main_img_img_read, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_img_read, &_picture_alpha_30x30);
	lv_img_set_pivot(ui->screen_main_img_img_read, 50,50);
	lv_img_set_angle(ui->screen_main_img_img_read, 0);
	lv_obj_set_pos(ui->screen_main_img_img_read, 55, 2);
	lv_obj_set_size(ui->screen_main_img_img_read, 30, 30);

	//Write style for screen_main_img_img_read, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_main_img_img_read, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_reader
	ui->screen_main_img_reader = lv_img_create(ui->screen_main_cont_app);
	lv_obj_add_flag(ui->screen_main_img_reader, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_reader, &_reader_alpha_30x30);
	lv_img_set_pivot(ui->screen_main_img_reader, 50,50);
	lv_img_set_angle(ui->screen_main_img_reader, 0);
	lv_obj_set_pos(ui->screen_main_img_reader, 105, 2);
	lv_obj_set_size(ui->screen_main_img_reader, 30, 30);

	//Write style for screen_main_img_reader, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_main_img_reader, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_setting
	ui->screen_main_img_setting = lv_img_create(ui->screen_main_cont_app);
	lv_obj_add_flag(ui->screen_main_img_setting, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_setting, &_setting1_alpha_30x30);
	lv_img_set_pivot(ui->screen_main_img_setting, 50,50);
	lv_img_set_angle(ui->screen_main_img_setting, 0);
	lv_obj_set_pos(ui->screen_main_img_setting, 155, 2);
	lv_obj_set_size(ui->screen_main_img_setting, 30, 30);
	lv_obj_add_flag(ui->screen_main_img_setting, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_main_img_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_main_img_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_img_light
	ui->screen_main_img_light = lv_img_create(ui->screen_main_cont_app);
	lv_obj_add_flag(ui->screen_main_img_light, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_main_img_light, &_nichijoubg_alpha_30x30);
	lv_img_set_pivot(ui->screen_main_img_light, 50,50);
	lv_img_set_angle(ui->screen_main_img_light, 0);
	lv_obj_set_pos(ui->screen_main_img_light, 205, 3);
	lv_obj_set_size(ui->screen_main_img_light, 30, 30);
	lv_obj_add_flag(ui->screen_main_img_light, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_main_img_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_main_img_light, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_main_slider_light
	ui->screen_main_slider_light = lv_slider_create(ui->screen_main);
	lv_slider_set_range(ui->screen_main_slider_light, 0, 100);
	lv_slider_set_mode(ui->screen_main_slider_light, LV_SLIDER_MODE_NORMAL);
	lv_slider_set_value(ui->screen_main_slider_light, 50, LV_ANIM_OFF);
	lv_obj_set_pos(ui->screen_main_slider_light, 43, 104);
	lv_obj_set_size(ui->screen_main_slider_light, 234, 46);
	lv_obj_add_flag(ui->screen_main_slider_light, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_main_slider_light, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_slider_light, 60, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_slider_light, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_slider_light, 50, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_width(ui->screen_main_slider_light, 3, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_opa(ui->screen_main_slider_light, 216, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_outline_color(ui->screen_main_slider_light, lv_color_hex(0xcecece), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_main_slider_light, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_main_slider_light, Part: LV_PART_INDICATOR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_slider_light, 255, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_main_slider_light, lv_color_hex(0xb8b84b), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_dir(ui->screen_main_slider_light, LV_GRAD_DIR_HOR, LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_grad_color(ui->screen_main_slider_light, lv_color_hex(0x2195f6), LV_PART_INDICATOR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_slider_light, 50, LV_PART_INDICATOR|LV_STATE_DEFAULT);

	//Write style for screen_main_slider_light, Part: LV_PART_KNOB, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_main_slider_light, 0, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->screen_main_slider_light, &_nichijoubg_52x52, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->screen_main_slider_light, 255, LV_PART_KNOB|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_main_slider_light, 50, LV_PART_KNOB|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_main);

	
	//Init events for screen.
	events_init_screen_main(ui);
}
