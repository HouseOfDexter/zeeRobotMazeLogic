#include "zeeOnOffLED.h"
zeeOnOffLED::zeeOnOffLED()
{
}

zeeOnOffLED::zeeOnOffLED(int ledPin1, int ledPin2)
  :_ledPin1(ledPin1), _ledPin2(ledPin2)
{
}

zeeOnOffLED::zeeOnOffLED(int ledPin1, int ledPin2, int ledPin3)
  : _ledPin1(ledPin1), _ledPin2(ledPin2), _ledPin3(ledPin3)
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

void zeeOnOffLED::Set3LEDs(int ledOn)
{
  Set3LEDs(ledOn, _ledPin1, _ledPin2, _ledPin3);
}

void zeeOnOffLED::Set3LEDs(int ledOn, int ledPin1, int ledPin2, int ledPin3)
{
  /*One LED goes on, the other goes off*/
  _ledPin1 = ledPin1;
  _ledPin2 = ledPin2;
  if (ledOn == 1)
  {
    digitalWrite(ledPin1, HIGH);
    digitalWrite(ledPin2, LOW);
    digitalWrite(ledPin3, LOW);
  }
  else
    if (ledOn == 2)
    {
      digitalWrite(ledPin1, LOW);
      digitalWrite(ledPin2, HIGH);
      digitalWrite(ledPin3, LOW);
    }
    else
      if (ledOn == 3)
      {
        digitalWrite(ledPin1, LOW);
        digitalWrite(ledPin2, LOW);
        digitalWrite(ledPin3, HIGH);
      }
}