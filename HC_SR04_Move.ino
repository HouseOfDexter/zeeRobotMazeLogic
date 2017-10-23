/*

*/
#include "zeeOnOffLED.h"
#include "zeeHC_SR04.h"
#include "zeeMoveRobot.h"
#include "zeeRobotMazeLogic.h"
#include "zeeLineReader.h"
#include "zeeSensorPins.h"

//default times in MS
const unsigned int cDelay = 250;
const unsigned int cMoveTime = 100;
const unsigned int cDistanceForwardDetection = 50;

void setup() {
  Serial.begin(9600);
  pinMode(cTrigForwardPin, OUTPUT);
  pinMode(cEchoForwardPin, INPUT);
  pinMode(cTrigRFPin, OUTPUT);
  pinMode(cEchoRFPin, INPUT);
  pinMode(cTrigRRPin, OUTPUT);
  pinMode(cEchoRRPin, INPUT);
  pinMode(cLedPin1, OUTPUT);
  pinMode(cLedPin2, OUTPUT);
}

void loop()
{
  //we use dependecy injection so we know when to free our memory
  zeeOnOffLED* onOffLed = new zeeOnOffLED(cLedPin1, cLedPin2);
  zeeHC_SR04_Sensor* sr04 = new zeeHC_SR04_Sensor(cMeasureSamples, cSampleMeasurementDelay, cSonicSlop);
  zeeLineReader* lineReader = new zeeLineReader();
  //we don't need to clean up the decorators as they will be cleaned up in the destructor of zeeMoveRobot as one of the chained Robots
  zeeDecoratorLed* ledDecorator = new zeeDecoratorLed(cMoveTime, NULL, onOffLed);
  zeeDecoratorPrintLn* printDecorator = new zeeDecoratorPrintLn(cMoveTime, ledDecorator);
  zeeMoveRobot* moveRobot = zeeRobotMazeLogic::SetMoveRobots(printDecorator, cMoveTime);
  zeeRobotMazeLogic *mazeLogic = new zeeRobotMazeLogic(sr04, moveRobot, lineReader, cDistanceForwardDetection);

  while (!mazeLogic->IsFinished())
  {
    mazeLogic->Execute();
  }

  delete onOffLed;
  delete sr04;
  delete moveRobot;
  delete mazeLogic;
  delete lineReader;
}