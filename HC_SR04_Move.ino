#include "zeeMotorPins.h"
#include <Adafruit_MotorShield.h>

/*

*/
#include "zeeOnOffLED.h"
#include "zeeHC_SR04.h"
#include "zeeMoveRobot.h"
#include "zeeRobotMazeLogic.h"
#include "zeeLineReader.h"
#include "zeeSensorPins.h"
#include "zeeMotorPins.h"
#include "zeeDCMotor.h"

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

  Adafruit_MotorShield motorShield = Adafruit_MotorShield(0x61);

  Adafruit_DCMotor* _dcMotorFL = motorShield.getMotor(cMotorFL);
  Adafruit_DCMotor* _dcMotorFR = motorShield.getMotor(cMotorFR);
  Adafruit_DCMotor* _dcMotorRL = motorShield.getMotor(cMotorRL);
  Adafruit_DCMotor* _dcMotorRR = motorShield.getMotor(cMotorRR);

  zeeAdafruitDCMotor* dcMotorFL = new zeeAdafruitDCMotor(cMotorPinFL, _dcMotorFL);
  zeeAdafruitDCMotor* dcMotorFR = new zeeAdafruitDCMotor(cMotorPinFR, _dcMotorFR);
  zeeAdafruitDCMotor* dcMotorRL = new zeeAdafruitDCMotor(cMotorPinRL, _dcMotorRL);
  zeeAdafruitDCMotor* dcMotorRR = new zeeAdafruitDCMotor(cMotorPinRR, _dcMotorRR);

  zeeMotors* motors = new zeeMotors(dcMotorFL, dcMotorFR, dcMotorRL, dcMotorRR);
  zeeMoveRobot* moveRobot = zeeRobotMazeLogic::SetMoveRobots(printDecorator, motors, cMoveTime);
  zeeRobotMazeLogic* mazeLogic = new zeeRobotMazeLogic(sr04, moveRobot, lineReader, cDistanceForwardDetection);

  while (!mazeLogic->IsFinished())
  {
    mazeLogic->Execute();
  }

  delete onOffLed;
  delete sr04;
  delete moveRobot;
  delete mazeLogic;
  delete lineReader;

  delete _dcMotorFL;
  delete _dcMotorFR;
  delete _dcMotorRL;
  delete _dcMotorRR;

  delete dcMotorFL;
  delete dcMotorFR;
  delete dcMotorRL;
  delete dcMotorRR;

  delete motors;
}