/**
 * @file token_store.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Restore AI_Server token
 * @version 1.0
 * @date 2022-09-22
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <WString.h>

#include "framework/context/network_context.h"

class TokenStore: public NetworkContext<TokenStore> {
//  private:
//   TokenStore(void) {}

//  public:
//   static TokenStore& instance() {
//     static TokenStore instance_;
//     return instance_;
//   }

 private:
  const char* kTag = "TokenStore";
  String baidu_token_ = "";
  
  const unsigned long kTokenExpiresTime = 28* 24 * 3600 * 1000; //设置28天有效期
  unsigned long last_reflash_time_=0; //上次成功获取 token millis();

 public:
  String baidu_token();
  String GetBaiduToken(bool auto_reflash = true);
  bool ReflashBaiduToken();

  //返回true 过期
  bool CheckExpired();  
};
