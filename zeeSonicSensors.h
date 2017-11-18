#include "zeeExecute.h"
#include "zeeArduino.h"
#include "zeeHC_SR04.h"

class zeeSSParam
{
public:
  zeeSSParam(zeeHC_SR04_Sensor* frontSensor, zeeHC_SR04_Sensor* rightFrontSensor, zeeHC_SR04_Sensor* rightRearSensor, int sonicSlop, unsigned int distanceForwardDetectionMm);
  zeeHC_SR04_Sensor* FrontSensor;
  zeeHC_SR04_Sensor* RightFrontSensor;
  zeeHC_SR04_Sensor* RightRearSensor;
  int SonicSlop;
  unsigned int DistanceForwardDetectionMm;
};

class zeeSonicSensors: public zeeExecute
{
public:
  zeeSonicSensors(zeeArduino* arduino, unsigned long executeLength, zeeSSParam param);
  ~zeeSonicSensors();
  bool IsEqual();
  bool ObstacleForward();
  long DifferenceBetweenRightSensorsInMM();
protected:
    void DoExecute();
private:
  zeeArduino* _arduino;
  zeeHC_SR04_Sensor* _frontSensor;
  zeeHC_SR04_Sensor* _rightFrontSensor;
  zeeHC_SR04_Sensor* _rightRearSensor;
  int _sonicSlop; //in mm, our sensor is not extremely accurate, we use slop to be acceptable values that are equal.
  unsigned int _distanceForwardDetectionMm;
  
  //state variables
  long _frontDistance = 0;
  long _rightFrontDistance = 0;
  long _rightRearDistance = 0;

};

