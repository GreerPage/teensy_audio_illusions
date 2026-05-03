/*
binaural.cpp demonstrates the binaural beats illusion.
This is when two tones of similar frequencies are played together for example; 440 and 444Hz.
the preceived tone is a beating tone at the frequency of the difference of the tones for example; 4Hz.
This module allows:
- Base note control with a potentiometer.
- Beat frequency control with a potentiometer.
*/

#include "audio_setup.h"
#include "binaural.h"
#include "missing_fundamental.h"

// Potentiometer pins
byte BASE_PIN = A1;
byte BEAT_PIN = A2;

// Delcaration of sien wave objects
AudioSynthWaveformSine base;
AudioSynthWaveformSine beat;

// Declaration of audio mixer
AudioMixer4 binMixer;

// Routing sine waves to the mixer
AudioConnection bb1(base, 0, binMixer, 0);
AudioConnection bb2(beat, 0, binMixer, 1);

// Routing local mixer to master mixer
AudioConnection bb3(binMixer, 0, masterMixer, 2);

void setupBinaural() {
  /* To run in setup() in audio_illusions.ino */
  // set gain as even for both.
  binMixer.gain(0, 0.5); 
  binMixer.gain(1, 0.5);
}

void binauralBeats() {
  /* Demostration of binaural betas to be run in loop() */

  int beatAdd = map(analogRead(BEAT_PIN), 0, 1023, 1, 10); // get difference between frequencies
  float baseFrequency = getNoteFrequency(analogRead(BASE_PIN)); // get base note (function from missing_fundamental.cpp)
  float beatFrequency = baseFrequency + (float)beatAdd; // beat freq. is base + difference
  
  // set frequencies 
  base.frequency(baseFrequency); 
  beat.frequency(beatFrequency);

  // set amplitudes
  base.amplitude(0.7);
  beat.amplitude(0.7);
}

void stopBinaural() {
  // turn off binaural beats
  base.amplitude(0);
  beat.amplitude(0);
}