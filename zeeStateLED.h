#ifndef zeeStateLED_h
#define zeeStateLED_h
#include "zeeArduino.h"
class zeeStateLED
{
public:
  zeeStateLED(zeeArduino* arduino, unsigned int ledPins[], int length);
  ~zeeStateLED();
  virtual void StateOn(unsigned int index);
  void AllOff();
private:
  zeeArduino* _arduino;
  unsigned int _numberStates;
  unsigned int _ledPins[];
};
#endif
