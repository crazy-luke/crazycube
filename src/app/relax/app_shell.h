#include "../app_contract.h"
#include "relax.h"

LV_IMG_DECLARE(app_relax);

class RelaxAppShell : public AppShell {
 public:
  APP* CreateApp() { return new Relax(); }
  const String app_id() { return "_relax"; }
  const char* app_name() { return "轻松一刻"; }
  const void* app_img() { return &app_relax; }

  const String app_manul() {
    String content = "";
    content += "左右切换游戏\n";
    content += "顺时针进入\n";
    return content;
  }
};
