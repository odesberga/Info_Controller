#include <Arduino.h>
#include <Servo.h>
#include <ModuleCommonFunctions.h>
// #include <modulemainclass.h>
// #include "modulePotentiometer.h"

CommonFunctions CF;
//Servo myservo;
//module M[numberOfFunctions];

void setup() {
    Serial.begin(9600);
     while (!Serial) {};
      Serial.println();
     Serial.println("INIT");
CF.begin();
}

void loop() {
    CF.RefreshFunctions();
    if(CF.gotData()){
        //CF.ProcessFunctions(CF.func(),CF.setVal(),CF.Val());





    }
}
