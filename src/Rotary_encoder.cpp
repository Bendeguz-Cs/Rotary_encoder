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
  : next(nullptr), _CLK_PIN(CLK_PIN), _DT_PIN(DT_PIN), _scale(1), position(0),
    lastCLK(LOW), lastDebounceTime(0)
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

void ENCODER_ISR_ATTR Encoder::updateState() {
    bool clk = digitalRead(_CLK_PIN);
    bool dt  = digitalRead(_DT_PIN);

    if (clk == LOW && lastCLK == HIGH) {
        position += (dt ? _scale : -_scale) * _direction;
        _motion_state = true;
        feedbackMotion = true; // Set feedback flag
    } else {
        _motion_state = false;
    }

    lastCLK = clk;
}


void ENCODER_ISR_ATTR Encoder::globalEncoderISR() {
  for (Encoder* enc = encoderHead; enc != nullptr; enc = enc->next) {
    enc->updateState();
  }
}

bool Encoder::motion() {
  bool state;

  noInterrupts();
  state = feedbackMotion;

  if (feedbackMotion) {
    lastMotion = millis();   // update ONLY if motion happened
    feedbackMotion = false;
  }

  interrupts();

  return state;
}

bool Encoder::lastMotionSince(int noMotionTime) {
  noInterrupts();
  bool state = (millis() - lastMotion > noMotionTime);
  interrupts();
  return state;
}

long Encoder::read() {
  return position;
}

long Encoder::limitedRead(int Minval, int Maxval) {
  position = constrain(position, Minval, Maxval);
  return position;
}

long Encoder::setPosition(int pos) {
  position = pos;
  return position;
}

void Encoder::setDirection(bool direction) {
  noInterrupts();
  _direction = direction ? 1 : -1;
  interrupts();
}

void Encoder::scale(int scale) {
  _scale = constrain(scale, 1, 100000);
}
