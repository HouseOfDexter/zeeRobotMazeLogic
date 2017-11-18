#ifndef zeeHC_SR04_Sensor_h
#define zeeHC_SR04_Sensor_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "zeeArduino.h"
#include "zeeSensorPins.h"
#include "zeeExecute.h"

class zeeHCSR04param 
{
public:
  zeeHCSR04param(unsigned int echoPin, unsigned int triggerPin, int measureSamples, int measureSampleDelay, unsigned int offset = 0);
  unsigned int EchoPin;
  unsigned int TriggerPin;
  int MeasureSamples;
  int MeasureSampleDelay;
  unsigned int Offset;
};

class zeeHC_SR04_Sensor: public zeeExecute
{
public:  
  zeeHC_SR04_Sensor(zeeArduino* arduino, unsigned long executeLength, zeeHCSR04param param);
  ~zeeHC_SR04_Sensor();
    
  long GetDistanceMm();
  long GetSingleDistanceMm();
protected:
  void DoExecute();
private:
  zeeArduino* _arduino;
  unsigned int _echoPin;
  unsigned int _triggerPin;
  int _measureSamples = cMeasureSamples; //how many samples to read and take average of the readings
  int _measureSampleDelay = cSampleMeasurementDelay; //in ms
  
  unsigned int _offset;
  long _distance;
};
#endif
