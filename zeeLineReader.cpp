#include "zeeLineReader.h"


zeeLineReader::zeeLineReader(zeeArduino * arduino, unsigned long executeLength, unsigned int pin)
  :zeeExecute(arduino, executeLength)
{
  _pin = pin;
}

zeeLineReader::~zeeLineReader()
{
}

bool zeeLineReader::DetectLine()
{
  return false;
}

void zeeLineReader::DoExecute()
{
}
