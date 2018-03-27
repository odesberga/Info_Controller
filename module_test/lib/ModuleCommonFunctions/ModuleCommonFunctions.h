#ifndef ModuleCommonFunctions_h
#define ModuleCommonFunctions_h
#include <SoftwareSerial.h>
#include <modulemainclass.h>
#include "modulePotentiometer.h"
#include "moduleButton.h"

#include <avr/pgmspace.h>
#include<Arduino.h>

#define SubfuncsCount 4
struct pins {
    byte pin;
    bool isAnalog;
    char name[3];
};

const pins P0={2,false,"D1"};
const pins P1={3,false,"D2"};
const pins P2={4,false,"D3"};
const pins P3={5,false,"D4"};
const pins P4={6,false,"D5"};
const pins P5={7,false,"D6"};
const pins P6={8,false,"D7"};
const pins P7={9,false,"D8"};
const pins P8={17,true,"A1"};
const pins P9={16,true,"A2"};
const pins P10={15,true,"A3"};
const pins P11={14,true,"A4"};

const pins PINS_Collection[]={
    P0,P1,P2,P3,P4,P5,P6,P7,P8,P9,P10,P11
};
#define PINS_CollectionCount 12
struct funcs {
    bool isAnalog;
    char name[15];
};

const funcs Fu0={true,"Potentiometer"};
const funcs Fu1={false,"Switch      "};

const funcs FUNCS_Collection[] = {
    Fu0,Fu1
};
#define FUNCS_CollectionCount 2


class CommonFunctions {

public:
    CommonFunctions();
    void begin();
    bool gotData();

    int func();
    bool setVal();
    int16_t Val();
    bool send(int16_t val);
    void ProcessFunctions(byte *Function,bool set,int16_t *setval);
    void RefreshFunctions();
private:
void(* resetFunc) (void) = 0;
bool testChar(char *c);
int loadAddress();
void PrintDescription();
void putPrgMemTextInBuffer(int arrIdx);
void setaddress();
void getFuncFromEEPROM(int slot);
void printFunc(int slot);
void delFunc();
void SerialMenu();
void readSerial();
void saveFunctoEEPROM(int slot);
void printAllFunc();
void help();
void addFunc();
void printsubc(int func,byte subfunc);
void clearFunc();
void saveFunc();
void  INITFunc(module &mod,int func,byte subfunc,bool init);
void loadFunctionsToRam();
void PFunction(byte PIN,byte *func,byte *subfunc,char *getset,int16_t *setval);
void CreateFunction(byte PIN,byte func,byte subfunc,byte funcnumb);
};


#endif
