
/**
 * @file gui.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 适配 SquareLine_Studio 工程 CrazyCube_CrazyAsst, Export UI Files 修改如下
 *  1. ui.h 
 *      注释或删除函数 ui_init
 *      增加函数声明 ui_CrazyAsstScreen_screen_init  
 *  2. ui.c
 *      注释或删除函数 ui_init
 * @version 1.0
 * @date 2022-09-14
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#pragma once
#include "ui.h"

// 适配初始化 ui_init
lv_obj_t * ui_init_crazy_asst(void){
    ui_CrazyAsstScreen_screen_init();
    return ui_CrazyAsstScreen;
}

void ui_update_content_crazy_asst(const char* title, const char* desc) {
    lv_label_set_text(ui_CrazyAsstTitleLabel,title);
    lv_label_set_text(ui_CrazyAsstContentLabel,desc);
}

void ui_update_hint_crazy_asst(const char* hint) {
    lv_label_set_text(ui_CrazyAsstHintLabel,hint);
}

