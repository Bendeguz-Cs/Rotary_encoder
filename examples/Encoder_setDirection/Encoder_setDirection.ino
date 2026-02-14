#include <Rotary_encoder.h>

//change the two defined pins for the two pins you use for your encoder
Encoder encoder(25, 26);

void setup() {
  Serial.begin(9600);
  //initialize the encoder
  encoder.begin();

}

void loop() {
  long encoderPos = encoder.read();
  //print the read value of the encoder
  Serial.println(encoderPos);

  if(encoderPos >= 20) {
    encoder.setDirection(false);  //input is a boolean, default direction is true, the real world direction depends on you hardware connection
  } else if(encoderPos <= 0) {
    encoder.setDirection(true);
  }
}
