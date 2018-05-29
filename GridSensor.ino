/*----------
  Grid Sensor 0.4

Sensors that can be used and it i2c addresses:
T/RH:
HDC1080 0x40
HUT21D  0x40
VOC:
CCS811  0x5A 
AMS iAq Core  0x5A


  -----------*/
#define ADDRESS_HDC1080 0x40
#define ADDRESS_HUT21D  0x40
#define ADDRESS_CCS811  0x5A 
#define ADDRESS_IAQ     0x5A



//debug
#define KDEBUG
//#define EXTENDED_DEBUG 

//run with or without KNX
#define KNX

//use i2c EEPROM if the chip is soldered. in other case internal flash will be used
//#define I2C_EEPROM

//define used sensors
#define HTU21_HDC1080 //Temp + RH
#define VOC_CCS811 //VOC
#define ONEWIRE

//DOSN'T WORK YET:
//#define ANALOG_T_RH //Temp TMP36 + RH HIH4030/5030
//#define VOC_IAQ //VOC
//#define BINARY


#define ERROR_TRH -127.00
#define ERROR_VOC 0
#define ERROR_TVOC -1
#define MEASURE_CYCLE 30000 //30 sec
#define INPUTS 2

#define SENSOR_INACTIVE 0
#define ON_CHANGE       1
#define CYCLIC          2
#define DO_NOTHING      0xFF

#define V_SWITCH   0x40
#define V_VAL_0    0x50
#define V_VAL_1    0x51
#define V_SCENE_1  0x00
#define V_SCENE_64 0x3F

//global varibales

unsigned long lastMillis = 0;
float t = ERROR_TRH;
float t_last = ERROR_TRH;
float rh = ERROR_TRH;
float rh_last = ERROR_TRH;
float owt = ERROR_TRH;
float owt_last = ERROR_TRH;
int voc = ERROR_VOC;
int voc_last = 1;
int tvoc = ERROR_TVOC;
int tvoc_last = ERROR_TVOC;
float tmp_t = ERROR_TRH;
float tmp_rh = ERROR_TRH;
int tmp_voc = ERROR_VOC;
int tmp_tvoc = ERROR_VOC;
float tmp_owt = ERROR_TRH;
bool progMode = false;

//temperature
byte typeTemp;
byte diffTempUser;
uint32_t intervalTempUser;
float offsetTemp = 0.0;
byte valueTempMin;
float limitTempMin;
byte valueTempMax;
float limitTempMax;
bool lastStateTempMinMax = false;
unsigned long lastMillisTemp = 0;

//humidity
byte typeHumd;
byte diffHumdUser;
uint32_t intervalHumdUser;
float offsetHumd = 0.0;
byte valueHumdMin;
float limitHumdMin;
byte valueHumdMax;
float limitHumdMax;
bool lastStateHumdMinMax = false;
unsigned long lastMillisHumd = 0;

//VOC
byte typeVoc;
byte diffVocUser;
uint32_t intervalVocUser;
int16_t offsetVoc = 0;
byte valueVocMin;
word limitVocMin;
byte valueVocMax;
word limitVocMax;
bool lastStateVocMinMax = false;
unsigned long lastMillisVoc = 0;

//OneWire temperature
byte typeOwTemp;
byte diffOwTempUser;
uint32_t intervalOwTempUser;
float offsetOwTemp = 0.0;
byte valueOwTempMin;
float limitOwTempMin;
byte valueOwTempMax;
float limitOwTempMax;
bool lastStateOwTempMinMax = false;
unsigned long lastMillisOwTemp = 0;

//button
int typeBtn = 0;
int longClickDurationBtn = 450;
byte valueShortClickBtn;
byte valueLongClickBtn;
byte valueShortClick = 255;
byte valueLongClick = 255;
bool boolButtonPressed = false;
bool boolShortClick = false; //Dimmer: false => off, true => on
bool boolLongClick = false;
//int dimDirection = true; //false => off, true => on

//binary iputs
byte valueBinaryD0;
byte valueBinaryD1;
uint16_t binaryCycleD0 = 100;
uint16_t binaryCycleD1 = 100;
unsigned long lastMillisBinaryD0 = 0;
unsigned long lastMillisBinaryD1 = 0;

bool inputStateD0 = false;
bool inputStateD1 = false;
bool currentStateD0 = false;
bool currentStateD1 = false;
bool lastStateD0 = false;
bool lastStateD1 = false;
long outputDelayD0 = 0;
long outputDelayD1 = 0;
long lastOutputDelayD0 = 0;
long lastOutputDelayD1 = 0;

//rgb
byte typeRgb = 0;
byte brightnessTypeRgb = 0;
byte colorOnClickRgb = 2;
byte colorStateShortRgb = 1;
byte colorStateLongRgb = 0;
bool alarmRgb = false;

//night mode
bool nightMode = false;

#ifdef KNX
#include <KonnektingDevice.h>
#include "kdevice_Gridsensor.h"
#else
#include <DebugUtil.h>
#endif
#include "kdelay.h"

#include "gridsensor.h"
#include "rgb.h"
#include "button.h"
#include "binary.h"
#include "onewire.h"

#if defined(HTU21_HDC1080) || defined(ANALOG_T_RH)
#include "temp_rh.h"
#define TRH
#endif
#if defined(VOC_CCS811) || defined(VOC_IAQ)
#include "voc.h"
#define VOC
#endif

#ifdef KDEBUG
void printConfig(){
    Debug.println(F("\nConfiguration temperature:"));
    Debug.println(F("typeTemp: %d"),typeTemp);
    Debug.println(F("diffTempUser: %3.2f °C"),diffTempUser);
    Debug.println(F("intervalTempUser: %d ms"),intervalTempUser);
    Debug.println(F("offsetTemp: %3.2f °C"),offsetTemp);
    Debug.println(F("valueTempMin: %d"),valueTempMin);
    Debug.println(F("limitTempMin: %3.2f °C"),limitTempMin);
    Debug.println(F("valueTempMax: %d"),valueTempMax);
    Debug.println(F("limitTempMax: %3.2f °C"),limitTempMax);
    Debug.println(F("\nConfiguration humidity:"));
    Debug.println(F("typeHumd: %d"),typeHumd);
    Debug.println(F("diffHumdUser: %3.2f %%"),diffHumdUser);
    Debug.println(F("intervalHumdUser: %d ms"),intervalHumdUser);
    Debug.println(F("offsetHumd: %3.2f %%"),offsetHumd);
    Debug.println(F("valueHumdMin: %d"),valueHumdMin);
    Debug.println(F("limitHumdMin: %3.2f %%"),limitHumdMin);
    Debug.println(F("valueHumdMax: %d"),valueHumdMax);
    Debug.println(F("limitHumdMax: %3.2f %%"),limitHumdMax);
    Debug.println(F("\nConfiguration VOC:"));
    Debug.println(F("typeVoc: %d"),typeVoc);
    Debug.println(F("diffVocUser: %d %%"),diffVocUser);
    Debug.println(F("intervalVocUser: %d ms"),intervalVocUser);
    Debug.println(F("offsetVoc: %d ppm"),offsetVoc);
    Debug.println(F("valueVocMin: %d"),valueVocMin);
    Debug.println(F("limitVocMin: %d ppm"),limitVocMin);
    Debug.println(F("valueVocMax: %d"),valueVocMax);
    Debug.println(F("limitVocMax: %d ppm"),limitVocMax);
    Debug.println(F("\nConfiguration OneWire temperature:"));
    Debug.println(F("typeOwTemp: %d"),typeOwTemp);
    Debug.println(F("diffOwTempUser: %3.2f °C"),diffOwTempUser);
    Debug.println(F("intervalOwTempUser: %d ms"),intervalOwTempUser);
    Debug.println(F("offsetOwTemp: %3.2f °C"),offsetOwTemp);
    Debug.println(F("valueOwTempMin: %d"),valueOwTempMin);
    Debug.println(F("limitOwTempMin: %3.2f °C"),limitOwTempMin);
    Debug.println(F("valueOwTempMax: %d"),valueOwTempMax);
    Debug.println(F("limitOwTempMax: %3.2f °C"),limitOwTempMax);    
    Debug.println(F("\nConfiguration button:"));
    Debug.println(F("typeBtn: %d"),typeBtn);
    Debug.println(F("longClickDurationBtn: %d ms"),longClickDurationBtn);
    Debug.println(F("valueShortClickBtn: %d"),valueShortClickBtn);
    Debug.println(F("valueLongClickBtn: %d"),valueLongClickBtn);
    Debug.println(F("brightnessTypeRgb: %d"),brightnessTypeRgb);
    Debug.println(F("colorOnClickRgb: %d"),colorOnClickRgb);
    Debug.println(F("colorStateShortRgb: %d"),colorStateShortRgb);
    Debug.println(F("colorStateLongRgb: %d"),colorStateLongRgb);
#ifdef BINARY  
//        Debug.println(F("Input: %d  active: %d  invert: %d  delay: %d ms"),i,inputActive[i],invertOutput[i],outputDelay[i]);
#endif
}
#endif

#include "setup.h"
#include "loop.h"

#ifdef KNX
void knxEvents(byte index) {
    switch (index) {
        case COMOBJ_btnShortInput:
            boolShortClick = Knx.read(COMOBJ_btnShortInput);
            Debug.println(F("KNX event: boolShortClick: %d"),boolShortClick);
            break;
        case COMOBJ_btnLongInput:
            boolLongClick = Knx.read(COMOBJ_btnLongInput);
            Debug.println(F("KNX event: boolLongClick: %d"),boolLongClick);
            break;
        case COMOBJ_binD0ValueInput:
            inputStateD0 = Knx.read(COMOBJ_binD0ValueInput);
            Debug.println(F("KNX event: inputStateD0: %d"),inputStateD0);
            break;
        case COMOBJ_binD1ValueInput:
            inputStateD1 = Knx.read(COMOBJ_binD1ValueInput);
            Debug.println(F("KNX event: inputStateD1: %d"),inputStateD1);
            break;
        case COMOBJ_nightMode:
            nightMode = (bool) Knx.read(COMOBJ_nightMode);
            Debug.println(F("KNX event: nightMode: %d"),nightMode);
            break;
        default:
          break;
    }

};

#endif //KNX

#if ((defined(HTU21_HDC1080) && defined(ANALOG_T_RH)))
#error "Please define only one of this sensors: HTU21_HDC1080 or ANALOG_T_RH"
#endif
#if (defined(VOC_CCS811) && defined(VOC_IAQ))
#error "Please define only one of this sensors: VOC_CCS811 or VOC_IAQ"
#endif
#ifdef KNX
#ifndef KONNEKTING_DEVICE_LIBRARY_VERSION
#error "This sketch requires beta4a version of KONNEKTING Library"
#endif
#endif
