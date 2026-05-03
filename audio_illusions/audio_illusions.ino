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
  volumeControl(); // update output volume (see audio_setup.cpp)
  
  // 10 bit pot value to switch between illusion modes
  int control = analogRead(CONTROL_PIN); 

  switch(control) {
    /* Control which illusion is displaying */
    case 200 ... 300:
      // missing fundamental (see missing_fundamental.cpp)
      demonstrateMF();
      break;

    case 400 ... 500:
      // shepard tone (see shepard.cpp)
      shepard();
      break;

    default: 
      // off by default
      stopShepard();
      stopMF();
      break; 
  } 
}
