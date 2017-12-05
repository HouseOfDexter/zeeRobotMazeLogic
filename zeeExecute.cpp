#include "zeeExecute.h"
#include "Arduino.h"

zeeExecute::zeeExecute(zeeArduino* arduino, unsigned long executeLength)
  :_arduino(arduino), _executeLength(executeLength)
{
}

zeeExecute::~zeeExecute()
{
}

void zeeExecute::Execute(bool bypassWait = false)
{
  Serial.println("Executing");
  Serial.print(bypassWait);
  Serial.println(" bypassWait");
  BeforeExecute();
  unsigned long executeLength =  _executeLength > 0 ? _executeLength : _arduino->GetIntervalRunTime();  
  unsigned long currentRunning = millis() - _lastUpdate;
  unsigned long updateInterval = _arduino->GetUpdateInterval();
  
  unsigned long startExecute = millis();
  /*we check if the time since we last executed is greater than our wait time
  we need to run again*/
  bool canExecute = IsExecuting() || _runningLength < executeLength;
  bool isPastWait = !IsExecuting() || _runningLength > updateInterval;

  if (bypassWait || canExecute || isPastWait)
  {
    Serial.println("DoExecute");
    SetIsExecuting(true);
    DoExecute(bypassWait);
    Serial.println("finished DoExecute");
    unsigned long endExecute = millis();
    unsigned long executeLength = endExecute - startExecute;
    _runningLength += executeLength;
    _lastUpdate = endExecute;
    Serial.print(_runningLength);
    Serial.println(" running length");
    if (_runningLength > updateInterval|| _runningLength > executeLength)
    {
      SetIsExecuting(false);
      _runningLength = 0;
    }
  }
  AfterExecute();
}

void zeeExecute::AfterExecute()
{
}

void zeeExecute::BeforeExecute()
{
}

