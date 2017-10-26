#ifndef zeeElegooDCMotor_h
#define zeeElegooDCMotor_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "zeeDCMotor.h"
#include "Elegoo_DCMotor.h"

class zeeElegooDCMotor :
  public zeeDCMotor
{
public:
  zeeElegooDCMotor::zeeElegooDCMotor(unsigned int pin, Elegoo_DCMotor * dcMotor);
  ~zeeElegooDCMotor();
  void Execute();
  void Setup(int speed);
private:
  unsigned int _pin;
  int _speed;
  Elegoo_DCMotor * _dcMotor;
};

#endif
