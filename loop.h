void loop() {

#ifdef KNX
    Knx.task();
    if (Konnekting.isReadyForApplication()) {
#endif //KNX
    taskButton();
    taskRgb();
#ifdef TRH
    taskTRH();
#endif //TRH
#ifdef VOC
    taskVOC();
#endif //VOC
#ifdef ONEWIRE
    taskOneWire();
#endif //ONEWIRE
         unsigned long currentMillis = millis();
         if (currentMillis - lastMillis >= MEASURE_CYCLE) {
            unsigned long measBegin = millis();
            Debug.println(F("\nValues to send: "));
#ifdef TRH
            tmp_t = getTemp();
            tmp_rh = getRH();
            Debug.println(F("Temp: \t%3.2f °C"), tmp_t);
            Debug.println(F("RH: \t%3.2f %%"), tmp_rh);
#endif //TRH
#ifdef VOC
            tmp_voc = getVOC();
            tmp_tvoc = getTVOC();
            Debug.println(F("VOC: \t%d ppm"), tmp_voc);
            Debug.println(F("tVOC: \t%d ppm"), tmp_tvoc);
#endif //VOC
#ifdef ONEWIRE
            tmp_owt = getOneWireTemp();
            Debug.println(F("OwTemp:\t%3.2f °C"), tmp_owt);
#endif //ONEWIRE
            Debug.println(F(""));
            lastMillis = currentMillis;
         
#ifdef KNX
#ifdef TRH
            //Temperature
            if(tmp_t != ERROR_TRH) {
                if(typeTemp == ON_CHANGE){
                    if(abs((int16_t)((tmp_t - t_last)*100)) >= (int16_t)diffTempUser*10){
                        Debug.println(F("KNX send (diff):\tTemp: \t%3.2f °C to comObj:\t%d"), tmp_t, COMOBJ_tempValue);
                        Knx.write(COMOBJ_tempValue, tmp_t);
                        t_last = tmp_t;
                    }
                }
                if(valueTempMin != DO_NOTHING){
                    if(tmp_t <= limitTempMin){
                        bool tmpValue = (bool)valueTempMin;
                        if(lastStateTempMinMax != tmpValue){
                            Debug.println(F("KNX send (LimMin):\tTemp: \t%3.2f °C, LimMin: \t%3.2f °C, value:\t%d to comObj:\t%d"), tmp_t, limitTempMin, tmpValue, COMOBJ_tempSendValue);
                            Knx.write(COMOBJ_tempSendValue, tmpValue);
                            lastStateTempMinMax = tmpValue;
                        }
                    }
                }
                if(valueTempMax != DO_NOTHING){
                    if(tmp_t >= limitTempMax){
                        bool tmpValue = (bool)valueTempMax;
                        if(lastStateTempMinMax != tmpValue){
                            Debug.println(F("KNX send (LimMax):\tTemp: \t%3.2f °C, LimMax: \t%3.2f °C, value:\t%d to comObj:\t%d"), tmp_t, limitTempMax, tmpValue, COMOBJ_tempSendValue);
                            Knx.write(COMOBJ_tempSendValue, tmpValue);
                            lastStateTempMinMax = tmpValue;
                        }
                    }
                }
            }
            
            //Humidity
            if(tmp_rh != ERROR_TRH) {
                if(typeHumd == ON_CHANGE){
                    if(abs((int16_t)((tmp_rh - rh_last)*100)) >= (int16_t)diffHumdUser*10){
                        Debug.println(F("KNX send (diff):\tRH: \t%3.2f %%  to comObj:\t%d"), tmp_rh, COMOBJ_rhValue);
                        Knx.write(COMOBJ_rhValue, tmp_rh);
                        rh_last = tmp_rh;
                    }
                }
                if(valueHumdMin != DO_NOTHING){
                    if(tmp_rh <= limitHumdMin){
                        bool tmpValue = (bool)valueHumdMin;
                        if(lastStateHumdMinMax != tmpValue){
                            Debug.println(F("KNX send (LimMin):\tRH: \t%3.2f %%, LimMin: \t%3.2f %%, value:\t%d to comObj:\t%d"), tmp_rh, limitHumdMin, tmpValue, COMOBJ_rhSendValue);
                            Knx.write(COMOBJ_rhSendValue, tmpValue);
                            lastStateHumdMinMax = tmpValue;
                        }
                    }
                }
                if(valueHumdMax != DO_NOTHING){
                    if(tmp_rh >= limitHumdMax){
                        bool tmpValue = (bool)valueHumdMax;
                        if(lastStateHumdMinMax != tmpValue){
                            Debug.println(F("KNX send (LimMin):\tRH: \t%3.2f %%, LimMax: \t%3.2f %%, value:\t%d to comObj:\t%d"), tmp_rh, limitHumdMax, tmpValue, COMOBJ_rhSendValue);
                            Knx.write(COMOBJ_rhSendValue, tmpValue);
                            lastStateHumdMinMax = tmpValue;
                        }
                    }
                }
            }    
#endif //TRH
#ifdef VOC
            //VOC
            if(tmp_voc != ERROR_VOC) {
                if(typeVoc == ON_CHANGE){
                    byte diffVoc = 1;
                    if (voc_last >= tmp_voc && tmp_voc > 0){
                        diffVoc = 100 - tmp_voc*100/voc_last;
                        
                    }else{
                        diffVoc = 100 - voc_last*100/tmp_voc;
                    }
                    if(diffVoc > diffVocUser){
                        Debug.println(F("KNX send (diff):\tVOC: \t%d ppm to comObj:\t%d"), tmp_voc, COMOBJ_vocValue);
                        Debug.println(F("KNX send (diff):\ttVOC: \t%d ppm to comObj:\t%d"), tmp_tvoc, COMOBJ_tvocValue);
                        Knx.write(COMOBJ_vocValue, tmp_voc);
                        Knx.write(COMOBJ_tvocValue, tmp_tvoc);
                        voc_last = tmp_voc;
                    }
                }
                if(valueVocMin != DO_NOTHING){
                    if(tmp_voc <= limitVocMin){
                        bool tmpValue = (bool)valueVocMin;
                        if(lastStateVocMinMax != tmpValue){
                            Debug.println(F("KNX send (LimMin):\tVOC: \t%d ppm, LimMin: \t%d ppm, value:\t%d to comObj:\t%d"), tmp_voc, limitVocMin, tmpValue, COMOBJ_vocSendValue);
                            Knx.write(COMOBJ_vocSendValue, tmpValue);
                            lastStateVocMinMax = tmpValue;
                        }
                    }
                }
                if(valueVocMax != DO_NOTHING){
                    if(tmp_voc >= limitVocMax){
                        bool tmpValue = (bool)valueVocMax;
                        if(lastStateVocMinMax != tmpValue){
                            Debug.println(F("KNX send (LimMax):\tVOC: \t%d ppm, LimMax: \t%d ppm, value:\t%d to comObj:\t%d"), tmp_voc, limitVocMax, tmpValue, COMOBJ_vocSendValue);
                            Knx.write(COMOBJ_vocSendValue, tmpValue);
                            lastStateVocMinMax = tmpValue;
                        }
                    }
                }
            }    
#endif //VOC
#ifdef ONEWIRE
            //OneWire Temperature
            if(tmp_owt != ERROR_TRH) {
                if(typeTemp == ON_CHANGE){
                    if(abs((int16_t)((tmp_owt - owt_last)*100)) >= (int16_t)diffOwTempUser*10){
                        Debug.println(F("KNX send (diff):\tOwTemp:\t%3.2f °C to comObj:\t%d"), tmp_owt, COMOBJ_owtempValue);
                        Knx.write(COMOBJ_owtempValue, tmp_owt);
                        owt_last = tmp_owt;
                    }
                }
                if(valueOwTempMin != DO_NOTHING){
                    if(tmp_owt <= limitOwTempMin){
                        bool tmpValue = (bool)valueOwTempMin;
                        if(lastStateOwTempMinMax != tmpValue){
                            Debug.println(F("KNX send (LimMin):\tOwTemp:\t%3.2f °C, LimMin: \t%3.2f °C, value:\t%d to comObj:\t%d"), tmp_owt, limitOwTempMin, tmpValue, COMOBJ_owtempSendValue);
                            Knx.write(COMOBJ_owtempSendValue, tmpValue);
                            lastStateOwTempMinMax = tmpValue;
                        }
                    }
                }
                if(valueOwTempMax != DO_NOTHING){
                    if(tmp_owt >= limitOwTempMax){
                        bool tmpValue = (bool)valueOwTempMax;
                        if(lastStateOwTempMinMax != tmpValue){
                            Debug.println(F("KNX send (LimMax):\tOwTemp:\t%3.2f °C, LimMin: \t%3.2f °C, value:\t%d to comObj:\t%d"), tmp_owt, limitOwTempMax, tmpValue, COMOBJ_owtempSendValue);
                            Knx.write(COMOBJ_owtempSendValue, tmpValue);
                            lastStateOwTempMinMax = tmpValue;
                        }
                    }
                }
            }
#endif //ONEWIRE
#endif //KNX
        }
#ifdef KNX
        //cyclic
#ifdef TRH
        if(tmp_t != ERROR_TRH) {
            if(typeTemp == CYCLIC){
                if(currentMillis - lastMillisTemp >= intervalTempUser){
                    Debug.println(F("KNX send (cycle): Temp:\t%3.2f °C to comObj:\t%d"), tmp_t, COMOBJ_tempValue);
                    Knx.write(COMOBJ_tempValue, tmp_t);
                    lastMillisTemp = currentMillis;
                }
            }
        }
        if(tmp_rh != ERROR_TRH) {
            if(typeHumd == CYCLIC){
                if(currentMillis - lastMillisHumd >= intervalHumdUser){
                    Debug.println(F("KNX send (cycle): RH:\t%3.2f %%  to comObj:\t%d"), tmp_rh, COMOBJ_rhValue);
                    Knx.write(COMOBJ_rhValue, tmp_rh);
                    lastMillisHumd = currentMillis;
                }
            }
        }
#endif //TRH        
#ifdef VOC
        if(tmp_voc != ERROR_VOC) {
            if(typeVoc == CYCLIC){
                if(currentMillis - lastMillisVoc >= intervalVocUser){
                    Debug.println(F("KNX send (cycle): VOC:\t%d ppm to comObj:\t%d"), tmp_voc, COMOBJ_vocValue);
                    Debug.println(F("KNX send (cycle): tVOC:\t%d ppm to comObj:\t%d"), tmp_tvoc, COMOBJ_tvocValue);
                    Knx.write(COMOBJ_vocValue, tmp_voc);
                    Knx.write(COMOBJ_tvocValue, tmp_tvoc);
                    lastMillisVoc = currentMillis;
                }
            }
        }
#endif //VOC        
#ifdef ONEWIRE
        if(tmp_owt != ERROR_TRH) {
            if(typeOwTemp == CYCLIC){
                if(currentMillis - lastMillisOwTemp >= intervalOwTempUser){
                    Debug.println(F("KNX send (cycle): OwTemp:\t%3.2f °C to comObj:\t%d"), tmp_owt, COMOBJ_tempValue);
                    Knx.write(COMOBJ_owtempValue, tmp_owt);
                    lastMillisOwTemp = currentMillis;
                }
            }
        }
#endif //ONEWIRE
#endif //KNX
#ifdef BINARY
        if ((currentMillis - lastMillisBinaryD0) >= binaryCycleD0){
                currentStateD0 = getBinaryState(PIN_BIN0);
                lastMillisBinaryD0 = currentMillis;
        }
        if ((currentMillis - lastMillisBinaryD1) >= binaryCycleD1){
                currentStateD1 = getBinaryState(PIN_BIN1);
                lastMillisBinaryD1 = currentMillis;
        }
        if (currentStateD0 != lastStateD0){
            Debug.println(F("Binary D0: new state: %d"), currentStateD0);
            if ((currentMillis - lastOutputDelayD0) >= outputDelayD0){
                lastStateD0 = currentStateD0;
                if(valueBinaryD0 == V_SWITCH){//switch value
                    Knx.write(COMOBJ_binD0SendValue, !boolShortClick);
                }else if(valueBinaryD0 == V_VAL_0){//send 0
                    Knx.write(COMOBJ_binD0SendValue, 0);
                }else if(valueBinaryD0 == V_VAL_1){//send 1
                    Knx.write(COMOBJ_binD0SendValue, 1);
                }else if(V_SCENE_1 <= valueBinaryD0 && valueBinaryD0 <= V_SCENE_64 ){//send scene
                    Knx.write(COMOBJ_binD0Scene, valueShortClickBtn);
                }
            }
            lastMillisBinaryD0 = currentMillis;
        }
#endif //BINARY
#ifdef KNX
    }//isReadyForApplication
#endif //KNX
}
