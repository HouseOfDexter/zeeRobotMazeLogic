#include "zeeHC_SR04.h"

//constant that is speed of sound divided by half
const long cUSo = 58.0;

zeeHC_SR04_Sensor::zeeHC_SR04_Sensor(zeeArduino* arduino, int measureSamples, int measureSampleDelay, int sonicSlop)
  :_arduino(arduino), _measureSamples(measureSamples), _measureSampleDelay(measureSampleDelay), _sonicSlop(sonicSlop)
{
}

zeeHC_SR04_Sensor::zeeHC_SR04_Sensor(zeeArduino* arduino)
  :_arduino(arduino)
{
}

zeeHC_SR04_Sensor::~zeeHC_SR04_Sensor()
{
}

bool zeeHC_SR04_Sensor::IsEqual(long diff)
{
  bool isEqual;
  /*Need to move this to a decorator class*/
  Serial.println("Difference: ");
  Serial.print(diff);
  Serial.println(" mm");

  if (diff < _sonicSlop && diff > -_sonicSlop) {
    isEqual = true;
  }
  else
  {
    isEqual = false;
  }
  return isEqual;
}

long zeeHC_SR04_Sensor::DiffInMM(long distanceRf, long distanceRr)
{
  /*Need to move this to a decorator class*/
  Serial.println("DistanceRF: ");
  Serial.print(distanceRf);
  Serial.println(" mm");

  Serial.println("DistanceRR: ");
  Serial.print(distanceRr);
  Serial.println(" mm");

  return distanceRf - distanceRr;
}

long zeeHC_SR04_Sensor::GetDistanceMm(int trigPin, int offset = 0)
{
  long measureSum = 0;
  if (_measureSamples == 0)
    _measureSamples = 1;
  for (int i = 1; i <= _measureSamples; i++)
  {
    /*We delay taking a reading if not the first reading*/
    if (_measureSamples > 1)
      delay(_measureSampleDelay);
    measureSum += GetSingleDistanceMm(trigPin, offset);
  }

  return measureSum / _measureSamples;
}

long zeeHC_SR04_Sensor::GetSingleDistanceMm(int trigPin, int offset = 0)
{
  long duration, distance;
  int echoPin = trigPin + 1;
  //we turn on the UltraSonic_pulse
  _arduino->digitalWrite(trigPin, HIGH);
  //wait for 11 µs
  _arduino->delayMicroseconds(11);
  //we turn off the UltraSonic_pulse
  _arduino->digitalWrite(trigPin, LOW);
  //we then read the echo of the UltraSonic_pulse...note this is returned in MicroSeconds
  duration = _arduino->pulseIn(echoPin, HIGH);
  distance = (long)(((float)duration / cUSo) * 10.0);
  return distance + offset;
}