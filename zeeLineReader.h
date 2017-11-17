#ifndef zeeLineReader_h
#define zeeLineReader_h
#include "zeeArduino.h"
#include "zeeExecute.h"

#if ARDUINO >= 100
#include "Arduino.h"
#else
#include "WProgram.h"
#endif

class zeeLineReader: public zeeExecute
{
public:
  zeeLineReader(zeeArduino* arduino, unsigned long executeLength, unsigned int pin);
  ~zeeLineReader();

  bool DetectLine();
protected:
  void DoExecute();
private:
  zeeArduino* arduino;
  unsigned int _pin;
};

#endif
