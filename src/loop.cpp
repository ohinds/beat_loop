#include "loop.h"

Loop::Loop()
  : playing(false)
  , current_position(0.)
{
  // nothing
}

Loop::~Loop() {
  // nothing
}

bool Loop::init() {
  // nothing
}

bool Loop::run() {
  // nothing
}

bool Loop::play() {
  // nothing
}

bool Loop::pause() {
  // nothing
}

bool Loop::stop() {
  // nothing
}

int Loop::processCallback(jack_nframes_t nframes, void* arg) {
  Loop* loop = static_cast<Loop*>(arg);
  return loop->process(nframes);
}

int Loop::process(jack_nframes_t nframes) {
  /* the real thing, as a normal member function */
}
