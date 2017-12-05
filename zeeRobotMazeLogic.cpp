#include "zeeRobotMazeLogic.h"
#include "zeeArduino.h"
#include "zeeMoveRobot.h"
#include "zeeDetection.h"
#include "Arduino.h"

/*This is a State Manager for zeeMoveRobot, which are state objects for moving the Robot*/

zeeRobotMazeLogic::zeeRobotMazeLogic(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* moveRobot, zeeDetector* detector)
  : zeeExecute(arduino, executeLength)
{
  _detector = detector;  
  _moveRobot = moveRobot;
}

zeeRobotMazeLogic::~zeeRobotMazeLogic()
{
}

void zeeRobotMazeLogic::AfterExecute()
{ 
  Serial.println("MazeLogic.AfterExecute");
  _detector->GetDetection(); 
  zeeDetection detection = zeeDetection(_detector->DetectLine(), _detector->ObstacleForward(), _detector->IsEqual(), _detector->DiffBetweenRightSensors());
  _isFinished = detection.GetDetectLine();  
  _robots = _moveRobot->Handle(detection, _isFinished, false, 0);
  Serial.print(_robots);
  Serial.println(" robotid");
}

bool zeeRobotMazeLogic::IsFinished()
{
  return false;
    //temp
    //_isFinished;
}

unsigned int zeeRobotMazeLogic::GetRobots()
{
  return _robots;
}

void zeeRobotMazeLogic::DoExecute(bool bypassWait)
{ 
}

