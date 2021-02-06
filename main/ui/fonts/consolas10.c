#include "lvgl.h"

/*******************************************************************************
 * Size: 10 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef CONSOLAS10
#define CONSOLAS10 1
#endif

#if CONSOLAS10

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
    0xb4,

    /* U+23 "#" */
    0x57, 0xd5, 0xf5, 0x28,

    /* U+24 "$" */
    0x23, 0xa8, 0xc5, 0x2b, 0xc8,

    /* U+25 "%" */
    0xcd, 0xb4, 0x45, 0xb6, 0x60,

    /* U+26 "&" */
    0x71, 0x45, 0x18, 0xaa, 0x4e, 0x80,

    /* U+27 "'" */
    0xc0,

    /* U+28 "(" */
    0x2a, 0x49, 0x22, 0x20,

    /* U+29 ")" */
    0x88, 0x92, 0x4a, 0x80,

    /* U+2A "*" */
    0x23, 0x9c, 0x40,

    /* U+2B "+" */
    0x27, 0xc8, 0x40,

    /* U+2C "," */
    0x16,

    /* U+2D "-" */
    0xe0,

    /* U+2E "." */
    0xc0,

    /* U+2F "/" */
    0x12, 0x24, 0x48, 0x88,

    /* U+30 "0" */
    0x74, 0x67, 0xd8, 0xb8,

    /* U+31 "1" */
    0x6a, 0x22, 0x2f,

    /* U+32 "2" */
    0x79, 0x12, 0x4f,

    /* U+33 "3" */
    0xf1, 0x61, 0x1e,

    /* U+34 "4" */
    0x31, 0x95, 0x2f, 0x88,

    /* U+35 "5" */
    0xf8, 0xe1, 0x1e,

    /* U+36 "6" */
    0x68, 0xf9, 0x96,

    /* U+37 "7" */
    0xf1, 0x22, 0x44,

    /* U+38 "8" */
    0x7a, 0x5c, 0xbc, 0xb8,

    /* U+39 "9" */
    0x69, 0x9f, 0x1e,

    /* U+3A ":" */
    0xc0, 0xc0,

    /* U+3B ";" */
    0xc1, 0x60,

    /* U+3C "<" */
    0x2a, 0x22,

    /* U+3D "=" */
    0xf0, 0xf0,

    /* U+3E ">" */
    0xc2, 0x34, 0x80,

    /* U+3F "?" */
    0xe1, 0x17, 0x40, 0x40,

    /* U+40 "@" */
    0x39, 0x3f, 0x75, 0xd7, 0x5f, 0xb0, 0x70,

    /* U+41 "A" */
    0x32, 0x94, 0x97, 0xc4,

    /* U+42 "B" */
    0xe9, 0xe9, 0x9e,

    /* U+43 "C" */
    0x7c, 0x88, 0xc7,

    /* U+44 "D" */
    0xf4, 0xe3, 0x19, 0xf8,

    /* U+45 "E" */
    0xf8, 0xf8, 0x8f,

    /* U+46 "F" */
    0xf8, 0xf8, 0x88,

    /* U+47 "G" */
    0x7e, 0x27, 0x1c, 0xbc,

    /* U+48 "H" */
    0x99, 0xf9, 0x99,

    /* U+49 "I" */
    0xe9, 0x25, 0xc0,

    /* U+4A "J" */
    0x71, 0x11, 0x1e,

    /* U+4B "K" */
    0x9a, 0xcc, 0xa9,

    /* U+4C "L" */
    0x88, 0x88, 0x8f,

    /* U+4D "M" */
    0xde, 0xfb, 0x58, 0xc4,

    /* U+4E "N" */
    0x9d, 0xdb, 0xb9,

    /* U+4F "O" */
    0x74, 0x63, 0x18, 0xb8,

    /* U+50 "P" */
    0xe9, 0x9e, 0x88,

    /* U+51 "Q" */
    0x76, 0xe3, 0x18, 0xc5, 0xc4, 0x18,

    /* U+52 "R" */
    0xf9, 0xea, 0x99,

    /* U+53 "S" */
    0x74, 0x10, 0x61, 0xf8,

    /* U+54 "T" */
    0xf9, 0x8, 0x42, 0x10,

    /* U+55 "U" */
    0x8c, 0x63, 0x18, 0xb8,

    /* U+56 "V" */
    0x8a, 0x52, 0xa3, 0x18,

    /* U+57 "W" */
    0x8c, 0x6b, 0xdd, 0xec,

    /* U+58 "X" */
    0x4a, 0x8c, 0x65, 0x64,

    /* U+59 "Y" */
    0x8a, 0x94, 0x42, 0x10,

    /* U+5A "Z" */
    0xf8, 0x88, 0x84, 0x7c,

    /* U+5B "[" */
    0xf2, 0x49, 0x24, 0xe0,

    /* U+5C "\\" */
    0x88, 0x44, 0x42, 0x21,

    /* U+5D "]" */
    0xe4, 0x92, 0x49, 0xe0,

    /* U+5E "^" */
    0x4a, 0x90,

    /* U+5F "_" */
    0xfc,

    /* U+60 "`" */
    0x20,

    /* U+61 "a" */
    0xf1, 0xf9, 0xf0,

    /* U+62 "b" */
    0x88, 0xe9, 0x99, 0xe0,

    /* U+63 "c" */
    0x78, 0x88, 0x70,

    /* U+64 "d" */
    0x11, 0x79, 0x99, 0x70,

    /* U+65 "e" */
    0x74, 0xbf, 0x7, 0x0,

    /* U+66 "f" */
    0x19, 0x9, 0xf2, 0x10, 0x80,

    /* U+67 "g" */
    0x7a, 0x9d, 0x7, 0x4b, 0xc0,

    /* U+68 "h" */
    0x88, 0xf9, 0x99, 0x90,

    /* U+69 "i" */
    0x20, 0x62, 0x22, 0xf0,

    /* U+6A "j" */
    0x10, 0x71, 0x11, 0x11, 0xe0,

    /* U+6B "k" */
    0x88, 0x9a, 0xca, 0x90,

    /* U+6C "l" */
    0x62, 0x22, 0x22, 0xf0,

    /* U+6D "m" */
    0xfd, 0x6b, 0x5a, 0x80,

    /* U+6E "n" */
    0xf9, 0x99, 0x90,

    /* U+6F "o" */
    0x74, 0x63, 0x17, 0x0,

    /* U+70 "p" */
    0xe9, 0x99, 0xe8, 0x80,

    /* U+71 "q" */
    0x79, 0x99, 0x71, 0x10,

    /* U+72 "r" */
    0xbd, 0x88, 0x80,

    /* U+73 "s" */
    0xe8, 0x61, 0xe0,

    /* U+74 "t" */
    0x4, 0xf4, 0x44, 0x70,

    /* U+75 "u" */
    0x99, 0x99, 0xf0,

    /* U+76 "v" */
    0x8a, 0x54, 0x62, 0x0,

    /* U+77 "w" */
    0x8d, 0x6b, 0xb5, 0x80,

    /* U+78 "x" */
    0x49, 0x88, 0xa4, 0x80,

    /* U+79 "y" */
    0x4a, 0x54, 0x62, 0x13, 0x0,

    /* U+7A "z" */
    0xf2, 0x24, 0xf0,

    /* U+7B "{" */
    0x69, 0x28, 0x92, 0x60,

    /* U+7C "|" */
    0xff, 0xc0,

    /* U+7D "}" */
    0xc9, 0x22, 0x92, 0xc0,

    /* U+7E "~" */
    0x6c, 0xc0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 88, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 88, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 88, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 3, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 7, .adv_w = 88, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 12, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 17, .adv_w = 88, .box_w = 6, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 23, .adv_w = 88, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 5},
    {.bitmap_index = 24, .adv_w = 88, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 88, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 32, .adv_w = 88, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 35, .adv_w = 88, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},
    {.bitmap_index = 38, .adv_w = 88, .box_w = 2, .box_h = 4, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 39, .adv_w = 88, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 40, .adv_w = 88, .box_w = 2, .box_h = 1, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 88, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 45, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 49, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 52, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 65, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 68, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 71, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 75, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 78, .adv_w = 88, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 88, .box_w = 2, .box_h = 6, .ofs_x = 2, .ofs_y = -1},
    {.bitmap_index = 82, .adv_w = 88, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 84, .adv_w = 88, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 86, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 89, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 93, .adv_w = 88, .box_w = 6, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 100, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 104, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 114, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 117, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 120, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 124, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 127, .adv_w = 88, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 130, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 133, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 136, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 143, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 146, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 150, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 153, .adv_w = 88, .box_w = 5, .box_h = 9, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 159, .adv_w = 88, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 162, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 166, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 170, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 178, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 182, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 190, .adv_w = 88, .box_w = 5, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 194, .adv_w = 88, .box_w = 3, .box_h = 9, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 198, .adv_w = 88, .box_w = 4, .box_h = 8, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 202, .adv_w = 88, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 206, .adv_w = 88, .box_w = 4, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 208, .adv_w = 88, .box_w = 6, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 209, .adv_w = 88, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 5},
    {.bitmap_index = 210, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 213, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 217, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 224, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 228, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 233, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 238, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 242, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 246, .adv_w = 88, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 251, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 255, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 263, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 266, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 270, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 274, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 278, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 281, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 284, .adv_w = 88, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 288, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 291, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 295, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 299, .adv_w = 88, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 303, .adv_w = 88, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 308, .adv_w = 88, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 311, .adv_w = 88, .box_w = 3, .box_h = 9, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 315, .adv_w = 88, .box_w = 1, .box_h = 10, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 317, .adv_w = 88, .box_w = 3, .box_h = 9, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 321, .adv_w = 88, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 2}
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
lv_font_t consolas10 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
    .base_line = 3,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if CONSOLAS10*/

