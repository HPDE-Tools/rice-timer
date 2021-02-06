#include "lvgl.h"

/*******************************************************************************
 * Size: 18 px
 * Bpp: 1
 * Opts: 
 ******************************************************************************/

#ifndef CAECILIA18
#define CAECILIA18 1
#endif

#if CAECILIA18

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t gylph_bitmap[] = {
    /* U+20 " " */
    0x0,

    /* U+21 "!" */
    0xff, 0xff, 0xf0, 0x3c,

    /* U+22 "\"" */
    0xde, 0xf7, 0xbd, 0x80,

    /* U+23 "#" */
    0x9, 0x84, 0x82, 0x43, 0x27, 0xf8, 0x90, 0x48,
    0x24, 0xff, 0x93, 0x9, 0x4, 0x86, 0x40,

    /* U+24 "$" */
    0x8, 0x4, 0x2, 0x7, 0xf6, 0x9e, 0x4f, 0x21,
    0x90, 0x78, 0x1f, 0x2, 0xe1, 0x30, 0x9e, 0x4f,
    0x2d, 0xfc, 0x8, 0x4, 0x2, 0x0,

    /* U+25 "%" */
    0x0, 0x0, 0x0, 0x87, 0x84, 0x33, 0x10, 0xcc,
    0x83, 0x32, 0x7, 0x90, 0x0, 0xc0, 0x2, 0x0,
    0x19, 0xe0, 0x58, 0xc3, 0x63, 0x9, 0x8c, 0x46,
    0x31, 0x7, 0x0, 0x0,

    /* U+26 "&" */
    0x3c, 0x2, 0x60, 0x66, 0x6, 0x60, 0x2c, 0x1,
    0xf, 0x78, 0x46, 0x44, 0xc2, 0xcc, 0x38, 0xc1,
    0x86, 0x1c, 0x3e, 0x30,

    /* U+27 "'" */
    0xff, 0xc0,

    /* U+28 "(" */
    0x10, 0x8c, 0xc6, 0x33, 0x18, 0xc6, 0x31, 0x8c,
    0x61, 0x8c, 0x61, 0x8c, 0x30,

    /* U+29 ")" */
    0x42, 0x18, 0x63, 0x18, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0xc6, 0x33, 0x11, 0x80,

    /* U+2A "*" */
    0x11, 0x57, 0x9e, 0x54, 0x40,

    /* U+2B "+" */
    0x8, 0x4, 0x2, 0x1, 0x0, 0x87, 0xfc, 0x20,
    0x10, 0x8, 0x4, 0x0,

    /* U+2C "," */
    0xdd, 0xbc, 0x0,

    /* U+2D "-" */
    0xf8,

    /* U+2E "." */
    0xf0,

    /* U+2F "/" */
    0x2, 0x2, 0x2, 0x6, 0x4, 0xc, 0x8, 0x8,
    0x18, 0x10, 0x10, 0x30, 0x20, 0x60, 0x40, 0x40,

    /* U+30 "0" */
    0x1c, 0x31, 0x98, 0xd8, 0x3c, 0x1e, 0xf, 0x7,
    0x83, 0xc1, 0xe0, 0xd8, 0xcc, 0x63, 0xc0,

    /* U+31 "1" */
    0x18, 0x78, 0xd8, 0x98, 0x18, 0x18, 0x18, 0x18,
    0x18, 0x18, 0x18, 0x18, 0x7f,

    /* U+32 "2" */
    0x3c, 0x46, 0xc3, 0x83, 0x3, 0x7, 0x6, 0xe,
    0x1c, 0x18, 0x30, 0x60, 0xff,

    /* U+33 "3" */
    0x3e, 0xc7, 0x83, 0x3, 0x6, 0x38, 0x6, 0x3,
    0x3, 0x3, 0x3, 0x86, 0xfc,

    /* U+34 "4" */
    0x6, 0x3, 0x81, 0xe0, 0x58, 0x26, 0x9, 0x84,
    0x63, 0x18, 0xff, 0xc1, 0x80, 0x60, 0x18, 0xf,
    0x0,

    /* U+35 "5" */
    0x7e, 0x60, 0x60, 0x60, 0x60, 0x7c, 0xe, 0x3,
    0x3, 0x3, 0x3, 0x86, 0xfc,

    /* U+36 "6" */
    0xf, 0x98, 0x18, 0xc, 0xc, 0x6, 0xf3, 0x8d,
    0x83, 0xc1, 0xe0, 0xd8, 0x6c, 0x61, 0xe0,

    /* U+37 "7" */
    0xff, 0x3, 0x2, 0x6, 0x4, 0xc, 0x8, 0x18,
    0x10, 0x30, 0x20, 0x60, 0x40,

    /* U+38 "8" */
    0x3c, 0x73, 0xb0, 0xd8, 0x6e, 0x73, 0xe0, 0x70,
    0xce, 0xc1, 0xe0, 0xf0, 0x7c, 0x63, 0xe0,

    /* U+39 "9" */
    0x3c, 0x31, 0xb0, 0xd8, 0x3c, 0x1e, 0xd, 0x8e,
    0x7b, 0x1, 0x81, 0x80, 0xc1, 0xcf, 0x80,

    /* U+3A ":" */
    0xf0, 0x0, 0xf0,

    /* U+3B ";" */
    0xfc, 0x0, 0x0, 0xed, 0xa8,

    /* U+3C "<" */
    0x0, 0x81, 0xc3, 0x87, 0xe, 0x6, 0x1, 0xc0,
    0x18, 0x3, 0x0, 0x40,

    /* U+3D "=" */
    0xff, 0x80, 0x0, 0x0, 0xf, 0xf8,

    /* U+3E ">" */
    0x0, 0x70, 0xe, 0x1, 0xc0, 0x38, 0xc, 0x1c,
    0x38, 0x60, 0x40, 0x0,

    /* U+3F "?" */
    0xf8, 0x18, 0x18, 0x30, 0x61, 0x86, 0x18, 0x40,
    0x81, 0x0, 0x0, 0xc, 0x18, 0x0,

    /* U+40 "@" */
    0xf, 0xc1, 0xc3, 0x1b, 0xcc, 0xf3, 0xbd, 0x89,
    0xf8, 0x4f, 0xc2, 0x7e, 0x36, 0xf3, 0x33, 0xee,
    0x18, 0xc, 0x70, 0xc0, 0xf8, 0x0,

    /* U+41 "A" */
    0x3, 0x0, 0x38, 0x1, 0x60, 0x1b, 0x0, 0x88,
    0x4, 0x60, 0x63, 0x3, 0xf8, 0x30, 0x61, 0x3,
    0x8, 0x8, 0xc0, 0x6f, 0x7, 0x80,

    /* U+42 "B" */
    0xff, 0xc, 0xe3, 0x18, 0xc6, 0x31, 0x8c, 0xc3,
    0xe0, 0xc6, 0x30, 0xcc, 0x33, 0xc, 0xc6, 0xff,
    0x0,

    /* U+43 "C" */
    0xf, 0xce, 0x16, 0x5, 0x80, 0xc0, 0x30, 0xc,
    0x3, 0x0, 0xc0, 0x38, 0x6, 0x4, 0xe1, 0xf,
    0xc0,

    /* U+44 "D" */
    0xff, 0x81, 0x83, 0xc, 0xc, 0x60, 0x73, 0x1,
    0x98, 0xc, 0xc0, 0x66, 0x3, 0x30, 0x19, 0x81,
    0x8c, 0xc, 0x61, 0xcf, 0xf8, 0x0,

    /* U+45 "E" */
    0xff, 0x63, 0x63, 0x60, 0x60, 0x60, 0x7c, 0x60,
    0x60, 0x60, 0x63, 0x63, 0xff,

    /* U+46 "F" */
    0xff, 0xb0, 0xd8, 0x6c, 0x6, 0x3, 0x1, 0xf8,
    0xc0, 0x60, 0x30, 0x18, 0xc, 0xf, 0x80,

    /* U+47 "G" */
    0xf, 0xe3, 0x6, 0x60, 0x66, 0x0, 0xc0, 0xc,
    0x0, 0xc0, 0xc, 0xf, 0xc0, 0x66, 0x6, 0x60,
    0x63, 0x86, 0xf, 0xe0,

    /* U+48 "H" */
    0xf0, 0xf6, 0x6, 0x60, 0x66, 0x6, 0x60, 0x66,
    0x6, 0x7f, 0xe6, 0x6, 0x60, 0x66, 0x6, 0x60,
    0x66, 0x6, 0xf0, 0xf0,

    /* U+49 "I" */
    0xf6, 0x66, 0x66, 0x66, 0x66, 0x66, 0xf0,

    /* U+4A "J" */
    0x3c, 0x61, 0x86, 0x18, 0x61, 0x86, 0x18, 0x61,
    0x86, 0x18, 0xc7, 0x30, 0x0,

    /* U+4B "K" */
    0xf1, 0xec, 0x11, 0x84, 0x31, 0x6, 0x40, 0xd0,
    0x1e, 0x3, 0x60, 0x66, 0xc, 0x61, 0x86, 0x30,
    0x6f, 0x1e,

    /* U+4C "L" */
    0xf0, 0x30, 0x18, 0xc, 0x6, 0x3, 0x1, 0x80,
    0xc0, 0x60, 0x30, 0x18, 0x6c, 0x3f, 0xf8,

    /* U+4D "M" */
    0xf0, 0x1e, 0x60, 0x38, 0xc0, 0x71, 0xc1, 0xe2,
    0x82, 0xc5, 0x5, 0x8b, 0x1b, 0x12, 0x26, 0x26,
    0xcc, 0x4d, 0x18, 0x8a, 0x31, 0x1c, 0x6f, 0x11,
    0xe0,

    /* U+4E "N" */
    0xe0, 0x79, 0x81, 0x8e, 0xc, 0x50, 0x62, 0xc3,
    0x13, 0x18, 0x88, 0xc4, 0x66, 0x21, 0xb1, 0x5,
    0x88, 0x3c, 0x40, 0xef, 0x3, 0x0,

    /* U+4F "O" */
    0x1f, 0x83, 0xc, 0x60, 0x66, 0x6, 0xc0, 0x3c,
    0x3, 0xc0, 0x3c, 0x3, 0xc0, 0x3e, 0x6, 0x60,
    0x63, 0xc, 0x1f, 0x80,

    /* U+50 "P" */
    0xfe, 0x31, 0x98, 0x6c, 0x36, 0x1b, 0xd, 0x8c,
    0xfc, 0x60, 0x30, 0x18, 0xc, 0xf, 0x80,

    /* U+51 "Q" */
    0x1f, 0x80, 0xc3, 0x6, 0x6, 0x18, 0x18, 0xc0,
    0x33, 0x0, 0xcc, 0x3, 0x30, 0xc, 0xc0, 0x31,
    0x81, 0x86, 0x6, 0xc, 0x30, 0x1f, 0x80, 0x6,
    0x0, 0x6, 0x0, 0x7,

    /* U+52 "R" */
    0xfe, 0xc, 0x71, 0x86, 0x30, 0xc6, 0x18, 0xc6,
    0x1f, 0x3, 0x30, 0x62, 0xc, 0x21, 0x86, 0x30,
    0x4f, 0xe,

    /* U+53 "S" */
    0x3f, 0x31, 0xb0, 0xd8, 0xe, 0x3, 0xc0, 0xfc,
    0xf, 0x1, 0x80, 0xf0, 0x78, 0x6f, 0xe0,

    /* U+54 "T" */
    0xff, 0xfc, 0x63, 0xc6, 0x30, 0x60, 0x6, 0x0,
    0x60, 0x6, 0x0, 0x60, 0x6, 0x0, 0x60, 0x6,
    0x0, 0x60, 0xf, 0x0,

    /* U+55 "U" */
    0xf0, 0xf6, 0x6, 0x60, 0x66, 0x6, 0x60, 0x66,
    0x6, 0x60, 0x66, 0x6, 0x60, 0x66, 0x6, 0x60,
    0x63, 0xc, 0x1f, 0x80,

    /* U+56 "V" */
    0xf0, 0x7b, 0x1, 0x88, 0x8, 0x60, 0xc3, 0x6,
    0x8, 0x20, 0x63, 0x3, 0x10, 0x8, 0x80, 0x6c,
    0x1, 0x40, 0xe, 0x0, 0x70, 0x0,

    /* U+57 "W" */
    0xf1, 0xe1, 0xec, 0x18, 0x18, 0x81, 0x2, 0x10,
    0x20, 0x43, 0x6, 0x18, 0x21, 0x42, 0x4, 0x28,
    0x40, 0xcd, 0x98, 0x9, 0x12, 0x1, 0x22, 0x40,
    0x3c, 0x78, 0x7, 0xe, 0x0, 0x60, 0xc0,

    /* U+58 "X" */
    0xf9, 0xe6, 0x18, 0xc6, 0xc, 0x80, 0xb0, 0x1c,
    0x1, 0x80, 0x70, 0x1b, 0x2, 0x20, 0xc6, 0x30,
    0x6f, 0x1e,

    /* U+59 "Y" */
    0xf0, 0x7b, 0x3, 0xc, 0x18, 0x31, 0x81, 0x98,
    0x6, 0x80, 0x3c, 0x0, 0xc0, 0x6, 0x0, 0x30,
    0x1, 0x80, 0xc, 0x0, 0xf0, 0x0,

    /* U+5A "Z" */
    0x7f, 0xec, 0x1d, 0x87, 0x0, 0xc0, 0x38, 0xe,
    0x1, 0x80, 0x60, 0x1c, 0x7, 0x0, 0xc1, 0xb8,
    0x3f, 0xfe,

    /* U+5B "[" */
    0xfc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc, 0xcc,
    0xcc, 0xcf,

    /* U+5C "\\" */
    0x1, 0x81, 0x2, 0x2, 0x4, 0xc, 0x8, 0x10,
    0x30, 0x20, 0x40, 0x40, 0x81, 0x81,

    /* U+5D "]" */
    0xf3, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33, 0x33,
    0x33, 0x3f,

    /* U+5E "^" */
    0x10, 0x70, 0xa3, 0x64, 0x58, 0xe0, 0x80,

    /* U+5F "_" */
    0xff, 0x80,

    /* U+60 "`" */
    0xc6, 0x31,

    /* U+61 "a" */
    0x7c, 0xc7, 0xc3, 0x3, 0x3f, 0xe3, 0xc3, 0xc3,
    0xc7, 0x7b,

    /* U+62 "b" */
    0xf0, 0x6, 0x0, 0xc0, 0x18, 0x3, 0x0, 0x6f,
    0xe, 0x31, 0x83, 0x30, 0x66, 0xc, 0xc1, 0x98,
    0x33, 0xc, 0x63, 0x8f, 0xc0,

    /* U+63 "c" */
    0x1f, 0x63, 0x43, 0xc0, 0xc0, 0xc0, 0xc0, 0x60,
    0x70, 0x1f,

    /* U+64 "d" */
    0x7, 0x80, 0x60, 0x18, 0x6, 0x1, 0x87, 0xe7,
    0x19, 0x86, 0xc1, 0xb0, 0x6c, 0x1b, 0x6, 0xc1,
    0x98, 0xe3, 0xdc,

    /* U+65 "e" */
    0x3e, 0x63, 0xc1, 0xc1, 0xff, 0xc0, 0xc0, 0xe0,
    0x61, 0x3f,

    /* U+66 "f" */
    0x1e, 0x61, 0x83, 0x6, 0x1f, 0x18, 0x30, 0x60,
    0xc1, 0x83, 0x6, 0xc, 0x3c, 0x0,

    /* U+67 "g" */
    0x3f, 0xb3, 0xb0, 0xd8, 0x6c, 0x33, 0x30, 0xf0,
    0x80, 0x60, 0x1f, 0x1b, 0xf8, 0x3c, 0x1f, 0x18,
    0xf8,

    /* U+68 "h" */
    0xe0, 0x18, 0x6, 0x1, 0x80, 0x60, 0x1b, 0xc7,
    0x39, 0x86, 0x61, 0x98, 0x66, 0x19, 0x86, 0x61,
    0x98, 0x6f, 0x3c,

    /* U+69 "i" */
    0x66, 0x0, 0xe, 0x66, 0x66, 0x66, 0x66, 0xf0,

    /* U+6A "j" */
    0x18, 0xc0, 0x0, 0x1c, 0x63, 0x18, 0xc6, 0x31,
    0x8c, 0x63, 0x31, 0xb9, 0x0,

    /* U+6B "k" */
    0xe0, 0x18, 0x6, 0x1, 0x80, 0x60, 0x19, 0xe6,
    0x31, 0x98, 0x68, 0x1c, 0x6, 0x81, 0x90, 0x62,
    0x18, 0xcf, 0x3c,

    /* U+6C "l" */
    0xe6, 0x66, 0x66, 0x66, 0x66, 0x66, 0x66, 0xf0,

    /* U+6D "m" */
    0xef, 0x3c, 0x73, 0xce, 0x61, 0x86, 0x61, 0x86,
    0x61, 0x86, 0x61, 0x86, 0x61, 0x86, 0x61, 0x86,
    0x61, 0x86, 0xf3, 0xcf,

    /* U+6E "n" */
    0xef, 0x1c, 0xe6, 0x19, 0x86, 0x61, 0x98, 0x66,
    0x19, 0x86, 0x61, 0xbc, 0xf0,

    /* U+6F "o" */
    0x3e, 0x31, 0x90, 0x78, 0x3c, 0x1e, 0xf, 0x7,
    0x82, 0x63, 0x1f, 0x0,

    /* U+70 "p" */
    0xef, 0x1c, 0x66, 0xd, 0x83, 0x60, 0xd8, 0x36,
    0xd, 0x86, 0x63, 0x9f, 0x86, 0x1, 0x80, 0x60,
    0x18, 0xf, 0x80,

    /* U+71 "q" */
    0x1f, 0x9c, 0x66, 0x1b, 0x6, 0xc1, 0xb0, 0x6c,
    0x1b, 0x6, 0x63, 0x8f, 0x60, 0x18, 0x6, 0x1,
    0x80, 0x60, 0x3c,

    /* U+72 "r" */
    0xee, 0xf1, 0xc3, 0x6, 0xc, 0x18, 0x30, 0x61,
    0xf0,

    /* U+73 "s" */
    0x7f, 0x8f, 0x1e, 0xf, 0x87, 0xc1, 0xe3, 0xc7,
    0xf0,

    /* U+74 "t" */
    0x61, 0x86, 0x3f, 0x61, 0x86, 0x18, 0x61, 0x86,
    0x18, 0x3c,

    /* U+75 "u" */
    0xe3, 0x98, 0x66, 0x19, 0x86, 0x61, 0x98, 0x66,
    0x19, 0x86, 0x73, 0x8f, 0x70,

    /* U+76 "v" */
    0xf3, 0xd8, 0x62, 0x10, 0xcc, 0x33, 0x4, 0x81,
    0x20, 0x78, 0xc, 0x3, 0x0,

    /* U+77 "w" */
    0xf7, 0x9e, 0xc6, 0x18, 0x84, 0x21, 0x18, 0xc3,
    0x39, 0x82, 0x52, 0x5, 0x24, 0xe, 0x70, 0xc,
    0x60, 0x10, 0xc0,

    /* U+78 "x" */
    0xf3, 0xcc, 0x43, 0x30, 0x78, 0xc, 0x3, 0x1,
    0x60, 0xcc, 0x61, 0xbc, 0xf0,

    /* U+79 "y" */
    0xf3, 0xd8, 0x62, 0x10, 0xc4, 0x33, 0x4, 0x81,
    0xa0, 0x78, 0xc, 0x3, 0x0, 0xc0, 0x20, 0x8,
    0x4, 0xe, 0x0,

    /* U+7A "z" */
    0xff, 0xc3, 0xc6, 0xc, 0x18, 0x18, 0x30, 0x61,
    0xe1, 0xff,

    /* U+7B "{" */
    0x36, 0x66, 0x66, 0x66, 0x66, 0x86, 0x66, 0x66,
    0x66, 0x63,

    /* U+7C "|" */
    0xff, 0xff, 0xf0,

    /* U+7D "}" */
    0xe1, 0x8c, 0x63, 0x18, 0xc6, 0x31, 0x82, 0x63,
    0x18, 0xc6, 0x31, 0x8d, 0xc0,

    /* U+7E "~" */
    0x79, 0x47, 0x80
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 1, .adv_w = 90, .box_w = 2, .box_h = 15, .ofs_x = 2, .ofs_y = 0},
    {.bitmap_index = 5, .adv_w = 128, .box_w = 5, .box_h = 5, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 9, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 24, .adv_w = 160, .box_w = 9, .box_h = 19, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 46, .adv_w = 240, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = -1},
    {.bitmap_index = 74, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 94, .adv_w = 80, .box_w = 2, .box_h = 5, .ofs_x = 2, .ofs_y = 10},
    {.bitmap_index = 96, .adv_w = 90, .box_w = 5, .box_h = 20, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 109, .adv_w = 90, .box_w = 5, .box_h = 20, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 122, .adv_w = 101, .box_w = 6, .box_h = 6, .ofs_x = 0, .ofs_y = 9},
    {.bitmap_index = 127, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 139, .adv_w = 80, .box_w = 3, .box_h = 6, .ofs_x = 1, .ofs_y = -4},
    {.bitmap_index = 142, .adv_w = 117, .box_w = 5, .box_h = 1, .ofs_x = 1, .ofs_y = 5},
    {.bitmap_index = 143, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 144, .adv_w = 107, .box_w = 8, .box_h = 16, .ofs_x = -1, .ofs_y = -1},
    {.bitmap_index = 160, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 175, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 188, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 201, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 214, .adv_w = 160, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 231, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 244, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 259, .adv_w = 160, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 272, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 287, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 302, .adv_w = 80, .box_w = 2, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 305, .adv_w = 80, .box_w = 3, .box_h = 13, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 310, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 322, .adv_w = 173, .box_w = 9, .box_h = 5, .ofs_x = 1, .ofs_y = 2},
    {.bitmap_index = 328, .adv_w = 173, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 340, .adv_w = 144, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 354, .adv_w = 230, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 376, .adv_w = 213, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 398, .adv_w = 181, .box_w = 10, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 415, .adv_w = 197, .box_w = 10, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 432, .adv_w = 219, .box_w = 13, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 454, .adv_w = 165, .box_w = 8, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 467, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 482, .adv_w = 208, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 502, .adv_w = 224, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 522, .adv_w = 96, .box_w = 4, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 529, .adv_w = 91, .box_w = 6, .box_h = 17, .ofs_x = -1, .ofs_y = -4},
    {.bitmap_index = 542, .adv_w = 203, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 560, .adv_w = 160, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 575, .adv_w = 267, .box_w = 15, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 600, .adv_w = 229, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 622, .adv_w = 219, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 642, .adv_w = 165, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 657, .adv_w = 219, .box_w = 14, .box_h = 16, .ofs_x = 1, .ofs_y = -3},
    {.bitmap_index = 685, .adv_w = 187, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 703, .adv_w = 171, .box_w = 9, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 718, .adv_w = 192, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 738, .adv_w = 219, .box_w = 12, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 758, .adv_w = 208, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 780, .adv_w = 309, .box_w = 19, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 811, .adv_w = 203, .box_w = 11, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 829, .adv_w = 208, .box_w = 13, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 851, .adv_w = 187, .box_w = 11, .box_h = 13, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 869, .adv_w = 90, .box_w = 4, .box_h = 20, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 879, .adv_w = 107, .box_w = 7, .box_h = 16, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 893, .adv_w = 90, .box_w = 4, .box_h = 20, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 903, .adv_w = 173, .box_w = 7, .box_h = 7, .ofs_x = 2, .ofs_y = 6},
    {.bitmap_index = 910, .adv_w = 144, .box_w = 9, .box_h = 1, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 912, .adv_w = 90, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 11},
    {.bitmap_index = 914, .adv_w = 165, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 924, .adv_w = 171, .box_w = 11, .box_h = 15, .ofs_x = 0, .ofs_y = 0},
    {.bitmap_index = 945, .adv_w = 149, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 955, .adv_w = 181, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 974, .adv_w = 160, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 984, .adv_w = 107, .box_w = 7, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 998, .adv_w = 160, .box_w = 9, .box_h = 15, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1015, .adv_w = 192, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1034, .adv_w = 90, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1042, .adv_w = 90, .box_w = 5, .box_h = 20, .ofs_x = -1, .ofs_y = -5},
    {.bitmap_index = 1055, .adv_w = 171, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1074, .adv_w = 90, .box_w = 4, .box_h = 15, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1082, .adv_w = 288, .box_w = 16, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1102, .adv_w = 192, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1115, .adv_w = 171, .box_w = 9, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1127, .adv_w = 181, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1146, .adv_w = 181, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1165, .adv_w = 123, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1174, .adv_w = 144, .box_w = 7, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1183, .adv_w = 112, .box_w = 6, .box_h = 13, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1193, .adv_w = 187, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1206, .adv_w = 165, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1219, .adv_w = 251, .box_w = 15, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1238, .adv_w = 171, .box_w = 10, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1251, .adv_w = 165, .box_w = 10, .box_h = 15, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1270, .adv_w = 155, .box_w = 8, .box_h = 10, .ofs_x = 1, .ofs_y = 0},
    {.bitmap_index = 1280, .adv_w = 90, .box_w = 4, .box_h = 20, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1290, .adv_w = 64, .box_w = 1, .box_h = 20, .ofs_x = 1, .ofs_y = -5},
    {.bitmap_index = 1293, .adv_w = 90, .box_w = 5, .box_h = 20, .ofs_x = 0, .ofs_y = -5},
    {.bitmap_index = 1306, .adv_w = 173, .box_w = 9, .box_h = 2, .ofs_x = 1, .ofs_y = 4}
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
    1, 55,
    1, 56,
    1, 58,
    13, 1,
    15, 1,
    34, 36,
    34, 40,
    34, 48,
    34, 50,
    34, 53,
    34, 54,
    34, 55,
    34, 56,
    34, 58,
    34, 86,
    34, 87,
    34, 88,
    34, 90,
    35, 13,
    35, 15,
    35, 34,
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
    39, 66,
    39, 70,
    39, 74,
    39, 80,
    39, 83,
    40, 13,
    40, 15,
    43, 13,
    43, 15,
    43, 34,
    43, 66,
    43, 70,
    43, 80,
    43, 86,
    44, 48,
    44, 70,
    44, 80,
    44, 86,
    44, 90,
    45, 53,
    45, 55,
    45, 56,
    45, 58,
    45, 90,
    47, 13,
    47, 15,
    47, 34,
    48, 13,
    48, 15,
    48, 34,
    48, 53,
    48, 55,
    48, 56,
    48, 57,
    48, 58,
    49, 13,
    49, 15,
    49, 34,
    49, 66,
    49, 70,
    49, 80,
    50, 54,
    51, 48,
    51, 53,
    51, 54,
    51, 55,
    51, 56,
    51, 58,
    52, 13,
    52, 15,
    53, 13,
    53, 14,
    53, 15,
    53, 27,
    53, 28,
    53, 34,
    53, 48,
    53, 66,
    53, 70,
    53, 74,
    53, 80,
    53, 83,
    53, 86,
    53, 88,
    53, 90,
    54, 13,
    54, 15,
    54, 34,
    55, 13,
    55, 14,
    55, 15,
    55, 27,
    55, 28,
    55, 34,
    55, 40,
    55, 48,
    55, 66,
    55, 70,
    55, 74,
    55, 80,
    55, 86,
    56, 13,
    56, 14,
    56, 15,
    56, 27,
    56, 28,
    56, 34,
    56, 48,
    56, 66,
    56, 70,
    56, 74,
    56, 80,
    56, 86,
    56, 90,
    58, 13,
    58, 14,
    58, 15,
    58, 27,
    58, 28,
    58, 34,
    58, 48,
    58, 52,
    58, 66,
    58, 70,
    58, 74,
    58, 80,
    58, 86,
    66, 67,
    66, 72,
    66, 87,
    66, 88,
    66, 90,
    67, 13,
    67, 15,
    67, 77,
    67, 87,
    67, 90,
    68, 73,
    68, 76,
    68, 90,
    69, 87,
    69, 88,
    69, 90,
    70, 13,
    70, 15,
    70, 67,
    70, 72,
    70, 81,
    70, 87,
    70, 88,
    70, 89,
    70, 90,
    72, 66,
    72, 70,
    72, 74,
    73, 90,
    74, 87,
    76, 90,
    77, 88,
    77, 90,
    78, 86,
    78, 90,
    79, 86,
    79, 87,
    79, 90,
    80, 13,
    80, 15,
    80, 72,
    80, 87,
    80, 88,
    80, 89,
    80, 90,
    81, 13,
    81, 15,
    81, 90,
    83, 13,
    83, 14,
    83, 15,
    83, 66,
    83, 68,
    83, 69,
    83, 70,
    83, 72,
    83, 80,
    83, 90,
    84, 88,
    87, 13,
    87, 15,
    87, 66,
    87, 70,
    87, 80,
    88, 13,
    88, 15,
    88, 66,
    88, 70,
    88, 80,
    90, 13,
    90, 15,
    90, 66,
    90, 70,
    90, 80
};

/* Kerning between the respective left and right glyphs
 * 4.4 format which needs to scaled with `kern_scale`*/
static const int8_t kern_pair_values[] =
{
    -11, -21, -21, -16, -21, -11, -11, -11,
    -11, -11, -11, -26, -9, -26, -21, -26,
    -7, -19, -21, -21, -7, -7, -9, -7,
    -13, -13, -16, -13, -13, -21, -37, -37,
    -21, -13, -9, -5, -9, -5, -7, -7,
    -11, -11, -5, -3, -3, -3, -5, -13,
    -3, -9, -11, -16, -26, -26, -26, -32,
    -21, -7, -7, -5, -13, -13, -13, -7,
    -11, -11, -7, -21, -37, -37, -21, -7,
    -7, -9, -3, -3, -11, -3, -16, -16,
    -16, -5, -7, -32, -32, -32, -21, -21,
    -26, -7, -26, -21, -16, -32, -26, -37,
    -43, -43, -13, -13, -16, -37, -26, -37,
    -21, -21, -26, -11, -9, -26, -21, -11,
    -21, -16, -37, -21, -37, -21, -21, -21,
    -11, -21, -21, -9, -21, -11, -19, -37,
    -37, -37, -26, -26, -26, -16, -11, -26,
    -26, -16, -32, -26, -3, -3, -9, -9,
    -9, -7, -7, -3, -7, -9, -5, -5,
    -7, -5, -9, -7, -5, -5, -2, -5,
    -3, -9, -9, -2, -9, 2, 3, 3,
    -9, -3, -3, -3, -3, -3, -5, -3,
    -9, -9, -7, -7, -2, -7, -7, -2,
    -7, -7, -7, -9, -16, -16, -16, -5,
    -5, -7, -3, -7, -3, -3, -7, -26,
    -26, -3, -3, -3, -26, -26, -3, -5,
    -5, -26, -26, -5, -5, -5
};

/*Collect the kern pair's data in one place*/
static const lv_font_fmt_txt_kern_pair_t kern_pairs =
{
    .glyph_ids = kern_pair_glyph_ids,
    .values = kern_pair_values,
    .pair_cnt = 214,
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
lv_font_t caecilia18 = {
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 21,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = -1,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if CAECILIA18*/

