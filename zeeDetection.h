#ifndef zeeDetection_h
#define zeeDetection_h

#include "zeeSonicSensors.h"
#include "zeeLineReader.h"

/*This is a value class, and should be readonly.  It is used by the zeeMoveRobot state class to decide if it should
handle moving.  The zeeRobotMazeLogic should create this class each time it uses the sensors, to decide how it
should move.*/
class zeeDetection
{
public:
  zeeDetection(bool lineDetected, bool obstacleForward, bool isEqual, long diffBetweenRightSensors);
  ~zeeDetection();

  bool GetDetectLine() { return _lineDetected; };
  bool GetObstacleForward() { return _obstacleForward; }
  bool GetIsEqual() { return _isEqual; }
  long GetDiffBetweenRightSensors() { return _diffBetweenRightSensors; }

private:
  bool _lineDetected;
  bool _obstacleForward;
  bool _isEqual;
  long _diffBetweenRightSensors;
};

/************************************************************************************/
class zeeDetector
{
public:
  zeeDetector(zeeSonicSensors* sonicSensors, zeeLineReader* lineReader, long distanceForwardDetectionMm);
  zeeDetection GetDetection();
  bool ObstacleForward();
  void Execute();
private:
  zeeSonicSensors* _sonicSensors;
  
  zeeLineReader* _lineReader;
  long _distanceForwardDetectionMm;
};
#endif
