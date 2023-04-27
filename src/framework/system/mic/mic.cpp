#include "mic.h"

#include "tools/crazy_log.h"
#include "ring_buffer.h"

Mic::~Mic() {
  CrazyLog::d(kTag, "~release"); 
  if (i2s_sampler_) {
    i2s_sampler_->Stop();
    delete (i2s_sampler_);
    i2s_sampler_ = nullptr;
  }
  if(i2s_sampler_ == nullptr){
    CrazyLog::d(kTag, "i2s_sampler_ is null"); 
  }
}

void Mic::Init() {
  CrazyLog::d(kTag, "init~");
  if(i2s_sampler_ != nullptr) return;
  i2s_pin_config_t i2s_pin_mic = {.bck_io_num = MIC_I2S_SCK,
                                  .ws_io_num = MIC_I2S_LRC,
                                  .data_out_num = I2S_PIN_NO_CHANGE,
                                  .data_in_num = MIC_I2S_DATA};

  // Crazy-Adam: DMA Buf 设置说明 ，DMA 缓存只能使用 Internal SRAM
  // 缓冲公式：(bits_per_sample/8) * num_channels * dma_buf_len * dma_buf_count
  // CrazyCube dma buffer： 16 / 8） * 1 * 4 * 64 *4 =2k

  i2s_config_t i2s_config = {
    .mode = (i2s_mode_t)(I2S_MODE_MASTER | I2S_MODE_RX),
    .sample_rate = SAMPLE_RATE,
#if USE_HIGH_BITS_SAMPER
    .bits_per_sample = I2S_BITS_PER_SAMPLE_32BIT,
#else
    .bits_per_sample = I2S_BITS_PER_SAMPLE_16BIT,  // enough for CrazyCube
#endif
    .channel_format = I2S_CHANNEL_FMT_ONLY_LEFT,
    .communication_format = i2s_comm_format_t(I2S_COMM_FORMAT_STAND_I2S),
    .intr_alloc_flags = ESP_INTR_FLAG_LEVEL1,
    .dma_buf_count = 4,  //
    .dma_buf_len = 256,
    .use_apll = false,
    .tx_desc_auto_clear = false,
    .fixed_mclk = 0
  };

  i2s_sampler_ = new I2SSampler(I2S_NUM_0, i2s_pin_mic, i2s_config);
}

void Mic::Start(TaskHandle_t processor_task_handle) {
  CrazyLog::d(kTag, "Start");
  if (TaskIsCreated()) {
    SetProcessor(processor_task_handle);
    Resume();
    return;
  }
  i2s_sampler_->Start(processor_task_handle);
}

void Mic::Stop() {
  CrazyLog::d(kTag, "stop!");
  i2s_sampler_->Stop();
}

void Mic::Stop(TaskHandle_t processor_taskhandle){
  if(IsProcessing(processor_taskhandle))
    Stop();
}

TaskHandle_t task_handle_tmp_ = nullptr;

void Mic::Suspend() {
  CrazyLog::d(kTag, "Suspend");
  if (TaskIsCreated()) {
    CrazyLog::d(kTag, "suspend i2s_sampler task_handle");
    vTaskSuspend(task_handle());
  }
   task_handle_tmp_ = nullptr;
}

void Mic::Suspend(TaskHandle_t processor_taskhandle) {
  if(IsProcessing(processor_taskhandle))
    Suspend();
}

void Mic::Resume(uint32_t delay) {
  CrazyLog::d(kTag, "Resume");
  if(delay<=0){
    if (TaskIsCreated()) vTaskResume(task_handle());
    CrazyLog::d(kTag,"Resumed now");
  }else{
    task_handle_tmp_ = i2s_sampler_->task_handle_;
    auto handler =
        xTimerCreate(kTag, delay, pdFALSE, (void*)1, [](TimerHandle_t xTimer) {
          if (task_handle_tmp_ != nullptr)  vTaskResume(task_handle_tmp_);
          task_handle_tmp_ = nullptr;
          CrazyLog::d("Mic","Resumed delay");
        });
    xTimerStart(handler, 0);
  }
}

//当前是否正在为此任务工作
bool Mic::IsProcessing(TaskHandle_t processor_taskhandle){
  if(TaskIsCreated() &&  
    !TaskIsSuspended() && 
    i2s_sampler_->processor_taskhandle_  == processor_taskhandle)
   return true;

  return false;
}

bool Mic::TaskIsSuspended() {
  bool is_suspended = false;
  if (TaskIsCreated() && eTaskGetState(task_handle()) == eSuspended ) {
    is_suspended = true;
  }
  return is_suspended;
}

void Mic::SetProcessor(TaskHandle_t processor_taskhandle)
{   CrazyLog::d(kTag, "SetProcessor");
  i2s_sampler_->processor_taskhandle_ = processor_taskhandle;
}

bool Mic::TaskIsCreated(){ 
  return i2s_sampler_->task_handle_ != nullptr; 
}

TaskHandle_t Mic::task_handle(){
  return i2s_sampler_->task_handle_;
}

