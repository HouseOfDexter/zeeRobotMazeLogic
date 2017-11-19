#include "zeeSonicSensors.h"

zeeSSParam::zeeSSParam(zeeHC_SR04_Sensor * frontSensor, zeeHC_SR04_Sensor * rightFrontSensor, zeeHC_SR04_Sensor * rightRearSensor, int sonicSlop, unsigned int distanceForwardDetectionMm)
{
  FrontSensor = frontSensor;
  RightFrontSensor = rightFrontSensor;
  RightRearSensor = rightRearSensor;
  SonicSlop = sonicSlop;
  DistanceForwardDetectionMm = distanceForwardDetectionMm;
}

zeeSSParam::~zeeSSParam()
{
}

zeeSonicSensors::zeeSonicSensors(zeeArduino* arduino, unsigned long executeLength, zeeSSParam param)
  :zeeExecute(arduino, executeLength)
{
  _frontSensor = param.FrontSensor;
  _rightFrontSensor = param.RightFrontSensor;
  _rightRearSensor = param.RightRearSensor;
  _sonicSlop = param.SonicSlop;
  _distanceForwardDetectionMm = param.DistanceForwardDetectionMm;
}

zeeSonicSensors::~zeeSonicSensors()
{
}

bool zeeSonicSensors::IsEqual()
{
  bool isEqual = true;
  long diff = DifferenceBetweenRightSensorsInMM();

  if (!IsExecuting() && (diff > _sonicSlop && diff < -_sonicSlop))
    isEqual = false;

  return isEqual;
}

long zeeSonicSensors::DifferenceBetweenRightSensorsInMM()
{
  long diff = 0;
  if (!IsExecuting())
    diff = _rightFrontDistance - _rightRearDistance;
  return diff;
}

void zeeSonicSensors::DoExecute()
{
  _frontSensor->Execute();
  _rightFrontSensor->Execute();
  _rightRearSensor->Execute();
  //front sensor
  _frontDistance = _frontSensor->GetDistanceMm();
  //right forward sensor
  _rightFrontDistance = _rightFrontSensor->GetDistanceMm();
  //right rear sensor
  _rightRearDistance = _rightRearSensor->GetDistanceMm();
}

bool zeeSonicSensors::ObstacleForward()
{
  bool obstacleForward = true;
  if (!IsExecuting() && _frontDistance > _distanceForwardDetectionMm)
    obstacleForward = false;  
  
  return obstacleForward;  
}

