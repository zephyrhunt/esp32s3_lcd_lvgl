/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/

#ifndef __CUSTOM_H_
#define __CUSTOM_H_
#ifdef __cplusplus
extern "C" {
#endif

#include "gui_guider.h"

typedef struct {
  int8_t id;
  int8_t id_max;
  int8_t id_min;
  int8_t is_child_focus;
}lv_cus_item_t;

typedef struct {
  int32_t time_ms;
}lv_cus_time_t;

void custom_init(lv_ui *ui);
void lv_cus_toggle(lv_obj_t * obj);
uint8_t lv_cus_is_display(lv_obj_t * obj);
int8_t lv_cus_to_next(lv_cus_item_t * item);
int8_t lv_cus_to_prev(lv_cus_item_t * item);
void lv_cus_disp_time(lv_obj_t * obj, uint32_t time_ms);
void lv_cus_set_x(lv_obj_t *obj, uint16_t x);

void lv_cus_focus_now(lv_obj_t *obj, lv_cus_item_t * item);
void lv_cus_focus_next(lv_obj_t *obj, lv_cus_item_t * item);
void lv_cus_focus_prev(lv_obj_t *obj, lv_cus_item_t * item);
void lv_cus_focus_none(lv_obj_t *obj, lv_cus_item_t * item);


#ifdef __cplusplus
}
#endif
#endif /* EVENT_CB_H_ */
