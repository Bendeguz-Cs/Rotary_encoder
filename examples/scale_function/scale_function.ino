#include <Rotary_encoder.h>

//change the two defined pins for the two pins you use for your encoder
Encoder encoder(4, 5);

void setup() {
  Serial.begin(9600);
  //initialize the encoder
  encoder.begin();
  //set the scale - the library will count by increments of 5 instead of one
  encoder.scale(5); //set this number as you wish

}

void loop() {
  //print the read value of the encoder
  Serial.println(encoder.read());
}
