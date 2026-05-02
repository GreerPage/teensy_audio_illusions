#include <Audio.h>
#include <Wire.h>
#include <SPI.h>

#include "audio_setup.h"
#include "missing_fundamental.h"

// Pots
byte POT1 = A0;
byte POT2 = A2;
byte POT3 = A1;


// Sustained oscillator
AudioSynthWaveform richOsc;

// Filter to remove the fundamental
AudioFilterBiquad highpass;

// Mixer
AudioMixer4 mainMixer;

// Routing
AudioConnection cable1(richOsc, 0, mainMixer, 0); // normal tone
AudioConnection cable2(richOsc, 0, highpass, 0);  // filtered tone
AudioConnection cable3(highpass, 0, mainMixer, 1);

AudioConnection cable4(mainMixer, 0, masterMixer, 1);

float getNoteFrequency(int potValue) {
  // Divide 1024 into 24 equal buckets (one per note)
  int noteIndex = potValue / (1024 / 24);
  
  float frequency;
  switch (noteIndex) {
    case 0:  frequency = 110.00; break; // A2
    case 1:  frequency = 116.54; break; // A#2
    case 2:  frequency = 123.47; break; // B2
    case 3:  frequency = 130.81; break; // C3
    case 4:  frequency = 138.59; break; // C#3
    case 5:  frequency = 146.83; break; // D3
    case 6:  frequency = 155.56; break; // D#3
    case 7:  frequency = 164.81; break; // E3
    case 8:  frequency = 174.61; break; // F3
    case 9:  frequency = 185.00; break; // F#3
    case 10: frequency = 196.00; break; // G3
    case 11: frequency = 207.65; break; // G#3
    case 12: frequency = 220.00; break; // A3
    case 13: frequency = 233.08; break; // A#3
    case 14: frequency = 246.94; break; // B3
    case 15: frequency = 261.63; break; // C4
    case 16: frequency = 277.18; break; // C#4
    case 17: frequency = 293.66; break; // D4
    case 18: frequency = 311.13; break; // D#4
    case 19: frequency = 329.63; break; // E4
    case 20: frequency = 349.23; break; // F4
    case 21: frequency = 369.99; break; // F#4
    case 22: frequency = 392.00; break; // G4
    case 23: frequency = 440.00; break; // A4
    default: frequency = 220.00; break; // default to A3
  }
  return frequency;
}

void playNormalTone() {
  mainMixer.gain(0, 0.45); // original signal
  mainMixer.gain(1, 0.0);  // filtered signal 
}

void playMissingFundamental() {
  mainMixer.gain(0, 0.0);  // original signal off
  mainMixer.gain(1, 0.75); // filtered signal
}

void demonstrateMF() {
  int mode = analogRead(POT2);
  float freq = getNoteFrequency(analogRead(POT3));

  richOsc.begin(0.45, freq, WAVEFORM_TRIANGLE);
  switch (mode) {
    case 0 ... 509:
      playNormalTone();
      break;

    case 510 ... 650:
      highpass.setHighpass(0, freq + 50.0, 0.5);
      playMissingFundamental();
      break;

    case 651 ... 750:
      highpass.setHighpass(0, 2.0 * freq + 50.0, 0.707);
      playMissingFundamental();
      break;

    case 751 ... 850:
      highpass.setHighpass(0, 3.0 * freq + 50.0, 0.707);
      playMissingFundamental();
      break;

    case 851 ... 950:
      highpass.setHighpass(0, 4.0 * freq + 50.0, 0.707);
      playMissingFundamental();
      break;
  }
  delay(20);
}

void stopMF() {
    mainMixer.gain(0, 0.0);
    mainMixer.gain(1, 0.0);
}
