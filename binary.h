#ifdef BINARY
void initBinary(){
    
}

bool getBinaryState(int pinNumber){
    pinMode(pinNumber, INPUT_PULLUP);
    bool actualState = !digitalRead(pinNumber);
    pinMode(pinNumber, OUTPUT);
    return actualState;
}
#endif
