#include "zeeMoveRobot.h"
//#include "zeeStateLED.h"

/*This is a Abstract State Class, it knows how to do it's one function and only that*/

zeeMoveRobot::zeeMoveRobot(zeeArduino* arduino, unsigned int moveTime, zeeMoveRobot* robot, zeeMotors* motors)
  :zeeExecute(arduino, moveTime)
{
  _moveTime = moveTime;
  _robot = robot;
  _motors = motors;
}

zeeMoveRobot::~zeeMoveRobot()
{
  //we clean up our chained robots
  if (_robot != NULL)
    delete _robot;
}

bool zeeMoveRobot::Handle(zeeDetection detection, bool isFinished)
{
  bool handled = false;
  if (ShouldHandle(detection, isFinished))
  {
    Execute();
    handled = true;
  }
  CallNextRobot(detection, isFinished);

  return handled;
}

unsigned int zeeMoveRobot::GetMoveTime()
{
  return _moveTime;
}

zeeMoveRobot * zeeMoveRobot::GetRobot()
{
  return _robot;
}

void zeeMoveRobot::CallNextRobot(zeeDetection detection, bool isFinished)
{
  //we call our chained robot to see if it needs to handle the request
  zeeMoveRobot* nextRobot = GetRobot();
  if (nextRobot != NULL)
    nextRobot->Handle(detection, isFinished);
}

/************************************************************************************/

zeeDecoratorLed::zeeDecoratorLed(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* robot, zeeStateLED* leds)
  : zeeMoveRobot(arduino, executeLength, robot, NULL)
{
  _leds = leds;
}

bool zeeDecoratorLed::Handle(zeeDetection detection, bool isFinished)
{
  if (!isFinished)
  {
    bool ledsOn = false;
    if (detection.GetIsEqual())
      ledsOn = true;
    SetLeds(ledsOn);
  }
  while (isFinished)
  {
    //once this starts there is no way to break out of the loop...
    //maybe introduce a callback function that allows a chance to breakout?
    FlashLeds();
  }
  CallNextRobot(detection, isFinished);
  return false;
}

void zeeDecoratorLed::FlashLeds()
{
  //We flash the LEDS on and off...
  _leds->StateOn(true);
  delayMicroseconds(500);
  _leds->StateOn(false);
}

void zeeDecoratorLed::SetLeds(bool setOn)
{
  _leds->StateOn(setOn);
}

bool zeeDecoratorLed::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return true;
}

void zeeDecoratorLed::DoExecute()
{
}

/************************************************************************************/

zeeTurnRight::zeeTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

void zeeTurnRight::DoExecute()
{
  Serial.println("zeeTurnRight Move");
  _motors->TurnRight();  
}

bool zeeTurnRight::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return !isFinished && !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() > 0;
}

/************************************************************************************/

zeeTurnLeft::zeeTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

void zeeTurnLeft::DoExecute()
{
  Serial.println("zeeTurnLeft Move");
  _motors->TurnLeft();
}

bool zeeTurnLeft::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return (!isFinished && detection.GetObstacleForward() &&
    !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() < 0);
}

/************************************************************************************/

zeeGoStraight::zeeGoStraight(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  :zeeMoveRobot(arduino, moveTime, robot, motors)
{};

void zeeGoStraight::DoExecute()
{
  Serial.println("zeeGoStraight Move");
  _motors->Forward();
}

bool zeeGoStraight::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return (!isFinished && detection.GetIsEqual() &&
    !detection.GetObstacleForward());
}

/************************************************************************************/



zeeStop::zeeStop(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors * motors)
  :zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

void zeeStop::DoExecute()
{
  Serial.println("zeeStop Move");
  _motors->Brake();
}

bool zeeStop::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return !isFinished && detection.GetObstacleForward();
}

/************************************************************************************/

zeeFinished::zeeFinished(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

void zeeFinished::DoExecute()
{
  Serial.println("zeeFinished Move");
  _motors->DisableMotors();
}

bool zeeFinished::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return isFinished;
}

/************************************************************************************/

zeeSmallTurnLeft::zeeSmallTurnLeft(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

void zeeSmallTurnLeft::DoExecute()
{
  Serial.println("zeeSmallTurnLeft Move");
  
  _motors->TurnLeft();
}

bool zeeSmallTurnLeft::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return (!isFinished && !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() < 0);
}

/************************************************************************************/

zeeSmallTurnRight::zeeSmallTurnRight(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

void zeeSmallTurnRight::DoExecute()
{
  Serial.println("zeeSmallTurnLeft Move");
  _motors->TurnRight();  
}

bool zeeSmallTurnRight::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return (!isFinished && !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() > 0);
}

/************************************************************************************/

zeeDecoratorPrintLn::zeeDecoratorPrintLn(zeeArduino * arduino, int moveTime, zeeMoveRobot* robot)
  : zeeMoveRobot(arduino, moveTime, robot, NULL)
{
}

bool zeeDecoratorPrintLn::Handle(zeeDetection detection, bool isFinished)
{
  Print("ObstacleForward: ", detection.GetObstacleForward(), "");
  Print("IsEqual: ", detection.GetIsEqual(), "");
  Print("DetectLine: ", detection.GetDetectLine(), "");
  Print("DiffBetweenRightSensors: ", detection.GetDiffBetweenRightSensors(), "mm");

  CallNextRobot(detection, isFinished);
  return false;
}

void zeeDecoratorPrintLn::Print(char description[], long value, char extension[])
{
  Serial.println(description);
  Serial.print(value);
  Serial.println(extension);
}

void zeeDecoratorPrintLn::Print(char description[], bool value, char extension[])
{
  Serial.println(description);
  Serial.print(value);
  Serial.println(extension);
}

void zeeDecoratorPrintLn::DoExecute()
{
}

bool zeeDecoratorPrintLn::ShouldHandle(zeeDetection detection, bool isFinished)
{
  return true;
}