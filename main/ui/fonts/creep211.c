#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif
/*-----------------
 *    BITMAPS
 *----------------*/
 static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+0020 ' ' */
    0x00,

    /* U+0021 '!' */
    0xfa,

    /* U+0022 '"' */
    0xb6, 0x80,

    /* U+0023 '#' */
    0x57, 0xd5, 0xf5, 0x00,

    /* U+0024 '$' */
    0x23, 0xe8, 0xe2, 0xf8, 0x80,

    /* U+0025 '%' */
    0x92, 0x49,

    /* U+0026 '&' */
    0x45, 0x28, 0x8a, 0xc9, 0xe0,

    /* U+0027 "'" */
    0xc0,

    /* U+0028 '(' */
    0x2a, 0x49, 0x22, 0x20,

    /* U+0029 ')' */
    0x88, 0x92, 0x4a, 0x80,

    /* U+002A '*' */
    0xaa, 0x80,

    /* U+002B '+' */
    0x21, 0x3e, 0x42, 0x00,

    /* U+002C ',' */
    0x60,

    /* U+002D '-' */
    0xf0,

    /* U+002E '.' */
    0x80,

    /* U+002F '/' */
    0x11, 0x22, 0x44, 0x88,

    /* U+0030 '0' */
    0x69, 0x9b, 0xd9, 0x60,

    /* U+0031 '1' */
    0x75, 0x54,

    /* U+0032 '2' */
    0x69, 0x12, 0x48, 0xf0,

    /* U+0033 '3' */
    0xf1, 0x26, 0x19, 0x60,

    /* U+0034 '4' */
    0x66, 0xaa, 0xf2, 0x20,

    /* U+0035 '5' */
    0xf8, 0xe9, 0x19, 0x60,

    /* U+0036 '6' */
    0x69, 0x8e, 0x99, 0x60,

    /* U+0037 '7' */
    0xf1, 0x12, 0x24, 0x40,

    /* U+0038 '8' */
    0x69, 0x96, 0x99, 0x60,

    /* U+0039 '9' */
    0x69, 0x97, 0x19, 0x60,

    /* U+003A ':' */
    0xa0,

    /* U+003B ';' */
    0x46,

    /* U+003C '<' */
    0x2a, 0x22,

    /* U+003D '=' */
    0xf0, 0xf0,

    /* U+003E '>' */
    0x88, 0xa8,

    /* U+003F '?' */
    0xe1, 0x34, 0x40, 0x40,

    /* U+0040 '@' */
    0xf9, 0xbb, 0x8f,

    /* U+0041 'A' */
    0x69, 0x9f, 0x99, 0x90,

    /* U+0042 'B' */
    0xca, 0xae, 0x99, 0xf0,

    /* U+0043 'C' */
    0x69, 0x88, 0x89, 0x60,

    /* U+0044 'D' */
    0xca, 0x99, 0x9a, 0xc0,

    /* U+0045 'E' */
    0xf8, 0x8c, 0x88, 0xf0,

    /* U+0046 'F' */
    0xf8, 0x8c, 0x88, 0x80,

    /* U+0047 'G' */
    0x69, 0x88, 0xb9, 0x60,

    /* U+0048 'H' */
    0x99, 0xf9, 0x99, 0x90,

    /* U+0049 'I' */
    0xe9, 0x24, 0xb8,

    /* U+004A 'J' */
    0x71, 0x11, 0x19, 0x70,

    /* U+004B 'K' */
    0x9a, 0xca, 0xa9, 0x90,

    /* U+004C 'L' */
    0x88, 0x88, 0x88, 0xf0,

    /* U+004D 'M' */
    0x9f, 0xf9, 0x99, 0x90,

    /* U+004E 'N' */
    0x9d, 0xdb, 0xb9, 0x90,

    /* U+004F 'O' */
    0x69, 0x99, 0x99, 0x60,

    /* U+0050 'P' */
    0xe9, 0x9e, 0x88, 0x80,

    /* U+0051 'Q' */
    0x69, 0x99, 0x9b, 0x71,

    /* U+0052 'R' */
    0xe9, 0x9e, 0xca, 0x90,

    /* U+0053 'S' */
    0x69, 0x86, 0x19, 0x60,

    /* U+0054 'T' */
    0xe9, 0x24, 0x90,

    /* U+0055 'U' */
    0x99, 0x99, 0x99, 0x70,

    /* U+0056 'V' */
    0x99, 0x95, 0x52, 0x20,

    /* U+0057 'W' */
    0x99, 0x99, 0xff, 0x90,

    /* U+0058 'X' */
    0x99, 0x69, 0x99, 0x90,

    /* U+0059 'Y' */
    0x99, 0x97, 0x19, 0x70,

    /* U+005A 'Z' */
    0xf1, 0x12, 0x48, 0xf0,

    /* U+005B '[' */
    0xea, 0xaa, 0xc0,

    /* U+005C '\\' */
    0x88, 0x44, 0x22, 0x11,

    /* U+005D ']' */
    0xd5, 0x55, 0xc0,

    /* U+005E '^' */
    0x54,

    /* U+005F '_' */
    0xf0,

    /* U+0060 '`' */
    0x90,

    /* U+0061 'a' */
    0x74, 0xa5, 0x26, 0x80,

    /* U+0062 'b' */
    0x88, 0xe9, 0x99, 0xe0,

    /* U+0063 'c' */
    0x69, 0x89, 0x60,

    /* U+0064 'd' */
    0x11, 0x79, 0x99, 0x70,

    /* U+0065 'e' */
    0x69, 0xf8, 0x70,

    /* U+0066 'f' */
    0x25, 0x4e, 0x44, 0x44,

    /* U+0067 'g' */
    0x79, 0x99, 0x71, 0x60,

    /* U+0068 'h' */
    0x88, 0xe9, 0x99, 0x90,

    /* U+0069 'i' */
    0x43, 0x24, 0x98,

    /* U+006A 'j' */
    0x4d, 0x55, 0x80,

    /* U+006B 'k' */
    0x88, 0x9a, 0xca, 0x90,

    /* U+006C 'l' */
    0xaa, 0xa4,

    /* U+006D 'm' */
    0x9f, 0x99, 0x90,

    /* U+006E 'n' */
    0xe9, 0x99, 0x90,

    /* U+006F 'o' */
    0x69, 0x99, 0x60,

    /* U+0070 'p' */
    0xe9, 0x99, 0xe8, 0x80,

    /* U+0071 'q' */
    0x79, 0x99, 0x71, 0x10,

    /* U+0072 'r' */
    0xe9, 0x88, 0x80,

    /* U+0073 's' */
    0x78, 0x61, 0xe0,

    /* U+0074 't' */
    0x4b, 0xa4, 0x88,

    /* U+0075 'u' */
    0x99, 0x99, 0x70,

    /* U+0076 'v' */
    0x99, 0x9a, 0x40,

    /* U+0077 'w' */
    0x99, 0x9f, 0x90,

    /* U+0078 'x' */
    0x99, 0x69, 0x90,

    /* U+0079 'y' */
    0x99, 0x97, 0x19, 0x60,

    /* U+007A 'z' */
    0xf2, 0x48, 0xf0,

    /* U+007B '{' */
    0x34, 0x44, 0x84, 0x44, 0x30,

    /* U+007C '|' */
    0xfe,

    /* U+007D '}' */
    0xc2, 0x22, 0x12, 0x22, 0xc0,

    /* U+007E '~' */
    0x5a,

    /* U+00A0 '\xa0' */
    0x00,

    /* U+00A1 '¡' */
    0xbe,

    /* U+00A2 '¢' */
    0x46, 0xdc, 0xd6, 0x40,

    /* U+00A3 '£' */
    0x69, 0x8c, 0x8d, 0xb0,

    /* U+00A4 '¤' */
    0x8b, 0x94, 0xe8, 0x80,

    /* U+00A5 '¥' */
    0x52, 0xbe, 0xaf, 0x90, 0x80,

    /* U+00A6 '¦' */
    0xee,

    /* U+00A7 '§' */
    0x69, 0xe9, 0x79, 0x60,

    /* U+00A8 '¨' */
    0xa0,

    /* U+00A9 '©' */
    0x32, 0x6d, 0x4b, 0x24, 0xc0,

    /* U+00AA 'ª' */
    0x79, 0x99, 0x70, 0xf0,

    /* U+00AB '«' */
    0x5a, 0xa5,

    /* U+00AC '¬' */
    0xf1,

    /* U+00AD '\xad' */
    0xf0,

    /* U+00AE '®' */
    0x32, 0x6d, 0x4a, 0x24, 0xc0,

    /* U+00AF '¯' */
    0xf0,

    /* U+00B0 '°' */
    0x55, 0x00,

    /* U+00B1 '±' */
    0x21, 0x3e, 0x4f, 0x80,

    /* U+00B2 '²' */
    0x75, 0x70,

    /* U+00B3 '³' */
    0xe8, 0xe0,

    /* U+00B4 '´' */
    0x60,

    /* U+00B5 'µ' */
    0x99, 0x99, 0xe8, 0x80,

    /* U+00B6 '¶' */
    0x7d, 0xdd, 0x55, 0x56,

    /* U+00B7 '·' */
    0x80,

    /* U+00B8 '¸' */
    0x1c,

    /* U+00B9 '¹' */
    0xc9, 0x70,

    /* U+00BA 'º' */
    0x55, 0x0e,

    /* U+00BB '»' */
    0xa5, 0x5a,

    /* U+00BC '¼' */
    0x22, 0x0f, 0x05, 0x71,

    /* U+00BD '½' */
    0x22, 0x0f, 0x06, 0x12, 0x70,

    /* U+00BE '¾' */
    0x71, 0x31, 0x70, 0xf0, 0x57, 0x10,

    /* U+00BF '¿' */
    0x20, 0x22, 0xc8, 0x70,

    /* U+00C0 'À' */
    0x42, 0x69, 0x9f, 0x99, 0x90,

    /* U+00C1 'Á' */
    0x24, 0x69, 0x9f, 0x99, 0x90,

    /* U+00C2 'Â' */
    0x69, 0x69, 0x9f, 0x99, 0x90,

    /* U+00C3 'Ã' */
    0x5a, 0x69, 0x9f, 0x99, 0x90,

    /* U+00C4 'Ä' */
    0x50, 0x69, 0x9f, 0x99, 0x90,

    /* U+00C5 'Å' */
    0x40, 0x69, 0x9f, 0x99, 0x90,

    /* U+00C6 'Æ' */
    0x7a, 0xaf, 0xaa, 0xb0,

    /* U+00C7 'Ç' */
    0x69, 0x88, 0x89, 0x62, 0x60,

    /* U+00C8 'È' */
    0x42, 0xf8, 0x8c, 0x88, 0xf0,

    /* U+00C9 'É' */
    0x24, 0xf8, 0x8c, 0x88, 0xf0,

    /* U+00CA 'Ê' */
    0x69, 0xf8, 0x8c, 0x88, 0xf0,

    /* U+00CB 'Ë' */
    0x50, 0xf8, 0x8c, 0x88, 0xf0,

    /* U+00CC 'Ì' */
    0x8b, 0xa4, 0x92, 0xe0,

    /* U+00CD 'Í' */
    0x2b, 0xa4, 0x92, 0xe0,

    /* U+00CE 'Î' */
    0x57, 0xa4, 0x92, 0xe0,

    /* U+00CF 'Ï' */
    0xa3, 0xa4, 0x92, 0xe0,

    /* U+00D0 'Ð' */
    0x62, 0x93, 0xd4, 0xa9, 0x80,

    /* U+00D1 'Ñ' */
    0x5a, 0x99, 0xdd, 0xbb, 0x90,

    /* U+00D2 'Ò' */
    0x42, 0x69, 0x99, 0x99, 0x60,

    /* U+00D3 'Ó' */
    0x24, 0x69, 0x99, 0x99, 0x60,

    /* U+00D4 'Ô' */
    0x69, 0x69, 0x99, 0x99, 0x60,

    /* U+00D5 'Õ' */
    0x5a, 0x69, 0x99, 0x99, 0x60,

    /* U+00D6 'Ö' */
    0x50, 0x69, 0x99, 0x99, 0x60,

    /* U+00D7 '×' */
    0x96, 0x69,

    /* U+00D8 'Ø' */
    0x6c, 0xed, 0xa9, 0x49, 0x80,

    /* U+00D9 'Ù' */
    0x42, 0x99, 0x99, 0x99, 0x70,

    /* U+00DA 'Ú' */
    0x24, 0x99, 0x99, 0x99, 0x70,

    /* U+00DB 'Û' */
    0x25, 0x09, 0x99, 0x99, 0x70,

    /* U+00DC 'Ü' */
    0x90, 0x99, 0x99, 0x99, 0x70,

    /* U+00DD 'Ý' */
    0x24, 0x99, 0x97, 0x19, 0x60,

    /* U+00DE 'Þ' */
    0x8e, 0x99, 0x9e, 0x80,

    /* U+00DF 'ß' */
    0xca, 0xad, 0x9e, 0x80,

    /* U+00E0 'à' */
    0x42, 0x07, 0x99, 0x97,

    /* U+00E1 'á' */
    0x24, 0x07, 0x99, 0x97,

    /* U+00E2 'â' */
    0x25, 0x07, 0x99, 0x97,

    /* U+00E3 'ã' */
    0x2a, 0x80, 0xe9, 0x4a, 0x4e,

    /* U+00E4 'ä' */
    0x50, 0x79, 0x99, 0x70,

    /* U+00E5 'å' */
    0x20, 0x79, 0x99, 0x70,

    /* U+00E6 'æ' */
    0x7a, 0xfa, 0xb0,

    /* U+00E7 'ç' */
    0x69, 0x89, 0x62, 0x60,

    /* U+00E8 'è' */
    0x42, 0x06, 0x9f, 0x87,

    /* U+00E9 'é' */
    0x24, 0x06, 0x9f, 0x87,

    /* U+00EA 'ê' */
    0x25, 0x06, 0x9f, 0x87,

    /* U+00EB 'ë' */
    0x50, 0x69, 0xf8, 0x70,

    /* U+00EC 'ì' */
    0x88, 0x64, 0x93,

    /* U+00ED 'í' */
    0x28, 0x64, 0x93,

    /* U+00EE 'î' */
    0x54, 0x64, 0x93,

    /* U+00EF 'ï' */
    0xa3, 0x24, 0x98,

    /* U+00F0 'ð' */
    0x61, 0x79, 0x99, 0x60,

    /* U+00F1 'ñ' */
    0x5a, 0x0e, 0x99, 0x99,

    /* U+00F2 'ò' */
    0x42, 0x06, 0x99, 0x96,

    /* U+00F3 'ó' */
    0x24, 0x06, 0x99, 0x96,

    /* U+00F4 'ô' */
    0x69, 0x06, 0x99, 0x96,

    /* U+00F5 'õ' */
    0x5a, 0x06, 0x99, 0x96,

    /* U+00F6 'ö' */
    0x50, 0x69, 0x99, 0x60,

    /* U+00F7 '÷' */
    0x60, 0xf0, 0x60,

    /* U+00F8 'ø' */
    0x0b, 0xad, 0xa9, 0x30,

    /* U+00F9 'ù' */
    0x42, 0x09, 0x99, 0x97,

    /* U+00FA 'ú' */
    0x24, 0x09, 0x99, 0x97,

    /* U+00FB 'û' */
    0x69, 0x09, 0x99, 0x97,

    /* U+00FC 'ü' */
    0x50, 0x09, 0x99, 0x97,

    /* U+00FD 'ý' */
    0x24, 0x09, 0x99, 0x71, 0x96,

    /* U+00FE 'þ' */
    0x88, 0xe9, 0x9e, 0x88,

    /* U+00FF 'ÿ' */
    0x50, 0x99, 0x97, 0x19, 0x60,

    /* U+0100 'Ā' */
    0xf0, 0x69, 0x9f, 0x99, 0x90,

    /* U+0103 'ă' */
    0x52, 0x00, 0x79, 0x99, 0x70,

    /* U+010C 'Č' */
    0x52, 0x69, 0x88, 0x89, 0x60,

    /* U+010D 'č' */
    0x52, 0x06, 0x98, 0x96,

    /* U+010E 'Ď' */
    0x52, 0xca, 0x99, 0x9a, 0x40,

    /* U+010F 'ď' */
    0x29, 0x59, 0x4a, 0x51, 0x80,

    /* U+011A 'Ě' */
    0x52, 0xf8, 0x8c, 0x88, 0xf0,

    /* U+011B 'ě' */
    0x52, 0x06, 0x9f, 0x87,

    /* U+013D 'Ľ' */
    0x9a, 0x88, 0x88, 0xf0,

    /* U+013E 'ľ' */
    0xb6, 0x49, 0x10,

    /* U+0147 'Ň' */
    0x52, 0x9d, 0xdb, 0xb9, 0x90,

    /* U+0148 'ň' */
    0x52, 0x0e, 0x99, 0x99,

    /* U+0156 'Ŗ' */
    0x52, 0xe9, 0x9e, 0xca, 0x90,

    /* U+0157 'ŗ' */
    0x52, 0x0e, 0x98, 0x88,

    /* U+0160 'Š' */
    0x52, 0x69, 0x86, 0x19, 0x60,

    /* U+0161 'š' */
    0x52, 0x07, 0x86, 0x1e,

    /* U+0164 'Ť' */
    0xab, 0xa4, 0x92, 0x40,

    /* U+0165 'ť' */
    0x4a, 0x78, 0x84, 0x20, 0x80,

    /* U+016E 'Ů' */
    0x25, 0xb9, 0x99, 0x99, 0x70,

    /* U+016F 'ů' */
    0x25, 0x29, 0x99, 0x97,

    /* U+017D 'Ž' */
    0x52, 0xf1, 0x12, 0x48, 0xf0,

    /* U+017E 'ž' */
    0x52, 0x0f, 0x24, 0x8f,

    /* U+0219 'ș' */
    0x78, 0x61, 0xe2, 0x40,

    /* U+02C7 'ˇ' */
    0xa8,

    /* U+02DA '˚' */
    0x55, 0x00,

    /* U+0391 'Α' */
    0x69, 0x9f, 0x99, 0x90,

    /* U+0392 'Β' */
    0xca, 0xae, 0x99, 0xf0,

    /* U+0393 'Γ' */
    0xf9, 0x88, 0x88, 0x80,

    /* U+0394 'Δ' */
    0x21, 0x14, 0xa8, 0xc7, 0xe0,

    /* U+0395 'Ε' */
    0xf8, 0x8c, 0x88, 0xf0,

    /* U+0396 'Ζ' */
    0xf1, 0x12, 0x48, 0xf0,

    /* U+0397 'Η' */
    0x99, 0xf9, 0x99, 0x90,

    /* U+0398 'Θ' */
    0x69, 0x9f, 0x99, 0x60,

    /* U+0399 'Ι' */
    0xe9, 0x24, 0xb8,

    /* U+039A 'Κ' */
    0x9a, 0xca, 0xa9, 0x90,

    /* U+039B 'Λ' */
    0x21, 0x14, 0xa8, 0xc6, 0x20,

    /* U+039C 'Μ' */
    0x9f, 0x99, 0x99, 0x90,

    /* U+039D 'Ν' */
    0x9d, 0xdb, 0xb9, 0x90,

    /* U+039E 'Ξ' */
    0xf9, 0x06, 0x09, 0xf0,

    /* U+039F 'Ο' */
    0x69, 0x99, 0x99, 0x60,

    /* U+03A0 'Π' */
    0xf9, 0x99, 0x99, 0x90,

    /* U+03A1 'Ρ' */
    0xe9, 0x9e, 0x88, 0x80,

    /* U+03A2 '\u03a2' */
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xfe,

    /* U+03A3 'Σ' */
    0xf9, 0x42, 0x49, 0xf0,

    /* U+03A4 'Τ' */
    0xe9, 0x24, 0x90,

    /* U+03A5 'Υ' */
    0x99, 0x97, 0x19, 0x60,

    /* U+03A6 'Φ' */
    0x23, 0xab, 0x5a, 0xb8, 0x80,

    /* U+03A7 'Χ' */
    0x99, 0x69, 0x99, 0x90,

    /* U+03A8 'Ψ' */
    0xad, 0x6a, 0xe2, 0x10, 0x80,

    /* U+03A9 'Ω' */
    0x74, 0x63, 0x1d, 0xab, 0x60,

    /* U+03B1 'α' */
    0x5a, 0xa7,

    /* U+03B2 'β' */
    0xca, 0xad, 0x9e, 0x88,

    /* U+03B3 'γ' */
    0x96, 0x25, 0x52,

    /* U+03B4 'δ' */
    0xf8, 0x69, 0x96,

    /* U+03B5 'ε' */
    0x69, 0x48, 0x96,

    /* U+03B6 'ζ' */
    0xf2, 0x48, 0x87, 0x10,

    /* U+03B7 'η' */
    0xe9, 0x99, 0x91, 0x10,

    /* U+03B8 'θ' */
    0x69, 0xf9, 0x60,

    /* U+03B9 'ι' */
    0xc9, 0x10,

    /* U+03BA 'κ' */
    0xbb, 0x5a,

    /* U+03BB 'λ' */
    0x4a, 0x26, 0xa9,

    /* U+03BC 'μ' */
    0x99, 0x99, 0xe8, 0x80,

    /* U+03BD 'ν' */
    0x29, 0x55, 0x64,

    /* U+03BE 'ξ' */
    0xe9, 0x48, 0x87, 0x16,

    /* U+03BF 'ο' */
    0x69, 0x99, 0x60,

    /* U+03C0 'π' */
    0xf6, 0xaa, 0x90,

    /* U+03C1 'ρ' */
    0x25, 0x56, 0x48,

    /* U+03C2 'ς' */
    0x69, 0x98, 0x61, 0x20,

    /* U+03C3 'σ' */
    0x16, 0x99, 0x96,

    /* U+03C4 'τ' */
    0xf4, 0x45, 0x20,

    /* U+03C5 'υ' */
    0x99, 0x99, 0x70,

    /* U+03C6 'φ' */
    0x4b, 0xdf, 0x44,

    /* U+03C7 'χ' */
    0x96, 0x6a, 0x10,

    /* U+03C8 'ψ' */
    0x25, 0x6a, 0xe2, 0x10,

    /* U+03C9 'ω' */
    0x54, 0x63, 0x55, 0x00,

    /* U+1E9E 'ẞ' */
    0xca, 0xad, 0x9f, 0x88,

    /* U+2010 '‐' */
    0xe0,

    /* U+2011 '‑' */
    0xe0,

    /* U+2012 '‒' */
    0xf0,

    /* U+2013 '–' */
    0xf0,

    /* U+2014 '—' */
    0xf8,

    /* U+2015 '―' */
    0xf8,

    /* U+2016 '‖' */
    0xb6, 0xdb, 0x68,

    /* U+2017 '‗' */
    0xf0, 0xf0,

    /* U+2018 '‘' */
    0xe4,

    /* U+2019 '’' */
    0xd8,

    /* U+201A '‚' */
    0xd8,

    /* U+201B '‛' */
    0xe4,

    /* U+201C '“' */
    0xfa, 0x50,

    /* U+201D '”' */
    0xf5, 0xa0,

    /* U+201E '„' */
    0xf5, 0xa0,

    /* U+201F '‟' */
    0x5a, 0xf0,

    /* U+2020 '†' */
    0x5d, 0x24,

    /* U+2021 '‡' */
    0x5d, 0x74,

    /* U+2022 '•' */
    0x55, 0x00,

    /* U+2023 '‣' */
    0xb8,

    /* U+2024 '․' */
    0x80,

    /* U+2025 '‥' */
    0xa0,

    /* U+2026 '…' */
    0xa8,

    /* U+2027 '‧' */
    0x80,

    /* U+2032 '′' */
    0x60,

    /* U+2033 '″' */
    0x5a,

    /* U+2034 '‴' */
    0x55, 0x40,

    /* U+2035 '‵' */
    0x90,

    /* U+2036 '‶' */
    0xa5,

    /* U+2037 '‷' */
    0xaa, 0x80,

    /* U+2038 '‸' */
    0x54,

    /* U+2039 '‹' */
    0x84, 0x21, 0x24, 0x80,

    /* U+203A '›' */
    0xe4,

    /* U+203C '‼' */
    0xb6, 0xda, 0x28,

    /* U+203E '‾' */
    0xf0,

    /* U+203F '‿' */
    0x96,

    /* U+2040 '⁀' */
    0x69,

    /* U+2041 '⁁' */
    0x12, 0x4a,

    /* U+2042 '⁂' */
    0x42, 0x80,

    /* U+204F '⁏' */
    0x89,

    /* U+2050 '⁐' */
    0x69, 0x00, 0x96,

    /* U+2051 '⁑' */
    0xaa, 0x8a, 0xa8,

    /* U+20AC '€' */
    0x78, 0xee, 0x87,

    /* U+2122 '™' */
    0xf9, 0x08, 0x48, 0xee, 0xb1, 0x88,

    /* U+2190 '←' */
    0x22, 0x3e, 0x82, 0x00,

    /* U+2191 '↑' */
    0x23, 0xaa, 0x42, 0x00,

    /* U+2192 '→' */
    0x20, 0xbe, 0x22, 0x00,

    /* U+2193 '↓' */
    0x21, 0x2a, 0xe2, 0x00,

    /* U+2194 '↔' */
    0x57, 0xd4,

    /* U+2195 '↕' */
    0x5d, 0x2e, 0x80,

    /* U+2196 '↖' */
    0xe8, 0xa1,

    /* U+2197 '↗' */
    0x71, 0x58,

    /* U+2198 '↘' */
    0x85, 0x17,

    /* U+2199 '↙' */
    0x1a, 0x8e,

    /* U+21D0 '⇐' */
    0x23, 0xe0, 0xf2, 0x00,

    /* U+21D1 '⇑' */
    0x22, 0xb6, 0xa5, 0x28,

    /* U+21D2 '⇒' */
    0x27, 0x83, 0xe2, 0x00,

    /* U+21D3 '⇓' */
    0x52, 0x95, 0xb5, 0x10,

    /* U+2200 '∀' */
    0x99, 0x9f, 0x99, 0x60,

    /* U+2201 '∁' */
    0x69, 0xa8, 0x99, 0x60,

    /* U+2202 '∂' */
    0x69, 0x17, 0x99, 0x60,

    /* U+2203 '∃' */
    0xf1, 0x17, 0x11, 0xf0,

    /* U+2204 '∄' */
    0x1f, 0x35, 0x79, 0x9f,

    /* U+2205 '∅' */
    0x16, 0xbd, 0x68,

    /* U+2206 '∆' */
    0x22, 0xa3, 0xf0,

    /* U+2207 '∇' */
    0xfc, 0x54, 0x40,

    /* U+2208 '∈' */
    0x78, 0xe8, 0x70,

    /* U+2209 '∉' */
    0x0b, 0xa9, 0xc8, 0x38,

    /* U+220A '∊' */
    0x78, 0xe8, 0x70,

    /* U+220B '∋' */
    0xe1, 0x71, 0xe0,

    /* U+220C '∌' */
    0x0f, 0x8c, 0xe9, 0x70,

    /* U+220D '∍' */
    0xe1, 0x71, 0xe0,

    /* U+220E '∎' */
    0xff, 0x80,

    /* U+220F '∏' */
    0xf9, 0x99, 0x99,

    /* U+2210 '∐' */
    0x99, 0x99, 0x9f,

    /* U+2211 '∑' */
    0xf9, 0x44, 0x9f,

    /* U+2212 '−' */
    0xf0,

    /* U+2213 '∓' */
    0xe1, 0x74,

    /* U+2260 '≠' */
    0x2f, 0x4f, 0x80,

    /* U+229E '⊞' */
    0xfd, 0x7f, 0x5f, 0x80,

    /* U+229F '⊟' */
    0xfc, 0x7f, 0x1f, 0x80,

    /* U+2500 '─' */
    0xf8,

    /* U+2502 '│' */
    0xff, 0xe0,

    /* U+250C '┌' */
    0xf2, 0x49, 0x20,

    /* U+250D '┍' */
    0xf2, 0x49, 0x20,

    /* U+250E '┎' */
    0xf2, 0x49, 0x20,

    /* U+250F '┏' */
    0xf2, 0x49, 0x20,

    /* U+2510 '┐' */
    0xe4, 0x92, 0x48,

    /* U+2511 '┑' */
    0xe4, 0x92, 0x48,

    /* U+2512 '┒' */
    0xe4, 0x92, 0x48,

    /* U+2513 '┓' */
    0xe4, 0x92, 0x48,

    /* U+2514 '└' */
    0x92, 0x4e,

    /* U+2515 '┕' */
    0x92, 0x4e,

    /* U+2516 '┖' */
    0x92, 0x4e,

    /* U+2517 '┗' */
    0x92, 0x4e,

    /* U+2518 '┘' */
    0x24, 0x9e,

    /* U+2519 '┙' */
    0x24, 0x9e,

    /* U+251A '┚' */
    0x24, 0x9e,

    /* U+251B '┛' */
    0x24, 0x9e,

    /* U+251C '├' */
    0x92, 0x4f, 0x24, 0x92, 0x00,

    /* U+251D '┝' */
    0x92, 0x4f, 0x24, 0x92, 0x00,

    /* U+251E '┞' */
    0x92, 0x4f, 0x24, 0x92, 0x00,

    /* U+251F '┟' */
    0x92, 0x4f, 0x24, 0x92, 0x00,

    /* U+2520 '┠' */
    0x92, 0x4f, 0x24, 0x92, 0x00,

    /* U+2521 '┡' */
    0x92, 0x4f, 0x24, 0x92, 0x00,

    /* U+2522 '┢' */
    0x92, 0x4f, 0x24, 0x92, 0x00,

    /* U+2523 '┣' */
    0x92, 0x4f, 0x24, 0x92, 0x00,

    /* U+2524 '┤' */
    0x24, 0x9e, 0x49, 0x24, 0x80,

    /* U+2525 '┥' */
    0x24, 0x9e, 0x49, 0x24, 0x80,

    /* U+2526 '┦' */
    0x24, 0x9e, 0x49, 0x24, 0x80,

    /* U+2527 '┧' */
    0x24, 0x9e, 0x49, 0x24, 0x80,

    /* U+2528 '┨' */
    0x24, 0x9e, 0x49, 0x24, 0x80,

    /* U+2529 '┩' */
    0x24, 0x9e, 0x49, 0x24, 0x80,

    /* U+252A '┪' */
    0x24, 0x9e, 0x49, 0x24, 0x80,

    /* U+252B '┫' */
    0x24, 0x9e, 0x49, 0x24, 0x80,

    /* U+252C '┬' */
    0xf9, 0x08, 0x42, 0x10, 0x80,

    /* U+252D '┭' */
    0xf9, 0x08, 0x42, 0x10, 0x80,

    /* U+252E '┮' */
    0xf9, 0x08, 0x42, 0x10, 0x80,

    /* U+252F '┯' */
    0xf9, 0x08, 0x42, 0x10, 0x80,

    /* U+2530 '┰' */
    0xf9, 0x08, 0x42, 0x10, 0x80,

    /* U+2531 '┱' */
    0xf9, 0x08, 0x42, 0x10, 0x80,

    /* U+2532 '┲' */
    0xf9, 0x08, 0x42, 0x10, 0x80,

    /* U+2533 '┳' */
    0xf9, 0x08, 0x42, 0x10, 0x80,

    /* U+2534 '┴' */
    0x21, 0x08, 0x4f, 0x80,

    /* U+2535 '┵' */
    0x21, 0x08, 0x4f, 0x80,

    /* U+2536 '┶' */
    0x21, 0x08, 0x4f, 0x80,

    /* U+2537 '┷' */
    0x21, 0x08, 0x4f, 0x80,

    /* U+2538 '┸' */
    0x21, 0x08, 0x4f, 0x80,

    /* U+2539 '┹' */
    0x21, 0x08, 0x4f, 0x80,

    /* U+253A '┺' */
    0x21, 0x08, 0x4f, 0x80,

    /* U+253B '┻' */
    0x21, 0x08, 0x4f, 0x80,

    /* U+253C '┼' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+253D '┽' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+253E '┾' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+253F '┿' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2540 '╀' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2541 '╁' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2542 '╂' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2543 '╃' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2544 '╄' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2545 '╅' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2546 '╆' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2547 '╇' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2548 '╈' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+2549 '╉' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+254A '╊' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+254B '╋' */
    0x21, 0x08, 0x4f, 0x90, 0x84, 0x21, 0x08,

    /* U+256D '╭' */
    0x2a, 0x49, 0x20,

    /* U+256E '╮' */
    0x88, 0x92, 0x48,

    /* U+256F '╯' */
    0x24, 0xa8,

    /* U+2570 '╰' */
    0x92, 0x22,

    /* U+25A1 '□' */
    0xf9, 0x9f,

    /* U+25A2 '▢' */
    0x69, 0x96,

    /* U+25AA '▪' */
    0xf0,

    /* U+25B2 '▲' */
    0x23, 0xbe,

    /* U+25B3 '△' */
    0x22, 0xbe,

    /* U+25B4 '▴' */
    0x5c,

    /* U+2600 '☀' */
    0x25, 0x5d, 0xf7, 0x54, 0x80,

    /* U+2601 '☁' */
    0x33, 0xfe,

    /* U+2602 '☂' */
    0x77, 0xfe, 0x42, 0x52, 0x88,

    /* U+2661 '♡' */
    0x55, 0x62, 0xa2, 0x00,

    /* U+2665 '♥' */
    0x57, 0xfe, 0xe2, 0x00,

    /* U+2713 '✓' */
    0x08, 0x45, 0x26, 0x10,

    /* U+2714 '✔' */
    0x08, 0xe5, 0xe6, 0x10,

    /* U+2715 '✕' */
    0x8a, 0x88, 0xa8, 0x80,

    /* U+2716 '✖' */
    0x8a, 0x88, 0xa8, 0x80,

    /* U+272E '✮' */
    0x21, 0x3e, 0xe7, 0x44,

    /* U+2744 '❄' */
    0x26, 0xea, 0xea, 0xec, 0x80,

    /* U+27C2 '⟂' */
    0x49, 0x2e,

    /* U+27C3 '⟃' */
    0x78, 0xa8, 0x70,

    /* U+27C4 '⟄' */
    0xe1, 0x51, 0xe0,

    /* U+27D6 '⟖' */
    0x21, 0x08, 0x42, 0x7c,

    /* U+27D7 '⟗' */
    0xf9, 0x08, 0x42, 0x10,

    /* U+27DC '⟜' */
    0x45, 0xd0,

    /* U+27DD '⟝' */
    0x87, 0xe0,

    /* U+27DE '⟞' */
    0x0f, 0xc2,

    /* U+2919 '⤙' */
    0x08, 0xb8, 0x20, 0x80,

    /* U+291A '⤚' */
    0x82, 0x0e, 0x88, 0x00,

    /* U+291B '⤛' */
    0x11, 0x74, 0x51, 0x00,

    /* U+291C '⤜' */
    0x45, 0x17, 0x44, 0x00,

    /* U+2B60 '⭠' */
    0x8a, 0xfa, 0xac, 0x88,

    /* U+2B61 '⭡' */
    0x88, 0x8c, 0x65, 0x55,

    /* U+2B62 '⭢' */
    0x22, 0x1c, 0xa5, 0xc8, 0x41,

    /* U+2B64 '⭤' */
    0x69, 0x9f, 0xdd, 0xf0,

    /* U+2B80 '⮀' */
    0x86, 0x39, 0xef, 0xfb, 0x98, 0x80,

    /* U+2B81 '⮁' */
    0x82, 0x08, 0x20, 0x88, 0x88, 0x80,

    /* U+2B82 '⮂' */
    0x08, 0xce, 0xff, 0xbc, 0xe3, 0x08,

    /* U+2B83 '⮃' */
    0x08, 0x88, 0x88, 0x20, 0x82, 0x08,

    /* U+E0A0 '\ue0a0' */
    0x8a, 0xfa, 0xac, 0x88,

    /* U+E0A1 '\ue0a1' */
    0x88, 0x8c, 0x65, 0x55,

    /* U+E0A2 '\ue0a2' */
    0x69, 0x9f, 0xdd, 0xf0,

    /* U+E0B0 '\ue0b0' */
    0x86, 0x39, 0xef, 0xff, 0xdc, 0xc4, 0x00,

    /* U+E0B1 '\ue0b1' */
    0x82, 0x08, 0x20, 0x84, 0x44, 0x44, 0x00,

    /* U+E0B2 '\ue0b2' */
    0x08, 0xce, 0xff, 0xfd, 0xe7, 0x18, 0x40,

    /* U+E0B3 '\ue0b3' */
    0x08, 0x88, 0x88, 0x41, 0x04, 0x10, 0x40,

    /* U+E0C0 '\ue0c0' */
    0x45, 0x15, 0x54, 0x80,

    /* U+E0C1 '\ue0c1' */
    0x88, 0xa8,

    /* U+E0C2 '\ue0c2' */
    0x52, 0xbe, 0xe7, 0x10, 0x84,

    /* U+E0C3 '\ue0c3' */
    0x83, 0xc0, 0xf8, 0x00,

    /* U+E0C4 '\ue0c4' */
    0xa2, 0xc8, 0xba, 0x00,

    /* U+E0C5 '\ue0c5' */
    0x0f, 0x81, 0xe0, 0x80,

    /* U+E0C6 '\ue0c6' */
    0x2e, 0x89, 0xa2, 0x80,

    /* U+E0D1 '\ue0d1' */
    0x2a, 0x22,

    /* U+F031 '\uf031' */
    0xff, 0x99, 0xf0,

    /* U+F033 '\uf033' */
    0x2f, 0xb2,

    /* U+F034 '\uf034' */
    0x9b, 0xe8,

    /* U+F035 '\uf035' */
    0x23, 0xbe,

    /* U+F036 '\uf036' */
    0xfb, 0x88,

    /* U+F037 '\uf037' */
    0x5f, 0x50,

    /* U+F038 '\uf038' */
    0xaf, 0xa0,

    /* U+F039 '\uf039' */
    0x85, 0x7f, 0x58, 0x00,

    /* U+F03A '\uf03a' */
    0x0d, 0x7f, 0x50, 0x80,

    /* U+F03B '\uf03b' */
    0xb6, 0xd0,

    /* U+F03C '\uf03c' */
    0xff, 0xff,

    /* U+F03D '\uf03d' */
    0x6f, 0xf6,

    /* U+F057 '\uf057' */
    0x8c, 0xff, 0xfc, 0x80,

    /* U+F058 '\uf058' */
    0x13, 0xff, 0xf3, 0x10,

    /* U+F059 '\uf059' */
    0x57, 0xfe, 0xe2, 0x00,

    /* U+F061 '\uf061' */
    0x0e, 0xdc, 0x40,

    /* U+F073 '\uf073' */
    0x67, 0xa7, 0x33, 0x31, 0x80, 0x60,

    /* U+F078 '\uf078' */
    0x76, 0x6b, 0x37, 0x00,

    /* U+F079 '\uf079' */
    0x74, 0x7f, 0x17, 0x00,

    /* U+F07E '\uf07e' */
    0x12, 0x7e, 0x48,

    /* U+F0CF '\uf0cf' */
    0x69, 0x9f, 0xdd, 0xf0,

    /* U+F0D0 '\uf0d0' */
    0x69, 0x11, 0xfd, 0xdf,

    /* U+F0D1 '\uf0d1' */
    0x6d, 0x25, 0x50,

    /* U+F0D5 '\uf0d5' */
    0x22, 0x7d, 0x39, 0x7a, 0xa0,

    /* U+F0D6 '\uf0d6' */
    0x15, 0x13, 0xe9, 0xdf, 0xff,

    /* U+F0D7 '\uf0d7' */
    0x64, 0xee, 0xf0,

    /* U+F0D8 '\uf0d8' */
    0x64, 0xee, 0xf0, 0x15, 0x40,

    /* U+F0D9 '\uf0d9' */
    0x13, 0xfe,

    /* U+F0DA '\uf0da' */
    0x13, 0xfe, 0x0a, 0x81, 0x40,

    /* U+F0DB '\uf0db' */
    0x13, 0xfe, 0x0a, 0xa8,

    /* U+F0DC '\uf0dc' */
    0x13, 0xfe, 0x23, 0x11, 0x00,

    /* U+F0DE '\uf0de' */
    0x55, 0x00, 0x22, 0x81, 0x54,

    /* U+F0DF '\uf0df' */
    0xaa, 0xaa, 0xaa, 0x80,

    /* U+F0E0 '\uf0e0' */
    0x75, 0xe7, 0x37, 0x00,

    /* U+F0ED '\uf0ed' */
    0x21, 0x22, 0xa0,

    /* U+F0EE '\uf0ee' */
    0x54, 0x48, 0x40,

    /* U+F0EF '\uf0ef' */
    0x44, 0x60, 0x50,

    /* U+F0F0 '\uf0f0' */
    0x50, 0x31, 0x10,

};

/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/
static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0},  // U+0000 '\x00'
    {.bitmap_index = 0, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 4, .ofs_y = 0},  // U+0020 ' '
    {.bitmap_index = 1, .adv_w = 80, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},  // U+0021 '!'
    {.bitmap_index = 2, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 4},  // U+0022 '"'
    {.bitmap_index = 4, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0023 '#'
    {.bitmap_index = 8, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0024 '$'
    {.bitmap_index = 13, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},  // U+0025 '%'
    {.bitmap_index = 15, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0026 '&'
    {.bitmap_index = 20, .adv_w = 80, .box_w = 1, .box_h = 2, .ofs_x = 2, .ofs_y = 4},  // U+0027 "'"
    {.bitmap_index = 21, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},  // U+0028 '('
    {.bitmap_index = 25, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = -2},  // U+0029 ')'
    {.bitmap_index = 29, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+002A '*'
    {.bitmap_index = 31, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+002B '+'
    {.bitmap_index = 35, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -1},  // U+002C ','
    {.bitmap_index = 36, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+002D '-'
    {.bitmap_index = 37, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 0},  // U+002E '.'
    {.bitmap_index = 38, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},  // U+002F '/'
    {.bitmap_index = 42, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0030 '0'
    {.bitmap_index = 46, .adv_w = 80, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},  // U+0031 '1'
    {.bitmap_index = 48, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0032 '2'
    {.bitmap_index = 52, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0033 '3'
    {.bitmap_index = 56, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0034 '4'
    {.bitmap_index = 60, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0035 '5'
    {.bitmap_index = 64, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0036 '6'
    {.bitmap_index = 68, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0037 '7'
    {.bitmap_index = 72, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0038 '8'
    {.bitmap_index = 76, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0039 '9'
    {.bitmap_index = 80, .adv_w = 80, .box_w = 1, .box_h = 3, .ofs_x = 1, .ofs_y = 1},  // U+003A ':'
    {.bitmap_index = 81, .adv_w = 80, .box_w = 2, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+003B ';'
    {.bitmap_index = 82, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+003C '<'
    {.bitmap_index = 84, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+003D '='
    {.bitmap_index = 86, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+003E '>'
    {.bitmap_index = 88, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+003F '?'
    {.bitmap_index = 92, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+0040 '@'
    {.bitmap_index = 95, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0041 'A'
    {.bitmap_index = 99, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0042 'B'
    {.bitmap_index = 103, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0043 'C'
    {.bitmap_index = 107, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0044 'D'
    {.bitmap_index = 111, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0045 'E'
    {.bitmap_index = 115, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0046 'F'
    {.bitmap_index = 119, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0047 'G'
    {.bitmap_index = 123, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0048 'H'
    {.bitmap_index = 127, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0049 'I'
    {.bitmap_index = 130, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+004A 'J'
    {.bitmap_index = 134, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+004B 'K'
    {.bitmap_index = 138, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+004C 'L'
    {.bitmap_index = 142, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+004D 'M'
    {.bitmap_index = 146, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+004E 'N'
    {.bitmap_index = 150, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+004F 'O'
    {.bitmap_index = 154, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0050 'P'
    {.bitmap_index = 158, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},  // U+0051 'Q'
    {.bitmap_index = 162, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0052 'R'
    {.bitmap_index = 166, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0053 'S'
    {.bitmap_index = 170, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0054 'T'
    {.bitmap_index = 173, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0055 'U'
    {.bitmap_index = 177, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0056 'V'
    {.bitmap_index = 181, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0057 'W'
    {.bitmap_index = 185, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0058 'X'
    {.bitmap_index = 189, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0059 'Y'
    {.bitmap_index = 193, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+005A 'Z'
    {.bitmap_index = 197, .adv_w = 80, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},  // U+005B '['
    {.bitmap_index = 200, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},  // U+005C '\\'
    {.bitmap_index = 204, .adv_w = 80, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},  // U+005D ']'
    {.bitmap_index = 207, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},  // U+005E '^'
    {.bitmap_index = 208, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 0},  // U+005F '_'
    {.bitmap_index = 209, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},  // U+0060 '`'
    {.bitmap_index = 210, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0061 'a'
    {.bitmap_index = 214, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0062 'b'
    {.bitmap_index = 218, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0063 'c'
    {.bitmap_index = 221, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0064 'd'
    {.bitmap_index = 225, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0065 'e'
    {.bitmap_index = 228, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},  // U+0066 'f'
    {.bitmap_index = 232, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+0067 'g'
    {.bitmap_index = 236, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0068 'h'
    {.bitmap_index = 240, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0069 'i'
    {.bitmap_index = 243, .adv_w = 80, .box_w = 2, .box_h = 9, .ofs_x = 1, .ofs_y = -2},  // U+006A 'j'
    {.bitmap_index = 246, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+006B 'k'
    {.bitmap_index = 250, .adv_w = 80, .box_w = 2, .box_h = 7, .ofs_x = 1, .ofs_y = 0},  // U+006C 'l'
    {.bitmap_index = 252, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+006D 'm'
    {.bitmap_index = 255, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+006E 'n'
    {.bitmap_index = 258, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+006F 'o'
    {.bitmap_index = 261, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+0070 'p'
    {.bitmap_index = 265, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+0071 'q'
    {.bitmap_index = 269, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0072 'r'
    {.bitmap_index = 272, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0073 's'
    {.bitmap_index = 275, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0074 't'
    {.bitmap_index = 278, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0075 'u'
    {.bitmap_index = 281, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0076 'v'
    {.bitmap_index = 284, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0077 'w'
    {.bitmap_index = 287, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+0078 'x'
    {.bitmap_index = 290, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+0079 'y'
    {.bitmap_index = 294, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+007A 'z'
    {.bitmap_index = 297, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},  // U+007B '{'
    {.bitmap_index = 302, .adv_w = 80, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},  // U+007C '|'
    {.bitmap_index = 303, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},  // U+007D '}'
    {.bitmap_index = 308, .adv_w = 80, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 1},  // U+007E '~'
    {.bitmap_index = 309, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 0, .ofs_y = 0},  // U+00A0 '\xa0'
    {.bitmap_index = 310, .adv_w = 80, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},  // U+00A1 '¡'
    {.bitmap_index = 311, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+00A2 '¢'
    {.bitmap_index = 315, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00A3 '£'
    {.bitmap_index = 319, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+00A4 '¤'
    {.bitmap_index = 323, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00A5 '¥'
    {.bitmap_index = 328, .adv_w = 80, .box_w = 1, .box_h = 7, .ofs_x = 2, .ofs_y = 0},  // U+00A6 '¦'
    {.bitmap_index = 329, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00A7 '§'
    {.bitmap_index = 333, .adv_w = 80, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 6},  // U+00A8 '¨'
    {.bitmap_index = 334, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00A9 '©'
    {.bitmap_index = 339, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 2},  // U+00AA 'ª'
    {.bitmap_index = 343, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},  // U+00AB '«'
    {.bitmap_index = 345, .adv_w = 80, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 3},  // U+00AC '¬'
    {.bitmap_index = 346, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+00AD '\xad'
    {.bitmap_index = 347, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00AE '®'
    {.bitmap_index = 352, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 6},  // U+00AF '¯'
    {.bitmap_index = 353, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 3},  // U+00B0 '°'
    {.bitmap_index = 355, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+00B1 '±'
    {.bitmap_index = 359, .adv_w = 80, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},  // U+00B2 '²'
    {.bitmap_index = 361, .adv_w = 80, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},  // U+00B3 '³'
    {.bitmap_index = 363, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 4},  // U+00B4 '´'
    {.bitmap_index = 364, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+00B5 'µ'
    {.bitmap_index = 368, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},  // U+00B6 '¶'
    {.bitmap_index = 372, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 2},  // U+00B7 '·'
    {.bitmap_index = 373, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = -2},  // U+00B8 '¸'
    {.bitmap_index = 374, .adv_w = 80, .box_w = 3, .box_h = 4, .ofs_x = 1, .ofs_y = 3},  // U+00B9 '¹'
    {.bitmap_index = 376, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 1},  // U+00BA 'º'
    {.bitmap_index = 378, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},  // U+00BB '»'
    {.bitmap_index = 380, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -1},  // U+00BC '¼'
    {.bitmap_index = 384, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},  // U+00BD '½'
    {.bitmap_index = 389, .adv_w = 80, .box_w = 4, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+00BE '¾'
    {.bitmap_index = 395, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00BF '¿'
    {.bitmap_index = 399, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00C0 'À'
    {.bitmap_index = 404, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00C1 'Á'
    {.bitmap_index = 409, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00C2 'Â'
    {.bitmap_index = 414, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00C3 'Ã'
    {.bitmap_index = 419, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00C4 'Ä'
    {.bitmap_index = 424, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00C5 'Å'
    {.bitmap_index = 429, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00C6 'Æ'
    {.bitmap_index = 433, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},  // U+00C7 'Ç'
    {.bitmap_index = 438, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00C8 'È'
    {.bitmap_index = 443, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00C9 'É'
    {.bitmap_index = 448, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00CA 'Ê'
    {.bitmap_index = 453, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00CB 'Ë'
    {.bitmap_index = 458, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00CC 'Ì'
    {.bitmap_index = 462, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00CD 'Í'
    {.bitmap_index = 466, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00CE 'Î'
    {.bitmap_index = 470, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00CF 'Ï'
    {.bitmap_index = 474, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00D0 'Ð'
    {.bitmap_index = 479, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00D1 'Ñ'
    {.bitmap_index = 484, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00D2 'Ò'
    {.bitmap_index = 489, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00D3 'Ó'
    {.bitmap_index = 494, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00D4 'Ô'
    {.bitmap_index = 499, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00D5 'Õ'
    {.bitmap_index = 504, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00D6 'Ö'
    {.bitmap_index = 509, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+00D7 '×'
    {.bitmap_index = 511, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00D8 'Ø'
    {.bitmap_index = 516, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00D9 'Ù'
    {.bitmap_index = 521, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00DA 'Ú'
    {.bitmap_index = 526, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00DB 'Û'
    {.bitmap_index = 531, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00DC 'Ü'
    {.bitmap_index = 536, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+00DD 'Ý'
    {.bitmap_index = 541, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00DE 'Þ'
    {.bitmap_index = 545, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+00DF 'ß'
    {.bitmap_index = 549, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00E0 'à'
    {.bitmap_index = 553, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00E1 'á'
    {.bitmap_index = 557, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00E2 'â'
    {.bitmap_index = 561, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00E3 'ã'
    {.bitmap_index = 566, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00E4 'ä'
    {.bitmap_index = 570, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00E5 'å'
    {.bitmap_index = 574, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+00E6 'æ'
    {.bitmap_index = 577, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+00E7 'ç'
    {.bitmap_index = 581, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00E8 'è'
    {.bitmap_index = 585, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00E9 'é'
    {.bitmap_index = 589, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00EA 'ê'
    {.bitmap_index = 593, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00EB 'ë'
    {.bitmap_index = 597, .adv_w = 80, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00EC 'ì'
    {.bitmap_index = 600, .adv_w = 80, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00ED 'í'
    {.bitmap_index = 603, .adv_w = 80, .box_w = 3, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00EE 'î'
    {.bitmap_index = 606, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00EF 'ï'
    {.bitmap_index = 609, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00F0 'ð'
    {.bitmap_index = 613, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00F1 'ñ'
    {.bitmap_index = 617, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00F2 'ò'
    {.bitmap_index = 621, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00F3 'ó'
    {.bitmap_index = 625, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00F4 'ô'
    {.bitmap_index = 629, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00F5 'õ'
    {.bitmap_index = 633, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+00F6 'ö'
    {.bitmap_index = 637, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+00F7 '÷'
    {.bitmap_index = 640, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+00F8 'ø'
    {.bitmap_index = 644, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00F9 'ù'
    {.bitmap_index = 648, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00FA 'ú'
    {.bitmap_index = 652, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00FB 'û'
    {.bitmap_index = 656, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+00FC 'ü'
    {.bitmap_index = 660, .adv_w = 80, .box_w = 4, .box_h = 10, .ofs_x = 0, .ofs_y = -2},  // U+00FD 'ý'
    {.bitmap_index = 665, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},  // U+00FE 'þ'
    {.bitmap_index = 669, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = -2},  // U+00FF 'ÿ'
    {.bitmap_index = 674, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+0100 'Ā'
    {.bitmap_index = 679, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+0103 'ă'
    {.bitmap_index = 684, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+010C 'Č'
    {.bitmap_index = 689, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+010D 'č'
    {.bitmap_index = 693, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+010E 'Ď'
    {.bitmap_index = 698, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+010F 'ď'
    {.bitmap_index = 703, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+011A 'Ě'
    {.bitmap_index = 708, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+011B 'ě'
    {.bitmap_index = 712, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+013D 'Ľ'
    {.bitmap_index = 716, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},  // U+013E 'ľ'
    {.bitmap_index = 719, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+0147 'Ň'
    {.bitmap_index = 724, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+0148 'ň'
    {.bitmap_index = 728, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+0156 'Ŗ'
    {.bitmap_index = 733, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+0157 'ŗ'
    {.bitmap_index = 737, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+0160 'Š'
    {.bitmap_index = 742, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+0161 'š'
    {.bitmap_index = 746, .adv_w = 80, .box_w = 3, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+0164 'Ť'
    {.bitmap_index = 750, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0165 'ť'
    {.bitmap_index = 755, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+016E 'Ů'
    {.bitmap_index = 760, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+016F 'ů'
    {.bitmap_index = 764, .adv_w = 80, .box_w = 4, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+017D 'Ž'
    {.bitmap_index = 769, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+017E 'ž'
    {.bitmap_index = 773, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+0219 'ș'
    {.bitmap_index = 777, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 5},  // U+02C7 'ˇ'
    {.bitmap_index = 778, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 5},  // U+02DA '˚'
    {.bitmap_index = 780, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0391 'Α'
    {.bitmap_index = 784, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0392 'Β'
    {.bitmap_index = 788, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0393 'Γ'
    {.bitmap_index = 792, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0394 'Δ'
    {.bitmap_index = 797, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0395 'Ε'
    {.bitmap_index = 801, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0396 'Ζ'
    {.bitmap_index = 805, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0397 'Η'
    {.bitmap_index = 809, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0398 'Θ'
    {.bitmap_index = 813, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+0399 'Ι'
    {.bitmap_index = 816, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+039A 'Κ'
    {.bitmap_index = 820, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+039B 'Λ'
    {.bitmap_index = 825, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+039C 'Μ'
    {.bitmap_index = 829, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+039D 'Ν'
    {.bitmap_index = 833, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+039E 'Ξ'
    {.bitmap_index = 837, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+039F 'Ο'
    {.bitmap_index = 841, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A0 'Π'
    {.bitmap_index = 845, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A1 'Ρ'
    {.bitmap_index = 849, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+03A2 '\u03a2'
    {.bitmap_index = 856, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A3 'Σ'
    {.bitmap_index = 860, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A4 'Τ'
    {.bitmap_index = 863, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A5 'Υ'
    {.bitmap_index = 867, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A6 'Φ'
    {.bitmap_index = 872, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A7 'Χ'
    {.bitmap_index = 876, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A8 'Ψ'
    {.bitmap_index = 881, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+03A9 'Ω'
    {.bitmap_index = 886, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+03B1 'α'
    {.bitmap_index = 888, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},  // U+03B2 'β'
    {.bitmap_index = 892, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -2},  // U+03B3 'γ'
    {.bitmap_index = 895, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+03B4 'δ'
    {.bitmap_index = 898, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+03B5 'ε'
    {.bitmap_index = 901, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+03B6 'ζ'
    {.bitmap_index = 905, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+03B7 'η'
    {.bitmap_index = 909, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+03B8 'θ'
    {.bitmap_index = 912, .adv_w = 80, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+03B9 'ι'
    {.bitmap_index = 914, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+03BA 'κ'
    {.bitmap_index = 916, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+03BB 'λ'
    {.bitmap_index = 919, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+03BC 'μ'
    {.bitmap_index = 923, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+03BD 'ν'
    {.bitmap_index = 926, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},  // U+03BE 'ξ'
    {.bitmap_index = 930, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+03BF 'ο'
    {.bitmap_index = 933, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+03C0 'π'
    {.bitmap_index = 936, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -2},  // U+03C1 'ρ'
    {.bitmap_index = 939, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+03C2 'ς'
    {.bitmap_index = 943, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+03C3 'σ'
    {.bitmap_index = 946, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+03C4 'τ'
    {.bitmap_index = 949, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+03C5 'υ'
    {.bitmap_index = 952, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = -2},  // U+03C6 'φ'
    {.bitmap_index = 955, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = -1},  // U+03C7 'χ'
    {.bitmap_index = 958, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -2},  // U+03C8 'ψ'
    {.bitmap_index = 962, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+03C9 'ω'
    {.bitmap_index = 966, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = -2},  // U+1E9E 'ẞ'
    {.bitmap_index = 970, .adv_w = 80, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+2010 '‐'
    {.bitmap_index = 971, .adv_w = 80, .box_w = 3, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+2011 '‑'
    {.bitmap_index = 972, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+2012 '‒'
    {.bitmap_index = 973, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+2013 '–'
    {.bitmap_index = 974, .adv_w = 80, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+2014 '—'
    {.bitmap_index = 975, .adv_w = 80, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+2015 '―'
    {.bitmap_index = 976, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = 0},  // U+2016 '‖'
    {.bitmap_index = 979, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = -1},  // U+2017 '‗'
    {.bitmap_index = 981, .adv_w = 80, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 4},  // U+2018 '‘'
    {.bitmap_index = 982, .adv_w = 80, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 4},  // U+2019 '’'
    {.bitmap_index = 983, .adv_w = 80, .box_w = 2, .box_h = 3, .ofs_x = 2, .ofs_y = -2},  // U+201A '‚'
    {.bitmap_index = 984, .adv_w = 80, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 3},  // U+201B '‛'
    {.bitmap_index = 985, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},  // U+201C '“'
    {.bitmap_index = 987, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},  // U+201D '”'
    {.bitmap_index = 989, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 0},  // U+201E '„'
    {.bitmap_index = 991, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 4},  // U+201F '‟'
    {.bitmap_index = 993, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2020 '†'
    {.bitmap_index = 995, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2021 '‡'
    {.bitmap_index = 997, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 1},  // U+2022 '•'
    {.bitmap_index = 999, .adv_w = 80, .box_w = 2, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+2023 '‣'
    {.bitmap_index = 1000, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 0},  // U+2024 '․'
    {.bitmap_index = 1001, .adv_w = 80, .box_w = 3, .box_h = 1, .ofs_x = 1, .ofs_y = 0},  // U+2025 '‥'
    {.bitmap_index = 1002, .adv_w = 80, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 0},  // U+2026 '…'
    {.bitmap_index = 1003, .adv_w = 80, .box_w = 1, .box_h = 1, .ofs_x = 2, .ofs_y = 2},  // U+2027 '‧'
    {.bitmap_index = 1004, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},  // U+2032 '′'
    {.bitmap_index = 1005, .adv_w = 80, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 5},  // U+2033 '″'
    {.bitmap_index = 1006, .adv_w = 80, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 5},  // U+2034 '‴'
    {.bitmap_index = 1008, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 5},  // U+2035 '‵'
    {.bitmap_index = 1009, .adv_w = 80, .box_w = 4, .box_h = 2, .ofs_x = 1, .ofs_y = 5},  // U+2036 '‶'
    {.bitmap_index = 1010, .adv_w = 80, .box_w = 5, .box_h = 2, .ofs_x = 0, .ofs_y = 5},  // U+2037 '‷'
    {.bitmap_index = 1012, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 0, .ofs_y = 0},  // U+2038 '‸'
    {.bitmap_index = 1013, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+2039 '‹'
    {.bitmap_index = 1017, .adv_w = 80, .box_w = 2, .box_h = 3, .ofs_x = 1, .ofs_y = 3},  // U+203A '›'
    {.bitmap_index = 1018, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+203C '‼'
    {.bitmap_index = 1021, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 6},  // U+203E '‾'
    {.bitmap_index = 1022, .adv_w = 80, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 5},  // U+203F '‿'
    {.bitmap_index = 1023, .adv_w = 80, .box_w = 4, .box_h = 2, .ofs_x = 0, .ofs_y = 5},  // U+2040 '⁀'
    {.bitmap_index = 1024, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+2041 '⁁'
    {.bitmap_index = 1026, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 0, .ofs_y = 2},  // U+2042 '⁂'
    {.bitmap_index = 1028, .adv_w = 80, .box_w = 2, .box_h = 4, .ofs_x = 1, .ofs_y = -1},  // U+204F '⁏'
    {.bitmap_index = 1029, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+2050 '⁐'
    {.bitmap_index = 1032, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+2051 '⁑'
    {.bitmap_index = 1035, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+20AC '€'
    {.bitmap_index = 1038, .adv_w = 80, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+2122 '™'
    {.bitmap_index = 1044, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2190 '←'
    {.bitmap_index = 1048, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2191 '↑'
    {.bitmap_index = 1052, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2192 '→'
    {.bitmap_index = 1056, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2193 '↓'
    {.bitmap_index = 1060, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+2194 '↔'
    {.bitmap_index = 1062, .adv_w = 80, .box_w = 3, .box_h = 6, .ofs_x = 0, .ofs_y = -1},  // U+2195 '↕'
    {.bitmap_index = 1065, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+2196 '↖'
    {.bitmap_index = 1067, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+2197 '↗'
    {.bitmap_index = 1069, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+2198 '↘'
    {.bitmap_index = 1071, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+2199 '↙'
    {.bitmap_index = 1073, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+21D0 '⇐'
    {.bitmap_index = 1077, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+21D1 '⇑'
    {.bitmap_index = 1081, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+21D2 '⇒'
    {.bitmap_index = 1085, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = -1},  // U+21D3 '⇓'
    {.bitmap_index = 1089, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+2200 '∀'
    {.bitmap_index = 1093, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+2201 '∁'
    {.bitmap_index = 1097, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+2202 '∂'
    {.bitmap_index = 1101, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+2203 '∃'
    {.bitmap_index = 1105, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+2204 '∄'
    {.bitmap_index = 1109, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+2205 '∅'
    {.bitmap_index = 1112, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 1},  // U+2206 '∆'
    {.bitmap_index = 1115, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 2},  // U+2207 '∇'
    {.bitmap_index = 1118, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2208 '∈'
    {.bitmap_index = 1121, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+2209 '∉'
    {.bitmap_index = 1125, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+220A '∊'
    {.bitmap_index = 1128, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+220B '∋'
    {.bitmap_index = 1131, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+220C '∌'
    {.bitmap_index = 1135, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+220D '∍'
    {.bitmap_index = 1138, .adv_w = 80, .box_w = 3, .box_h = 3, .ofs_x = 1, .ofs_y = 1},  // U+220E '∎'
    {.bitmap_index = 1140, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+220F '∏'
    {.bitmap_index = 1143, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+2210 '∐'
    {.bitmap_index = 1146, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+2211 '∑'
    {.bitmap_index = 1149, .adv_w = 80, .box_w = 4, .box_h = 1, .ofs_x = 0, .ofs_y = 2},  // U+2212 '−'
    {.bitmap_index = 1150, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2213 '∓'
    {.bitmap_index = 1152, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2260 '≠'
    {.bitmap_index = 1155, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+229E '⊞'
    {.bitmap_index = 1159, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+229F '⊟'
    {.bitmap_index = 1163, .adv_w = 80, .box_w = 5, .box_h = 1, .ofs_x = 0, .ofs_y = 4},  // U+2500 '─'
    {.bitmap_index = 1164, .adv_w = 80, .box_w = 1, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+2502 '│'
    {.bitmap_index = 1166, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = -2},  // U+250C '┌'
    {.bitmap_index = 1169, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = -2},  // U+250D '┍'
    {.bitmap_index = 1172, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = -2},  // U+250E '┎'
    {.bitmap_index = 1175, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = -2},  // U+250F '┏'
    {.bitmap_index = 1178, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+2510 '┐'
    {.bitmap_index = 1181, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+2511 '┑'
    {.bitmap_index = 1184, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+2512 '┒'
    {.bitmap_index = 1187, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+2513 '┓'
    {.bitmap_index = 1190, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 4},  // U+2514 '└'
    {.bitmap_index = 1192, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 4},  // U+2515 '┕'
    {.bitmap_index = 1194, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 4},  // U+2516 '┖'
    {.bitmap_index = 1196, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 4},  // U+2517 '┗'
    {.bitmap_index = 1198, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+2518 '┘'
    {.bitmap_index = 1200, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+2519 '┙'
    {.bitmap_index = 1202, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+251A '┚'
    {.bitmap_index = 1204, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+251B '┛'
    {.bitmap_index = 1206, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+251C '├'
    {.bitmap_index = 1211, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+251D '┝'
    {.bitmap_index = 1216, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+251E '┞'
    {.bitmap_index = 1221, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+251F '┟'
    {.bitmap_index = 1226, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+2520 '┠'
    {.bitmap_index = 1231, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+2521 '┡'
    {.bitmap_index = 1236, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+2522 '┢'
    {.bitmap_index = 1241, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 2, .ofs_y = -2},  // U+2523 '┣'
    {.bitmap_index = 1246, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2524 '┤'
    {.bitmap_index = 1251, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2525 '┥'
    {.bitmap_index = 1256, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2526 '┦'
    {.bitmap_index = 1261, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2527 '┧'
    {.bitmap_index = 1266, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2528 '┨'
    {.bitmap_index = 1271, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2529 '┩'
    {.bitmap_index = 1276, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+252A '┪'
    {.bitmap_index = 1281, .adv_w = 80, .box_w = 3, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+252B '┫'
    {.bitmap_index = 1286, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+252C '┬'
    {.bitmap_index = 1291, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+252D '┭'
    {.bitmap_index = 1296, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+252E '┮'
    {.bitmap_index = 1301, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+252F '┯'
    {.bitmap_index = 1306, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+2530 '┰'
    {.bitmap_index = 1311, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+2531 '┱'
    {.bitmap_index = 1316, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+2532 '┲'
    {.bitmap_index = 1321, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+2533 '┳'
    {.bitmap_index = 1326, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+2534 '┴'
    {.bitmap_index = 1330, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+2535 '┵'
    {.bitmap_index = 1334, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+2536 '┶'
    {.bitmap_index = 1338, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+2537 '┷'
    {.bitmap_index = 1342, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+2538 '┸'
    {.bitmap_index = 1346, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+2539 '┹'
    {.bitmap_index = 1350, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+253A '┺'
    {.bitmap_index = 1354, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+253B '┻'
    {.bitmap_index = 1358, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+253C '┼'
    {.bitmap_index = 1365, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+253D '┽'
    {.bitmap_index = 1372, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+253E '┾'
    {.bitmap_index = 1379, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+253F '┿'
    {.bitmap_index = 1386, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2540 '╀'
    {.bitmap_index = 1393, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2541 '╁'
    {.bitmap_index = 1400, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2542 '╂'
    {.bitmap_index = 1407, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2543 '╃'
    {.bitmap_index = 1414, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2544 '╄'
    {.bitmap_index = 1421, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2545 '╅'
    {.bitmap_index = 1428, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2546 '╆'
    {.bitmap_index = 1435, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2547 '╇'
    {.bitmap_index = 1442, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2548 '╈'
    {.bitmap_index = 1449, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+2549 '╉'
    {.bitmap_index = 1456, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+254A '╊'
    {.bitmap_index = 1463, .adv_w = 80, .box_w = 5, .box_h = 11, .ofs_x = 0, .ofs_y = -2},  // U+254B '╋'
    {.bitmap_index = 1470, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 2, .ofs_y = -2},  // U+256D '╭'
    {.bitmap_index = 1473, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -2},  // U+256E '╮'
    {.bitmap_index = 1476, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 4},  // U+256F '╯'
    {.bitmap_index = 1478, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 4},  // U+2570 '╰'
    {.bitmap_index = 1480, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},  // U+25A1 '□'
    {.bitmap_index = 1482, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 1},  // U+25A2 '▢'
    {.bitmap_index = 1484, .adv_w = 80, .box_w = 2, .box_h = 2, .ofs_x = 1, .ofs_y = 2},  // U+25AA '▪'
    {.bitmap_index = 1485, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+25B2 '▲'
    {.bitmap_index = 1487, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+25B3 '△'
    {.bitmap_index = 1489, .adv_w = 80, .box_w = 3, .box_h = 2, .ofs_x = 1, .ofs_y = 1},  // U+25B4 '▴'
    {.bitmap_index = 1490, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+2600 '☀'
    {.bitmap_index = 1495, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 2},  // U+2601 '☁'
    {.bitmap_index = 1497, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},  // U+2602 '☂'
    {.bitmap_index = 1502, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2661 '♡'
    {.bitmap_index = 1506, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2665 '♥'
    {.bitmap_index = 1510, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+2713 '✓'
    {.bitmap_index = 1514, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+2714 '✔'
    {.bitmap_index = 1518, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2715 '✕'
    {.bitmap_index = 1522, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2716 '✖'
    {.bitmap_index = 1526, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+272E '✮'
    {.bitmap_index = 1530, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+2744 '❄'
    {.bitmap_index = 1535, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+27C2 '⟂'
    {.bitmap_index = 1537, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+27C3 '⟃'
    {.bitmap_index = 1540, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+27C4 '⟄'
    {.bitmap_index = 1543, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+27D6 '⟖'
    {.bitmap_index = 1547, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+27D7 '⟗'
    {.bitmap_index = 1551, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+27DC '⟜'
    {.bitmap_index = 1553, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+27DD '⟝'
    {.bitmap_index = 1555, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+27DE '⟞'
    {.bitmap_index = 1557, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+2919 '⤙'
    {.bitmap_index = 1561, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+291A '⤚'
    {.bitmap_index = 1565, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+291B '⤛'
    {.bitmap_index = 1569, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+291C '⤜'
    {.bitmap_index = 1573, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+2B60 '⭠'
    {.bitmap_index = 1577, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+2B61 '⭡'
    {.bitmap_index = 1581, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+2B62 '⭢'
    {.bitmap_index = 1586, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+2B64 '⭤'
    {.bitmap_index = 1590, .adv_w = 80, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+2B80 '⮀'
    {.bitmap_index = 1596, .adv_w = 80, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+2B81 '⮁'
    {.bitmap_index = 1602, .adv_w = 80, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+2B82 '⮂'
    {.bitmap_index = 1608, .adv_w = 80, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = 0},  // U+2B83 '⮃'
    {.bitmap_index = 1614, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+E0A0 '\ue0a0'
    {.bitmap_index = 1618, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+E0A1 '\ue0a1'
    {.bitmap_index = 1622, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+E0A2 '\ue0a2'
    {.bitmap_index = 1626, .adv_w = 80, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},  // U+E0B0 '\ue0b0'
    {.bitmap_index = 1633, .adv_w = 80, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},  // U+E0B1 '\ue0b1'
    {.bitmap_index = 1640, .adv_w = 80, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},  // U+E0B2 '\ue0b2'
    {.bitmap_index = 1647, .adv_w = 80, .box_w = 5, .box_h = 10, .ofs_x = 0, .ofs_y = -1},  // U+E0B3 '\ue0b3'
    {.bitmap_index = 1654, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+E0C0 '\ue0c0'
    {.bitmap_index = 1658, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 2, .ofs_y = 0},  // U+E0C1 '\ue0c1'
    {.bitmap_index = 1660, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = -1},  // U+E0C2 '\ue0c2'
    {.bitmap_index = 1665, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+E0C3 '\ue0c3'
    {.bitmap_index = 1669, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+E0C4 '\ue0c4'
    {.bitmap_index = 1673, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+E0C5 '\ue0c5'
    {.bitmap_index = 1677, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+E0C6 '\ue0c6'
    {.bitmap_index = 1681, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+E0D1 '\ue0d1'
    {.bitmap_index = 1683, .adv_w = 80, .box_w = 4, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F031 '\uf031'
    {.bitmap_index = 1686, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F033 '\uf033'
    {.bitmap_index = 1688, .adv_w = 80, .box_w = 3, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F034 '\uf034'
    {.bitmap_index = 1690, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+F035 '\uf035'
    {.bitmap_index = 1692, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+F036 '\uf036'
    {.bitmap_index = 1694, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+F037 '\uf037'
    {.bitmap_index = 1696, .adv_w = 80, .box_w = 4, .box_h = 3, .ofs_x = 0, .ofs_y = 1},  // U+F038 '\uf038'
    {.bitmap_index = 1698, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F039 '\uf039'
    {.bitmap_index = 1702, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F03A '\uf03a'
    {.bitmap_index = 1706, .adv_w = 80, .box_w = 3, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+F03B '\uf03b'
    {.bitmap_index = 1708, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+F03C '\uf03c'
    {.bitmap_index = 1710, .adv_w = 80, .box_w = 4, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+F03D '\uf03d'
    {.bitmap_index = 1712, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+F057 '\uf057'
    {.bitmap_index = 1716, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+F058 '\uf058'
    {.bitmap_index = 1720, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F059 '\uf059'
    {.bitmap_index = 1724, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+F061 '\uf061'
    {.bitmap_index = 1727, .adv_w = 80, .box_w = 5, .box_h = 9, .ofs_x = 0, .ofs_y = -2},  // U+F073 '\uf073'
    {.bitmap_index = 1733, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F078 '\uf078'
    {.bitmap_index = 1737, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F079 '\uf079'
    {.bitmap_index = 1741, .adv_w = 80, .box_w = 4, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+F07E '\uf07e'
    {.bitmap_index = 1744, .adv_w = 80, .box_w = 4, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+F0CF '\uf0cf'
    {.bitmap_index = 1748, .adv_w = 80, .box_w = 4, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+F0D0 '\uf0d0'
    {.bitmap_index = 1752, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+F0D1 '\uf0d1'
    {.bitmap_index = 1755, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = 0},  // U+F0D5 '\uf0d5'
    {.bitmap_index = 1760, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+F0D6 '\uf0d6'
    {.bitmap_index = 1765, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 2},  // U+F0D7 '\uf0d7'
    {.bitmap_index = 1768, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+F0D8 '\uf0d8'
    {.bitmap_index = 1773, .adv_w = 80, .box_w = 5, .box_h = 3, .ofs_x = 0, .ofs_y = 3},  // U+F0D9 '\uf0d9'
    {.bitmap_index = 1775, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+F0DA '\uf0da'
    {.bitmap_index = 1780, .adv_w = 80, .box_w = 5, .box_h = 6, .ofs_x = 0, .ofs_y = 0},  // U+F0DB '\uf0db'
    {.bitmap_index = 1784, .adv_w = 80, .box_w = 5, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+F0DC '\uf0dc'
    {.bitmap_index = 1789, .adv_w = 80, .box_w = 5, .box_h = 8, .ofs_x = 0, .ofs_y = 0},  // U+F0DE '\uf0de'
    {.bitmap_index = 1794, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F0DF '\uf0df'
    {.bitmap_index = 1798, .adv_w = 80, .box_w = 5, .box_h = 5, .ofs_x = 0, .ofs_y = 0},  // U+F0E0 '\uf0e0'
    {.bitmap_index = 1802, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 0},  // U+F0ED '\uf0ed'
    {.bitmap_index = 1805, .adv_w = 80, .box_w = 5, .box_h = 4, .ofs_x = 0, .ofs_y = 4},  // U+F0EE '\uf0ee'
    {.bitmap_index = 1808, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 1, .ofs_y = -1},  // U+F0EF '\uf0ef'
    {.bitmap_index = 1811, .adv_w = 80, .box_w = 3, .box_h = 7, .ofs_x = 0, .ofs_y = -1},  // U+F0F0 '\uf0f0'
};

static const uint16_t unicode_list_2[] = {
    0, 9, 10, 11, 12, 23, 24, 58, 59, 68, 69, 83, 84, 93, 94, 97, 98, 107, 108, 122, 123, 278, 452, 471, 
};

static const uint16_t unicode_list_5[] = {
    0, 
};

static const uint16_t unicode_list_7[] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 10, 12, 13, 14, 15, 16, 29, 30, 31, 122, 240, 350, 351, 352, 353, 354, 355, 356, 357, 358, 359, 414, 415, 416, 417, 
};

static const uint16_t unicode_list_9[] = {
    0, 62, 63, 672, 674, 
};

static const uint16_t unicode_list_11[] = {
    0, 1, 2, 3, 52, 53, 61, 69, 70, 71, 147, 148, 149, 244, 248, 422, 423, 424, 425, 449, 471, 597, 598, 599, 617, 618, 623, 624, 625, 940, 941, 942, 943, 1523, 1524, 1525, 1527, 1555, 1556, 1557, 1558, 47923, 47924, 47925, 47939, 47940, 47941, 47942, 47955, 47956, 47957, 47958, 47959, 47960, 47961, 47972, 51908, 51910, 51911, 51912, 51913, 51914, 51915, 51916, 51917, 51918, 51919, 51920, 51946, 51947, 51948, 51956, 51974, 51979, 51980, 51985, 52066, 52067, 52068, 52072, 52073, 52074, 52075, 52076, 52077, 52078, 52079, 52081, 52082, 52083, 52096, 52097, 52098, 52099, 
};

static const lv_font_fmt_txt_cmap_t cmaps[] = {
    {
        .range_start = 32, .range_length = 95, .glyph_id_start = 1,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 160, .range_length = 97, .glyph_id_start = 96,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 259, .range_length = 472, .glyph_id_start = 193,
        .unicode_list = unicode_list_2, .glyph_id_ofs_list = NULL, .list_length = 24, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 913, .range_length = 25, .glyph_id_start = 217,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 945, .range_length = 25, .glyph_id_start = 242,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 7838, .range_length = 1, .glyph_id_start = 267,
        .unicode_list = unicode_list_5, .glyph_id_ofs_list = NULL, .list_length = 1, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 8208, .range_length = 24, .glyph_id_start = 268,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8242, .range_length = 418, .glyph_id_start = 292,
        .unicode_list = unicode_list_7, .glyph_id_ofs_list = NULL, .list_length = 34, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 8704, .range_length = 20, .glyph_id_start = 326,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 8800, .range_length = 675, .glyph_id_start = 346,
        .unicode_list = unicode_list_9, .glyph_id_ofs_list = NULL, .list_length = 5, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
    {
        .range_start = 9484, .range_length = 64, .glyph_id_start = 351,
        .unicode_list = NULL, .glyph_id_ofs_list = NULL, .list_length = 0, .type = LV_FONT_FMT_TXT_CMAP_FORMAT0_TINY
    },
    {
        .range_start = 9581, .range_length = 52100, .glyph_id_start = 415,
        .unicode_list = unicode_list_11, .glyph_id_ofs_list = NULL, .list_length = 94, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    },
};

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
    .cmap_num = 12,
    .bpp = 1,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t creep211 = {
#else
lv_font_t creep211 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 11,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0)
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};
    