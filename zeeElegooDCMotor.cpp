#include "zeeElegooDCMotor.h"
#include "Arduino.h"

zeeElegooDCMparam::zeeElegooDCMparam(unsigned int in1Pin, unsigned int in2Pin, unsigned int enaPin, Elegoo_DCMotor * dcMotor)
{
}

zeeElegooDCMparam::~zeeElegooDCMparam()
{
}

zeeElegooDCMotor::~zeeElegooDCMotor()
{
}

zeeElegooDCMotor::zeeElegooDCMotor(zeeArduino* arduino, unsigned long executeLength, zeeElegooDCMparam param)  
  :zeeDCMotor(arduino, executeLength)
{
  _dcMotor = param.DcMotor;
  _in1Pin = param.In1Pin;
  _in2Pin = param.In2Pin;
  _enaPin = param.EnaPin;

  arduino->pinMode(_in1Pin, OUTPUT);   
  arduino->pinMode(_in2Pin, OUTPUT);
  arduino->pinMode(_enaPin, OUTPUT);
}

void zeeElegooDCMotor::DoExecute()
{
}

void zeeElegooDCMotor::Setup(int speed)
{
}

