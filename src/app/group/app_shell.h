#pragma once
#include "../app_contract.h"
#include "group_app.h"

LV_IMG_DECLARE(app_group);

class GroupShell : public AppShell {

  private:
    String group_id_;
    char * group_name_;

 public: 
  GroupShell(String group_id, char* group_name): group_id_(group_id), group_name_(group_name){}

 public:
  APP* CreateApp() { return new GroupAPP(group_id_); }
  const String app_id() { return "_group_" + group_id_; }
  const char* app_name() { return group_name_; }
  const void* app_img() { return &app_group; }

};
