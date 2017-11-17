#include "zeeArduino.h"
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
//#include "zeeAdafruitDCMotor.h"
#include "zeeElegooDCMotor.h"

//default times in MS
const unsigned int cDelay = 250;
const unsigned long cMoveTime = 100;

//distance in millimeters
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
  zeeArduino* arduino = new zeeArduino(10);
  zeeArduino* ledarduino = new zeeArduino(100);
  zeeOnOffLED* onOffLed = new zeeOnOffLED(ledarduino, cLedPin1, cLedPin2);
  zeeHC_SR04_Sensor* sr04 = new zeeHC_SR04_Sensor(arduino, cMeasureSamples, cSampleMeasurementDelay, cSonicSlop);
  zeeLineReader* lineReader = new zeeLineReader(arduino, cMoveTime, cLineReaderPin);
  //we don't need to clean up the decorators as they will be cleaned up in the destructor of zeeMoveRobot as one of the chained Robots
  zeeDecoratorLed* ledDecorator = new zeeDecoratorLed(ledarduino, cMoveTime, NULL, onOffLed);
  zeeDecoratorPrintLn* printDecorator = new zeeDecoratorPrintLn(ledarduino, cMoveTime, ledDecorator);

  //Adafruit_MotorShield motorShield = Adafruit_MotorShield(0x61);

  //Adafruit_DCMotor* _dcMotorFL = motorShield.getMotor(cMotorFL);
  //Adafruit_DCMotor* _dcMotorFR = motorShield.getMotor(cMotorFR);
  //Adafruit_DCMotor* _dcMotorRL = motorShield.getMotor(cMotorRL);
  //Adafruit_DCMotor* _dcMotorRR = motorShield.getMotor(cMotorRR);

  //zeeAdafruitDCMotor* dcMotorFL = new zeeAdafruitDCMotor(cMotorPinFL, _dcMotorFL);
  //zeeAdafruitDCMotor* dcMotorFR = new zeeAdafruitDCMotor(cMotorPinFR, _dcMotorFR);
  //zeeAdafruitDCMotor* dcMotorRL = new zeeAdafruitDCMotor(cMotorPinRL, _dcMotorRL);
  //zeeAdafruitDCMotor* dcMotorRR = new zeeAdafruitDCMotor(cMotorPinRR, _dcMotorRR);

  Elegoo_MotorShield motorShield = Elegoo_MotorShield();

  Elegoo_DCMotor* _dcMotorFL = motorShield.getMotor(cMotorFL);
  Elegoo_DCMotor* _dcMotorFR = motorShield.getMotor(cMotorFR);
  Elegoo_DCMotor* _dcMotorRL = motorShield.getMotor(cMotorRL);
  Elegoo_DCMotor* _dcMotorRR = motorShield.getMotor(cMotorRR);

  zeeElegooDCMotor* dcMotorFL = new zeeElegooDCMotor(arduino, cMoveTime, cMotorPinFL, _dcMotorFL);
  zeeElegooDCMotor* dcMotorFR = new zeeElegooDCMotor(arduino, cMoveTime, cMotorPinFR, _dcMotorFR);
  zeeElegooDCMotor* dcMotorRL = new zeeElegooDCMotor(arduino, cMoveTime, cMotorPinRL, _dcMotorRL);
  zeeElegooDCMotor* dcMotorRR = new zeeElegooDCMotor(arduino, cMoveTime, cMotorPinRR, _dcMotorRR);

  zeeMotors* motors = new zeeMotors(dcMotorFL, dcMotorFR, dcMotorRL, dcMotorRR);
  zeeMoveRobot* moveRobot = zeeRobotMazeLogic::SetMoveRobots(arduino, printDecorator, motors, cMoveTime);
  zeeRobotMazeLogic* mazeLogic = new zeeRobotMazeLogic(arduino, cMoveTime, sr04, moveRobot, lineReader, cDistanceForwardDetection);

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