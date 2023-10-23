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


void setup_scr_screen_setting(lv_ui *ui)
{
	//Write codes screen_setting
	ui->screen_setting = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_setting, 320, 240);

	//Write style for screen_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_setting, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_setting, lv_color_hex(0x589bcc), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_tileview_setting
	ui->screen_setting_tileview_setting = lv_tileview_create(ui->screen_setting);
	ui->screen_setting_tileview_setting_tile_main = lv_tileview_add_tile(ui->screen_setting_tileview_setting, 0, 0, LV_DIR_BOTTOM);
	ui->screen_setting_tileview_setting_tile_wifi = lv_tileview_add_tile(ui->screen_setting_tileview_setting, 0, 1, LV_DIR_TOP | LV_DIR_BOTTOM);
	ui->screen_setting_tileview_setting_tile_ble = lv_tileview_add_tile(ui->screen_setting_tileview_setting, 0, 2, LV_DIR_TOP | LV_DIR_BOTTOM);
	ui->screen_setting_tileview_setting_tile_uart = lv_tileview_add_tile(ui->screen_setting_tileview_setting, 0, 3, LV_DIR_TOP);
	lv_obj_set_pos(ui->screen_setting_tileview_setting, 10, 20);
	lv_obj_set_size(ui->screen_setting_tileview_setting, 300, 200);
	lv_obj_set_scrollbar_mode(ui->screen_setting_tileview_setting, LV_SCROLLBAR_MODE_AUTO);

	//Write style for screen_setting_tileview_setting, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_setting_tileview_setting, 98, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_setting_tileview_setting, lv_color_hex(0xa7a4a4), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_setting_tileview_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_setting_tileview_setting, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style for screen_setting_tileview_setting, Part: LV_PART_SCROLLBAR, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_setting_tileview_setting, 188, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_setting_tileview_setting, lv_color_hex(0x5b8438), LV_PART_SCROLLBAR|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_setting_tileview_setting, 0, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);



	//Write codes screen_setting_list_1
	ui->screen_setting_list_1 = lv_list_create(ui->screen_setting_tileview_setting_tile_main);
	ui->screen_setting_list_1_item0 = lv_list_add_btn(ui->screen_setting_list_1, &_wifi1_alpha_20x20, "WIFI");
	ui->screen_setting_list_1_item1 = lv_list_add_btn(ui->screen_setting_list_1, &_bluetooth30_30_alpha_20x20, "BLE");
	lv_obj_set_pos(ui->screen_setting_list_1, 27, 16);
	lv_obj_set_size(ui->screen_setting_list_1, 250, 170);
	lv_obj_set_scrollbar_mode(ui->screen_setting_list_1, LV_SCROLLBAR_MODE_OFF);

	//Write style state: LV_STATE_DEFAULT for &style_screen_setting_list_1_main_main_default
	static lv_style_t style_screen_setting_list_1_main_main_default;
	ui_init_style(&style_screen_setting_list_1_main_main_default);
	
	lv_style_set_pad_top(&style_screen_setting_list_1_main_main_default, 5);
	lv_style_set_pad_left(&style_screen_setting_list_1_main_main_default, 5);
	lv_style_set_pad_right(&style_screen_setting_list_1_main_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_setting_list_1_main_main_default, 5);
	lv_style_set_bg_opa(&style_screen_setting_list_1_main_main_default, 0);
	lv_style_set_border_width(&style_screen_setting_list_1_main_main_default, 1);
	lv_style_set_border_opa(&style_screen_setting_list_1_main_main_default, 255);
	lv_style_set_border_color(&style_screen_setting_list_1_main_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_setting_list_1_main_main_default, LV_BORDER_SIDE_NONE);
	lv_style_set_radius(&style_screen_setting_list_1_main_main_default, 3);
	lv_style_set_shadow_width(&style_screen_setting_list_1_main_main_default, 0);
	lv_obj_add_style(ui->screen_setting_list_1, &style_screen_setting_list_1_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_setting_list_1_main_scrollbar_default
	static lv_style_t style_screen_setting_list_1_main_scrollbar_default;
	ui_init_style(&style_screen_setting_list_1_main_scrollbar_default);
	
	lv_style_set_radius(&style_screen_setting_list_1_main_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_setting_list_1_main_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_setting_list_1_main_scrollbar_default, lv_color_hex(0xffffff));
	lv_obj_add_style(ui->screen_setting_list_1, &style_screen_setting_list_1_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_setting_list_1_extra_btns_main_default
	static lv_style_t style_screen_setting_list_1_extra_btns_main_default;
	ui_init_style(&style_screen_setting_list_1_extra_btns_main_default);
	
	lv_style_set_pad_top(&style_screen_setting_list_1_extra_btns_main_default, 5);
	lv_style_set_pad_left(&style_screen_setting_list_1_extra_btns_main_default, 5);
	lv_style_set_pad_right(&style_screen_setting_list_1_extra_btns_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_setting_list_1_extra_btns_main_default, 5);
	lv_style_set_border_width(&style_screen_setting_list_1_extra_btns_main_default, 0);
	lv_style_set_text_color(&style_screen_setting_list_1_extra_btns_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_setting_list_1_extra_btns_main_default, &lv_font_Abel_regular_12);
	lv_style_set_radius(&style_screen_setting_list_1_extra_btns_main_default, 3);
	lv_style_set_bg_opa(&style_screen_setting_list_1_extra_btns_main_default, 44);
	lv_style_set_bg_color(&style_screen_setting_list_1_extra_btns_main_default, lv_color_hex(0xd04545));
	lv_obj_add_style(ui->screen_setting_list_1_item1, &style_screen_setting_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_add_style(ui->screen_setting_list_1_item0, &style_screen_setting_list_1_extra_btns_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_PRESSED for &style_screen_setting_list_1_extra_btns_main_pressed
	static lv_style_t style_screen_setting_list_1_extra_btns_main_pressed;
	ui_init_style(&style_screen_setting_list_1_extra_btns_main_pressed);
	
	lv_style_set_pad_top(&style_screen_setting_list_1_extra_btns_main_pressed, 5);
	lv_style_set_pad_left(&style_screen_setting_list_1_extra_btns_main_pressed, 5);
	lv_style_set_pad_right(&style_screen_setting_list_1_extra_btns_main_pressed, 5);
	lv_style_set_pad_bottom(&style_screen_setting_list_1_extra_btns_main_pressed, 5);
	lv_style_set_border_width(&style_screen_setting_list_1_extra_btns_main_pressed, 0);
	lv_style_set_radius(&style_screen_setting_list_1_extra_btns_main_pressed, 3);
	lv_style_set_text_color(&style_screen_setting_list_1_extra_btns_main_pressed, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_setting_list_1_extra_btns_main_pressed, &lv_font_Abel_regular_12);
	lv_style_set_bg_opa(&style_screen_setting_list_1_extra_btns_main_pressed, 88);
	lv_style_set_bg_color(&style_screen_setting_list_1_extra_btns_main_pressed, lv_color_hex(0x29ff00));
	lv_obj_add_style(ui->screen_setting_list_1_item1, &style_screen_setting_list_1_extra_btns_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);
	lv_obj_add_style(ui->screen_setting_list_1_item0, &style_screen_setting_list_1_extra_btns_main_pressed, LV_PART_MAIN|LV_STATE_PRESSED);

	//Write style state: LV_STATE_FOCUSED for &style_screen_setting_list_1_extra_btns_main_focused
	static lv_style_t style_screen_setting_list_1_extra_btns_main_focused;
	ui_init_style(&style_screen_setting_list_1_extra_btns_main_focused);
	
	lv_style_set_pad_top(&style_screen_setting_list_1_extra_btns_main_focused, 5);
	lv_style_set_pad_left(&style_screen_setting_list_1_extra_btns_main_focused, 5);
	lv_style_set_pad_right(&style_screen_setting_list_1_extra_btns_main_focused, 5);
	lv_style_set_pad_bottom(&style_screen_setting_list_1_extra_btns_main_focused, 5);
	lv_style_set_border_width(&style_screen_setting_list_1_extra_btns_main_focused, 0);
	lv_style_set_radius(&style_screen_setting_list_1_extra_btns_main_focused, 3);
	lv_style_set_text_color(&style_screen_setting_list_1_extra_btns_main_focused, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_setting_list_1_extra_btns_main_focused, &lv_font_Abel_regular_12);
	lv_style_set_bg_opa(&style_screen_setting_list_1_extra_btns_main_focused, 255);
	lv_style_set_bg_color(&style_screen_setting_list_1_extra_btns_main_focused, lv_color_hex(0x55acaa));
	lv_obj_add_style(ui->screen_setting_list_1_item1, &style_screen_setting_list_1_extra_btns_main_focused, LV_PART_MAIN|LV_STATE_FOCUSED);
	lv_obj_add_style(ui->screen_setting_list_1_item0, &style_screen_setting_list_1_extra_btns_main_focused, LV_PART_MAIN|LV_STATE_FOCUSED);

	//Write style state: LV_STATE_DEFAULT for &style_screen_setting_list_1_extra_texts_main_default
	static lv_style_t style_screen_setting_list_1_extra_texts_main_default;
	ui_init_style(&style_screen_setting_list_1_extra_texts_main_default);
	
	lv_style_set_pad_top(&style_screen_setting_list_1_extra_texts_main_default, 5);
	lv_style_set_pad_left(&style_screen_setting_list_1_extra_texts_main_default, 5);
	lv_style_set_pad_right(&style_screen_setting_list_1_extra_texts_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_setting_list_1_extra_texts_main_default, 5);
	lv_style_set_border_width(&style_screen_setting_list_1_extra_texts_main_default, 0);
	lv_style_set_text_color(&style_screen_setting_list_1_extra_texts_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_setting_list_1_extra_texts_main_default, &lv_font_Abel_regular_12);
	lv_style_set_radius(&style_screen_setting_list_1_extra_texts_main_default, 3);
	lv_style_set_bg_opa(&style_screen_setting_list_1_extra_texts_main_default, 161);
	lv_style_set_bg_color(&style_screen_setting_list_1_extra_texts_main_default, lv_color_hex(0xffffff));







	//Write codes screen_setting_img_menu2
	ui->screen_setting_img_menu2 = lv_img_create(ui->screen_setting);
	lv_obj_add_flag(ui->screen_setting_img_menu2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_setting_img_menu2, &_menu_alpha_20x20);
	lv_img_set_pivot(ui->screen_setting_img_menu2, 0,0);
	lv_img_set_angle(ui->screen_setting_img_menu2, 0);
	lv_obj_set_pos(ui->screen_setting_img_menu2, 300, 135);
	lv_obj_set_size(ui->screen_setting_img_menu2, 20, 20);
	lv_obj_add_flag(ui->screen_setting_img_menu2, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_setting_img_menu2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_setting_img_menu2, 93, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_setting_img_home2
	ui->screen_setting_img_home2 = lv_img_create(ui->screen_setting);
	lv_obj_add_flag(ui->screen_setting_img_home2, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_setting_img_home2, &_home_alpha_20x20);
	lv_img_set_pivot(ui->screen_setting_img_home2, 0,0);
	lv_img_set_angle(ui->screen_setting_img_home2, 0);
	lv_obj_set_pos(ui->screen_setting_img_home2, 300, 220);
	lv_obj_set_size(ui->screen_setting_img_home2, 20, 20);
	lv_obj_add_flag(ui->screen_setting_img_home2, LV_OBJ_FLAG_CLICKABLE);

	//Write style for screen_setting_img_home2, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_setting_img_home2, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_setting);

	
	//Init events for screen.
	events_init_screen_setting(ui);
}
