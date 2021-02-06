#include "lvgl.h"

/*******************************************************************************
 * Size: 8 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef CONSOLAS8
#define CONSOLAS8 1
#endif

#if CONSOLAS8

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xf4,

    /* U+22 "\"" */
    0xf0,

    /* U+23 "#" */
    0x6f, 0x6f, 0x60,

    /* U+24 "$" */
    0x5f, 0x6b, 0xe0,

    /* U+25 "%" */
    0xde, 0x25, 0x7b,

    /* U+26 "&" */
    0x6a, 0x6d, 0xbf,

    /* U+27 "'" */
    0xc0,

    /* U+28 "(" */
    0xa, 0x49, 0x10,

    /* U+29 ")" */
    0x8, 0x92, 0x50,

    /* U+2A "*" */
    0x4d, 0x0,

    /* U+2B "+" */
    0x27, 0xc8, 0x40,

    /* U+2C "," */
    0x58,

    /* U+2D "-" */
    0xc0,

    /* U+2E "." */
    0x80,

    /* U+2F "/" */
    0x12, 0x24, 0x44, 0x80,

    /* U+30 "0" */
    0x69, 0xf9, 0x60,

    /* U+31 "1" */
    0xc9, 0x2e,

    /* U+32 "2" */
    0xe4, 0xae,

    /* U+33 "3" */
    0xe2, 0x43, 0xe0,

    /* U+34 "4" */
    0x32, 0x95, 0xf1, 0x0,

    /* U+35 "5" */
    0xf3, 0x1c,

    /* U+36 "6" */
    0x68, 0xea, 0xe0,

    /* U+37 "7" */
    0xe5, 0x28,

    /* U+38 "8" */
    0x79, 0x69, 0x70,

    /* U+39 "9" */
    0xea, 0x72, 0xe0,

    /* U+3A ":" */
    0x90,

    /* U+3B ";" */
    0x41, 0x60,

    /* U+3C "<" */
    0x52, 0x20,

    /* U+3D "=" */
    0xfc,

    /* U+3E ">" */
    0x89, 0x40,

    /* U+3F "?" */
    0x44, 0xa5, 0x0,

    /* U+40 "@" */
    0x32, 0x63, 0x7e, 0xda, 0xe,

    /* U+41 "A" */
    0x26, 0x57, 0x90,

    /* U+42 "B" */
    0xf7, 0x5e,

    /* U+43 "C" */
    0x78, 0x88, 0x70,

    /* U+44 "D" */
    0xe9, 0x99, 0xe0,

    /* U+45 "E" */
    0xf3, 0xce,

    /* U+46 "F" */
    0xf3, 0xc8,

    /* U+47 "G" */
    0x78, 0xb9, 0x70,

    /* U+48 "H" */
    0x99, 0xf9, 0x90,

    /* U+49 "I" */
    0xe9, 0x2e,

    /* U+4A "J" */
    0xe4, 0x9e,

    /* U+4B "K" */
    0xac, 0xca, 0xa0,

    /* U+4C "L" */
    0x92, 0x4e,

    /* U+4D "M" */
    0x9f, 0xd9, 0x90,

    /* U+4E "N" */
    0x9d, 0xdb, 0x90,

    /* U+4F "O" */
    0x69, 0x99, 0x60,

    /* U+50 "P" */
    0xf7, 0x48,

    /* U+51 "Q" */
    0x69, 0x99, 0x96, 0x30,

    /* U+52 "R" */
    0xea, 0xea, 0x90,

    /* U+53 "S" */
    0xe8, 0x62, 0xe0,

    /* U+54 "T" */
    0xf9, 0x8, 0x42, 0x0,

    /* U+55 "U" */
    0x99, 0x99, 0xe0,

    /* U+56 "V" */
    0x99, 0x56, 0x20,

    /* U+57 "W" */
    0x99, 0xdf, 0xb0,

    /* U+58 "X" */
    0x96, 0x26, 0x90,

    /* U+59 "Y" */
    0x8a, 0x88, 0x42, 0x0,

    /* U+5A "Z" */
    0xf2, 0x48, 0xf0,

    /* U+5B "[" */
    0xea, 0xab,

    /* U+5C "\\" */
    0x92, 0x24, 0x48,

    /* U+5D "]" */
    0xd5, 0x57,

    /* U+5E "^" */
    0x6, 0x90,

    /* U+5F "_" */
    0xf0,

    /* U+60 "`" */
    0x40,

    /* U+61 "a" */
    0xee, 0xf0,

    /* U+62 "b" */
    0x88, 0xf9, 0x9e,

    /* U+63 "c" */
    0x72, 0x30,

    /* U+64 "d" */
    0x27, 0xdb, 0xc0,

    /* U+65 "e" */
    0x6f, 0x86,

    /* U+66 "f" */
    0x74, 0xf4, 0x44,

    /* U+67 "g" */
    0x79, 0x66, 0x97,

    /* U+68 "h" */
    0x93, 0xdb, 0x40,

    /* U+69 "i" */
    0x43, 0x25, 0xc0,

    /* U+6A "j" */
    0x23, 0x92, 0x4f,

    /* U+6B "k" */
    0x88, 0xac, 0xca,

    /* U+6C "l" */
    0xc9, 0x25, 0xc0,

    /* U+6D "m" */
    0xff, 0xf0,

    /* U+6E "n" */
    0xf6, 0xd0,

    /* U+6F "o" */
    0x69, 0x96,

    /* U+70 "p" */
    0xf9, 0x9e, 0x88,

    /* U+71 "q" */
    0x79, 0x9f, 0x11,

    /* U+72 "r" */
    0xf6, 0x40,

    /* U+73 "s" */
    0xd1, 0xf0,

    /* U+74 "t" */
    0x4f, 0x44, 0x70,

    /* U+75 "u" */
    0xb6, 0xf0,

    /* U+76 "v" */
    0x95, 0x62,

    /* U+77 "w" */
    0x9b, 0xf5,

    /* U+78 "x" */
    0x56, 0x65,

    /* U+79 "y" */
    0x95, 0x62, 0x4c,

    /* U+7A "z" */
    0xe9, 0x70,

    /* U+7B "{" */
    0x69, 0x28, 0x93,

    /* U+7C "|" */
    0xff,

    /* U+7D "}" */
    0xc9, 0x22, 0x96,

    /* U+7E "~" */
    0x5b
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 70, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 70, .box_w = 1, .box_h = 6, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 2, .adv_w = 70, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},
    {.bitmap_index = 3, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 6, .adv_w = 70, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 9, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 12, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 15, .adv_w = 70, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 4},
    {.bitmap_index = 16, .adv_w = 70, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 19, .adv_w = 70, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 22, .adv_w = 70, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},
    {.bitmap_index = 24, .adv_w = 70, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 27, .adv_w = 70, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 28, .adv_w = 70, .box_w = 2, .box_h = 1, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 29, .adv_w = 70, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 30, .adv_w = 70, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 34, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 37, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 39, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 41, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 44, .adv_w = 70, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 48, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 50, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 53, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 55, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 58, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 61, .adv_w = 70, .box_w = 1, .box_h = 4, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 62, .adv_w = 70, .box_w = 2, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 64, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 66, .adv_w = 70, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 1},
    {.bitmap_index = 67, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 69, .adv_w = 70, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 72, .adv_w = 70, .box_w = 5, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 77, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 80, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 82, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 85, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 88, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 90, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 92, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 95, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 98, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 100, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 102, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 105, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 107, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 110, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 113, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 116, .adv_w = 70, .box_w = 3, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 118, .adv_w = 70, .box_w = 4, .box_h = 7, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 122, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 125, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 128, .adv_w = 70, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 132, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 135, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 138, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 141, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 70, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 148, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 151, .adv_w = 70, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 153, .adv_w = 70, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 156, .adv_w = 70, .box_w = 2, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 158, .adv_w = 70, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 3},
    {.bitmap_index = 160, .adv_w = 70, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 161, .adv_w = 70, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 4},
    {.bitmap_index = 162, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 164, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 167, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 169, .adv_w = 70, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 172, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 174, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 177, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 180, .adv_w = 70, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 183, .adv_w = 70, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 186, .adv_w = 70, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 189, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 192, .adv_w = 70, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 195, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 197, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 199, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 204, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 207, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 209, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 211, .adv_w = 70, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 216, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 218, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 220, .adv_w = 70, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 222, .adv_w = 70, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 225, .adv_w = 70, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 227, .adv_w = 70, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 230, .adv_w = 70, .box_w = 1, .box_h = 8, .ofs_x = 2, .ofs_y = -2},
    {.bitmap_index = 231, .adv_w = 70, .box_w = 3, .box_h = 8, .ofs_x = 1, .ofs_y = -2},
    {.bitmap_index = 234, .adv_w = 70, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1}
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
lv_font_t consolas8 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 8,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if CONSOLAS8*/

