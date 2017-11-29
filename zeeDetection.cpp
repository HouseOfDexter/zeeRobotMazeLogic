#include "zeeDetection.h"

zeeDetection::zeeDetection(bool lineDetected, bool obstacleForward, bool isEqual, long diffBetweenRightSensors)
  :_lineDetected(lineDetected), _obstacleForward(obstacleForward), _isEqual(isEqual), _diffBetweenRightSensors(diffBetweenRightSensors)
{
}

zeeDetection::~zeeDetection()
{
}

/************************************************************************************/

zeeDetector::zeeDetector(zeeArduino* arduino, zeeSonicSensors * sonicSensors, zeeLineReader * lineReader, long distanceForwardDetectionMm)
{
  _arduino = arduino;
  _sonicSensors = sonicSensors;  
  _lineReader = lineReader;
  _distanceForwardDetectionMm = distanceForwardDetectionMm;

}

zeeDetection zeeDetector::GetDetection()
{
  long differenceBetweenRightSensors = _sonicSensors->DifferenceBetweenRightSensorsInMM();
  bool isEqual = _sonicSensors->IsEqual();
  bool obstacleForward = _sonicSensors->ObstacleForward();
  bool detectLine = _lineReader->DetectLeft() && _lineReader->DetectMiddle() && _lineReader->DetectRight();

  return zeeDetection(detectLine, obstacleForward, isEqual, differenceBetweenRightSensors);
}

bool zeeDetector::ObstacleForward()
{
  return _sonicSensors->ObstacleForward();
}

void zeeDetector::Execute()
{
  _lineReader->Execute();
  _sonicSensors->Execute();
}
