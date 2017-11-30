#include "zeeMotors.h"

/************************************************************************************/
zeeMotors::zeeMotors(zeeArduino * arduino, unsigned long executeLength)
  :zeeExecute(arduino, executeLength)
{
}

zeeMotors::~zeeMotors()
{
}

void zeeMotors::SetEnabled(bool enabled)
{
  _enabled = enabled;
}

bool zeeMotors::GetEnabled() 
{
  return _enabled;
}



