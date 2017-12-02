#include "zeeHC_SR04.h"
#include "Arduino.h"
//constant that is speed of sound divided by half
const long cUSo = 58.0;

zeeHCSR04param::zeeHCSR04param(unsigned int echoPin, unsigned int triggerPin, int measureSamples, int measureSampleDelay, unsigned int offset)
{
  EchoPin = echoPin;
  TriggerPin = triggerPin;
  MeasureSamples = measureSamples;
  MeasureSampleDelay = measureSampleDelay;
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
  _offset = param.Offset;
  //arduino->PinMode(_triggerPin, OUTPUT);
  //arduino->PinMode(_echoPin, INPUT);
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
  int samples = 1;
  for (int i = 1; i <= _measureSamples; i++)
  {
    /*We delay taking a reading if not the first reading*/
    if (_measureSamples > 1)
      _arduino->Delay(_measureSampleDelay);
    DoExecute();
    long tempReading = GetSingleDistanceMm();
    if (tempReading != cMaxLong)
    {
      samples = i;
      measureSum += GetSingleDistanceMm();
    }
  }
  return measureSum / samples;
}

long zeeHC_SR04_Sensor::GetSingleDistanceMm()
{
  return _distance;
}

long zeeHC_SR04_Sensor::GetOffsetDistance(long distance) 
{
  unsigned long diff = cMaxLong;
  if (!IsExecuting())
    diff = distance + _offset;
  return diff;
}

long zeeHC_SR04_Sensor::GetDistance(unsigned long duration)
{
  float distance = (duration / cUSo) * 10.0;
  return (unsigned long)distance;
}

void zeeHC_SR04_Sensor::DoExecute()
{
  unsigned long duration = 0;
  //we turn on the UltraSonic_pulse

  //  _arduino->DigitalWrite(_triggerPin, HIGH);
  digitalWrite(_triggerPin, HIGH);
  //wait for 11 µs
  //_arduino->DelayMicroseconds(11);
  delayMicroseconds(11);
  //we turn off the UltraSonic_pulse
  //  _arduino->DigitalWrite(_triggerPin, LOW);
  digitalWrite(_triggerPin, LOW);
  //we then read the echo of the UltraSonic_pulse...note this is returned in MicroSeconds
  //  duration = _arduino->PulseIn(_echoPin, HIGH);
  duration = pulseIn(_echoPin, HIGH);
   
  long distance = GetDistance(duration);
  _distance = GetOffsetDistance(distance);
}

