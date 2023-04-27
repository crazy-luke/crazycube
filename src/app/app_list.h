/**
 * @file app_list.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief Assemble All App
 * @version 1.0
 * @date 2022-09-23
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include <vector>

#include "app_contract.h"

class AppList {
 public:
  std::vector<AppShell*> AllAPP();
  std::vector<AppShell*> RootAPP(bool include_group_shell);
  std::vector<AppShell*> GroupAPP(String group_id);

  //remove apps in vector
  void Clean(std::vector<AppShell*> &apps);
};
