#include "zeeArduino.h"

#include "Arduino.h"
#include "HardwareSerial.h"
#include "stdint.h"

zeeArduino::zeeArduino(unsigned int updateInterval, unsigned int intervalRunTime)
  :_updateInterval(updateInterval), _intervalRunTime(intervalRunTime)
{
}

zeeArduino::~zeeArduino()
{
}

void zeeArduino::Delay(unsigned long us)
{
  delay(us);
}

void zeeArduino::DelayMicroseconds(unsigned int us)
{
  delayMicroseconds(us);
}

unsigned long zeeArduino::PulseIn(unsigned int pin, unsigned int state, unsigned long timeout)
{
   return pulseIn((uint8_t)pin, (uint8_t)state, timeout);
}

unsigned long zeeArduino::PulseInLong(unsigned int pin, unsigned int state, unsigned long timeout)
{
  return pulseInLong((uint8_t)pin, (uint8_t)state, timeout);
}

void zeeArduino::DigitalWrite(unsigned int pin, unsigned int highlow)
{
  digitalWrite((uint8_t) pin, (uint8_t) highlow);
}

int zeeArduino::DigitalRead(unsigned int pin)
{
  return digitalRead((uint8_t) pin);
}

unsigned long zeeArduino::Millis()
{
  return millis();
}

void zeeArduino::PinMode(unsigned int pin, unsigned int direction)
{
  pinMode((uint8_t)pin, (uint8_t)direction);
}

void zeeArduino::Println(const String value)
{
  Serial.println(value);
}

void zeeArduino::Print(long value)
{ 
  Serial.print(value);
}

void zeeArduino::Print(unsigned long value)
{
  Serial.print(value);
}

void zeeArduino::Print(bool value)
{
  Serial.print(value);
}

