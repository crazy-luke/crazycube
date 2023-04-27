/**
 * @file keyboard.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 键盘
 * @version 0.1
 * @date 2023-01-18
 * 
 * @copyright Copyright (c) 2023
 * 
 */
#include <BleKeyboard.h>
#include <map>

#include "gesture_senor.h"

struct CubeCMDKey {
  const uint8_t* key_media = nullptr;
  uint8_t key_int = 0;
};

struct CubeKeyboardCMD{
  CubeCMDKey cmd1;
  CubeCMDKey cmd2;
  CubeCMDKey cmd3;
};

class Keyboard
{
private:
  const char* kTag = "Keyboard";
  BleKeyboard bleKeyboard_ = BleKeyboard("Cube-Keyboard","立方豆",100);
  std::map<GestureAction, CubeKeyboardCMD>  keymap_;

private:
  CubeKeyboardCMD ParseFromRaw(String raw);
  CubeCMDKey ParseIntent(String cmd);
  void SendKey(CubeKeyboardCMD cmd);
public:
    Keyboard();
    ~Keyboard();

public:
  bool isConnected();
  void Begin();
  void End();
  void OnAction(GestureAction action);
  void ReloadKeyMap();
};

