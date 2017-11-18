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
  zeeLineReader(zeeArduino* arduino, unsigned long executeLength, unsigned int rPin, unsigned int mPin, unsigned int lPin);
  ~zeeLineReader();

  bool DetectRight();
  bool DetectLeft();
  bool DetectMiddle();
protected:
  void DoExecute();
private:
  zeeArduino* arduino;
  unsigned int _rPin;
  unsigned int _mPin;
  unsigned int _lPin;
};

#endif
