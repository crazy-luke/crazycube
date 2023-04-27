#include "speech_recognise.h"

#include <string.h>

#include "audio_processor/chunked_uploader.h"
#include "audio_processor/token_store.h"
#include "tools/crazy_log.h"
#include "framework/framework.h"
#include "framework/system/mic/mic.h"

#define WINDOW_SIZE 320
#define STEP_SIZE 160
#define POOLING_SIZE 6
#define AUDIO_LENGTH 16000

#define SPEECH_DURATION_LIMIT uint16_t(30000)  //限制收音时长,30秒
#define CHUNK_BUFFER_LEN 500

SpeechRecognise::~SpeechRecognise() {
  CrazyLog::d(kTag, "~release");
  if (m_speech_recogniser != nullptr) {
    delete (m_speech_recogniser);
    m_speech_recogniser = NULL;
  }

  if(reader_temp_){
    CrazyLog::i(kTag, "wo~,catch memory leak reader");
    delete(reader_temp_);
    reader_temp_ = nullptr;
  }
}

SpeechRecognise::SpeechRecognise(I2SSampler *sample_provider) {
  CrazyLog::d(kTag, "constructor!"); 
  sample_provider_ = sample_provider;
}

bool SpeechRecognise::Enter(String token, SpeechLanguage language, uint16_t speech_max_time) {
  CrazyLog::d(kTag, "Enter language:%d, speech_max_time:%d",language,speech_max_time);
  
  if(token.isEmpty()){
    CrazyLog::e(kTag,"token is empty");
    return false;
  }

  // CrazyLog::ram("speech before connection");
  m_speech_recogniser = new ChunkedUploader();

  String dev_pid="";
  if(language == SpeechLanguage::MANDARIN)  
    dev_pid = DEV_PID_SPEECH_MANDARIN;
  else if(language == SpeechLanguage::ENGLISH) 
    dev_pid = DEV_PID_SPEECH_ENGLISH;

  if(!m_speech_recogniser->ConnectHost(token, dev_pid, 1))
    return false;

  speech_max_time_ = std::min(speech_max_time, SPEECH_DURATION_LIMIT);

  // CrazyLog::ram("speech after connection");

  start_time_ = millis();
  elapsed_time_ = 0;
  last_audio_position_ = -1;
  return true;
}

bool SpeechRecognise::Run(String& msg, bool force_result) {
#if CRAZY_LOG_YELL  // save memory
  CrazyLog::v(kTag, "Run~");
#endif

  if (!m_speech_recogniser || !m_speech_recogniser->connected()) {
    // no http client - something went wrong somewhere move to the next state as
    // there's nothing for us to do
    CrazyLog::e(kTag, "Error - Attempt to run with no http client");
    return true;
  }

  if (last_audio_position_ == -1) {
    // set to 1 seconds in the past the allow for the really slow connection
    // time
    last_audio_position_ =
        sample_provider_->GetCurrentWritePosition() - SAMPLE_RATE;
  }
  // how many samples have been captured since we last ran
  int audio_position = sample_provider_->GetCurrentWritePosition();

  // work out how many samples there are taking into account that we can wrap
  // around
  int sample_count = (audio_position - last_audio_position_ +
                      sample_provider_->GetRingBufferSize()) %
                     sample_provider_->GetRingBufferSize();

#if CRAZY_LOG_YELL  // save memory
  CrazyLog::d(
      kTag, "Last sample position %d, current position %d, number samples %d\n",
      last_audio_position_, audio_position, sample_count);
#endif

  if (sample_count > 0) {
    // send the samples to the server
    m_speech_recogniser->StartChunk(sample_count * sizeof(int16_t));
    RingBufferAccessor *reader = sample_provider_->GetRingBufferReader();
    reader_temp_ = reader;
    reader->SetIndex(last_audio_position_);
    // send the samples up in chunks
    int16_t sample_buffer[CHUNK_BUFFER_LEN];
    while (sample_count > 0) {
      for (int i = 0; i < sample_count && i < CHUNK_BUFFER_LEN; i++) {
        sample_buffer[i] = reader->GetCurrentSample();
        reader->MoveToNextSample();
      }

      size_t send_size = m_speech_recogniser->SendChunkData(
          (const uint8_t *)sample_buffer, std::min(sample_count, CHUNK_BUFFER_LEN) * 2);
      // if (!m_speech_recogniser || !m_speech_recogniser->connected())
      // CrazyLog::e(kTag,"Error -  9~~ %d",send_size);
      sample_count -= CHUNK_BUFFER_LEN;
    }
    last_audio_position_ = reader->GetIndex();
    m_speech_recogniser->FinishChunk();
    delete (reader);
    reader_temp_ = nullptr;

    // check finish 
    elapsed_time_ = millis() - start_time_;
    if (force_result || elapsed_time_ >= speech_max_time_) {
      CrazyLog::d(kTag, "finishing recognition request");
      if(force_result) CrazyLog::d(kTag,"finishing by force");
      // final new line to finish off the request
      auto speech_result = m_speech_recogniser->GetResults();
      if (speech_result.success) {
        msg = speech_result.result_text;
      }
      return true;
    }
  }
  return false;
}

void SpeechRecognise::Exit() {
  CrazyLog::d(kTag, "Exit");
  // clean up the speech recognizer client as it takes up a lot of RAM
  if (m_speech_recogniser != nullptr) {
    delete (m_speech_recogniser);
    m_speech_recogniser = nullptr;
  }
  CrazyLog::ram("SpeechRecognise Exit");
}