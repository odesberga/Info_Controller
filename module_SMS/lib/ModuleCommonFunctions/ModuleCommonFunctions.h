#ifndef ModuleCommonFunctions_h
#define ModuleCommonFunctions_h
#include <SoftwareSerial.h>
#include <modulesmsclass.h>
#include <avr/pgmspace.h>
#include<Arduino.h>


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
void INITFunc(smsclass &mod,int func,byte subfunc,bool init);
void loadFunctionsToRam();
void PFunction(byte PIN,byte *func,byte *subfunc,char *getset,int16_t *setval);
void CreateFunction(byte PIN,byte func,byte subfunc,byte funcnumb);
void nilFuncSbuf();
void setPhone();
void setMessage();
void sendsms(int func);
};


#endif
