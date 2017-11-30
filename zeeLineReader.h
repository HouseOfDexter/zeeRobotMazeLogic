#ifndef zeeLineReader_h
#define zeeLineReader_h
#include "zeeArduino.h"
#include "zeeExecute.h"

class zeeLineReader: public zeeExecute
{
public:
  zeeLineReader(zeeArduino* arduino, unsigned long executeLength, unsigned int rPin, unsigned int mPin, unsigned int lPin);
  virtual ~zeeLineReader();

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

