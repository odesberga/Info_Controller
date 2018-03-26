#include <SensorHandler.h>
#include <SD.h>
#include "Arduino.h"
#include <EEPROM.h>



SensorHandler::SensorHandler(int count){
addFromEEPROM();
};

void SensorHandler::add(char * SensorStr){
  char intBuffer[6];
  int commacount=0;
  int idx=0;
  int j=0;
  int emptySensoridx=0;
            j=SensorCount;
            SensorCount++;
            for (int i =0; i< 61;i++){
                if (SensorStr[i]=='\0'){
                    break;};
                if (SensorStr[i]==','){
                  commacount++;
                  idx=0;
                  memset(intBuffer, 0, 6);
                } else {
                  switch (commacount) {
                    case 0:
                    if (idx<=NameLength)
                      _SensorData[j].SensorName[idx] = SensorStr[i];
                      break;
                    case 1:
                        intBuffer[idx]= SensorStr[i];
                        intBuffer[idx+1]= '\0';
                        _SensorData[j].SensorAddress = atoi(intBuffer);
                      break;
                    case 2:
                    intBuffer[idx]= SensorStr[i];
                    intBuffer[idx+1]= '\0';
                    _SensorData[j].SensorFunction = atoi(intBuffer);
                        break;
                    case 3:
                        intBuffer[idx]= SensorStr[i];
                        intBuffer[idx+1]= '\0';
                        _SensorData[j].SensorThreshold = atoi(intBuffer);
                        break;
                    case 4:
                        _SensorData[j].ThresholdPosNeg = SensorStr[i];
                        break;
                    case 5:
                        _SensorData[j].Valtype = SensorStr[i];
                        break;
                    case 6:
                        _SensorData[j].PrintToScreen = SensorStr[i];
                        break;
                    case 7:
                        intBuffer[idx]= SensorStr[i];
                        intBuffer[idx+1]= '\0';
                        _SensorData[j].ForwardSensorAddress = atoi(intBuffer);
                        break;
                    case 8:
                        intBuffer[idx]= SensorStr[i];
                        intBuffer[idx+1]= '\0';
                        _SensorData[j].ForwardSensorFunction = atoi(intBuffer);
                        break;
                  }
                  idx++;
                }
            }
}


SensorData SensorHandler::getSensor(char * sensorname,uint8_t Address,uint8_t Function,int16_t CurrValue){
for (int j =0; j< SensorCount+1;j++){
    if ((_SensorData[j].SensorName==sensorname) && (_SensorData[j].SensorAddress==Address) && (_SensorData[j].SensorFunction==Function)){
         _SensorData[j].LastValue=CurrValue;
        return _SensorData[j];
        break;}
    }
}
int SensorHandler::sensorCount() {return SensorCount;};

void SensorHandler::clearEEPROM(int slot){
    int c=EEslotlength;
    c++;
    c=c*slot;

    for(int i =c;i<= c+EEslotlength;i++){
            EEPROM.write(i, 0);
    }
};

void SensorHandler::getStringFromEEPROM(int slot, String &retstring){
    char tmp[EEslotlength]="";
    retstring="";
    int c=EEslotlength;
    c++;
    c=c*slot;
            if(EEPROM.read(c)!=0) {
                int writeaddr= 0;
                memset(tmp, 0, sizeof(tmp));
                for(int i =c;i < c+EEslotlength+1;i++){
                    if(EEPROM.read(i)!=0) {
                    tmp[writeaddr] =  EEPROM.read(i);
                    tmp[writeaddr+1] ='\0';
                    writeaddr++;
                    } else {
                        retstring=(String)tmp;
                        break;
                    }
                }
            }
}

void SensorHandler::addFromEEPROM(){
for(int j =1;j<= SensorMaxCount;j++){
    String aString;
    char a[60];
    getStringFromEEPROM(j,aString);
    if(aString.length() > 1){
        aString.toCharArray(a,60);
        add(a);
    }
}
};

bool SensorHandler::delFromEEPROM(char *sensorName){
    bool deleted=false;
    bool found=false;
    int readaddr = 0;
    int c = EEslotlength;
    c++;
    char tmp[NameLength+1]="";
    for(int j =1;j<= SensorMaxCount;j++){
        for(int i =c*j;i<(c*j)+NameLength+1;i++){
                if(EEPROM.read(i)!=0) {
                    if(EEPROM.read(i)!=',') {
                        tmp[readaddr]=EEPROM.read(i);
                        tmp[readaddr+1]='\0';
                        readaddr++;
                    } else {
                        if(strcmp(tmp,sensorName)==0){
                            found=true;
                            break;
                        } else {
                            memset(tmp, 0, sizeof(tmp));
                            found=false;
                            readaddr=0;

                            break;
                        }
                    }
                } else {
                    break;
                }

            }
        if(found){
            clearEEPROM(j);
            deleted=true;
            break;
        }

    }

return deleted;
};
bool SensorHandler::saveToEEPROM(char *SensorStr,int len){
    bool saved=false;
    int tmp=0;
    int c=EEslotlength;
    c++;
    for(int j =1;j<= SensorMaxCount;j++){
        if(EEPROM.read(c*j)==0) {
            int writeaddr= c*j;
            for(int i =0;i < len+1;i++){
                tmp=writeaddr+i;
                EEPROM.write(tmp, SensorStr[i]);

                //writeaddr++;
            }
            saved=true;
            break;
        } else {
        saved=false;
        }
    }
return saved;
};


bool SensorHandler::loadfromsd(char* filename){
File RuleFile;
char a[EEslotlength];
 if (!SD.exists(filename)) {
     return false;
 } else {
     RuleFile = SD.open(filename);
       while (RuleFile.available()) {
          String aString = RuleFile.readStringUntil('\n');
          Serial.println(aString);
          aString.toCharArray(a,EEslotlength);
          saveToEEPROM(a,EEslotlength);
       }
       RuleFile.close();
       return true;
}
}
bool SensorHandler::savetosd(char* filename){

     File RuleFile = SD.open(filename, FILE_WRITE);
      if (RuleFile) {
        for(int i=1;i<SensorMaxCount+1;i++){
            String aString;
            getStringFromEEPROM(i,aString);
            if(aString.length()>1){
                RuleFile.println(aString);
            }
        }
       RuleFile.close();
       return true;
   } else {return false;};
}
bool SensorHandler::deletefromsd(char* filename){
    if (SD.exists(filename)){
        SD.remove(filename);
        return true;
}
else {
    Serial.print(filename);
    Serial.println(F(" doesn't exist."));
    return false;
}

};

bool SensorHandler::lssd(){
    File root;
    root = SD.open("/");
      listsd(root, 0);
}

bool SensorHandler::listsd(File dir, int numTabs){
    dir.rewindDirectory();
    while(true) {
           File entry =  dir.openNextFile();
           if (! entry) {
             break;
           }
           for (uint8_t i=0; i<numTabs; i++) {
             Serial.print('\t');
           }
           Serial.print(entry.name());

           Serial.print("\t\t");
           Serial.println(entry.size(), DEC);

           entry.close();
     }
};
bool SensorHandler::catfilesd(char* filename){
    File RuleFile;
    if (!SD.exists(filename)) {
        return false;
    } else {
         Serial.println(filename);
         Serial.println();
        RuleFile = SD.open(filename);
          while (RuleFile.available()) {
             String aString = RuleFile.readStringUntil('\n');
             Serial.println(aString);
          }
          RuleFile.close();
          return true;
    }
};
