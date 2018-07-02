#ifndef moduleServo_h
#define moduleServo_h
#include "Arduino.h"




class modServ  {
public:
modServ();
void begin(int *pin);
 int getVal();
 void setVal(int16_t value,int *subfunc,int *pin,int *laststate);
 void printSubfuncs(byte subfunc);



private:

};
#endif
