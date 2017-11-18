#include "zeeArduino.h"

zeeArduino::zeeArduino(unsigned int updateInterval, unsigned int intervalRunTime)
  :_updateInterval(updateInterval), _intervalRunTime(intervalRunTime)
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

int zeeArduino::digitalRead(uint8_t pin)
{
  return Arduino_h::digitalRead(pin);
}

unsigned long zeeArduino::millis()
{
  return Arduino_h::millis();
}

void zeeArduino::pinMode(byte pin, byte direction)
{
  Arduino_h::pinMode(pin, direction);
}
