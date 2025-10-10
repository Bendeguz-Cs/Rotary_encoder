/*
  Rotary_encoder.h - Library for using a rotary encoder.
  Created by Csermendy Bendeguz, February 7, 2025.
*/

#ifndef Rotary_encoder_h
#define Rotary_encoder_h

#include "Arduino.h"

class Encoder {
  public:
    Encoder(int CLK_PIN, int DT_PIN);
    void begin();
    void setDebounceTime(int debounce_time);
    bool motion();
    long read();
    long limitedRead(int Minval, int Maxval);
    long setPosition(int pos);
    void scale(int scale);

    // Linked list pointer for multiple encoders
    Encoder* next;

    // Static function for global ISR
    static void globalEncoderISR();

  private:
    int _CLK_PIN;
    int _DT_PIN;
    int _scale;
    bool _motion_state = false;
    volatile long position;
    volatile bool lastCLK;
    int _debounce_time = 5;
    volatile unsigned long lastDebounceTime;

    void updateState();  // Private function to update the state
};

// Global linked list of encoders
extern Encoder* encoderHead;

#endif
