/**
 * @file ring_buffer.h
 * @author 疯狂豆 crazyluke193@gmail.com
 * @brief RingAudioBuffer, not good at  C style
 * @version 1.0
 * @date 2022-08-21
 *
 * @copyright Copyright (c) 2022
 *
 */

#pragma once
#include <string.h>
#include <esp32-hal-psram.h>

#include "../sys.h"
#include "tools/crazy_log.h"

class RingAudioBuffer {
 public:
  int16_t *samples_ = NULL;

 public:
  RingAudioBuffer() {
#if CRAZY_LOG_YELL
   CrazyLog::d("RingAudioBuffer", "RingAudioBuffer");
#endif
    samples_ = (int16_t *)ps_calloc(SAMPLE_PSRAM_BUF, sizeof(int16_t));
  }

  ~RingAudioBuffer() {
    CrazyLog::d("RingAudioBuffer", "~release");
    if (samples_) {
      free(samples_);
    }
  }
};

class RingBufferAccessor {
 private:
  RingAudioBuffer **audio_buffers_;
  int number_audio_buffers_;
  RingAudioBuffer *current_buffer_;
  int buffer_pos_; //current buffer position
  int buffer_idx_; //current buffer index  -> audio_buffers_[buffer_idx_]
  int total_size_;

 public:
  RingBufferAccessor(RingAudioBuffer **audioBuffers, int number_audio_buffers) {
    buffer_pos_ = 0;
    buffer_idx_ = 0;
    total_size_ = number_audio_buffers * SAMPLE_PSRAM_BUF;
    audio_buffers_ = audioBuffers;
    number_audio_buffers_ = number_audio_buffers;
    current_buffer_ = audioBuffers[0];
  }
  int GetIndex() { return buffer_idx_ * SAMPLE_PSRAM_BUF + buffer_pos_; }
  void SetIndex(int index) {
    // handle negative indexes
    index = (index + total_size_) % total_size_;
    // work out which buffer
    buffer_idx_ = (index / SAMPLE_PSRAM_BUF) % number_audio_buffers_;
    // and where we are in the buffer
    buffer_pos_ = index % SAMPLE_PSRAM_BUF;
    current_buffer_ = audio_buffers_[buffer_idx_];
  }
  inline int16_t GetCurrentSample() {
    return current_buffer_->samples_[buffer_pos_];
  }
  inline void SetCurrentSample(int16_t sample) {
    current_buffer_->samples_[buffer_pos_] = sample;
  }
  inline void Rewind(int samples) { SetIndex(GetIndex() - samples); }
  inline bool MoveToNextSample() {
    buffer_pos_++;
    if (buffer_pos_ == SAMPLE_PSRAM_BUF) {
      buffer_pos_ = 0;
      buffer_idx_++;
      if (buffer_idx_ == number_audio_buffers_) {
        buffer_idx_ = 0;
      }
      current_buffer_ = audio_buffers_[buffer_idx_];
      return true;
    }
    return false;
  }
};
