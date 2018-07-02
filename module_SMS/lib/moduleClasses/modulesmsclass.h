#ifndef modulesmsclass_h
#define modulesmsclass_h
#include "Arduino.h"


class smsclass {

public:
smsclass();
virtual void begin(int subfunc,int pin, int funcnum);
virtual int getVal();
virtual void setVal(int16_t value);
virtual void printSubfuncs(byte subfunc);
virtual bool hasfunc();
virtual void refresh();
void getPhoneFromEEprom(byte phidx, char &buffer);
void setPhonetoEEprom(byte phidx, char &buffer);
char getThreshholdFromEEprom();
char setThreshholdtoEEprom(int16_t t);


int funcNum();
private:

protected:
    int _PIN;
    int _subfunc;
    int _funcnum;

};
#endif
