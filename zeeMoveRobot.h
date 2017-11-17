#ifndef zeeMoveRobot_h
#define zeeMoveRobot_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "zeeOnOffLED.h"
#include "zeeDetection.h"
#include "zeeExecute.h"
#include "zeeDCMotor.h"

class zeeMoveRobot : zeeExecute
{
public:
  const int defaultMoveTime = 250;
  zeeMoveRobot(zeeArduino* arduino, unsigned int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  ~zeeMoveRobot();

  virtual bool Handle(zeeDetection* detection, bool isFinished);
protected:
  //abstract method that will be implemented by State Class
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished) = 0;
  zeeMoveRobot* GetRobot();
  void CallNextRobot(zeeDetection* detection, bool isFinished);  
  unsigned int GetMoveTime();
  zeeDCMotor* GetMotorFL();
  zeeDCMotor* GetMotorFR();
  zeeDCMotor* GetMotorRL();
  zeeDCMotor* GetMotorRR();
private:
  unsigned int _moveTime = defaultMoveTime;
  zeeMoveRobot* _robot;
  zeeMotors* _motors;
};

/************************************************************************************/
class zeeTurnRight : public zeeMoveRobot
{
public:
  zeeTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

/************************************************************************************/

class zeeTurnLeft : public zeeMoveRobot
{
public:
  zeeTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

/************************************************************************************/
class zeeSmallTurnLeft : public zeeMoveRobot
{
public:
  zeeSmallTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

/************************************************************************************/
class zeeSmallTurnRight : public zeeMoveRobot
{
public:
  zeeSmallTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

/************************************************************************************/
class zeeGoStraight : public zeeMoveRobot
{
public:
  zeeGoStraight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

/************************************************************************************/
class zeeStop : public zeeMoveRobot
{
public:
  zeeStop(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

/************************************************************************************/
class zeeFinished : public zeeMoveRobot
{
public:
  zeeFinished(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

/************************************************************************************/
class zeeDecoratorLed : public zeeMoveRobot
{
  /*
    this is a decorator class that can be inserted into our chain of MoveRobot(s)
    that handles blinking of LEDs for outside status
  */
public:
  zeeDecoratorLed(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* robot, zeeOnOffLED* onOffLed);

  bool Handle(zeeDetection* detection, bool isFinished);
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
  void DoExecute();
private:
  zeeOnOffLED* _onOffLed;
  void FlashLeds();
  void SetLeds(bool setOn);
};

/************************************************************************************/
class zeeDecoratorPrintLn : public zeeMoveRobot
{
public:
  zeeDecoratorPrintLn(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot);
  bool Handle(zeeDetection* detection, bool isFinished);
protected:
  void DoExecute();
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
  void Print(char description[], long value, char extension[]);
  void Print(char description[], bool value, char extension[]);
};
#endif