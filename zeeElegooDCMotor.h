#pragma once
#include "zeeDCMotor.h"
#include "Elegoo_DCMotor.h"
class zeeElegooDCMotor :
  public zeeDCMotor
{
public:
  zeeElegooDCMotor::zeeElegooDCMotor(unsigned int pin, Elegoo_DCMotor * dcMotor);
  zeeElegooDCMotor();
  ~zeeElegooDCMotor();
  void Execute();
  void Setup(int speed);
private:
  unsigned int _pin;
  int _speed;
  Elegoo_DCMotor * _dcMotor;
};
