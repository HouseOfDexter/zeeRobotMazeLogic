#ifndef zeeHC_SR04_Sensor_h
#define zeeHC_SR04_Sensor_h

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

#include "zeeSensorPins.h"

class zeeHC_SR04_Sensor
{
public:
  zeeHC_SR04_Sensor();
  zeeHC_SR04_Sensor(int measureSamples, int measureSampleDelay, int sonicSlop);
  ~zeeHC_SR04_Sensor();

  bool IsEqual(long diff);
  long DiffInMM(long distanceRf, long distanceRr);
  long GetDistanceMm(int trigPin);
  long GetSingleDistanceMm(int trigPin);
private:
  int _measureSamples = cMeasureSamples; //how many samples to read and take average of the readings
  int _measureSampleDelay = cSampleMeasurementDelay; //in ms
  int _sonicSlop = cSonicSlop; //in mm, our sensor is not extremely accurate, we use slop to be acceptable values that are equal.
};
#endif
