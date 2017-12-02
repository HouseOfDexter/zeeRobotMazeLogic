#include "zee298DualHBridgeMotorDriver.h"
#include "zeeArduino.h"

zeeHBridgeMDparam::zeeHBridgeMDparam(unsigned int enablePin, unsigned int pin1, unsigned int pin2)
{
  EnablePin = enablePin;
  Pin1 = pin1;
  Pin2 = pin2;
}


zee298DualHBridgeMotorDriver::zee298DualHBridgeMotorDriver(zeeArduino* arduino, unsigned long executeLength, zeeHBridgeMDparam paramA, zeeHBridgeMDparam paramB)
  :zeeMotors(arduino, executeLength)
{
  _enableAPin = paramA.EnablePin;
  _pinA1 = paramA.Pin1;
  _pinA2 = paramA.Pin2;

  _enableBPin = paramB.EnablePin;
  _pinB1 = paramB.Pin1;
  _pinB2 = paramB.Pin2;

  arduino->PinMode(_enableAPin, OUTPUT);
  arduino->PinMode(_pinA1, OUTPUT);
  arduino->PinMode(_pinA2, OUTPUT);

  arduino->PinMode(_enableBPin, OUTPUT);
  arduino->PinMode(_pinB1, OUTPUT);
  arduino->PinMode(_pinB2, OUTPUT);
}


zee298DualHBridgeMotorDriver::~zee298DualHBridgeMotorDriver()
{
}

void zee298DualHBridgeMotorDriver::EnableMotors()
{
  MotorAOn();
  MotorBOn();
}

void zee298DualHBridgeMotorDriver::DisableMotors()
{
  MotorAOff();
  MotorBOff();
}

void zee298DualHBridgeMotorDriver::Forward(unsigned int duration = 0)
{
  MotorAForward();
  MotorBForward();
  Execute();
}

void zee298DualHBridgeMotorDriver::Backward(unsigned int duration = 0)
{
  MotorABackward();
  MotorBBackward();
  Execute();
}

void zee298DualHBridgeMotorDriver::TurnLeft(unsigned int duration = 0)
{
  MotorABackward();
  MotorBForward();
  Execute();
}

void zee298DualHBridgeMotorDriver::TurnRight(unsigned int duration = 0)
{
  MotorAForward();
  MotorBBackward();  
  Execute();
}

void zee298DualHBridgeMotorDriver::Coast(unsigned int duration = 0)
{
  MotorACoast();
  MotorBCoast();
  Execute();
}

void zee298DualHBridgeMotorDriver::Brake(unsigned int duration = 0)
{  
  MotorABrake();
  MotorBBrake();
  Execute();
}

void zee298DualHBridgeMotorDriver::DoExecute()
{
}

void zee298DualHBridgeMotorDriver::DoMotor(unsigned int pin, unsigned int direction)
{
  _arduino->DigitalWrite(pin, direction);
}

void zee298DualHBridgeMotorDriver::DoMotor(unsigned int pin1, unsigned int direction1, unsigned pin2, unsigned direction2)
{
  _arduino->DigitalWrite(pin1, direction1);
  _arduino->DigitalWrite(pin2, direction2);
}

void zee298DualHBridgeMotorDriver::MotorAOn()
{
  DoMotor(_enableAPin, HIGH);
}

void zee298DualHBridgeMotorDriver::MotorBOn()
{
  DoMotor(_enableBPin, HIGH);
}

void zee298DualHBridgeMotorDriver::MotorAOff()
{
  DoMotor(_enableAPin, LOW);
}

void zee298DualHBridgeMotorDriver::MotorBOff()
{
  DoMotor(_enableBPin, LOW);
}

void zee298DualHBridgeMotorDriver::MotorAForward()
{
  DoMotor(_pinA1, HIGH, _pinA2, LOW);
}

void zee298DualHBridgeMotorDriver::MotorBForward()
{
  DoMotor(_pinB1, HIGH, _pinB2, LOW);
}

void zee298DualHBridgeMotorDriver::MotorABackward()
{
  DoMotor(_pinA1, LOW, _pinA2, HIGH);
}

void zee298DualHBridgeMotorDriver::MotorBBackward()
{
  DoMotor(_pinB1, LOW, _pinB2, HIGH);
}

void zee298DualHBridgeMotorDriver::MotorACoast()
{
  DoMotor(_pinA1, LOW, _pinA2, LOW);
}

void zee298DualHBridgeMotorDriver::MotorBCoast()
{
  DoMotor(_pinB1, LOW, _pinB2, LOW);
}

void zee298DualHBridgeMotorDriver::MotorABrake()
{
  DoMotor(_pinA1, HIGH, _pinA2, HIGH);
}

void zee298DualHBridgeMotorDriver::MotorBBrake()
{
  DoMotor(_pinB1, HIGH, _pinB2, HIGH);
}

