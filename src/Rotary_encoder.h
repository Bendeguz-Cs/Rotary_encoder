/*
  Rotary_encoder.h - Library for using a rotary encoder.
  Created by Csermendy Bendeguz, February 7, 2025.
*/

#ifndef Rotary_encoder_h
#define Rotary_encoder_h

#include "Arduino.h"

#define USE_LED_RING  // Comment this out to disable LED ring support

#ifdef USE_LED_RING
  #include <Adafruit_NeoPixel.h>
  #warning "LED Ring enabled!"
#else
  #warning "LED Ring disabled! To enable, define USE_LED_RING before including Rotary_encoder.h"
#endif

#if defined(ARDUINO_ARCH_ESP32)
  #define ENCODER_ISR_ATTR IRAM_ATTR
#elif defined(ARDUINO_ARCH_ESP8266)
  #define ENCODER_ISR_ATTR ICACHE_RAM_ATTR
#else
  #define ENCODER_ISR_ATTR
#endif

#ifdef USE_LED_RING
  enum PatternMode {
    NO_PATTERN,
    POSITION_DOT_PATTERN,
    FILL_BAR_PATTERN,
    GRADIENT_BAR_PATTERN,
    FIXED_GRADIENT_BAR_PATTERN
  };
#endif

class Encoder {
  public:
    Encoder(int CLK_PIN, int DT_PIN);
    void begin();
    void LEDRing(int ledPin, uint16_t ledCount);
    #ifdef USE_LED_RING
      Adafruit_NeoPixel* getRing();
      void positionDotPattern(byte red, byte green, byte blue);
      void fillBarPattern(byte red, byte green, byte blue);
      void gradientBarPattern(byte startRed, byte startGreen, byte startBlue, byte endRed, byte endGreen, byte endBlue);
      void fixedGradientBarPattern(byte startRed, byte startGreen, byte startBlue, byte endRed, byte endGreen, byte endBlue);
      void noPattern();
    #endif
    void setDebounceTime(int debounce_time);
    bool motion();
    bool lastMotionSince(int noMotionTime); //returns if there hasn't been any motion for at least the amount of ms entered as the parameter
    long read();
    void limits();
    void noLimits();
    void setMin(long Minval);
    void setMax(long Maxval);
    void setLimits(long Minval, long Maxval);
    void setPosition(int pos);
    void setDirection(bool direction);
    void scale(int scale);

    // Linked list pointer for multiple encoders
    Encoder* next;

    // Static function for global ISR
    static void ENCODER_ISR_ATTR globalEncoderISR();

  private:
    int _CLK_PIN;
    int _DT_PIN;
    int _LED_PIN;
    int _LED_COUNT;
    bool useLEDRing = false;  //Flag to indicate if the LED ring is used by the current instance
    #ifdef USE_LED_RING
      Adafruit_NeoPixel* ring = nullptr; // per-instance NeoPixel
    #endif
    int _scale;
    bool _motion_state = false;
    volatile bool feedbackMotion = false;
    volatile int8_t _direction = 1; // -1 for CCW, +1 for CW
    volatile long lastMotion;
    volatile long position;
    volatile bool limitsEnabled = false;
    volatile long _MinLimit;
    volatile long _MaxLimit;
    volatile long lastPosition;
    volatile bool lastCLK = HIGH;
    volatile bool _lastDT = HIGH;
    int8_t _quadState = 0;
    int _debounce_time = 5; // Default debounce time in milliseconds
    volatile unsigned long lastDebounceTime = 0;

    #ifdef USE_LED_RING
      PatternMode _activePattern = NO_PATTERN;
      byte _patternRed = 255, _patternGreen = 255, _patternBlue = 255;
      // Gradient endpoints for GRADIENT_BAR_PATTERN
      byte _gradStartR = 255, _gradStartG = 0, _gradStartB = 0;
      byte _gradEndR = 0, _gradEndG = 255, _gradEndB = 0;
      void _updatePattern();
    #endif

    void ENCODER_ISR_ATTR updateState();  // Private function to update the state
};

// Global linked list of encoders
extern Encoder* encoderHead;

#endif
