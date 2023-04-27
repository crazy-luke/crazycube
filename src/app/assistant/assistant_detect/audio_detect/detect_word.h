/**
 * @file detect_word.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief 语音信号本地唤醒词识别。 当前使用:Tensorflowlite
 * @version 1.0
 * @date 2022-09-19
 *
 * @copyright Copyright (c) 2022
 *
 */
#pragma once

#include "framework/system/mic/i2s_sampler.h"

#define DECTECT_THRESHOLD 0.82  // max 1.0
#define SHOWLOG_THRESHOLD 0.3

class I2SSampler;
class NeuralNetwork;
class AudioProcessor;
class RingBufferAccessor;

class DetectWord {
 private:
  const char *kTag = "DetectWord";
  I2SSampler *sample_provider_;
  NeuralNetwork *neural_network_;
  AudioProcessor *audio_processor_;
  float average_detect_time_;
  int number_of_runs_;
  unsigned char *model_;

  // crazyadam: make sure free memory, task may delete
  RingBufferAccessor *reader_temp_ = nullptr;  

 public:
  DetectWord(I2SSampler *sample_provider, unsigned char *model);
  ~DetectWord();
  
  void Enter();
  bool Run(String& msg);
  void Exit();
};
