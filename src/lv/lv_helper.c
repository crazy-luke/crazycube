#include "lv_helper.h"
#include "ui_helpers.h"

void lv_anim_move(lv_obj_t *ui_obj, lv_obj_t *ui_obj_disp, AnimMoveDirection direction, uint32_t duration)
{
  lv_anim_t anim;
  lv_anim_init(&anim);
  lv_anim_set_var(&anim, ui_obj);
  lv_anim_set_time(&anim, duration);
  lv_anim_set_delay(&anim, 0);
  lv_disp_t *d = lv_obj_get_disp(ui_obj_disp);

  switch (direction) {
    case LEFT_TO_RIGNT: {
      lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_x);
      lv_anim_set_values(&anim, lv_disp_get_hor_res(d), 0);
    } break;
    case RIGHT_TO_LEFT: {
      lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_x);
      lv_anim_set_values(&anim, -lv_disp_get_hor_res(d), 0);
    } break;
    case TOP_TO_BUTTOM: {
      lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
      lv_anim_set_values(&anim, -lv_disp_get_ver_res(d), 0);
    }
    case BOTTOM_TO_TOP: {
      lv_anim_set_exec_cb(&anim, (lv_anim_exec_xcb_t)lv_obj_set_y);
      lv_anim_set_values(&anim, lv_disp_get_ver_res(d), 0);
    }
  }

  lv_anim_start(&anim);
  lv_task_handler(); 
}

void lv_anim_move_in_out(lv_obj_t *ui_obj_in, lv_obj_t *ui_obj_out,
                         lv_obj_t *ui_obj_disp, AnimMoveDirection direction,
                         bool mirror, uint32_t duratiom) {
  if (mirror) {
    if (direction == LEFT_TO_RIGNT)
      direction = RIGHT_TO_LEFT;
    else if (direction == RIGHT_TO_LEFT)
      direction = LEFT_TO_RIGNT;
    else if (direction == BOTTOM_TO_TOP)
      direction = TOP_TO_BUTTOM;
    else if (direction == TOP_TO_BUTTOM)
      direction = BOTTOM_TO_TOP;
  }

  lv_anim_t a_in;
  lv_anim_init(&a_in);
  lv_anim_set_var(&a_in, ui_obj_in);
  lv_anim_set_time(&a_in, duratiom);
  lv_anim_set_delay(&a_in, 0);

  lv_anim_t a_out;
  lv_anim_init(&a_out);
  lv_anim_set_var(&a_out, ui_obj_out);
  lv_anim_set_time(&a_out, duratiom);
  lv_anim_set_delay(&a_out, 0);

  lv_disp_t *d = lv_obj_get_disp(ui_obj_disp);

  switch (direction) {
    case LEFT_TO_RIGNT: {
      lv_anim_set_exec_cb(&a_in, (lv_anim_exec_xcb_t)lv_obj_set_x);
      lv_anim_set_values(&a_in, lv_disp_get_hor_res(d), 0);

      lv_anim_set_exec_cb(&a_out, (lv_anim_exec_xcb_t)lv_obj_set_x);
      lv_anim_set_values(&a_out, 0, -lv_disp_get_hor_res(d));
    } break;
    case RIGHT_TO_LEFT: {
      lv_anim_set_exec_cb(&a_in, (lv_anim_exec_xcb_t)lv_obj_set_x);
      lv_anim_set_values(&a_in, -lv_disp_get_hor_res(d), 0);

      lv_anim_set_exec_cb(&a_out, (lv_anim_exec_xcb_t)lv_obj_set_x);
      lv_anim_set_values(&a_out, 0, lv_disp_get_hor_res(d));
    } break;
    case BOTTOM_TO_TOP: {
    }

    case TOP_TO_BUTTOM: {
    }
  }

  // lv_anim_set_path_cb(&a_in, lv_anim_path_linear);
  // lv_anim_set_path_cb(&a_out, lv_anim_path_linear);
  lv_anim_start(&a_in);
  lv_anim_start(&a_out);
}

lv_obj_t* create_empty_screen(){
  lv_obj_t* screen_obj = lv_obj_create(NULL);
  lv_obj_clear_flag(screen_obj, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
  lv_obj_set_style_bg_color(screen_obj, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
  lv_obj_set_style_bg_opa(screen_obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
  return screen_obj;
}

void move_animation(lv_obj_t *TargetObject, int32_t start, int32_t end, uint32_t duration, uint32_t delay) {
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, duration);
  lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_x);
  lv_anim_set_values(&PropertyAnimation_0, start, end);
  lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
  lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
  lv_anim_set_playback_time(&PropertyAnimation_0, 0);
  lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
  lv_anim_set_early_apply(&PropertyAnimation_0, false);
  lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_x);
  lv_anim_start(&PropertyAnimation_0);
}


void fade_animation(lv_obj_t *TargetObject, int32_t start, int32_t end, uint32_t duration, uint32_t delay, AnimPath path) {
  lv_anim_t PropertyAnimation_0;
  lv_anim_init(&PropertyAnimation_0);
  lv_anim_set_time(&PropertyAnimation_0, duration);
  lv_anim_set_user_data(&PropertyAnimation_0, TargetObject);
  lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_opacity);
  lv_anim_set_values(&PropertyAnimation_0, start, end);
  if(path == ANIM_PATH_LINER)
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_linear);
  else if(path == ANIM_PATH_EASE_IN)
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_in);
  else if(path == ANIM_PATH_EASE_OUT)
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_ease_out);
  else if(path == ANIM_PATH_BOUNCE)
    lv_anim_set_path_cb(&PropertyAnimation_0, lv_anim_path_bounce);


  lv_anim_set_delay(&PropertyAnimation_0, delay + 0);
  lv_anim_set_playback_time(&PropertyAnimation_0, 0);
  lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
  lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
  lv_anim_set_early_apply(&PropertyAnimation_0, false);
  lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_opacity);
  lv_anim_start(&PropertyAnimation_0);
}


void zoom_animation( lv_obj_t *TargetObject, int32_t start, int32_t end, uint32_t duration, uint32_t delay) {
    lv_anim_t PropertyAnimation_0;
    lv_anim_init(&PropertyAnimation_0);
    lv_anim_set_time(&PropertyAnimation_0, delay);
    lv_anim_set_user_data(&PropertyAnimation_0,TargetObject);
    lv_anim_set_custom_exec_cb(&PropertyAnimation_0, _ui_anim_callback_set_image_zoom );
    lv_anim_set_values(&PropertyAnimation_0, start, end );
    lv_anim_set_path_cb( &PropertyAnimation_0, lv_anim_path_linear);
    lv_anim_set_delay( &PropertyAnimation_0, delay + 0 );
    lv_anim_set_playback_time(&PropertyAnimation_0, 0);
    lv_anim_set_playback_delay(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_count(&PropertyAnimation_0, 0);
    lv_anim_set_repeat_delay(&PropertyAnimation_0, 0);
    lv_anim_set_early_apply( &PropertyAnimation_0, false );
    lv_anim_set_get_value_cb(&PropertyAnimation_0, &_ui_anim_callback_get_image_zoom );
    lv_anim_start(&PropertyAnimation_0);
}