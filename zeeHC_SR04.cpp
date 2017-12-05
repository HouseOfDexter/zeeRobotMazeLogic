#include "zeeHC_SR04.h"
#include "Arduino.h"
//constant that is speed of sound
// 340m/s = .34mm/µs(millimeter/microsecond)
const float cUSo = .34;
const float cUS = 5.8;//µs/58cm

zeeHCSR04param::zeeHCSR04param(unsigned int echoPin, unsigned int triggerPin, int measureSamples, int measureSampleDelay, unsigned int detectionRange, unsigned int offset)
{
  EchoPin = echoPin;
  TriggerPin = triggerPin;
  MeasureSamples = measureSamples;
  MeasureSampleDelay = measureSampleDelay;
  DetectionRange = detectionRange;
  Offset = offset;
}

zeeHCSR04param::~zeeHCSR04param()
{
}

zeeHC_SR04_Sensor::zeeHC_SR04_Sensor(zeeArduino* arduino, unsigned long executeLength, zeeHCSR04param param)
  : zeeExecute(arduino, executeLength)
{
  _echoPin = param.EchoPin;
  _triggerPin = param.TriggerPin;
  _measureSamples = param.MeasureSamples;
  _measureSampleDelay = param.MeasureSampleDelay;  
  _detectionRange = param.DetectionRange;
  _offset = param.Offset;
  pinMode(_triggerPin, OUTPUT);  
  pinMode(_echoPin, INPUT);
}

zeeHC_SR04_Sensor::~zeeHC_SR04_Sensor()
{
}

long zeeHC_SR04_Sensor::GetDistanceMm()
{
  long measureSum = 0;
  if (_measureSamples == 0)
    _measureSamples = 1;
  for (int i = 1; i <= _measureSamples; i++)
  {
    /*We delay taking a reading if not the first reading*/
    if (_measureSamples > 1)
      delayMicroseconds(_measureSampleDelay);      
    DoExecute(true);    
    measureSum += GetSingleDistanceMm();
  }
  return measureSum / _measureSamples;
}

long zeeHC_SR04_Sensor::GetSingleDistanceMm()
{
  //bug potential...we are going from unsigned long to long
  if (IsExecuting() || _distance == 0)
    return cMaxLong;
  return _distance + _offset;
}

unsigned long zeeHC_SR04_Sensor::GetDistance(unsigned long duration)
{//Note duration is in MicroSeconds µs and Distance is returned in Millimeters mm
  //t=s/v and s=t*v
  //half the distance to the echo
  float distance = (duration * cUSo) / 2;
  unsigned long rtn = (unsigned long)distance;
  return rtn;
}

unsigned long zeeHC_SR04_Sensor::GetTimeOutDuration(unsigned long distance)
{
  //t=s/v
  //note distance will be the full distance traveled of the pulse
  float duration = distance * 3 * 2;//it takes ~3µs to travel 1mm and we have to travel there and back
  unsigned long rtn = (unsigned long) duration + 500;//add a little slop
  Serial.print(rtn);
  Serial.println(" TimeOut");
  return rtn;
}

void zeeHC_SR04_Sensor::DoExecute(bool bypassWait)
{
  unsigned long duration = 0;
  unsigned long timeout = 0;

  if (_detectionRange > 0)
    timeout = GetTimeOutDuration(_detectionRange) ;
  
  digitalWrite(_triggerPin, LOW);
  //delayMicroseconds is  only accurate at 3µs or higher
  delayMicroseconds(3);  
  /*https://www.arduino.cc/reference/en/language/functions/time/delaymicroseconds/
  Notes and Warnings

  This function works very accurately in the range 3 microseconds and up. We cannot assure that delayMicroseconds will perform precisely for smaller delay-times.
*/
  

  //we turn on the UltraSonic_pulse
  digitalWrite(_triggerPin, HIGH);
  
  //wait for 10 µs  
  delayMicroseconds(10);  
  //we turn off the UltraSonic_pulse
  digitalWrite(_triggerPin, LOW);  

  //we then read the echo of the UltraSonic_pulse...note this is returned in µs MicroSeconds
  //Note this sits in a Delay for ever long  it takes to get the pulse back
  duration = timeout == 0 ? pulseIn(_echoPin, HIGH): pulseIn(_echoPin, HIGH, timeout);
  
  _distance = GetDistance(duration);  
  Serial.print(duration);
  Serial.println(" duration");
  Serial.print(_distance);
  Serial.println(" distance");
}


