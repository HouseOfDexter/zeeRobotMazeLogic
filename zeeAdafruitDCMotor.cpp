#include "zeeAdafruitDCMotor.h"

zeeAdafruitDCMotor::zeeAdafruitDCMotor(zeeArduino* arduino, unsigned long executeLength, unsigned int pin, Adafruit_DCMotor * dcMotor)
  : zeeDCMotor(arduino, executeLength, pin)
{
  _dcMotor = dcMotor;
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