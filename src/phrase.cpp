#include "phrase.h"

Phrase::Phrase(int sample_rate)
  : sample_rate(sample_rate)
{}

Phrase::~Phrase() {
  // nothing
}


bool Phrase::addAudio(const float* buffer) {
  // nothing
}

bool Phrase::completeRecording() {
  // nothing
}

bool Phrase::getAudio(float begin, float end, float* buffer) {
  // nothing
}
