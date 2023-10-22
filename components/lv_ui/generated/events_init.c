/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#include "events_init.h"
#include <stdio.h>
#include "lvgl.h"


static void screen_main_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	default:
		break;
	}
}
static void screen_main_cont_weather_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_add_flag(guider_ui.screen_main_img_voice, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(guider_ui.screen_main_img_mute, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_main_btn_app1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.screen_main_cont_app, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_main_list_musics, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_main_img_menu1_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.screen_main_list_musics, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(guider_ui.screen_main_cont_app, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
static void screen_main_img_setting_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_setting_del == true) {
	          setup_scr_screen_setting(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_setting, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
	        guider_ui.screen_main_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
static void screen_main_img_light_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		lv_obj_clear_flag(guider_ui.screen_main_slider_light, LV_OBJ_FLAG_HIDDEN);
		break;
	}
	default:
		break;
	}
}
void events_init_screen_main(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_main, screen_main_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_cont_weather, screen_main_cont_weather_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_btn_app1, screen_main_btn_app1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_img_menu1, screen_main_img_menu1_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_img_setting, screen_main_img_setting_event_handler, LV_EVENT_ALL, NULL);
	lv_obj_add_event_cb(ui->screen_main_img_light, screen_main_img_light_event_handler, LV_EVENT_ALL, NULL);
}
static void screen_setting_img_home2_event_handler (lv_event_t *e)
{
	lv_event_code_t code = lv_event_get_code(e);

	switch (code) {
	case LV_EVENT_CLICKED:
	{
		//Write the load screen code.
	    lv_obj_t * act_scr = lv_scr_act();
	    lv_disp_t * d = lv_obj_get_disp(act_scr);
	    if (d->prev_scr == NULL && (d->scr_to_load == NULL || d->scr_to_load == act_scr)) {
	        if (guider_ui.screen_main_del == true) {
	          setup_scr_screen_main(&guider_ui);
	        }
	        lv_scr_load_anim(guider_ui.screen_main, LV_SCR_LOAD_ANIM_NONE, 200, 200, true);
	        guider_ui.screen_setting_del = true;
	    }
		break;
	}
	default:
		break;
	}
}
void events_init_screen_setting(lv_ui *ui)
{
	lv_obj_add_event_cb(ui->screen_setting_img_home2, screen_setting_img_home2_event_handler, LV_EVENT_ALL, NULL);
}

void events_init(lv_ui *ui)
{

}
