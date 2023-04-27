/**
 * @file group_app.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Group
 * @version 1.0
 * @date 2022-09-14
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "../app_contract.h"

class GroupAPP: public APP {

 private:
   const char* kTag = "GroupAPP";
   String group_id_;

 public:
  GroupAPP(String group_id): group_id_(group_id){}
  void OnExitApp() override;
  void OnLaunch() override;
};
