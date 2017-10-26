#include "Elegoo_DCMotor.h"

Elegoo_MotorShield::Elegoo_MotorShield()
{
}

Elegoo_MotorShield::~Elegoo_MotorShield()
{
}

Elegoo_DCMotor *Elegoo_MotorShield::getMotor(unsigned int motor)
{
  if (motor > 4)
    return NULL;
  if (_dcMotors[motor].Id() == 0)
  {
    _dcMotors[motor].SetId(motor);
    //Set Reserved Pins
    switch (motor)
    {
    case 0:
      break;
    case 1:
      break;
    case 2:
      break;
    case 3:
      break;
    }
  }
  return &_dcMotors[motor];
}

Elegoo_DCMotor::Elegoo_DCMotor()
{
}

Elegoo_DCMotor::~Elegoo_DCMotor()
{
}

int Elegoo_DCMotor::Id()
{
  return _id;
}

void Elegoo_DCMotor::SetId(int id)
{
}