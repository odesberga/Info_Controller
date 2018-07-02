#include <ModuleCommonFunctions.h>
#include <SerialCommunication.h>
#include <modulesmsclass.h>
#include <EEPROMAnything.h>
#include <EEPROM.h>
#define SofSerialRXPin 10
#define SofSerialTXPin 11
#define RS485EnablePin 0
#define FuncSaveStartAddress 10
#define numberOfFunctions 10
#define FuncMobnrCount 5
#define FuncMobnrByteCount 13
#define FuncMessByteCount 50
#define minutesbetweensend 10
unsigned long secondssbetweensend = minutesbetweensend*60;
unsigned long millisbetweensend= secondssbetweensend*1000;
struct smscontrol {
    bool hasresponded[FuncMobnrCount];
    bool isactive=false;
    bool firstsend=true;
    unsigned long msgtime=millis();
};
struct smscontainer {
    char phone[FuncMobnrCount][FuncMobnrByteCount];
    char message[FuncMessByteCount];
};
smscontrol functions[numberOfFunctions];
smscontainer SMSContainer;



SoftwareSerial mySeria1( SofSerialRXPin,SofSerialTXPin);
SerialCommunication SC(mySeria1,RS485EnablePin);
char address;
char pMemBuf[10];
char commandBuf[FuncMessByteCount];

int funcCount=0;


CommonFunctions::CommonFunctions(){};

void CommonFunctions::ProcessFunctions(byte *Function,bool set,int16_t *setval){

    if((int)setval> 0-9999){
        functions[(int)Function-1].isactive=true;

        // RefreshFunctions();
    } else {
        functions[(int)Function-1].firstsend=true;
        functions[(int)Function-1].isactive=false;
        for(int i=0;i<FuncMobnrCount;i++){
            functions[(int)Function-1].hasresponded[i]=false;
        }
    }

    while (Serial3.available() > 0) {
        Serial.print(Serial3.read());
    }

};







void CommonFunctions::RefreshFunctions(){
    for(int i=0;i<numberOfFunctions;i++){

        if(functions[i].isactive){

            if(functions[i].firstsend){
                    functions[i].firstsend=false;
                    sendsms(i);

            } else {
                if(millis()>functions[i].msgtime+millisbetweensend){

                    sendsms(i);
                }
            }
        }
    }


}
void CommonFunctions::CreateFunction(byte PIN,byte func,byte subfunc,byte funcnumb){

};

void CommonFunctions::sendsms(int func){
    getFuncFromEEPROM(func);
    for(int i=0;i<FuncMobnrCount;i++){
    if(functions[func].hasresponded[i]==false){
        if (!SMSContainer.phone[i][3]==0){
            Serial.println();
            Serial.print("AT+CMGF=1\r");
            delay(100);
            Serial.print("AT + CMGS = \"");
            Serial.print(SMSContainer.phone[i]);
            Serial.println("\"");
            delay(100);
            Serial.println(SMSContainer.message);
            delay(100);
            Serial.println((char)26);  // End AT command with a ^Z, ASCII code 26
            delay(100);
            Serial.println();


            Serial3.print("AT+CMGF=1\r");
            delay(100);
            Serial3.print("AT + CMGS = \"");
            Serial3.print(SMSContainer.phone[i]);
            Serial3.println("\"");
            delay(100);
            Serial3.println(SMSContainer.message);
            delay(100);
            Serial3.println((char)26);  // End AT command with a ^Z, ASCII code 26
            delay(100);
            Serial3.println();
            delay(5000);

        }
    }
}
functions[func].msgtime=millis();
Serial3.print("AT+CNMI=2,2,0,0,0\r");
}

void CommonFunctions::printsubc(int func,byte subfunc){


}


void CommonFunctions::begin(){

SC.begin(loadAddress());
Serial.print(F("Current address = "));
Serial.print(SC.ownAddress());
Serial.println();
if(SC.ownAddress()==127){
    Serial.println(F("Clearing memory: "));
    clearFunc();};
loadFunctionsToRam();
help();
};

bool CommonFunctions::gotData(){
    if(Serial.available() > 0){
        SerialMenu();
    }
    if(SC.gotData()){

    ProcessFunctions(func(),setVal(),Val());
    return true;
    } else {
    return false;
    }
};

void CommonFunctions::readSerial(){
int idx=0;

bool b=false;
memset(commandBuf, 0, sizeof(commandBuf));
    while(true){
          while (Serial.available() > 0) {
                     if (idx<=sizeof(commandBuf)) {
                    commandBuf[idx]=Serial.read();
                    Serial.print(commandBuf[idx]);
                    delay(10);
                    if (commandBuf[idx]=='\r') {
                        commandBuf[idx]='\0';
                        b=true;
                        //break;
                    } else {
                        idx++;
                    }
                 }
          }
        if(b){break;};
    }

}

void CommonFunctions::SerialMenu(){
readSerial();
    switch (atoi(commandBuf)){
            case 1:
                setaddress();
                help();
                break;
            case 2:
                printAllFunc();
                help();
                break;
            case 3:
                addFunc();
                printAllFunc();
                // resetFunc();
                break;
            case 4:
                delFunc();
                printAllFunc();
                // resetFunc();
                help();
                break;
            case 5:
                clearFunc();
                // resetFunc();
                help();
                break;
            default:
            help();
            break;
    }

}


void CommonFunctions::addFunc(){
    int f=0;
    int func=0;
    Serial.println();
    Serial.print(F("Choose function: 1-"));
    Serial.print(numberOfFunctions);
    Serial.println();
    readSerial();
    func=atoi(commandBuf)-1;
    getFuncFromEEPROM(func);
    Serial.println();
    Serial.print(F("Choose setting:"));
    Serial.println();
    Serial.print(F("1: Phone Number"));
    Serial.println();
    Serial.print(F("2: Text"));
    Serial.println();
    readSerial();
    f=atoi(commandBuf);

    switch(f){
        case 1:
            setPhone();
        break;
        case 2:
            setMessage();
        break;
    break;
};
saveFunctoEEPROM(func);

};
void CommonFunctions::setPhone(){
    int f=0;
    Serial.println();
    Serial.print(F("Choose number to edit: 1-"));
    Serial.print(FuncMobnrCount);
    Serial.println();
    readSerial();
    f=atoi(commandBuf);
    if(f<=FuncMobnrCount){
        Serial.println();
    Serial.println(F("Enter phone number"));
    readSerial();
    strncpy(SMSContainer.phone[f-1],commandBuf,FuncMobnrByteCount);
    }

}
void CommonFunctions::setMessage(){
Serial.println();
    Serial.println(F("Enter SMS text:"));
    readSerial();
    strncpy(SMSContainer.message,commandBuf,FuncMessByteCount);


}

void CommonFunctions::help(){
    Serial.println();
    Serial.println();
    Serial.println(F("1: set address"));
    Serial.println(F("2: list functions"));
    Serial.println(F("3: add value to function"));
    Serial.println(F("4: del function"));
    Serial.println(F("5: clear EEprom"));
};



void CommonFunctions::delFunc(){


};
void CommonFunctions::clearFunc(){
Serial.println();
    for(int i =FuncSaveStartAddress;i<=numberOfFunctions*sizeof(SMSContainer);i++){
    EEPROM.write(i,(byte)'\0');
    Serial.print("*");
    }
    Serial.println(" Done!");
};


void CommonFunctions::printAllFunc(){
    for(int i =0;i<numberOfFunctions;i++){
    printFunc(i);
    }
};
void CommonFunctions::loadFunctionsToRam(){

}


void CommonFunctions::printFunc(int slot){
    getFuncFromEEPROM(slot);
    Serial.println();
    Serial.print(F("Function: "));
    Serial.print(slot+1);
    Serial.println();
    Serial.print(F("Text: "));
    Serial.print(SMSContainer.message);
    Serial.println();
    for(int i =0;i<FuncMobnrCount;i++){
        Serial.print(F("Phone "));
        Serial.print(i+1);
        Serial.print(":");
        Serial.print(SMSContainer.phone[i]);
        Serial.println();

    }

    Serial.println();
};

void CommonFunctions::getFuncFromEEPROM(int slot){
int addr=slot*sizeof(SMSContainer);
addr=addr+FuncSaveStartAddress;
 EEPROM_readAnything(addr, SMSContainer);
};
void CommonFunctions::saveFunc(){

}

void CommonFunctions::saveFunctoEEPROM(int slot){
    int addr=slot*sizeof(SMSContainer);
    addr=addr+FuncSaveStartAddress;
     EEPROM_writeAnything(addr, SMSContainer);
};



int CommonFunctions::func(){
return SC.resvData.Function;
};
bool CommonFunctions::setVal(){
    //Serial.println(SC.resvData.GetOrSet);
if(SC.resvData.GetOrSet=='S'){return true;} else {return false;}

};

int16_t CommonFunctions::Val(){
return SC.resvData.Value;
};

bool CommonFunctions::send(int16_t val){
SC.sendData(SC.resvData.sender_address, 'S', 1, val);
};

int CommonFunctions::loadAddress(){
    address=EEPROM.read(0);
        if(((byte)address > 1) && ((byte)address < 128)) {
        return (byte)address;
        } else {
            return 127;
        }


};


void CommonFunctions::setaddress(){
Serial.println(F("Enter new address 2-127") );
bool validaddr=false;
readSerial();
uint8_t a = atoi(commandBuf);
 if((a > 1) && (a < 128)){validaddr=true;};
            if(validaddr){
                    EEPROM.write(0,(byte)a);
                    resetFunc();
            } else {
                Serial.println(F("ERROR! Invalid address. please set address 2-127"));
                help();

            }
};
void CommonFunctions::nilFuncSbuf(){



}
