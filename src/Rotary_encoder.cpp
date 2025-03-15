/*
  Rotary_encoder.cpp - Library for using a rotary encoder.
  Created by Csermendy Bendeguz, February 7, 2025.
*/

#include "Arduino.h"
#include "Rotary_encoder.h"

#if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_ESP8266)
  #include "PinChangeInterrupt.h"
  #warning "Set up PinChangeInterrupt library!"
#elif defined(ARDUINO_ARCH_SAM) || defined(ARDUINO_ARCH_SAMD)
  #warning "Set up attachInterrupt library!"
#else
  #error "This library only works on AVR, SAMD and ESP architectures!"
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
  
  #if defined(ARDUINO_ARCH_AVR) || defined(ARDUINO_ARCH_ESP8266)
    // Attach global ISR to the CLK pin
    attachPinChangeInterrupt(digitalPinToPinChangeInterrupt(_CLK_PIN), globalEncoderISR, CHANGE);
  #elif defined(ARDUINO_ARCH_SAMD) || defined(ARDUINO_ARCH_ESP32)
    // Attach global ISR to the CLK pin
    attachInterrupt(digitalPinToInterrupt(_CLK_PIN), globalEncoderISR, CHANGE);
  #endif
}

void Encoder::updateState() {
  bool newCLK = digitalRead(_CLK_PIN);
  bool newDT = digitalRead(_DT_PIN);

  // Debounce check (5ms)
  if ((millis() - lastDebounceTime) < 5) return;
  lastDebounceTime = millis();

  // Detect rotation on falling edge of CLK
  if (newCLK == LOW && lastCLK == HIGH) {
    if (newDT == HIGH) {
      position += _scale;  // Clockwise
    } else {
      position -= _scale;  // Counterclockwise
    }
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

long Encoder::read() {
  return position;
}

long Encoder::limitedRead(int Minval, int Maxval) {
  return constrain(read(), Minval, Maxval);
}

long Encoder::setPosition(int pos) {
  position = pos;
  return position;
}

void Encoder::scale(int scale) {
  _scale = constrain(scale, 1, 100000);
}
