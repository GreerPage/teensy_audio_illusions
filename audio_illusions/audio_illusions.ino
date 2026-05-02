#include "shepard.h"
#include "audio_setup.h"
#include "missing_fundamental.h"

byte CONTROL_PIN = A8;

void setup() {
  // put your setup code here, to run once:
  setupAudioSystem();
  setupShepardTone();
}

void loop() {
  volumeControl();
  int control = analogRead(CONTROL_PIN);

  switch(control) {
    case 200 ... 300:
      shepard();
      delay(10);
      break;

    case 400 ... 500:
      demonstrateMF();
      break;

    default: 
      stopShepard();
      stopMF();
      break; 
  } 
}
