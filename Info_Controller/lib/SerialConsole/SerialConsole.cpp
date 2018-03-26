#include <SerialConsole.h>
#include <SensorHandler.h>
#include <EEPROM.h>

/////////////////////////////////////// info text //////////////////////////////////////

const char icmd0[]  = "";
const char icmd1[]  = "Unknown Command!";
const char icmd2[]  = "Really";
const char icmd3[]  = "aborted";
const char icmd4[]  = "please";
const char icmd5[]  = "enter";
const char icmd6[]  = "select";
const char icmd7[]  = "reboot";
const char icmd8[]  = "Done";
const char icmd9[]  = "sensor";
const char icmd10[]  = "not";
const char icmd11[]  = "found";
const char icmd12[]  = "Error";
const char icmd13[]  = "Success";
const char icmd14[]  = "deleted";
const char icmd15[]  = "added";
const char icmd16  = '\t';
const char icmd17[]  = "Save";
const char icmd18[]  = "file";
const char icmd19[]  = "?";
const char icmd20[]  = "y/n";
const char icmd21[]  = " ";
const char icmd22[]  = "now";
const char icmd23[]  = "required";
const char icmd24[]  = "to";
const char icmd25[]  = "activate";
const char icmd26[]  = "changes";
const char icmd27[]  = "memory";
const char icmd28[]  = "telephone";
const char icmd29[]  = "number";
const char icmd30[]  = "!";
const char icmd31[]  = "load";
const char icmd32[]  = "from";

const char *infcmd_lst[] = {
    icmd0,icmd1,icmd2,icmd3,icmd4,icmd5,icmd6,icmd7,icmd8,icmd9,icmd10,
    icmd11,icmd12,icmd13,icmd14,icmd15,icmd16,icmd17,icmd18,
    icmd19,icmd20,icmd21,icmd22,icmd23,icmd24,icmd25,icmd26,
    icmd27,icmd28,icmd29,icmd30,icmd31,icmd32
};

#define txt_space 21
#define txt_qstn 19

/////////////////////////////////// Commands //////////////////////////////
const char cmd1[]  ="module";
const char cmd2[]  ="file";
const char cmd3[]  ="ip";
const char cmd4[]  ="debug";
const char cmd5[]  ="reboot";
const char cmd6[]  ="help";
const char cmd7[]  ="eeprom";
const char*  cmd_lst[]  = {
    cmd1,cmd2,cmd3,cmd4,cmd5,cmd6,cmd7
};

#define cmd_lst_count 7
/////////////////////////////////// Sub commands //////////////////////////////
const char subcmd1[]  ="add";
const char subcmd2[]  ="del";
const char subcmd3[]  ="list";
const char subcmd4[]  ="set";
const char subcmd5[]  ="clear";
const char subcmd6[]  ="show";
const char subcmd7[]  ="loadfromsd";
const char subcmd8[]  ="savetosd";
const char subcmd9[]  ="help";

const char*  subcmd_lst1[] = {
    subcmd1,subcmd2,subcmd3,subcmd4,subcmd5,subcmd6,subcmd7,subcmd8,subcmd9
};
#define subcmd_count 8

const char sensAddMenu_string_0[] PROGMEM = "Enter Name";
const char sensAddMenu_string_1[] PROGMEM = "Enter Address";
const char sensAddMenu_string_2[] PROGMEM = "Enter Function";
const char sensAddMenu_string_3[] PROGMEM = "Enter forwarding threshold";
const char sensAddMenu_string_4[] PROGMEM = "Enter forwarding threshold Over/Under [+/-]";
const char sensAddMenu_string_5[] PROGMEM = "Enter Value type eg V for Volt, C for celsius or P for pascal";
const char sensAddMenu_string_6[] PROGMEM = "Print to screen [y/n]";
const char sensAddMenu_string_7[] PROGMEM = "Enter address to forwarding module [0-100] 0 = n/a";
const char sensAddMenu_string_8[] PROGMEM = "Enter function on forwarding function 0 = n/a";
const char sensAddMenu_string_9[] PROGMEM = "";
const char* const sensAddMenu[] PROGMEM = {
sensAddMenu_string_0,sensAddMenu_string_1,sensAddMenu_string_2,sensAddMenu_string_3,sensAddMenu_string_4,sensAddMenu_string_5,
sensAddMenu_string_6,sensAddMenu_string_7,sensAddMenu_string_8,sensAddMenu_string_9
};




const char HelpMenu_string_0[] PROGMEM = "Help!";
const char HelpMenu_string_1[] PROGMEM = "module list                    :list modules";
const char HelpMenu_string_2[] PROGMEM = "module del [modulename]        :delete module";
const char HelpMenu_string_3[] PROGMEM = "module add                     :add new module (wizard)";
const char HelpMenu_string_4[] PROGMEM = "module savetosd [filename]     :save modules to file ";
const char HelpMenu_string_41[] PROGMEM = "module loadfromsd [filename]   :load modules from file";
const char HelpMenu_string_5[] PROGMEM = "module clear                   :clear all modules";
const char HelpMenu_string_6[] PROGMEM = "file list                      :list files on SD";
const char HelpMenu_string_7[] PROGMEM = "file show [filename]           :show file content";
const char HelpMenu_string_8[] PROGMEM = "file del [filename]            :delete file from SD";
const char HelpMenu_string_9[] PROGMEM = "eeprom list                    :list values saved in eeprom";
const char HelpMenu_string_10[] PROGMEM = "ip set [ip Address]            :Set IP address";
const char HelpMenu_string_11[] PROGMEM = "ip show                        :show current IP address";
const char HelpMenu_string_12[] PROGMEM = "";
const char HelpMenu_string_13[] PROGMEM = "reboot                         :restart the system";
const char HelpMenu_string_14[] PROGMEM = "help                           :show help";
const char* const menu_help[] PROGMEM = {
    HelpMenu_string_0, HelpMenu_string_1, HelpMenu_string_2, HelpMenu_string_3, HelpMenu_string_4, HelpMenu_string_41, HelpMenu_string_5
    , HelpMenu_string_6, HelpMenu_string_7, HelpMenu_string_8, HelpMenu_string_9, HelpMenu_string_10, HelpMenu_string_11
    , HelpMenu_string_12, HelpMenu_string_13, HelpMenu_string_14
};
#define mnuhelpcount 16
#define infocmd_count 2
#define cmdsize 30
char pMemBuf[200];
char cmd[cmdsize];
char commandBuf[60];
bool debug=true;
SensorHandler _SH(3);


SerialConsole::SerialConsole(HardwareSerial& serial): _Serial(serial){
}
void SerialConsole::begin(int baud){
    _Serial.begin(baud);
    mnuHelp();
}

void SerialConsole::putPrgMemTextInBuffer(int arrIdx,char *arr[]){
memset(pMemBuf, 0, sizeof(pMemBuf));
strcpy_P(pMemBuf, (char*)pgm_read_dword(&(arr[arrIdx])));
}

void SerialConsole::getCommand(int pos){
  int commacount=0;
  int idx=0;
  memset(cmd, 0, sizeof(cmd));
  for (int i =0; i< sizeof(commandBuf)-1;i++){

      if (isSpace(commandBuf[i]) || commandBuf[i]=='#'){
          if (commacount == pos){
              cmd[idx]='\0';
              break;
          }else {
               memset(cmd, 0, sizeof(cmd));
               commacount++;
               idx=0;
          }
      } else {
            cmd[idx]= commandBuf[i];
            idx++;
        }
      }
  }

void SerialConsole::refresh(SensorHandler &SH){
//    if (_Serial.available()) {
            int idx=0;
            bool newdata=false;
            memset(commandBuf, 0, sizeof(commandBuf));
              while (_Serial.available() > 0) {
                        commandBuf[idx]=_Serial.read();
                        delay(10);
                        if (commandBuf[idx]=='\r') {
                            break;
                        } else {
                            idx++;
                            newdata=true;
                        }
              }

        if (newdata){

        _SH=SH;
            parseCommand();
        }
    //}
}

int  SerialConsole::getCommandindex(char *lst[],int lstcnt){
bool Found=false;
    for(int i =0;i<lstcnt;i++){
        if (strcmp(lst[i],cmd)==0){
            Found=true;
            return i;
            break;
        }
}
if(!Found){return -1;};
}
void SerialConsole::mnuReboot(){
    _Serial.print((char*)infcmd_lst[7]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[22]);
    _Serial.print((char*)infcmd_lst[19]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.println((char*)infcmd_lst[20]);
        if(ConfirmMenu(0)){
        resetFunc();
        }
}
void SerialConsole::parseCommand(){
getCommand(0);
//_Serial.println((char*)cmd);

int cmdidx=getCommandindex(cmd_lst,cmd_lst_count);
    if(cmdidx > -1){
        switch (cmdidx) {
            case 0:
                mnuSensor();
                break;
            case 1:
                mnuFile();
                break;
            case 2:
                mnuIP();
                break;
            case 4:
                mnuReboot();
                break;
            case 5:
                mnuHelp();
                break;
            case 6:
                mnueeprom();
                break;
        }

    } else {
    _Serial.println((char*)infcmd_lst[1]);
    }
}


void SerialConsole::mnuIP(){
    switch (getSubCommandindex(1)) {

        case 3:
            mnuIPset();
            break;

        case 5:
            mnuIPshow();
            break;
        default:
            _Serial.println((char*)infcmd_lst[1]);
            _Serial.println((char*)subcmd_lst1[3]);
            _Serial.println((char*)subcmd_lst1[5]);

    }
}

void SerialConsole::mnuIPshow(){
    int startidx=30;
    startidx++;
    startidx=startidx*101;
    startidx++;
    int i=0;
    char b;
    _Serial.println();
    while(true){
        b=EEPROM.read(startidx+i);
        if(b=='\0'){
            break;
        } else {

            _Serial.print(b) ;
            i++;
        }
    }
}
void SerialConsole::mnuIPset(){
    getCommand(2);
    int startidx=30;
    startidx++;
    startidx=startidx*101;
    startidx++;

        int i=0;
        char b;
        while(true){
            b=cmd[i];
            if(b=='\0'){
                break;
            } else {
                EEPROM.write(startidx+i,b);
                EEPROM.write(startidx+i+1,'\0');
                i++;
            }
        }
        _Serial.print((char*)cmd);
        _Serial.println();
        _Serial.print((char*)infcmd_lst[13]);
        _Serial.println((char*)infcmd_lst[30]);
        txt_reboot();

}


void SerialConsole::mnuFile(){
    switch (getSubCommandindex(1)) {

        case 1:
            mnuFiledel();
            break;
        case 2:
            mnuFilelist();
            break;
        case 5:
            mnuFileshow();
            break;
        default:
            _Serial.println((char*)infcmd_lst[1]);
            _Serial.println((char*)subcmd_lst1[1]);
            _Serial.println((char*)subcmd_lst1[2]);
            _Serial.println((char*)subcmd_lst1[5]);
    }
}
void SerialConsole::mnuFilelist(){
    _SH.lssd();
    Serial.println();
}
void SerialConsole::mnuFileshow(){
getCommand(2);
_SH.catfilesd(cmd);
Serial.println();

}
void SerialConsole::mnuFiledel(){
    _Serial.print((char*)infcmd_lst[2]);
    _Serial.print((char*)infcmd_lst[txt_qstn]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.println((char*)infcmd_lst[20]);
    if (ConfirmMenu(0)){
        getCommand(2);
        if(_SH.deletefromsd(cmd)){
        _Serial.print((char*)infcmd_lst[13]);
        _Serial.println((char*)infcmd_lst[30]);
        };

    }
    Serial.println();
}

void SerialConsole::mnueeprom(){
    switch (getSubCommandindex(1)) {
        case 0:
            mnueepromadd();
            break;
        case 1:
            mnueepromdel();
            break;
        case 2:
            mnueepromlist();
            break;
        case 4:
            mnueepromclear();
            break;



        default:
            _Serial.println((char*)infcmd_lst[1]);
            _Serial.println((char*)subcmd_lst1[0]);
            _Serial.println((char*)subcmd_lst1[1]);
            _Serial.println((char*)subcmd_lst1[2]);
            _Serial.println((char*)subcmd_lst1[4]);
    }
}

void SerialConsole::mnueepromdel(){
    _Serial.print((char*)infcmd_lst[2]);
    _Serial.print((char*)infcmd_lst[txt_qstn]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.println((char*)infcmd_lst[20]);
if (ConfirmMenu(1)){
    getCommand(2);
    _SH.clearEEPROM(atoi(cmd));
    _Serial.print(F("deleted slot: "));
    _Serial.println((char*)cmd);
}
Serial.println();
}
void SerialConsole::mnueepromclear(){
    _Serial.print((char*)infcmd_lst[2]);
    _Serial.print((char*)infcmd_lst[txt_qstn]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.println((char*)infcmd_lst[20]);
    if (ConfirmMenu(0)){
        for(int i =1;i<=SensorMaxCount;i++){
        //for(int i =1;i<=10;i++){
            _SH.clearEEPROM(i);
            _Serial.print("*");
        }
    }
    _Serial.println();
    _Serial.print((char*)infcmd_lst[8]);
    _Serial.println((char*)infcmd_lst[30]);

}

void SerialConsole::mnueepromlist(){
    String aString;

    for(int i =1;i<=SensorMaxCount;i++){
        _SH.getStringFromEEPROM(i,aString);
        if(aString.length()>1){
            _Serial.print(F("Slot "));
            _Serial.print((String)i);
            _Serial.print(" ");
            _Serial.println(aString);
            }
    }
    _Serial.print((char*)infcmd_lst[8]);
    _Serial.println((char*)infcmd_lst[30]);
    Serial.println();
}
void SerialConsole::mnueepromadd(){
getCommand(2);
    if(cmd[0]!=0){
        _SH.saveToEEPROM(cmd,cmdsize);
        _Serial.print((char*)cmd);
        _Serial.println();
        _Serial.print((char*)infcmd_lst[13]);
        _Serial.println((char*)infcmd_lst[30]);
        }
        Serial.println();
}


int SerialConsole::getSubCommandindex(int scmdidx){
    getCommand(scmdidx);
//    _Serial.println((char*)cmd);
    return getCommandindex(subcmd_lst1,subcmd_count);
}
void SerialConsole::mnuSensor(){

            switch (getSubCommandindex(1)) {
                case 0:
                    mnuSensor_add();
                    break;
                case 1:
                    mnusensor_del();
                    break;
                case 2:
                    mnuSensor_list();
                    break;
                case 4:
                    mnueepromclear();
                    break;
                case 6:
                    mnusensor_loadfromsd();
                    break;
                case 7:
                    mnusensor_savetosd();
                    break;
                default:
                    mnuHelp();
                    _Serial.println((char*)infcmd_lst[1]);
            }

}

void SerialConsole::mnuSensor_add(){
memset(cmd,0,sizeof(cmd));
_Serial.println((char*)cmd);
    char sens[cmdsize];
    memset(sens,0,sizeof(sens));
    bool aborted=false;
int tmot=20;
    putPrgMemTextInBuffer(0,sensAddMenu);
    if (getTextMenu(pMemBuf,10)){
        strcpy(sens,cmd);
        _Serial.println((char*)sens);
    } else { aborted=true;};

    if (!aborted){
        putPrgMemTextInBuffer(1,sensAddMenu);
        if (getTextMenu(pMemBuf,10)){
            strcat(sens,",");
            strcat(sens,cmd);
            _Serial.println((char*)sens);
        } else { aborted=true;};
    };
    if (!aborted){
        putPrgMemTextInBuffer(2,sensAddMenu);
        if (getTextMenu(pMemBuf,tmot)){
            strcat(sens,",");
            strcat(sens,cmd);
            _Serial.println((char*)sens);
        } else { aborted=true;};
    };
    if (!aborted){
        putPrgMemTextInBuffer(3,sensAddMenu);
        if (getTextMenu(pMemBuf,tmot)){
            strcat(sens,",");
            strcat(sens,cmd);
            _Serial.println((char*)sens);
        } else { aborted=true;};
    };
    if (!aborted){

        putPrgMemTextInBuffer(4,sensAddMenu);
        if (getTextMenu(pMemBuf,tmot)){

            strcat(sens,",");
            strcat(sens,cmd);
            _Serial.println((char*)sens);
        } else {
            strcat(sens,",");
        strcat(sens,"+");
        _Serial.println((char*)sens);};


    };
    if (!aborted){
         putPrgMemTextInBuffer(5,sensAddMenu);
         if (getTextMenu(pMemBuf,tmot)){
             strcat(sens,",");
             strcat(sens,cmd);
             _Serial.println((char*)sens);
         } else { strcat(sens,",");
     strcat(sens,'0');
     _Serial.println((char*)sens);};

    };
    if (!aborted){
        putPrgMemTextInBuffer(6,sensAddMenu);
        if (getTextMenu(pMemBuf,tmot)){
            strcat(sens,",");
            strcat(sens,cmd);
            _Serial.println((char*)sens);
        } else { strcat(sens,",");
    strcat(sens,"y");
    _Serial.println((char*)sens);};
};
    if (!aborted){
        putPrgMemTextInBuffer(7,sensAddMenu);
        if (getTextMenu(pMemBuf,tmot)){
            strcat(sens,",");
            strcat(sens,cmd);
            _Serial.println((char*)sens);
        } else { strcat(sens,",");
    strcat(sens,"0");
    _Serial.println((char*)sens);};
};
    if (!aborted){
        putPrgMemTextInBuffer(8,sensAddMenu);
        if (getTextMenu(pMemBuf,tmot)){
            strcat(sens,",");
            strcat(sens,cmd);
            _Serial.println((char*)sens);
        } else { strcat(sens,",");
    strcat(sens,"0");
    _Serial.println((char*)sens);};
};
    if (!aborted){
        _Serial.print((char*)infcmd_lst[17]);
        _Serial.print((char*)infcmd_lst[txt_space]);
        _Serial.print((char*)infcmd_lst[24]);
        _Serial.print((char*)infcmd_lst[txt_space]);
        _Serial.print((char*)infcmd_lst[27]);
        _Serial.print((char*)infcmd_lst[txt_qstn]);
        _Serial.print((char*)infcmd_lst[txt_space]);
        _Serial.println((char*)infcmd_lst[20]);
        if(ConfirmMenu(16)){
            _SH.saveToEEPROM(sens,cmdsize);
            _Serial.print((char*)sens);
            _Serial.println();
            _Serial.print((char*)infcmd_lst[13]);
            _Serial.println((char*)infcmd_lst[30]);
        txt_reboot();
        } else {
            _Serial.println((char*)infcmd_lst[3]);
        }
    };
}

void SerialConsole::mnuSensor_list(){
    _Serial.println(F("Modules:"));


    //Serial.println(F("Name       Address Function Threshold ThresholdPosNeg Level PrintToScreen ForwardSensorAddress ForwardSensorFunction"));
_Serial.print(F("Name"));
_Serial.print('\t');
_Serial.print('\t');
_Serial.print(F("Address"));
_Serial.print('\t');
_Serial.print('\t');
_Serial.print(F("Function"));
_Serial.print('\t');

_Serial.print(F("Threshold"));
_Serial.print('\t');

_Serial.print(F("ThresholdPosNeg"));
_Serial.print('\t');

_Serial.print(F("Value type"));
_Serial.print('\t');

_Serial.print(F("PrintToScreen"));
_Serial.print('\t');

_Serial.print(F("ForwardSensorAddress"));

_Serial.print('\t');
_Serial.println(F("ForwardSensorFunction"));

    SensorData aSensordata;
    for(int i = 0;i<_SH.sensorCount();i++){
        aSensordata=_SH._SensorData[i];
    _Serial.print(String(aSensordata.SensorName));
    _Serial.print('\t');
    _Serial.print('\t');
    _Serial.print(String(aSensordata.SensorAddress));
    _Serial.print('\t');
    _Serial.print('\t');
    _Serial.print(String(aSensordata.SensorFunction));
    _Serial.print('\t');
    _Serial.print('\t');
    _Serial.print(String(aSensordata.SensorThreshold));
    _Serial.print('\t');
    _Serial.print('\t');
    _Serial.print(String(aSensordata.ThresholdPosNeg));
    _Serial.print('\t');
    _Serial.print('\t');
    _Serial.print(String(aSensordata.Valtype));
    _Serial.print('\t');
    _Serial.print('\t');
    _Serial.print(String(aSensordata.PrintToScreen));
    _Serial.print('\t');
    _Serial.print('\t');
    _Serial.print(String(aSensordata.ForwardSensorAddress));
    _Serial.print('\t');
    _Serial.print('\t');
    _Serial.println(String(aSensordata.ForwardSensorFunction));
}
}




void SerialConsole::mnusensor_del(){
    _Serial.print((char*)infcmd_lst[2]);
    _Serial.print((char*)infcmd_lst[txt_qstn]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.println((char*)infcmd_lst[20]);
if (ConfirmMenu(0)){
    getCommand(2);
    if( _SH.delFromEEPROM(cmd)){
    _Serial.print((char*)infcmd_lst[13]);
    _Serial.println((char*)infcmd_lst[30]);
    txt_reboot();
} else {
    txt_error_not_found(9);
}
}
}

void SerialConsole::mnusensor_loadfromsd(){
    _Serial.print((char*)infcmd_lst[31]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[9]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[32]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[18]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[24]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[27]);
    _Serial.print((char*)infcmd_lst[txt_qstn]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.println((char*)infcmd_lst[20]);

if (ConfirmMenu(16)){
    getCommand(2);
    if(_SH.loadfromsd(cmd)){
        _Serial.println((char*)infcmd_lst[13]);
        txt_reboot();
    } else {
        txt_error_not_found(18);
    }

    }
}
void SerialConsole::mnusensor_savetosd(){
    _Serial.print((char*)infcmd_lst[17]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[9]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[24]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[18]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[32]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[27]);
    _Serial.print((char*)infcmd_lst[txt_qstn]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.println((char*)infcmd_lst[20]);
if (ConfirmMenu(16)){
    getCommand(2);
    if(_SH.savetosd(cmd)){
        _Serial.print((char*)infcmd_lst[13]);
        _Serial.println((char*)infcmd_lst[30]);

    } else {
        txt_error_not_found(18);
    }

    }
}


void SerialConsole::PrintpMemBuf(){
            _Serial.println((char*)pMemBuf);
}
void SerialConsole::mnuHelp(){
    for (int i =0; i< 50;i++){
    _Serial.println();
    }
    for (int i =0; i< mnuhelpcount;i++){
        putPrgMemTextInBuffer(i,menu_help );
        PrintpMemBuf();
    }
}
bool SerialConsole::ConfirmMenu(int inftxt){
    //_Serial.println((char*)infcmd_lst[inftxt]);
    bool retval=false;
    unsigned long w=millis();
    bool newdata=false;
    while (millis()<5000+w){
      while (_Serial.available() > 0) {
                if (_Serial.read()=='y'){
                retval= true;
                    newdata=true;
                    break;
                } else {
                    newdata=true;
                    break;
                }
        }
    if (newdata){
        break;
    }
    }
    if(!retval){ _Serial.println((char*)infcmd_lst[2]);};
    return retval;
}

bool SerialConsole::getTextMenu(char* qtxt,int timeoutSec){
    _Serial.println(qtxt);
    memset(cmd,0,sizeof(cmd));
    bool retval=false;
    int c=0;
    char aBuf;
    unsigned long w=millis();
    bool newdata=false;
    while (millis()<(timeoutSec*1000)+w){
      while (_Serial.available() > 0) {
                aBuf=_Serial.read();
                if (aBuf=='\r'){
                    if(c>0){
                retval= true;
                break;
                } else {
                    retval= false;
                    break;
                }
                } else {
                    cmd[c]=aBuf;
                    cmd[c+1]='\0';
                    c++;
                }
        }
        if (retval){
            break;
        }
    }
    if(!retval){ _Serial.println((char*)infcmd_lst[1]);};
    return retval;
}
void SerialConsole::txt_reboot(){
    /////reboot required to activate changes
    _Serial.print((char*)infcmd_lst[7]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[23]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[24]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[25]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.println((char*)infcmd_lst[26]);
}

void SerialConsole::txt_error_not_found(int what){
    _Serial.print((char*)infcmd_lst[12]);
    _Serial.println((char*)infcmd_lst[30]);
    _Serial.print((char*)infcmd_lst[what]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[10]);
    _Serial.print((char*)infcmd_lst[txt_space]);
    _Serial.print((char*)infcmd_lst[11]);
    _Serial.println((char*)infcmd_lst[30]);
}
