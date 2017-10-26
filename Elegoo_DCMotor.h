#ifndef Elegoo_MotorShield_h
#define Elegoo_MotorShield_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class Elegoo_MotorShield;

class Elegoo_DCMotor
{
public:
  Elegoo_DCMotor();
  ~Elegoo_DCMotor();
  int Id();
  void SetId(int id);
private:
  int _id;
};

class Elegoo_MotorShield
{
public:
  Elegoo_MotorShield();
  ~Elegoo_MotorShield();
  Elegoo_DCMotor *getMotor(unsigned int motor);
private:
  Elegoo_DCMotor _dcMotors[4];
};

#endif
