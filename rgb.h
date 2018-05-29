//#define PULS_DELAY 30

#define RGB_RED    0
#define RGB_GREEN  1
#define RGB_BLUE   2
#define RGB_OFF    255

#define RGB_BLINK_DELAY 300

byte lastR = 0;
byte lastG = 0;
byte lastB = 0;
byte color = 0;
byte buttonStateOn = 255;
byte buttonStateOff = 0;
bool lastStateShort = false;
bool lastStateLong = false;
byte lastColor = 0;
//bool lastState = false;
unsigned long lastBlinkMillis = 0;



void initRGB(){
    pinMode(PIN_LED_R,OUTPUT);
    pinMode(PIN_LED_G,OUTPUT);
    pinMode(PIN_LED_B,OUTPUT);
}

void setR(byte r){
    if(r != lastR){
#ifdef EXTENDED_DEBUG
        Debug.println(F("RGB: new R: %d"), r);
#endif
        analogWrite(PIN_LED_R,r);
        lastR = r;
    }
}
void setG(byte g){
    if(g != lastG){
#ifdef EXTENDED_DEBUG
        Debug.println(F("RGB: new G: %d"), g);
#endif
        analogWrite(PIN_LED_G,g);
        lastG = g;
    }
}
void setB(byte b){
    if(b != lastB){
#ifdef EXTENDED_DEBUG
        Debug.println(F("RGB: new B: %d"), b);
#endif
        analogWrite(PIN_LED_B,b);
        lastB = b;
    }
}

void setRGB(byte r, byte g, byte b){
//#ifdef EXTENDED_DEBUG
//    Debug.println(F("RGB: setRGB: %d, %d, %d"), r,g,b);
//#endif
    setR(r);
    setG(g);
    setB(b);
}

/*

RGB Prios:
0. ProgState
1. button pressed
2. alarm (blink)
3. long press
4. short press
*/

void blinkRGB(){
    if (millis() - lastBlinkMillis >= RGB_BLINK_DELAY) {
        if(lastColor > 2) lastColor = 0;
        switch (lastColor){
            case RGB_RED:
                setRGB(255,0,0);
                break;
            case RGB_GREEN:
                setRGB(0,255,0);
                break;
            case RGB_BLUE:
                setRGB(0,0,255);
                break;
            default:
                setRGB(0,0,0);
                break;
        }
        lastColor++;
        lastBlinkMillis = millis();
    }
}


void taskRgb(){
    if(progMode){
        blinkRGB();
    }else{
        if(boolButtonPressed){//Prio 1
            switch (colorOnClickRgb){
                case RGB_RED:
                    setRGB(buttonStateOn,0,0);
                    break;
                case RGB_GREEN:
                    setRGB(0,buttonStateOn,0);
                    break;
                case RGB_BLUE:
                    setRGB(0,0,buttonStateOn);
                    break;
                default:
                    setRGB(0,0,0);
                    break;
            }
        }else{
            if(alarmRgb){//Prio 2
                //ToDo
            }else{
                if(boolLongClick){//Prio 3
                    switch (colorStateLongRgb){
                        case RGB_RED:
                            setRGB(buttonStateOn,0,0);
                            break;
                        case RGB_GREEN:
                            setRGB(0,buttonStateOn,0);
                            break;
                        case RGB_BLUE:
                            setRGB(0,0,buttonStateOn);
                            break;
                        default:
                            setRGB(0,0,0);
                            break;
                    }
                }else{
                    if(boolShortClick){//Prio 4
                        switch (colorStateShortRgb){
                        case RGB_RED:
                            setRGB(buttonStateOn,0,0);
                            break;
                        case RGB_GREEN:
                            setRGB(0,buttonStateOn,0);
                            break;
                        case RGB_BLUE:
                            setRGB(0,0,buttonStateOn);
                            break;
                        default:
                            setRGB(0,0,0);
                            break;
                        }
                    }else{//off
                        setRGB(0,0,0);
                    }
                }
            }
        }
    }
}



