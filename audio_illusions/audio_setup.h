#ifndef AUDIO_SYSTEM_H
#define AUDIO_SYSTEM_H

#include <Audio.h>

extern AudioMixer4 masterMixer;
extern AudioOutputI2S audioOut;
extern AudioControlSGTL5000 sgtl5000;

void setupAudioSystem();
void volumeControl();

#endif