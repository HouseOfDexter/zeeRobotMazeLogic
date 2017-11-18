#ifndef zeeOnOffLED_h
#define zeeOnOffLED_h
#include "zeeArduino.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class zeeOnOffLED: public zeeStateLED
{
public:
  zeeOnOffLED();  
  zeeOnOffLED(zeeArduino* arduino, int ledPin1, int ledPin2);  
  ~zeeOnOffLED();

  override void StateOn(bool isOn);  
private:
  zeeArduino* _arduino;
  int _ledPin1;
  int _ledPin2;
  int _ledPin3;
  bool _isOn;
};

#endif