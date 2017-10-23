#ifndef zeeOnOffLED_h
#define zeeOnOffLED_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class zeeOnOffLED
{
public:
  zeeOnOffLED();
  zeeOnOffLED(int ledPin1, int ledPin2);
  ~zeeOnOffLED();

  void Set2LEDs(bool isOn);
  void Set2LEDs(bool isOn, int ledPin1, int ledPin2);
private:
  int _ledPin1;
  int _ledPin2;
};

#endif