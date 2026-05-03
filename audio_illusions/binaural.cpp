#include "audio_setup.h"
#include "binaural.h"

AudioSynthWaveformSine base;
AudioSynthWaveformSine beat;

AudioMixer4 binMixer;

AudioConnection bb1(base, 0, binMixer, 0);
AudioConnection bb2(beat, 0, binMixer, 1);

AudioConnection bb3(binMixer, 0, masterMixer, 2);

void setupBinaural() {
  binMixer.gain(0, 0.5);
  binMixer.gain(1, 0.5);
}

void binauralBeats() {
  base.frequency(440);
  beat.frequency(444);
  base.amplitude(0.4);
  beat.amplitude(0.4);
}

void stopBinaural() {
  base.amplitude(0);
  beat.amplitude(0);
}