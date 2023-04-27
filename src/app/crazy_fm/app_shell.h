#include "../app_contract.h"
#include "crazy_fm.h"

LV_IMG_DECLARE(app_crazyfm);

class CrazyFMShell : public AppShell {
 public:
  APP* CreateApp() { return new CrazyFM(); }
  const String app_id() { return "_crazy_fm"; }
  const char* app_name() { return "播客"; }
  const void* app_img() { return &app_crazyfm; }

  const String app_manul() {
    String content = "";
    content += "顺时针：停止或播放\n";
    content += "左右：切换频道\n";
    content += ">> 状态栏调节音量";
    return content;
  }
};