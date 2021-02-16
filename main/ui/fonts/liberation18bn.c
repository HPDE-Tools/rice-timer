#include "lvgl.h"

/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef LIBERATION18BN
#define LIBERATION18BN 1
#endif

#if LIBERATION18BN

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xff, 0xff, 0xc0, 0xc0,

    /* U+22 "\"" */
    0xde, 0xf7, 0xb0,

    /* U+23 "#" */
    0x12, 0x12, 0x12, 0x14, 0x7f, 0x24, 0x24, 0x24,
    0xfe, 0x28, 0x48, 0x48, 0x48,

    /* U+24 "$" */
    0x7c, 0xfe, 0xd6, 0xd2, 0xd0, 0xf8, 0x7e, 0x1f,
    0x13, 0xd3, 0xd3, 0xfe, 0x7c, 0x10, 0x10,

    /* U+25 "%" */
    0x70, 0x46, 0xc6, 0x36, 0x21, 0xb2, 0xd, 0x90,
    0x6d, 0x7b, 0x6e, 0x6e, 0xb3, 0x5, 0x98, 0x4c,
    0xc2, 0x66, 0x23, 0x32, 0xf, 0x0,

    /* U+26 "&" */
    0x1c, 0xd, 0x83, 0x60, 0xd8, 0x3e, 0x7, 0x7,
    0x13, 0xe6, 0xcb, 0x32, 0xcc, 0x73, 0x98, 0x7f,
    0xc0,

    /* U+27 "'" */
    0xff,

    /* U+28 "(" */
    0x36, 0x66, 0xcc, 0xcc, 0xcc, 0xcc, 0xc6, 0x66,
    0x30,

    /* U+29 ")" */
    0xc6, 0x66, 0x33, 0x33, 0x33, 0x33, 0x36, 0x66,
    0xc0,

    /* U+2A "*" */
    0x30, 0xcf, 0xff, 0x7b, 0x24, 0x80,

    /* U+2B "+" */
    0x18, 0x30, 0x60, 0xcf, 0xe3, 0x6, 0xc, 0x18,

    /* U+2C "," */
    0xfd, 0x60,

    /* U+2D "-" */
    0xf0,

    /* U+2E "." */
    0xfc,

    /* U+2F "/" */
    0x33, 0x32, 0x66, 0x66, 0x64, 0x4c, 0xc0,

    /* U+30 "0" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x13, 0x63, 0x80,

    /* U+31 "1" */
    0x38, 0xf3, 0xe4, 0xc1, 0x83, 0x6, 0xc, 0x18,
    0x30, 0x60, 0xcf, 0xe0,

    /* U+32 "2" */
    0x38, 0xcb, 0x18, 0x30, 0x61, 0xc7, 0xe, 0x38,
    0xe1, 0x87, 0xf, 0xe0,

    /* U+33 "3" */
    0x3d, 0xdf, 0x18, 0x30, 0x61, 0x8e, 0x6, 0x6,
    0x8f, 0x1e, 0x67, 0x80,

    /* U+34 "4" */
    0xe, 0xe, 0x1e, 0x1e, 0x36, 0x36, 0x66, 0x66,
    0xc6, 0xff, 0x6, 0x6, 0x6,

    /* U+35 "5" */
    0xfd, 0x83, 0x6, 0xc, 0x1f, 0xb3, 0x3, 0x6,
    0xf, 0x1e, 0x67, 0x80,

    /* U+36 "6" */
    0x3c, 0xd9, 0x16, 0xc, 0x1f, 0xbb, 0xe3, 0xc7,
    0x8f, 0x1b, 0x63, 0x80,

    /* U+37 "7" */
    0xfe, 0xc, 0x10, 0x60, 0xc3, 0x6, 0xc, 0x10,
    0x60, 0xc1, 0x83, 0x0,

    /* U+38 "8" */
    0x7d, 0x8f, 0x1e, 0x3c, 0x68, 0x8e, 0x63, 0xc7,
    0x8f, 0x1e, 0x37, 0xc0,

    /* U+39 "9" */
    0x38, 0xdb, 0x1e, 0x3c, 0x78, 0xdb, 0xbf, 0x6,
    0xf, 0x12, 0x67, 0x80,

    /* U+3A ":" */
    0xc0, 0x0, 0x30,

    /* U+3B ";" */
    0xc0, 0x0, 0x35, 0xc0,

    /* U+3C "<" */
    0x3, 0xf, 0x3c, 0xf0, 0xc0, 0xe0, 0xf8, 0x1e,
    0x7, 0x1,

    /* U+3D "=" */
    0xfe, 0x0, 0x0, 0xf, 0xe0,

    /* U+3E ">" */
    0x80, 0xf0, 0x7c, 0x1f, 0x7, 0x7, 0x1e, 0x78,
    0xe0, 0x80,

    /* U+3F "?" */
    0x3c, 0x66, 0x63, 0x3, 0x3, 0x7, 0xe, 0xc,
    0x1c, 0x18, 0x0, 0x0, 0x18,

    /* U+40 "@" */
    0x7, 0xc0, 0xc3, 0x8, 0x4, 0x8e, 0xb4, 0x9c,
    0xc4, 0x66, 0x43, 0x32, 0x11, 0x91, 0x8c, 0x8c,
    0xa4, 0xe4, 0x9d, 0xc4, 0x0, 0x18, 0x30, 0x7e,
    0x0,

    /* U+41 "A" */
    0xe, 0x3, 0x81, 0xe0, 0x6c, 0x1b, 0xe, 0xc3,
    0x30, 0xc6, 0x3f, 0x98, 0x66, 0xd, 0x83, 0x60,
    0xc0,

    /* U+42 "B" */
    0xfe, 0x63, 0xb0, 0xd8, 0x6c, 0x36, 0x3b, 0xf9,
    0x86, 0xc1, 0xe0, 0xf0, 0x78, 0x6f, 0xe0,

    /* U+43 "C" */
    0x1e, 0x18, 0xe6, 0x1b, 0x4, 0xc0, 0x30, 0xc,
    0x3, 0x0, 0xc0, 0x30, 0x46, 0x19, 0xce, 0x1e,
    0x0,

    /* U+44 "D" */
    0xfc, 0x63, 0x30, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0xd8, 0xcf, 0xc0,

    /* U+45 "E" */
    0xff, 0x60, 0x30, 0x18, 0xc, 0x6, 0x3, 0xfd,
    0x80, 0xc0, 0x60, 0x30, 0x18, 0xf, 0xf8,

    /* U+46 "F" */
    0xff, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xff,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+47 "G" */
    0x1f, 0x1c, 0xe6, 0x1f, 0x0, 0xc0, 0x30, 0xc,
    0x3, 0x1f, 0xc0, 0xf0, 0x36, 0xd, 0xc7, 0x1f,
    0x0,

    /* U+48 "H" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0xff,
    0x83, 0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x18,

    /* U+49 "I" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+4A "J" */
    0x1e, 0xc, 0x18, 0x30, 0x60, 0xc1, 0x83, 0x6,
    0xf, 0x1b, 0x23, 0x80,

    /* U+4B "K" */
    0xc3, 0xe3, 0xb1, 0x99, 0x8d, 0xc7, 0xc3, 0xe1,
    0xd8, 0xce, 0x63, 0x31, 0xd8, 0x6c, 0x18,

    /* U+4C "L" */
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0, 0xc0,
    0xc0, 0xc0, 0xc0, 0xc0, 0xff,

    /* U+4D "M" */
    0xe1, 0xf8, 0x7e, 0x1f, 0xcf, 0xf3, 0xf4, 0xbd,
    0x2f, 0x7b, 0xde, 0xf3, 0x3c, 0xcf, 0x33, 0xcc,
    0xc0,

    /* U+4E "N" */
    0xe1, 0xf0, 0xfc, 0x7e, 0x3d, 0x9e, 0xcf, 0x67,
    0x9b, 0xcd, 0xe3, 0xf1, 0xf8, 0x7c, 0x38,

    /* U+4F "O" */
    0x1e, 0x1c, 0xc6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf0, 0x36, 0x18, 0xcc, 0x1e,
    0x0,

    /* U+50 "P" */
    0xfc, 0xc6, 0xc3, 0xc3, 0xc3, 0xc3, 0xc6, 0xfc,
    0xc0, 0xc0, 0xc0, 0xc0, 0xc0,

    /* U+51 "Q" */
    0x1e, 0xc, 0xc6, 0x1b, 0x3, 0xc0, 0xf0, 0x3c,
    0xf, 0x3, 0xc0, 0xf8, 0x77, 0x39, 0xfe, 0x3e,
    0x3, 0x80, 0x60, 0x1e, 0x3, 0x80,

    /* U+52 "R" */
    0xfe, 0x30, 0xcc, 0x1b, 0x6, 0xc1, 0xb0, 0x6c,
    0x33, 0xf8, 0xc6, 0x31, 0xcc, 0x33, 0xe, 0xc1,
    0x80,

    /* U+53 "S" */
    0x3c, 0x46, 0xc3, 0xc0, 0xf0, 0xfc, 0x7e, 0x3f,
    0x7, 0x3, 0xc3, 0xc6, 0x7c,

    /* U+54 "T" */
    0xff, 0x8c, 0x6, 0x3, 0x1, 0x80, 0xc0, 0x60,
    0x30, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80,

    /* U+55 "U" */
    0xc1, 0xe0, 0xf0, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xf0, 0x6c, 0x63, 0xe0,

    /* U+56 "V" */
    0xc1, 0xd8, 0x66, 0x19, 0x86, 0x63, 0xc, 0xc3,
    0x30, 0xcc, 0x16, 0x7, 0x81, 0xe0, 0x70, 0xc,
    0x0,

    /* U+57 "W" */
    0xc3, 0xf, 0xc, 0x76, 0x79, 0x99, 0xe6, 0x67,
    0x99, 0x9e, 0x66, 0x49, 0x8b, 0x3c, 0x3c, 0xf0,
    0xf3, 0xc3, 0xcf, 0xe, 0x3c, 0x18, 0x60,

    /* U+58 "X" */
    0x61, 0x98, 0xe3, 0x30, 0xdc, 0x1e, 0x7, 0x81,
    0xe0, 0x78, 0x3f, 0xc, 0xc7, 0x31, 0x86, 0xe1,
    0x80,

    /* U+59 "Y" */
    0x61, 0x98, 0x63, 0x30, 0xcc, 0x1f, 0x7, 0x81,
    0xe0, 0x30, 0xc, 0x3, 0x0, 0xc0, 0x30, 0xc,
    0x0,

    /* U+5A "Z" */
    0x7f, 0x7, 0x6, 0xe, 0xc, 0x1c, 0x18, 0x38,
    0x30, 0x70, 0x60, 0xe0, 0xff,

    /* U+5B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
    0xf0,

    /* U+5C "\\" */
    0xcc, 0x44, 0x66, 0x66, 0x22, 0x33, 0x30,

    /* U+5D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    0xf0,

    /* U+5E "^" */
    0x1c, 0x1c, 0x34, 0x36, 0x26, 0x62, 0x43, 0xc3,

    /* U+5F "_" */
    0xff,

    /* U+60 "`" */
    0xc6, 0x20,

    /* U+61 "a" */
    0x3c, 0x66, 0xc6, 0x6, 0x7e, 0xc6, 0xc6, 0xc6,
    0xce, 0x73,

    /* U+62 "b" */
    0xc1, 0x83, 0x6, 0xee, 0xd8, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1f, 0x6f, 0xc0,

    /* U+63 "c" */
    0x3c, 0xcf, 0x1e, 0xc, 0x18, 0x30, 0x63, 0x66,
    0x70,

    /* U+64 "d" */
    0x6, 0xc, 0x1b, 0xb7, 0xf9, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1b, 0x77, 0x60,

    /* U+65 "e" */
    0x38, 0xdb, 0x1e, 0x3f, 0xf8, 0x30, 0x62, 0x64,
    0x78,

    /* U+66 "f" */
    0x3b, 0x99, 0xf6, 0x31, 0x8c, 0x63, 0x18, 0xc6,
    0x0,

    /* U+67 "g" */
    0x7e, 0xdf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x6e,
    0xec, 0x1a, 0x36, 0xc7, 0x0,

    /* U+68 "h" */
    0xc1, 0x83, 0x6, 0xee, 0x78, 0xf1, 0xe3, 0xc7,
    0x8f, 0x1e, 0x3c, 0x60,

    /* U+69 "i" */
    0xc3, 0xff, 0xff, 0xc0,

    /* U+6A "j" */
    0x30, 0x3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x3f,
    0xe0,

    /* U+6B "k" */
    0xc1, 0x83, 0x6, 0x7c, 0xdb, 0x3e, 0x7c, 0xf9,
    0xb3, 0x36, 0x6c, 0x60,

    /* U+6C "l" */
    0xff, 0xff, 0xff, 0xc0,

    /* U+6D "m" */
    0xdc, 0xee, 0x73, 0xc6, 0x3c, 0x63, 0xc6, 0x3c,
    0x63, 0xc6, 0x3c, 0x63, 0xc6, 0x3c, 0x63,

    /* U+6E "n" */
    0xdd, 0xcf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xc7,
    0x8c,

    /* U+6F "o" */
    0x3c, 0x66, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3, 0xc3,
    0x66, 0x3c,

    /* U+70 "p" */
    0xdd, 0xdb, 0x1e, 0x3c, 0x78, 0xf1, 0xf7, 0xfd,
    0xbb, 0x6, 0xc, 0x18, 0x0,

    /* U+71 "q" */
    0x7e, 0xdf, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0x6e,
    0xec, 0x18, 0x30, 0x60, 0xc0,

    /* U+72 "r" */
    0xdf, 0x31, 0x8c, 0x63, 0x18, 0xc6, 0x0,

    /* U+73 "s" */
    0x7d, 0x8f, 0x7, 0x8f, 0xcf, 0xc7, 0x83, 0xc6,
    0xf8,

    /* U+74 "t" */
    0x26, 0x6f, 0x66, 0x66, 0x66, 0x67, 0x30,

    /* U+75 "u" */
    0xc7, 0x8f, 0x1e, 0x3c, 0x78, 0xf1, 0xe3, 0xce,
    0xec,

    /* U+76 "v" */
    0xc3, 0xe3, 0x66, 0x66, 0x66, 0x36, 0x3c, 0x3c,
    0x3c, 0x18,

    /* U+77 "w" */
    0xc6, 0x2c, 0xe6, 0xce, 0x64, 0xb6, 0x6b, 0x67,
    0xb4, 0x79, 0xc7, 0x9c, 0x31, 0xc3, 0x1c,

    /* U+78 "x" */
    0x67, 0x66, 0x3e, 0x3c, 0x18, 0x1c, 0x3c, 0x76,
    0x66, 0xe3,

    /* U+79 "y" */
    0xe3, 0x63, 0x63, 0x66, 0x36, 0x36, 0x34, 0x1c,
    0x1c, 0x1c, 0x18, 0x18, 0x78, 0x70,

    /* U+7A "z" */
    0xfc, 0x71, 0x86, 0x30, 0xc6, 0x18, 0xc3, 0xf0,

    /* U+7B "{" */
    0x1c, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0xc0, 0xc3,
    0xc, 0x30, 0xc3, 0xc, 0x1c,

    /* U+7C "|" */
    0xff, 0xff, 0xff, 0xff, 0xc0,

    /* U+7D "}" */
    0xe0, 0xc3, 0xc, 0x30, 0xc3, 0xc, 0xc, 0xc3,
    0xc, 0x30, 0xc3, 0xc, 0xe0,

    /* U+7E "~" */
    0xf0, 0x3c
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 66, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 79, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 112, .box_w = 5, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 8, .adv_w = 131, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 21, .adv_w = 131, .box_w = 8, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 36, .adv_w = 210, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 56, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = 9},
    {.bitmap_index = 76, .adv_w = 79, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 85, .adv_w = 79, .box_w = 4, .box_h = 17, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 94, .adv_w = 92, .box_w = 6, .box_h = 7, .ofs_x = 0, .ofs_y = 6},
    {.bitmap_index = 100, .adv_w = 138, .box_w = 7, .box_h = 9, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 108, .adv_w = 66, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 110, .adv_w = 79, .box_w = 4, .box_h = 1, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 111, .adv_w = 66, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 112, .adv_w = 66, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 119, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 131, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 155, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 131, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 180, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 204, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 240, .adv_w = 79, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 243, .adv_w = 79, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 247, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 257, .adv_w = 138, .box_w = 7, .box_h = 5, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 262, .adv_w = 138, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 272, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 285, .adv_w = 230, .box_w = 13, .box_h = 15, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 310, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 327, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 342, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 359, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 374, .adv_w = 158, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 389, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 402, .adv_w = 184, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 419, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 434, .adv_w = 66, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 438, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 450, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 465, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 478, .adv_w = 197, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 495, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 510, .adv_w = 184, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 527, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 540, .adv_w = 184, .box_w = 10, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 562, .adv_w = 170, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 579, .adv_w = 158, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 592, .adv_w = 144, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 607, .adv_w = 170, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 158, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 639, .adv_w = 223, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 662, .adv_w = 158, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 679, .adv_w = 158, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 696, .adv_w = 144, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 709, .adv_w = 79, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 718, .adv_w = 66, .box_w = 4, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 725, .adv_w = 79, .box_w = 4, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 734, .adv_w = 138, .box_w = 8, .box_h = 8, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 742, .adv_w = 131, .box_w = 8, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 743, .adv_w = 79, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 11},
    {.bitmap_index = 745, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 755, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 767, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 776, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 788, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 797, .adv_w = 79, .box_w = 5, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 806, .adv_w = 144, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 819, .adv_w = 144, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 831, .adv_w = 66, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 835, .adv_w = 66, .box_w = 4, .box_h = 17, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 844, .adv_w = 131, .box_w = 7, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 856, .adv_w = 66, .box_w = 2, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 860, .adv_w = 210, .box_w = 12, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 875, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 884, .adv_w = 144, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 894, .adv_w = 144, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 907, .adv_w = 144, .box_w = 7, .box_h = 14, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 920, .adv_w = 92, .box_w = 5, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 927, .adv_w = 131, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 936, .adv_w = 79, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 943, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 952, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 962, .adv_w = 184, .box_w = 12, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 977, .adv_w = 131, .box_w = 8, .box_h = 10, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 987, .adv_w = 131, .box_w = 8, .box_h = 14, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1001, .adv_w = 118, .box_w = 6, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1009, .adv_w = 92, .box_w = 6, .box_h = 17, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1022, .adv_w = 66, .box_w = 2, .box_h = 17, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 1027, .adv_w = 92, .box_w = 6, .box_h = 17, .ofs_x = 0, .ofs_y = -4},
    {.bitmap_index = 1040, .adv_w = 138, .box_w = 7, .box_h = 2, .ofs_x = 1, .ofs_y = 5}
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
    51, 55,
    51, 56,
    51, 58,
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
    56, 74,
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
    -9, -4, -13, -9, -17, -17, -13, -22,
    -9, -4, -9, -26, -26, -13, -4, -17,
    -17, -13, -22, -9, -4, -30, -30, -17,
    -4, -4, -9, -26, -13, -26, -26, -26,
    -17, -4, -17, -17, -17, -4, -17, -13,
    -17, -17, -17, -17, -22, -13, -22, -13,
    -13, -17, -13, -13, -4, -17, -13, -9,
    -9, -13, -5, -13, -4, -4, -13, -9,
    -4, -2, -4, -4, -4, -4, -4, -26,
    -13, -26, -17, -17, -22, -13, -13, -9,
    -17, -13, -17, -13, -13, -13, -13, -17,
    -17, -9, -9, -17, -17
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 93,
    .glyph_ids_size = 0
};

/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

/*Store all the custom data of the font*/
static lv_font_fmt_txt_dsc_t font_dsc = {
    .glyph_bitmap = gylph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = &kern_pairs,
    .kern_scale = 16,
    .cmap_num = 1,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
lv_font_t liberation18bn = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 18,          /*The maximum line height required by the font*/
    .base_line = 4,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = 0,
    .underline_thickness = 2,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if LIBERATION18BN*/

