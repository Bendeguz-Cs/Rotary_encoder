/*
  Rotary_encoder.h - Library for using a rotary encoder.
  Created by Csermendy Bendeguz, February 7, 2025.
*/

#ifndef Rotary_encoder_h
#define Rotary_encoder_h

#include "Arduino.h"

#if defined(ARDUINO_ARCH_ESP32)
  #define ENCODER_ISR_ATTR IRAM_ATTR
#elif defined(ARDUINO_ARCH_ESP8266)
  #define ENCODER_ISR_ATTR ICACHE_RAM_ATTR
#else
  #define ENCODER_ISR_ATTR
#endif

class Encoder {
  public:
    Encoder(int CLK_PIN, int DT_PIN);
    void begin();
    void setDebounceTime(int debounce_time);
    bool motion();
    long read();
    long limitedRead(int Minval, int Maxval);
    long setPosition(int pos);
    void setDirection(bool direction);
    void scale(int scale);

    // Linked list pointer for multiple encoders
    Encoder* next;

    // Static function for global ISR
    static void ENCODER_ISR_ATTR globalEncoderISR();

  private:
    int _CLK_PIN;
    int _DT_PIN;
    int _scale;
    bool _motion_state = false;
    volatile bool feedbackMotion = false;
    volatile int8_t _direction = 1; // -1 for CCW, +1 for CW
    volatile long position;
    volatile long lastPosition;
    volatile bool lastCLK;
    int _debounce_time = 5;
    volatile unsigned long lastDebounceTime;

    void ENCODER_ISR_ATTR updateState();  // Private function to update the state
};

// Global linked list of encoders
extern Encoder* encoderHead;

#endif
