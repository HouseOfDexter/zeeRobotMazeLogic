#ifndef zeeAdafruitDCMotor_h
#define zeeAdafruitDCMotor_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include <Adafruit_MotorShield.h>
#include "zeeDCMotor.h"
/*We create a Fascade around Adafruit Library*/
class zeeAdafruitDCMotor : public zeeDCMotor
{
public:
  zeeAdafruitDCMotor(unsigned int pin, Adafruit_DCMotor* dcMotor);
  ~zeeAdafruitDCMotor();
  void Execute();
  void Setup(int speed);
private:
  unsigned int _pin;
  int _speed;
  Adafruit_DCMotor * _dcMotor;
};
#endif
