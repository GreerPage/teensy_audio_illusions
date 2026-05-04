/* 
arduino_illusions.ino handles 
- volume control 
- switching between illusions
*/

// link files
#include "shepard.h"
#include "binaural.h"
#include "audio_setup.h"
#include "missing_fundamental.h"

// pin associated with mode switching pot
byte CONTROL_PIN = A8;

void setup() {
  /* SETUP */
  setupAudioSystem(); // initialize audio library (see audio_setup.cpp)
  setupShepardTone(); // initilaize shepard (see shepard.cpp) 
  setupBinaural(); // setup binaural beats (see binaural.cpp)
}

void loop() {
  /* LOOP */
  volumeControl(); // update output volume (see audio_setup.cpp)
  
  // 10 bit pot value to switch between illusion modes
  int control = analogRead(CONTROL_PIN); 

  switch(control) {
    /* Control which illusion is playing */
    case 200 ... 400:
      // demonstrate binaural beats
      binauralBeats();
      break;

    case 500 ... 700:
      // demonstrate missing fundamental (see missing_fundamental.cpp)
      demonstrateMF();
      break;

    case 800 ... 1000:
      // play shepard tone (see shepard.cpp)
      shepard();
      break;

    default: 
      // off by default
      stopShepard();
      stopMF();
      stopBinaural();
      break; 
  } 
}
