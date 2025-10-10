/*
  Rotary_encoder.cpp - Library for using a rotary encoder.
  Created by Csermendy Bendeguz, February 7, 2025.
*/

#include "Arduino.h"
#include "Rotary_encoder.h"

#if defined(ARDUINO_ARCH_AVR)
  #include "PinChangeInterrupt.h"
  #warning "Set up PinChangeInterrupt library!"
#else
  #warning "This library uses Hardware interrupts on your currently selected processor"
#endif

// Global pointer to the linked list of encoders
Encoder* encoderHead = nullptr;

Encoder::Encoder(int CLK_PIN, int DT_PIN)
  : _CLK_PIN(CLK_PIN), _DT_PIN(DT_PIN), _scale(1), position(0),
    lastCLK(LOW), lastDebounceTime(0), next(nullptr)
{
  // Add this encoder to the linked list
  next = encoderHead;
  encoderHead = this;
}

void Encoder::begin() {
  pinMode(_CLK_PIN, INPUT_PULLUP);
  pinMode(_DT_PIN, INPUT_PULLUP);
  
  #if defined(ARDUINO_ARCH_AVR)
    // Attach global ISR to the CLK pin
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(_CLK_PIN), globalEncoderISR, CHANGE);
  #else
    // Attach global ISR to the CLK pin
    attachInterrupt(digitalPinToInterrupt(_CLK_PIN), globalEncoderISR, CHANGE);
  #endif
}

void Encoder::setDebounceTime(int debounce_time) {
  _debounce_time = debounce_time;
}

void Encoder::updateState() {
  bool newCLK = digitalRead(_CLK_PIN);
  bool newDT = digitalRead(_DT_PIN);

  // Debounce check (5ms)
  if ((millis() - lastDebounceTime) < _debounce_time) return;
  lastDebounceTime = millis();

  // Detect rotation on falling edge of CLK
  if (newCLK == LOW && lastCLK == HIGH) {
    if (newDT == HIGH) {
      position += _scale;  // Clockwise
    } else {
      position -= _scale;  // Counterclockwise
    }
    _motion_state = true;
  } else {
    _motion_state = false;
  }

  // Save last CLK state
  lastCLK = newCLK;
}

void Encoder::globalEncoderISR() {
  // Loop through all encoders and update their state
  for (Encoder* enc = encoderHead; enc != nullptr; enc = enc->next) {
    enc->updateState();
  }
}

bool Encoder::motion() {
  return _motion_state;
}

long Encoder::read() {
  return position;
}

long Encoder::limitedRead(int Minval, int Maxval) {
  if(position < Minval) {
    position = Minval;
  } else if(position > Maxval) {
    position = Maxval;
  }
  return position;
}

long Encoder::setPosition(int pos) {
  position = pos;
  return position;
}

void Encoder::scale(int scale) {
  _scale = constrain(scale, 1, 100000);
}
