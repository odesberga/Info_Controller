#include <modulemainclass.h>




module::module(){


};
void module::begin(int subfunc,int pin, int funcnum){
_PIN=pin;
_subfunc=subfunc;
_funcnum=funcnum;
};
void module::setVal(int16_t value){

};
void module::refresh(){

};
int module::getVal(){

};
void module::printSubfuncs(byte subfunc){

}
bool module::hasfunc(){
    return false;
}
int module::funcNum(){
    return _funcnum;
};
