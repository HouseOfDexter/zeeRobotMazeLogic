#include "zeeMoveRobot.h"
#include "stddef.h"
#include "zeeMotorPins.h"
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

bool zeeMoveRobot::Handle(zeeDetection detection, bool isFinished, bool handled)
{  
  if (ShouldHandle(detection, isFinished, handled))
  {
    Execute();
    handled = IsHandled();
  }
  CallNextRobot(detection, isFinished, handled);

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

void zeeMoveRobot::CallNextRobot(zeeDetection detection, bool isFinished, bool handled)
{
  //we call our chained robot to see if it needs to handle the request
  zeeMoveRobot* nextRobot = GetRobot();
  if (nextRobot != NULL)
    nextRobot->Handle(detection, isFinished, handled);
}

bool zeeMoveRobot::IsHandled()
{
  return true;
}

/************************************************************************************/

zeeDecoratorLed::zeeDecoratorLed(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* robot, zeeStateLED* leds)
  : zeeMoveRobot(arduino, executeLength, robot, NULL)
{
  _arduino = arduino;
  _leds = leds;
}

zeeDecoratorLed::~zeeDecoratorLed()
{
}

bool zeeDecoratorLed::Handle(zeeDetection detection, bool isFinished, bool handled)
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
  CallNextRobot(detection, isFinished, handled);
  return handled;
}

void zeeDecoratorLed::FlashLeds()
{
  //We flash the LEDS on and off...
  _leds->StateOn(true);
  _arduino->delayMicroseconds(500);
  _leds->StateOn(false);
}

void zeeDecoratorLed::SetLeds(bool setOn)
{
  _leds->StateOn(setOn);
}

bool zeeDecoratorLed::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return true;
}

void zeeDecoratorLed::DoExecute()
{
}

bool zeeDecoratorLed::IsHandled()
{
  return false;
}

/************************************************************************************/

zeeTurnRight::zeeTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

zeeTurnRight::~zeeTurnRight()
{
}

void zeeTurnRight::DoExecute()
{  
  _motors->TurnRight();  
}

bool zeeTurnRight::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return !isFinished && 
    !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() > 0 && 
    _motors->GetEnabled() &&
    !handled;
}

/************************************************************************************/

zeeTurnLeft::zeeTurnLeft(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

zeeTurnLeft::~zeeTurnLeft()
{
}

void zeeTurnLeft::DoExecute()
{  
  _motors->TurnLeft();
}

bool zeeTurnLeft::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return (!isFinished &&
    detection.GetObstacleForward() &&
    !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() < 0) && 
    _motors->GetEnabled() &&
    !handled;
}

/************************************************************************************/

zeeGoStraight::zeeGoStraight(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  :zeeMoveRobot(arduino, moveTime, robot, motors)
{}
zeeGoStraight::~zeeGoStraight()
{
}

void zeeGoStraight::DoExecute()
{  
  _motors->Forward();
}

bool zeeGoStraight::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return (!isFinished &&
    detection.GetIsEqual() &&
    !detection.GetObstacleForward()) &&
    _motors->GetEnabled() &&
    !handled;
}

/************************************************************************************/

zeeGoCoast::zeeGoCoast(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  :zeeMoveRobot(arduino, moveTime, robot, motors)
{}

zeeGoCoast::~zeeGoCoast()
{
}

void zeeGoCoast::DoExecute()
{
  _motors->Coast();
}

bool zeeGoCoast::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return (!isFinished &&
    detection.GetIsEqual() &&
    !detection.GetObstacleForward()) &&
    _motors->GetEnabled() &&
    !handled;
}

/************************************************************************************/

zeeStop::zeeStop(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors * motors)
  :zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

zeeStop::~zeeStop()
{
}

void zeeStop::DoExecute()
{
  _motors->Brake();
}

bool zeeStop::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return !isFinished &&
    detection.GetObstacleForward() &&
    _motors->GetEnabled() &&
    !handled;
}

/************************************************************************************/
zeeStart::zeeStart(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

zeeStart::~zeeStart()
{
}

void zeeStart::DoExecute()
{
  _motors->SetEnabled(true);
  _motors->EnableMotors();
}

bool zeeStart::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return !isFinished &&
    !_motors->GetEnabled() &&
    !handled;
}

/************************************************************************************/
zeeFinished::zeeFinished(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

zeeFinished::~zeeFinished()
{
}

void zeeFinished::DoExecute()
{  
  _motors->SetEnabled(false);
  _motors->DisableMotors();
}

bool zeeFinished::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return isFinished;
}

/************************************************************************************/

zeeSmallTurnLeft::zeeSmallTurnLeft(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

zeeSmallTurnLeft::~zeeSmallTurnLeft()
{
}

void zeeSmallTurnLeft::DoExecute()
{  
  _motors->TurnLeft();
}

bool zeeSmallTurnLeft::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return (!isFinished &&
    !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() < 0) &&
    !handled;;
}

/************************************************************************************/

zeeSmallTurnRight::zeeSmallTurnRight(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
}

zeeSmallTurnRight::~zeeSmallTurnRight()
{
}

void zeeSmallTurnRight::DoExecute()
{  
  _motors->TurnRight();  
}

bool zeeSmallTurnRight::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return (!isFinished &&
    !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() > 0) &&
    !handled;
}

/************************************************************************************/

zeeDecoratorPrintLn::zeeDecoratorPrintLn(zeeArduino * arduino, int moveTime, zeeMoveRobot* robot)
  : zeeMoveRobot(arduino, moveTime, robot, NULL)
{
}

zeeDecoratorPrintLn::~zeeDecoratorPrintLn()
{
}

bool zeeDecoratorPrintLn::Handle(zeeDetection detection, bool isFinished, bool handled)
{
  Print("ObstacleForward: ", detection.GetObstacleForward(), "");
  Print("IsEqual: ", detection.GetIsEqual(), "");
  Print("DetectLine: ", detection.GetDetectLine(), "");
  Print("DiffBetweenRightSensors: ", detection.GetDiffBetweenRightSensors(), "mm");

  CallNextRobot(detection, isFinished, handled);
  return handled;
}

void zeeDecoratorPrintLn::Print(char description[], long value, char extension[])
{
  //Serial.println(description);
  //Serial.print(value);
  //Serial.println(extension);
}

void zeeDecoratorPrintLn::Print(char description[], bool value, char extension[])
{
  //Serial.println(description);
  //Serial.print(value);
  //Serial.println(extension);
}

bool zeeDecoratorPrintLn::IsHandled()
{
  return false;
}

void zeeDecoratorPrintLn::DoExecute()
{
}

bool zeeDecoratorPrintLn::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return true;
}

/************************************************************************************/

zeeDetectorRobot::zeeDetectorRobot(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeDetector * detector)
  : zeeMoveRobot(arduino, moveTime, robot, NULL)
{
  _detector = detector;
}

zeeDetectorRobot::~zeeDetectorRobot()
{
}

bool zeeDetectorRobot::Handle(zeeDetection detection, bool isFinished, bool handled)
{
  return false;
}

bool zeeDetectorRobot::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return false;
}

void zeeDetectorRobot::DoExecute()
{
}

bool zeeDetectorRobot::IsHandled()
{
  return false;
}

/************************************************************************************/
zeeMoveRobot * zeeMotorFactory::SetMoveRobots(zeeArduino * arduino, zeeMoveRobot * zeeMoveRobot, zeeMotors * motors, int moveTime)
{
  //zeeDecoratorTestLed *ledDecorator = new zeeDecoratorTestLed(moveTime, NULL, onOffLed);

  zeeFinished* finished = new zeeFinished(arduino, moveTime, zeeMoveRobot, motors);
  zeeStop* stop = new zeeStop(arduino, cBreakTime, finished, motors);
  //A turn Left will make up two parts, a turnLeft and smallTurnLeft.
  zeeTurnLeft* turnLeft = new zeeTurnLeft(arduino, moveTime - cSmallTurnTime, stop, motors);
  zeeTurnRight* turnRight = new zeeTurnRight(arduino, moveTime - cSmallTurnTime, turnLeft, motors);
  zeeGoStraight* straight = new zeeGoStraight(arduino, moveTime, turnRight, motors);
  zeeSmallTurnLeft* smallTurnLeft = new zeeSmallTurnLeft(arduino, cSmallTurnTime, straight, motors);
  zeeSmallTurnRight* smallTurnRight = new zeeSmallTurnRight(arduino, cSmallTurnTime, smallTurnLeft, motors);
  zeeGoCoast* coast = new zeeGoCoast(arduino, cSmallTurnTime, smallTurnRight, motors);

  zeeStart* start = new zeeStart(arduino, cSmallTurnTime, zeeMoveRobot, motors);
  /*we return the last moverobot in our chain...as this will need to be freed(delete).  This will cause
  a cascade of deletes through the destructor.  If you add to this chain, make sure the last in the chain is
  returned and then delete called when it needs to be cleaned up.
  */
  return start;
}