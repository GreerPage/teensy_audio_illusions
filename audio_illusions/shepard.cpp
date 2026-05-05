/*
shepard.cpp demonstrates the shepard tone auditory illusion:
A tone that sounds like it is infinetly rising.
Sine waves one octave part are rasied in pitch simultaneously.
As they reach an upper octave their volume decreaases.
When they reach that octave they reset to a lower octave.
The wave gets louder as it reapproaches the center range of frequencies.
There is also speed control implemented.
*/

#include "audio_setup.h"
#include "shepard.h"

// speed control pot
const byte POT_SPEED  = A1;

// Shepard settings
const float BASE_FREQ = 55.0;   // A1
const int NUM_OSC = 8; // number of sine waves



// Initialize 8 oscillator objects
AudioSynthWaveformSine osc0, osc1, osc2, osc3, osc4, osc5, osc6, osc7;

// 3 mixers are necessary as they only take 4 inputs
// 2 for the 8 sine waves and 1 to combine the first 2
AudioMixer4 mixerA;
AudioMixer4 mixerB;
AudioMixer4 finalMixer;


// Routing to Mixer A
AudioConnection pc1(osc0, 0, mixerA, 0);
AudioConnection pc2(osc1, 0, mixerA, 1);
AudioConnection pc3(osc2, 0, mixerA, 2);
AudioConnection pc4(osc3, 0, mixerA, 3);
// Routing to Mixer B
AudioConnection pc5(osc4, 0, mixerB, 0);
AudioConnection pc6(osc5, 0, mixerB, 1);
AudioConnection pc7(osc6, 0, mixerB, 2);
AudioConnection pc8(osc7, 0, mixerB, 3);
// Combing A and B
AudioConnection pc9(mixerA, 0, finalMixer, 0);
AudioConnection pc10(mixerB, 0, finalMixer, 1);
// Routing to Master 
AudioConnection pc11(finalMixer, 0, masterMixer, 0);

// pointer array so that oscillators can be iterated over
// traditional arrays of oscillator objects break
AudioSynthWaveformSine* osc[NUM_OSC] = {
    &osc0, &osc1, &osc2, &osc3, &osc4, &osc5, &osc6, &osc7
};

float phase = 0.0; // phase initilization 

void setupShepardTone() {
  /* Set up for sheoard tone */

  // gain for Mixer A
  mixerA.gain(0, 1.0);
  mixerA.gain(1, 1.0);
  mixerA.gain(2, 1.0);
  mixerA.gain(3, 1.0);

  // gain for Mixer B
  mixerB.gain(0, 1.0);
  mixerB.gain(1, 1.0);
  mixerB.gain(2, 1.0);
  mixerB.gain(3, 1.0);

  // final gain
  finalMixer.gain(0, 0.35);
  finalMixer.gain(1, 0.35);

  for (int i = 0; i < NUM_OSC; i++) {
    // initial octave positioning
    osc[i]->frequency(BASE_FREQ * pow(2.0, i));
    osc[i]->amplitude(0.0);
  }
}

float octavePosition(float x) {
  /* Keeps all sine waves between 1st and 8th octave of base tone */

  while (x >= NUM_OSC) x -= NUM_OSC;
  while (x < 0) x += NUM_OSC;
  return x;
}

float bellGain(float pos) {
  /* Keeps middle frequencies loud and lower and upper frequencies quiet */
  /* Allows for seemless transition when waves reach their max octave and reset */

  float center = (NUM_OSC - 1) / 2.0; // finder center of frequency ranges acorss all octaves
  float width = 2.1; // width of loud region from the center

  float diff = pos - center; // used to determine how loud based on octave position
  float gain = exp(-(diff * diff) / (2.0 * width * width)); // bell curve gain determination

  return gain;
}


void shepard() {
  /* Shepard demonstration, looped in loop() in audio_illusions.ino */

  int speedPot = analogRead(POT_SPEED); // read pot for speed control
  float speed = map(speedPot, 0, 1023, 1, 40) / 10000.0; // map to a speed value
                                                         // this vlaue determines how quickly the waves rise in pitch
  phase += speed;
  if (phase >= 1.0) {
    phase -= 1.0;
  }

  for (int i = 0; i < NUM_OSC; i++) {
    // iterate over all waves from the pointer array

    float pos = octavePosition(i + phase); // get octave position
    float freq = BASE_FREQ * pow(2.0, pos); // get the frequency based on octave position

    while (freq > BASE_FREQ * pow(2.0, NUM_OSC)) {
      // if the wave's frequency is an octave too high, move it down an octave
      freq /= 2.0;
    }

    float gain = bellGain(pos) * 0.18; // determine gain based on octave position
                                       // 0.18 keeps it in a comfortable audio ranges

    osc[i]->frequency(freq); // set the wave's frequency 
    osc[i]->amplitude(gain); // set the waves amplitude
  }
  delay(10);
}

void stopShepard() {
  /* Shut off shepard tone for control in audio_illusions.ino */

    for (int i = 0; i < NUM_OSC; i++) {
        // turn each oscillators amplitude to 0
        osc[i]->amplitude(0);
    }
}