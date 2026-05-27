#include <Rotary_encoder.h>

Encoder encoder(4, 5);

void setup() {
  encoder.LEDRing(6, 20);
  encoder.setLimits(0, 40);   // set the range
  encoder.limits();   // enable limit enforcement
  encoder.gradientBarPattern(0, 25, 0, 25, 0, 0);
  encoder.begin();
  Serial.begin(9600);
}

void loop() {
  Serial.println(encoder.read());
}
