#include "zeeArduino.h"
#include "zeeOnOffLED.h"
zeeOnOffLED::zeeOnOffLED()
{
}

zeeOnOffLED::zeeOnOffLED(zeeArduino* arduino, int ledPin1, int ledPin2)
  :_arduino(arduino), _ledPin1(ledPin1), _ledPin2(ledPin2)
{
}

zeeOnOffLED::zeeOnOffLED(zeeArduino* arduino, int ledPin1, int ledPin2, int ledPin3)
  : _arduino(arduino), _ledPin1(ledPin1), _ledPin2(ledPin2), _ledPin3(ledPin3)
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
    _arduino->digitalWrite(ledPin1, HIGH);
    _arduino->digitalWrite(ledPin2, LOW);
  }
  else
  {
    _arduino->digitalWrite(ledPin2, HIGH);
    _arduino->digitalWrite(ledPin1, LOW);
  }
}

void zeeOnOffLED::Set3LEDs(int ledOn)
{
  Set3LEDs(ledOn, _ledPin1, _ledPin2, _ledPin3);
}

void zeeOnOffLED::Set3LEDs(int ledOn, int ledPin1, int ledPin2, int ledPin3)
{
  /*One LED goes on, the others go off*/
  _ledPin1 = ledPin1;
  _ledPin2 = ledPin2;
  _ledPin3 = ledPin3;
  if (ledOn == 1)
  {
    _arduino->digitalWrite(ledPin1, HIGH);
    _arduino->digitalWrite(ledPin2, LOW);
    _arduino->digitalWrite(ledPin3, LOW);
  }
  else
    if (ledOn == 2)
    {
      _arduino->digitalWrite(ledPin1, LOW);
      _arduino->digitalWrite(ledPin2, HIGH);
      _arduino->digitalWrite(ledPin3, LOW);
    }
    else
      if (ledOn == 3)
      {
        _arduino->digitalWrite(ledPin1, LOW);
        _arduino->digitalWrite(ledPin2, LOW);
        _arduino->digitalWrite(ledPin3, HIGH);
      }
}