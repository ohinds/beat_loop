// A phrase is a single instance of loop content. I.e., a single loop
// cycle with unique audio samples

#pragma once

#include "types.h"
#include "ui.h"

class Phrase {

 public:

  Phrase();

  ~Phrase();

  bool addAudio(const sample_vec &buffer);

  bool getAudio(nframes_t begin_sample, sample_vec* buffer);

 private:

  sample_vec audio;

  Ui ui;
};
