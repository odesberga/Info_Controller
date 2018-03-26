#include <lcdHandler.h>
#include <SensorHandler.h>
#include <LiquidCrystal_I2C.h>




SensorHandler __SH(3);


lcdHandler::lcdHandler(){


}

void lcdHandler::begin(){

    //__SH=sh;
}
void lcdHandler::refresh(){
    int c=0;
    for(int i =0;i<__SH.SensorCount;i++){
        if(__SH._SensorData[i].PrintToScreen=='y'){
            c++;
            if(c>currpage*4){
                if(c<=currpage*4+4){
                    printToScreen(i);
                }
            }
        }
    }
}
void lcdHandler::printToScreen(int sensidx){
    _lcd.setCursor(currRow, 1);
    _lcd.print(__SH._SensorData[sensidx].SensorName);
    _lcd.print(" = ");
    _lcd.print(__SH._SensorData[sensidx].LastValue);

    if(currRow<=rowcount){
        currRow++;
    } else {
        currRow=0;
    }
}
void lcdHandler::nextPage(){
    if(currpage<pagecount){
        currpage++;
        _lcd.clear();
    };
}

void lcdHandler::prevPage(){
    if(currpage>0){currpage--;};
}
