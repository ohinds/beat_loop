// A phrase is a single instance of loop content. I.e., a single loop
// cycle with unique audio samples

#include <vector>

class Phrase {

 public:

  Phrase(int sample_rate);

  ~Phrase();

  bool addAudio(const float* buffer);

  bool completeRecording();

  bool getAudio(float begin, float end, float* buffer);

 private:

  int sample_rate;
  std::vector<float> audio;

};
