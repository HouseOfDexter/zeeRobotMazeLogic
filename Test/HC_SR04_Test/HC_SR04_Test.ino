
#define _echoPin1 11
#define _trigPin1 10
#define _echoPin2 9
#define _trigPin2 8
#define _ledPin1 2
#define _ledPin2 3

#define _uso 58.0
#define _delay 500
#define _measureSamples 10
#define _measureSampleDelay 5

void setup() {
  Serial.begin (9600);
  pinMode(_trigPin1, OUTPUT);
  pinMode(_echoPin1, INPUT);
  pinMode(_trigPin2, OUTPUT);
  pinMode(_echoPin2, INPUT);  
  //pinMode(_ledPin1, OUTPUT);
  //pinMode(_ledPin2, OUTPUT);
}

void loop() {
  long distance1 = GetDistanceMm(_trigPin1, _echoPin1);
  long distance2 = GetDistanceMm(_trigPin2, _echoPin2);
  bool isEqual = IsEqual(8, distance1, distance2);
  digitalWrite(13, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(_delay);              // wait for a second
  digitalWrite(13, LOW);    // turn the LED off by making the voltage LOW
  delay(_delay); 
 // SetLED(isEqual);
  //simulte driving delay
}

long GetSingleDistanceMm(int trigPin, int echoPin)
{
  long duration, distance;   
  //we turn on the US_pulse
  digitalWrite(trigPin, HIGH);
  //wait for 11 µs
  delayMicroseconds(11); 
  //we turn off the US_pulse
  digitalWrite(trigPin, LOW);
  //we then read the echo of the US_Pulse...note this is returned in MicroSeconds
  duration = pulseIn(echoPin, HIGH);
  distance =  (long) (((float) duration / _uso) * 10.0); 
  return distance;
}

long GetDistanceMm(int trigPin, int echoPin)
{
  long measureSum = 0;
  for (int i = 0; i < _measureSamples; i++)
  {
    delay(_measureSampleDelay);
    measureSum += GetSingleDistanceMm(trigPin, echoPin);
  }
  return measureSum / _measureSamples;  
}

bool IsEqual(long maxDiff, long distance1, long distance2)
{
  bool isEqual;
  long diff = distance1 - distance2;
  Serial.println("Distance1: ");
  Serial.print(distance1);
  Serial.println(" mm");

  Serial.println("Distance2: ");
  Serial.print(distance1);
  Serial.println(" mm");

  Serial.println("Difference: ");
  Serial.print(diff);
  Serial.println(" mm");  
  
  if (diff < maxDiff && diff > -maxDiff) {  
    isEqual = true;    
  }
  else
  {    
    isEqual = false;
  }
  return isEqual;    
}

void SetLED(bool isOn)
{

  if(isOn == true)
  {
    digitalWrite(_ledPin1,HIGH);
    digitalWrite(_ledPin2,LOW);
  }
  else 
  {
    digitalWrite(_ledPin2,HIGH);
    digitalWrite(_ledPin1,LOW);        
  }
}

