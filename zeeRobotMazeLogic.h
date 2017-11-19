#ifndef zeeRobotMazeLogic_h
#define zeeRobotMazeLogic_h

#include "zeeHC_SR04.h"
#include "zeeMoveRobot.h"
#include "zeeLineReader.h"
#include "zeeExecute.h"
#include "zeeSonicSensors.h"

class zeeRobotMazeLogic : public zeeExecute
{
public:
  zeeRobotMazeLogic(zeeArduino* arduino, unsigned long executeLength, zeeSonicSensors* sonicSensors, zeeMoveRobot* moveRobot, zeeLineReader* lineReader, long distanceForwardDetectionMm);
  virtual ~zeeRobotMazeLogic();

  static zeeMoveRobot* SetMoveRobots(zeeArduino* arduino, zeeMoveRobot* zeeMoveRobot, zeeMotors* motors, int moveTime);

  void AfterExecute();

  bool IsFinished();
protected:
  void DoExecute();
private:
  zeeSonicSensors* _sonicSensors;
  zeeMoveRobot* _moveRobot;
  zeeLineReader* _lineReader;
  long _distanceForwardDetectionMm;

  bool ObstacleForward();
};
#endif