#line 2 "AlgernonTest.ino"
#include "zeeArduino.h"
#include "zeeHC_SR04.h"
#include <ArduinoUnit.h>

void setup()
{
  Serial.begin(9600);
}

test(distance) 
{
  int executeLength = 100;
  unsigned int updateInterval = 10;
  unsigned int intervalRunTime = 10;
  zeeArduino* nowait = new zeeArduino(0, 0);
  zeeHC_SR04_Sensor* f_sr04 = new zeeHC_SR04_Sensor(nowait, 0, zeeHCSR04param(cEchoRFPin, cTrigRFPin, cMeasureSamples, cSampleMeasurementDelay));
  f_sr04->Execute(false);
  long actual = f_sr04->GetDistanceMm();
  
  long expected = 1;
  assertMoreOrEqual(actual, expected);
  delete nowait;
  delete f_sr04;
}

void loop()
{
  Test::run();
  
}
