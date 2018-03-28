#ifndef moduleTempSens_h
#define moduleTempSens_h
#include "Arduino.h"
#include <modulemainclass.h>



class modTempSens : public module {
public:

virtual int getVal();
virtual void setVal(int16_t value);
virtual bool hasfunc();
virtual void printSubfuncs(byte subfunc);
virtual void refresh();
virtual void begin(int subfunc,int pin, int funcnum);

private:
  int _PIN;
  int _subfunc;
  int _funcnum;
};
#endif