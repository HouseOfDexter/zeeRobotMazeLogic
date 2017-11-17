#include "zeeElegooDCMotor.h"

zeeElegooDCMotor::~zeeElegooDCMotor()
{
}

zeeElegooDCMotor::zeeElegooDCMotor(zeeArduino* arduino, unsigned long executeLength, unsigned int pin, Elegoo_DCMotor * dcMotor)
  : zeeDCMotor(arduino, executeLength, pin)
{
  _dcMotor = dcMotor;
}

void zeeElegooDCMotor::DoExecute()
{
}

void zeeElegooDCMotor::Setup(int speed)
{
}