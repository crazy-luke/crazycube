/**
 * @file kc_keyboard.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief  Keyboard data persistence
 * @version 1.0
 * @date 2022-08-27
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "kc_.h"

struct KeyboardInfo {
  String name;
  String up;
  String down;
  String left;
  String right;
  String clockwise;
  String anticlockwise;
};

class KeyboardKeyChain {
 public:
  void Save(KeyboardInfo info) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    pref.putString("kb_name", info.name);
    pref.putString("kb_up", info.up);
    pref.putString("kb_down", info.down);
    pref.putString("kb_left", info.left);
    pref.putString("kb_right", info.right);
    pref.putString("kb_cw", info.clockwise);
    pref.putString("kb_anticw", info.anticlockwise);
    pref.end();
  };

  KeyboardInfo Read() {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    KeyboardInfo info = {
        .name = pref.getString("kb_name", "立方豆键盘"),
        .up = pref.getString("kb_up", "KEY_NONE#_#KEY_UP_ARROW#_#KEY_NONE"),
        .down = pref.getString("kb_down", "KEY_NONE#_#KEY_DOWN_ARROW#_#KEY_NONE"),
        .left = pref.getString("kb_left", "KEY_NONE#_#KEY_LEFT_ARROW#_#KEY_NONE"),
        .right = pref.getString("kb_right", "KEY_NONE#_#KEY_RIGHT_ARROW#_#KEY_NONE"),
        .clockwise = pref.getString("kb_cw", "KEY_NONE#_#KEY_RETURN#_#KEY_NONE"),
        .anticlockwise = pref.getString("kb_anticw", "KEY_NONE#_#KEY_ESC#_#KEY_NONE"),
    };
    pref.end();
    return info;
  };
};