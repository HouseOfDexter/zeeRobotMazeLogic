#include "zeeLineReader.h"


zeeLineReader::zeeLineReader(zeeArduino * arduino, unsigned long executeLength, unsigned int rPin, unsigned int mPin, unsigned int lPin)
  :zeeExecute(arduino, executeLength)
{
  _rPin = rPin;
  _mPin = mPin;
  _lPin = lPin;
  arduino->PinMode(rPin, INPUT);
  arduino->PinMode(mPin, INPUT);
  arduino->PinMode(lPin, INPUT);
}

zeeLineReader::~zeeLineReader()
{
}

bool zeeLineReader::DetectRight()
{
  return _arduino->DigitalRead(_rPin);
}

bool zeeLineReader::DetectLeft()
{
  return _arduino->DigitalRead(_lPin);
}

bool zeeLineReader::DetectMiddle()
{
  return _arduino->DigitalRead(_mPin);
}

void zeeLineReader::DoExecute()
{
}

