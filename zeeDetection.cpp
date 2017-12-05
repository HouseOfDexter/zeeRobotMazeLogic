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

void zeeDetector::GetDetection(bool bypassWait = true)
{
  _sonicSensors->Execute(bypassWait);
  _lineReader->Execute(bypassWait);
}

bool zeeDetector::ObstacleForward()
{
  return _sonicSensors->ObstacleForward();
}

bool zeeDetector::DetectLine()
{
  return false;//_lineReader->DetectLeft() || _lineReader->DetectMiddle() || _lineReader->DetectRight();
}

bool zeeDetector::IsEqual()
{
  return _sonicSensors->IsEqual();
}

long zeeDetector::DiffBetweenRightSensors()
{
  return _sonicSensors->DifferenceBetweenRightSensorsInMM();
}

