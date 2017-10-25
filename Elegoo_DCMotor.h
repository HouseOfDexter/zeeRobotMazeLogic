#pragma once

class Elegoo_MotorShield
{
public:
  Elegoo_MotorShield();
  ~Elegoo_MotorShield();
  Elegoo_DCMotor *getMotor(unsigned int motor);
private:
  Elegoo_DCMotor _dcMotors[4];
};

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
