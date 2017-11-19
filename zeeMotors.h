#ifndef zeeMotors_h
#define zeeMotors_h

#include "zeeExecute.h"


/************************************************************************************/

class zeeMotors : public zeeExecute
{
public:
  zeeMotors(zeeArduino* arduino, unsigned long executeLength);
  virtual ~zeeMotors();

  virtual void EnableMotors() = 0;
  virtual void DisableMotors() = 0;

  virtual void Forward() = 0;
  virtual void Backward() = 0;
  virtual void TurnLeft() = 0;
  virtual void TurnRight() = 0;
  virtual void Coast() = 0;
  virtual void Brake() = 0;
};

#endif
