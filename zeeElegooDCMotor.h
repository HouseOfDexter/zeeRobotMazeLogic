#ifndef zeeElegooDCMotor_h
#define zeeElegooDCMotor_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "zeeArduino.h"
#include "zeeDCMotor.h"
#include "Elegoo_DCMotor.h"

class zeeElegooDCMparam 
{
public:
  zeeElegooDCMparam(unsigned int in1Pin, unsigned int in2Pin, unsigned int enaPin,  Elegoo_DCMotor * dcMotor);
  ~zeeElegooDCMparam();
  
  unsigned int In1Pin;
  unsigned int In2Pin;
  unsigned int EnaPin;
  Elegoo_DCMotor* DcMotor;
};

class zeeElegooDCMotor :
  public zeeDCMotor
{
public:
  zeeElegooDCMotor(zeeArduino* arduino, unsigned long executeLength, zeeElegooDCMparam param);
  ~zeeElegooDCMotor();  
  void Setup(int speed);
protected:
  void DoExecute();
private:
  unsigned int _in1Pin;
  unsigned int _in2Pin;
  unsigned int _enaPin;
  int _speed;
  Elegoo_DCMotor * _dcMotor;
};

#endif
