// Loop class

#include <vector>

#include <jack/jack.h>

#include "phrase.h"

class Loop {

 public:

  Loop();

  ~Loop();

  bool init();

  bool run();

  bool play();

  bool pause();

  bool stop();

 private:

  static int processCallback(jack_nframes_t nframes, void* arg);

  int process(jack_nframes_t nframes);

  bool playing;
  float current_position;

  std::vector<Phrase> phrases;
};
