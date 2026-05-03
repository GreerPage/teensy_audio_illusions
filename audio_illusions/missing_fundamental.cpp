/* 
missing_fundamental.cpp demonstrates the mssing fundamental illusion:
Using a high pass filter, the fundamental (lowest) tone can be removed from a frequency
The mind will still perceive the original fundamental tone even though its not playing
The mind uses the overtones (harmonics) to deduce the filtered fundamental
This script can:
- Play notes A2 to A4 to demonstrate the illusions
- Filter out fundamental tone and multiple harmonics based on a potentiometer
*/

#include "audio_setup.h"
#include "missing_fundamental.h"

// Pots
byte NOTE_CONTROL = A1;
byte FILTER_CONTROL = A2;



AudioSynthWaveform fundamental; // create the wave object to be filtered 
AudioFilterBiquad highpass; // filter to remove the fundamental
AudioMixer4 mainMixer; // create a mixer to connect differnt frequencies

// Routing
AudioConnection cable1(fundamental, 0, mainMixer, 0); // normal tone to mixer channel 0
AudioConnection cable2(fundamental, 0, highpass, 0);  // normal tome to filtered tone
AudioConnection cable3(highpass, 0, mainMixer, 1); // filtered tone to mixer channel 1
AudioConnection cable4(mainMixer, 0, masterMixer, 1); // patch to master

float getNoteFrequency(int potValue) {
  /* Get a note frequency based on a potentiometer */

  // divide 1024 into 24 equal buckets (one per note)
  int noteIndex = potValue / (1024 / 24);
  float frequency;

  switch (noteIndex) {
    // get note frequency
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
  /* play the fundamenal tone without filter */

  mainMixer.gain(0, 0.45); // original signal on
  mainMixer.gain(1, 0.0);  // filtered signal off
}

void playMissingFundamental() {
  /* play the filtered tone (overtones) */

  mainMixer.gain(0, 0.0);  // original signal off
  mainMixer.gain(1, 0.75); // filtered signal on
}

void demonstrateMF() {
  /* Demo of the missing fundamental illusion */

  int mode = analogRead(FILTER_CONTROL); // pot vlaue to control severity of filtration
  float freq = getNoteFrequency(analogRead(NOTE_CONTROL)); // pot value to determine note

  fundamental.begin(0.45, freq, WAVEFORM_TRIANGLE); // define the fundamental tone
  switch (mode) {
    // control filtration 
    case 0 ... 509:
      // play unfiltered tone
      playNormalTone();
      break;

    case 510 ... 1023:
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
  /* Stop function for control in audio_illusions.ino */
  mainMixer.gain(0, 0.0);
  mainMixer.gain(1, 0.0);
}
