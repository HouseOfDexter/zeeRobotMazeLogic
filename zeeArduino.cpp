#include "zeeArduino.h"

#include "Arduino.h"

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

unsigned long zeeArduino::pulseIn(unsigned int pin, unsigned int state, unsigned long timeout)
{
   return Arduino_h::pulseIn(pin, state, timeout);
}

unsigned long zeeArduino::pulseInLong(unsigned int pin, unsigned int state, unsigned long timeout)
{
  return Arduino_h::pulseInLong(pin, state, timeout);
}

void zeeArduino::digitalWrite(unsigned int pin, unsigned int highlow)
{
  Arduino_h::digitalWrite(pin, highlow);
}

int zeeArduino::digitalRead(unsigned int pin)
{
  return Arduino_h::digitalRead(pin);
}

unsigned long zeeArduino::millis()
{
  return Arduino_h::millis();
}

void zeeArduino::pinMode(unsigned int pin, unsigned int direction)
{
  Arduino_h::pinMode((uint8_t)pin, (uint8_t)direction);
}
