/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef LIBERATION8N
#define LIBERATION8N 1
#endif

#if LIBERATION8N

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xf8,

    /* U+0022 "\"" */
    0xf0,

    /* U+0023 "#" */
    0x4f, 0xae, 0x80,

    /* U+0024 "$" */
    0xf9, 0xbe, 0x80,

    /* U+0025 "%" */
    0xf2, 0xe5, 0x4d, 0x58,

    /* U+0026 "&" */
    0x66, 0x5b, 0x70,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x6a, 0xa4,

    /* U+0029 ")" */
    0xa5, 0x68,

    /* U+002A "*" */
    0x48, 0x0,

    /* U+002B "+" */
    0x4b, 0xa0,

    /* U+002C "," */
    0x0,

    /* U+002D "-" */
    0xc0,

    /* U+002E "." */
    0x0,

    /* U+002F "/" */
    0x6a, 0x80,

    /* U+0030 "0" */
    0x69, 0x99, 0x60,

    /* U+0031 "1" */
    0x49, 0x2e,

    /* U+0032 "2" */
    0xe5, 0x4e,

    /* U+0033 "3" */
    0xc5, 0x1e,

    /* U+0034 "4" */
    0x2e, 0xf2,

    /* U+0035 "5" */
    0xfc, 0x9e,

    /* U+0036 "6" */
    0x7a, 0xd6,

    /* U+0037 "7" */
    0xe5, 0x24,

    /* U+0038 "8" */
    0xf5, 0x5e,

    /* U+0039 "9" */
    0xf5, 0x9c,

    /* U+003A ":" */
    0x0,

    /* U+003B ";" */
    0x0,

    /* U+003C "<" */
    0x71, 0x80,

    /* U+003D "=" */
    0xf0, 0xf0,

    /* U+003E ">" */
    0xc7, 0x0,

    /* U+003F "?" */
    0xe5, 0x24,

    /* U+0040 "@" */
    0x3b, 0xdd, 0x75, 0xa9, 0xc0,

    /* U+0041 "A" */
    0x26, 0x67, 0x90,

    /* U+0042 "B" */
    0xea, 0xe9, 0xe0,

    /* U+0043 "C" */
    0x78, 0x88, 0x70,

    /* U+0044 "D" */
    0xe9, 0x99, 0xe0,

    /* U+0045 "E" */
    0xf8, 0xe8, 0xf0,

    /* U+0046 "F" */
    0xf3, 0xc8,

    /* U+0047 "G" */
    0x74, 0x27, 0x17, 0x0,

    /* U+0048 "H" */
    0x99, 0xf9, 0x90,

    /* U+0049 "I" */
    0xf8,

    /* U+004A "J" */
    0x64, 0x9e,

    /* U+004B "K" */
    0xac, 0xca, 0x90,

    /* U+004C "L" */
    0x92, 0x4e,

    /* U+004D "M" */
    0x8e, 0xf7, 0xda, 0x80,

    /* U+004E "N" */
    0x9d, 0xdb, 0x90,

    /* U+004F "O" */
    0x74, 0x63, 0x17, 0x0,

    /* U+0050 "P" */
    0xe9, 0xe8, 0x80,

    /* U+0051 "Q" */
    0x74, 0x63, 0x17, 0x10, 0x40,

    /* U+0052 "R" */
    0xe9, 0xea, 0x90,

    /* U+0053 "S" */
    0xe8, 0x62, 0xe0,

    /* U+0054 "T" */
    0xe9, 0x24,

    /* U+0055 "U" */
    0x99, 0x99, 0x60,

    /* U+0056 "V" */
    0x99, 0x66, 0x20,

    /* U+0057 "W" */
    0x96, 0xdb, 0x56, 0x48,

    /* U+0058 "X" */
    0x96, 0x26, 0x90,

    /* U+0059 "Y" */
    0x92, 0x88, 0x42, 0x0,

    /* U+005A "Z" */
    0xf2, 0x48, 0xf0,

    /* U+005B "[" */
    0xaa, 0xa8,

    /* U+005C "\\" */
    0xaa, 0x40,

    /* U+005D "]" */
    0x55, 0x54,

    /* U+005E "^" */
    0x5a, 0x80,

    /* U+005F "_" */
    0xf0,

    /* U+0060 "`" */
    0x80,

    /* U+0061 "a" */
    0xe6, 0xaf,

    /* U+0062 "b" */
    0x9e, 0xde,

    /* U+0063 "c" */
    0x72, 0x30,

    /* U+0064 "d" */
    0x3e, 0xde,

    /* U+0065 "e" */
    0xfe, 0x70,

    /* U+0066 "f" */
    0xf8,

    /* U+0067 "g" */
    0xf6, 0xf2, 0x80,

    /* U+0068 "h" */
    0x9e, 0xda,

    /* U+0069 "i" */
    0xf8,

    /* U+006A "j" */
    0xfe,

    /* U+006B "k" */
    0x97, 0x6a,

    /* U+006C "l" */
    0xf8,

    /* U+006D "m" */
    0xfd, 0x6b, 0x50,

    /* U+006E "n" */
    0xf6, 0xd0,

    /* U+006F "o" */
    0xd6, 0xe0,

    /* U+0070 "p" */
    0xf6, 0xf9, 0x0,

    /* U+0071 "q" */
    0xf6, 0xf2, 0x40,

    /* U+0072 "r" */
    0xea,

    /* U+0073 "s" */
    0xd1, 0xf0,

    /* U+0074 "t" */
    0xaa, 0xc0,

    /* U+0075 "u" */
    0xb6, 0xf0,

    /* U+0076 "v" */
    0xb7, 0x20,

    /* U+0077 "w" */
    0xaf, 0x9c, 0xa0,

    /* U+0078 "x" */
    0xa9, 0x50,

    /* U+0079 "y" */
    0xb6, 0xa5, 0x0,

    /* U+007A "z" */
    0xea, 0x70,

    /* U+007B "{" */
    0xaa, 0xa8,

    /* U+007C "|" */
    0xfe,

    /* U+007D "}" */
    0x55, 0x54,

    /* U+007E "~" */
    0xf0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 29, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 29, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 37, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 3, .adv_w = 58, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 58, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 9, .adv_w = 93, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 13, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 16, .adv_w = 20, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 17, .adv_w = 35, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 19, .adv_w = 35, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 21, .adv_w = 41, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 23, .adv_w = 61, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 25, .adv_w = 29, .box_w = 1, .box_h = 2, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 26, .adv_w = 35, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 27, .adv_w = 29, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 29, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 58, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 43, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 47, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 51, .adv_w = 29, .box_w = 1, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 29, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 53, .adv_w = 61, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 55, .adv_w = 61, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 57, .adv_w = 61, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 59, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 107, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 66, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 81, .adv_w = 64, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 82, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 29, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 53, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 96, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 87, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 82, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 82, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 117, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 123, .adv_w = 64, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 76, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 99, .box_w = 6, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 70, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 64, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 145, .adv_w = 29, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 147, .adv_w = 29, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 149, .adv_w = 29, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 151, .adv_w = 49, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 153, .adv_w = 58, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 154, .adv_w = 35, .box_w = 2, .box_h = 1, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 155, .adv_w = 58, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 157, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 53, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 161, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 165, .adv_w = 29, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 58, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 169, .adv_w = 58, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 171, .adv_w = 23, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 23, .box_w = 1, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 173, .adv_w = 53, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 23, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 176, .adv_w = 87, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 179, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 58, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 186, .adv_w = 58, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 189, .adv_w = 35, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 53, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 29, .box_w = 2, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 58, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 53, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 76, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 53, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 53, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 206, .adv_w = 53, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 208, .adv_w = 35, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 210, .adv_w = 27, .box_w = 1, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 211, .adv_w = 35, .box_w = 2, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 213, .adv_w = 61, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 2}
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
    1, 34,
    1, 53,
    1, 58,
    18, 18,
    34, 1,
    34, 53,
    34, 55,
    34, 56,
    34, 58,
    34, 87,
    34, 88,
    34, 90,
    39, 13,
    39, 15,
    39, 34,
    45, 1,
    45, 53,
    45, 55,
    45, 56,
    45, 58,
    45, 90,
    49, 1,
    49, 13,
    49, 15,
    49, 34,
    51, 53,
    51, 55,
    51, 56,
    51, 58,
    53, 1,
    53, 13,
    53, 14,
    53, 15,
    53, 27,
    53, 28,
    53, 34,
    53, 48,
    53, 66,
    53, 68,
    53, 70,
    53, 74,
    53, 80,
    53, 83,
    53, 84,
    53, 86,
    53, 88,
    53, 90,
    55, 13,
    55, 14,
    55, 15,
    55, 27,
    55, 28,
    55, 34,
    55, 66,
    55, 70,
    55, 74,
    55, 80,
    55, 83,
    55, 86,
    55, 90,
    56, 13,
    56, 14,
    56, 15,
    56, 27,
    56, 28,
    56, 34,
    56, 66,
    56, 70,
    56, 80,
    56, 83,
    56, 86,
    56, 90,
    58, 1,
    58, 13,
    58, 14,
    58, 15,
    58, 27,
    58, 28,
    58, 34,
    58, 66,
    58, 70,
    58, 74,
    58, 80,
    58, 81,
    58, 82,
    58, 86,
    58, 87,
    71, 71,
    83, 13,
    83, 15,
    87, 13,
    87, 15,
    88, 13,
    88, 15,
    90, 13,
    90, 15
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -6, -2, -2, -8, -6, -8, -8, -4,
    -8, -2, -2, -2, -12, -12, -6, -4,
    -8, -8, -8, -8, -4, -2, -13, -13,
    -8, -2, -2, -2, -2, -2, -12, -6,
    -12, -12, -12, -8, -2, -12, -12, -12,
    -2, -12, -4, -9, -4, -6, -6, -10,
    -6, -10, -4, -4, -8, -8, -6, -2,
    -6, -4, -4, -4, -6, -2, -6, -2,
    -2, -4, -4, -2, -2, -2, -2, -1,
    -2, -13, -10, -13, -6, -7, -8, -8,
    -10, -4, -10, -8, -10, -6, -6, -2,
    -6, -6, -8, -8, -6, -6, -8, -8
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 96,
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
const lv_font_t liberation8n = {
#else
lv_font_t liberation8n = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 7,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = 0,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LIBERATION8N*/

