#include "zeeOnOffLED.h"
zeeOnOffLED::zeeOnOffLED()
{
}

zeeOnOffLED::zeeOnOffLED(int ledPin1, int ledPin2)
  :_ledPin1(ledPin1), _ledPin2(ledPin2)
{
}

zeeOnOffLED::~zeeOnOffLED()
{
}

void zeeOnOffLED::Set2LEDs(bool isOn)
{
  Set2LEDs(isOn, _ledPin1, _ledPin2);
}

void zeeOnOffLED::Set2LEDs(bool isOn, int ledPin1, int ledPin2)
{
  /*One LED goes on, the other goes off*/
  _ledPin1 = ledPin1;
  _ledPin2 = ledPin2;
  if (isOn == true)
  {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
  }
  else
  {
    digitalWrite(ledPin2, HIGH);
    digitalWrite(ledPin1, LOW);
  }
}