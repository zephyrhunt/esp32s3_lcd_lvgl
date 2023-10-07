// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquarePrj

#include "../ui.h"

void ui_ScreenMain_screen_init(void)
{
ui_ScreenMain = lv_obj_create(NULL);
lv_obj_clear_flag( ui_ScreenMain, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_img_src( ui_ScreenMain, &ui_img_blue_brown_bg320_240_png, LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_font(ui_ScreenMain, &lv_font_montserrat_8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PanelMain = lv_obj_create(ui_ScreenMain);
lv_obj_set_width( ui_PanelMain, 320);
lv_obj_set_height( ui_PanelMain, 62);
lv_obj_set_align( ui_PanelMain, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_PanelMain, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_PanelMain, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_PanelMain, lv_color_hex(0xFFDAB4), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_PanelMain, 100, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_PanelMain, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_PanelMain, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_PanelMain, lv_color_hex(0xB0D6EE), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_PanelMain, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(ui_PanelMain, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(ui_PanelMain, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_ofs_x(ui_PanelMain, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_ofs_y(ui_PanelMain, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgBtnWeather = lv_imgbtn_create(ui_PanelMain);
lv_imgbtn_set_src(ui_ImgBtnWeather, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_weather_simple52_png, NULL);
lv_obj_set_height( ui_ImgBtnWeather, 52);
lv_obj_set_width( ui_ImgBtnWeather, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgBtnWeather, -120 );
lv_obj_set_y( ui_ImgBtnWeather, 0 );
lv_obj_set_align( ui_ImgBtnWeather, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_ImgBtnWeather, LV_OBJ_FLAG_CLICKABLE );    /// Flags

ui_ImgBtnPlay = lv_imgbtn_create(ui_PanelMain);
lv_imgbtn_set_src(ui_ImgBtnPlay, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_video3o60_60_png, NULL);
lv_imgbtn_set_src(ui_ImgBtnPlay, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_videos60_60_png, NULL);
lv_obj_set_height( ui_ImgBtnPlay, 60);
lv_obj_set_width( ui_ImgBtnPlay, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgBtnPlay, -40 );
lv_obj_set_y( ui_ImgBtnPlay, 2 );
lv_obj_set_align( ui_ImgBtnPlay, LV_ALIGN_CENTER );
lv_obj_set_style_opa(ui_ImgBtnPlay, 100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgBtnSet = lv_imgbtn_create(ui_PanelMain);
lv_imgbtn_set_src(ui_ImgBtnSet, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_setting60_60_png, NULL);
lv_imgbtn_set_src(ui_ImgBtnSet, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_setting60_60_png, NULL);
lv_obj_set_height( ui_ImgBtnSet, 60);
lv_obj_set_width( ui_ImgBtnSet, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgBtnSet, 120 );
lv_obj_set_y( ui_ImgBtnSet, 0 );
lv_obj_set_align( ui_ImgBtnSet, LV_ALIGN_CENTER );
lv_obj_set_style_blend_mode(ui_ImgBtnSet, LV_BLEND_MODE_NORMAL, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_opa(ui_ImgBtnSet, 100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgBtnControl = lv_imgbtn_create(ui_PanelMain);
lv_imgbtn_set_src(ui_ImgBtnControl, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_robot60_60_png, NULL);
lv_imgbtn_set_src(ui_ImgBtnControl, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_robot60_60_png, NULL);
lv_obj_set_height( ui_ImgBtnControl, 60);
lv_obj_set_width( ui_ImgBtnControl, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgBtnControl, 40 );
lv_obj_set_y( ui_ImgBtnControl, 0 );
lv_obj_set_align( ui_ImgBtnControl, LV_ALIGN_CENTER );
lv_obj_set_style_blend_mode(ui_ImgBtnControl, LV_BLEND_MODE_NORMAL, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_opa(ui_ImgBtnControl, 100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel3 = lv_obj_create(ui_ScreenMain);
lv_obj_set_width( ui_Panel3, 130);
lv_obj_set_height( ui_Panel3, 36);
lv_obj_set_x( ui_Panel3, 10 );
lv_obj_set_y( ui_Panel3, 0 );
lv_obj_set_align( ui_Panel3, LV_ALIGN_TOP_RIGHT );
lv_obj_clear_flag( ui_Panel3, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel3, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel3, lv_color_hex(0xB3D9EE), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel3, 160, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel3, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_Panel3, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImageBle = lv_img_create(ui_Panel3);
lv_img_set_src(ui_ImageBle, &ui_img_bluetooth30_30_png);
lv_obj_set_width( ui_ImageBle, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ImageBle, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ImageBle, -32 );
lv_obj_set_y( ui_ImageBle, 0 );
lv_obj_set_align( ui_ImageBle, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ImageBle, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_ImageBle, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_ImageBle, lv_color_hex(0xA6A6A6), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_ImageBle, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImageUsb = lv_img_create(ui_Panel3);
lv_img_set_src(ui_ImageUsb, &ui_img_usb30_30_png);
lv_obj_set_width( ui_ImageUsb, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ImageUsb, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ImageUsb, -1 );
lv_obj_set_y( ui_ImageUsb, 0 );
lv_obj_set_align( ui_ImageUsb, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ImageUsb, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_ImageUsb, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_ImageUsb, lv_color_hex(0xA6A6A6), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_ImageUsb, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImageWifi = lv_img_create(ui_Panel3);
lv_img_set_src(ui_ImageWifi, &ui_img_wifi30_30_png);
lv_obj_set_width( ui_ImageWifi, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ImageWifi, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ImageWifi, 33 );
lv_obj_set_y( ui_ImageWifi, 0 );
lv_obj_set_align( ui_ImageWifi, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ImageWifi, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_ImageWifi, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_ImageWifi, lv_color_hex(0xA6A6A6), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_ImageWifi, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LabelDate = lv_label_create(ui_ScreenMain);
lv_obj_set_width( ui_LabelDate, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelDate, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelDate, -88 );
lv_obj_set_y( ui_LabelDate, -53 );
lv_obj_set_align( ui_LabelDate, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelDate,"Date: 2023-7-10");
lv_obj_set_style_text_color(ui_LabelDate, lv_color_hex(0x8E8E8E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_LabelDate, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_LabelDate, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_LabelDate, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_LabelDate, lv_color_hex(0xFFD6B4), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_LabelDate, 200, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_LabelDate, lv_color_hex(0xA7D2E6), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_main_stop(ui_LabelDate, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_stop(ui_LabelDate, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_dir(ui_LabelDate, LV_GRAD_DIR_HOR, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_LabelLocation = lv_label_create(ui_ScreenMain);
lv_obj_set_width( ui_LabelLocation, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_LabelLocation, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_LabelLocation, -91 );
lv_obj_set_y( ui_LabelLocation, -78 );
lv_obj_set_align( ui_LabelLocation, LV_ALIGN_CENTER );
lv_label_set_text(ui_LabelLocation,"Local: WuHan");
lv_obj_set_style_text_color(ui_LabelLocation, lv_color_hex(0x8E8E8E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_LabelLocation, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_LabelLocation, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_LabelLocation, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_LabelLocation, lv_color_hex(0xFFD6B4), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_LabelLocation, 200, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_LabelLocation, lv_color_hex(0xA7D2E6), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_main_stop(ui_LabelLocation, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_stop(ui_LabelLocation, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_dir(ui_LabelLocation, LV_GRAD_DIR_HOR, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Weather = lv_label_create(ui_ScreenMain);
lv_obj_set_width( ui_Weather, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Weather, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Weather, -90 );
lv_obj_set_y( ui_Weather, -28 );
lv_obj_set_align( ui_Weather, LV_ALIGN_CENTER );
lv_label_set_text(ui_Weather,"Weather: Rain");
lv_obj_set_style_text_color(ui_Weather, lv_color_hex(0x8E8E8E), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_Weather, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_Weather, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_Weather, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Weather, lv_color_hex(0xFFD6B4), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Weather, 200, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_color(ui_Weather, lv_color_hex(0xA7D2E6), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_main_stop(ui_Weather, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_stop(ui_Weather, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_grad_dir(ui_Weather, LV_GRAD_DIR_HOR, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_TextArea1 = lv_textarea_create(ui_ScreenMain);
lv_obj_set_width( ui_TextArea1, 260);
lv_obj_set_height( ui_TextArea1, 70);
lv_obj_set_x( ui_TextArea1, -1 );
lv_obj_set_y( ui_TextArea1, 20 );
lv_obj_set_align( ui_TextArea1, LV_ALIGN_CENTER );
lv_textarea_set_text(ui_TextArea1,"Report:");
lv_textarea_set_placeholder_text(ui_TextArea1,"Placeholder...");
lv_obj_clear_flag( ui_TextArea1, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_PRESS_LOCK | LV_OBJ_FLAG_CLICK_FOCUSABLE | LV_OBJ_FLAG_GESTURE_BUBBLE | LV_OBJ_FLAG_SNAPPABLE );    /// Flags
lv_obj_set_style_text_font(ui_TextArea1, &lv_font_montserrat_14, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_radius(ui_TextArea1, 8, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_TextArea1, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_TextArea1, 150, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_TextArea1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_TextArea1, 0, LV_PART_MAIN| LV_STATE_DEFAULT);



ui_Image7 = lv_img_create(ui_ScreenMain);
lv_img_set_src(ui_Image7, &ui_img_rain60_60_png);
lv_obj_set_width( ui_Image7, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_Image7, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_Image7, 37 );
lv_obj_set_y( ui_Image7, -50 );
lv_obj_set_align( ui_Image7, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_Image7, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_Image7, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

lv_obj_add_event_cb(ui_ImgBtnPlay, ui_event_ImgBtnPlay, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ImgBtnSet, ui_event_ImgBtnSet, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ImgBtnControl, ui_event_ImgBtnControl, LV_EVENT_ALL, NULL);

}
