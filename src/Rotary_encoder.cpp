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
  int currentCLK = digitalRead(_CLK_PIN);
  int currentDT = digitalRead(_DT_PIN);

  // Debouncing
  if ((currentCLK != lastCLK) && (millis() - lastDebounceTime > 5)) {
    if (currentCLK == LOW) {
      if (currentDT == HIGH) {
        position++;
      } else {
        position--;
      }
    }
    lastDebounceTime = millis();
  }

  lastCLK = currentCLK;
  return position;
}



long Encoder::limitedRead(int Minval, int Maxval)
{
  position = constrain(read(), Minval, Maxval);
  return position;
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
