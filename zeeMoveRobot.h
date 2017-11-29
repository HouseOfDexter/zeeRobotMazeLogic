#ifndef zeeMoveRobot_h
#define zeeMoveRobot_h

#include "zeeStateLED.h"
#include "zeeDetection.h"
#include "zeeExecute.h"
#include "zeeMotors.h"

class zeeMoveRobot : zeeExecute
{
public:
  const int defaultMoveTime = 250;
  zeeMoveRobot(zeeArduino* arduino, unsigned int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeMoveRobot();

  virtual bool Handle(zeeDetection detection, bool isFinished, bool handled);
  unsigned int GetMoveTime();
protected:
  //abstract method that will be implemented by State Class
  virtual bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) = 0;
  zeeMoveRobot* GetRobot();
  void CallNextRobot(zeeDetection detection, bool isFinished, bool handled);
  virtual bool IsHandled();
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
  virtual ~zeeTurnRight();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
};

/************************************************************************************/

class zeeTurnLeft : public zeeMoveRobot
{
public:
  zeeTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeTurnLeft();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
};

/************************************************************************************/
class zeeSmallTurnLeft : public zeeMoveRobot
{
public:
  zeeSmallTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeSmallTurnLeft();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
};

/************************************************************************************/
class zeeSmallTurnRight : public zeeMoveRobot
{
public:
  zeeSmallTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeSmallTurnRight();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
};

/************************************************************************************/
class zeeGoStraight : public zeeMoveRobot
{
public:
  zeeGoStraight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeGoStraight();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
};
/************************************************************************************/

class zeeGoCoast : public zeeMoveRobot
{
public:
  zeeGoCoast::zeeGoCoast(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors);
  virtual ~zeeGoCoast();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
};
/************************************************************************************/


class zeeStop : public zeeMoveRobot
{
public:
  zeeStop(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeStop();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
};

/************************************************************************************/
class zeeStart : public zeeMoveRobot
{
public:
  zeeStart(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeStart();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
};

/************************************************************************************/
class zeeFinished : public zeeMoveRobot
{
public:
  zeeFinished(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeFinished();
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
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
  virtual ~zeeDecoratorLed();
  bool Handle(zeeDetection detection, bool isFinished, bool handled) override;
protected:
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
  void DoExecute();
  bool IsHandled() override;
private:
  zeeArduino* _arduino;
  zeeStateLED* _leds;
  void FlashLeds();
  void SetLeds(bool setOn);
};

/************************************************************************************/
class zeeDecoratorPrintLn : public zeeMoveRobot
{
public:
  zeeDecoratorPrintLn(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot);
  virtual ~zeeDecoratorPrintLn();
  bool Handle(zeeDetection detection, bool isFinished, bool handled) override;
protected:
  void DoExecute();
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
  void Print(char description[], long value, char extension[]);
  void Print(char description[], bool value, char extension[]);
  bool IsHandled() override;
};
/************************************************************************************/
class zeeDetectorRobot : public zeeMoveRobot 
{
public:
  zeeDetectorRobot(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeDetector* detector);
  virtual ~zeeDetectorRobot();
  bool Handle(zeeDetection detection, bool isFinished, bool handled) override;
protected:
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
  void DoExecute();
  bool IsHandled() override;
private:
  zeeDetector* _detector;
};
/************************************************************************************/
class zeeMotorFactory
{
public:
  static zeeMoveRobot* SetMoveRobots(zeeArduino* arduino, zeeMoveRobot* zeeMoveRobot, zeeMotors* motors, int moveTime);
};
#endif