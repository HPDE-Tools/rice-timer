/*******************************************************************************
 * Size: 16 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef PIXERIF16
#define PIXERIF16 1
#endif

#if PIXERIF16

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 " " */
    0x0,

    /* U+0021 "!" */
    0xfd,

    /* U+0022 "\"" */
    0xb4,

    /* U+0023 "#" */
    0x14, 0x29, 0xf9, 0x42, 0x9f, 0x94, 0x28,

    /* U+0024 "$" */
    0x23, 0xeb, 0x47, 0x14, 0xb5, 0xf1, 0x0,

    /* U+0025 "%" */
    0x64, 0x94, 0x98, 0x68, 0x16, 0x19, 0x29, 0x26,

    /* U+0026 "&" */
    0x38, 0x48, 0x40, 0x67, 0x92, 0x8a, 0x84, 0x7b,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 "(" */
    0x2a, 0x49, 0x11,

    /* U+0029 ")" */
    0x88, 0x92, 0x54,

    /* U+002A "*" */
    0xab, 0x9d, 0x50,

    /* U+002B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+002C "," */
    0x58,

    /* U+002D "-" */
    0xf0,

    /* U+002E "." */
    0x80,

    /* U+002F "/" */
    0x11, 0x22, 0x44, 0x88,

    /* U+0030 "0" */
    0x31, 0x28, 0x61, 0x86, 0x14, 0x8c,

    /* U+0031 "1" */
    0x59, 0x24, 0x97,

    /* U+0032 "2" */
    0xf0, 0x42, 0x22, 0x22, 0x3f,

    /* U+0033 "3" */
    0xf4, 0x42, 0x60, 0x86, 0x3e,

    /* U+0034 "4" */
    0x21, 0x10, 0xa9, 0x7c, 0x42,

    /* U+0035 "5" */
    0xfc, 0x21, 0xe0, 0x86, 0x3e,

    /* U+0036 "6" */
    0x32, 0x21, 0xe8, 0xc6, 0x2e,

    /* U+0037 "7" */
    0xf8, 0x44, 0x22, 0x11, 0x8,

    /* U+0038 "8" */
    0x74, 0x62, 0xe8, 0xc6, 0x2e,

    /* U+0039 "9" */
    0x74, 0x63, 0x17, 0x84, 0x5c,

    /* U+003A ":" */
    0x88,

    /* U+003B ";" */
    0x40, 0x58,

    /* U+003C "<" */
    0xc, 0xcc, 0xc, 0xc,

    /* U+003D "=" */
    0xfc, 0xf, 0xc0,

    /* U+003E ">" */
    0xc0, 0xc0, 0xcc, 0xc0,

    /* U+003F "?" */
    0xf0, 0x42, 0x22, 0x20, 0x8,

    /* U+0040 "@" */
    0x1e, 0x8, 0x44, 0xea, 0x4a, 0xa2, 0xa9, 0x29,
    0xf1, 0x1, 0x3f, 0x80,

    /* U+0041 "A" */
    0x10, 0x20, 0xa1, 0x43, 0x88, 0x91, 0x77,

    /* U+0042 "B" */
    0xf1, 0x24, 0x9e, 0x45, 0x14, 0x7e,

    /* U+0043 "C" */
    0x3a, 0x61, 0x8, 0x41, 0x27,

    /* U+0044 "D" */
    0xf1, 0x24, 0x51, 0x45, 0x14, 0xbc,

    /* U+0045 "E" */
    0xfa, 0x50, 0xe4, 0x21, 0x3f,

    /* U+0046 "F" */
    0xfa, 0x50, 0xe4, 0x21, 0x1c,

    /* U+0047 "G" */
    0x3a, 0x61, 0x9, 0xc5, 0x27,

    /* U+0048 "H" */
    0xee, 0x89, 0x13, 0xe4, 0x48, 0x91, 0x77,

    /* U+0049 "I" */
    0xe9, 0x24, 0x97,

    /* U+004A "J" */
    0x71, 0x11, 0x11, 0x96,

    /* U+004B "K" */
    0xee, 0x89, 0x23, 0x85, 0x9, 0x11, 0x77,

    /* U+004C "L" */
    0xe2, 0x10, 0x84, 0x21, 0x3f,

    /* U+004D "M" */
    0xc3, 0x66, 0x66, 0x5a, 0x5a, 0x42, 0x42, 0xe7,

    /* U+004E "N" */
    0xce, 0xc9, 0x92, 0xa5, 0x49, 0x93, 0x72,

    /* U+004F "O" */
    0x31, 0x28, 0x61, 0x86, 0x14, 0x8c,

    /* U+0050 "P" */
    0xf2, 0x52, 0xe4, 0x21, 0x1c,

    /* U+0051 "Q" */
    0x30, 0x92, 0x14, 0x28, 0x52, 0x92, 0x1b,

    /* U+0052 "R" */
    0xf1, 0x24, 0x9c, 0x51, 0x24, 0xbb,

    /* U+0053 "S" */
    0x7c, 0x60, 0xe0, 0x86, 0x3e,

    /* U+0054 "T" */
    0xfd, 0x48, 0x42, 0x10, 0x8e,

    /* U+0055 "U" */
    0xee, 0x89, 0x12, 0x24, 0x48, 0x91, 0x1c,

    /* U+0056 "V" */
    0xee, 0x89, 0x12, 0x22, 0x85, 0x4, 0x8,

    /* U+0057 "W" */
    0xe0, 0xe8, 0x9, 0x11, 0x22, 0x22, 0xa8, 0x55,
    0x4, 0x40, 0x88,

    /* U+0058 "X" */
    0xee, 0x88, 0xa0, 0x81, 0x5, 0x11, 0x77,

    /* U+0059 "Y" */
    0xee, 0x88, 0xa0, 0x81, 0x2, 0x4, 0x1c,

    /* U+005A "Z" */
    0xfc, 0x44, 0x44, 0x42, 0x3f,

    /* U+005B "[" */
    0xf2, 0x49, 0x27,

    /* U+005C "\\" */
    0x88, 0x44, 0x22, 0x11,

    /* U+005D "]" */
    0xe4, 0x92, 0x4f,

    /* U+005E "^" */
    0x22, 0xa2,

    /* U+005F "_" */
    0xfe,

    /* U+0060 "`" */
    0x90,

    /* U+0061 "a" */
    0xe0, 0x9d, 0x29, 0x3c,

    /* U+0062 "b" */
    0xc2, 0x1c, 0x94, 0xa5, 0x36,

    /* U+0063 "c" */
    0x79, 0x88, 0x97,

    /* U+0064 "d" */
    0x30, 0x9d, 0x29, 0x4a, 0x4d,

    /* U+0065 "e" */
    0x69, 0xf8, 0x97,

    /* U+0066 "f" */
    0x34, 0xe4, 0x44, 0x4e,

    /* U+0067 "g" */
    0x6c, 0xa5, 0x29, 0x38, 0x5c,

    /* U+0068 "h" */
    0xc1, 0x7, 0x12, 0x49, 0x24, 0xbb,

    /* U+0069 "i" */
    0x43, 0x24, 0x97,

    /* U+006A "j" */
    0x21, 0x92, 0x49, 0x38,

    /* U+006B "k" */
    0xc2, 0x12, 0xa6, 0x29, 0x5d,

    /* U+006C "l" */
    0x92, 0x49, 0x23,

    /* U+006D "m" */
    0xb6, 0x24, 0x92, 0x49, 0x24, 0x97, 0x6c,

    /* U+006E "n" */
    0xb1, 0x24, 0x92, 0x4b, 0xb0,

    /* U+006F "o" */
    0x69, 0x99, 0x96,

    /* U+0070 "p" */
    0xb2, 0x52, 0x94, 0xb9, 0x1c,

    /* U+0071 "q" */
    0x6c, 0xa5, 0x29, 0x38, 0x47,

    /* U+0072 "r" */
    0xb5, 0x44, 0x4e,

    /* U+0073 "s" */
    0x78, 0x61, 0x9e,

    /* U+0074 "t" */
    0x5d, 0x24, 0x88,

    /* U+0075 "u" */
    0xd9, 0x24, 0x92, 0x48, 0xd0,

    /* U+0076 "v" */
    0xee, 0x89, 0x11, 0x42, 0x82, 0x0,

    /* U+0077 "w" */
    0xe3, 0xa0, 0x92, 0x45, 0x42, 0xa0, 0xa0,

    /* U+0078 "x" */
    0xcd, 0x23, 0xc, 0x4b, 0x30,

    /* U+0079 "y" */
    0xcd, 0x24, 0x8c, 0x30, 0x42, 0x18,

    /* U+007A "z" */
    0xf9, 0x24, 0x9f,

    /* U+007B "{" */
    0x19, 0x8, 0x42, 0x60, 0x84, 0x21, 0x6,

    /* U+007C "|" */
    0xff,

    /* U+007D "}" */
    0xc1, 0x8, 0x42, 0xc, 0x84, 0x21, 0x30,

    /* U+007E "~" */
    0x61, 0x24, 0x30
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 32, .box_w = 1, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 64, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 3, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 10, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 17, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 33, .adv_w = 48, .box_w = 1, .box_h = 2, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 34, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 96, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 43, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 47, .adv_w = 32, .box_w = 2, .box_h = 3, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 48, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 49, .adv_w = 32, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 60, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 73, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 83, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 103, .adv_w = 32, .box_w = 1, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 32, .box_w = 2, .box_h = 7, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 106, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 110, .adv_w = 128, .box_w = 6, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 113, .adv_w = 128, .box_w = 6, .box_h = 5, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 117, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 176, .box_w = 10, .box_h = 9, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 134, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 147, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 158, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 173, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 187, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 144, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 225, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 232, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 248, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 262, .adv_w = 192, .box_w = 11, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 280, .adv_w = 128, .box_w = 7, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 292, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 112, .box_w = 5, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 304, .adv_w = 128, .box_w = 7, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 305, .adv_w = 48, .box_w = 2, .box_h = 2, .ofs_x = 0, .ofs_y = 7},
    {.bitmap_index = 306, .adv_w = 96, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 310, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 323, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 330, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 335, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 341, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 344, .adv_w = 48, .box_w = 3, .box_h = 10, .ofs_x = -1, .ofs_y = -2},
    {.bitmap_index = 348, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 353, .adv_w = 64, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 356, .adv_w = 160, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 363, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 368, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 376, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 381, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 384, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 387, .adv_w = 64, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 128, .box_w = 7, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 401, .adv_w = 160, .box_w = 9, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 408, .adv_w = 112, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 413, .adv_w = 112, .box_w = 6, .box_h = 8, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 419, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 422, .adv_w = 96, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 429, .adv_w = 32, .box_w = 1, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 430, .adv_w = 96, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 437, .adv_w = 128, .box_w = 7, .box_h = 3, .ofs_x = 0, .ofs_y = 2}
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
    .kern_dsc = NULL,
    .kern_scale = 0,
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
const lv_font_t pixerif16 = {
#else
lv_font_t pixerif16 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if PIXERIF16*/

