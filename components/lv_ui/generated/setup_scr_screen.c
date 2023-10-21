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


void setup_scr_screen(lv_ui *ui)
{
	//Write codes screen
	ui->screen = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen, 320, 240);

	//Write style for screen, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_src(ui->screen, &_nichijoubg_320x240, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_opa(ui->screen, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_cont_timer
	ui->screen_cont_timer = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_cont_timer, 5, 5);
	lv_obj_set_size(ui->screen_cont_timer, 190, 200);
	lv_obj_set_scrollbar_mode(ui->screen_cont_timer, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_cont_timer, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_cont_timer, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_cont_timer, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_cont_timer, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_cont_timer, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_cont_timer, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_cont_timer, 116, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_cont_timer, lv_color_hex(0xcefffc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_cont_timer, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_cont_days
	ui->screen_cont_days = lv_obj_create(ui->screen_cont_timer);
	lv_obj_set_pos(ui->screen_cont_days, 5, 50);
	lv_obj_set_size(ui->screen_cont_days, 200, 60);
	lv_obj_set_scrollbar_mode(ui->screen_cont_days, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_cont_days, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_cont_days, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_cont_days, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_cont_days, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_cont_days, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_cont_days, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_cont_days, 247, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_cont_days, lv_color_hex(0x74a7cd), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_cont_days, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_text_day
	ui->screen_text_day = lv_spangroup_create(ui->screen_cont_days);
	lv_spangroup_set_align(ui->screen_text_day, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_text_day, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_text_day, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_text_day_span;
	screen_text_day_span = lv_spangroup_new_span(ui->screen_text_day);
	lv_span_set_text(screen_text_day_span, "2023年\n");
	lv_style_set_text_color(&screen_text_day_span->style, lv_color_hex(0xaa379d));
	lv_style_set_text_decor(&screen_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_day_span->style, &lv_font_simsun_28);
	screen_text_day_span = lv_spangroup_new_span(ui->screen_text_day);
	lv_span_set_text(screen_text_day_span, "  ");
	lv_style_set_text_color(&screen_text_day_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_day_span->style, &lv_font_Abel_regular_28);
	screen_text_day_span = lv_spangroup_new_span(ui->screen_text_day);
	lv_span_set_text(screen_text_day_span, "星期一");
	lv_style_set_text_color(&screen_text_day_span->style, lv_color_hex(0x15604c));
	lv_style_set_text_decor(&screen_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_day_span->style, &lv_font_simsun_28);
	screen_text_day_span = lv_spangroup_new_span(ui->screen_text_day);
	lv_span_set_text(screen_text_day_span, "10月21日");
	lv_style_set_text_color(&screen_text_day_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_day_span->style, &lv_font_simsun_28);
	screen_text_day_span = lv_spangroup_new_span(ui->screen_text_day);
	lv_span_set_text(screen_text_day_span, "HELLO WORLD");
	lv_style_set_text_color(&screen_text_day_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&screen_text_day_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_day_span->style, &lv_font_Abel_regular_12);
	lv_obj_set_pos(ui->screen_text_day, 0, 0);
	lv_obj_set_size(ui->screen_text_day, 199, 59);

	//Write style state: LV_STATE_DEFAULT for &style_screen_text_day_main_main_default
	static lv_style_t style_screen_text_day_main_main_default;
	ui_init_style(&style_screen_text_day_main_main_default);
	
	lv_style_set_border_width(&style_screen_text_day_main_main_default, 0);
	lv_style_set_radius(&style_screen_text_day_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_text_day_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_text_day_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_text_day_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_text_day_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_text_day_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_text_day_main_main_default, 0);
	lv_obj_add_style(ui->screen_text_day, &style_screen_text_day_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_text_day);

	//Write codes screen_cont_time
	ui->screen_cont_time = lv_obj_create(ui->screen_cont_timer);
	lv_obj_set_pos(ui->screen_cont_time, -20, 3);
	lv_obj_set_size(ui->screen_cont_time, 200, 40);
	lv_obj_set_scrollbar_mode(ui->screen_cont_time, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_cont_time, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_cont_time, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_cont_time, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_cont_time, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_cont_time, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_cont_time, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_cont_time, 222, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_cont_time, lv_color_hex(0xdeb923), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_cont_time, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_text_time
	ui->screen_text_time = lv_spangroup_create(ui->screen_cont_time);
	lv_spangroup_set_align(ui->screen_text_time, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_text_time, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_text_time, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_text_time_span;
	screen_text_time_span = lv_spangroup_new_span(ui->screen_text_time);
	lv_span_set_text(screen_text_time_span, "00");
	lv_style_set_text_color(&screen_text_time_span->style, lv_color_hex(0xaa379d));
	lv_style_set_text_decor(&screen_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_time_span->style, &lv_font_Abel_regular_40);
	screen_text_time_span = lv_spangroup_new_span(ui->screen_text_time);
	lv_span_set_text(screen_text_time_span, ":");
	lv_style_set_text_color(&screen_text_time_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_time_span->style, &lv_font_Abel_regular_40);
	screen_text_time_span = lv_spangroup_new_span(ui->screen_text_time);
	lv_span_set_text(screen_text_time_span, "00");
	lv_style_set_text_color(&screen_text_time_span->style, lv_color_hex(0x26B08C));
	lv_style_set_text_decor(&screen_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_time_span->style, &lv_font_Abel_regular_40);
	screen_text_time_span = lv_spangroup_new_span(ui->screen_text_time);
	lv_span_set_text(screen_text_time_span, ":");
	lv_style_set_text_color(&screen_text_time_span->style, lv_color_hex(0x2F35DA));
	lv_style_set_text_decor(&screen_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_time_span->style, &lv_font_Abel_regular_28);
	screen_text_time_span = lv_spangroup_new_span(ui->screen_text_time);
	lv_span_set_text(screen_text_time_span, "00");
	lv_style_set_text_color(&screen_text_time_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&screen_text_time_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_time_span->style, &lv_font_Abel_regular_28);
	lv_obj_set_pos(ui->screen_text_time, 30, 0);
	lv_obj_set_size(ui->screen_text_time, 200, 40);

	//Write style state: LV_STATE_DEFAULT for &style_screen_text_time_main_main_default
	static lv_style_t style_screen_text_time_main_main_default;
	ui_init_style(&style_screen_text_time_main_main_default);
	
	lv_style_set_border_width(&style_screen_text_time_main_main_default, 0);
	lv_style_set_radius(&style_screen_text_time_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_text_time_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_text_time_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_text_time_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_text_time_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_text_time_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_text_time_main_main_default, 0);
	lv_obj_add_style(ui->screen_text_time, &style_screen_text_time_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_text_time);

	//Write codes screen_cont_nichijou
	ui->screen_cont_nichijou = lv_obj_create(ui->screen_cont_timer);
	lv_obj_set_pos(ui->screen_cont_nichijou, 3, 120);
	lv_obj_set_size(ui->screen_cont_nichijou, 180, 30);
	lv_obj_set_scrollbar_mode(ui->screen_cont_nichijou, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_cont_nichijou, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_cont_nichijou, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_cont_nichijou, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_cont_nichijou, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_cont_nichijou, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_cont_nichijou, 10, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_cont_nichijou, 197, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_cont_nichijou, lv_color_hex(0x8ce45d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_cont_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_cont_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_cont_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_cont_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_cont_nichijou, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_text_nichijou
	ui->screen_text_nichijou = lv_spangroup_create(ui->screen_cont_nichijou);
	lv_spangroup_set_align(ui->screen_text_nichijou, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_text_nichijou, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_text_nichijou, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_text_nichijou_span;
	screen_text_nichijou_span = lv_spangroup_new_span(ui->screen_text_nichijou);
	lv_span_set_text(screen_text_nichijou_span, "日常NICHIJOU");
	lv_style_set_text_color(&screen_text_nichijou_span->style, lv_color_hex(0x812a77));
	lv_style_set_text_decor(&screen_text_nichijou_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_text_nichijou_span->style, &lv_font_simsun_28);
	lv_obj_set_pos(ui->screen_text_nichijou, 4, 0);
	lv_obj_set_size(ui->screen_text_nichijou, 172, 28);

	//Write style state: LV_STATE_DEFAULT for &style_screen_text_nichijou_main_main_default
	static lv_style_t style_screen_text_nichijou_main_main_default;
	ui_init_style(&style_screen_text_nichijou_main_main_default);
	
	lv_style_set_border_width(&style_screen_text_nichijou_main_main_default, 0);
	lv_style_set_radius(&style_screen_text_nichijou_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_text_nichijou_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_text_nichijou_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_text_nichijou_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_text_nichijou_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_text_nichijou_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_text_nichijou_main_main_default, 0);
	lv_obj_add_style(ui->screen_text_nichijou, &style_screen_text_nichijou_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_text_nichijou);

	//Write codes screen_cont_weather
	ui->screen_cont_weather = lv_obj_create(ui->screen);
	lv_obj_set_pos(ui->screen_cont_weather, 200, 5);
	lv_obj_set_size(ui->screen_cont_weather, 110, 200);
	lv_obj_set_scrollbar_mode(ui->screen_cont_weather, LV_SCROLLBAR_MODE_OFF);

	//Write style for screen_cont_weather, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_cont_weather, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_cont_weather, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_cont_weather, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_cont_weather, LV_BORDER_SIDE_NONE, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_cont_weather, 20, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_cont_weather, 116, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_cont_weather, lv_color_hex(0xcefffc), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_cont_weather, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label_1
	ui->screen_label_1 = lv_label_create(ui->screen);
	lv_label_set_text(ui->screen_label_1, "我们所经历的每一个日常，也许都是不断发生的奇迹！");
	lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_SCROLL_CIRCULAR);
	lv_obj_set_pos(ui->screen_label_1, 5, 208);
	lv_obj_set_size(ui->screen_label_1, 310, 29);

	//Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_label_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_label_1, lv_color_hex(0x6bb8c0), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_label_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_label_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_simsun_12, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_1, 185, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_label_1, lv_color_hex(0x92bfed), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen);

	
	//Init events for screen.
	events_init_screen(ui);
}
