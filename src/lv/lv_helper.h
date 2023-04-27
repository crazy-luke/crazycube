/**
 * @file lv_anim.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief lv anim helper
 * @version 1.0
 * @date 2022-09-08
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <lvgl.h>
// enum class AnimMoveDirection{
//   LEFT_TO_RIGNT,
//   RIGHT_TO_LEFT,
//   BOTTOM_TO_TOP,
//   TOP_TO_BUTTOM
// };


#ifdef __cplusplus
extern "C" {
#endif

typedef enum
{
  LEFT_TO_RIGNT,
  RIGHT_TO_LEFT,
  BOTTOM_TO_TOP,
  TOP_TO_BUTTOM
} AnimMoveDirection;

typedef enum{
  ANIM_PATH_LINER,
  ANIM_PATH_EASE_IN,
  ANIM_PATH_EASE_OUT,
  ANIM_PATH_BOUNCE
} AnimPath;

void lv_anim_move(lv_obj_t *ui_obj, lv_obj_t *ui_obj_disp, AnimMoveDirection direction, uint32_t duration);
void lv_anim_move_in_out(lv_obj_t *ui_obj_in, lv_obj_t *ui_obj_out, lv_obj_t *ui_obj_disp, 
                    AnimMoveDirection direction, bool mirror, uint32_t duratiom);
lv_obj_t *create_empty_screen();

void move_animation(lv_obj_t *TargetObject, int32_t start, int32_t end, uint32_t duration, uint32_t delay);
void fade_animation(lv_obj_t *TargetObject, int32_t start, int32_t end, uint32_t duration, uint32_t delay, AnimPath path);
void zoom_animation( lv_obj_t *TargetObject, int32_t start, int32_t end, uint32_t duration, uint32_t delay);

#ifdef __cplusplus
} /*extern "C"*/
#endif