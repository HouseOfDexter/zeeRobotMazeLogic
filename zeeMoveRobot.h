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

class zeeMoveRobot : zeeExecute
{
public:
  const int defaultMoveTime = 250;
  zeeMoveRobot(unsigned int moveTime, zeeMoveRobot* robot);
  ~zeeMoveRobot();

  virtual bool Handle(zeeDetection* detection, bool isFinished);
protected:
  //abstract method that will be implemented by State Class
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished) = 0;
  zeeMoveRobot* GetRobot();
  void CallNextRobot(zeeDetection* detection, bool isFinished);
  //abstract method that will be implemented by State Class
  virtual void Execute();
  unsigned int GetMoveTime();
private:
  unsigned int _moveTime = defaultMoveTime;
  zeeMoveRobot* _robot;
};

class zeeTurnRight : public zeeMoveRobot
{
public:
  zeeTurnRight(int moveTime, zeeMoveRobot* robot);
  void Execute();
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

class zeeTurnLeft : public zeeMoveRobot
{
public:
  zeeTurnLeft(int moveTime, zeeMoveRobot* robot);
  void Execute();
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

class zeeSmallTurnLeft : public zeeMoveRobot
{
public:
  zeeSmallTurnLeft(int moveTime, zeeMoveRobot* robot);
  void Execute();
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

class zeeGoStraight : public zeeMoveRobot
{
public:
  zeeGoStraight(int moveTime, zeeMoveRobot* robot);
  void Execute();
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

class zeeStop : public zeeMoveRobot
{
public:
  zeeStop(int moveTime, zeeMoveRobot* robot);
  void Execute();
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

class zeeFinished : public zeeMoveRobot
{
public:
  zeeFinished(int moveTime, zeeMoveRobot* robot);
  void Execute();
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
};

class zeeDecoratorLed : public zeeMoveRobot
{
  /*
    this is a decorator class that can be inserted into our chain of MoveRobot(s)
    that handles blinking of LEDs for outside status
  */
public:
  zeeDecoratorLed(int moveTime, zeeMoveRobot* robot, zeeOnOffLED* onOffLed);

  bool Handle(zeeDetection* detection, bool isFinished);
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
private:
  zeeOnOffLED *_onOffLed;
  void FlashLeds();
  void SetLeds(bool setOn);
};

class zeeDecoratorPrintLn : public zeeMoveRobot
{
public:
  zeeDecoratorPrintLn(int moveTime, zeeMoveRobot* robot);
  bool Handle(zeeDetection* detection, bool isFinished);
protected:
  virtual bool ShouldHandle(zeeDetection* detection, bool isFinished);
  void Print(char description[], long value, char extension[]);
  void Print(char description[], bool value, char extension[]);
};
#endif