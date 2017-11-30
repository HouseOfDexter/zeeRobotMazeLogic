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

unsigned int zeeMoveRobot::Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots)
{  
  if (ShouldHandle(detection, isFinished, handled))
  {
    Execute();
    handled = IsHandled();
    robots = GetId();
  }
  robots = CallNextRobot(detection, isFinished, handled, robots);

  return robots;
}

unsigned int zeeMoveRobot::GetMoveTime()
{
  return _moveTime;
}

zeeMoveRobot * zeeMoveRobot::GetRobot()
{
  return _robot;
}

unsigned int zeeMoveRobot::CallNextRobot(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots)
{
  //we call our chained robot to see if it needs to handle the request
  zeeMoveRobot* nextRobot = GetRobot();
  if (nextRobot != NULL)
    robots = nextRobot->Handle(detection, isFinished, handled, robots);
  return robots;
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

unsigned int zeeDecoratorLed::Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots)
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
  robots = robots | GetId();
  robots = CallNextRobot(detection, isFinished, handled, robots);
  return robots;
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

unsigned int zeeDecoratorPrintLn::Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots)
{
  Print("ObstacleForward: ", detection.GetObstacleForward(), "");
  Print("IsEqual: ", detection.GetIsEqual(), "");
  Print("DetectLine: ", detection.GetDetectLine(), "");
  Print("DiffBetweenRightSensors: ", detection.GetDiffBetweenRightSensors(), "mm");
  robots = robots | GetId();

  robots = CallNextRobot(detection, isFinished, handled, robots);
  return robots;
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

void zeeDecoratorPrintLn::Print(String description, long value, String extension)
{
  _arduino->println(description);
  _arduino->print(value);
  _arduino->println(extension);
}

void zeeDecoratorPrintLn::Print(String description, bool value, String extension)
{
  _arduino->println(description);
  _arduino->print(value);
  _arduino->println(extension);
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

unsigned int zeeDetectorRobot::Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots)
{
  detection = _detector->GetDetection();
  robots = robots | GetId();
  robots = CallNextRobot(detection, detection.GetDetectLine(), false, robots);
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
zeeMoveRobot * zeeMotorFactory::SetMoveRobots(zeeArduino * arduino, zeeMoveRobot * zeeMoveRobot, zeeMotors * motors, zeeDetector* detector, int moveTime)
{
  //zeeDecoratorTestLed *ledDecorator = new zeeDecoratorTestLed(moveTime, NULL, onOffLed);

  zeeFinished* finished = new zeeFinished(arduino, moveTime, zeeMoveRobot, motors);
  zeeStop* stop = new zeeStop(arduino, cBreakTime, finished, motors);
  //A turn Left will make up two parts, a turnLeft and smallTurnLeft.
  zeeTurnLeft* turnLeft = new zeeTurnLeft(arduino, moveTime - cSmallTurnTime, stop, motors);
  zeeTurnRight* turnRight = new zeeTurnRight(arduino, moveTime - cSmallTurnTime, turnLeft, motors);
  zeeGoStraight* straight = new zeeGoStraight(arduino, moveTime, turnRight, motors);
  zeeDetectorRobot* detectorRobot = new zeeDetectorRobot(detector->GetArduino(), 0, straight, detector);
  zeeSmallTurnLeft* smallTurnLeft = new zeeSmallTurnLeft(arduino, cSmallTurnTime, detectorRobot, motors);
  zeeSmallTurnRight* smallTurnRight = new zeeSmallTurnRight(arduino, cSmallTurnTime, smallTurnLeft, motors);
  zeeGoCoast* coast = new zeeGoCoast(arduino, cSmallTurnTime, smallTurnRight, motors);

  zeeStart* start = new zeeStart(arduino, cSmallTurnTime, zeeMoveRobot, motors);
  /*we return the last moverobot in our chain...as this will need to be freed(delete).  This will cause
  a cascade of deletes through the destructor.  If you add to this chain, make sure the last in the chain is
  returned and then delete called when it needs to be cleaned up.
  */
  return start;
}

/*
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
*/
String zeeMotorFactory::GetRobotString(unsigned int id)
{
  String robots = "";

  if (id & cTurnRight == cTurnRight)
    robots = robots + "Turn Right ";
  if (id & cTurnLeft == cTurnLeft)
    robots = robots + "Turn Left ";
  if (id & cSmallTurnRight == cSmallTurnRight)
    robots = robots + "Small Turn Right ";
  if (id & cSmallTurnLeft == cSmallTurnLeft)
    robots = robots + "Small Turn Left ";

  if (id & cGoStraight == cGoStraight)
    robots = robots + "Go Straight ";
  if (id & cGoCoast == cGoCoast)
    robots = robots + "Go Coast ";
  if (id & cStop == cStop)
    robots = robots + "Stop ";
  if (id & cStart == cStart)
    robots = robots + "Start ";
  if (id & cFinished == cFinished)
    robots = robots + "Finished ";
  if (id & cDecoratorLed == cDecoratorLed)
    robots = robots + "Decorator Led ";
  if (id & cDecoratorPrintLn == cDecoratorPrintLn)
    robots = robots + "Decorator Print Ln ";
  if (id & cDetectorRobot == cDetectorRobot)
    robots = robots + "Detector Robot ";
  return robots;
}
