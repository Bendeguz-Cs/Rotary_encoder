#include <Rotary_encoder.h>

//change the two defined pins for the two pins you use for your encoder
Encoder encoder(4, 5);

void setup() {
  Serial.begin(9600);
  //initialize the encoder
  encoder.begin();
}

void loop() {
  if (encoder.motion()) {  //check for motion - only print when there is a change in position
    //print the read value of the encoder
    Serial.println(encoder.read());
    delay(100); //delay to only print output once
  }
}
