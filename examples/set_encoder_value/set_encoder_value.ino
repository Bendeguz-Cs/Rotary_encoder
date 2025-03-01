#include <Rotary_encoder.h>

//change this to the pin you use for your button
const int buttonPin = 3;

//change the two defined pins for the two pins you use for your encoder
Encoder encoder(4, 5);

void setup() {
  Serial.begin(9600);
  encoder.begin();
  pinMode(buttonPin, INPUT_PULLUP);

}

void loop() {
  Serial.println(encoder.read());
  //sett the encoder position to 0 if the button has been pressed
  if(digitalRead(buttonPin) == LOW) {
    //set the encoder position to 0
    encoder.setPosition(0);
  }
}
