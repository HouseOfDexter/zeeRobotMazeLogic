#ifndef zeeMotors_h
#define zeeMotors_h

#include "zeeExecute.h"
#include "zeeArduino.h"

/************************************************************************************/
/*Abstract class with interface to move the robot*/
class zeeMotors : public zeeExecute
{
public:
  zeeMotors(zeeArduino* arduino, unsigned long executeLength);
  virtual ~zeeMotors();

  virtual void EnableMotors() = 0;
  virtual void DisableMotors() = 0;

  virtual void Forward(unsigned int duration = 0) = 0;
  virtual void Backward(unsigned int duration = 0) = 0;
  virtual void TurnLeft(unsigned int duration = 0) = 0;
  virtual void TurnRight(unsigned int duration = 0) = 0;
  virtual void Coast(unsigned int duration = 0) = 0;
  virtual void Brake(unsigned int duration = 0) = 0;
  void SetEnabled(bool enabled);
  bool GetEnabled();
private:
  bool _enabled = false;

};

#endif

