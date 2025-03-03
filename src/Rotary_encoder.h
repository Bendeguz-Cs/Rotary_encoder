/*
  Rotary_encoder.h - Library for using a rotary encoder.
  Created by Csermendy Bendeguz, February 7, 2025.
*/

#ifndef Rotary_encoder_h
#define Rotary_encoder_h

#include "Arduino.h"

class Encoder
{
  public:
    Encoder(int CLK_PIN, int DT_PIN);
    void begin();
    long read();
    long limitedRead(int Minval, int Maxval);
    long getMotion();
    int8_t getDirection();
    long setPosition(int pos);
    void scale(int scale);

  private:
    int _CLK_PIN;
    int _DT_PIN;
    int _scale = 1;
    volatile long position = 0;
    volatile int lastCLK = HIGH;
    unsigned long lastDebounceTime = 0;
    
};

#endif

