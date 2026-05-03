/*
audio_setup.cpp handles 
- Initialization of teensy Audio library
- Volume control
- 
*/

#include "audio_setup.h"

byte VOLUME_PIN = A0;

AudioMixer4 masterMixer;
AudioOutputI2S audioOut;
AudioControlSGTL5000 sgtl5000;

AudioConnection masterLeft(masterMixer, 0, audioOut, 0);
AudioConnection masterRight(masterMixer, 0, audioOut, 1);

void setupAudioSystem() {
  AudioMemory(60);

  sgtl5000.enable();
  sgtl5000.volume(0.5);

  masterMixer.gain(0, 1.0);
  masterMixer.gain(1, 1.0);
  masterMixer.gain(2, 1.0);
  masterMixer.gain(3, 1.0);
}

void volumeControl() {
  int pot = analogRead(VOLUME_PIN);
  float volume = pot / 2046.0;
  if (volume < 0.002) sgtl5000.volume(0);
  else sgtl5000.volume(volume);
}