/*******************************************************************************
 * Size: 36 px
 * Bpp: 1
 * Opts: --bpp 1 --size 36 --font D:/文档/SquareLine/examples/Smart_Gadget/assets/fonts/icon_eco.ttf -o D:/文档/SquareLine/examples/Smart_Gadget/assets/fonts\ui_font_iconeco30.c --format lvgl -r 0xe609 -r 0xe628 -r 0xe687 --no-compress --no-prefilter
 ******************************************************************************/

#include "../ui.h"

#ifndef UI_FONT_ICONECO30
#define UI_FONT_ICONECO30 1
#endif

#if UI_FONT_ICONECO30

/*-----------------
 *    BITMAPS
 *----------------*/

/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+E609 "" */
    0x3f, 0xff, 0xff, 0xfc, 0x7f, 0xff, 0xff, 0xfe,
    0xff, 0xff, 0xff, 0xff, 0xe0, 0x0, 0x0, 0x7,
    0xe0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x7,
    0xe0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x7,
    0xe1, 0x0, 0x0, 0x7, 0xe3, 0x80, 0x0, 0x7,
    0xe3, 0x80, 0x0, 0x7, 0xe3, 0x80, 0x0, 0x7,
    0xe3, 0x80, 0x0, 0xc7, 0xe3, 0x80, 0x1, 0xc7,
    0xe3, 0x80, 0x3, 0x87, 0xe3, 0x80, 0x7, 0x7,
    0xe3, 0x88, 0xe, 0x7, 0xe3, 0xbe, 0x1c, 0x7,
    0xe3, 0xf7, 0xb8, 0x7, 0xe3, 0xc1, 0xf0, 0x7,
    0xe3, 0x80, 0x60, 0x7, 0xe3, 0x80, 0x0, 0x7,
    0xe3, 0x80, 0x0, 0x7, 0xe3, 0x80, 0x0, 0x7,
    0xe3, 0xff, 0xff, 0xc7, 0xe3, 0xff, 0xff, 0xc7,
    0xe0, 0x0, 0x0, 0x7, 0xe0, 0x0, 0x0, 0x7,
    0xe0, 0x0, 0x0, 0x7, 0xff, 0xff, 0xff, 0xff,
    0x7f, 0xff, 0xff, 0xfe, 0x3f, 0xff, 0xff, 0xfc,
    0x3, 0xff, 0xff, 0xc0, 0x3, 0xff, 0xff, 0xc0,
    0x3, 0xff, 0xff, 0xc0, 0x0, 0xff, 0xff, 0x0,

    /* U+E628 "" */
    0xf, 0xff, 0xff, 0xfe, 0x1, 0xff, 0xff, 0xff,
    0xf8, 0x33, 0xfc, 0x3, 0xfe, 0xc6, 0x1f, 0x0,
    0xf, 0xc6, 0xe1, 0xc0, 0x20, 0x3c, 0x7f, 0xb0,
    0x2, 0x0, 0xef, 0xfe, 0x10, 0x20, 0x87, 0xff,
    0xc1, 0x82, 0x18, 0x7f, 0xfc, 0x8, 0x21, 0x3,
    0xff, 0x80, 0xc0, 0x30, 0x1f, 0xf8, 0x4, 0x2,
    0x1, 0xff, 0x30, 0x0, 0x10, 0xcf, 0xf1, 0xc0,
    0x3, 0x38, 0xfe, 0x6, 0x0, 0xe6, 0x7, 0xe0,
    0x0, 0x3c, 0x0, 0x7e, 0x0, 0xf, 0xc0, 0x7,
    0xe0, 0x0, 0xf8, 0x0, 0x7e, 0x0, 0x1f, 0xc0,
    0x7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xf8, 0xff, 0xff, 0xff, 0xff, 0x8f, 0xff, 0xff,
    0xff, 0xfa, 0xff, 0xff, 0xff, 0xff, 0x27, 0xff,
    0xff, 0xff, 0xf2, 0x7f, 0xff, 0xf3, 0xff, 0x77,
    0xfe, 0xfe, 0x1f, 0xe0, 0x3f, 0xc7, 0xe1, 0xfe,
    0x3, 0xfc, 0x77, 0x3f, 0xef, 0x3f, 0xee, 0x3f,
    0xfc, 0xf9, 0xff, 0xc1, 0xff, 0xcf, 0x9f, 0xf8,
    0xf, 0xff, 0xff, 0xff, 0x0,

    /* U+E687 "" */
    0x1f, 0xff, 0xff, 0xf8, 0x7f, 0xff, 0xff, 0xfe,
    0x7f, 0xff, 0xff, 0xfe, 0xf3, 0xf0, 0xf, 0xc7,
    0xf1, 0xc1, 0x83, 0xc7, 0xf3, 0x1, 0x84, 0xc7,
    0xfe, 0x21, 0x84, 0x7f, 0xfc, 0x31, 0x8c, 0x3f,
    0xf8, 0x10, 0x8, 0x1f, 0xf8, 0x0, 0x0, 0x1f,
    0xf7, 0x0, 0x4, 0xef, 0xf1, 0x80, 0x9, 0x8f,
    0xf0, 0x0, 0x38, 0xf, 0xe0, 0x0, 0x70, 0x7,
    0xe0, 0x3, 0xe0, 0x7, 0xe0, 0x7, 0xe0, 0x7,
    0xe0, 0x7, 0xe0, 0x7, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff,
    0xff, 0xe7, 0xe7, 0xff, 0xff, 0xe3, 0xc7, 0xff,
    0xff, 0xf3, 0xcf, 0xff, 0xff, 0xf3, 0xcf, 0xff,
    0xff, 0xf1, 0x9f, 0xff, 0xff, 0xf9, 0x9f, 0xff,
    0xe3, 0xf9, 0x1f, 0xcf, 0xe3, 0xfc, 0x3f, 0xc7,
    0x67, 0xfc, 0x3f, 0xce, 0x7f, 0xff, 0xff, 0xfe,
    0x1f, 0xff, 0xff, 0xf8
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 576, .box_w = 32, .box_h = 36, .ofs_x = 2, .ofs_y = -5},
    {.bitmap_index = 144, .adv_w = 576, .box_w = 36, .box_h = 33, .ofs_x = 0, .ofs_y = -3},
    {.bitmap_index = 293, .adv_w = 576, .box_w = 32, .box_h = 31, .ofs_x = 2, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x1f, 0x7e
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 58889, .range_length = 127, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 3, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
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
const lv_font_t ui_font_iconeco30 = {
#else
lv_font_t ui_font_iconeco30 = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 36,          /*The maximum line height required by the font*/
    .base_line = 5,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = 0,
    .underline_thickness = 0,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};



#endif /*#if UI_FONT_ICONECO30*/

