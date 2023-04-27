// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.1.0
// LVGL VERSION: 8.2
// PROJECT: CrazyCube_Relax

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t * ui_RelaxScreen;
lv_obj_t * ui_GameTitleLabel;
lv_obj_t * ui_RelaxManualLabel;
lv_obj_t * ui_RelaxHintLabel;
lv_obj_t * ui_RelaxDirectionHintLabel;
lv_obj_t * ui_RelaxDirectionLabel;

///////////////////// TEST LVGL SETTINGS ////////////////////
#if LV_COLOR_DEPTH != 16
    #error "LV_COLOR_DEPTH should be 16bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

///////////////////// SCREENS ////////////////////
void ui_RelaxScreen_screen_init(void)
{
    ui_RelaxScreen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_RelaxScreen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_RelaxScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_RelaxScreen, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_GameTitleLabel = lv_label_create(ui_RelaxScreen);
    lv_obj_set_width(ui_GameTitleLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_GameTitleLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_GameTitleLabel, 0);
    lv_obj_set_y(ui_GameTitleLabel, 25);
    lv_obj_set_align(ui_GameTitleLabel, LV_ALIGN_TOP_MID);
    lv_label_set_text(ui_GameTitleLabel, "贪食蛇");
    lv_obj_set_style_text_font(ui_GameTitleLabel, &ui_font_SourceHanCrazyCube30, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RelaxManualLabel = lv_label_create(ui_RelaxScreen);
    lv_obj_set_width(ui_RelaxManualLabel, lv_pct(90));
    lv_obj_set_height(ui_RelaxManualLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RelaxManualLabel, 0);
    lv_obj_set_y(ui_RelaxManualLabel, -45);
    lv_obj_set_align(ui_RelaxManualLabel, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_RelaxManualLabel,
                      "顺时针手势开始\n逆时针退出\n左右上下旋转立方豆控制方向");
    lv_obj_set_style_text_font(ui_RelaxManualLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RelaxHintLabel = lv_label_create(ui_RelaxScreen);
    lv_obj_set_width(ui_RelaxHintLabel, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_RelaxHintLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RelaxHintLabel, 20);
    lv_obj_set_y(ui_RelaxHintLabel, 30);
    lv_label_set_text(ui_RelaxHintLabel, "<<");
    lv_obj_set_style_text_font(ui_RelaxHintLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RelaxDirectionHintLabel = lv_label_create(ui_RelaxScreen);
    lv_obj_set_width(ui_RelaxDirectionHintLabel, LV_SIZE_CONTENT);   /// 90
    lv_obj_set_height(ui_RelaxDirectionHintLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RelaxDirectionHintLabel, -30);
    lv_obj_set_y(ui_RelaxDirectionHintLabel, -10);
    lv_obj_set_align(ui_RelaxDirectionHintLabel, LV_ALIGN_BOTTOM_MID);
    lv_label_set_text(ui_RelaxDirectionHintLabel, "方向：");
    lv_obj_set_style_text_font(ui_RelaxDirectionHintLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_RelaxDirectionLabel = lv_label_create(ui_RelaxScreen);
    lv_obj_set_width(ui_RelaxDirectionLabel, LV_SIZE_CONTENT);   /// 90
    lv_obj_set_height(ui_RelaxDirectionLabel, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_RelaxDirectionLabel, 120);
    lv_obj_set_y(ui_RelaxDirectionLabel, -10);
    lv_obj_set_align(ui_RelaxDirectionLabel, LV_ALIGN_BOTTOM_LEFT);
    lv_label_set_text(ui_RelaxDirectionLabel, "重启中...");
    lv_obj_set_style_text_font(ui_RelaxDirectionLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN | LV_STATE_DEFAULT);

}

// void ui_init(void)
// {
//     lv_disp_t * dispp = lv_disp_get_default();
//     lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
//                                                true, LV_FONT_DEFAULT);
//     lv_disp_set_theme(dispp, theme);
//     ui_RelaxScreen_screen_init();
//     lv_disp_load_scr(ui_RelaxScreen);
// }
