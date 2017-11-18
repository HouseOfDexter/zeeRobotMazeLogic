#ifndef zeeMoveRobot_h
#define zeeMoveRobot_h
#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "zeeStateLED.h"
#include "zeeDetection.h"
#include "zeeExecute.h"
#include "zeeMotors.h"

class zeeMoveRobot : zeeExecute
{
public:
  const int defaultMoveTime = 250;
  zeeMoveRobot(zeeArduino* arduino, unsigned int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  ~zeeMoveRobot();

  virtual bool Handle(zeeDetection detection, bool isFinished);
protected:
  //abstract method that will be implemented by State Class
  virtual bool ShouldHandle(zeeDetection detection, bool isFinished) = 0;
  zeeMoveRobot* GetRobot();
  void CallNextRobot(zeeDetection detection, bool isFinished);  
  unsigned int GetMoveTime();
  zeeMotors* _motors;
private:
  unsigned int _moveTime = defaultMoveTime;
  zeeMoveRobot* _robot;  
};

/************************************************************************************/
class zeeTurnRight : public zeeMoveRobot
{
public:
  zeeTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished);
};

/************************************************************************************/

class zeeTurnLeft : public zeeMoveRobot
{
public:
  zeeTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished);
};

/************************************************************************************/
class zeeSmallTurnLeft : public zeeMoveRobot
{
public:
  zeeSmallTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished);
};

/************************************************************************************/
class zeeSmallTurnRight : public zeeMoveRobot
{
public:
  zeeSmallTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished);
};

/************************************************************************************/
class zeeGoStraight : public zeeMoveRobot
{
public:
  zeeGoStraight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished);
};

/************************************************************************************/
class zeeStop : public zeeMoveRobot
{
public:
  zeeStop(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished);
};

/************************************************************************************/
class zeeFinished : public zeeMoveRobot
{
public:
  zeeFinished(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished);
};

/************************************************************************************/
class zeeDecoratorLed : public zeeMoveRobot
{
  /*
    this is a decorator class that can be inserted into our chain of MoveRobot(s)
    that handles blinking of LEDs for outside status
  */
public:
  zeeDecoratorLed(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* robot, zeeStateLED* _leds);

  bool Handle(zeeDetection detection, bool isFinished);
protected:
  bool ShouldHandle(zeeDetection detection, bool isFinished);
  void DoExecute();
private:
  zeeStateLED* _leds;
  void FlashLeds();
  void SetLeds(bool setOn);
};

/************************************************************************************/
class zeeDecoratorPrintLn : public zeeMoveRobot
{
public:
  zeeDecoratorPrintLn(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot);
  bool Handle(zeeDetection detection, bool isFinished);
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished);
  void Print(char description[], long value, char extension[]);
  void Print(char description[], bool value, char extension[]);
};
#endif