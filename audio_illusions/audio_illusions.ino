/* 
arduino_illusions.ino handles 
- volume control 
- switching between illusions
*/

// link files
#include "shepard.h"
#include "audio_setup.h"
#include "missing_fundamental.h"

// pin associated with mode switching pot
byte CONTROL_PIN = A8;

void setup() {
  /* SETUP */
  setupAudioSystem(); // initialize audio library (see audio_setup.cpp)
  setupShepardTone(); // initilaize shepard (see shepard.cpp) 
}

void loop() {
  /* LOOP */
  volumeControl(); // update output volume
  int control = analogRead(CONTROL_PIN); 

  switch(control) {
    case 200 ... 300:
      demonstrateMF();
      break;

    case 400 ... 500:
      shepard();
      break;

    default: 
      stopShepard();
      stopMF();
      break; 
  } 
}
