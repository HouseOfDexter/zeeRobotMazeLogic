#ifndef zeeDetection_h
#define zeeDetection_h

#include "zeeArduino.h"
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
  bool GetObstacleForward() { return _obstacleForward; };
  bool GetIsEqual() { return _isEqual; }
  long GetDiffBetweenRightSensors() { return _diffBetweenRightSensors; }

private:
  bool _lineDetected = false;
  bool _obstacleForward = false;
  bool _isEqual = false;
  long _diffBetweenRightSensors = 0;
};

/************************************************************************************/
class zeeDetector
{
public:
  zeeDetector(zeeArduino* arduino, zeeSonicSensors* sonicSensors, zeeLineReader* lineReader, long distanceForwardDetectionMm);
  virtual void GetDetection(bool bypassWait = true);
  bool ObstacleForward(); 
  bool DetectLine();  
  bool IsEqual();
  long DiffBetweenRightSensors();

  zeeArduino* GetArduino() { return _arduino; }
private:
  zeeArduino* _arduino;
  zeeSonicSensors* _sonicSensors;  
  zeeLineReader* _lineReader;
  long _distanceForwardDetectionMm = 0;
};
#endif

