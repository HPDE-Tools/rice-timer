#include "lvgl.h"

/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef MONONOKI10
#define MONONOKI10 1
#endif

#if MONONOKI10

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xfa,

    /* U+22 "\"" */
    0xb6, 0x80,

    /* U+23 "#" */
    0x52, 0xbe, 0xaf, 0xa9, 0x40,

    /* U+24 "$" */
    0x21, 0x3d, 0x8, 0x3c, 0x3e, 0x21, 0x0,

    /* U+25 "%" */
    0x40, 0x44, 0x44, 0x4,

    /* U+26 "&" */
    0x64, 0xa4, 0xc9, 0xcd, 0xa0,

    /* U+27 "'" */
    0xe0,

    /* U+28 "(" */
    0x34, 0x88, 0x88, 0x84, 0x30,

    /* U+29 ")" */
    0xc2, 0x11, 0x11, 0x32, 0xc0,

    /* U+2A "*" */
    0x25, 0x5c, 0xa0, 0x0,

    /* U+2B "+" */
    0x21, 0x3e, 0x42, 0x0,

    /* U+2C "," */
    0x67, 0x0,

    /* U+2D "-" */
    0xf0,

    /* U+2E "." */
    0x80,

    /* U+2F "/" */
    0x8, 0x44, 0x22, 0x11, 0x8, 0x0,

    /* U+30 "0" */
    0x76, 0xe7, 0x5c, 0xed, 0xc0,

    /* U+31 "1" */
    0x2e, 0x22, 0x22, 0xf0,

    /* U+32 "2" */
    0xe1, 0x12, 0x48, 0xf0,

    /* U+33 "3" */
    0xe1, 0x16, 0x11, 0xe0,

    /* U+34 "4" */
    0x21, 0x10, 0xa9, 0x7c, 0x40,

    /* U+35 "5" */
    0xe8, 0x8e, 0x11, 0xe0,

    /* U+36 "6" */
    0x7c, 0x8e, 0x99, 0x60,

    /* U+37 "7" */
    0xf9, 0x12, 0x24, 0x40,

    /* U+38 "8" */
    0x64, 0xa4, 0xc9, 0xc5, 0xc0,

    /* U+39 "9" */
    0x69, 0x97, 0x13, 0xe0,

    /* U+3A ":" */
    0x88,

    /* U+3B ";" */
    0x60, 0x6, 0x70,

    /* U+3C "<" */
    0x16, 0x84, 0x30,

    /* U+3D "=" */
    0xf8, 0x3e,

    /* U+3E ">" */
    0x86, 0x16, 0x80,

    /* U+3F "?" */
    0xc3, 0x16, 0x40, 0x0,

    /* U+40 "@" */
    0x74, 0x63, 0x3b, 0xce, 0x10, 0x70,

    /* U+41 "A" */
    0x32, 0x94, 0x97, 0xc6, 0x20,

    /* U+42 "B" */
    0xf2, 0x52, 0xe4, 0xa5, 0xc0,

    /* U+43 "C" */
    0x78, 0x88, 0x88, 0x70,

    /* U+44 "D" */
    0xf2, 0xd2, 0x94, 0xad, 0xc0,

    /* U+45 "E" */
    0xf8, 0x8f, 0x88, 0xf0,

    /* U+46 "F" */
    0xf8, 0x8f, 0x88, 0x80,

    /* U+47 "G" */
    0x78, 0x8b, 0x99, 0x70,

    /* U+48 "H" */
    0x99, 0x9f, 0x99, 0x90,

    /* U+49 "I" */
    0x71, 0x8, 0x42, 0x13, 0xe0,

    /* U+4A "J" */
    0x71, 0x11, 0x11, 0xe0,

    /* U+4B "K" */
    0x9a, 0xac, 0xaa, 0x90,

    /* U+4C "L" */
    0x84, 0x21, 0x8, 0x43, 0xe0,

    /* U+4D "M" */
    0x8e, 0xf7, 0x58, 0xc6, 0x20,

    /* U+4E "N" */
    0x99, 0xdd, 0xb9, 0x90,

    /* U+4F "O" */
    0x69, 0x99, 0x99, 0x60,

    /* U+50 "P" */
    0xe9, 0x99, 0xe8, 0x80,

    /* U+51 "Q" */
    0x4a, 0xaa, 0xaa, 0x44, 0x70,

    /* U+52 "R" */
    0xe9, 0x9e, 0xa9, 0x90,

    /* U+53 "S" */
    0x68, 0x86, 0x11, 0xe0,

    /* U+54 "T" */
    0xf9, 0x8, 0x42, 0x10, 0x80,

    /* U+55 "U" */
    0x99, 0x99, 0x99, 0x60,

    /* U+56 "V" */
    0x8c, 0x62, 0x95, 0x28, 0xc0,

    /* U+57 "W" */
    0x8c, 0x63, 0x5d, 0xee, 0x20,

    /* U+58 "X" */
    0x8a, 0x54, 0x45, 0x26, 0x20,

    /* U+59 "Y" */
    0x8c, 0x54, 0xa2, 0x10, 0x80,

    /* U+5A "Z" */
    0xf8, 0x84, 0x44, 0x43, 0xe0,

    /* U+5B "[" */
    0xf8, 0x88, 0x88, 0x88, 0xf0,

    /* U+5C "\\" */
    0x82, 0x10, 0x42, 0x8, 0x41, 0x0,

    /* U+5D "]" */
    0xf1, 0x11, 0x11, 0x11, 0xf0,

    /* U+5E "^" */
    0x32, 0xe2,

    /* U+5F "_" */
    0xf8,

    /* U+60 "`" */
    0xc,

    /* U+61 "a" */
    0x71, 0xf9, 0xf0,

    /* U+62 "b" */
    0x88, 0xe9, 0x99, 0xe0,

    /* U+63 "c" */
    0x78, 0x88, 0x70,

    /* U+64 "d" */
    0x11, 0x79, 0x99, 0x70,

    /* U+65 "e" */
    0x69, 0xf8, 0x70,

    /* U+66 "f" */
    0x74, 0xf4, 0x44, 0x40,

    /* U+67 "g" */
    0xf4, 0x9d, 0x7, 0x47, 0xc0,

    /* U+68 "h" */
    0x88, 0xf9, 0x99, 0x90,

    /* U+69 "i" */
    0x20, 0x18, 0x42, 0x13, 0xe0,

    /* U+6A "j" */
    0x10, 0xf1, 0x11, 0x11, 0xe0,

    /* U+6B "k" */
    0x88, 0x9a, 0xca, 0x90,

    /* U+6C "l" */
    0xc4, 0x44, 0x44, 0x70,

    /* U+6D "m" */
    0xfd, 0x6b, 0x5a, 0x80,

    /* U+6E "n" */
    0xf9, 0x99, 0x90,

    /* U+6F "o" */
    0x69, 0x99, 0x60,

    /* U+70 "p" */
    0xe9, 0x99, 0xe8, 0x80,

    /* U+71 "q" */
    0x79, 0x99, 0x71, 0x10,

    /* U+72 "r" */
    0xf9, 0x88, 0x80,

    /* U+73 "s" */
    0x78, 0x61, 0xf0,

    /* U+74 "t" */
    0x44, 0xf4, 0x44, 0x30,

    /* U+75 "u" */
    0x99, 0x99, 0xf0,

    /* U+76 "v" */
    0x99, 0x95, 0x60,

    /* U+77 "w" */
    0x8d, 0x77, 0xb8, 0x80,

    /* U+78 "x" */
    0x9a, 0x4a, 0x90,

    /* U+79 "y" */
    0x99, 0x96, 0x62, 0xc0,

    /* U+7A "z" */
    0xf2, 0x48, 0xf0,

    /* U+7B "{" */
    0x39, 0x8, 0x4c, 0x10, 0x84, 0x38,

    /* U+7C "|" */
    0xff, 0x80,

    /* U+7D "}" */
    0xe1, 0x8, 0x41, 0x90, 0x84, 0xe0,

    /* U+7E "~" */
    0xe5, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 90, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 90, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 90, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 4, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 9, .adv_w = 90, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 16, .adv_w = 90, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 20, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 25, .adv_w = 90, .box_w = 1, .box_h = 3, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 26, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 31, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 40, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 90, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 46, .adv_w = 90, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 47, .adv_w = 90, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 54, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 59, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 63, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 67, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 76, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 97, .adv_w = 90, .box_w = 1, .box_h = 5, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 90, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 101, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 90, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 106, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 109, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 119, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 129, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 142, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 154, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 159, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 163, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 181, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 185, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 189, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 194, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 198, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 202, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 207, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 221, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 226, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 236, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 241, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 247, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 252, .adv_w = 90, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 254, .adv_w = 90, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 255, .adv_w = 90, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 256, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 273, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 277, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 282, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 286, .adv_w = 90, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 90, .box_w = 4, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 296, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 300, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 304, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 308, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 314, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 318, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 322, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 325, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 328, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 332, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 335, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 338, .adv_w = 90, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 345, .adv_w = 90, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 349, .adv_w = 90, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 352, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 358, .adv_w = 90, .box_w = 1, .box_h = 9, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 360, .adv_w = 90, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 366, .adv_w = 90, .box_w = 5, .box_h = 2, .ofs_x = 1, .ofs_y = 1}
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
lv_font_t mononoki10 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 10,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -1,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if MONONOKI10*/

