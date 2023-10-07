// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquarePrj

#include "../ui.h"

void ui_ScreenMain2_screen_init(void)
{
ui_ScreenMain2 = lv_obj_create(NULL);
lv_obj_clear_flag( ui_ScreenMain2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_img_src( ui_ScreenMain2, &ui_img_blue_brown_bg320_240_png, LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_font(ui_ScreenMain2, &lv_font_montserrat_8, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_PanelMain2 = lv_obj_create(ui_ScreenMain2);
lv_obj_set_width( ui_PanelMain2, 320);
lv_obj_set_height( ui_PanelMain2, 62);
lv_obj_set_align( ui_PanelMain2, LV_ALIGN_BOTTOM_MID );
lv_obj_clear_flag( ui_PanelMain2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_PanelMain2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_PanelMain2, lv_color_hex(0xFFDAB4), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_PanelMain2, 100, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_PanelMain2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_PanelMain2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_color(ui_PanelMain2, lv_color_hex(0xB0D6EE), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_shadow_opa(ui_PanelMain2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_width(ui_PanelMain2, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_spread(ui_PanelMain2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_ofs_x(ui_PanelMain2, 5, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_shadow_ofs_y(ui_PanelMain2, 5, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgBtnWeather2 = lv_imgbtn_create(ui_PanelMain2);
lv_imgbtn_set_src(ui_ImgBtnWeather2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_weather_simple52_png, NULL);
lv_imgbtn_set_src(ui_ImgBtnWeather2, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_weather_simple60_60_png, NULL);
lv_obj_set_height( ui_ImgBtnWeather2, 52);
lv_obj_set_width( ui_ImgBtnWeather2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgBtnWeather2, -120 );
lv_obj_set_y( ui_ImgBtnWeather2, 0 );
lv_obj_set_align( ui_ImgBtnWeather2, LV_ALIGN_CENTER );
lv_obj_set_style_opa(ui_ImgBtnWeather2, 100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgBtnPlay2 = lv_imgbtn_create(ui_PanelMain2);
lv_imgbtn_set_src(ui_ImgBtnPlay2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_video3o60_60_png, NULL);
lv_imgbtn_set_src(ui_ImgBtnPlay2, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_video3o60_60_png, NULL);
lv_obj_set_height( ui_ImgBtnPlay2, 60);
lv_obj_set_width( ui_ImgBtnPlay2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgBtnPlay2, -40 );
lv_obj_set_y( ui_ImgBtnPlay2, 2 );
lv_obj_set_align( ui_ImgBtnPlay2, LV_ALIGN_CENTER );
lv_obj_set_style_opa(ui_ImgBtnPlay2, 100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgBtnSet2 = lv_imgbtn_create(ui_PanelMain2);
lv_imgbtn_set_src(ui_ImgBtnSet2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_setting60_60_png, NULL);
lv_imgbtn_set_src(ui_ImgBtnSet2, LV_IMGBTN_STATE_PRESSED, NULL, &ui_img_setting60_60_png, NULL);
lv_obj_set_height( ui_ImgBtnSet2, 60);
lv_obj_set_width( ui_ImgBtnSet2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgBtnSet2, 120 );
lv_obj_set_y( ui_ImgBtnSet2, 0 );
lv_obj_set_align( ui_ImgBtnSet2, LV_ALIGN_CENTER );
lv_obj_set_style_blend_mode(ui_ImgBtnSet2, LV_BLEND_MODE_NORMAL, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_opa(ui_ImgBtnSet2, 100, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImgBtnControl2 = lv_imgbtn_create(ui_PanelMain2);
lv_imgbtn_set_src(ui_ImgBtnControl2, LV_IMGBTN_STATE_RELEASED, NULL, &ui_img_robot60_60_png, NULL);
lv_obj_set_height( ui_ImgBtnControl2, 60);
lv_obj_set_width( ui_ImgBtnControl2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_x( ui_ImgBtnControl2, 40 );
lv_obj_set_y( ui_ImgBtnControl2, 0 );
lv_obj_set_align( ui_ImgBtnControl2, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_ImgBtnControl2, LV_OBJ_FLAG_CLICKABLE );    /// Flags
lv_obj_set_style_blend_mode(ui_ImgBtnControl2, LV_BLEND_MODE_NORMAL, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Panel2 = lv_obj_create(ui_ScreenMain2);
lv_obj_set_width( ui_Panel2, 130);
lv_obj_set_height( ui_Panel2, 36);
lv_obj_set_x( ui_Panel2, 10 );
lv_obj_set_y( ui_Panel2, 0 );
lv_obj_set_align( ui_Panel2, LV_ALIGN_TOP_RIGHT );
lv_obj_clear_flag( ui_Panel2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_radius(ui_Panel2, 15, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Panel2, lv_color_hex(0xB3D9EE), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Panel2, 160, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_color(ui_Panel2, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_border_opa(ui_Panel2, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImageBle2 = lv_img_create(ui_Panel2);
lv_img_set_src(ui_ImageBle2, &ui_img_bluetooth30_30_png);
lv_obj_set_width( ui_ImageBle2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ImageBle2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ImageBle2, -32 );
lv_obj_set_y( ui_ImageBle2, 0 );
lv_obj_set_align( ui_ImageBle2, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ImageBle2, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_ImageBle2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_ImageBle2, lv_color_hex(0xA6A6A6), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_ImageBle2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImageUsb2 = lv_img_create(ui_Panel2);
lv_img_set_src(ui_ImageUsb2, &ui_img_usb30_30_png);
lv_obj_set_width( ui_ImageUsb2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ImageUsb2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ImageUsb2, -1 );
lv_obj_set_y( ui_ImageUsb2, 0 );
lv_obj_set_align( ui_ImageUsb2, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ImageUsb2, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_ImageUsb2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_ImageUsb2, lv_color_hex(0xA6A6A6), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_ImageUsb2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_ImageWifi2 = lv_img_create(ui_Panel2);
lv_img_set_src(ui_ImageWifi2, &ui_img_wifi30_30_png);
lv_obj_set_width( ui_ImageWifi2, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_ImageWifi2, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_ImageWifi2, 33 );
lv_obj_set_y( ui_ImageWifi2, 0 );
lv_obj_set_align( ui_ImageWifi2, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_ImageWifi2, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_ImageWifi2, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_img_recolor(ui_ImageWifi2, lv_color_hex(0xA6A6A6), LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_img_recolor_opa(ui_ImageWifi2, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_Slider1 = lv_slider_create(ui_ScreenMain2);
lv_obj_set_width( ui_Slider1, 200);
lv_obj_set_height( ui_Slider1, 50);
lv_obj_set_x( ui_Slider1, 1 );
lv_obj_set_y( ui_Slider1, -14 );
lv_obj_set_align( ui_Slider1, LV_ALIGN_CENTER );
lv_obj_set_style_radius(ui_Slider1, 10, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_bg_img_src( ui_Slider1, &ui_img_robot_arm30_30_png, LV_PART_MAIN | LV_STATE_DEFAULT );

lv_obj_set_style_radius(ui_Slider1, 10, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xFFDCBA), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Slider1, 150, LV_PART_INDICATOR| LV_STATE_DEFAULT);

lv_obj_set_style_radius(ui_Slider1, 0, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_bg_color(ui_Slider1, lv_color_hex(0xFFFFFF), LV_PART_KNOB | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_Slider1, 0, LV_PART_KNOB| LV_STATE_DEFAULT);

lv_obj_add_event_cb(ui_ImgBtnWeather2, ui_event_ImgBtnWeather2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ImgBtnPlay2, ui_event_ImgBtnPlay2, LV_EVENT_ALL, NULL);
lv_obj_add_event_cb(ui_ImgBtnSet2, ui_event_ImgBtnSet2, LV_EVENT_ALL, NULL);

}
