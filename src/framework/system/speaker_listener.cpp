#include "speaker_listener.h"

#include "tools/crazy_log.h"

void SpeakerListenerContainer::OnAudioFinishLintener() {
  CrazyLog::d(kTag, "OnAudioFinishLintener");
  if (listener_) {
    listener_->OnAudioFinish();
  }
}

void SpeakerListenerContainer::PutListener(SpeakerListener* listener) {
  CrazyLog::d(kTag, "PutListener");
  listener_ = listener;
}

void SpeakerListenerContainer::Clear() {
  CrazyLog::d(kTag, "Clear");
  listener_ = nullptr;
}