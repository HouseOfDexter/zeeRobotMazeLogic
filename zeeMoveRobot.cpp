#include "zeeMoveRobot.h"
//#include "zeeOnOffLED.h"

/*This is a Abstract State Class, it knows how to do it's one function and only that*/

zeeMoveRobot::zeeMoveRobot(unsigned int moveTime, zeeMoveRobot* robot, zeeMotors* motors)
  :_moveTime(moveTime), _robot(robot), _motors(motors)
{
}

zeeMoveRobot::~zeeMoveRobot()
{
  //we clean up our chained robots
  if (_robot != NULL)
    delete _robot;
}

bool zeeMoveRobot::Handle(zeeDetection * detection, bool isFinished)
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

void zeeMoveRobot::Execute()
{
  Serial.println("Default Move");
}

unsigned int zeeMoveRobot::GetMoveTime()
{
  return _moveTime;
}

zeeDCMotor * zeeMoveRobot::GetMotorFL()
{
  return _motors->GetMotorFL();
}

zeeDCMotor * zeeMoveRobot::GetMotorFR()
{
  return _motors->GetMotorFR();
}

zeeDCMotor * zeeMoveRobot::GetMotorRL()
{
  return _motors->GetMotorRL();
}

zeeDCMotor * zeeMoveRobot::GetMotorRR()
{
  return _motors->GetMotorRR();
}

zeeMoveRobot * zeeMoveRobot::GetRobot()
{
  return _robot;
}

void zeeMoveRobot::CallNextRobot(zeeDetection* detection, bool isFinished)
{
  //we call our chained robot to see if it needs to handle the request
  zeeMoveRobot* nextRobot = GetRobot();
  if (nextRobot != NULL)
    nextRobot->Handle(detection, isFinished);
}

/************************************************************************************/

zeeDecoratorLed::zeeDecoratorLed(int moveTime, zeeMoveRobot* robot, zeeOnOffLED *onOffLed)
  : zeeMoveRobot(moveTime, robot, NULL)
{
  _onOffLed = onOffLed;
}

bool zeeDecoratorLed::Handle(zeeDetection* detection, bool isFinished)
{
  if (!isFinished)
  {
    bool ledsOn = false;
    if (detection->GetIsEqual())
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
  _onOffLed->Set2LEDs(true);
  delayMicroseconds(500);
  _onOffLed->Set2LEDs(false);
}

void zeeDecoratorLed::SetLeds(bool setOn)
{
  _onOffLed->Set2LEDs(setOn);
}

bool zeeDecoratorLed::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return true;
}

/************************************************************************************/

zeeTurnRight::zeeTurnRight(int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(moveTime, robot, motors)
{
}

void zeeTurnRight::Execute()
{
  Serial.println("zeeTurnRight Move");
  //temp mock moving
  delayMicroseconds(GetMoveTime());
  GetMotorFL()->Execute();
  GetMotorRL()->Execute();
}

bool zeeTurnRight::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return !isFinished && !detection->GetIsEqual() &&
    detection->GetDiffBetweenRightSensors() > 0;
}

/************************************************************************************/

zeeTurnLeft::zeeTurnLeft(int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(moveTime, robot, motors)
{
}

void zeeTurnLeft::Execute()
{
  Serial.println("zeeTurnLeft Move");
  //temp mock moving
  delayMicroseconds(GetMoveTime());
  GetMotorFR()->Execute();
  GetMotorRR()->Execute();
}

bool zeeTurnLeft::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return (!isFinished && detection->GetObstacleForward() &&
    !detection->GetIsEqual() &&
    detection->GetDiffBetweenRightSensors() < 0);
}

/************************************************************************************/

zeeGoStraight::zeeGoStraight(int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  :zeeMoveRobot(moveTime, robot, motors)
{};

void zeeGoStraight::Execute()
{
  Serial.println("zeeGoStraight Move");
  //temp mock moving
  delayMicroseconds(GetMoveTime());
  GetMotorFL()->Execute();
  GetMotorRL()->Execute();
  GetMotorFR()->Execute();
  GetMotorRR()->Execute();
}

bool zeeGoStraight::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return (!isFinished && detection->GetIsEqual() &&
    !detection->GetObstacleForward());
}

/************************************************************************************/

zeeStop::zeeStop(int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(moveTime, robot, motors)
{
}

void zeeStop::Execute()
{
  Serial.println("zeeStop Move");
  delayMicroseconds(GetMoveTime());
}

bool zeeStop::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return !isFinished && detection->GetObstacleForward();
}

/************************************************************************************/

zeeFinished::zeeFinished(int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(moveTime, robot, motors)
{
}

void zeeFinished::Execute()
{
  Serial.println("zeeFinished Move");
  delayMicroseconds(GetMoveTime());
}

bool zeeFinished::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return isFinished;
}

/************************************************************************************/

zeeSmallTurnLeft::zeeSmallTurnLeft(int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(moveTime, robot, motors)
{
}

void zeeSmallTurnLeft::Execute()
{
  Serial.println("zeeSmallTurnLeft Move");
  //temp mock moving
  delayMicroseconds(GetMoveTime());
  GetMotorFR()->Execute();
}

bool zeeSmallTurnLeft::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return (!isFinished && !detection->GetIsEqual() &&
    detection->GetDiffBetweenRightSensors() < 0);
}

/************************************************************************************/

zeeSmallTurnRight::zeeSmallTurnRight(int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(moveTime, robot, motors)
{
}

void zeeSmallTurnRight::Execute()
{
  Serial.println("zeeSmallTurnLeft Move");
  //temp mock moving
  delayMicroseconds(GetMoveTime());
  GetMotorFL()->Execute();
}

bool zeeSmallTurnRight::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return (!isFinished && !detection->GetIsEqual() &&
    detection->GetDiffBetweenRightSensors() > 0);
}

/************************************************************************************/

zeeDecoratorPrintLn::zeeDecoratorPrintLn(int moveTime, zeeMoveRobot* robot)
  : zeeMoveRobot(moveTime, robot, NULL)
{
}

bool zeeDecoratorPrintLn::Handle(zeeDetection * detection, bool isFinished)
{
  Print("ObstacleForward: ", detection->GetObstacleForward(), "");
  Print("IsEqual: ", detection->GetIsEqual(), "");
  Print("DetectLine: ", detection->GetDetectLine(), "");
  Print("DiffBetweenRightSensors: ", detection->GetDiffBetweenRightSensors(), "mm");

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

bool zeeDecoratorPrintLn::ShouldHandle(zeeDetection * detection, bool isFinished)
{
  return true;
}