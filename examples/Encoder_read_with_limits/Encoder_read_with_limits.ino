#include <Rotary_encoder.h>

Encoder encoder(4, 5);

void setup() {
  Serial.begin(9600);
  encoder.begin();

}

void loop() {
  Serial.println(encoder.limitedRead());
}
