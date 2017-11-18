#include "zeeArduino.h"
#include "zeeOnOffLED.h"
zeeOnOffLED::zeeOnOffLED()
{
}

zeeOnOffLED::zeeOnOffLED(zeeArduino* arduino, int ledPin1, int ledPin2)
  : zeeStateLed(arduino, unsigned int[][ledPin1],[ledPin2], 2)
{
  _arduino = arduino;
}


zeeOnOffLED::~zeeOnOffLED()
{
}

void zeeOnOffLED::StateOn(bool isOn)
{
  StateOn(int(bool))
}

