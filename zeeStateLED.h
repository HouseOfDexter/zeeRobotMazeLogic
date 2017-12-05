#ifndef zeeStateLED_h
#define zeeStateLED_h
#include "zeeArduino.h"
class zeeStateLED
{
public:
  zeeStateLED(zeeArduino* arduino, unsigned int ledPins[], int length);
  virtual ~zeeStateLED();
  virtual void StateOn(unsigned int index);
  void AllOff();
private:
  zeeArduino* _arduino;
  unsigned int _numberStates = 0;
  unsigned int _ledPins[];
};
#endif


