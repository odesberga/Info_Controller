#include <ModuleCommonFunctions.h>
#include <SerialCommunication.h>
#include <modulemainclass.h>
#include "modulePotentiometer.h"
//#include <Description.h>
#include <EEPROM.h>
#define SofSerialRXPin 10
#define SofSerialTXPin 12
#define RS485EnablePin 11
SoftwareSerial mySeria1( SofSerialRXPin,SofSerialTXPin);
SerialCommunication SC(mySeria1,RS485EnablePin);
char address;
char pMemBuf[10];
char commandBuf[5];

#define numberOfFunctions 20
#define FuncByteCount 4
module* M[numberOfFunctions];
modPot *pot;
//byte FunctionList[numberOfFunctions][FuncByteCount];
int funcCount=0;
char funcBuf[FuncByteCount];
CommonFunctions::CommonFunctions(){
};
// new
void * operator new (size_t size) { return malloc (size); }
// placement new
void * operator new (size_t size, void * ptr) { return ptr; }
// delete
void operator delete (void * ptr) { free (ptr); }

void CommonFunctions::ProcessFunctions(byte *Function,bool set,int16_t *setval){

for(int i=0;i<=funcCount;i++){
    if(M[i]->funcNum() == Function){
        if(set){
        // if(SC.resvData.GetOrSet=='S'){
            M[i]->setVal(setval);
        } else {

            SC.sendData(SC.resvData.sender_address, 'S', Function, M[i]->getVal());
        //    Serial.println(M[i]->getVal());
            break;
        }
    }
}
}
void CommonFunctions::RefreshFunctions(){
    for(int i=0;i<funcCount;i++){
                M[i]->refresh();

    }
}
void CommonFunctions::CreateFunction(byte PIN,byte func,byte subfunc,byte funcnumb){
    switch(func)    {
        case 0:
         M[funcCount] = new(modPot);
         M[funcCount]->begin(subfunc, PIN,funcnumb);


         break;
    }

}
void CommonFunctions::printsubc(int func,byte subfunc){
switch(func) {
    case 0:
    modPot B;
    B.printSubfuncs(subfunc);
     break;
}

}


void CommonFunctions::begin(){

SC.begin(loadAddress());
Serial.print(F("Current address = "));
Serial.print(SC.ownAddress());
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
                resetFunc();
                break;
            case 4:
                delFunc();
                printAllFunc();
                resetFunc();
                help();
                break;
            case 5:
                clearFunc();
                resetFunc();
                help();
                break;
            default:
            help();
            break;
    }

}


void CommonFunctions::addFunc(){
int fnmbr=0;
int a;
Serial.println();
memset(funcBuf,0,sizeof(funcBuf));
printAllFunc();
Serial.println();
Serial.println();

Serial.println(F("Enter function number:"));
readSerial();
a=atoi(commandBuf);
funcBuf[3]=(byte)a;

    Serial.println(F("Select PIN"));
    for(int i =0;i<PINS_CollectionCount;i++){
    Serial.print(i+1);
    Serial.print(" :");
    Serial.println(PINS_Collection[i].name);
    };
    readSerial();
    a=atoi(commandBuf);
    a--;
    funcBuf[0]=(byte)a;

    Serial.println();
    Serial.println();
    Serial.println(F("Select function"));
    for(int i =0;i<FUNCS_CollectionCount;i++){
    Serial.print(i);
    Serial.print(" :");
    Serial.println( FUNCS_Collection[i].name );
    };
    readSerial();
    a=atoi(commandBuf);
    funcBuf[1]=(byte)a;

    Serial.println();
    Serial.println();
    Serial.println(F("Select subfunction (result type)"));
    printsubc(atoi(commandBuf),100);
    readSerial();
    a=atoi(commandBuf);
    funcBuf[2]=(byte)a;

    saveFunc();
};









void CommonFunctions::help(){
    Serial.println();
    Serial.println();
    Serial.println(F("1: set address"));
    Serial.println(F("2: list functions"));
    Serial.println(F("3: add function"));
    Serial.println(F("4: del function"));
    Serial.println(F("5: clear EEprom"));
};



void CommonFunctions::delFunc(){
    Serial.println();
    printAllFunc();
    Serial.println();
    Serial.print(F("Select slot to delete"));
    Serial.println();
    readSerial();
    memset(funcBuf,0,sizeof(funcBuf));
    saveFunctoEEPROM(atoi(commandBuf));

};
void CommonFunctions::clearFunc(){
    memset(funcBuf,0,sizeof(funcBuf));
    for(int i=1;i<numberOfFunctions+1;i++){
        saveFunctoEEPROM(i);
        Serial.print(F("*"));

    };
Serial.print(F(" Done!"));
Serial.println();

};


void CommonFunctions::printAllFunc(){
    Serial.println();
    Serial.println();
    Serial.print(F("Slot:"));
    Serial.print('\t');
    Serial.print(F("PIN:"));
    Serial.print('\t');
    Serial.print('\t');
    Serial.print(F("Function:"));
    Serial.print('\t');
    Serial.print('\t');
    Serial.print(F("Type:"));
    Serial.print('\t');
    Serial.print('\t');
    Serial.println(F("Number:"));

    for(int i=1;i<numberOfFunctions+1;i++){
    printFunc(i);
    };
};
void CommonFunctions::loadFunctionsToRam(){
//memset(FunctionList,0,sizeof(FunctionList[0][0]) * numberOfFunctions *FuncByteCount);
int j =0;
for(int i=1;i<numberOfFunctions+1;i++){
    getFuncFromEEPROM(i);
    if(funcBuf[0]!=0){
        // FunctionList[j][0]=funcBuf[0];
        // FunctionList[j][1]=funcBuf[1];
        // FunctionList[j][2]=funcBuf[2];
        // FunctionList[j][3]=funcBuf[3];
            CreateFunction(PINS_Collection[(byte)funcBuf[0]].pin ,(byte)funcBuf[1],(byte*)funcBuf[2],(byte*)funcBuf[3]);
        funcCount++;
    }
};
}


void CommonFunctions::printFunc(int slot){
    getFuncFromEEPROM(slot);
    if((byte)funcBuf[0] != 0){
        Serial.println();
Serial.print(slot);
Serial.print('\t');
Serial.print((char*)PINS_Collection[funcBuf[0]].name);
Serial.print('\t');
Serial.print('\t');
Serial.print((char*)FUNCS_Collection[funcBuf[1]].name);
Serial.print('\t');
Serial.print('\t');
printsubc((byte*)funcBuf[1],(byte*)funcBuf[2]);
Serial.print('\t');
Serial.print('\t');
Serial.print((byte)funcBuf[3]);
};
};

void CommonFunctions::getFuncFromEEPROM(int slot){
memset(funcBuf,0,sizeof(funcBuf));

funcBuf[0]=EEPROM.read(slot*FuncByteCount);
funcBuf[1]=EEPROM.read((slot*FuncByteCount)+1);
funcBuf[2]=EEPROM.read((slot*FuncByteCount)+2);
funcBuf[3]=EEPROM.read((slot*FuncByteCount)+3);

};
void CommonFunctions::saveFunc(){
    bool saved=false;
    for(int i=1;i<numberOfFunctions+1;i++){
        if(EEPROM.read(i*FuncByteCount)==0){
            saveFunctoEEPROM(i);
            Serial.println(F("Done!"));
            saved=true;
            break;
        };
    };
if(!saved){
    Serial.println();
    Serial.println(F("Error! No empty slots!"));
}
}

void CommonFunctions::saveFunctoEEPROM(int slot){

EEPROM.write(slot*FuncByteCount,funcBuf[0]);
EEPROM.write((slot*FuncByteCount)+1,funcBuf[1]);
EEPROM.write((slot*FuncByteCount)+2,funcBuf[2]);
EEPROM.write((slot*FuncByteCount)+3,funcBuf[3]);


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

// bool CommonFunctions::testChar(char *c){
//     bool found = false;
    // char t[10]{'0','1','2','3','4','5','6','7','8','9'};
    // for(int i =0;i<10;i++){
    //     if(c=t[i]){
    //     found=true;
    //     break;
    //     };
    // };
//     return found;
// };

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
