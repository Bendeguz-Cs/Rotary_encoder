#include <Rotary_encoder.h>

//change the two defined pins for the two pins you use for your encoder
Encoder encoder(4, 5);

void setup() {
  Serial.begin(9600);
  //initialize the encoder
  encoder.begin();
  //set the debounce time to 2 milliseconds
  encoder.setDebounceTime(2);
}

void loop() {
  Serial.println(encoder.read());
}
