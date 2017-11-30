#ifndef zeeArduino_h
#define zeeArduino_h

#include "WString.h"

#define HIGH 0x1
#define LOW  0x0

#define INPUT 0x0
#define OUTPUT 0x1
#define INPUT_PULLUP 0x2

class zeeArduino
{
/*This class is a fascade around Arduino.h, allowing us to unit test around the Sensors and Motors*/
public:
  zeeArduino(unsigned int updateInterval, unsigned int intervalRunTime);
  virtual ~zeeArduino();

  virtual void delay(unsigned long us);
  virtual void delayMicroseconds(unsigned int us);
  virtual unsigned long pulseIn(unsigned int pin, unsigned int state, unsigned long timeout=0);
  virtual unsigned long pulseInLong(unsigned int pin, unsigned int state, unsigned long timeout=0);

  virtual void digitalWrite(unsigned int pin, unsigned int highlow);
  virtual int digitalRead(unsigned int pin);

  virtual unsigned long millis();

  unsigned int GetUpdateInterval() { return _updateInterval; }
  unsigned int GetIntervalRunTime() { return _intervalRunTime; }

  void pinMode(unsigned int pin, unsigned int direction);

  void println(String value);
  void print(long value);
  void print(bool value);

private:
  unsigned int _updateInterval;
  unsigned int _intervalRunTime;

  
};

#endif

