#include "zeeRobotMazeLogic.h"
#include "zeeSensorPins.h"

/*This is a State Manager for zeeMoveRobot, which are state objects for moving the Robot*/

zeeRobotMazeLogic::zeeRobotMazeLogic(zeeArduino* arduino, unsigned long executeLength, zeeMoveRobot* moveRobot,  zeeDetector* detector)
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
  zeeDetection detection = _detector->GetDetection();
  _isFinished = detection.GetDetectLine();
  _moveRobot->Handle(detection, _isFinished, false);  
}

bool zeeRobotMazeLogic::IsFinished()
{
  return _isFinished;
}

void zeeRobotMazeLogic::DoExecute()
{
  _detector->Execute();
}


