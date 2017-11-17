#include "zeeArduino.h"

zeeArduino::zeeArduino(unsigned long updateInterval)
  :_updateInterval(updateInterval)
{
}

zeeArduino::~zeeArduino()
{
}

void zeeArduino::delay(unsigned long us)
{
  Arduino_h::delay(us);
}

void zeeArduino::delayMicroseconds(unsigned int us)
{
  Arduino_h::delayMicroseconds(us);
}

unsigned long zeeArduino::pulseIn(uint8_t pin, uint8_t state, unsigned long timeout)
{
   return Arduino_h::pulseIn(pin, state, timeout);
}

unsigned long zeeArduino::pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout)
{
  return Arduino_h::pulseInLong(pin, state, timeout);
}

void zeeArduino::digitalWrite(uint8_t pin, uint8_t highlow)
{
  Arduino_h::digitalWrite(pin, highlow);
}

unsigned long zeeArduino::millis()
{
  return Arduino_h::millis();
}
