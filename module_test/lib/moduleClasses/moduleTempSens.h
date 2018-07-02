#ifndef moduleTempSens_h
#define moduleTempSens_h
#include "Arduino.h"




class modTempSens {
public:

 int getVal(int *subfunc,int *pin);
 void printSubfuncs(byte subfunc);
private:

};
#endif
