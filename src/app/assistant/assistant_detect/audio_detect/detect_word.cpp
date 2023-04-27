#include "detect_word.h"

#include "audio_processor/audio_processor.h"
#include "tflite_adapter/neural_network/NeuralNetwork.h"
#include "tools/crazy_log.h"
#include "framework/system/mic/ring_buffer.h"
#include "framework/system/sys.h"

#define WINDOW_SIZE 320
#define STEP_SIZE 160
#define POOLING_SIZE 6
#define AUDIO_LENGTH 16000

DetectWord::~DetectWord() {
  CrazyLog::d(kTag, "~release");
  if (neural_network_) {
    delete (neural_network_);
    neural_network_ = nullptr;
  }
  if (audio_processor_) {
    delete (audio_processor_);
    audio_processor_ = nullptr;
  }

  if (model_) {
    free(model_);
  }

  if(reader_temp_){
    CrazyLog::i(kTag, "wo~,catch memory leak reader");
    delete(reader_temp_);
    reader_temp_ = nullptr;
  }
}

DetectWord::DetectWord(I2SSampler *sample_provider, unsigned char *model) {
  CrazyLog::d(kTag, "constructor!"); 
  // save the sample provider for use later
  sample_provider_ = sample_provider;
  // some stats on performance
  average_detect_time_ = 0;
  number_of_runs_ = 0;
  model_ = model;
}

void DetectWord::Enter() {
  size_t arenaSize = TENSOR_PSRAM_ARENA_SIZE;

  // make sure TFModePSRAM has already loaded
  neural_network_ = new NeuralNetwork(model_, arenaSize);
  // neural_network_ = new NeuralNetwork(converted_model_tflite,tensorArena,arenaSize);
  CrazyLog::d(kTag, "Created Neral Net");
  // create our audio processor
  audio_processor_ =  new AudioProcessor(AUDIO_LENGTH, WINDOW_SIZE, STEP_SIZE, POOLING_SIZE);
  CrazyLog::d(kTag, "Created audio processor");
}

bool DetectWord::Run(String& msg) {
#if CRAZY_LOG_YELL  // save memory  
    CrazyLog::v(kTag, "run~");
#endif 

  long detect_start = millis();

  // get access to the samples that have been read in
  RingBufferAccessor *reader = sample_provider_->GetRingBufferReader();
  reader_temp_ = reader;
  // rewind by 1 second
  reader->Rewind(16000);
  // get hold of the input buffer for the neural network so we can feed it data
  float *input_buffer = neural_network_->getInputBuffer();
  // process the samples to get the spectrogram
  audio_processor_->get_spectrogram(reader, input_buffer);
  // finished with the sample reader
  delete reader;
  reader_temp_ = nullptr;
  // get the prediction for the spectrogram
  float output = neural_network_->predict();

  // show average_detect_time
  average_detect_time_ = (millis() - detect_start) * 0.1 + average_detect_time_ * 0.9;
  number_of_runs_++;
  if (number_of_runs_ == 100) {
    number_of_runs_ = 0;
    CrazyLog::i(kTag, "Average detection time %.fms", average_detect_time_);
  }

  // move to the next state if detected the wake word , otherwise stay in the current state
  if (output >= DECTECT_THRESHOLD) {
    CrazyLog::i(kTag, "P(%.2f) Yes Yes  I am here ~~~ CrazyLuke", output);
    msg = String(output);
    return true;
  } else if (output >= SHOWLOG_THRESHOLD) {
    CrazyLog::d(kTag, "output: P(%.2f)", output);
  }
  return false;
}

void DetectWord::Exit() {
  delete neural_network_;
  neural_network_ = NULL;
  delete audio_processor_;
  audio_processor_ = NULL;
  uint32_t free_ram = esp_get_free_heap_size();
  CrazyLog::d(kTag, "Free ram after DetectWakeWord cleanup %d", free_ram);
}