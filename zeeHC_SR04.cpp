#include "zeeHC_SR04.h"

//constant that is speed of sound divided by half
const long _uso = 58.0;

zeeHC_SR04_Sensor::zeeHC_SR04_Sensor(int measureSamples, int measureSampleDelay, int sonicSlop)
  :_measureSamples(measureSamples), _measureSampleDelay(measureSampleDelay), _sonicSlop(sonicSlop)
{
}

zeeHC_SR04_Sensor::zeeHC_SR04_Sensor()
{
}

zeeHC_SR04_Sensor::~zeeHC_SR04_Sensor()
{
}

bool zeeHC_SR04_Sensor::IsEqual(long diff)
{
  bool isEqual;

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
  Serial.println("DistanceRF: ");
  Serial.print(distanceRf);
  Serial.println(" mm");

  Serial.println("DistanceRR: ");
  Serial.print(distanceRr);
  Serial.println(" mm");

  return distanceRf - distanceRr;
}

long zeeHC_SR04_Sensor::GetDistanceMm(int trigPin)
{
  long measureSum = 0;
  for (int i = 0; i < _measureSamples; i++)
  {
    delay(_measureSampleDelay);
    measureSum += GetSingleDistanceMm(trigPin);
  }
  return measureSum / _measureSamples;
}

long zeeHC_SR04_Sensor::GetSingleDistanceMm(int trigPin)
{
  long duration, distance;
  int echoPin = trigPin + 1;
  //we turn on the US_pulse
  digitalWrite(trigPin, HIGH);
  //wait for 11 µs
  delayMicroseconds(11);
  //we turn off the US_pulse
  digitalWrite(trigPin, LOW);
  //we then read the echo of the US_Pulse...note this is returned in MicroSeconds
  duration = pulseIn(echoPin, HIGH);
  distance = (long)(((float)duration / _uso) * 10.0);
  return distance;
}