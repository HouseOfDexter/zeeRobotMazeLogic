#ifndef zeeDCMotor_h
#define zeeDCMotor_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif
#include "zeeExecute.h"

class zeeDCMotor : public zeeExecute
{
public:
  zeeDCMotor(zeeArduino* arduino, unsigned long executeLength, unsigned int pin);
  ~zeeDCMotor();

  virtual void Setup(int speed) = 0;
private:
  unsigned int _pin;
};

/************************************************************************************/

class zeeMotors
{
public:
  zeeMotors(zeeDCMotor* motorFL, zeeDCMotor* motorFR, zeeDCMotor* motorRL, zeeDCMotor* motorRR);
  zeeDCMotor* GetMotorFL();
  zeeDCMotor* GetMotorFR();
  zeeDCMotor* GetMotorRL();
  zeeDCMotor* GetMotorRR();
private:
  zeeDCMotor* _motorFL;
  zeeDCMotor* _motorFR;
  zeeDCMotor* _motorRL;
  zeeDCMotor* _motorRR;
};

#endif
