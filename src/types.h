#pragma once

#include <vector>

#include <jack/jack.h>

typedef jack_default_audio_sample_t sample_t;

typedef std::vector<sample_t> sample_vec;

typedef jack_nframes_t nframes_t;
