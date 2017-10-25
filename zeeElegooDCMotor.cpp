#include "zeeElegooDCMotor.h"

zeeElegooDCMotor::zeeElegooDCMotor()
{
}

zeeElegooDCMotor::~zeeElegooDCMotor()
{
}

zeeElegooDCMotor::zeeElegooDCMotor(unsigned int pin, Elegoo_DCMotor * dcMotor)
  : _pin(pin), _dcMotor(dcMotor)
{
}

zeeElegooDCMotor::~zeeElegooDCMotor()
{
}

void zeeElegooDCMotor::Execute()
{
}

void zeeElegooDCMotor::Setup(int speed)
{
}