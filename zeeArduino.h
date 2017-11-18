#ifndef zeeArduino_h
#define zeeArduino_h
#include "Arduino.h"

class zeeArduino
{
/*This class is a fascade around Arduino.h, allowing us to unit test around the Sensors and Motors*/
public:
  zeeArduino(unsigned int updateInterval, unsigned int intervalRunTime);
  ~zeeArduino();

  virtual void delay(unsigned long us);
  virtual void delayMicroseconds(unsigned int us);
  virtual unsigned long pulseIn(uint8_t pin, uint8_t state, unsigned long timeout=0);
  virtual unsigned long pulseInLong(uint8_t pin, uint8_t state, unsigned long timeout=0);

  virtual void digitalWrite(uint8_t pin, uint8_t highlow);
  virtual int digitalRead(uint8_t pin);

  virtual unsigned long millis();

  unsigned int GetUpdateInterval() { return _updateInterval; }
  unsigned int GetIntervalRunTime() { return _intervalRunTime; }

  void pinMode(byte pin, byte direction);
private:
  unsigned int _updateInterval;
  unsigned int _intervalRunTime;

  
};

#endif

