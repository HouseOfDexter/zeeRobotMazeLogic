#include "zeeLineReader.h"


zeeLineReader::zeeLineReader(zeeArduino * arduino, unsigned long executeLength, unsigned int rPin, unsigned int mPin, unsigned int lPin)
  :zeeExecute(arduino, executeLength)
{
  _rPin = rPin;
  _mPin = mPin;
  _lPin = lPin;
  arduino->pinMode(rPin, INPUT);
  arduino->pinMode(mPin, INPUT);
  arduino->pinMode(lPin, INPUT);
}

zeeLineReader::~zeeLineReader()
{
}

bool zeeLineReader::DetectRight()
{
  return _arduino->digitalRead(_rPin);
}

bool zeeLineReader::DetectLeft()
{
  return _arduino->digitalRead(_lPin);
}

bool zeeLineReader::DetectMiddle()
{
  return _arduino->digitalRead(_mPin);
}

void zeeLineReader::DoExecute()
{
}

