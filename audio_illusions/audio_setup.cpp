/*
audio_setup.cpp handles 
- Initialization of teensy Audio library
- Volume control
- Definition of output devices and master mixer
*/

#include "audio_setup.h"

// volume control pin
byte VOLUME_PIN = A0;

AudioMixer4 masterMixer; // create master mixer for all illusions to pass through
AudioOutputI2S audioOut; // create single audio output from headphone jack
AudioControlSGTL5000 sgtl5000; // create audio controller object

// output the master mix from the headphone jack
AudioConnection masterLeft(masterMixer, 0, audioOut, 0); // left speacker
AudioConnection masterRight(masterMixer, 0, audioOut, 1); // right speaker

void setupAudioSystem() {
  /* set up audio system */

  AudioMemory(60); // allocate memory to audio
  sgtl5000.enable(); // start comtroller

  // set gain for each channel of master mixer (1 for max gain)
  masterMixer.gain(0, 1.0);
  masterMixer.gain(1, 1.0);
  masterMixer.gain(2, 1.0);
  masterMixer.gain(3, 1.0);
}

void volumeControl() {
  /* Control device output volume */
  int pot = analogRead(VOLUME_PIN); // read volume pot
  float volume = pot / 2046.0; // keep volume from 0 - 0.5 (comfortable range)
  if (volume < 0.002) sgtl5000.volume(0); // make sure it goes to 0
  else sgtl5000.volume(volume); // set volume
}