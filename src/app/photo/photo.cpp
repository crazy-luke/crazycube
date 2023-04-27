#include "photo.h"

#include "./gui/gui.h"
void PhotoTask(void* param) {
  delay(400);  // Waiting for ui update
  Photo* app = static_cast<Photo*>(param);
  app->PhotoTaskWithLock();
  app->task_handle_ = NULL;
  vTaskDelete(NULL);
}
void Photo::OnLaunch() {
  CrazyLog::d(kTag, "onLaunch");

  lv_obj_t* ui_screen = ui_init_Photo();
  lv_scr_load_anim(ui_screen, LV_SCR_LOAD_ANIM_MOVE_BOTTOM, 300, 0, false);

  xTaskCreatePinnedToCore(PhotoTask, "PhotoTask", 1024 * 4, this,
                          TASK_PRIORITY_APP, &task_handle_, CORE_0);
}
void Photo::OnExitApp() {
  CrazyLog::d(kTag, "onExitApp");
  if (task_handle_) {
    xTaskNotify(task_handle_, NOTIFY_ID_EXIT_TASK, eSetBits);
    CrazyLog::d(kTag, "Waiting For task exit");
    { std::lock_guard<std::mutex> l(lock_task_); }
    CrazyLog::d(kTag, "Task has exit");
  }
  lv_scr_load_anim(context()->home_screen(), LV_SCR_LOAD_ANIM_MOVE_TOP, 300, 0,
                   true);
}
uint8_t Photo::InitPhotoFiles() {
  FileManager fm;
  file_list_ = fm.GetFileList(FILEPATH_ROOT_PHOTO, "jpg");
  fm.SortFiles(file_list_);
  return file_list_.size();
}
void Photo::OnAction(AppAction action) {
  if (action == AppAction::LEFT)
    ShowPhoto(photo_idx_ - 1);
  else if (action == AppAction::RIGHT)
    ShowPhoto(photo_idx_ + 1);
}

void Photo::ShowPhoto(int idx) {
  int max_size = file_list_.size();
  if (max_size == 0) {
    CrazyLog::e(kTag, "No Photo!");
    return;
  }
  if (idx < 0) idx = max_size - 1;
  if (idx >= max_size) idx = 0;
  CrazyLog::d(kTag, "file:%d path:%s", idx, file_list_[idx].path.c_str());
  ui_set_Photo(file_list_[idx].path);
  photo_idx_ = idx;
}
void Photo::PhotoTaskWithLock() {
  CrazyLog::d(kTag, "PhotoTaskWithLock");
  std::lock_guard<std::mutex> l(lock_task_);  // Lock Task before exit
  InitPhotoFiles();

  const TickType_t xNormalBlockTime = pdMS_TO_TICKS(PHOTO_PERIOD_NORMAL);

  ShowPhoto(0);
  while (true)
  {
    CrazyLog::d(kTag, "Waiting to switch");
    uint32_t ulNotificationValue = ulTaskNotifyTake(pdTRUE, xNormalBlockTime);
    if(NOTIFY_ID_EXIT_TASK == ulNotificationValue){
      CrazyLog::d(kTag, "Receive exit signal");
      return;
    }

    ShowPhoto(photo_idx_ + 1);
  }
  
}