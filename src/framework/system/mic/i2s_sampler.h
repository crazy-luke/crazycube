/**
 * @file i2s_sampler.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief I2S Mic Sampler
 * @version 1.0
 * @date 2022-08-20
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#pragma once

#include <driver/i2s.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <algorithm>

#include "ring_buffer.h"
#include "../sys.h"

#define NOTIFY_ID_STATE_I2S_SAMPLER 1 
#define USE_HIGH_BITS_SAMPER 0    //1:32bit,  0: 16bit

/**
 * Base Class for both the ADC and I2S sampler
 **/
class I2SSampler {
 private:
  const char* kTag = "I2SSampler";

  TaskHandle_t task_handle_ = nullptr;
  TaskHandle_t processor_taskhandle_ = nullptr;  //需要通知的 processor task
  QueueHandle_t i2s_queue_;
  i2s_port_t i2s_port_;
  i2s_pin_config_t i2s_pins_;
  i2s_config_t i2s_config_;
  uint8_t sampler_shift_ = 0;   // 32位采样左位移
  uint8_t * i2s_data_temp_ = nullptr;      //Task 中临时采样数据

 private:
  void AddSample(int16_t sample);

 public:
  ~I2SSampler();
  I2SSampler(i2s_port_t i2s_port, i2s_pin_config_t &i2s_pins, i2s_config_t &i2s_config);
  void Start(TaskHandle_t processor_taskhandle);
  void Stop();
  void set_sampler_shift(uint8_t sampler_shift) { sampler_shift_ = sampler_shift;}

// ---------------- Samper Data ----------------
private:
  RingAudioBuffer* audio_buffers_[SAMPLE_BUFFER_COUNT];
  RingBufferAccessor* write_ring_buffer_accessor_;

public:
  RingBufferAccessor *GetRingBufferReader();
  int GetCurrentWritePosition() { return write_ring_buffer_accessor_->GetIndex(); }
  int GetRingBufferSize() { return SAMPLE_BUFFER_COUNT * SAMPLE_PSRAM_BUF; }

// ---------------- Friend ----------------
private:
  friend void I2SSamplerTask(void *param);
  friend class Mic;

};
