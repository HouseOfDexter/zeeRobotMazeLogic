#include "zeeRobotMazeLogic.h"
#include "zeeSensorPins.h"

/*This is a State Manager for zeeMoveRobot, which are state objects for moving the Robot*/

const int cSmallTurnTime = 50;
const int cBreakTime = 100;

zeeRobotMazeLogic::zeeRobotMazeLogic(zeeArduino* arduino, unsigned long executeLength, zeeHC_SR04_Sensor* sr04, zeeMoveRobot* moveRobot, zeeLineReader* lineReader, long distanceForwardDetectionMm)
  : zeeExecute(arduino, executeLength)
{
  _sr04 = sr04;
  _moveRobot = moveRobot;
  _lineReader = lineReader;
  _distanceForwardDetectionMm = distanceForwardDetectionMm;
}

zeeRobotMazeLogic::~zeeRobotMazeLogic()
{
}

zeeMoveRobot* zeeRobotMazeLogic::SetMoveRobots(zeeArduino* arduino, zeeMoveRobot* zeeMoveRobot, zeeMotors* motors, int moveTime)
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
  /*we return the last moverobot in our chain...as this will need to be freed(delete).  This will cause
  a cascade of deletes through the destructor.  If you add to this chain, make sure the last in the chain is
  returned and then delete called when it needs to be cleaned up.
  */
  return smallTurnLeft;
}

bool zeeRobotMazeLogic::ObstacleForward(long distance)
{
  //long distance = GetDistanceMm(_trigForward, _echoForward);
  bool obstacleForward;
  if (distance < _distanceForwardDetectionMm)
  {
    obstacleForward = true;
  }
  else
  {
    obstacleForward = false;
  }
  return obstacleForward;
}

bool zeeRobotMazeLogic::IsFinished()
{
  return false;
}

void zeeRobotMazeLogic::DoExecute()
{
  //right forward sensor
  long distanceRF = _sr04->GetDistanceMm(cTrigRFPin);
  //right rear sensor
  long distanceRR = _sr04->GetDistanceMm(cTrigRRPin, 5);
  long differenceBetweenRightSensors = _sr04->DiffInMM(distanceRF, distanceRR);
  bool isEqual = _sr04->IsEqual(differenceBetweenRightSensors);
  //forward sensor
  long forwardSensor = _sr04->GetSingleDistanceMm(cTrigForwardPin);
  bool obstacleForward = ObstacleForward(forwardSensor);

  bool detectLine = _lineReader->DetectLine();

  zeeDetection* detection = new zeeDetection(detectLine, obstacleForward, isEqual, differenceBetweenRightSensors);
  _moveRobot->Handle(detection, detectLine);

  delete detection;
}