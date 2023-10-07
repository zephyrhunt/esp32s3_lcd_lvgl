// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.2
// LVGL version: 8.3.6
// Project name: SquarePrj

#ifndef _SQUAREPRJ_UI_H
#define _SQUAREPRJ_UI_H

#ifdef __cplusplus
extern "C" {
#endif

    #include "lvgl.h"

#include "ui_helpers.h"
#include "ui_events.h"
void play_Animation( lv_obj_t *TargetObject, int delay);
// SCREEN: ui_ScreenMain
void ui_ScreenMain_screen_init(void);
extern lv_obj_t *ui_ScreenMain;
extern lv_obj_t *ui_PanelMain;
extern lv_obj_t *ui_ImgBtnWeather;
void ui_event_ImgBtnPlay( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnPlay;
void ui_event_ImgBtnSet( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnSet;
void ui_event_ImgBtnControl( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnControl;
extern lv_obj_t *ui_Panel3;
extern lv_obj_t *ui_ImageBle;
extern lv_obj_t *ui_ImageUsb;
extern lv_obj_t *ui_ImageWifi;
extern lv_obj_t *ui_LabelDate;
extern lv_obj_t *ui_LabelLocation;
extern lv_obj_t *ui_Weather;
extern lv_obj_t *ui_Image7;
extern lv_obj_t *ui_LabelReport;
// SCREEN: ui_ScreenMain1
void ui_ScreenMain1_screen_init(void);
extern lv_obj_t *ui_ScreenMain1;
extern lv_obj_t *ui_PanelMain1;
void ui_event_ImgBtnWeather1( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnWeather1;
extern lv_obj_t *ui_ImgBtnPlay1;
void ui_event_ImgBtnSet1( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnSet1;
void ui_event_ImgBtnControl1( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnControl1;
extern lv_obj_t *ui_Panel1;
extern lv_obj_t *ui_ImageBle1;
extern lv_obj_t *ui_ImageUsb1;
extern lv_obj_t *ui_ImageWifi1;
extern lv_obj_t *ui_ImagePlay;
// SCREEN: ui_ScreenMain2
void ui_ScreenMain2_screen_init(void);
extern lv_obj_t *ui_ScreenMain2;
extern lv_obj_t *ui_PanelMain2;
void ui_event_ImgBtnWeather2( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnWeather2;
void ui_event_ImgBtnPlay2( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnPlay2;
void ui_event_ImgBtnSet2( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnSet2;
extern lv_obj_t *ui_ImgBtnControl2;
extern lv_obj_t *ui_Panel2;
extern lv_obj_t *ui_ImageBle2;
extern lv_obj_t *ui_ImageUsb2;
extern lv_obj_t *ui_ImageWifi2;
extern lv_obj_t *ui_Slider1;
// SCREEN: ui_ScreenMain3
void ui_ScreenMain3_screen_init(void);
extern lv_obj_t *ui_ScreenMain3;
extern lv_obj_t *ui_PanelMain3;
void ui_event_ImgBtnWeather3( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnWeather3;
void ui_event_ImgBtnPlay3( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnPlay3;
extern lv_obj_t *ui_ImgBtnSet3;
void ui_event_ImgBtnControl3( lv_event_t * e);
extern lv_obj_t *ui_ImgBtnControl3;
extern lv_obj_t *ui_Panel4;
extern lv_obj_t *ui_ImageBle3;
extern lv_obj_t *ui_ImageUsb3;
extern lv_obj_t *ui_ImageWifi3;
extern lv_obj_t *ui_Group;
extern lv_obj_t *ui_list1;
extern lv_obj_t *ui_Image9;
extern lv_obj_t *ui_Label3;
extern lv_obj_t *ui_list2;
extern lv_obj_t *ui_Image1;
extern lv_obj_t *ui_Label1;
extern lv_obj_t *ui_list3;
extern lv_obj_t *ui_Image2;
extern lv_obj_t *ui_Label2;
extern lv_obj_t *ui_list4;
extern lv_obj_t *ui_Image3;
extern lv_obj_t *ui_Label4;
extern lv_obj_t *ui_list5;
extern lv_obj_t *ui_Image4;
extern lv_obj_t *ui_Label5;
void ui_event____initial_actions0( lv_event_t * e);
extern lv_obj_t *ui____initial_actions0;

LV_IMG_DECLARE( ui_img_blue_brown_bg320_240_png);   // assets\blue_brown_bg320_240.png
LV_IMG_DECLARE( ui_img_weather_simple52_png);   // assets\weather_simple52.png
LV_IMG_DECLARE( ui_img_video3o60_60_png);   // assets\video3o60_60.png
LV_IMG_DECLARE( ui_img_videos60_60_png);   // assets\videos60_60.png
LV_IMG_DECLARE( ui_img_setting60_60_png);   // assets\setting60_60.png
LV_IMG_DECLARE( ui_img_robot60_60_png);   // assets\robot60_60.png
LV_IMG_DECLARE( ui_img_bluetooth30_30_png);   // assets\bluetooth30_30.png
LV_IMG_DECLARE( ui_img_usb30_30_png);   // assets\usb30_30.png
LV_IMG_DECLARE( ui_img_wifi30_30_png);   // assets\wifi30_30.png
LV_IMG_DECLARE( ui_img_rain60_60_png);   // assets\rain60_60.png
LV_IMG_DECLARE( ui_img_weather_simple60_60_png);   // assets\weather_simple60_60.png
LV_IMG_DECLARE( ui_img_hutao_15_png);   // assets\hutao_15.png
LV_IMG_DECLARE( ui_img_robot_arm30_30_png);   // assets\robot_arm30_30.png
LV_IMG_DECLARE( ui_img_api30_30_png);   // assets\api30_30.png
LV_IMG_DECLARE( ui_img_more30_30_png);   // assets\more30_30.png
LV_IMG_DECLARE( ui_img_hutao_0_png);   // assets\hutao_0.png
LV_IMG_DECLARE( ui_img_hutao_1_png);   // assets\hutao_1.png
LV_IMG_DECLARE( ui_img_hutao_10_png);   // assets\hutao_10.png
LV_IMG_DECLARE( ui_img_hutao_11_png);   // assets\hutao_11.png
LV_IMG_DECLARE( ui_img_hutao_12_png);   // assets\hutao_12.png
LV_IMG_DECLARE( ui_img_hutao_13_png);   // assets\hutao_13.png
LV_IMG_DECLARE( ui_img_hutao_14_png);   // assets\hutao_14.png
LV_IMG_DECLARE( ui_img_hutao_16_png);   // assets\hutao_16.png
LV_IMG_DECLARE( ui_img_hutao_17_png);   // assets\hutao_17.png
LV_IMG_DECLARE( ui_img_hutao_18_png);   // assets\hutao_18.png
LV_IMG_DECLARE( ui_img_hutao_19_png);   // assets\hutao_19.png
LV_IMG_DECLARE( ui_img_hutao_2_png);   // assets\hutao_2.png
LV_IMG_DECLARE( ui_img_hutao_20_png);   // assets\hutao_20.png
LV_IMG_DECLARE( ui_img_hutao_21_png);   // assets\hutao_21.png
LV_IMG_DECLARE( ui_img_hutao_22_png);   // assets\hutao_22.png
LV_IMG_DECLARE( ui_img_hutao_23_png);   // assets\hutao_23.png
LV_IMG_DECLARE( ui_img_hutao_24_png);   // assets\hutao_24.png
LV_IMG_DECLARE( ui_img_hutao_25_png);   // assets\hutao_25.png
LV_IMG_DECLARE( ui_img_hutao_26_png);   // assets\hutao_26.png
LV_IMG_DECLARE( ui_img_hutao_27_png);   // assets\hutao_27.png
LV_IMG_DECLARE( ui_img_hutao_28_png);   // assets\hutao_28.png
LV_IMG_DECLARE( ui_img_hutao_29_png);   // assets\hutao_29.png
LV_IMG_DECLARE( ui_img_hutao_3_png);   // assets\hutao_3.png
LV_IMG_DECLARE( ui_img_hutao_30_png);   // assets\hutao_30.png
LV_IMG_DECLARE( ui_img_hutao_31_png);   // assets\hutao_31.png
LV_IMG_DECLARE( ui_img_hutao_32_png);   // assets\hutao_32.png
LV_IMG_DECLARE( ui_img_hutao_33_png);   // assets\hutao_33.png
LV_IMG_DECLARE( ui_img_hutao_34_png);   // assets\hutao_34.png
LV_IMG_DECLARE( ui_img_hutao_35_png);   // assets\hutao_35.png
LV_IMG_DECLARE( ui_img_hutao_4_png);   // assets\hutao_4.png
LV_IMG_DECLARE( ui_img_hutao_5_png);   // assets\hutao_5.png
LV_IMG_DECLARE( ui_img_hutao_6_png);   // assets\hutao_6.png
LV_IMG_DECLARE( ui_img_hutao_7_png);   // assets\hutao_7.png
LV_IMG_DECLARE( ui_img_hutao_8_png);   // assets\hutao_8.png
LV_IMG_DECLARE( ui_img_hutao_9_png);   // assets\hutao_9.png
LV_IMG_DECLARE( ui_img_video60_60_png);   // assets\video60_60.png
LV_IMG_DECLARE( ui_img_weathe2_png);   // assets\weathe2.png
LV_IMG_DECLARE( ui_img_weather_square60_60_png);   // assets\weather_square60_60.png



void ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif

#endif
