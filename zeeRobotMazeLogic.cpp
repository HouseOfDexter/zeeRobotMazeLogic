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
  _arduino->println("zeeRobotMazeLogic::AfterExecute");
  zeeDetection detection = _detector->GetDetection();
  _isFinished = detection.GetDetectLine();
  unsigned int robots = 0;
  robots = _moveRobot->Handle(detection, _isFinished, false, robots);
  String robotStr = zeeMotorFactory::GetRobotString(robots);
  _arduino->println("RobotStr: " + robotStr);
}

bool zeeRobotMazeLogic::IsFinished()
{
  return _isFinished;
}

void zeeRobotMazeLogic::DoExecute()
{
  _detector->Execute();
}



