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
  zeeOnOffLED(int ledPin1, int ledPin2, int ledPin3);
  ~zeeOnOffLED();

  void Set2LEDs(bool isOn);
  void Set2LEDs(bool isOn, int ledPin1, int ledPin2);
  void Set3LEDs(int ledOn);
  void Set3LEDs(int ledOn, int ledPin1, int ledPin2, int ledPin3);
private:
  int _ledPin1;
  int _ledPin2;
  int _ledPin3;
};

#endif