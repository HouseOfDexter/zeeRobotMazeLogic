#include "zeeMoveRobot.h"
#include "stddef.h"
#include "zeeMotorPins.h"
#include "zeeArduino.h"
#include "zeeStateLED.h"
#include "Arduino.h"

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

unsigned int zeeMoveRobot::Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int robots)
{   
  Serial.print(GetId());
  Serial.println("-RobotId");

  bool shouldHandle = ShouldHandle(detection, isFinished, handled);

  Serial.print(shouldHandle);
  Serial.println("-shouldHandle");

  Serial.print(detection.GetIsEqual());
  Serial.println("-isEqual");
  Serial.print(detection.GetDiffBetweenRightSensors());
  Serial.println("-Diff");
  if (shouldHandle)
  {
    Execute(true);
    if (GetId() != cStop)
      digitalWrite(13, LOW);
    SetIsHandled(true);
    handled = ReportIsHandled();    
    robots = robots | GetId();
  }  

  return CallNextRobot(detection, isFinished, handled, robots);
}

unsigned int zeeMoveRobot::GetMoveTime()
{
  return _moveTime;
}

bool zeeMoveRobot::IsHandled()
{
  return _isHandled;
}

zeeMoveRobot * zeeMoveRobot::GetRobot()
{
  return _robot;
}

unsigned int zeeMoveRobot::CallNextRobot(zeeDetection detection, bool isFinished, bool handled, unsigned int robots)
{
  unsigned int robotIds = robots;
  //we call our chained robot to see if it needs to handle the request
  zeeMoveRobot* nextRobot = GetRobot();
  if (nextRobot == NULL) 
  {
    zeeMoveRobot* robot = zeeMotorFactory::GetRobot(robots & _defaultBitMask, this);
    //if (robot != NULL)
    //  delay(robot->GetMoveTime());
  }
  else 
  {
    robots = nextRobot->Handle(detection, isFinished, handled, robots);
  }
    
  return robots;
}

bool zeeMoveRobot::ReportIsHandled()
{
  return true;
}

void zeeMoveRobot::SetIsHandled(bool value)
{
  _isHandled = value;
}

/************************************************************************************/

zeeDecoratorLed::zeeDecoratorLed(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* robot, zeeStateLED* leds)
  : zeeMoveRobot(arduino, executeLength, robot, NULL)
{  
  _leds = leds;
  _defaultBitMask = c2ndRobotCallMask;
}

zeeDecoratorLed::~zeeDecoratorLed()
{
}

unsigned int zeeDecoratorLed::Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int robots)
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
  delay(500);
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

void zeeDecoratorLed::DoExecute(bool bypassWait)
{
  Serial.println("zeeDecoratorLed::DoExecute");
}

bool zeeDecoratorLed::ReportIsHandled()
{
  return false;
}

/************************************************************************************/

zeeTurnRight::zeeTurnRight(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{
  _defaultBitMask = c2ndRobotCallMask;
}

zeeTurnRight::~zeeTurnRight()
{
}

void zeeTurnRight::DoExecute(bool bypassWait)
{  
  Serial.println("zeeTurnRight::DoExecute");
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
  _defaultBitMask = c2ndRobotCallMask;
}

zeeTurnLeft::~zeeTurnLeft()
{
}

void zeeTurnLeft::DoExecute(bool bypassWait)
{  
  Serial.println("zeeTurnLeft::DoExecute");
  _motors->TurnLeft();  
}

bool zeeTurnLeft::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{  
  return (!isFinished &&
    !detection.GetIsEqual() &&
    detection.GetDiffBetweenRightSensors() < 0) && 
    _motors->GetEnabled() &&
    !handled;
}

/************************************************************************************/

zeeGoStraight::zeeGoStraight(zeeArduino* arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  :zeeMoveRobot(arduino, moveTime, robot, motors)
{  
  _defaultBitMask = c2ndRobotCallMask;
}
zeeGoStraight::~zeeGoStraight()
{
}

void zeeGoStraight::DoExecute(bool bypassWait)
{   
  Serial.println("straight.DoExecute");
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
{  
  _defaultBitMask = c1stRobotCallMask;
}

zeeGoCoast::~zeeGoCoast()
{
}

void zeeGoCoast::DoExecute(bool bypassWait)
{ 
  Serial.println("zeeGoCoast::DoExecute");
  _motors->Coast();
}

bool zeeGoCoast::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{  
  return (!isFinished &&
    detection.GetIsEqual() &&
    !detection.GetObstacleForward()) &&
    _motors->GetEnabled() &&
    !handled &&
    false;//can't figure why we would coast
}

/************************************************************************************/

zeeStop::zeeStop(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors * motors)
  :zeeMoveRobot(arduino, moveTime, robot, motors)
{  
  _defaultBitMask = c2ndRobotCallMask;
}

zeeStop::~zeeStop()
{
}

void zeeStop::DoExecute(bool bypassWait)
{
  digitalWrite(13, HIGH);
  Serial.println("zeeStop::DoExecute");
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
  _defaultBitMask = c1stRobotCallMask;
}

zeeStart::~zeeStart()
{
}

void zeeStart::DoExecute(bool bypassWait)
{  
  Serial.println("zeeStart::DoExecute");
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
  _defaultBitMask = c2ndRobotCallMask;
}

zeeFinished::~zeeFinished()
{
}

void zeeFinished::DoExecute(bool bypassWait)
{  
  Serial.println("zeeFinished::DoExecute");
  _motors->SetEnabled(false);
  _motors->DisableMotors();
}

bool zeeFinished::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
{
  return  false;
    //temp
    //detection.GetDetectLine();
}

/************************************************************************************/

zeeSmallTurnLeft::zeeSmallTurnLeft(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeMotors* motors)
  : zeeMoveRobot(arduino, moveTime, robot, motors)
{  
  _defaultBitMask = c1stRobotCallMask;
}

zeeSmallTurnLeft::~zeeSmallTurnLeft()
{
}

void zeeSmallTurnLeft::DoExecute(bool bypassWait)
{ 
  Serial.println("zeeSmallTurnLeft::DoExecute");
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
  _defaultBitMask = c1stRobotCallMask;
}

zeeSmallTurnRight::~zeeSmallTurnRight()
{
}

void zeeSmallTurnRight::DoExecute(bool bypassWait)
{  
  Serial.println("zeeSmallTurnRight::DoExecute");
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

//zeeDecoratorPrintLn::zeeDecoratorPrintLn(zeeArduino* arduino, int moveTime, zeeMoveRobot* robot, zeeMotors* motors)
//  : zeeMoveRobot(arduino, moveTime, robot, motors)
//{
//}
//
//zeeDecoratorPrintLn::~zeeDecoratorPrintLn()
//{
//}
//
//unsigned int zeeDecoratorPrintLn::Handle(zeeDetection detection, bool isFinished, bool handled, unsigned int &robots)
//{
//  robots = robots | GetId();
//  _detection = detection;
//
//  robots = CallNextRobot(detection, isFinished, handled, robots);
//  return robots;
//}
//
//bool zeeDecoratorPrintLn::IsHandled()
//{
//  return false;
//}
//
//void zeeDecoratorPrintLn::DoExecute()
//{ 
//  _arduino->Println("OF");
//  _arduino->Print(_detection.GetObstacleForward());
//  _arduino->Println(" ");
//  _arduino->Println("Equal");
//  _arduino->Print(_detection.GetIsEqual());
//  _arduino->Println(" ");
//  _arduino->Println("diff");
//  _arduino->Print(_detection.GetDiffBetweenRightSensors());
//  _arduino->Println("mm");
//}
//
//bool zeeDecoratorPrintLn::ShouldHandle(zeeDetection detection, bool isFinished, bool handled)
//{
//  return true;
//}
//
//void zeeDecoratorPrintLn::Print(const String &description, long value, const String &extension)
//{
//  _arduino->Println(description);
//  _arduino->Print(value);
//  _arduino->Println(extension);
//}
//
//void zeeDecoratorPrintLn::Print(const String &description, bool value, const String &extension)
//{
//  _arduino->Println(description);
//  _arduino->Print(value);
//  _arduino->Println(extension);
//}

/************************************************************************************/

zeeDetectorRobot::zeeDetectorRobot(zeeArduino * arduino, int moveTime, zeeMoveRobot * robot, zeeDetector* detector, unsigned int bitMask)
  : zeeMoveRobot(arduino, moveTime, robot, NULL)
{
  _detector = detector;
  _defaultBitMask = c1stRobotCallMask;
}

zeeDetectorRobot::~zeeDetectorRobot()
{
}

unsigned int zeeDetectorRobot::Handle(const zeeDetection detection, bool isFinished, bool handled, unsigned int robots)
{ 
  zeeMoveRobot* robot = zeeMotorFactory::GetRobot(robots & _bitMask, this);
//  if (robot != NULL)
//    delay(robot->GetMoveTime());
  _detector->GetDetection();
  zeeDetection newdetection = zeeDetection(_detector->DetectLine(), _detector->ObstacleForward(), _detector->IsEqual(), _detector->DiffBetweenRightSensors());
  robots = robots | GetId();
  
  return CallNextRobot(newdetection, newdetection.GetDetectLine(), false, robots);
}

bool zeeDetectorRobot::ShouldHandle(const zeeDetection detection, bool isFinished, bool handled)
{
  return true;
}

void zeeDetectorRobot::DoExecute(bool bypassWait)
{  
  Serial.println("zeeDetectorRobot::DoExecute");
}

bool zeeDetectorRobot::ReportIsHandled()
{
  return false;
}

/************************************************************************************/
zeeMoveRobot * zeeMotorFactory::SetMoveRobots(zeeArduino * arduino, zeeArduino * nowait, zeeMoveRobot * moveRobot, zeeMotors * motors, zeeDetector* detector, int moveTime)
{
  zeeFinished* finished = new zeeFinished(nowait, 0, moveRobot, motors);  
  zeeGoStraight* straight = new zeeGoStraight(arduino, moveTime, finished, motors);
  zeeStop* stop = new zeeStop(arduino, cBreakTime - cSmallTurnTime, straight, motors);
  zeeTurnLeft* turnLeft = new zeeTurnLeft(arduino, moveTime - cSmallTurnTime, stop, motors);
  zeeTurnRight* turnRight = new zeeTurnRight(arduino, moveTime - cSmallTurnTime, turnLeft, motors);

  //the detector allows us to get a new detection in the middle of our chain
  
//  zeeDetectorRobot* smallDetectorRobot = new zeeDetectorRobot(nowait, 0, straight, detector, c1stRobotCallMask);
//  zeeSmallTurnLeft* smallTurnLeft = new zeeSmallTurnLeft(arduino, cSmallTurnTime, smallDetectorRobot, motors);
//  zeeSmallTurnRight* smallTurnRight = new zeeSmallTurnRight(arduino, cSmallTurnTime, smallTurnLeft, motors);
//  zeeGoCoast* coast = new zeeGoCoast(arduino, cSmallTurnTime, smallTurnRight, motors);
//  zeeStart* start = new zeeStart(nowait, 0, coast, motors);  
  
  /*we return the last moverobot in our chain...as this will need to be freed(delete).  This will cause
  a cascade of deletes through the destructor.  If you add to this chain, make sure the last in the chain is
  returned and then delete called when it needs to be cleaned up.
  */  
  return turnRight;
}

zeeMoveRobot * zeeMotorFactory::GetRobot(unsigned int id, zeeMoveRobot* robot)
{
  //note GetRobot will return the first Robot that has an id(id can be multiple robots with flags flipped)
  if (robot == NULL || robot->GetId() & id == id)
  {
    Serial.print(id);
    Serial.println(" found Robot");
    return robot;
  }
  else
  {
    //recursive call to find the robot in the chain
    robot = zeeMotorFactory::GetRobot(id, robot->GetRobot());
  }  
}




