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

	//Write codes screen_btnm_1
	ui->screen_btnm_1 = lv_btnmatrix_create(ui->screen);
	static const char *screen_btnm_1_text_map[] = {"1", "2", "3", "\n", "4", "5", "6", "\n", "7", "8", "9", "",};
	lv_btnmatrix_set_map(ui->screen_btnm_1, screen_btnm_1_text_map);
	lv_obj_set_pos(ui->screen_btnm_1, 6, 65);
	lv_obj_set_size(ui->screen_btnm_1, 200, 150);
	lv_obj_add_flag(ui->screen_btnm_1, LV_OBJ_FLAG_HIDDEN);

	//Write style for screen_btnm_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_btnm_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_btnm_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_btnm_1, lv_color_hex(0xc9c9c9), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_btnm_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_btnm_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_btnm_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_btnm_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_btnm_1, 16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_row(ui->screen_btnm_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_column(ui->screen_btnm_1, 8, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btnm_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_btnm_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btnm_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_btnm_1, Part: LV_PART_ITEMS, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_btnm_1, 1, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_btnm_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_btnm_1, lv_color_hex(0xc9c9c9), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_btnm_1, LV_BORDER_SIDE_FULL, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btnm_1, lv_color_hex(0xffffff), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btnm_1, &lv_font_simsun_16, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btnm_1, 4, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_btnm_1, 255, LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btnm_1, lv_color_hex(0x2195f6), LV_PART_ITEMS|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btnm_1, 0, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes screen_spangroup_1
	ui->screen_spangroup_1 = lv_spangroup_create(ui->screen);
	lv_spangroup_set_align(ui->screen_spangroup_1, LV_TEXT_ALIGN_LEFT);
	lv_spangroup_set_overflow(ui->screen_spangroup_1, LV_SPAN_OVERFLOW_CLIP);
	lv_spangroup_set_mode(ui->screen_spangroup_1, LV_SPAN_MODE_BREAK);
	//create spans
	lv_span_t *screen_spangroup_1_span;
	screen_spangroup_1_span = lv_spangroup_new_span(ui->screen_spangroup_1);
	lv_span_set_text(screen_spangroup_1_span, "hello");
	lv_style_set_text_color(&screen_spangroup_1_span->style, lv_color_hex(0x000000));
	lv_style_set_text_decor(&screen_spangroup_1_span->style, LV_TEXT_DECOR_NONE);
	lv_style_set_text_font(&screen_spangroup_1_span->style, &lv_font_montserratMedium_12);
	lv_obj_set_pos(ui->screen_spangroup_1, 74, 30);
	lv_obj_set_size(ui->screen_spangroup_1, 200, 100);
	lv_obj_add_flag(ui->screen_spangroup_1, LV_OBJ_FLAG_HIDDEN);

	//Write style state: LV_STATE_DEFAULT for &style_screen_spangroup_1_main_main_default
	static lv_style_t style_screen_spangroup_1_main_main_default;
	ui_init_style(&style_screen_spangroup_1_main_main_default);
	
	lv_style_set_border_width(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_radius(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_bg_opa(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_top(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_right(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_pad_left(&style_screen_spangroup_1_main_main_default, 0);
	lv_style_set_shadow_width(&style_screen_spangroup_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_spangroup_1, &style_screen_spangroup_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_spangroup_refr_mode(ui->screen_spangroup_1);

	//Write codes screen_tileview_1
	ui->screen_tileview_1 = lv_tileview_create(ui->screen);
	ui->screen_tileview_1_hello = lv_tileview_add_tile(ui->screen_tileview_1, 0, 0, LV_DIR_BOTTOM);
	ui->screen_tileview_1_tile_2 = lv_tileview_add_tile(ui->screen_tileview_1, 0, 1, LV_DIR_TOP | LV_DIR_BOTTOM);
	ui->screen_tileview_1_tile_3 = lv_tileview_add_tile(ui->screen_tileview_1, 0, 2, LV_DIR_TOP);
	lv_obj_set_pos(ui->screen_tileview_1, 25, 20);
	lv_obj_set_size(ui->screen_tileview_1, 300, 200);
	lv_obj_set_scrollbar_mode(ui->screen_tileview_1, LV_SCROLLBAR_MODE_AUTO);

	//Write style for screen_tileview_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_tileview_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_tileview_1, lv_color_hex(0xad1c1c), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_tileview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_tileview_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_tileview_1, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_tileview_1, 255, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_tileview_1, lv_color_hex(0xeaeff3), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_tileview_1, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



	//Write codes screen_btn_1
	ui->screen_btn_1 = lv_btn_create(ui->screen_tileview_1_hello);
	ui->screen_btn_1_label = lv_label_create(ui->screen_btn_1);
	lv_label_set_text(ui->screen_btn_1_label, "Button");
	lv_label_set_long_mode(ui->screen_btn_1_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_1_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_1, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_btn_1, 5, 19);
	lv_obj_set_size(ui->screen_btn_1, 41, 48);
	lv_obj_add_flag(ui->screen_btn_1, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_btn_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_1, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_1, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_1, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_1, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_msgbox_1
	static const char * screen_msgbox_1_btns[] = {"Apply","Close","title",""};
	ui->screen_msgbox_1 = lv_msgbox_create(ui->screen_tileview_1_hello, "a", "content", screen_msgbox_1_btns, true);
	lv_obj_set_size(lv_msgbox_get_btns(ui->screen_msgbox_1), 180, 30);
	lv_obj_set_pos(ui->screen_msgbox_1, 56, 19);
	lv_obj_set_size(ui->screen_msgbox_1, 243, 135);

	//Write style for screen_msgbox_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_msgbox_1, 251, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_msgbox_1, lv_color_hex(0xdbffbd), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_msgbox_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_opa(ui->screen_msgbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_color(ui->screen_msgbox_1, lv_color_hex(0x575757), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_side(ui->screen_msgbox_1, LV_BORDER_SIDE_FULL, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_msgbox_1, 18, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_msgbox_1, 4, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_color(ui->screen_msgbox_1, lv_color_hex(0x4d4d4d), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_opa(ui->screen_msgbox_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_spread(ui->screen_msgbox_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_x(ui->screen_msgbox_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_ofs_y(ui->screen_msgbox_1, 1, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_1_extra_title_main_default
	static lv_style_t style_screen_msgbox_1_extra_title_main_default;
	ui_init_style(&style_screen_msgbox_1_extra_title_main_default);
	
	lv_style_set_text_color(&style_screen_msgbox_1_extra_title_main_default, lv_color_hex(0x31312d));
	lv_style_set_text_font(&style_screen_msgbox_1_extra_title_main_default, &lv_font_montserratMedium_19);
	lv_style_set_text_letter_space(&style_screen_msgbox_1_extra_title_main_default, 0);
	lv_style_set_text_line_space(&style_screen_msgbox_1_extra_title_main_default, 30);
	lv_obj_add_style(lv_msgbox_get_title(ui->screen_msgbox_1), &style_screen_msgbox_1_extra_title_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_1_extra_content_main_default
	static lv_style_t style_screen_msgbox_1_extra_content_main_default;
	ui_init_style(&style_screen_msgbox_1_extra_content_main_default);
	
	lv_style_set_text_color(&style_screen_msgbox_1_extra_content_main_default, lv_color_hex(0x383732));
	lv_style_set_text_font(&style_screen_msgbox_1_extra_content_main_default, &lv_font_montserratMedium_14);
	lv_style_set_text_letter_space(&style_screen_msgbox_1_extra_content_main_default, 0);
	lv_style_set_text_line_space(&style_screen_msgbox_1_extra_content_main_default, 10);
	lv_obj_add_style(lv_msgbox_get_text(ui->screen_msgbox_1), &style_screen_msgbox_1_extra_content_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_msgbox_1_extra_btns_items_default
	static lv_style_t style_screen_msgbox_1_extra_btns_items_default;
	ui_init_style(&style_screen_msgbox_1_extra_btns_items_default);
	
	lv_style_set_bg_opa(&style_screen_msgbox_1_extra_btns_items_default, 0);
	lv_style_set_border_width(&style_screen_msgbox_1_extra_btns_items_default, 2);
	lv_style_set_border_opa(&style_screen_msgbox_1_extra_btns_items_default, 255);
	lv_style_set_border_color(&style_screen_msgbox_1_extra_btns_items_default, lv_color_hex(0x299d9c));
	lv_style_set_border_side(&style_screen_msgbox_1_extra_btns_items_default, LV_BORDER_SIDE_FULL);
	lv_style_set_radius(&style_screen_msgbox_1_extra_btns_items_default, 4);
	lv_style_set_text_color(&style_screen_msgbox_1_extra_btns_items_default, lv_color_hex(0x01798e));
	lv_style_set_text_font(&style_screen_msgbox_1_extra_btns_items_default, &lv_font_Alatsi_Regular_13);
	lv_obj_add_style(lv_msgbox_get_btns(ui->screen_msgbox_1), &style_screen_msgbox_1_extra_btns_items_default, LV_PART_ITEMS|LV_STATE_DEFAULT);

	//Write codes screen_btn_3
	ui->screen_btn_3 = lv_btn_create(ui->screen_tileview_1_hello);
	ui->screen_btn_3_label = lv_label_create(ui->screen_btn_3);
	lv_label_set_text(ui->screen_btn_3_label, "Button");
	lv_label_set_long_mode(ui->screen_btn_3_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_3_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_3, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_btn_3, 4, 89);
	lv_obj_set_size(ui->screen_btn_3, 41, 48);
	lv_obj_add_flag(ui->screen_btn_3, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_btn_3, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_3, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_3, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_3, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_3, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_3, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_3, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_3, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_img_1
	ui->screen_img_1 = lv_img_create(ui->screen_tileview_1_hello);
	lv_obj_add_flag(ui->screen_img_1, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_img_1, &_nichijou_alpha_80x52);
	lv_img_set_pivot(ui->screen_img_1, 50,50);
	lv_img_set_angle(ui->screen_img_1, 0);
	lv_obj_set_pos(ui->screen_img_1, 146, 42);
	lv_obj_set_size(ui->screen_img_1, 80, 52);

	//Write style for screen_img_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_1, 255, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_btn_2
	ui->screen_btn_2 = lv_btn_create(ui->screen_tileview_1_tile_2);
	ui->screen_btn_2_label = lv_label_create(ui->screen_btn_2);
	lv_label_set_text(ui->screen_btn_2_label, "Button");
	lv_label_set_long_mode(ui->screen_btn_2_label, LV_LABEL_LONG_WRAP);
	lv_obj_align(ui->screen_btn_2_label, LV_ALIGN_CENTER, 0, 0);
	lv_obj_set_style_pad_all(ui->screen_btn_2, 0, LV_STATE_DEFAULT);
	lv_obj_set_pos(ui->screen_btn_2, 110, 95);
	lv_obj_set_size(ui->screen_btn_2, 100, 50);

	//Write style for screen_btn_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_btn_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_btn_2, lv_color_hex(0x2195f6), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_border_width(ui->screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_btn_2, 5, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_btn_2, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_btn_2, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_btn_2, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_btn_2, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_label_1
	ui->screen_label_1 = lv_label_create(ui->screen_tileview_1_tile_2);
	lv_label_set_text(ui->screen_label_1, "Labelaaa");
	lv_label_set_long_mode(ui->screen_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_label_1, 111, 51);
	lv_obj_set_size(ui->screen_label_1, 100, 32);

	//Write style for screen_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_label_1, &lv_font_simsun_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);



	//Write codes screen_img_2
	ui->screen_img_2 = lv_img_create(ui->screen);
	lv_obj_add_flag(ui->screen_img_2, LV_OBJ_FLAG_CLICKABLE);
#if LV_USE_GUIDER_SIMULATOR
	lv_img_set_src(ui->screen_img_2, "C:\\NXP\\GUI-Guider-Projects\\guider_nplayer\\import\\image\\bg.png");
#else
	lv_img_set_src(ui->screen_img_2,"S:/bg.bin");
#endif
//	lv_img_set_pivot(ui->screen_img_2, 50,50);
//	lv_img_set_angle(ui->screen_img_2, 0);
//	lv_obj_set_pos(ui->screen_img_2, 0, 8);
//	lv_obj_set_size(ui->screen_img_2, 320, 120);

	//Write style for screen_img_2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_img_2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen);

	
	//Init events for screen.
	events_init_screen(ui);
}
