#include "../app_contract.h"
#include "photo.h"

LV_IMG_DECLARE(app_photos);

class PhotoAppShell : public AppShell {
 private:
 public:
  APP* CreateApp() { return new Photo(); }
  const char* app_name() { return "相册"; }
  const void* app_img() { return &app_photos; }
  const String app_id() { return "photo"; }
};
