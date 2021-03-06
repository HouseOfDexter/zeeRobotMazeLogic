#ifndef zee298DualHBridgeMotorDriver_h
#define zee298DualHBridgeMotorDriver_h

#include "zeeExecute.h"
#include "zeeMotors.h"

class zeeHBridgeMDparam 
{
public:
  zeeHBridgeMDparam(unsigned int enablePin, unsigned int pin1, unsigned int pin2);
  unsigned int EnablePin;
  unsigned int Pin1;
  unsigned int Pin2;
};

class zee298DualHBridgeMotorDriver :
  public zeeMotors
{
public:
  zee298DualHBridgeMotorDriver(zeeArduino* arduino, unsigned long executeLength, zeeHBridgeMDparam paramA, zeeHBridgeMDparam paramB);
  virtual ~zee298DualHBridgeMotorDriver();

  void EnableMotors();
  void EnableTurMotors();
  void DisableMotors();

  void Forward(unsigned int duration = 0);
  void Backward(unsigned int duration = 0);
  void TurnLeft(unsigned int duration = 0);
  void TurnRight(unsigned int duration = 0);
  void Coast(unsigned int duration = 0);
  void Brake(unsigned int duration = 0);
protected:
  void DoExecute(bool bypassWait);
  void DoMotor(unsigned int pin, unsigned int direction);
  void DoMotor(unsigned int pin1, unsigned int direction1, unsigned pin2, unsigned direction2);

  void MotorAOn();
  void MotorBOn();
  void MotorAOff();
  void MotorBOff();
  void MotorAForward();
  void MotorBForward();
  void MotorABackward();
  void MotorBBackward();
  void MotorACoast();
  void MotorBCoast();
  void MotorABrake();
  void MotorBBrake();
private:
  unsigned int _enableAPin;
  unsigned int _pinA1;
  unsigned int _pinA2;

  unsigned int _enableBPin;
  unsigned int _pinB1;
  unsigned int _pinB2;
};
#endif

