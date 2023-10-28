/*
* Copyright 2023 NXP
* NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
* accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
* activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
* terms, then you may not retain, install, activate or otherwise use the software.
*/


/*********************
 *      INCLUDES
 *********************/
#include <stdio.h>
#include "lvgl.h"
#include "custom.h"

/*********************
 *      DEFINES
 *********************/

/**********************
 *      TYPEDEFS
 **********************/

/**********************
 *  STATIC PROTOTYPES
 **********************/

/**********************
 *  STATIC VARIABLES
 **********************/

/**
 * Create a demo application
 */


static void scroll_event_cb(lv_event_t * e)
{
    lv_obj_t * cont = lv_event_get_target(e);

    lv_area_t cont_a;
    lv_obj_get_coords(cont, &cont_a);
    lv_coord_t cont_y_center = cont_a.y1 + lv_area_get_height(&cont_a) / 2;

    lv_coord_t r = lv_obj_get_height(cont) * 7 / 10;
    uint32_t i;
    uint32_t child_cnt = lv_obj_get_child_cnt(cont);
    for(i = 0; i < child_cnt; i++) {
        lv_obj_t * child = lv_obj_get_child(cont, i);
        lv_area_t child_a;
        lv_obj_get_coords(child, &child_a);

        lv_coord_t child_y_center = child_a.y1 + lv_area_get_height(&child_a) / 2;

        lv_coord_t diff_y = child_y_center - cont_y_center;
        diff_y = LV_ABS(diff_y);

        /*Get the x of diff_y on a circle.*/
        lv_coord_t x;
        /*If diff_y is out of the circle use the last point of the circle (the radius)*/
        if(diff_y >= r) {
            x = r;
        }
        else {
            /*Use Pythagoras theorem to get x from radius and y*/
            uint32_t x_sqr = r * r - diff_y * diff_y;
            lv_sqrt_res_t res;
            lv_sqrt(x_sqr, &res, 0x8000);   /*Use lvgl's built in sqrt root function*/
            x = r - res.i;
        }

        /*Translate the item by the calculated X coordinate*/
        lv_obj_set_style_translate_x(child, x, 0);

        /*Use some opacity with larger translations*/
        lv_opa_t opa = lv_map(x, 0, r, LV_OPA_TRANSP, LV_OPA_COVER);
        lv_obj_set_style_opa(child, LV_OPA_COVER - opa, 0);
    }
}

lv_obj_t * cont;
/**
 * Translate the object as they scroll
 */
void lv_example_scroll_6(void)
{
    cont = lv_obj_create(lv_scr_act());
    lv_obj_set_size(cont, 200, 200);
    lv_obj_center(cont);
    lv_obj_set_flex_flow(cont, LV_FLEX_FLOW_COLUMN);
    lv_obj_add_event_cb(cont, scroll_event_cb, LV_EVENT_SCROLL, NULL);
    lv_obj_set_style_radius(cont, LV_RADIUS_CIRCLE, 0);
    lv_obj_set_style_clip_corner(cont, true, 0);
    lv_obj_set_scroll_dir(cont, LV_DIR_VER);
    lv_obj_set_scroll_snap_y(cont, LV_SCROLL_SNAP_CENTER);
    lv_obj_set_scrollbar_mode(cont, LV_SCROLLBAR_MODE_OFF);

    uint32_t i;
    for(i = 0; i < 20; i++) {
        lv_obj_t * btn = lv_btn_create(cont);
        lv_obj_set_width(btn, lv_pct(100));

        lv_obj_t * label = lv_label_create(btn);
        lv_label_set_text_fmt(label, "Button %"LV_PRIu32, i);
    }

    /*Update the buttons position manually for first*/
    lv_event_send(cont, LV_EVENT_SCROLL, NULL);

    /*Be sure the fist button is in the middle*/
    lv_obj_scroll_to_view(lv_obj_get_child(cont, 0), LV_ANIM_OFF);
}

void lv_cus_toggle(lv_obj_t * obj)
{
    if (lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN))
        lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
    else
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

uint8_t lv_cus_is_display(lv_obj_t * obj)
{
    if (lv_obj_has_flag(obj, LV_OBJ_FLAG_HIDDEN))
        return 0;
    else
        return 1;
}

void lv_cus_focus_now(lv_obj_t *obj, lv_cus_item_t * item)
{
    lv_obj_t *child = lv_obj_get_child(obj, item->id);
    lv_event_send(child, LV_EVENT_FOCUSED, NULL);
}

void lv_cus_focus_next(lv_obj_t *obj, lv_cus_item_t * item)
{
    int8_t id_pre = item->id;
    lv_obj_t *child = lv_obj_get_child(obj, lv_cus_to_next(item));
    lv_event_send(child, LV_EVENT_FOCUSED, NULL);
    lv_obj_t *last_child = lv_obj_get_child(obj, id_pre);
    lv_event_send(last_child, LV_EVENT_DEFOCUSED, NULL);
}

void lv_cus_focus_prev(lv_obj_t *obj, lv_cus_item_t * item)
{
    int8_t id_pre = item->id;
    lv_obj_t *child = lv_obj_get_child(obj, lv_cus_to_prev(item));
    lv_event_send(child, LV_EVENT_FOCUSED, NULL);
    lv_obj_t *last_child = lv_obj_get_child(obj, id_pre);
    lv_event_send(last_child, LV_EVENT_DEFOCUSED, NULL);
}

void lv_cus_focus_none(lv_obj_t *obj, lv_cus_item_t * item)
{
    int8_t id_pre = item->id;
    lv_obj_t *child = lv_obj_get_child(obj, id_pre);
    lv_event_send(child, LV_EVENT_DEFOCUSED, NULL);
}

int8_t lv_cus_to_next(lv_cus_item_t * item)
{
    item->id_last = item->id;
    item->id++;
    if (item->id > item->id_max)
        item->id = item->id_min; // usually 0

    return item->id;
}

int8_t lv_cus_to_prev(lv_cus_item_t * item)
{
    item->id_next = item->id;
    item->id--;
    if (item->id < item->id_min)
        item->id = item->id_max;

    return item->id;
}

void lv_set_time(lv_obj_t * obj, uint16_t time)
{
//    lv_obj_set_style_opa(obj, opa, LV_STATE_DEFAULT);
    if (time <= 1)
        lv_obj_add_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

//void lv_cus_anime_move(lv)
void lv_cus_disp_time(lv_obj_t * obj, uint32_t time_ms)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, 1200);
    lv_anim_set_values(&a, 240, 0);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_set_time);
    lv_anim_start(&a);
    lv_obj_clear_flag(obj, LV_OBJ_FLAG_HIDDEN);
}

void lv_cus_set_x(lv_obj_t *obj, uint16_t x)
{
    lv_anim_t a;
    lv_anim_init(&a);
    lv_anim_set_var(&a, obj);
    lv_anim_set_time(&a, 300);
    lv_anim_set_path_cb(&a, lv_anim_path_overshoot);
    lv_anim_set_values(&a, lv_obj_get_x(obj), x);
    lv_anim_set_exec_cb(&a, (lv_anim_exec_xcb_t) lv_obj_set_x);
    lv_anim_start(&a);
}

void custom_init(lv_ui *ui)
{
    /* Add your codes here */
//  lv_example_scroll_6();
}

