#include <Arduino.h>
#include <ModuleCommonFunctions.h>
#include <SerialCommunication.h>
// #include <modulemainclass.h>
// #include "modulePotentiometer.h"




CommonFunctions CF;
//Servo myservo;
//module M[numberOfFunctions];

void setup() {
    Serial.begin(19200);
    Serial3.begin(19200);
     while (!Serial) {};
      Serial.println();
     Serial.println("INIT");
     digitalWrite(9, HIGH);
    delay(1000);
    digitalWrite(9, LOW);

     //delay(25000);
     Serial3.print("AT+CLIP=1\r");



CF.begin();
}

void loop() {
    CF.RefreshFunctions();
    if(CF.gotData()){

    }
CF.RefreshFunctions();

}
