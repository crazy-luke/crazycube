#pragma once
#include <freertos/semphr.h>

class MutexSemaphore {
  private:  
    SemaphoreHandle_t semaphore_;
 public:
  MutexSemaphore() { semaphore_ = xSemaphoreCreateMutex(); }
 public:
  void Lock() { xSemaphoreTake(semaphore_, portMAX_DELAY); }
  void Unlock() { xSemaphoreGive(semaphore_); }
};

class MutexUI: public MutexSemaphore {
 public:
    MutexUI(MutexUI const &) = delete;
    MutexUI &operator=(MutexUI const &) = delete;
    static MutexUI &instance() {
      static MutexUI instance_;
      return instance_;
    }
  private:
    MutexUI():MutexSemaphore(){}
};