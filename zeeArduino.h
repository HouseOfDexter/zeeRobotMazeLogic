#ifndef zeeArduino_h
#define zeeArduino_h
#include "Arduino.h"

class zeeArduino
{
public:
  zeeArduino(unsigned long updateInterval);
  ~zeeArduino();

  virtual void delay(unsigned long us);
  virtual void delayMicroseconds(unsigned int us);
  virtual unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout=0);
  virtual unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout=0);

  virtual void digitalWrite(uint8_t pin, uint8_t highlow);

  unsigned long millis();

  unsigned long GetUpdateInterval() { return _updateInterval; }
private:
  unsigned long _updateInterval;
};

#endif

