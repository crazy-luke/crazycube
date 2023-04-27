/**
 * @file kc_group.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Save Group App
 * @version 1.0
 * @date 2022-08-17
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "kc_.h"

#define GROUP_APP_G1  "g1"

#define GROUP_APP_G1_DEFAULT_APPS "_manual#_#"

class GroupKeyChain {
 public:
  
  void Save(String group_id, std::vector<String> app_ids) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    String key =  "group_"+group_id;

    String value ="";
    //value format: app_id_1#_#app_id_2#_#...
    for(auto id: app_ids)
      value += id+"#_#";
    pref.putString(key.c_str(), value);
    pref.end();
  };


  String Read(String group_id) {
    Preferences pref;
    pref.begin(KC_NAMESPACE_OS);
    String key =  "group_"+group_id;
    String default_value =  "";
    if(group_id.compareTo(GROUP_APP_G1) ==0)
       default_value = GROUP_APP_G1_DEFAULT_APPS;
    String group_appid = pref.getString(key.c_str(), default_value);
    pref.end();
    return group_appid;
  };
};