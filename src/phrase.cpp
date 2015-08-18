#include "phrase.h"

#include "algorithm"

using std::copy;

Phrase::Phrase()
  : ui(true)
{}

Phrase::~Phrase() {
  // nothing
}


bool Phrase::addAudio(const sample_vec &buffer) {
  audio.reserve(audio.size() + buffer.size());
  audio.insert(audio.end(), buffer.begin(), buffer.end());
  return true;
}

bool Phrase::getAudio(nframes_t begin, sample_vec* buffer) {

  if (begin + buffer->size() > audio.size()) {
    ui << "error, audio request out of bounds\n";
    return false;
  }

  copy(audio.begin() + begin, audio.begin() + begin + buffer->size(),
       buffer->begin());

  return true;
}
