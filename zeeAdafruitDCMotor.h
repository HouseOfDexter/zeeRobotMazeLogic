#pragma once
#include "zeeDCMotor.h"
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
