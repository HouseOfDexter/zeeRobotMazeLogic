#include "zeeAdafruitDCMotor.h"

zeeAdafruitDCMotor::zeeAdafruitDCMotor(unsigned int pin, Adafruit_DCMotor * dcMotor)
  : _pin(pin), _dcMotor(dcMotor)
{
}

zeeAdafruitDCMotor::~zeeAdafruitDCMotor()
{
}

void zeeAdafruitDCMotor::Execute()
{
}

void zeeAdafruitDCMotor::Setup(int speed)
{
}