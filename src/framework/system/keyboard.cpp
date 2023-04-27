#include "keyboard.h"

#include <NimBLEDevice.h>

#include "tools/crazy_log.h"
#include "keychain/kc_keyboard.h"

const uint8_t KEY_SPACE = 0x20;

Keyboard::Keyboard() { 
  ReloadKeyMap(); 
}

Keyboard::~Keyboard() { End(); }

void Keyboard::OnAction(GestureAction action) {
  if (!bleKeyboard_.isConnected()) {
    CrazyLog::w(kTag, "keyboard is not connected!");
    return;
  }
  if(keymap_.count(action)>0){
    SendKey(keymap_[action]);
  }else{
    CrazyLog::w(kTag, "No action key");
  }
}

void Keyboard::Begin() {
  CrazyLog::d(kTag, "Begin");
  bleKeyboard_.begin();
  bleKeyboard_.releaseAll();
}

void Keyboard::End() {
  bleKeyboard_.end();
  NimBLEDevice::deinit(true);
  CrazyLog::d(kTag, "End");
}

bool Keyboard::isConnected() { return bleKeyboard_.isConnected(); }

void Keyboard::ReloadKeyMap() {
  CrazyLog::d(kTag, "ReloadKeyMap");
  auto info = KeyboardKeyChain().Read();
  bleKeyboard_.setName(info.name.c_str());
  keymap_.clear();
  keymap_[GestureAction::UP] = ParseFromRaw(info.up);
  keymap_[GestureAction::DOWN] = ParseFromRaw(info.down);
  keymap_[GestureAction::LEFT] = ParseFromRaw(info.left);
  keymap_[GestureAction::RIGHT] = ParseFromRaw(info.right);
  keymap_[GestureAction::CLOCKWISE] = ParseFromRaw(info.clockwise);
  keymap_[GestureAction::ANTICLOCKWISE] = ParseFromRaw(info.anticlockwise);
}

CubeCMDKey Keyboard::ParseIntent(String cmd){
  CrazyLog::d(kTag, "ParseIntent: %s",cmd.c_str());
  CubeCMDKey cKey;
  if (cmd == "KEY_MEDIA_VOLUME_UP") {
    cKey.key_media = KEY_MEDIA_VOLUME_UP;
  } else if (cmd == "KEY_MEDIA_VOLUME_DOWN") {
    cKey.key_media = KEY_MEDIA_VOLUME_DOWN;
  } else if (cmd == "KEY_MEDIA_MUTE") {
    cKey.key_media = KEY_MEDIA_MUTE;
  } else if (cmd == "KEY_MEDIA_PLAY_PAUSE") {
    cKey.key_media = KEY_MEDIA_PLAY_PAUSE;
  } else if (cmd == "KEY_MEDIA_NEXT_TRACK") {
    cKey.key_media = KEY_MEDIA_NEXT_TRACK;
  } else if (cmd == "KEY_MEDIA_PREVIOUS_TRACK") {
    cKey.key_media = KEY_MEDIA_PREVIOUS_TRACK;
  } else if (cmd == "KEY_UP_ARROW") {
    cKey.key_int = KEY_UP_ARROW;
  } else if (cmd == "KEY_DOWN_ARROW") {
    cKey.key_int = KEY_DOWN_ARROW;
  } else if (cmd == "KEY_LEFT_ARROW") {
    cKey.key_int = KEY_LEFT_ARROW;
  } else if (cmd == "KEY_RIGHT_ARROW") {
    cKey.key_int = KEY_RIGHT_ARROW;
  } else if (cmd == "KEY_PAGE_UP") {
    cKey.key_int = KEY_PAGE_UP;
  } else if (cmd == "KEY_PAGE_DOWN") {
    cKey.key_int = KEY_PAGE_DOWN;
  } else if (cmd == "KEY_HOME") {
    cKey.key_int = KEY_HOME;
  } else if (cmd == "KEY_RETURN") {
    cKey.key_int = KEY_RETURN;
  } else if (cmd == "KEY_ESC") {
    cKey.key_int = KEY_ESC;
  }else if (cmd == "KEY_SPACE") {
    cKey.key_int = KEY_SPACE;
  } else if (cmd == "KEY_F1") {
    cKey.key_int = KEY_F1;
  } else if (cmd == "KEY_F2") {
    cKey.key_int = KEY_F2;
  } else if (cmd == "KEY_F3") {
    cKey.key_int = KEY_F3;
  } else if (cmd == "KEY_F4") {
    cKey.key_int = KEY_F4;
  } else if (cmd == "KEY_F5") {
    cKey.key_int = KEY_F5;
  } else if (cmd == "KEY_F6") {
    cKey.key_int = KEY_F6;
  } else if (cmd == "KEY_F7") {
    cKey.key_int = KEY_F7;
  } else if (cmd == "KEY_F8") {
   cKey.key_int = KEY_F8;
  } else if (cmd == "KEY_F9") {
    cKey.key_int = KEY_F9;
  } else if (cmd == "KEY_F10") {
   cKey.key_int = KEY_F10;
  } else if (cmd == "KEY_F11") {
    cKey.key_int = KEY_F11;
  } else if (cmd == "KEY_F12") {
    cKey.key_int = KEY_F12;
  } else if (cmd == "KEY_LEFT_CTRL") {
    cKey.key_int = KEY_LEFT_CTRL;
  } else if (cmd == "KEY_LEFT_SHIFT") {
    cKey.key_int = KEY_LEFT_SHIFT;
  } else if (cmd == "KEY_LEFT_ALT") {
    cKey.key_int = KEY_LEFT_ALT;
  } else if (cmd == "KEY_LEFT_GUI") {
    cKey.key_int = KEY_LEFT_GUI;
  } else if(cmd.length()==1){
    cKey.key_int = (uint8_t)cmd.c_str()[0];
#if CRAZY_LOG_YELL
    CrazyLog::d(kTag, "cKey c_str:%s, key_int:%d",cmd.c_str(),cKey.key_int);
#endif
  }
  return cKey;
}
/**
 * @brief 
 * 
 * @param raw  : 格式 cmd#_#str
 * @return CubeKeyboardSet 
 */
CubeKeyboardCMD Keyboard::ParseFromRaw(String raw) {
  CrazyLog::d(kTag, "ParseFromRaw: %s",raw.c_str());
  String cmd = "";
  String cmd2 = "";
  String cmd3 = "";

  int idx = raw.indexOf("#_#");
  int idx2 = raw.indexOf("#_#",idx+3);
  cmd = raw.substring(0,idx);
  if(idx2<0){
    cmd2 = raw.substring(idx, raw.length());
  }else{
    cmd2 = raw.substring(idx+3, idx2);
    cmd3 = raw.substring(idx2+3, raw.length());
  }

  CrazyLog::d(kTag, "ParseFromRaw cmd1:%s, cmd2:%s, cmd3:%s",cmd,cmd2,cmd3);
  return CubeKeyboardCMD{ParseIntent(cmd), ParseIntent(cmd2), ParseIntent(cmd3)};
}

void Keyboard::SendKey(CubeKeyboardCMD cmd){

  CrazyLog::d(kTag, "SendKey");
  bool need_release = false;

  if(cmd.cmd1.key_media !=nullptr){
      bleKeyboard_.write(cmd.cmd1.key_media);
      CrazyLog::d(kTag, "cmd1.key_media");
  }else if(cmd.cmd1.key_int !=0){
      bleKeyboard_.press(cmd.cmd1.key_int);
      need_release = true;
      CrazyLog::d(kTag, "cmd1.key_int %d", cmd.cmd1.key_int);
  }

  if(cmd.cmd2.key_media !=nullptr){
      bleKeyboard_.write(cmd.cmd2.key_media);
      CrazyLog::d(kTag, "cmd2.key_media");
  }else if(cmd.cmd2.key_int !=0){
      bleKeyboard_.press(cmd.cmd2.key_int);
      need_release = true;
      CrazyLog::d(kTag, "cmd2.key_int %d",cmd.cmd2.key_int);
  }

   if(cmd.cmd3.key_media !=nullptr){
      bleKeyboard_.write(cmd.cmd3.key_media);
      CrazyLog::d(kTag, "cmd3.key_media");
  }else if(cmd.cmd3.key_int !=0){
      bleKeyboard_.press(cmd.cmd3.key_int);
      need_release = true;
      CrazyLog::d(kTag, "cmd3.key_int %d",cmd.cmd3.key_int);
  }

  if(need_release)
    bleKeyboard_.releaseAll();

}
