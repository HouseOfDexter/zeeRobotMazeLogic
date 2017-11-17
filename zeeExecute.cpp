#include "zeeExecute.h"

zeeExecute::zeeExecute(zeeArduino* arduino, unsigned long executeLength)
  :_arduino(arduino), _executeLength(executeLength)
{
}

zeeExecute::~zeeExecute()
{
}

void zeeExecute::Execute()
{
  unsigned long currentRunning = _arduino->millis() - _lastUpdate;
  /*we check if the time since we last executed is greater than our wait time
  we need to run again*/
  if (currentRunning > _arduino->GetUpdateInterval()) 
  {
    if (_runningLength + currentRunning  < _executeLength)
    {
      SetIsExecuting(true);
      unsigned long startExecute = _arduino->millis();
      DoExecute();
      _lastUpdate = _arduino->millis();
      _runningLength += _lastUpdate - startExecute;
    }
    else
    {
      SetIsExecuting(false);
    }
    
  }
}
