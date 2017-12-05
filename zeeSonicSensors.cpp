#include "zeeSonicSensors.h"
#include "Arduino.h"

zeeSSParam::zeeSSParam(zeeHC_SR04_Sensor *frontSensor, zeeHC_SR04_Sensor *rightFrontSensor, zeeHC_SR04_Sensor *rightRearSensor, int sonicSlop, unsigned int distanceForwardDetectionMm)
{
  SonicSlop = sonicSlop;
  DistanceForwardDetectionMm = distanceForwardDetectionMm;
  _frontSensor = frontSensor;
  _rightFrontSensor = rightFrontSensor;
  _rightRearSensor = rightRearSensor;
}

zeeSSParam::~zeeSSParam()
{
}

zeeSonicSensors::zeeSonicSensors(zeeArduino* arduino, unsigned long executeLength, zeeSSParam param)
  :zeeExecute(arduino, executeLength)
{
  _arduino = arduino;
  _frontSensor = param.FrontSensor();
  _rightFrontSensor = param.RightFrontSensor();
  _rightRearSensor = param.RightRearSensor();
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

  if (diff > _sonicSlop || diff < -_sonicSlop )
    isEqual = false;

  return isEqual;
}

long zeeSonicSensors::DifferenceBetweenRightSensorsInMM()
{
  long diff = cMaxLong;
  if (_rightFrontDistance != cMaxLong && _rightRearDistance != cMaxLong)
    diff = _rightFrontDistance - _rightRearDistance;
  return diff;
}

void zeeSonicSensors::DoExecute(bool bypassWait)
{
  unsigned long start = millis();
  _frontDistance = 0;
  _rightFrontDistance = 0;
  _rightRearDistance = 0;

  _frontSensor->Execute(bypassWait);
  _rightFrontSensor->Execute(bypassWait);
  _rightRearSensor->Execute(bypassWait);

  //front sensor
  _frontDistance = _frontSensor->GetSingleDistanceMm();
  //right forward sensor
  _rightFrontDistance = _rightFrontSensor->GetSingleDistanceMm();
  //right rear sensor
  _rightRearDistance = _rightRearSensor->GetSingleDistanceMm();
  unsigned long stop = millis();
  Serial.print(stop - start);
  Serial.println(" Sonic Sensor time");
  Serial.print(_frontDistance);
  Serial.println(" _frontDistance");
  Serial.print(_rightFrontDistance);
  Serial.println(" _rightFrontDistance");
  Serial.print(_rightRearDistance);
  Serial.println(" _rightRearDistance");
}

bool zeeSonicSensors::ObstacleForward()
{
  bool obstacleForward = true;
  if (!IsExecuting() && _frontDistance > _distanceForwardDetectionMm) 
  {    
    obstacleForward = false;
  }
  
  return obstacleForward;  
}


