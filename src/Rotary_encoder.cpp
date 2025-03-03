/*
  Rotary_encoder.cpp - Library for using a rotary encoder.
  Created by Csermendy Bendeguz, February 7, 2025.
*/

#include "Arduino.h"
#include "Rotary_encoder.h"

Encoder::Encoder(int CLK_PIN, int DT_PIN)
{
  _CLK_PIN = CLK_PIN;
  _DT_PIN = DT_PIN;
  position = 0;
  lastCLK = LOW; // Initialize lastCLK
}



void Encoder::begin()
{
  pinMode(_CLK_PIN, INPUT_PULLUP);
  pinMode(_DT_PIN, INPUT_PULLUP);
    
}



long Encoder::read()
{
  int8_t direction = getDirection();
  if (direction == 1) {
    position = position + _scale;  // Clockwise
  } else if (direction == -1) {
    position = position - _scale;  // Counterclockwise
  }
  return position;
}



long Encoder::limitedRead(int Minval, int Maxval)
{
  position = constrain(read(), Minval, Maxval);
  return position;
}



long Encoder::getMotion() {
  int currentCLK = digitalRead(_CLK_PIN);
  if (currentCLK == LOW && lastCLK == HIGH && (millis() - lastDebounceTime > 5)) {
    lastDebounceTime = millis();
    lastCLK = currentCLK;
    return true;
  }
  lastCLK = currentCLK;
  return false;
}




int8_t Encoder::getDirection() {
  if (!getMotion()) return 0;  // No motion detected
  return digitalRead(_CLK_PIN) != digitalRead(_DT_PIN) ? 1 : -1;
}



long Encoder::setPosition(int pos)
{
  position = pos;
  if(position == pos) {
    return true;
  } else {
    return false;
  }
}



void Encoder::scale(int scale = 1)
{
  constrain(scale, 1, 100000);
  _scale = scale;
}
