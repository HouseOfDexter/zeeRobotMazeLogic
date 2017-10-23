#include "zeeDetection.h"

zeeDetection::zeeDetection(bool lineDetected, bool obstacleForward, bool isEqual, long diffBetweenRightSensors)
  :_lineDetected(lineDetected), _obstacleForward(obstacleForward), _isEqual(isEqual), _diffBetweenRightSensors(diffBetweenRightSensors)
{
}

zeeDetection::~zeeDetection()
{
}