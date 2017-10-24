#ifndef zeeDCMotor_h
#define zeeDCMotor_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_MotorShield.h>
#include "zeeExecute.h"

class zeeDCMotor : public zeeExecute
{
public:
  zeeDCMotor();
  zeeDCMotor(unsigned int Pin);
  ~zeeDCMotor();

  virtual void Setup(int speed) = 0;
};

/************************************************************************************/
/*We create a Fascade around Adafruit Library*/
class zeeAdafruitDCMotor : public zeeDCMotor
{
public:
  zeeAdafruitDCMotor(unsigned int pin, Adafruit_DCMotor* dcMotor);
  ~zeeAdafruitDCMotor();
  void Execute();
  void Setup(int speed);
private:
  unsigned int _pin;
  int _speed;
  Adafruit_DCMotor * _dcMotor;
};

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
