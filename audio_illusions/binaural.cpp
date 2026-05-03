#include "audio_setup.h"
#include "binaural.h"
#include "missing_fundamental.h"

byte BASE_PIN = A1;
byte BEAT_PIN = A2;

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
  int beatAdd = map(analogRead(BEAT_PIN), 0, 1023, 1, 10);
  float baseFrequency = getNoteFrequency(analogRead(BASE_PIN));
  float beatFrequency = baseFrequency + (float)beatAdd;
  base.frequency(baseFrequency);
  beat.frequency(beatFrequency);
  base.amplitude(0.4);
  beat.amplitude(0.4);
}

void stopBinaural() {
  base.amplitude(0);
  beat.amplitude(0);
}