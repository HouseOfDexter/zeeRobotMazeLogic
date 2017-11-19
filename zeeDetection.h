#ifndef zeeDetection_h
#define zeeDetection_h

/*This is a value class, and should be readonly.  It is used by the zeeMoveRobot state class to decide if it should
handle moving.  The zeeRobotMazeLogic should create this class each time it uses the sensors, to decide how it
should move.*/
class zeeDetection
{
public:
  zeeDetection(bool lineDetected, bool obstacleForward, bool isEqual, long diffBetweenRightSensors);
  virtual ~zeeDetection();

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

#endif
