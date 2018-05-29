void setup() {

    kinit();
    Debug.println(F("kinit done"));
    initRGB();
    Debug.println(F("initRGB done"));
    initButton();
    Debug.println(F("initButton done"));

#ifdef TRH
    initTempRH();
    Debug.println(F("initTempRH done"));
#endif
#ifdef VOC
    initVOC();
    Debug.println(F("initVOC done"));
#endif
#ifdef ONEWIRE
    initOneWire();
    Debug.println(F("initOneWire done"));
#endif
#ifdef KNX
    Debug.println(F("KNX activated"));
    if (!Konnekting.isFactorySetting()) {

        typeTemp = (byte) Konnekting.getUINT8Param(PARAM_tempSendUpdate);
        diffTempUser = (byte) Konnekting.getUINT8Param(PARAM_tempDiff);
        intervalTempUser = (uint32_t) Konnekting.getUINT16Param(PARAM_tempCycle) * 1000;
        offsetTemp   = (float) Konnekting.getINT8Param(PARAM_tempOffset) * 0.1;
        valueTempMin = Konnekting.getUINT8Param(PARAM_tempMinValue);
        limitTempMin = (float) Konnekting.getINT16Param(PARAM_tempMinLimit) * 0.1;
        valueTempMax = Konnekting.getUINT8Param(PARAM_tempMaxValue);
        limitTempMax = (float) Konnekting.getINT16Param(PARAM_tempMaxLimit) * 0.1;
    
        typeHumd = (byte) Konnekting.getUINT8Param(PARAM_rhSendUpdate);
        diffHumdUser = (byte) Konnekting.getUINT8Param(PARAM_rhDiff);
        intervalHumdUser = (uint32_t) Konnekting.getUINT16Param(PARAM_rhCycle) * 1000;
        offsetHumd   = (float) Konnekting.getINT8Param(PARAM_rhOffset) * 0.1;
        valueHumdMin = Konnekting.getUINT8Param(PARAM_rhMinValue);
        limitHumdMin = (float) Konnekting.getUINT16Param(PARAM_rhMinLimit) * 0.1;
        valueHumdMax = Konnekting.getUINT8Param(PARAM_rhMaxValue);
        limitHumdMax = (float) Konnekting.getUINT16Param(PARAM_rhMaxLimit) * 0.1;

        typeVoc = (byte) Konnekting.getUINT8Param(PARAM_vocSendUpdate);
        diffVocUser = (byte) Konnekting.getUINT8Param(PARAM_vocDiff);
        intervalVocUser = (uint32_t) Konnekting.getUINT16Param(PARAM_vocPollingTime) * 1000;
        offsetVoc   = (int16_t) Konnekting.getUINT16Param(PARAM_vocOffset);
        valueVocMin = Konnekting.getUINT8Param(PARAM_vocMinValue);
        limitVocMin = (word) Konnekting.getINT16Param(PARAM_vocMinLimit);
        valueVocMax = Konnekting.getUINT8Param(PARAM_vocMaxValue);
        limitVocMax = (word) Konnekting.getINT16Param(PARAM_vocMaxLimit);

        typeOwTemp = (byte) Konnekting.getUINT8Param(PARAM_owtempSendUpdate);
        diffOwTempUser = (byte) Konnekting.getUINT8Param(PARAM_owtempDiff);
        intervalOwTempUser = (uint32_t) Konnekting.getUINT16Param(PARAM_owtempCycle) * 1000;
        offsetOwTemp   = (float) Konnekting.getINT8Param(PARAM_owtempOffset) * 0.1;
        valueOwTempMin = Konnekting.getUINT8Param(PARAM_owtempMinValue);
        limitOwTempMin = (float) Konnekting.getINT16Param(PARAM_owtempMinLimit) * 0.1;
        valueOwTempMax = Konnekting.getUINT8Param(PARAM_owtempMaxValue);
        limitOwTempMax = (float) Konnekting.getINT16Param(PARAM_owtempMaxLimit) * 0.1;
         
        typeBtn = (byte) Konnekting.getUINT8Param(PARAM_btnType);
        longClickDurationBtn = (int) Konnekting.getUINT16Param(PARAM_btnLongClickDuration);
        valueShortClickBtn = (byte) Konnekting.getUINT8Param(PARAM_btnValueShortClick);
        valueLongClickBtn = (byte) Konnekting.getUINT8Param(PARAM_btnValueLongClick);

        valueBinaryD0 = (byte) Konnekting.getUINT8Param(PARAM_binD0type);
        valueBinaryD1 = (byte) Konnekting.getUINT8Param(PARAM_binD1type);
        binaryCycleD0 = (uint16_t) Konnekting.getUINT16Param(PARAM_binD0cycle);
        binaryCycleD1 = (uint16_t) Konnekting.getUINT16Param(PARAM_binD1cycle);
  
        typeRgb = Konnekting.getUINT8Param(PARAM_rgbType);
        brightnessTypeRgb = Konnekting.getUINT8Param(PARAM_rgbBrightnessDay);
        colorOnClickRgb = Konnekting.getUINT8Param(PARAM_rgbColorOnClick);
        colorStateShortRgb = Konnekting.getUINT8Param(PARAM_rgbStateShortColor);
        colorStateLongRgb = Konnekting.getUINT8Param(PARAM_rgbStateLongColor);
    
    
    }else{
        //factory settings -> start progMode
        Konnekting.setProgState(true);
    }
    //ToDo: send initial Values for COMOBJ_*SendValue
#endif

#ifdef KDEBUG
    printConfig();
#endif
    Debug.println(F("\nSetup is ready. go to loop...\n"));
}
