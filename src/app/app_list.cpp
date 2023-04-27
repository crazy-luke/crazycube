#include "app_list.h"

#include "./assistant/app_shell.h"
#include "./crazy_fm/app_shell.h"
#include "./group/app_shell.h"
#include "./manual/app_shell.h"
#include "./relax/app_shell.h"
#include "./webserver/app_shell.h"
#include "keychain/kc_group.h"
#include"./photo/app_shell.h"

std::vector<AppShell*> AppList::AllAPP() {
  return {
      new AssistantShell(), 
      new CrazyFMShell(),
      new WebServerShell(), 
      new CubeManualShell(),
      new RelaxAppShell(),
      new PhotoAppShell(),
  };
};

std::vector<AppShell*> AppList::RootAPP(bool include_group_shell) {
  auto apps = AllAPP();
  auto group_app = GroupKeyChain().Read(GROUP_APP_G1);
  if (group_app.isEmpty()) {
    // add empty Group
    if(include_group_shell) apps.push_back(new GroupShell("", "APP收纳盒"));
  } else {
    for (auto& app : apps) {
      // remove app which is in group_app
      if (group_app.indexOf(app->app_id()) >= 0) {
        delete app;
        app = nullptr;
      }
    }
    // add Group g1
    if(include_group_shell)  apps.push_back(new GroupShell(GROUP_APP_G1, "APP收纳盒"));
  }

  apps.erase(std::remove(apps.begin(), apps.end(), nullptr), apps.end());

  return apps;
}

std::vector<AppShell*> AppList::GroupAPP(String group_appid) {
  std::vector<AppShell*> apps;
  if (!group_appid.isEmpty()) {
    apps = AllAPP();
    auto group_app = GroupKeyChain().Read(group_appid);
    for (auto& app : apps) {
      // remove app which is not in group_app
      if (group_app.indexOf(app->app_id()) < 0) {
        delete app;
        app = nullptr;
      }
    }
    apps.erase(std::remove(apps.begin(), apps.end(), nullptr), apps.end());
  }

  return apps;
}

void AppList::Clean(std::vector<AppShell*> &apps){
    for(auto& pointer : apps) {
          delete pointer;
          pointer = nullptr;
    }
    apps.erase(std::remove(apps.begin(), apps.end(), nullptr), apps.end());
}