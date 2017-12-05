#ifndef zeeHC_SR04_Sensor_h
#define zeeHC_SR04_Sensor_h

#include "zeeArduino.h"
#include "zeeSensorPins.h"
#include "zeeExecute.h"

const unsigned long cMaxLong = 2147483647;

class zeeHCSR04param 
{
public:
  zeeHCSR04param(unsigned int echoPin, unsigned int triggerPin, int measureSamples, int measureSampleDelay, unsigned int detectionRange, unsigned int offset = 0);
  ~zeeHCSR04param();
  unsigned int EchoPin = 0;
  unsigned int TriggerPin = 0;
  int MeasureSamples = 0;
  int MeasureSampleDelay = 0;
  unsigned int DetectionRange = 0;
  unsigned int Offset = 0;

};

/************************************************************************************/

class zeeHC_SR04_Sensor: public zeeExecute
{
public:  
  zeeHC_SR04_Sensor(zeeArduino* arduino, unsigned long executeLength, zeeHCSR04param param);
  virtual ~zeeHC_SR04_Sensor();
    
  long GetDistanceMm();
  long GetSingleDistanceMm();
protected:
  void DoExecute(bool bypassWait);
  unsigned long GetDistance(unsigned long duration);
  unsigned long GetTimeOutDuration(unsigned long distance);
private:
  zeeArduino* _arduino;
  unsigned int _echoPin = 0;
  unsigned int _triggerPin = 0;
  int _measureSamples = cMeasureSamples; //how many samples to read and take average of the readings
  int _measureSampleDelay = cSampleMeasurementDelay; //in ms
  unsigned int _detectionRange = 0;
  
  unsigned int _offset = 0;
  unsigned long _distance = 0;
};
#endif

