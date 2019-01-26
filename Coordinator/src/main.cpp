#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SerialCommunication.h>
#include <SensorHandler.h>
#include <EEPROM.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <SerialConsole.h>

#define serial_resv_timeout_ms 100
uint8_t CHIPADDRESS = 1;
SoftwareSerial mySeria1(A11,A14 );
SoftwareSerial smsSeria1(16,17);
SensorHandler SH(3);
SerialCommunication SC(mySeria1,A12);
SerialCommunication smsSC(smsSeria1,0);
SerialConsole SCLI(Serial,SH);
int i=0;
int16_t val=0;
int lastval=0;
 // void processSensors;
 // void forwardMessage
int counter = 0;
int aState;
int aLastState;

void setup() {
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    pinMode(37, OUTPUT);
    digitalWrite(37, HIGH);
    //Serial.begin(9600);
    SCLI.begin(19200);
    SC.begin(CHIPADDRESS);
}


void forwardMessage(){

SC.sendData(SCLI.ForwardMessage.destAddress, SCLI.ForwardMessage.code, SCLI.ForwardMessage.Function, SCLI.ForwardMessage.firstVal, SCLI.ForwardMessage.secVal);
unsigned long m=millis();
    while (millis()<serial_resv_timeout_ms+m){
        if (SC.gotData()){
            if(SC.resvData.Function==SCLI.ForwardMessage.destAddress){
            Serial.write('!');
            Serial.write(SC.resvData.GetOrSet);
            Serial.write(" ");
            Serial.write(SC.resvData.sender_address); 
            Serial.write(" ");
            Serial.write(SC.resvData.Function);
            Serial.write(" ");
            Serial.write(SC.resvData.firstVal);
            Serial.write(" ");
            Serial.write(SC.resvData.secVal);
            Serial.write('#');
            }
        }
    }
SCLI.ForwardMessage=SCLI.emptyForwardMessage;
}
void processSensors() {
    for(int i =0;i<SH.SensorCount;i++){
        SC.sendData(SH._SensorData[i].SensorAddress, 'G', SH._SensorData[i].SensorFunction,0);
        unsigned long m=millis();
        while (millis()<serial_resv_timeout_ms+m){
                if (SC.gotData()){
                    if(SC.resvData.Function==SH._SensorData[i].SensorFunction){
                        SH._SensorData[i].CurrentValue = SC.resvData.Value;
                        bool forward=false;
                        if(SH._SensorData[i].LastValue!=SH._SensorData[i].CurrentValue){
                            SH._SensorData[i].LastValue =SH._SensorData[i].CurrentValue ;
                            if (SH._SensorData[i].ForwardSensorAddress > 0) {
                                    if (SH._SensorData[i].CurrentValue <= SH._SensorData[i].maxSensorThreshold) {
                                        if (SH._SensorData[i].CurrentValue>= SH._SensorData[i].minSensorThreshold) {
                                        forward=true;
                                    }
                            }

                            if(forward){
                                    if(SH._SensorData[i].ForwardSensorAddress!=128){
                                        SC.sendData(SH._SensorData[i].ForwardSensorAddress, 'S', SH._SensorData[i].ForwardSensorFunction, SH._SensorData[i].CurrentValue);
                                    } else {
                                    smsSC.sendData(2, 'S', SH._SensorData[i].ForwardSensorFunction, SH._SensorData[i].CurrentValue);
                                    }
                            } else {
                                 if(SH._SensorData[i].ForwardSensorAddress!=128){
                                    // SC.sendData(SH._SensorData[i].ForwardSensorAddress, 'S', SH._SensorData[i].ForwardSensorFunction, 0);
                                } else {
                                     smsSC.sendData(2, 'S', SH._SensorData[i].ForwardSensorFunction, -9999);
                                }
                            }
                        };
                    }
                    break;
                }
            }
        }
    }
}



void loop() {
processSensors();
SCLI.refresh(SH);
if (SCLI.ForwardMessage.destAddress > 0){

}
}
