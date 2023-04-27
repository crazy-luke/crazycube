
#include <stddef.h>
#include <esp32-hal-psram.h>

#include "i2s_sampler.h"
#include "../sys.h"
#include "tools/crazy_log.h"

I2SSampler::I2SSampler(i2s_port_t i2s_port, i2s_pin_config_t &i2s_pins,
                       i2s_config_t &i2s_config) {
  CrazyLog::d(kTag, "constructor!");            
  i2s_port_ = i2s_port;
  i2s_pins_ = i2s_pins;
  i2s_config_ = i2s_config;
  for (int i = 0; i < SAMPLE_BUFFER_COUNT; i++) {
    audio_buffers_[i] = new RingAudioBuffer();
  }
  write_ring_buffer_accessor_ =
      new RingBufferAccessor(audio_buffers_, SAMPLE_BUFFER_COUNT);
}

I2SSampler::~I2SSampler() {
  CrazyLog::d(kTag, "~release");
  Stop();
  for (int i = 0; i < SAMPLE_BUFFER_COUNT; i++) {
    delete (audio_buffers_[i]);
  }
  delete (write_ring_buffer_accessor_);
}

void I2SSampler::AddSample(int16_t sample) {
  write_ring_buffer_accessor_->SetCurrentSample(sample);
  if (write_ring_buffer_accessor_->MoveToNextSample()) {
    // trigger  processor task
    if(processor_taskhandle_)
      xTaskNotify(processor_taskhandle_, NOTIFY_ID_STATE_I2S_SAMPLER, eSetBits);
  }
}

void I2SSamplerTask(void *param) {
  I2SSampler *sampler = (I2SSampler *)param;
  CrazyLog::d(sampler->kTag, "Task start~");
  while (true) {
    // wait for some data to arrive on the queue   
#if CRAZY_LOG_YELL
    CrazyLog::v(sampler->kTag, "do~");
#endif
    i2s_event_t evt;
    uint8_t *i2s_data = (uint8_t *)ps_malloc(1024);
    sampler->i2s_data_temp_ = i2s_data;
    if (xQueueReceive(sampler->i2s_queue_, &evt, portMAX_DELAY) == pdPASS) {
      if (evt.type == I2S_EVENT_RX_DONE) {
        size_t bytes_read = 0;
        do {
#if CRAZY_LOG_YELL          
          CrazyLog::d("I2SSampler", "do~ 2");
#endif
        //32bit

#if USE_HIGH_BITS_SAMPER
          // uint8_t i2s_data[1024];  //size= 4*1024
          i2s_read(sampler->i2s_port_, i2s_data, 1024, &bytes_read, 20);
          int32_t *samples = (int32_t *)i2s_data;  //转成原始的 采样值32bit
          for (int i = 0; i < bytes_read / 4; i++) {  //降低信号能量
            sampler->AddSample(samples[i] >> sampler->sampler_shift_);
          }
#else
        //16bit
          // uint8_t i2s_data[1024];  //size= 2*1024
          i2s_read(sampler->i2s_port_, i2s_data, 1024, &bytes_read, 20);
          int16_t *samples = (int16_t *)i2s_data;  //转成原始的 采样值16bit
          for (int i = 0; i < bytes_read / 2; i++) {
            sampler->AddSample(samples[i]);
          }
#endif
          delay(10);
        } while (bytes_read > 0);
      }
    }
    free(i2s_data);
    sampler->i2s_data_temp_ = nullptr;
  }
}

void I2SSampler::Start(TaskHandle_t processor_taskhandle) {
  CrazyLog::d(kTag,"Start");
  processor_taskhandle_ = processor_taskhandle;
  i2s_driver_install(i2s_port_, &i2s_config_, 4, &i2s_queue_);
  i2s_set_pin(i2s_port_, &i2s_pins_);
  i2s_zero_dma_buffer(i2s_port_);
  ////采样任务
  xTaskCreatePinnedToCore(I2SSamplerTask, "I2SSamplerTask", 1024*2, this,
                          TASK_PRIORITY_SAMPLER, &task_handle_, CORE_0);
}

void I2SSampler::Stop() {
  CrazyLog::d(kTag, "Stop");
  if (task_handle_) {
    vTaskDelete(task_handle_);
    task_handle_ = nullptr;
  }
  if(i2s_data_temp_ != nullptr){
    //catch memory leak cause by vTaskDelete
    free(i2s_data_temp_);
    i2s_data_temp_ = nullptr;
  }

  i2s_driver_uninstall(i2s_port_);
}

RingBufferAccessor *I2SSampler::GetRingBufferReader() {
  RingBufferAccessor *reader =
      new RingBufferAccessor(audio_buffers_, SAMPLE_BUFFER_COUNT);
  reader->SetIndex(write_ring_buffer_accessor_->GetIndex());
  return reader;
}

