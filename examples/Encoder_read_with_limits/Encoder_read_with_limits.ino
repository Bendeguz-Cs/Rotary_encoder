#include <Rotary_encoder.h>

//set the pins CLK and DIO
Encoder encoder(4, 5);

void setup() {
  Serial.begin(9600);
  //initialize
  encoder.begin();

  //set the limits
  encoder.setLimits(0, 10);
  //enable limiting
  encoder.limits();
}

void loop() {
  //print the value constrained between 0 and 10 to the Serial monitor
  Serial.println(encoder.read());
}
