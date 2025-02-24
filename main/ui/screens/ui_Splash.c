// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.3.4
// LVGL version: 8.3.6
// Project name: Smart_Gadget

#include "../ui.h"

void ui_Splash_screen_init(void)
{
    ui_Splash = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Splash, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Splash, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Splash, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_tiled(ui_Splash, true, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Demo = ui_Small_Label_create(ui_Splash);
    lv_obj_set_x(ui_Demo, 0);
    lv_obj_set_y(ui_Demo, 77);
    lv_obj_set_align(ui_Demo, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Demo, "TJ-SDU");
    lv_obj_set_style_text_color(ui_Demo, lv_color_hex(0x9C9CD9), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_Demo, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_align(ui_Demo, LV_TEXT_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_UAV_Control = ui_Small_Label_create(ui_Splash);
    lv_obj_set_x(ui_UAV_Control, 0);
    lv_obj_set_y(ui_UAV_Control, 50);
    lv_obj_set_align(ui_UAV_Control, LV_ALIGN_CENTER);
    lv_label_set_text(ui_UAV_Control, "UAV Control");
    lv_obj_set_style_text_color(ui_UAV_Control, lv_color_hex(0x000746), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_text_opa(ui_UAV_Control, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Image4 = lv_img_create(ui_Splash);
    lv_img_set_src(ui_Image4, &ui_img_uav_png);
    lv_obj_set_width(ui_Image4, LV_SIZE_CONTENT);   /// 127
    lv_obj_set_height(ui_Image4, LV_SIZE_CONTENT);    /// 127
    lv_obj_set_x(ui_Image4, 0);
    lv_obj_set_y(ui_Image4, -50);
    lv_obj_set_align(ui_Image4, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image4, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image4, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    lv_obj_add_event_cb(ui_Splash, ui_event_Splash, LV_EVENT_ALL, NULL);

}
