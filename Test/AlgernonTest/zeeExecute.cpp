#include "zeeExecute.h"

zeeExecute::zeeExecute(zeeArduino* arduino, unsigned long executeLength)
  :_arduino(arduino), _executeLength(executeLength)
{
}

zeeExecute::~zeeExecute()
{
}

void zeeExecute::Execute(bool bypassWait = false)
{
  if (_executeLength == 0)
    _executeLength = 4294967295;

  unsigned long currentRunning = _arduino->Millis() - _lastUpdate;
  unsigned long updateInterval = _arduino->GetUpdateInterval();  
  unsigned long startExecute = _arduino->Millis();
  /*we check if the time since we last executed is greater than our wait time
  we need to run again*/
  bool isExecuting = IsExecuting();  
  bool isPastWait = (!isExecuting &&(currentRunning > updateInterval));  
  
  if (bypassWait|| isExecuting ||isPastWait)
  {      
    SetIsExecuting(true);      
    DoExecute();
    _lastUpdate = _arduino->Millis();
    _runningLength += _lastUpdate - startExecute;            
    if (_runningLength > updateInterval) 
    {
      SetIsExecuting(false);
      _runningLength = 0;
    }    
  }
  

}

