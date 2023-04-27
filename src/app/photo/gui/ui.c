// SquareLine LVGL GENERATED FILE
// EDITOR VERSION: SquareLine Studio 1.2.1
// LVGL VERSION: 8.3.4
// PROJECT: CrazyCube_Photo

#include "ui.h"
#include "lv/ui_helpers.h"
///////////////////// VARIABLES ////////////////////
lv_obj_t *ui_PhotoScreen;
lv_obj_t *ui_PhotoImge;

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
void ui_PhotoScreen_screen_init(void)
{
ui_PhotoScreen = lv_obj_create(NULL);
lv_obj_clear_flag( ui_PhotoScreen, LV_OBJ_FLAG_SCROLLABLE );    /// Flags
lv_obj_set_style_bg_color(ui_PhotoScreen, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT );

ui_PhotoImge = lv_img_create(ui_PhotoScreen);
lv_obj_set_width( ui_PhotoImge, LV_SIZE_CONTENT);  /// 1
lv_obj_set_height( ui_PhotoImge, LV_SIZE_CONTENT);   /// 1
lv_obj_set_x( ui_PhotoImge, 0 );
lv_obj_set_y( ui_PhotoImge, 0 );
lv_obj_set_align( ui_PhotoImge, LV_ALIGN_CENTER );
lv_obj_add_flag( ui_PhotoImge, LV_OBJ_FLAG_ADV_HITTEST );   /// Flags
lv_obj_clear_flag( ui_PhotoImge, LV_OBJ_FLAG_SCROLLABLE );    /// Flags

}

// void ui_init( void )
// {
// lv_disp_t *dispp = lv_disp_get_default();
// lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
// lv_disp_set_theme(dispp, theme);
// ui_PhotoScreen_screen_init();
// lv_disp_load_scr( ui_PhotoScreen);
// }
