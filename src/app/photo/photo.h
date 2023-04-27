/**
 * @file photo.h
 * @author crazyluke
 * @brief
 * @version 0.2
 * @date 2023-04-09
 *
 * @copyright Copyright (c) 2023
 *
 */
#pragma once

#include <Arduino.h>

#include <mutex>

#include "../app_contract.h"
#include "lv/lv_helper.h"
#include "tools/crazy_log.h"
#include "tools/file_manager.h"

#define PHOTO_PERIOD_NORMAL 6* 10 * 1000
class Photo : public APP {
 private:
  const char* kTag = "Photo";
  friend void PhotoTask(void* param);
  TaskHandle_t task_handle_ = NULL;
  void PhotoTaskWithLock();
  std::mutex lock_task_;
  std::vector<FileInfo> file_list_;
  uint8_t InitPhotoFiles();
  void ShowPhoto(int idx);
  int photo_idx_ = 0;

 public:
  void OnLaunch() override;
  void OnExitApp() override;
  void OnAction(AppAction action) override;
};