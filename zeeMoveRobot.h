#ifndef zeeMoveRobot_h
#define zeeMoveRobot_h

#include "zeeArduino.h"
#include "zeeStateLED.h"
#include "zeeDetection.h"
#include "zeeExecute.h"
#include "zeeMotors.h"

/*These constants are bit flags
 To add flags, you Or against a running total i.e. robots = robots | GetId();
 which flips the flag for the id in the running total robots.
 
 To find flags that match, you AND running Total against a Bit Mask i.e. robots && c2ndRobotCallMask
 which will only return flags greater than or equal to 32
*/
const int cStart = 1;
const int cGoCoast = 2;
const int cSmallTurnRight = 4;
const int cSmallTurnLeft = 8;
const int cDetectorRobot = 16;

//this bit mask is 1 + 2 + 4 +8 + 16
const int c1stRobotCallMask = 31;

const int cTurnRight = 32;
const int cTurnLeft = 64;
const int cGoStraight = 128;
const int cStop = 256;
const int cFinished = 512;
const int cDecoratorLed = 1024;
const int cDecoratorPrintLn = 2048;
//if you need to add more MoveRobots like decorators just double the last cMoveRobot and add it to the bitMask


//this bit flag is 32 + 64 + 128 + 256 + 512 + 1024 + 2048
const int c2ndRobotCallMask = 4064;

class zeeMoveRobot : public zeeExecute
{
public:
  const int defaultMoveTime = 250;
  zeeMoveRobot(zeeArduino* arduino, unsigned int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeMoveRobot();

  virtual unsigned int Handle(const zeeDetection detection, bool isFinished, bool handled, unsigned int robots);
  unsigned int GetMoveTime();
  virtual unsigned int GetId() = 0;
  bool IsHandled();
  zeeMoveRobot* GetRobot();
protected:
  //abstract method that will be implemented by State Class
  virtual bool ShouldHandle(const zeeDetection detection, bool isFinished, bool handled) = 0;  
  unsigned int CallNextRobot(const zeeDetection detection, bool isFinished, bool handled, unsigned int robots);
  virtual bool ReportIsHandled();
  
  zeeMotors* _motors;
  unsigned int _defaultBitMask = 0;
private:
  void SetIsHandled(bool value);
  unsigned int _moveTime = defaultMoveTime;
  zeeMoveRobot* _robot;  
  bool _isHandled = false;
};

/************************************************************************************/
class zeeTurnRight : public zeeMoveRobot
{
public:
  zeeTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeTurnRight();
  unsigned int GetId() { return cTurnRight; }
protected:
  void DoExecute(bool bypassWait) override;
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
};

/************************************************************************************/

class zeeTurnLeft : public zeeMoveRobot
{
public:
  zeeTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeTurnLeft();
  unsigned int GetId() { return cTurnLeft; }
protected:
  void DoExecute(bool bypassWait) override;
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
};

/************************************************************************************/
class zeeSmallTurnLeft : public zeeMoveRobot
{
public:
  zeeSmallTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeSmallTurnLeft();
  unsigned int GetId() { return cSmallTurnLeft; }
protected:
  void DoExecute(bool bypassWait) override;
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
};

/************************************************************************************/
class zeeSmallTurnRight : public zeeMoveRobot
{
public:
  zeeSmallTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeSmallTurnRight();
  unsigned int GetId() { return cSmallTurnRight; }
protected:
  void DoExecute(bool bypassWait) override;
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
};

/************************************************************************************/
class zeeGoStraight : public zeeMoveRobot
{
public:
  zeeGoStraight(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeGoStraight();
  unsigned int GetId() { return cGoStraight; }
protected:
  void DoExecute(bool bypassWait) override;
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
};
/************************************************************************************/

class zeeGoCoast : public zeeMoveRobot
{
public:
  zeeGoCoast::zeeGoCoast(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors);
  virtual ~zeeGoCoast();
  unsigned int GetId() { return cGoCoast; }
protected:
  void DoExecute(bool bypassWait) override;
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
};
/************************************************************************************/


class zeeStop : public zeeMoveRobot
{
public:
  zeeStop(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeStop();
  unsigned int GetId() { return cStop; }
protected:
  void DoExecute(bool bypassWait);
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
};

/************************************************************************************/
class zeeStart : public zeeMoveRobot
{
public:
  zeeStart(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeStart();
  unsigned int GetId() { return cStart; }
protected:
  void DoExecute(bool bypassWait) override;
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
};

/************************************************************************************/
class zeeFinished : public zeeMoveRobot
{
public:
  zeeFinished(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors);
  virtual ~zeeFinished();
  unsigned int GetId() { return cFinished; }
protected:
  void DoExecute(bool bypassWait) override;
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
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
  unsigned int Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int robots) override;
  unsigned int GetId() { return cDecoratorLed; }
protected:
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
  void DoExecute(bool bypassWait) override;
  bool ReportIsHandled() override;
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
  zeeDetectorRobot(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeDetector* detector, unsigned int bitMask);
  virtual ~zeeDetectorRobot();
  unsigned int Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int robots) override;
  unsigned int GetId() { return cDetectorRobot; }
protected:
  bool ShouldHandle(zeeDetection detection, bool isFinished, bool handled) override;
  void DoExecute(bool bypassWait) override;
  bool ReportIsHandled() override;
private:
  zeeDetector* _detector;
  unsigned int _bitMask = 0;
};
/************************************************************************************/
class zeeMotorFactory
{
public:
  static zeeMoveRobot* SetMoveRobots(zeeArduino* arduino, zeeArduino * nowait, zeeMoveRobot* moveRobot, zeeMotors* motors, zeeDetector* detector, int moveTime);
  static zeeMoveRobot* GetRobot(unsigned int id, zeeMoveRobot* robot);
};
#endif

