// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.0
// LVGL VERSION: 8.2.0
// PROJECT: CrazyFM

#include "ui.h"
#include "lv/ui_helpers.h"

///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_CrazyFMScreen;
lv_obj_t *ui_CrazyFMScreenEffectPanel;
lv_obj_t *ui_CrazyFMScreenColorwheel;
lv_obj_t *ui_CrazyFMScreenSpinner;
lv_obj_t *ui_CrazyFMCoverImage;
lv_obj_t *ui_CrazyFMTitleLabel;
lv_obj_t *ui_CrazyFMStateLabel;

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
void ui_CrazyFMScreen_screen_init(void)
{
ui_CrazyFMScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_CrazyFMScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_CrazyFMScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CrazyFMScreen, 255, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CrazyFMScreenEffectPanel = lv_obj_create(ui_CrazyFMScreen);
lv_obj_set_width( ui_CrazyFMScreenEffectPanel, lv_pct(100));
lv_obj_set_height( ui_CrazyFMScreenEffectPanel, lv_pct(100));
lv_obj_set_align( ui_CrazyFMScreenEffectPanel, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_CrazyFMScreenEffectPanel, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_CrazyFMScreenEffectPanel, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );
lv_obj_set_style_bg_opa(ui_CrazyFMScreenEffectPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);
lv_obj_set_style_border_width(ui_CrazyFMScreenEffectPanel, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CrazyFMScreenColorwheel = lv_colorwheel_create(ui_CrazyFMScreenEffectPanel,true);
lv_obj_set_width( ui_CrazyFMScreenColorwheel, 150);
lv_obj_set_height( ui_CrazyFMScreenColorwheel, 150);
lv_obj_set_align( ui_CrazyFMScreenColorwheel, LV_ALIGN_CENTER );
lv_obj_set_style_arc_width(ui_CrazyFMScreenColorwheel, 8, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_pad_left(ui_CrazyFMScreenColorwheel, -10, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_pad_right(ui_CrazyFMScreenColorwheel, -10, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_pad_top(ui_CrazyFMScreenColorwheel, -10, LV_PART_KNOB| LV_STATE_DEFAULT);
lv_obj_set_style_pad_bottom(ui_CrazyFMScreenColorwheel, -10, LV_PART_KNOB| LV_STATE_DEFAULT);

ui_CrazyFMScreenSpinner = lv_spinner_create(ui_CrazyFMScreenEffectPanel,2000,90);
lv_obj_set_width( ui_CrazyFMScreenSpinner, 150);
lv_obj_set_height( ui_CrazyFMScreenSpinner, 150);
lv_obj_set_align( ui_CrazyFMScreenSpinner, LV_ALIGN_CENTER );
lv_obj_clear_flag( ui_CrazyFMScreenSpinner, LV_OBJ_FLAG_CLICKABLE );    /// Flags
lv_obj_set_style_arc_width(ui_CrazyFMScreenSpinner, 0, LV_PART_MAIN| LV_STATE_DEFAULT);

lv_obj_set_style_arc_color(ui_CrazyFMScreenSpinner, lv_color_hex(0x000000), LV_PART_INDICATOR | LV_STATE_DEFAULT );
lv_obj_set_style_arc_opa(ui_CrazyFMScreenSpinner, 255, LV_PART_INDICATOR| LV_STATE_DEFAULT);
lv_obj_set_style_arc_width(ui_CrazyFMScreenSpinner, 8, LV_PART_INDICATOR| LV_STATE_DEFAULT);

ui_CrazyFMCoverImage = lv_img_create(ui_CrazyFMScreen);
// lv_img_set_src(ui_CrazyFMCoverImage, &ui_img_crazyfm_cover_png);
lv_obj_set_width( ui_CrazyFMCoverImage, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CrazyFMCoverImage, LV_SIZE_CONTENT);   /// 1
lv_obj_set_align( ui_CrazyFMCoverImage, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_CrazyFMCoverImage, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_CrazyFMCoverImage, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

ui_CrazyFMTitleLabel = lv_label_create(ui_CrazyFMScreen);
lv_obj_set_width( ui_CrazyFMTitleLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CrazyFMTitleLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CrazyFMTitleLabel, 0 );
lv_obj_set_y( ui_CrazyFMTitleLabel, -10 );
lv_obj_set_align( ui_CrazyFMTitleLabel, LV_ALIGN_BOTTOM_MID );
lv_label_set_text(ui_CrazyFMTitleLabel,"CrazyFM");
lv_obj_set_style_text_font(ui_CrazyFMTitleLabel, &ui_font_SourceHanCrazyCube26, LV_PART_MAIN| LV_STATE_DEFAULT);

ui_CrazyFMStateLabel = lv_label_create(ui_CrazyFMScreen);
lv_obj_set_width( ui_CrazyFMStateLabel, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_CrazyFMStateLabel, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_CrazyFMStateLabel, 2 );
lv_obj_set_y( ui_CrazyFMStateLabel, 23 );
lv_label_set_text(ui_CrazyFMStateLabel,"连接失败，请重试");
lv_obj_set_style_text_font(ui_CrazyFMStateLabel, &ui_font_SourceHanCrazyCube22, LV_PART_MAIN| LV_STATE_DEFAULT);

}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_CrazyFMScreen_screen_init();
// lv_disp_load_scr( ui_CrazyFMScreen);
// }
