#include "zeeLineReader.h"
#include "Arduino.h"

zeeLineReader::zeeLineReader(zeeArduino * arduino, unsigned long executeLength, unsigned int lPin, unsigned int mPin, unsigned int rPin)
  :zeeExecute(arduino, executeLength)
{
  _rPin = rPin;
  _mPin = mPin;
  _lPin = lPin;

//  pinMode(rPin, INPUT);
//  pinMode(mPin, INPUT);
//  pinMode(lPin, INPUT);
}

zeeLineReader::~zeeLineReader()
{
}

bool zeeLineReader::DetectRight()
{
  return _detectRight;
}

bool zeeLineReader::DetectLeft()
{
  return _detectLeft;
}

bool zeeLineReader::DetectMiddle()
{
  return _detectMiddle;
}

void zeeLineReader::DoExecute(bool bypassWait)
{
//  _detectRight = !digitalRead(_rPin);
//  _detectLeft = !digitalRead(_lPin);
//  _detectMiddle = !digitalRead(_mPin);
}

