// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.3.3
// PROJECT: CrazyCube_CubeAsst

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_CrazyAsstScreen;
lv_obj_t *ui_CrazyAsstPanel;
lv_obj_t *ui_CrazyAsstTitleLabel;
lv_obj_t *ui_CrazyAsstContentLabel;
lv_obj_t *ui_CrazyAsstHintLabel;

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
void ui_CrazyAsstScreen_screen_init(void)
{
ui_CrazyAsstScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_CrazyAsstScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_CrazyAsstScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CrazyAsstScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CrazyAsstPanel = lv_obj_create(ui_CrazyAsstScreen);
lv_obj_set_width( ui_CrazyAsstPanel, lv_pct(100));
lv_obj_set_height( ui_CrazyAsstPanel, lv_pct(100));
lv_obj_set_x( ui_CrazyAsstPanel, 0 );
lv_obj_set_y( ui_CrazyAsstPanel, -1 );
lv_obj_set_align( ui_CrazyAsstPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_CrazyAsstPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_CrazyAsstPanel, lv_color_hex(0xFFFFFF), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CrazyAsstPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_CrazyAsstPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_left(ui_CrazyAsstPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_CrazyAsstPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_CrazyAsstPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_CrazyAsstPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CrazyAsstTitleLabel = lv_label_create(ui_CrazyAsstPanel);
lv_obj_set_width( ui_CrazyAsstTitleLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CrazyAsstTitleLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CrazyAsstTitleLabel, 0 );
lv_obj_set_y( ui_CrazyAsstTitleLabel, 30 );
lv_obj_set_align( ui_CrazyAsstTitleLabel, LV_ALIGN_TOP_MID );
lv_label_set_text(ui_CrazyAsstTitleLabel,"语音唤醒");
lv_obj_set_style_text_font(ui_CrazyAsstTitleLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CrazyAsstContentLabel = lv_label_create(ui_CrazyAsstPanel);
lv_obj_set_height( ui_CrazyAsstContentLabel, 160);
lv_obj_set_width( ui_CrazyAsstContentLabel, lv_pct(90));
lv_obj_set_x( ui_CrazyAsstContentLabel, 14 );
lv_obj_set_y( ui_CrazyAsstContentLabel, -15 );
lv_obj_set_align( ui_CrazyAsstContentLabel, LV_ALIGN_BOTTOM_LEFT );
lv_label_set_text(ui_CrazyAsstContentLabel,"1.长按背后系统按钮\n2.语音 Marvin\n3.顺时针手势\n\n注: 方法2、3 仅在当前 APP 有效");
lv_obj_set_style_text_font(ui_CrazyAsstContentLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CrazyAsstHintLabel = lv_label_create(ui_CrazyAsstScreen);
lv_obj_set_width( ui_CrazyAsstHintLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CrazyAsstHintLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CrazyAsstHintLabel, -2 );
lv_obj_set_y( ui_CrazyAsstHintLabel, -2 );
lv_obj_set_align( ui_CrazyAsstHintLabel, LV_ALIGN_BOTTOM_RIGHT );
lv_label_set_text(ui_CrazyAsstHintLabel,"1/2 >>");
lv_obj_set_style_text_color(ui_CrazyAsstHintLabel, lv_color_hex(0x00FF00), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_text_opa(ui_CrazyAsstHintLabel, 255, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_text_font(ui_CrazyAsstHintLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_CrazyAsstScreen_screen_init();
// lv_disp_load_scr( ui_CrazyAsstScreen);
// }
