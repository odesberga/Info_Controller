#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SerialCommunication.h>
#include <SensorHandler.h>
#include <SPI.h>
#include <Ethernet.h>
#include <SD.h>
#include <LiquidCrystal_I2C.h>
#include <SerialConsole.h>
/*
#define I2C_ADDR 0x3f
#define Rs_pin 0
#define Rw_pin 1
#define En_pin 2
#define BACKLIGHT_PIN 3
#define D4_pin 4
#define D5_pin 5
#define D6_pin 6
#define D7_pin 7*/
byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
IPAddress ip(192, 168, 6, 3);
EthernetServer server(80);
LiquidCrystal_I2C lcd(0x27,20,4);
//LiquidCrystal_I2C lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
uint8_t CHIPADDRESS = 2;
SoftwareSerial mySeria1(14, 15);
SensorHandler SH(3);
SerialCommunication SC(mySeria1,CHIPADDRESS,9);
SerialConsole SCLI(Serial);

int i=0;
int16_t val=0;
int lastval=0;

//Prototypes
//////////////////////////////////////////////////////////////////////////////////

void t(void);
void fillSensorsFromFile();
void showsensor(uint8_t address,uint8_t func);


//////////////////////////////////////////////////////////////////////////////////

void setup() {
    pinMode(10, OUTPUT);
    digitalWrite(10, HIGH);

    lcd.begin (20,4);
    //lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
    //lcd.setBacklight(HIGH);
    //Serial.begin(9600);
    SCLI.begin(9600,SH);
    SC.begin();

    Serial.println("Initializing SD card...");
       if (!SD.begin(4)) {
           Serial.println("ERROR - SD card initialization failed!");
           return;    // init failed
       }

       if (!SD.exists("SENSORS")) {
            Serial.println("ERROR - Can't find SENSORS file!");
            return;  // can't find index file
        } else {
        Serial.println("SUCCESS - Found SENSORS file.");
        }
    Ethernet.begin(mac, ip);  // initialize Ethernet device
    server.begin();
    fillSensorsFromFile();
    showsensor(2,1);
}

void loop() {

//    SensorData a = SH.getSensor(2);

    delay(30);
    if (SC.gotData()){
        lcd.setCursor(2, 1);
        lcd.print("         ");
        lcd.setCursor(1, 1);
        //lcd.print(SC.resvData.Value);
    //    delay(100);
        lcd.print(SC.resvData.sender_address);
        lcd.print(SC.resvData.GetOrSet);
        lcd.print(SC.resvData.Function);
        lcd.print(SC.resvData.Value);
    };

}

void fillSensorsFromFile() {
    File RuleFile;
    char a[60];
    RuleFile = SD.open("SENSORS");
           while (RuleFile.available()) {
          String aString = RuleFile.readStringUntil('#');
          aString.toCharArray(a,60);
          SH.add(a);
           }
    RuleFile.close();
}

void showsensor(uint8_t address,uint8_t func){
    SensorData aSensordata;
//    aSensordata = SH.getSensor(address,func);
    Serial.println("Sensor:");

    Serial.println("Name Address Function Threshold ThresholdPosNeg Alarmlevel PrintToScreen ForwardSensorAddress ForwardSensorFunction");

    for(int i = 0;i<SH.sensorCount();i++){
        aSensordata=SH._SensorData[i];
    Serial.print(String(aSensordata.SensorName));
    Serial.print("  ");
    Serial.print(String(aSensordata.SensorAddress));
    Serial.print("  ");
    Serial.print(String(aSensordata.SensorFunction));
    Serial.print("  ");
    Serial.print(String(aSensordata.SensorThreshold));
    Serial.print("  ");
    Serial.print(String(aSensordata.ThresholdPosNeg));
    Serial.print("  ");
    Serial.print(String(aSensordata.Alarmlevel));
    Serial.print("  ");
    Serial.print(String(aSensordata.PrintToScreen));
    Serial.print("  ");
    Serial.print(String(aSensordata.ForwardSensorAddress));
    Serial.print("  ");
     Serial.println(String(aSensordata.ForwardSensorFunction));
}

}
