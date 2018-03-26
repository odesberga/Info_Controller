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
#define I2C_ADDR 0x3f
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define BACKLIGHT_PIN 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7
LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

#define charrow 20
#define columncount 1
#define charcolumn charrow/columncount
int rowcount =4;
int currpage=0;
int currRow=0;

int pagecount=1;
#define serial_resv_timeout_ms 30

EthernetServer server(80);

byte mac[] = {
  0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
//IPAddress ip(192,168,1,177);
uint8_t ipaddr[4];
uint8_t CHIPADDRESS = 1;
SoftwareSerial mySeria1(A11,A14 );
SensorHandler SH(3);
SerialCommunication SC(mySeria1,A12);
SerialConsole SCLI(Serial);
int i=0;
int16_t val=0;
int lastval=0;
#define LcdTimeOut 1
unsigned long lcdrefreshtmout=0;

//Prototypes
//////////////////////////////////////////////////////////////////////////////////



void printToScreen(int sensidx);
void nextPage();
void prevPage();
void lcdrefresh();
void readEnc();
void processSensors();
void startethernet();
void webhandle();
//////////////////////////////////////////////////////////////////////////////////
#define outputA A8
#define outputB A9
int counter = 0;
int aState;
int aLastState;
void setup() {
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);
    pinMode(37, OUTPUT);
    digitalWrite(37, HIGH);


    //Serial.begin(9600);
    SCLI.begin(9600);
    SC.begin(CHIPADDRESS);

    Serial.println(F("Initializing SD card..."));
       if (!SD.begin(4)) {
           Serial.println(F("ERROR - SD card initialization failed!"));
           return;    // init failed
       }
    lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    lcd.setBacklight(HIGH);
    lcd.clear();
    lcd.begin (20,4);
    lcd.setCursor(1, 0);
    lcd.print(F("Welcome!"));
    pinMode (outputA,INPUT);
pinMode (outputB,INPUT);
startethernet();
}

void loop() {
processSensors();
    if(millis() > lcdrefreshtmout+(LcdTimeOut*1000) ){
        lcdrefresh();
        webhandle();
        lcdrefreshtmout=millis();
}
readEnc();
SCLI.refresh(SH);
}



void processSensors() {

    for(int i =0;i<SH.SensorCount;i++){
        SC.sendData(SH._SensorData[i].SensorAddress, 'G', SH._SensorData[i].SensorFunction,0);
        delay(10);
        unsigned long m=millis();
        while (millis()<serial_resv_timeout_ms+m){
            if (SC.gotData()){
                delay(10);
                SensorData aSensordata=SH.getSensor(SH._SensorData[i].SensorName,SC.resvData.sender_address,SC.resvData.Function,SC.resvData.Value);
                bool forward=false;
                    //Serial.println(SC.resvData.Value);

                if (aSensordata.ForwardSensorAddress > 0) {
                    if (aSensordata.ThresholdPosNeg=='-') {
                        if (aSensordata.SensorThreshold<aSensordata.LastValue) {
                            forward=true;
                        }
                    } else {
                        if (aSensordata.SensorThreshold>aSensordata.LastValue) {
                            forward=true;
                        }
                }
                if(forward){
                    delay(10);
                //    SC.sendData(aSensordata.ForwardSensorAddress, 'S', aSensordata.ForwardSensorFunction, aSensordata.LastValue);
                }

            }
            break;
        }


        }
    }

}


void readEnc(){
    aState = digitalRead(outputA);
    if (aState != aLastState){
      if (digitalRead(outputB) != aState) {
        nextPage();
      } else {
        prevPage();
      }
    }
    aLastState = aState;
  }






void printToScreen(int sensidx){
    int i=3;
    lcd.setCursor(0,currRow);
    lcd.print(SH._SensorData[sensidx].SensorName);
    lcd.print(" = ");
    lcd.print(SH._SensorData[sensidx].LastValue);
    if(SH._SensorData[sensidx].Valtype != '0'){
    lcd.print(SH._SensorData[sensidx].Valtype);};
    lcd.print("  ");


    if(currRow<=rowcount){
        currRow++;
    } else {
        currRow=0;
    }
}
void nextPage(){
    if(currpage<pagecount){
        currpage++;
        lcd.clear();
        lcdrefresh();
    };
}

void prevPage(){
    if(currpage>0){
        currpage--;
        lcd.clear();
        lcdrefresh();
    };
}

void lcdrefresh(){

    int c=0;
    currRow=0;
    for(int i =0;i<SH.SensorCount;i++){
        if(SH._SensorData[i].PrintToScreen=='y'){
            c++;

            if(c>currpage*rowcount){
                if(c<=currpage*rowcount+rowcount){
                    printToScreen(i);
                }
            }
        }
    }
}

void startethernet(){
    int startidx=EEslotlength;
    startidx++;
    startidx=startidx*(SensorMaxCount+1);
    startidx++;
    int i=0;
    int j=0;
    int k=0;
    char buff[3];
    char b;
    while(true){
        b=EEPROM.read(startidx+i);
        if(b=='\0'){
            ipaddr[j]=atoi(buff);
            break;
        } else {
            if(b=='.'){
                ipaddr[j]=atoi(buff);

                memset(buff,0,3);
                j++;
                k=0;
            } else {
            buff[k]=b ;
            k++;
            }
        }
        i++;
    };

Ethernet.begin(mac, ipaddr);
server.begin();
Serial.print(F("IP address: "));
Serial.println(Ethernet.localIP());
}
void webhandle(){
    EthernetClient client = server.available();      if (client) {

        boolean currentLineIsBlank = true;
        while (client.connected()) {
          if (client.available()) {
            char c = client.read();
            if (c == '\n' && currentLineIsBlank) {

              client.println(F("HTTP/1.1 200 OK"));
              client.println(F("Content-Type: text/html"));
              client.println(F("Connection: close"));
    	      client.println(F("Refresh: 3"));
              client.println();
              client.println(F("<!DOCTYPE HTML>"));
              client.println(F("<html>"));
              client.print(F("Module: "));
              client.print(F("&emsp;"));
              client.print(F("&emsp;"));
              client.print(F("Value: "));
              client.println(F("<br />"));
                for(int i =0;i<SH.SensorCount;i++){
                    if (SH._SensorData[i].PrintToScreen=='y') {
                        client.print(SH._SensorData[i].SensorName);
                        client.print(F("&emsp;"));
                        client.print(F("&emsp;"));
                        client.print(F("="));
                        client.print(F("&emsp;"));
                        client.print(F("&emsp;"));
                        client.print(SH._SensorData[i].LastValue);
                        if(SH._SensorData[i].Valtype != '0'){
                        client.print(SH._SensorData[i].Valtype);};
                        client.println(F("<br />"));

                    }

                }
              client.println(F("</html>"));
              break;
            }
            if (c == '\n') {
              // you're starting a new line
              currentLineIsBlank = true;
            }
            else if (c != '\r') {
              // you've gotten a character on the current line
              currentLineIsBlank = false;
            }
          }
        }
        // give the web browser time to receive the data
        delay(1);
        // close the connection:
        client.stop();

      }



}
