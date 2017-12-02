#include "zeeStateLED.h"



zeeStateLED::zeeStateLED(zeeArduino* arduino, unsigned int ledPins[], int length)
{ 
  _arduino = arduino;
  _numberStates = length;
  for (int pin = 0; pin < _numberStates; pin++) 
  {
    _ledPins[pin] = ledPins[pin];
  }
}

zeeStateLED::~zeeStateLED()
{
}

void zeeStateLED::StateOn(unsigned int index)
{
  AllOff();
  if (index < _numberStates)
    _arduino->DigitalWrite(_ledPins[index], HIGH);
}

void zeeStateLED::AllOff()
{
  for (int pin = 0; pin < _numberStates; pin++)
  {
    _arduino->DigitalWrite(_ledPins[pin], LOW);    
  }
}

