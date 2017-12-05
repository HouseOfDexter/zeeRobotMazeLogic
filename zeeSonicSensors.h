#ifndef zeeSonicSensors_h
#define zeeSonicSensors_h
#include "zeeArduino.h"
#include "zeeExecute.h"
#include "zeeHC_SR04.h"

class zeeSSParam
{
public:
  zeeSSParam(zeeHC_SR04_Sensor *frontSensor, zeeHC_SR04_Sensor *rightFrontSensor, zeeHC_SR04_Sensor *rightRearSensor, int sonicSlop, unsigned int distanceForwardDetectionMm);
  ~zeeSSParam();
  zeeHC_SR04_Sensor* FrontSensor() { return _frontSensor; };
  zeeHC_SR04_Sensor* RightFrontSensor() { return _rightFrontSensor; };
  zeeHC_SR04_Sensor* RightRearSensor() { return _rightRearSensor; };
  int SonicSlop;
  unsigned int DistanceForwardDetectionMm;
private:
  zeeHC_SR04_Sensor *_frontSensor;
  zeeHC_SR04_Sensor *_rightFrontSensor;
  zeeHC_SR04_Sensor *_rightRearSensor;
};

/************************************************************************************/

class zeeSonicSensors: public zeeExecute
{
public:  
  zeeSonicSensors(zeeArduino* arduino, unsigned long executeLength, zeeSSParam param);
  virtual ~zeeSonicSensors();
  bool IsEqual();
  bool ObstacleForward();
  long DifferenceBetweenRightSensorsInMM();
protected:
  void DoExecute(bool bypassWait);
private:
  zeeArduino* _arduino;
  zeeHC_SR04_Sensor* _frontSensor;
  zeeHC_SR04_Sensor* _rightFrontSensor;
  zeeHC_SR04_Sensor* _rightRearSensor;
  int _sonicSlop = 0; //in mm, our sensor is not extremely accurate, we use slop to be acceptable values that are equal.
  unsigned int _distanceForwardDetectionMm = 0;
  
  //state variables
  long _frontDistance = 0;
  long _rightFrontDistance = cMaxLong;
  long _rightRearDistance = 0;

};
#endif

