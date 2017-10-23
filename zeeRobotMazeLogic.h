#ifndef zeeRobotMazeLogic_h
#define zeeRobotMazeLogic_h

#include "zeeHC_SR04.h"
#include "zeeMoveRobot.h"
#include "zeeLineReader.h"
#include "zeeExecute.h"

class zeeRobotMazeLogic : zeeExecute
{
public:
  zeeRobotMazeLogic(zeeHC_SR04_Sensor* sr04, zeeMoveRobot* moveRobot, zeeLineReader* lineReader, long distanceForwardDetectionMm);
  ~zeeRobotMazeLogic();

  static zeeMoveRobot* SetMoveRobots(zeeMoveRobot* zeeMoveRobot, int moveTime);

  bool IsFinished();
  void Execute();
private:
  zeeHC_SR04_Sensor* _sr04;
  zeeMoveRobot* _moveRobot;
  zeeLineReader* _lineReader;
  long _distanceForwardDetectionMm;

  bool ObstacleForward(long distance);
};
#endif