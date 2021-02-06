#include "lvgl.h"

/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef IOSEVKA10L
#define IOSEVKA10L 1
#endif

#if IOSEVKA10L

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xf9,

    /* U+22 "\"" */
    0xb6, 0x80,

    /* U+23 "#" */
    0x52, 0x95, 0xf5, 0x29, 0x5f, 0x52, 0x94,

    /* U+24 "$" */
    0x22, 0x7a, 0xa6, 0x33, 0xb6, 0x20,

    /* U+25 "%" */
    0x9a, 0x22, 0x44, 0x99,

    /* U+26 "&" */
    0x69, 0x96, 0xdb, 0x97,

    /* U+27 "'" */
    0xe0,

    /* U+28 "(" */
    0x2a, 0x49, 0x24, 0x91, 0x10,

    /* U+29 ")" */
    0x89, 0x12, 0x49, 0x29, 0x40,

    /* U+2A "*" */
    0x25, 0x5c, 0xa0,

    /* U+2B "+" */
    0x27, 0xc8, 0x40,

    /* U+2C "," */
    0xe0,

    /* U+2D "-" */
    0xe0,

    /* U+2E "." */
    0x80,

    /* U+2F "/" */
    0x24, 0x94, 0x94, 0x92, 0x40,

    /* U+30 "0" */
    0x69, 0x9f, 0xd9, 0x96,

    /* U+31 "1" */
    0x74, 0x92, 0x49,

    /* U+32 "2" */
    0x69, 0x12, 0x48, 0x8f,

    /* U+33 "3" */
    0x69, 0x16, 0x31, 0x96,

    /* U+34 "4" */
    0x11, 0x94, 0xa9, 0x7c, 0x42,

    /* U+35 "5" */
    0xf8, 0xe9, 0x11, 0x96,

    /* U+36 "6" */
    0x24, 0x8e, 0x99, 0x96,

    /* U+37 "7" */
    0xf1, 0x12, 0x22, 0x44,

    /* U+38 "8" */
    0x69, 0x96, 0x69, 0x96,

    /* U+39 "9" */
    0x69, 0x99, 0x71, 0x96,

    /* U+3A ":" */
    0x84,

    /* U+3B ";" */
    0x87,

    /* U+3C "<" */
    0x16, 0x88, 0x43,

    /* U+3D "=" */
    0xe3, 0x80,

    /* U+3E ">" */
    0x86, 0x11, 0x2c,

    /* U+3F "?" */
    0x69, 0x12, 0x24, 0x4,

    /* U+40 "@" */
    0xd4, 0xff, 0xff, 0xfc, 0x80,

    /* U+41 "A" */
    0x46, 0x6a, 0x9f, 0x99,

    /* U+42 "B" */
    0xe9, 0x9e, 0x99, 0x9e,

    /* U+43 "C" */
    0x69, 0x88, 0x88, 0x96,

    /* U+44 "D" */
    0xe9, 0x99, 0x99, 0x9e,

    /* U+45 "E" */
    0xf8, 0x8e, 0x88, 0x8f,

    /* U+46 "F" */
    0xf8, 0x8e, 0x88, 0x88,

    /* U+47 "G" */
    0x69, 0x8b, 0x99, 0x96,

    /* U+48 "H" */
    0x99, 0x9f, 0x99, 0x99,

    /* U+49 "I" */
    0xe9, 0x24, 0x97,

    /* U+4A "J" */
    0x31, 0x11, 0x11, 0x96,

    /* U+4B "K" */
    0x9a, 0xac, 0xaa, 0x99,

    /* U+4C "L" */
    0x88, 0x88, 0x88, 0x8f,

    /* U+4D "M" */
    0x99, 0xff, 0xd9, 0x99,

    /* U+4E "N" */
    0x9d, 0xdd, 0xdb, 0xb9,

    /* U+4F "O" */
    0x69, 0x99, 0x99, 0x96,

    /* U+50 "P" */
    0xe9, 0x99, 0xe8, 0x88,

    /* U+51 "Q" */
    0x69, 0x99, 0x99, 0x99, 0x64, 0x30,

    /* U+52 "R" */
    0xe9, 0x99, 0xea, 0x99,

    /* U+53 "S" */
    0x69, 0x84, 0x21, 0x96,

    /* U+54 "T" */
    0xf9, 0x8, 0x42, 0x10, 0x84,

    /* U+55 "U" */
    0x99, 0x99, 0x99, 0x96,

    /* U+56 "V" */
    0x99, 0x99, 0xa6, 0x64,

    /* U+57 "W" */
    0x99, 0x99, 0xde, 0x66,

    /* U+58 "X" */
    0x99, 0x66, 0x66, 0x99,

    /* U+59 "Y" */
    0xb6, 0xe4, 0x92,

    /* U+5A "Z" */
    0xf2, 0x24, 0x48, 0x8f,

    /* U+5B "[" */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x8f,

    /* U+5C "\\" */
    0x92, 0x48, 0x92, 0x44, 0x90,

    /* U+5D "]" */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x1f,

    /* U+5E "^" */
    0x54, 0x0,

    /* U+5F "_" */
    0xe0,

    /* U+60 "`" */
    0xa4,

    /* U+61 "a" */
    0x69, 0x79, 0x9f,

    /* U+62 "b" */
    0x88, 0xe9, 0x99, 0x9e,

    /* U+63 "c" */
    0x69, 0x88, 0x96,

    /* U+64 "d" */
    0x11, 0x79, 0x99, 0x97,

    /* U+65 "e" */
    0x69, 0xf8, 0x96,

    /* U+66 "f" */
    0x74, 0xf4, 0x44, 0x44,

    /* U+67 "g" */
    0x79, 0x96, 0x79, 0x96,

    /* U+68 "h" */
    0x88, 0xe9, 0x99, 0x99,

    /* U+69 "i" */
    0x20, 0x62, 0x22, 0x2f,

    /* U+6A "j" */
    0x10, 0x31, 0x11, 0x11, 0x96,

    /* U+6B "k" */
    0x88, 0x9a, 0xca, 0xa9,

    /* U+6C "l" */
    0x62, 0x22, 0x22, 0x2f,

    /* U+6D "m" */
    0xff, 0xff, 0xc0,

    /* U+6E "n" */
    0xe9, 0x99, 0x99,

    /* U+6F "o" */
    0x69, 0x99, 0x96,

    /* U+70 "p" */
    0xe9, 0x99, 0x9e, 0x88,

    /* U+71 "q" */
    0x79, 0x99, 0x97, 0x11,

    /* U+72 "r" */
    0xe9, 0x88, 0x88,

    /* U+73 "s" */
    0xe9, 0x87, 0x97,

    /* U+74 "t" */
    0x42, 0x3c, 0x84, 0x21, 0x46,

    /* U+75 "u" */
    0x99, 0x99, 0x97,

    /* U+76 "v" */
    0x99, 0x9a, 0x64,

    /* U+77 "w" */
    0x99, 0x9d, 0x66,

    /* U+78 "x" */
    0x15, 0x2b, 0x40,

    /* U+79 "y" */
    0x99, 0x96, 0x62, 0x44,

    /* U+7A "z" */
    0xf2, 0x44, 0x8f,

    /* U+7B "{" */
    0x29, 0x25, 0x12, 0x49, 0x10,

    /* U+7C "|" */
    0xff, 0xf0,

    /* U+7D "}" */
    0x89, 0x24, 0x52, 0x49, 0x40,

    /* U+7E "~" */
    0x3, 0xa4
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 80, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 4, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 11, .adv_w = 80, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 17, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 80, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 26, .adv_w = 80, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 31, .adv_w = 80, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 39, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 2},
    {.bitmap_index = 42, .adv_w = 80, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 43, .adv_w = 80, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 44, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 45, .adv_w = 80, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 50, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 54, .adv_w = 80, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 57, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 70, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 74, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 86, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 80, .box_w = 1, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 91, .adv_w = 80, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 92, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 95, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 97, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 100, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 109, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 121, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 137, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 80, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 152, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 156, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 168, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 80, .box_w = 4, .box_h = 11, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 178, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 191, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 203, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 80, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 210, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 80, .box_w = 4, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 220, .adv_w = 80, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 225, .adv_w = 80, .box_w = 4, .box_h = 12, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 231, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 233, .adv_w = 80, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 234, .adv_w = 80, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 235, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 245, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 249, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 252, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 256, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 260, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 268, .adv_w = 80, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 273, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 80, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 290, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 294, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 298, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 301, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 309, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 315, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 318, .adv_w = 80, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 321, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 325, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 80, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 333, .adv_w = 80, .box_w = 1, .box_h = 12, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 335, .adv_w = 80, .box_w = 3, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 340, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 3}
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

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t iosevka10l = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 13,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = 0,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if IOSEVKA10L*/

