#ifndef zeeMoveRobot_h
#define zeeMoveRobot_h

#include "zeeArduino.h"
#include "zeeStateLED.h"
#include "zeeDetection.h"
#include "zeeExecute.h"
#include "zeeMotors.h"

const int cTurnRight = 1;
const int cTurnLeft = 2;
const int cSmallTurnRight = 4;
const int cSmallTurnLeft = 8;
const int cGoStraight = 16;
const int cGoCoast = 32;
const int cStop = 64;
const int cStart = 128;
const int cFinished = 256;
const int cDecoratorLed = 512;
const int cDecoratorPrintLn = 1024;
const int cDetectorRobot = 2048;

class zeeMoveRobot : public zeeExecute
{
public:
  const int defaultMoveTime = 250;
  zeeMoveRobot(zeeArduino* arduino, unsigned int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeMoveRobot();

  virtual unsigned int Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots);
  unsigned int GetMoveTime();
  virtual unsigned int GetId() = 0;
protected:
  //abstract method that will be implemented by State Class
  virtual bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) = 0;
  zeeMoveRobot* GetRobot();
  unsigned int CallNextRobot(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots);
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
  unsigned int GetId() { return cTurnRight; }
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
  unsigned int GetId() { return cTurnLeft; }
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
  unsigned int GetId() { return cSmallTurnLeft; }
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
  unsigned int GetId() { return cSmallTurnRight; }
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
  unsigned int GetId() { return cGoStraight; }
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
  unsigned int GetId() { return cGoCoast; }
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
  unsigned int GetId() { return cStop; }
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
  unsigned int GetId() { return cStart; }
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
  unsigned int GetId() { return cFinished; }
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
  unsigned int Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots) override;
  unsigned int GetId() { return cDecoratorLed; }
protected:
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
  void DoExecute();
  bool IsHandled() override;
private:  
  zeeStateLED* _leds;
  void FlashLeds();
  void SetLeds(bool setOn);
};

/************************************************************************************/
//class zeeDecoratorPrintLn : public zeeMoveRobot
//{
//public:
//  zeeDecoratorPrintLn(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
//  virtual ~zeeDecoratorPrintLn();
//  unsigned int Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots) override;
//  unsigned int GetId() { return cDecoratorPrintLn; }
//protected:
//  void DoExecute();
//  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled);
//  void Print(const String &description, long value, const String &extension);
//  void Print(const String &description, bool value, const String &extension);
//  bool IsHandled() override;
//private:
//  zeeDetection _detection;
//};
/************************************************************************************/
class zeeDetectorRobot : public zeeMoveRobot 
{
public:
  zeeDetectorRobot(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeDetector* detector);
  virtual ~zeeDetectorRobot();
  unsigned int Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots) override;
  unsigned int GetId() { return cDetectorRobot; }
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
  static zeeMoveRobot* SetMoveRobots(zeeArduino* arduino, zeeMoveRobot* zeeMoveRobot, zeeMotors* motors, zeeDetector* detector, int moveTime);
  static String GetRobotString(unsigned int id);
};
#endif

