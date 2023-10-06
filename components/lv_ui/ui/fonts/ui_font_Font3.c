/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: --bpp 1 --size 16 --font C:\Users\15341\Documents\SquareLine\assets\Antonio-Regular.ttf -o C:\Users\15341\Documents\SquareLine\assets\ui_font_Font3.c --format lvgl -r 0x20-0x7f --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_FONT3
#define UI_FONT_FONT3 1
#endif

#if UI_FONT_FONT3

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xff, 0xec,

    /* U+0022 "\"" */
    0xbb, 0xba, 0xa0,

    /* U+0023 "#" */
    0x12, 0x6c, 0xd9, 0x22, 0x5f, 0xdb, 0x36, 0xfe,
    0x91, 0x26, 0xc9, 0x92, 0x0,

    /* U+0024 "$" */
    0x21, 0x1d, 0xbd, 0xef, 0x8e, 0x31, 0xf7, 0xbd,
    0xb8, 0x84,

    /* U+0025 "%" */
    0x70, 0x41, 0xb1, 0x83, 0x62, 0x6, 0xcc, 0xd,
    0x98, 0x1b, 0x27, 0xb6, 0xd9, 0xed, 0xb3, 0x72,
    0x66, 0xc, 0xcc, 0x19, 0x98, 0x23, 0x30, 0xc6,
    0x61, 0x87, 0x80,

    /* U+0026 "&" */
    0x38, 0x64, 0x64, 0x64, 0x3c, 0x38, 0x18, 0x38,
    0x7a, 0xca, 0xcc, 0xc4, 0xce, 0x7a,

    /* U+0027 "'" */
    0xf8,

    /* U+0028 "(" */
    0x7b, 0x6d, 0xb6, 0xdb, 0x6d, 0x98,

    /* U+0029 ")" */
    0xcd, 0xb6, 0xdb, 0x6d, 0xb6, 0xf0,

    /* U+002A "*" */
    0x22, 0xa7, 0x9e, 0xa8, 0x80,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0xf5, 0x80,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0xc0,

    /* U+002F "/" */
    0x10, 0x8c, 0x62, 0x10, 0x8c, 0x42, 0x11, 0x88,
    0x40,

    /* U+0030 "0" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3, 0xcd, 0xe0,

    /* U+0031 "1" */
    0x37, 0xf3, 0x33, 0x33, 0x33, 0x33, 0x33,

    /* U+0032 "2" */
    0x76, 0xf7, 0xbd, 0x8c, 0xe6, 0x73, 0x19, 0x8c,
    0x7c,

    /* U+0033 "3" */
    0x7b, 0x3c, 0xf3, 0xc, 0x33, 0x82, 0xc, 0x3c,
    0xf3, 0xcd, 0xe0,

    /* U+0034 "4" */
    0x18, 0xe3, 0x8e, 0x39, 0x65, 0x96, 0xda, 0x6f,
    0xc6, 0x18, 0x60,

    /* U+0035 "5" */
    0xfe, 0x31, 0x8f, 0x6f, 0x63, 0x18, 0xf7, 0xbd,
    0xb8,

    /* U+0036 "6" */
    0x73, 0x6d, 0xb6, 0xc3, 0xec, 0xf3, 0xcf, 0x3c,
    0xf3, 0xcd, 0xe0,

    /* U+0037 "7" */
    0xf8, 0x46, 0x21, 0x18, 0x84, 0x23, 0x18, 0xc6,
    0x30,

    /* U+0038 "8" */
    0x76, 0xf7, 0xbd, 0xed, 0xca, 0xde, 0xf7, 0xbd,
    0xb8,

    /* U+0039 "9" */
    0x76, 0xf7, 0xbd, 0xef, 0x6f, 0x1e, 0xf7, 0xbd,
    0xb8,

    /* U+003A ":" */
    0xf0, 0xf,

    /* U+003B ";" */
    0xf0, 0x3d, 0x60,

    /* U+003C "<" */
    0x8, 0xdd, 0x8c, 0x30, 0xe1,

    /* U+003D "=" */
    0xf8, 0x1, 0xf0,

    /* U+003E ">" */
    0x6, 0x18, 0x71, 0xbb, 0x10,

    /* U+003F "?" */
    0x76, 0xf7, 0xbd, 0x8c, 0xee, 0xc6, 0x0, 0xc,
    0x60,

    /* U+0040 "@" */
    0x1e, 0x31, 0x90, 0x50, 0x18, 0xec, 0x96, 0x4b,
    0x25, 0x92, 0xc9, 0x63, 0x48, 0x6, 0x1, 0xe0,

    /* U+0041 "A" */
    0x31, 0xc7, 0x14, 0x51, 0x45, 0xb6, 0xdb, 0x2f,
    0xa2, 0x8e, 0x30,

    /* U+0042 "B" */
    0xf6, 0xf7, 0xbd, 0xef, 0xdb, 0xde, 0xf7, 0xbd,
    0xf8,

    /* U+0043 "C" */
    0x7b, 0x3c, 0xf3, 0xcf, 0xc, 0x30, 0xcf, 0x3c,
    0xf3, 0xcd, 0xe0,

    /* U+0044 "D" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3, 0xcf, 0xe0,

    /* U+0045 "E" */
    0xf6, 0x31, 0x8c, 0x63, 0xd8, 0xc6, 0x31, 0x8c,
    0x7c,

    /* U+0046 "F" */
    0xfe, 0x31, 0x8c, 0x63, 0xd8, 0xc6, 0x31, 0x8c,
    0x60,

    /* U+0047 "G" */
    0x7b, 0x3c, 0xf3, 0xcf, 0xc, 0x37, 0xcf, 0x3c,
    0xf3, 0xcd, 0xd0,

    /* U+0048 "H" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3f, 0xf3, 0xcf, 0x3c,
    0xf3, 0xcf, 0x30,

    /* U+0049 "I" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+004A "J" */
    0x18, 0xc6, 0x31, 0x8c, 0x63, 0x1e, 0xf7, 0xbd,
    0xb8,

    /* U+004B "K" */
    0xcf, 0x3d, 0xb6, 0xd3, 0xcf, 0x3c, 0xf3, 0x4d,
    0xb2, 0xcf, 0x30,

    /* U+004C "L" */
    0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8c,
    0x7c,

    /* U+004D "M" */
    0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xe7, 0xdb,
    0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,

    /* U+004E "N" */
    0xcf, 0x3c, 0xfb, 0xef, 0xbe, 0xf7, 0xdf, 0x7d,
    0xf3, 0xcf, 0x30,

    /* U+004F "O" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3, 0xcd, 0xe0,

    /* U+0050 "P" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xfe, 0xc3, 0xc,
    0x30, 0xc3, 0x0,

    /* U+0051 "Q" */
    0x7b, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3, 0xcd, 0xe1, 0x82,

    /* U+0052 "R" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3f, 0xb3, 0xcf, 0x3c,
    0xf3, 0xcf, 0x30,

    /* U+0053 "S" */
    0x76, 0xf7, 0xbd, 0xf1, 0xc6, 0x3e, 0xf7, 0xbd,
    0xb8,

    /* U+0054 "T" */
    0xfb, 0x18, 0xc6, 0x31, 0x8c, 0x63, 0x18, 0xc6,
    0x30,

    /* U+0055 "U" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3, 0xcd, 0xe0,

    /* U+0056 "V" */
    0x46, 0x8d, 0x13, 0x26, 0x4d, 0x8b, 0x16, 0x28,
    0x50, 0xe1, 0xc1, 0x83, 0x0,

    /* U+0057 "W" */
    0x44, 0x53, 0x34, 0xcd, 0x3b, 0x4a, 0xda, 0xa6,
    0xa9, 0xaa, 0x3a, 0x8e, 0xa3, 0x38, 0xc6, 0x31,
    0x8c, 0x60,

    /* U+0058 "X" */
    0x4d, 0x36, 0x8a, 0x38, 0xc3, 0xc, 0x30, 0xe6,
    0x9a, 0x4d, 0x30,

    /* U+0059 "Y" */
    0x8f, 0x3c, 0xd2, 0x79, 0xe3, 0xc, 0x30, 0xc3,
    0xc, 0x30, 0xc0,

    /* U+005A "Z" */
    0xf3, 0x32, 0x26, 0x66, 0x44, 0xcc, 0x8f,

    /* U+005B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcf,

    /* U+005C "\\" */
    0x86, 0x30, 0x84, 0x31, 0x84, 0x21, 0xc, 0x21,
    0x8,

    /* U+005D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,

    /* U+005E "^" */
    0x30, 0xc7, 0x9e, 0x49, 0x2c, 0xf3,

    /* U+005F "_" */
    0xf8,

    /* U+0060 "`" */
    0x18, 0x80,

    /* U+0061 "a" */
    0x76, 0xf7, 0xb3, 0xbf, 0x7b, 0xde, 0xf6, 0xf0,

    /* U+0062 "b" */
    0xc6, 0x3d, 0xbd, 0xef, 0x7b, 0xde, 0xf7, 0xbd,
    0xf8,

    /* U+0063 "c" */
    0x76, 0xf7, 0xbc, 0x63, 0x1b, 0xde, 0xf6, 0xe0,

    /* U+0064 "d" */
    0x18, 0xdf, 0xbd, 0xef, 0x7b, 0xde, 0xf7, 0xbd,
    0xbc,

    /* U+0065 "e" */
    0x76, 0xf7, 0xbd, 0xff, 0x18, 0xde, 0xf6, 0xe0,

    /* U+0066 "f" */
    0x36, 0x6f, 0x66, 0x66, 0x66, 0x66, 0x66,

    /* U+0067 "g" */
    0x7e, 0xf7, 0xbd, 0xef, 0x7b, 0xde, 0xde, 0x31,
    0xf8,

    /* U+0068 "h" */
    0xc3, 0xf, 0xb3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3, 0xcf, 0x30,

    /* U+0069 "i" */
    0xcf, 0xff, 0xff, 0xf0,

    /* U+006A "j" */
    0x61, 0xb6, 0xdb, 0x6d, 0xb6, 0xdf,

    /* U+006B "k" */
    0xc3, 0xc, 0xf2, 0xdb, 0x4f, 0x3c, 0xf3, 0x4d,
    0xb6, 0xcb, 0x30,

    /* U+006C "l" */
    0xff, 0xff, 0xff, 0xf0,

    /* U+006D "m" */
    0xfe, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb, 0xdb,
    0xdb, 0xdb, 0xdb, 0xdb,

    /* U+006E "n" */
    0xfb, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xf3,

    /* U+006F "o" */
    0x76, 0xf7, 0xbd, 0xef, 0x7b, 0xde, 0xf6, 0xe0,

    /* U+0070 "p" */
    0xf6, 0xf7, 0xbd, 0xef, 0x7b, 0xde, 0xf7, 0xec,
    0x60,

    /* U+0071 "q" */
    0x7e, 0xf7, 0xbd, 0xef, 0x7b, 0xde, 0xf6, 0xf1,
    0x8c,

    /* U+0072 "r" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,

    /* U+0073 "s" */
    0x76, 0xf7, 0xbe, 0x38, 0xc7, 0xde, 0xf6, 0xe0,

    /* U+0074 "t" */
    0x66, 0xf6, 0x66, 0x66, 0x66, 0x66, 0x67,

    /* U+0075 "u" */
    0xcf, 0x3c, 0xf3, 0xcf, 0x3c, 0xf3, 0xcf, 0x3c,
    0xdf,

    /* U+0076 "v" */
    0xc9, 0x24, 0x92, 0x49, 0xe7, 0x9e, 0x30, 0xc3,
    0xc,

    /* U+0077 "w" */
    0xc9, 0xa4, 0x97, 0x4a, 0xa5, 0x52, 0xa9, 0x54,
    0xaa, 0x75, 0x3b, 0x88, 0x84, 0x40,

    /* U+0078 "x" */
    0xc9, 0x27, 0x9c, 0x30, 0xc3, 0xc, 0x71, 0x64,
    0xb2,

    /* U+0079 "y" */
    0x9c, 0xe7, 0xbd, 0x69, 0x4a, 0x53, 0x98, 0xc2,
    0x70,

    /* U+007A "z" */
    0xf3, 0x32, 0x26, 0x64, 0x4c, 0xcf,

    /* U+007B "{" */
    0x36, 0x66, 0x66, 0xec, 0x66, 0x66, 0x66, 0x30,

    /* U+007C "|" */
    0xff, 0xff, 0xff, 0xff,

    /* U+007D "}" */
    0xc6, 0x66, 0x66, 0x73, 0x66, 0x66, 0x66, 0xc0,

    /* U+007E "~" */
    0xe7, 0x38
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 63, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 66, .box_w = 1, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 3, .adv_w = 118, .box_w = 4, .box_h = 5, .ofs_x = 2, .ofs_y = 9},
    {.bitmap_index = 6, .adv_w = 161, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 19, .adv_w = 110, .box_w = 5, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 272, .box_w = 15, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 56, .adv_w = 123, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 52, .box_w = 1, .box_h = 5, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 71, .adv_w = 71, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 77, .adv_w = 71, .box_w = 3, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 83, .adv_w = 120, .box_w = 6, .box_h = 6, .ofs_x = 1, .ofs_y = 8},
    {.bitmap_index = 88, .adv_w = 101, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 92, .adv_w = 58, .box_w = 2, .box_h = 5, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 94, .adv_w = 87, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 95, .adv_w = 67, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 98, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 114, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 81, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 112, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 114, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 112, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 112, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 112, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 112, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 112, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 112, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 69, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 203, .adv_w = 70, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 206, .adv_w = 91, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 211, .adv_w = 90, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 214, .adv_w = 91, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 219, .adv_w = 100, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 176, .box_w = 9, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 117, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 119, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 115, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 275, .adv_w = 119, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 96, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 93, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 118, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 123, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 66, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 107, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 339, .adv_w = 112, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 350, .adv_w = 89, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 162, .box_w = 8, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 373, .adv_w = 127, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 118, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 111, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 406, .adv_w = 118, .box_w = 6, .box_h = 16, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 418, .adv_w = 119, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 429, .adv_w = 109, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 80, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 120, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 458, .adv_w = 115, .box_w = 7, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 471, .adv_w = 170, .box_w = 10, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 489, .adv_w = 102, .box_w = 6, .box_h = 14, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 500, .adv_w = 105, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 511, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 525, .adv_w = 109, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 534, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 541, .adv_w = 129, .box_w = 6, .box_h = 8, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 547, .adv_w = 94, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 548, .adv_w = 81, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 550, .adv_w = 116, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 558, .adv_w = 117, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 567, .adv_w = 110, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 117, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 584, .adv_w = 112, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 78, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 599, .adv_w = 116, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 608, .adv_w = 121, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 619, .adv_w = 63, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 623, .adv_w = 67, .box_w = 3, .box_h = 16, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 629, .adv_w = 108, .box_w = 6, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 640, .adv_w = 63, .box_w = 2, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 644, .adv_w = 179, .box_w = 8, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 656, .adv_w = 121, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 665, .adv_w = 114, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 673, .adv_w = 117, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 682, .adv_w = 116, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 691, .adv_w = 81, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 697, .adv_w = 101, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 705, .adv_w = 77, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 712, .adv_w = 121, .box_w = 6, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 721, .adv_w = 94, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 730, .adv_w = 145, .box_w = 9, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 744, .adv_w = 93, .box_w = 6, .box_h = 12, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 753, .adv_w = 99, .box_w = 5, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 762, .adv_w = 85, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 768, .adv_w = 100, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 776, .adv_w = 67, .box_w = 2, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 780, .adv_w = 100, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 788, .adv_w = 140, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 7}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/



/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    }
};

/*-----------------
 *    KERNING
 *----------------*/


/*Pair left and right glyphs for kerning*/
static const uint8_t kern_pair_glyph_ids[] =
{
    34, 36,
    34, 40,
    34, 48,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 66,
    34, 86,
    34, 87,
    34, 88,
    34, 90,
    35, 13,
    35, 15,
    36, 34,
    37, 13,
    37, 15,
    37, 34,
    37, 55,
    37, 56,
    37, 58,
    39, 13,
    39, 15,
    39, 34,
    40, 55,
    43, 13,
    43, 15,
    44, 36,
    44, 40,
    44, 48,
    44, 52,
    44, 66,
    44, 70,
    44, 80,
    45, 36,
    45, 40,
    45, 48,
    45, 50,
    45, 52,
    45, 53,
    45, 55,
    45, 56,
    45, 58,
    45, 88,
    45, 90,
    48, 13,
    48, 15,
    48, 34,
    48, 57,
    49, 13,
    49, 15,
    49, 34,
    49, 43,
    51, 55,
    51, 56,
    51, 58,
    55, 13,
    55, 15,
    55, 34,
    55, 36,
    55, 40,
    55, 43,
    55, 48,
    55, 66,
    55, 70,
    55, 72,
    55, 80,
    56, 15,
    56, 34,
    56, 48,
    56, 66,
    56, 68,
    56, 70,
    56, 72,
    58, 13,
    58, 15,
    58, 34,
    58, 48,
    58, 66,
    58, 84,
    67, 13,
    67, 15,
    68, 15,
    76, 70,
    76, 80,
    80, 66,
    80, 87,
    80, 88,
    80, 89,
    83, 13,
    83, 15,
    83, 66,
    83, 72,
    83, 80,
    87, 13,
    87, 15,
    88, 13,
    88, 15,
    88, 66,
    90, 13,
    90, 15,
    90, 80
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -3, -3, -3, -3, -2, -5, -6, -5,
    0, -1, -2, -1, -3, -8, -11, -1,
    -8, -9, -1, -1, -1, -1, -13, -15,
    -4, -1, -3, -8, 0, -1, -1, -1,
    -1, 0, 0, -2, -2, -3, -2, -2,
    -2, -4, -4, -5, 0, -1, -2, -4,
    -1, -1, -29, -32, -4, -5, -1, -1,
    0, -10, -8, -5, 0, 0, -5, 0,
    -1, -1, -1, -1, -5, -4, -1, -1,
    -1, -1, 0, -1, -1, -4, -1, -2,
    -1, -4, -5, -5, 0, 0, -1, 0,
    0, 0, -1, -10, -1, -1, -1, -2,
    -6, -2, -9, -1, -6, -11, -1
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 103,
    .glyph_ids_size = 0
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
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
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
const lv_font_t ui_font_Font3 = {
#else
lv_font_t ui_font_Font3 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_FONT3*/

