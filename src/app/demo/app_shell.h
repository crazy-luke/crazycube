#include "../app_contract.h"
#include "demo_app.h"

LV_IMG_DECLARE(crazy_cube);

class DemoAppShell : public AppShell {
 private:
  const lv_img_dsc_t* img_;
  const char* name_;

 public:
  DemoAppShell() : DemoAppShell(&crazy_cube, "DemoAPP") {}

  DemoAppShell(const lv_img_dsc_t* img, const char* name) {
    img_ = img;
    name_ = name;
  }

  APP* CreateApp() { return new DemoApp(); }
  const char* app_name() { return name_; }
  const void* app_img() { return img_; }
  const String app_id() { return "_demo"; }
};
