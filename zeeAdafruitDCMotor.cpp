#include "zeeAdafruitDCMotor.h"

zeeAdafruitDCMparam::zeeAdafruitDCMparam(unsigned int pin, Adafruit_DCMotor * dcMotor)
{
  Pin = pin;
  DcMotor = dcMotor;
}

zeeAdafruitDCMparam::~zeeAdafruitDCMparam()
{
}

zeeAdafruitDCMotor::zeeAdafruitDCMotor(zeeArduino* arduino, unsigned long executeLength, zeeAdafruitDCMparam param)
  : zeeDCMotor(arduino, executeLength)
{
  _dcMotor = param.DcMotor;
  _pin = param.Pin;
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

