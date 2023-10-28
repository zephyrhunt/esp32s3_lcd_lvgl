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


void setup_scr_screen_image(lv_ui *ui)
{
	//Write codes screen_image
	ui->screen_image = lv_obj_create(NULL);
	lv_obj_set_size(ui->screen_image, 320, 240);

	//Write style for screen_image, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_bg_opa(ui->screen_image, 255, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_image, lv_color_hex(0xffffff), LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_image_list_image
	ui->screen_image_list_image = lv_list_create(ui->screen_image);
	ui->screen_image_list_image_item0 =lv_list_add_text(ui->screen_image_list_image, "Images");
	lv_obj_set_pos(ui->screen_image_list_image, 246, 1);
	lv_obj_set_size(ui->screen_image_list_image, 73, 182);
	lv_obj_set_scrollbar_mode(ui->screen_image_list_image, LV_SCROLLBAR_MODE_OFF);
	lv_obj_add_flag(ui->screen_image_list_image, LV_OBJ_FLAG_HIDDEN);

	//Write style state: LV_STATE_DEFAULT for &style_screen_image_list_image_main_main_default
	static lv_style_t style_screen_image_list_image_main_main_default;
	ui_init_style(&style_screen_image_list_image_main_main_default);
	
	lv_style_set_pad_top(&style_screen_image_list_image_main_main_default, 5);
	lv_style_set_pad_left(&style_screen_image_list_image_main_main_default, 5);
	lv_style_set_pad_right(&style_screen_image_list_image_main_main_default, 5);
	lv_style_set_pad_bottom(&style_screen_image_list_image_main_main_default, 5);
	lv_style_set_bg_opa(&style_screen_image_list_image_main_main_default, 215);
	lv_style_set_bg_color(&style_screen_image_list_image_main_main_default, lv_color_hex(0xd86700));
	lv_style_set_bg_grad_dir(&style_screen_image_list_image_main_main_default, LV_GRAD_DIR_VER);
	lv_style_set_bg_grad_color(&style_screen_image_list_image_main_main_default, lv_color_hex(0x35a605));
	lv_style_set_border_width(&style_screen_image_list_image_main_main_default, 0);
	lv_style_set_radius(&style_screen_image_list_image_main_main_default, 3);
	lv_style_set_shadow_width(&style_screen_image_list_image_main_main_default, 0);
	lv_obj_add_style(ui->screen_image_list_image, &style_screen_image_list_image_main_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_image_list_image_main_scrollbar_default
	static lv_style_t style_screen_image_list_image_main_scrollbar_default;
	ui_init_style(&style_screen_image_list_image_main_scrollbar_default);
	
	lv_style_set_radius(&style_screen_image_list_image_main_scrollbar_default, 3);
	lv_style_set_bg_opa(&style_screen_image_list_image_main_scrollbar_default, 255);
	lv_style_set_bg_color(&style_screen_image_list_image_main_scrollbar_default, lv_color_hex(0xffffff));
	lv_obj_add_style(ui->screen_image_list_image, &style_screen_image_list_image_main_scrollbar_default, LV_PART_SCROLLBAR|LV_STATE_DEFAULT);

	//Write style state: LV_STATE_DEFAULT for &style_screen_image_list_image_extra_btns_main_default
	static lv_style_t style_screen_image_list_image_extra_btns_main_default;
	ui_init_style(&style_screen_image_list_image_extra_btns_main_default);
	
	lv_style_set_pad_top(&style_screen_image_list_image_extra_btns_main_default, 0);
	lv_style_set_pad_left(&style_screen_image_list_image_extra_btns_main_default, 0);
	lv_style_set_pad_right(&style_screen_image_list_image_extra_btns_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_image_list_image_extra_btns_main_default, 0);
	lv_style_set_border_width(&style_screen_image_list_image_extra_btns_main_default, 0);
	lv_style_set_text_color(&style_screen_image_list_image_extra_btns_main_default, lv_color_hex(0x0D3055));
	lv_style_set_text_font(&style_screen_image_list_image_extra_btns_main_default, &lv_font_montserratMedium_12);
	lv_style_set_radius(&style_screen_image_list_image_extra_btns_main_default, 3);
	lv_style_set_bg_opa(&style_screen_image_list_image_extra_btns_main_default, 144);
	lv_style_set_bg_color(&style_screen_image_list_image_extra_btns_main_default, lv_color_hex(0x340000));

	//Write style state: LV_STATE_DEFAULT for &style_screen_image_list_image_extra_texts_main_default
	static lv_style_t style_screen_image_list_image_extra_texts_main_default;
	ui_init_style(&style_screen_image_list_image_extra_texts_main_default);
	
	lv_style_set_pad_top(&style_screen_image_list_image_extra_texts_main_default, 5);
	lv_style_set_pad_left(&style_screen_image_list_image_extra_texts_main_default, 0);
	lv_style_set_pad_right(&style_screen_image_list_image_extra_texts_main_default, 0);
	lv_style_set_pad_bottom(&style_screen_image_list_image_extra_texts_main_default, 5);
	lv_style_set_border_width(&style_screen_image_list_image_extra_texts_main_default, 2);
	lv_style_set_border_opa(&style_screen_image_list_image_extra_texts_main_default, 255);
	lv_style_set_border_color(&style_screen_image_list_image_extra_texts_main_default, lv_color_hex(0xe1e6ee));
	lv_style_set_border_side(&style_screen_image_list_image_extra_texts_main_default, LV_BORDER_SIDE_BOTTOM);
	lv_style_set_text_color(&style_screen_image_list_image_extra_texts_main_default, lv_color_hex(0xeaeaea));
	lv_style_set_text_font(&style_screen_image_list_image_extra_texts_main_default, &lv_font_Abel_regular_12);
	lv_style_set_radius(&style_screen_image_list_image_extra_texts_main_default, 2);
	lv_style_set_bg_opa(&style_screen_image_list_image_extra_texts_main_default, 0);
	lv_obj_add_style(ui->screen_image_list_image_item0, &style_screen_image_list_image_extra_texts_main_default, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_image_label_1
	ui->screen_image_label_1 = lv_label_create(ui->screen_image);
	lv_label_set_text(ui->screen_image_label_1, "");
	lv_label_set_long_mode(ui->screen_image_label_1, LV_LABEL_LONG_WRAP);
	lv_obj_set_pos(ui->screen_image_label_1, 2, 190);
	lv_obj_set_size(ui->screen_image_label_1, 316, 45);

	//Write style for screen_image_label_1, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_border_width(ui->screen_image_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_radius(ui->screen_image_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_color(ui->screen_image_label_1, lv_color_hex(0x000000), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_font(ui->screen_image_label_1, &lv_font_montserratMedium_16, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_letter_space(ui->screen_image_label_1, 2, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_line_space(ui->screen_image_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_text_align(ui->screen_image_label_1, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_opa(ui->screen_image_label_1, 133, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_bg_color(ui->screen_image_label_1, lv_color_hex(0xff0027), LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_top(ui->screen_image_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_right(ui->screen_image_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_bottom(ui->screen_image_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_pad_left(ui->screen_image_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);
	lv_obj_set_style_shadow_width(ui->screen_image_label_1, 0, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Write codes screen_image_img_display
	ui->screen_image_img_display = lv_img_create(ui->screen_image);
	lv_obj_add_flag(ui->screen_image_img_display, LV_OBJ_FLAG_CLICKABLE);
	lv_img_set_src(ui->screen_image_img_display, &_nichijou_alpha_230x160);
	lv_img_set_pivot(ui->screen_image_img_display, 50,50);
	lv_img_set_angle(ui->screen_image_img_display, 0);
	lv_obj_set_pos(ui->screen_image_img_display, 52, 21);
	lv_obj_set_size(ui->screen_image_img_display, 230, 160);

	//Write style for screen_image_img_display, Part: LV_PART_MAIN, State: LV_STATE_DEFAULT.
	lv_obj_set_style_img_opa(ui->screen_image_img_display, 255, LV_PART_MAIN|LV_STATE_DEFAULT);

	//Update current screen layout.
	lv_obj_update_layout(ui->screen_image);

	
}
