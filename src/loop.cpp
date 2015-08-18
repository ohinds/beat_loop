#include "loop.h"

#include <algorithm>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <string.h>
#include <unistd.h>

using std::plus;
using std::string;
using std::transform;

namespace {

jack_port_t *input_port;
jack_port_t *output_port;
jack_client_t *client;

}

Loop::Loop()
  : playing(false)
  , recording(false)
  , paused(false)
  , current_position(0)
  , loop_length(0)
  , num_active_phrases(0)
  , ui(true)
{
  // nothing
}

Loop::~Loop() {
  // nothing
}

bool Loop::init() {
  const char *client_name = "beat_loop";
  const char *server_name = NULL;
  jack_options_t options = JackNullOption;
  jack_status_t status;

  client = jack_client_open(client_name, options, &status, server_name);
  if (client == NULL) {
    ui << "jack_client_open() failed, status = " << status << "\n";
    if (status & JackServerFailed) {
      ui << "Unable to connect to JACK server\n";
    }
    return false;
  }
  if (status & JackServerStarted) {
    ui << "JACK server started\n";
  }
  if (status & JackNameNotUnique) {
    client_name = jack_get_client_name(client);
    ui << "unique name '" << client_name << "' assigned\n";
  }

  jack_set_process_callback(client, processCallback, this);

  input_port = jack_port_register(
    client, "input",
    JACK_DEFAULT_AUDIO_TYPE, JackPortIsInput, 0);
  output_port = jack_port_register(
    client, "output",
    JACK_DEFAULT_AUDIO_TYPE, JackPortIsOutput, 0);

  return true;
}

bool Loop::run() {
  const char **ports;

  if (jack_activate(client)) {
    ui << "cannot activate client\n";
    return false;
  }

  if ((ports = jack_get_ports(client, NULL, NULL,
                              JackPortIsPhysical|JackPortIsOutput)) == NULL) {
    ui << "Cannot find any physical capture ports\n";
    return false;
  }

  if (jack_connect(client, ports[0], jack_port_name (input_port))) {
    ui << "cannot connect input ports\n";
  }

  free(ports);

  ports = jack_get_ports(
    client, NULL, NULL, JackPortIsPhysical|JackPortIsInput);
  if (ports == NULL) {
    ui << "Cannot find any physical playback ports\n";
     return false;
  }

  for (int i = 0; ports[i] != NULL; i++) {
    if (jack_connect(client, jack_port_name(output_port), ports[i])) {
      ui << "cannot connect output ports\n";
    }
  }

  free(ports);
}

bool Loop::shutdown() {
  jack_client_close(client);
}

bool Loop::play() {
  if (playing) {
    ui << "can't play when already playing\n";
    return false;
  }

  playing = true;

  return true;
}

bool Loop::toggle_pause() {
  return true;
}

bool Loop::stop() {
  if (!playing) {
    ui << "can't stop when not playing\n";
    return false;
  }

  playing = false;

  return true;
}

bool Loop::toggle_record() {
  ui << "toggle record from " << recording << "\n";

  if (recording) {
    return stop_recording();
  }
  else {
    return start_recording();
  }
}

bool Loop::start_recording() {
  if (recording) {
    ui << "can't start recording when already recording\n";
    return false;
  }

  if (!playing) {
    if (play()) {
      recording = true;
      phrases.push_back(Phrase());
    }
    else {
      ui << "failed to start playback\n";
      return false;
    }
  }
  else if (paused) {
    if (toggle_pause()) {
      waiting_to_record = true;
    }
    else {
      ui << "failed to resume playback\n";
    }
  }
  else {
    waiting_to_record = true;
  }

  return true;
}

bool Loop::stop_recording() {
  if (!recording) {
    ui << "can't stop recording when not recording\n";
    return false;
  }

  num_active_phrases++;

  if (num_active_phrases == 1) {
    loop_length = current_position;
  }

  recording = false;

  return true;
}

int Loop::processCallback(nframes_t nframes, void* arg) {
  Loop* loop = static_cast<Loop*>(arg);
  return loop->process(nframes);
}

int Loop::process(nframes_t nframes) {
  if (playing) {
    current_position += nframes;

    if (loop_length > 0 && current_position >= loop_length) {
      current_position -= loop_length;

      //assert(current_position < loop_length);

      // if (recording) {
      //   num_active_phrases++;
      //   phrases.push_back(Phrase());
      // }

      if (waiting_to_record) {
        recording = true;
        waiting_to_record = false;
        phrases.push_back(Phrase());
      }
    }
  }

  jack_default_audio_sample_t *jack_out =
    static_cast<jack_default_audio_sample_t*>(
      jack_port_get_buffer(output_port, nframes));

  jack_default_audio_sample_t *jack_in =
    static_cast<jack_default_audio_sample_t *>(
      jack_port_get_buffer(input_port, nframes));
  sample_vec in(jack_in, jack_in + nframes);

  if (recording && playing) {
    phrases.back().addAudio(in);
  }

  // combine the existing phrases with the out buffer
  sample_vec phrase_out(nframes);

  for (size_t i = 0; i < num_active_phrases; i++) {
    if (!phrases[i].getAudio(current_position, &phrase_out)) {
      ui << "phrase " << i << " failed\n";
      continue;
    }

    transform(in.begin(), in.end(), phrase_out.begin(),
              in.begin(), plus<sample_t>());
  }

  memcpy(jack_out, in.data(), sizeof(sample_t) * nframes);
  return 0;
}
