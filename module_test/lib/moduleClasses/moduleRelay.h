#ifndef moduleRelay_h
#define moduleRelay_h
#include "Arduino.h"




class modRel {
public:

 int getVal(int *subfunc,int *pin);
 void setVal(int16_t value,int *subfunc,int *pin,int *laststate);
 void printSubfuncs(byte subfunc);



};
#endif
