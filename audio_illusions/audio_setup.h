/* Header file for audio_setup */

#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

// include all necessary libraries
#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

// objects needed for each illusion
extern AudioMixer4 masterMixer;
extern AudioOutputI2S audioOut;
extern AudioControlSGTL5000 sgtl5000;

// functions from audio_setup.cpp
void setupAudioSystem();
void volumeControl();

#endif