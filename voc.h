#ifdef VOC_IAQ
#define CYCLE_VOC 15000 //15s
unsigned long previousVocTime = 0;
int vocPredict = 0;
byte vocState = 0;
int vocResistance = 0;
int vocTVOC = 0;

void initVOC(){
    //nothing to do, placeholder only
}

int getVOC(){
    return voc;
}

int getTVOC(){
    return tvoc;
}

void taskVOC(){
    if ((millis() - previousVocTime) >= CYCLE_VOC){
        previousVocTime = millis();
        //Datasheet page 6    
        Wire.requestFrom(ADDRESS_IAQ, 9);
        vocPredict = (Wire.read() << 8 | Wire.read());
        vocState = Wire.read();
        vocResistance = (Wire.read()& 0x00) | (Wire.read() << 16) | (Wire.read() << 8 | Wire.read());
        vocTVOC = (Wire.read() << 8 | Wire.read());
    }
#ifdef KDEBUG    
    if (vocState == 0x10) {
        Debug.println(F("VOC: Warming up..."));
    } else if (vocState == 0x00) {
        Debug.println(F("VOC: Ready"));
    } else if (vocState == 0x01) {
        Debug.println(F("VOC: Busy"));
    } else if (vocState == 0x80) {
        Debug.println(F("VOC: Error"));
    } else
        Debug.println(F("No Status, check module"));
#endif
    if(vocState == 0x00){
        voc = vocPredict;
        tvoc = vocTVOC;
#ifdef EXTENDED_DEBUG
        Debug.println(F("VOC: %d ppm, TVOC: %d ppm"), voc, tvoc);
#endif
    }
}

#endif



#ifdef VOC_CCS811
#include "src/CCS811/Adafruit_CCS811.h"      


#define CYCLE_VOC 10000 //10s
unsigned long previousVocTime = 0;
bool vocOk = false;

Adafruit_CCS811 ccs;


void initVOC(){
    if(!ccs.begin(ADDRESS_CCS811)){
          Debug.println(F("VOC: Initialization failed."));
          vocOk = false;
    }else{
          vocOk = true;
          
    }
    while(!ccs.available()); //??
}

int getVOC(){
    return voc;
}

int getTVOC(){
    return tvoc;
}

int taskVOC(){
    if ((millis() - previousVocTime) >= CYCLE_VOC){
        previousVocTime = millis();
        if(vocOk){
      
#ifdef TRH
//        ccs.compensate(getTemp(), getRH());
#endif
        
            if(ccs.available()){
                if(!ccs.readData()){
                    voc = ccs.geteCO2();
                    tvoc = ccs.getTVOC();
#ifdef EXTENDED_DEBUG
                    Debug.println(F("VOC: %d ppm, TVOC: %d ppm"), voc, tvoc);
#endif
                }
            }
        }else{
            initVOC();
        }
    }
}

#endif
