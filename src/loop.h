// Loop class

#pragma once

#include <vector>

#include "phrase.h"
#include "types.h"
#include "ui.h"

class Loop {

 public:

  Loop();

  ~Loop();

  bool init();

  bool run();

  bool shutdown();

  bool play();

  bool toggle_pause();

  bool toggle_record();

  bool stop();

 private:

  bool start_recording();

  bool stop_recording();

  static int processCallback(nframes_t nframes, void* arg);

  int process(nframes_t nframes);

  bool playing;
  bool recording;
  bool waiting_to_record;
  bool paused;
  nframes_t current_position;
  nframes_t loop_length;

  std::vector<Phrase> phrases;
  size_t num_active_phrases;

  Ui ui;
};
