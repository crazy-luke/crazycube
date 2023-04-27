/**
 * @file launchpad.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Launchpad is named from MacOS Launchpad
 * @version 1.0
 * @date 2022-08-16
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once
#include <lvgl.h>

#include "app/app_contract.h"
#define AUDIO_RES_SWITCH "/audio/switch.mp3"

class Launchpad {
 private:
  const char *kTag = "Launchpad";
  lv_obj_t *actived_panel_;

  bool is_sub_mode_ = false;

 private:
    void ShowBackHint(bool flag);

 public:
  void Init();
  // switch luanch pad
  void SwitchAPP(bool forward, const void *icon, const char *name);
  // set current active app icon and name
  void ReloadActiveAPP(const void *icon, const char *name);
  lv_obj_t *launchpad_screen();

  bool is_sub_mode() { return is_sub_mode_;}
  void SetSubMode(bool flag);
};