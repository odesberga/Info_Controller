#ifndef SerialConsole_h
#define SerialConsole_h
#include <SensorHandler.h>
#include <SoftwareSerial.h>
#include <avr/pgmspace.h>
#include<Arduino.h>

struct sData {
    byte destAddress=0;
    char code=0;
    byte Function=0;
    byte firstVal=0;
    byte secVal=0;
};

class SerialConsole
{

  public:
    sData ForwardMessage;
    sData emptyForwardMessage;
    SerialConsole(HardwareSerial& serial,SensorHandler& SH);
    HardwareSerial&  _Serial;
    SensorHandler& _SH;

    void refresh(SensorHandler& SH);
    //void begin(int baud, SensorHandler& sensHand);
    void begin(int baud);
    private:
        void(* resetFunc) (void) = 0;
        bool ConfirmMenu(int inftxt);
        void getCommand(int pos);
        int getCommandindex(char *lst[],int lstcnt);
        void putPrgMemTextInBuffer(int arrIdx,char *arr[]);
        void PrintpMemBuf();
        void mnuSensor();
        void mnuReboot();
        void mnusensor_del();
        void mnuSensor_add();
        void mnuSensor_list();
        void mnusensor_loadfromsd();
        void mnusensor_savetosd();
        void mnueeprom();
        void mnueepromdel();
        void mnueepromclear();
        void mnueepromlist();
        void mnueepromadd();
        void txt_reboot();
        void txt_error_not_found(int what);
        int getSubCommandindex(int scmdidx);
        bool getTextMenu(char* qtxt,int timeoutSec);
        void parseCommand();
        void mnuHelp();
        void mnuIPset();
        void mnuIPshow();
        void mnuIP();
        void mnuFilelist();
        void mnuFileshow();
        void mnuFiledel();
        void mnuFile();
        void mnuForward();
    int _inMenu=0;



};





#endif
