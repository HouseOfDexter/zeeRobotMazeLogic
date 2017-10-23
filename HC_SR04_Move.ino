/*

*/
#include "zeeOnOffLED.h"
#include "zeeHC_SR04.h"
#include "zeeMoveRobot.h"
#include "zeeRobotMazeLogic.h"
#include "zeeLineReader.h"
#include "zeeSensorPins.h"

//LEDs to give us feedback
const unsigned int _ledPin1 = 3;
const unsigned int _ledPin2 = 2;

//default times in MS
const unsigned int _delay = 250;
const unsigned int _moveTime = 100;
const unsigned int _distanceForwardDetection = 50;

void setup() {
  Serial.begin(9600);
  pinMode(trigForwardPin, OUTPUT);
  pinMode(echoForwardPin, INPUT);
  pinMode(trigRFPin, OUTPUT);
  pinMode(echoRFPin, INPUT);
  pinMode(trigRRPin, OUTPUT);
  pinMode(echoRRPin, INPUT);
  pinMode(_ledPin1, OUTPUT);
  pinMode(_ledPin2, OUTPUT);
}

void loop()
{
  //we use dependecy injection so we know when to free our memory
  zeeOnOffLED* onOffLed = new zeeOnOffLED(_ledPin1, _ledPin2);
  zeeHC_SR04_Sensor* sr04 = new zeeHC_SR04_Sensor(MeasureSamples, SampleMeasurementDelay, sonicSlop);
  zeeLineReader* lineReader = new zeeLineReader();
  //we don't need to clean up the decorators as they will be cleaned up in the destructor of zeeMoveRobot as one of the chained Robots
  zeeDecoratorLed* ledDecorator = new zeeDecoratorLed(_moveTime, NULL, onOffLed);
  zeeDecoratorPrintLn* printDecorator = new zeeDecoratorPrintLn(_moveTime, ledDecorator);
  zeeMoveRobot* moveRobot = zeeRobotMazeLogic::SetMoveRobots(printDecorator, _moveTime);
  zeeRobotMazeLogic *mazeLogic = new zeeRobotMazeLogic(sr04, moveRobot, lineReader, _distanceForwardDetection);

  while (!mazeLogic->IsFinished())
  {
    mazeLogic->Move();
  }

  delete onOffLed;
  delete sr04;
  int i;

  delete moveRobot;

  delete mazeLogic;

  delete lineReader;
}