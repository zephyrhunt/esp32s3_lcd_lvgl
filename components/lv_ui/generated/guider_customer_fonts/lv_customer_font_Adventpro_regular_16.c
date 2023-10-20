/*
 * Copyright 2023 NXP
 * NXP Confidential and Proprietary. This software is owned or controlled by NXP and may only be used strictly in
 * accordance with the applicable license terms. By expressly accepting such terms or by downloading, installing,
 * activating and/or otherwise using the software, you are agreeing that you have read, and that you agree to
 * comply with and are bound by, such license terms.  If you do not agree to be bound by the applicable license
 * terms, then you may not retain, install, activate or otherwise use the software.
 */
/*******************************************************************************
 * Size: 16 px
 * Bpp: 4
 * Opts: --user-data-dir=C:\Users\15341\AppData\Roaming\gui-guider --app-path=C:\NXP\GUI-Guider-1.6.1-GA\resources\app.asar --no-sandbox --no-zygote --lang=zh-CN --device-scale-factor=1.5 --num-raster-threads=4 --enable-main-frame-before-activation --renderer-client-id=5 --time-ticks-at-unix-epoch=-1697397275763561 --launch-time-ticks=315992401994 --mojo-platform-channel-handle=2824 --field-trial-handle=1740,i,14364229891389902407,8450241825491093044,131072 --disable-features=SpareRendererForSitePerProcess,WinRetrieveSuggestionsOnlyOnDemand /prefetch:1
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl.h"
#endif

#ifndef LV_CUSTOMER_FONT_ADVENTPRO_REGULAR_16
#define LV_CUSTOMER_FONT_ADVENTPRO_REGULAR_16 1
#endif

#if LV_CUSTOMER_FONT_ADVENTPRO_REGULAR_16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0061 "a" */
    0x0, 0x6, 0xa9, 0x0, 0x6c, 0xca, 0x88, 0x3c,
    0x0, 0x39, 0xb6, 0x70, 0x0, 0x2b, 0x67, 0x0,
    0x2, 0xc5, 0x80, 0x0, 0x2c, 0x1d, 0x10, 0x2,
    0xc0, 0x3b, 0xcc, 0xda,

    /* U+0062 "b" */
    0xc2, 0x0, 0x0, 0xc, 0x20, 0x0, 0x0, 0xc2,
    0x0, 0x0, 0xc, 0xbc, 0xcc, 0x30, 0xc4, 0x0,
    0x2e, 0xc, 0x20, 0x0, 0xc2, 0xc2, 0x0, 0xb,
    0x2c, 0x20, 0x0, 0xb2, 0xc2, 0x0, 0xc, 0x2c,
    0x20, 0x3, 0xd0, 0xad, 0xcc, 0xa2, 0x0,

    /* U+0063 "c" */
    0x4, 0xcd, 0xc6, 0x1d, 0x10, 0x0, 0x58, 0x0,
    0x0, 0x67, 0x0, 0x0, 0x67, 0x0, 0x0, 0x68,
    0x0, 0x0, 0x2d, 0x10, 0x0, 0x5, 0xcc, 0xc7
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 117, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 123, .box_w = 7, .box_h = 11, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 98, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 97, .range_length = 3, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Map glyph_ids to kern left classes*/
static const uint8_t kern_left_class_mapping[] =
{
    0, 1, 2, 0
};

/*Map glyph_ids to kern right classes*/
static const uint8_t kern_right_class_mapping[] =
{
    0, 0, 1, 0
};

/*Kern values between classes*/
static const int8_t kern_class_values[] =
{
    -12, -18
};


/*Collect the kern class' data in one place*/
static const lv_font_fmt_txt_kern_classes_t kern_classes =
{
    .class_pair_values   = kern_class_values,
    .left_class_mapping  = kern_left_class_mapping,
    .right_class_mapping = kern_right_class_mapping,
    .left_class_cnt      = 2,
    .right_class_cnt     = 1,
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_classes,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 4,
    .kern_classes = 1,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t lv_customer_font_Adventpro_regular_16 = {
#else
lv_font_t lv_customer_font_Adventpro_regular_16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 16,          /*The maximum line height required by the font  default: (f.src.ascent - f.src.descent)*/
    .base_line = 2.4,                          /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LV_CUSTOMER_FONT_ADVENTPRO_REGULAR_16*/

