#include <Arduino.h>
#include <SoftwareSerial.h>
#include <SerialCommunication.h>
#include <SensorHandler.h>

#include <LiquidCrystal_I2C.h>

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



uint8_t CHIPADDRESS = 2;

SoftwareSerial mySeria1(10, 11);
SensorHandler mySensor(3);
SerialCommunication SC(mySeria1,CHIPADDRESS,9);
int i=0;
int16_t val=0;
int lastval=0;
void setup() {
    // put your setup code here, to run once:
    lcd.begin (20,4);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  lcd.setBacklight(HIGH);
    Serial.begin(9600);
    while (!Serial) {
      ; // wait for serial port to connect. Needed for Leonardo only
    }

    SC.begin();





}

void loop() {

    SensorData a = mySensor.getSensor(2);

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
