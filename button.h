#define DEBOUNCE 80 //minimal click duration for short click

#define BTNT_INACTIV    0
#define BTNT_SHORT      2
#define BTNT_SHORT_LONG 3
#define BTNT_DIMMER     1

bool buttonTL = true;
bool buttonTR = true;
bool buttonBL = true;
bool buttonBR = true;

bool duringLongClick = false;
unsigned long clickMillis = 0;
unsigned long clickDuration = 0;

void taskOnShortClick(){
    Debug.println(F("taskOnShortClick, type: %d, value: %x"),typeBtn,valueShortClickBtn);
#ifdef KNX
    if (typeBtn == BTNT_SHORT || typeBtn == BTNT_SHORT_LONG){//short or short/long click
        if(valueShortClickBtn == V_SWITCH){//switch value
            Knx.write(COMOBJ_btnShortValue, !boolShortClick);
        }else if(valueShortClickBtn == V_VAL_0){//send 0
            Knx.write(COMOBJ_btnShortValue, 0);
        }else if(valueShortClickBtn == V_VAL_1){//send 1
            Knx.write(COMOBJ_btnShortValue, 1);
        }else if(V_SCENE_1 <= valueShortClickBtn && valueShortClickBtn <= V_SCENE_64 ){//send scene
            Knx.write(COMOBJ_btnShortScene, valueShortClickBtn);
        }
    }else if(typeBtn = BTNT_DIMMER){//dimmer switch
        Knx.write(COMOBJ_btnShortValue, !boolShortClick);
    }
#endif
}
void taskOnLongClick(){
    //Nothing to do here, see taskStartLongClick() and taskEndLongClick()
}
void taskStartLongClick(){
    duringLongClick = true;
#ifdef KNX
    Debug.println(F("taskStartLongClick, type: %d, value: %x"),typeBtn,valueLongClickBtn);
    if (typeBtn = BTNT_SHORT_LONG){//long click
        if(valueLongClickBtn == V_SWITCH){//switch value
            Knx.write(COMOBJ_btnLongValue, !boolLongClick);
        }else if(valueLongClickBtn == V_VAL_0){//send 0
            Knx.write(COMOBJ_btnLongValue, 0);
        }else if(valueLongClickBtn == V_VAL_1){//send 1
            Knx.write(COMOBJ_btnLongValue, 1);
        }else if(V_SCENE_1 <= valueLongClickBtn && valueLongClickBtn <= V_SCENE_64 ){//send scene
            Knx.write(COMOBJ_btnLongScene, valueLongClickBtn);
        }
    }
#endif
/*    Debug.println(F("taskStartLongClick"));
    if(boolShortClick){//false => decrease, true => increase
        Knx.write(COMOBJ_btnDim, B1111);//Increase, 256 Steps
    }else{
        Knx.write(COMOBJ_btnDim, B0111);//Decrease, 256 Steps
    }*/
}
void taskEndLongClick(){
    duringLongClick = false;
    Debug.println(F("taskEndLongClick"));
#ifdef KNX
    Knx.write(COMOBJ_btnDim, B1000);//Stop dimming
#endif
}

void taskButton(){
    if(boolButtonPressed && !duringLongClick && (millis() - clickMillis >= longClickDurationBtn)){
        taskStartLongClick();
    }
    if(!boolButtonPressed && duringLongClick && (millis() - clickMillis >= longClickDurationBtn)){
        taskEndLongClick();
    }
}

void interruptCallChange(){
    bool buttonTLtmp = digitalRead(PIN_SW_TL);
    bool buttonTRtmp = digitalRead(PIN_SW_TR);
    bool buttonBLtmp = digitalRead(PIN_SW_BL);
    bool buttonBRtmp = digitalRead(PIN_SW_BR);
    if(!buttonTLtmp || !buttonTRtmp || !buttonBLtmp || !buttonBRtmp){
//        Debug.println(F("at least one button pressed"));
        if(!boolButtonPressed){
            clickMillis = millis();
        }
        boolButtonPressed = true;
//        buttonPressedLED();
    }
    if(buttonTLtmp && buttonTRtmp && buttonBLtmp && buttonBRtmp){
//        Debug.println(F("all buttons released"));
        unsigned long tempMillis = millis();
        long clickDuration = tempMillis - clickMillis;
        Debug.println(F("Click duration: %d"),clickDuration);
        boolButtonPressed = false;
//        buttonReleasedLED();
        if (DEBOUNCE <= clickDuration){ //debounce
            if (clickDuration >= longClickDurationBtn){
                taskOnLongClick();
            }else{
                taskOnShortClick();
            }
        }
    }
}

void initButton(){
    pinMode(PIN_SW_TL, INPUT);
    pinMode(PIN_SW_TR, INPUT);
    pinMode(PIN_SW_BL, INPUT);
    pinMode(PIN_SW_BR, INPUT);
    attachInterrupt(PIN_SW_TL, interruptCallChange, CHANGE);
    attachInterrupt(PIN_SW_TR, interruptCallChange, CHANGE);
    attachInterrupt(PIN_SW_BL, interruptCallChange, CHANGE);
    attachInterrupt(PIN_SW_BR, interruptCallChange, CHANGE);
}
