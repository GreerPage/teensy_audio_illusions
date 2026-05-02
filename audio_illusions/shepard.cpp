#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

#include "audio_setup.h"
#include "shepard.h"

// Pots
const byte POT_VOLUME = A0;
const byte POT_SPEED  = A1;

// Shepard settings
const float BASE_FREQ = 55.0;   // A1
const int NUM_OSC = 8;



// Oscillators
AudioSynthWaveformSine osc0, osc1, osc2, osc3, osc4, osc5, osc6, osc7;

// Mixers
AudioMixer4 mixerA;
AudioMixer4 mixerB;
AudioMixer4 finalMixer;


// Routing
AudioConnection pc1(osc0, 0, mixerA, 0);
AudioConnection pc2(osc1, 0, mixerA, 1);
AudioConnection pc3(osc2, 0, mixerA, 2);
AudioConnection pc4(osc3, 0, mixerA, 3);

AudioConnection pc5(osc4, 0, mixerB, 0);
AudioConnection pc6(osc5, 0, mixerB, 1);
AudioConnection pc7(osc6, 0, mixerB, 2);
AudioConnection pc8(osc7, 0, mixerB, 3);

AudioConnection pc9(mixerA, 0, finalMixer, 0);
AudioConnection pc10(mixerB, 0, finalMixer, 1);

AudioConnection pc11(finalMixer, 0, masterMixer, 0);


AudioSynthWaveformSine* osc[NUM_OSC] = {
    &osc0, &osc1, &osc2, &osc3, &osc4, &osc5, &osc6, &osc7
};

float phase = 0.0;

float octavePosition(float x) {
  while (x >= NUM_OSC) x -= NUM_OSC;
  while (x < 0) x += NUM_OSC;
  return x;
}

float bellGain(float pos) {
  float center = (NUM_OSC - 1) / 2.0;
  float width = 2.1;

  float diff = pos - center;
  float gain = exp(-(diff * diff) / (2.0 * width * width));

  return gain;
}


void shepard() {
  int speedPot = analogRead(POT_SPEED);
  float speed = map(speedPot, 0, 1023, 1, 40) / 10000.0;
  phase += speed;
  if (phase >= 1.0) {
    phase -= 1.0;
  }

  for (int i = 0; i < NUM_OSC; i++) {
    float pos = octavePosition(i + phase);

    float freq = BASE_FREQ * pow(2.0, pos);

    // Wrap into useful audible range
    while (freq > BASE_FREQ * pow(2.0, NUM_OSC)) {
      freq /= 2.0;
    }

    float gain = bellGain(pos) * 0.18;

    osc[i]->frequency(freq);
    osc[i]->amplitude(gain);
  }
}

void stopShepard() {
    for (int i = 0; i < NUM_OSC; i++) {
        osc[i]->amplitude(0);
    }
}

void setupShepardTone() {
  mixerA.gain(0, 1.0);
  mixerA.gain(1, 1.0);
  mixerA.gain(2, 1.0);
  mixerA.gain(3, 1.0);

  mixerB.gain(0, 1.0);
  mixerB.gain(1, 1.0);
  mixerB.gain(2, 1.0);
  mixerB.gain(3, 1.0);

  finalMixer.gain(0, 0.35);
  finalMixer.gain(1, 0.35);

  for (int i = 0; i < NUM_OSC; i++) {
    osc[i]->frequency(BASE_FREQ * pow(2.0, i));
    osc[i]->amplitude(0.0);
  }
}

