#include "zeeHC_SR04.h"

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
  arduino->pinMode(_triggerPin, OUTPUT);
  arduino->pinMode(_echoPin, INPUT);
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
      _arduino->delay(_measureSampleDelay);
    DoExecute();
    measureSum += GetSingleDistanceMm();
  }

  return measureSum / _measureSamples;
}

long zeeHC_SR04_Sensor::GetSingleDistanceMm()
{
  if (IsExecuting())
    return 0;
  return _distance + _offset;
}

void zeeHC_SR04_Sensor::DoExecute()
{
  long duration, distance;
  //we turn on the UltraSonic_pulse
  _arduino->digitalWrite(_triggerPin, HIGH);
  //wait for 11 µs
  _arduino->delayMicroseconds(11);
  //we turn off the UltraSonic_pulse
  _arduino->digitalWrite(_triggerPin, LOW);
  //we then read the echo of the UltraSonic_pulse...note this is returned in MicroSeconds
  duration = _arduino->pulseIn(_echoPin, HIGH);
  _distance = (long)(((float)duration / cUSo) * 10.0);
}

