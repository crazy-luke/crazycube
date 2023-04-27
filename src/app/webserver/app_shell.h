#include "../app_contract.h"
#include "web_server.h"

LV_IMG_DECLARE(app_web);

class WebServerShell : public AppShell {
 public:
  APP* CreateApp() { return new WebServer(); }
  const char* app_name() { return "系统设置 Web"; }
  const void* app_img() { return &app_web; }
  const String app_id() { return "_webserver"; }

 public:
  const bool asst_supress() { return true; }
};