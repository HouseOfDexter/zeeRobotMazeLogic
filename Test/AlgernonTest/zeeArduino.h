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

  virtual void Delay(unsigned long us);
  virtual void DelayMicroseconds(unsigned int us);
  virtual unsigned long PulseIn(unsigned int pin, unsigned int state, unsigned long timeout=0);
  virtual unsigned long PulseInLong(unsigned int pin, unsigned int state, unsigned long timeout=0);

  virtual void DigitalWrite(unsigned int pin, unsigned int highlow);
  virtual int DigitalRead(unsigned int pin);

  virtual unsigned long Millis();

  unsigned int GetUpdateInterval() { return _updateInterval; }
  unsigned int GetIntervalRunTime() { return _intervalRunTime; }

  void PinMode(unsigned int pin, unsigned int direction);

  void Println(const String value);
  void Print(long value);
  void Print(unsigned long value);
  void Print(bool value);

private:
  unsigned int _updateInterval;
  unsigned int _intervalRunTime;

  
};

#endif


