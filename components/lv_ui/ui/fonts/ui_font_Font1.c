/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: --bpp 1 --size 8 --font C:\Users\15341\Documents\SquareLine\assets\Antonio-Regular.ttf -o C:\Users\15341\Documents\SquareLine\assets\ui_font_Font1.c --format lvgl -r 0x20-0x7f --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_FONT1
#define UI_FONT_FONT1 1
#endif

#if UI_FONT_FONT1

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfa,

    /* U+0022 "\"" */
    0xd0,

    /* U+0023 "#" */
    0x77, 0xdf, 0xb0,

    /* U+0024 "$" */
    0x56, 0xe7, 0x6a,

    /* U+0025 "%" */
    0xe5, 0x52, 0xbd, 0xbf, 0x62, 0xc9, 0x80,

    /* U+0026 "&" */
    0xea, 0xa4, 0xda, 0xe0,

    /* U+0027 "'" */
    0x80,

    /* U+0028 "(" */
    0xea, 0xab,

    /* U+0029 ")" */
    0xd5, 0x57,

    /* U+002A "*" */
    0x4d, 0x80,

    /* U+002B "+" */
    0xe8,

    /* U+002C "," */
    0xe0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x29, 0x25, 0x20,

    /* U+0030 "0" */
    0xf6, 0xdb, 0x78,

    /* U+0031 "1" */
    0x55, 0x54,

    /* U+0032 "2" */
    0xf6, 0xa5, 0x38,

    /* U+0033 "3" */
    0xf4, 0xb3, 0x78,

    /* U+0034 "4" */
    0x26, 0x6a, 0xaf, 0x20,

    /* U+0035 "5" */
    0xf3, 0xd3, 0x78,

    /* U+0036 "6" */
    0xf7, 0xdb, 0x78,

    /* U+0037 "7" */
    0xd6, 0xa8,

    /* U+0038 "8" */
    0xf6, 0xab, 0x78,

    /* U+0039 "9" */
    0xf6, 0xf3, 0x78,

    /* U+003A ":" */
    0x90,

    /* U+003B ";" */
    0x9c,

    /* U+003C "<" */
    0x3a, 0x30,

    /* U+003D "=" */
    0xfc,

    /* U+003E ">" */
    0x89, 0x40,

    /* U+003F "?" */
    0xfd, 0x88,

    /* U+0040 "@" */
    0x76, 0x7f, 0xbd, 0xfd, 0x80,

    /* U+0041 "A" */
    0x4d, 0xbb, 0xe8,

    /* U+0042 "B" */
    0xf6, 0xeb, 0x78,

    /* U+0043 "C" */
    0xf6, 0xcb, 0x78,

    /* U+0044 "D" */
    0xf6, 0xdb, 0x78,

    /* U+0045 "E" */
    0xeb, 0xac,

    /* U+0046 "F" */
    0xeb, 0xa8,

    /* U+0047 "G" */
    0xf6, 0x5b, 0x78,

    /* U+0048 "H" */
    0xb6, 0xfb, 0x68,

    /* U+0049 "I" */
    0xfe,

    /* U+004A "J" */
    0x24, 0x9b, 0x78,

    /* U+004B "K" */
    0xbb, 0x6d, 0x68,

    /* U+004C "L" */
    0xaa, 0xac,

    /* U+004D "M" */
    0x99, 0xff, 0xfb, 0xd0,

    /* U+004E "N" */
    0xb6, 0xfb, 0x68,

    /* U+004F "O" */
    0xf6, 0xdb, 0x78,

    /* U+0050 "P" */
    0xf6, 0xf9, 0x20,

    /* U+0051 "Q" */
    0xf6, 0xdb, 0x79,

    /* U+0052 "R" */
    0xf6, 0xeb, 0x68,

    /* U+0053 "S" */
    0xf6, 0xab, 0x78,

    /* U+0054 "T" */
    0xe9, 0x24, 0x90,

    /* U+0055 "U" */
    0xb6, 0xdb, 0x78,

    /* U+0056 "V" */
    0xb6, 0xb6, 0xd0,

    /* U+0057 "W" */
    0xad, 0x6b, 0xbd, 0xa9, 0x40,

    /* U+0058 "X" */
    0xb5, 0x25, 0x68,

    /* U+0059 "Y" */
    0xb7, 0x24, 0x90,

    /* U+005A "Z" */
    0xe9, 0x29, 0x30,

    /* U+005B "[" */
    0xea, 0xac,

    /* U+005C "\\" */
    0x99, 0x24, 0x88,

    /* U+005D "]" */
    0xd5, 0x5c,

    /* U+005E "^" */
    0xff,

    /* U+005F "_" */
    0xe0,

    /* U+0060 "`" */
    0x80,

    /* U+0061 "a" */
    0xf5, 0xdb, 0xc0,

    /* U+0062 "b" */
    0x9e, 0xdb, 0x78,

    /* U+0063 "c" */
    0xf6, 0x4b, 0xc0,

    /* U+0064 "d" */
    0x3e, 0xdb, 0x78,

    /* U+0065 "e" */
    0xf7, 0xcb, 0xc0,

    /* U+0066 "f" */
    0x7d, 0x24, 0x90,

    /* U+0067 "g" */
    0xf6, 0xdb, 0xf8,

    /* U+0068 "h" */
    0x9e, 0xdb, 0x68,

    /* U+0069 "i" */
    0xfe,

    /* U+006A "j" */
    0xff,

    /* U+006B "k" */
    0x97, 0x6d, 0xa8,

    /* U+006C "l" */
    0xfe,

    /* U+006D "m" */
    0xfd, 0x6b, 0x5a, 0xd4,

    /* U+006E "n" */
    0xf6, 0xdb, 0x40,

    /* U+006F "o" */
    0xf6, 0xdb, 0xc0,

    /* U+0070 "p" */
    0xf6, 0xdb, 0xe0,

    /* U+0071 "q" */
    0xf6, 0xdb, 0xc8,

    /* U+0072 "r" */
    0xea, 0xa0,

    /* U+0073 "s" */
    0xf6, 0x3b, 0xc0,

    /* U+0074 "t" */
    0x5d, 0x24, 0x98,

    /* U+0075 "u" */
    0xb6, 0xdb, 0xc0,

    /* U+0076 "v" */
    0xb7, 0x6c, 0x80,

    /* U+0077 "w" */
    0xbb, 0xb5, 0x55,

    /* U+0078 "x" */
    0xb9, 0x2d, 0x40,

    /* U+0079 "y" */
    0xb6, 0xe4, 0xb0,

    /* U+007A "z" */
    0xd6, 0xb0,

    /* U+007B "{" */
    0x69, 0x28, 0x93,

    /* U+007C "|" */
    0xff,

    /* U+007D "}" */
    0xc9, 0x22, 0x96,

    /* U+007E "~" */
    0x70
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 31, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 33, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 59, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 3, .adv_w = 81, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 55, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 9, .adv_w = 136, .box_w = 7, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 61, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 26, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 21, .adv_w = 35, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 35, .box_w = 2, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 25, .adv_w = 60, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 27, .adv_w = 51, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 28, .adv_w = 29, .box_w = 1, .box_h = 3, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 29, .adv_w = 44, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 30, .adv_w = 33, .box_w = 1, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 31, .adv_w = 49, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 34, .adv_w = 57, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 40, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 56, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 42, .adv_w = 57, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 56, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 56, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 56, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 56, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 56, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 56, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 35, .box_w = 1, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 64, .adv_w = 35, .box_w = 1, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 65, .adv_w = 46, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 67, .adv_w = 45, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 68, .adv_w = 46, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 70, .adv_w = 50, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 77, .adv_w = 59, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 60, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 57, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 59, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 48, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 47, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 59, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 62, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 99, .adv_w = 33, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 54, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 56, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 106, .adv_w = 45, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 81, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 63, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 59, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 56, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 59, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 124, .adv_w = 60, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 55, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 40, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 60, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 58, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 85, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 51, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 52, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 48, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 48, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 54, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 48, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 64, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 161, .adv_w = 47, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 162, .adv_w = 41, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 163, .adv_w = 58, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 59, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 55, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 59, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 56, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 39, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 58, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 184, .adv_w = 61, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 31, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 33, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 189, .adv_w = 54, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 31, .box_w = 1, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 193, .adv_w = 90, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 61, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 200, .adv_w = 57, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 59, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 206, .adv_w = 58, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 209, .adv_w = 41, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 50, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 38, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 61, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 47, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 223, .adv_w = 73, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 46, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 229, .adv_w = 49, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 232, .adv_w = 43, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 50, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 237, .adv_w = 34, .box_w = 1, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 50, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 241, .adv_w = 70, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 3}
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
    -1, -1, -1, -2, -1, -3, -3, -3,
    0, 0, -1, -1, -1, -4, -5, -1,
    -4, -4, -1, -1, -1, -1, -6, -7,
    -2, 0, -1, -4, 0, 0, 0, 0,
    -1, 0, 0, -1, -1, -1, -1, -1,
    -1, -2, -2, -3, 0, -1, -1, -2,
    0, -1, -14, -16, -2, -3, 0, 0,
    0, -5, -4, -3, 0, 0, -2, 0,
    -1, -1, 0, -1, -2, -2, -1, 0,
    0, 0, 0, -1, 0, -2, 0, -1,
    -1, -2, -2, -2, 0, 0, 0, 0,
    0, 0, 0, -5, 0, -1, 0, -1,
    -3, -1, -4, 0, -3, -5, 0
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
const lv_font_t ui_font_Font1 = {
#else
lv_font_t ui_font_Font1 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_FONT1*/

