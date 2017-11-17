#ifndef zeeRobotMazeLogic_h
#define zeeRobotMazeLogic_h

#include "zeeHC_SR04.h"
#include "zeeMoveRobot.h"
#include "zeeLineReader.h"
#include "zeeExecute.h"

class zeeRobotMazeLogic : public zeeExecute
{
public:
  zeeRobotMazeLogic(zeeArduino* arduino, unsigned long executeLength, zeeHC_SR04_Sensor* sr04, zeeMoveRobot* moveRobot, zeeLineReader* lineReader, long distanceForwardDetectionMm);
  ~zeeRobotMazeLogic();

  static zeeMoveRobot* SetMoveRobots(zeeArduino* arduino, zeeMoveRobot* zeeMoveRobot, zeeMotors* motors, int moveTime);

  bool IsFinished();
protected:
  void DoExecute();
private:
  zeeHC_SR04_Sensor* _sr04;
  zeeMoveRobot* _moveRobot;
  zeeLineReader* _lineReader;
  long _distanceForwardDetectionMm;

  bool ObstacleForward(long distance);
};
#endif