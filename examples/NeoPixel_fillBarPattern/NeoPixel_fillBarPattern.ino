#include <Rotary_encoder.h>

Encoder encoder(4, 5);

void setup() {
  //initialize the NeoPixels on pin 6 with a 20 piece ring
  encoder.LEDRing(6, 20);
  encoder.setLimits(0, 40);
  encoder.limits();   // enable limit enforcement
  encoder.fillBarPattern(0, 25, 0);
  encoder.begin();
}

void loop() {
  Serial.println(encoder.read());
}
