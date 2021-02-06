#include "lvgl.h"

/*******************************************************************************
 * Size: 12 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef IOSEVKA12
#define IOSEVKA12 1
#endif

#if IOSEVKA12

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0x55, 0x50, 0xf0,

    /* U+22 "\"" */
    0xb6, 0xd0,

    /* U+23 "#" */
    0x52, 0x95, 0xf5, 0x29, 0x4a, 0xfa, 0x94, 0xa0,

    /* U+24 "$" */
    0x21, 0x1d, 0xea, 0x71, 0x86, 0x35, 0xbc, 0x42,
    0x0,

    /* U+25 "%" */
    0x99, 0xa2, 0x24, 0x45, 0x99,

    /* U+26 "&" */
    0x64, 0xa5, 0x66, 0x36, 0xf3, 0x8b, 0xc0,

    /* U+27 "'" */
    0xf0,

    /* U+28 "(" */
    0x12, 0x44, 0x88, 0x88, 0x88, 0x84, 0x63,

    /* U+29 ")" */
    0x84, 0x22, 0x11, 0x11, 0x11, 0x12, 0x6c,

    /* U+2A "*" */
    0x21, 0x3e, 0xa5, 0x0,

    /* U+2B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+2C "," */
    0xf6, 0x0,

    /* U+2D "-" */
    0xf0,

    /* U+2E "." */
    0xf0,

    /* U+2F "/" */
    0x11, 0x12, 0x22, 0x24, 0x44, 0x48, 0x88,

    /* U+30 "0" */
    0x74, 0x63, 0x3b, 0xf7, 0x31, 0xcb, 0x80,

    /* U+31 "1" */
    0x7c, 0x92, 0x49, 0x24,

    /* U+32 "2" */
    0x72, 0x42, 0x11, 0x19, 0x88, 0x47, 0xc0,

    /* U+33 "3" */
    0x72, 0x42, 0x13, 0xc, 0x21, 0xcb, 0x80,

    /* U+34 "4" */
    0x11, 0x8c, 0xa5, 0x4b, 0xe2, 0x10, 0x80,

    /* U+35 "5" */
    0xfc, 0x21, 0xf, 0x44, 0x21, 0x9b, 0x80,

    /* U+36 "6" */
    0x11, 0x11, 0x8f, 0x46, 0x31, 0x8b, 0x80,

    /* U+37 "7" */
    0xf8, 0x42, 0x21, 0x8, 0x84, 0x22, 0x0,

    /* U+38 "8" */
    0x74, 0x63, 0x17, 0x2a, 0x31, 0x8b, 0x80,

    /* U+39 "9" */
    0x74, 0x63, 0x18, 0xbc, 0x31, 0x9b, 0x80,

    /* U+3A ":" */
    0xf0, 0x3c,

    /* U+3B ";" */
    0xf0, 0x3d, 0x80,

    /* U+3C "<" */
    0x0, 0x89, 0x88, 0x20, 0xc3,

    /* U+3D "=" */
    0xf0, 0xf,

    /* U+3E ">" */
    0x2, 0x8, 0x30, 0x89, 0x98,

    /* U+3F "?" */
    0x74, 0x42, 0x11, 0x10, 0x80, 0x63, 0x0,

    /* U+40 "@" */
    0x74, 0x42, 0x1e, 0xd6, 0xb5, 0xad, 0x6b, 0xb0,

    /* U+41 "A" */
    0x22, 0x94, 0xa5, 0x6e, 0x3f, 0x8c, 0x40,

    /* U+42 "B" */
    0xe4, 0xa5, 0x29, 0x72, 0x71, 0x8f, 0x80,

    /* U+43 "C" */
    0x74, 0xe1, 0x8, 0x42, 0x10, 0x9b, 0x80,

    /* U+44 "D" */
    0xf4, 0xe3, 0x18, 0xc6, 0x31, 0x9f, 0x80,

    /* U+45 "E" */
    0xf8, 0x88, 0xf8, 0x88, 0x8f,

    /* U+46 "F" */
    0xf8, 0x88, 0xf8, 0x88, 0x88,

    /* U+47 "G" */
    0x74, 0x61, 0x8, 0x4e, 0x31, 0x8b, 0x80,

    /* U+48 "H" */
    0x8c, 0x63, 0x1f, 0xc6, 0x31, 0x8c, 0x40,

    /* U+49 "I" */
    0xe9, 0x24, 0x92, 0x5c,

    /* U+4A "J" */
    0x38, 0x42, 0x10, 0x84, 0x21, 0x4b, 0x80,

    /* U+4B "K" */
    0x8c, 0xa5, 0x4e, 0x6a, 0x52, 0x8c, 0x40,

    /* U+4C "L" */
    0x88, 0x88, 0x88, 0x88, 0x8f,

    /* U+4D "M" */
    0x8e, 0xf7, 0xbe, 0xd6, 0xb1, 0x8c, 0x40,

    /* U+4E "N" */
    0xce, 0x73, 0x5a, 0xd6, 0xb3, 0x9c, 0xc0,

    /* U+4F "O" */
    0x74, 0x63, 0x18, 0xc6, 0x31, 0x8b, 0x80,

    /* U+50 "P" */
    0xe9, 0x99, 0x9e, 0x88, 0x88,

    /* U+51 "Q" */
    0x74, 0x63, 0x18, 0xc6, 0x31, 0x8b, 0x88, 0x30,

    /* U+52 "R" */
    0xf4, 0x63, 0x18, 0xfa, 0x52, 0x8c, 0x40,

    /* U+53 "S" */
    0x74, 0x61, 0x6, 0x18, 0x21, 0x8b, 0x80,

    /* U+54 "T" */
    0xf9, 0x8, 0x42, 0x10, 0x84, 0x21, 0x0,

    /* U+55 "U" */
    0x8c, 0x63, 0x18, 0xc6, 0x31, 0x8b, 0x80,

    /* U+56 "V" */
    0x8c, 0x63, 0x18, 0xa9, 0x4a, 0x51, 0x0,

    /* U+57 "W" */
    0x8c, 0x63, 0x1a, 0xd7, 0xaa, 0x52, 0x80,

    /* U+58 "X" */
    0x8c, 0x76, 0xa2, 0x11, 0x5b, 0x8c, 0x40,

    /* U+59 "Y" */
    0x8c, 0x62, 0xa5, 0x10, 0x84, 0x21, 0x0,

    /* U+5A "Z" */
    0xf8, 0x84, 0x42, 0x31, 0x8, 0x87, 0xc0,

    /* U+5B "[" */
    0xf8, 0x88, 0x88, 0x88, 0x88, 0x88, 0x8f,

    /* U+5C "\\" */
    0x88, 0x84, 0x44, 0x42, 0x22, 0x21, 0x11,

    /* U+5D "]" */
    0xf1, 0x11, 0x11, 0x11, 0x11, 0x11, 0x1f,

    /* U+5E "^" */
    0x6f, 0x90,

    /* U+5F "_" */
    0xf0,

    /* U+60 "`" */
    0x88, 0x80,

    /* U+61 "a" */
    0x72, 0x42, 0xf4, 0xc5, 0xe0,

    /* U+62 "b" */
    0x84, 0x21, 0xe8, 0xc6, 0x31, 0x8f, 0x80,

    /* U+63 "c" */
    0x74, 0xe1, 0x8, 0x4d, 0xc0,

    /* U+64 "d" */
    0x8, 0x42, 0xf8, 0xc6, 0x31, 0x8b, 0xc0,

    /* U+65 "e" */
    0x74, 0x63, 0xf8, 0x45, 0xc0,

    /* U+66 "f" */
    0x75, 0x4f, 0x44, 0x44, 0x44,

    /* U+67 "g" */
    0x7c, 0x63, 0x17, 0x41, 0xd3, 0x9b, 0x80,

    /* U+68 "h" */
    0x84, 0x21, 0xe8, 0xc6, 0x31, 0x8c, 0x40,

    /* U+69 "i" */
    0x60, 0x1, 0xc2, 0x10, 0x84, 0x27, 0xc0,

    /* U+6A "j" */
    0x10, 0x7, 0x11, 0x11, 0x11, 0x19, 0x60,

    /* U+6B "k" */
    0x84, 0x21, 0x19, 0x53, 0xd2, 0x9c, 0x40,

    /* U+6C "l" */
    0xe1, 0x8, 0x42, 0x10, 0x84, 0x27, 0xc0,

    /* U+6D "m" */
    0xfd, 0x6b, 0x5a, 0xd6, 0xa0,

    /* U+6E "n" */
    0xf4, 0x63, 0x18, 0xc6, 0x20,

    /* U+6F "o" */
    0x74, 0x63, 0x18, 0xc5, 0xc0,

    /* U+70 "p" */
    0xf4, 0x63, 0x18, 0xc7, 0xd0, 0x84, 0x0,

    /* U+71 "q" */
    0x7c, 0x63, 0x18, 0xc5, 0xe1, 0x8, 0x40,

    /* U+72 "r" */
    0xf9, 0x88, 0x88, 0x80,

    /* U+73 "s" */
    0x74, 0xa0, 0xe1, 0x49, 0xc0,

    /* U+74 "t" */
    0x42, 0x11, 0xe4, 0x21, 0x8, 0x49, 0x80,

    /* U+75 "u" */
    0x8c, 0x63, 0x18, 0xc5, 0xe0,

    /* U+76 "v" */
    0x8c, 0x62, 0xa5, 0x28, 0x80,

    /* U+77 "w" */
    0x8c, 0x63, 0x5e, 0xa9, 0x40,

    /* U+78 "x" */
    0x99, 0x66, 0x69, 0x90,

    /* U+79 "y" */
    0x8c, 0x62, 0xa5, 0x38, 0x84, 0x42, 0x0,

    /* U+7A "z" */
    0xf8, 0x88, 0x44, 0x43, 0xe0,

    /* U+7B "{" */
    0x36, 0x46, 0x22, 0xc6, 0x22, 0x44, 0x63,

    /* U+7C "|" */
    0xff, 0xfc,

    /* U+7D "}" */
    0xc6, 0x26, 0x44, 0x36, 0x44, 0x22, 0x6c,

    /* U+7E "~" */
    0x65, 0xe9, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 96, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 96, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 4, .adv_w = 96, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 6, .adv_w = 96, .box_w = 5, .box_h = 12, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 14, .adv_w = 96, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 23, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 28, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 35, .adv_w = 96, .box_w = 1, .box_h = 4, .ofs_x = 3, .ofs_y = 6},
    {.bitmap_index = 36, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 43, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 50, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 6},
    {.bitmap_index = 54, .adv_w = 96, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 58, .adv_w = 96, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 60, .adv_w = 96, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 61, .adv_w = 96, .box_w = 2, .box_h = 2, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 69, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 96, .box_w = 3, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 87, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 101, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 108, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 115, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 122, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 96, .box_w = 2, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 96, .box_w = 2, .box_h = 10, .ofs_x = 2, .ofs_y = -3},
    {.bitmap_index = 141, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 146, .adv_w = 96, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 148, .adv_w = 96, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 153, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 160, .adv_w = 96, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 168, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 196, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 206, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 96, .box_w = 3, .box_h = 10, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 238, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 250, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 257, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 264, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 269, .adv_w = 96, .box_w = 5, .box_h = 12, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 277, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 298, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 312, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 319, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 326, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 333, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 347, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 354, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 361, .adv_w = 96, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 363, .adv_w = 96, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 364, .adv_w = 96, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 7},
    {.bitmap_index = 366, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 371, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 378, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 383, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 390, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 395, .adv_w = 96, .box_w = 4, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 400, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 407, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 414, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 421, .adv_w = 96, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 428, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 435, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 442, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 447, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 452, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 457, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 464, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 471, .adv_w = 96, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 475, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 480, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 487, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 492, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 497, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 96, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 506, .adv_w = 96, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 513, .adv_w = 96, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 518, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 525, .adv_w = 96, .box_w = 1, .box_h = 14, .ofs_x = 3, .ofs_y = -2},
    {.bitmap_index = 527, .adv_w = 96, .box_w = 4, .box_h = 14, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 534, .adv_w = 96, .box_w = 6, .box_h = 3, .ofs_x = 0, .ofs_y = 3}
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
lv_font_t iosevka12 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 15,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if IOSEVKA12*/

