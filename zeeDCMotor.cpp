#include "zeeDCMotor.h"

zeeDCMotor::zeeDCMotor()
{
}

zeeDCMotor::~zeeDCMotor()
{
}

zeeDCMotor::zeeDCMotor(unsigned int Pin)
{
}

/************************************************************************************/
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

/************************************************************************************/
zeeMotors::zeeMotors(zeeDCMotor * motorFL, zeeDCMotor * motorFR, zeeDCMotor * motorRL, zeeDCMotor * motorRR)
  :_motorFL(motorFL), _motorFR(motorFR), _motorRL(motorRL), _motorRR(motorRR)
{
}

zeeDCMotor * zeeMotors::GetMotorFL()
{
  return _motorFL;
}

zeeDCMotor * zeeMotors::GetMotorFR()
{
  return _motorFR;
}

zeeDCMotor * zeeMotors::GetMotorRL()
{
  return _motorRL;
}

zeeDCMotor * zeeMotors::GetMotorRR()
{
  return _motorRR;
}