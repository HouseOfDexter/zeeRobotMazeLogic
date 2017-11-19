#include "zeeMotors.h"

/************************************************************************************/
zeeMotors::zeeMotors(zeeArduino * arduino, unsigned long executeLength)
  :zeeExecute(arduino, executeLength)
{
}

zeeMotors::~zeeMotors()
{
}



