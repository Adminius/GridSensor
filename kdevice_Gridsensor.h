#define MANUFACTURER_ID 7070
#define DEVICE_ID 180
#define REVISION 1

#define COMOBJ_tempValue 0
#define COMOBJ_tempSendValue 1
#define COMOBJ_rhValue 2
#define COMOBJ_rhSendValue 3
#define COMOBJ_vocValue 4
#define COMOBJ_vocSendValue 5
#define COMOBJ_tvocValue 6
#define COMOBJ_owtempValue 7
#define COMOBJ_owtempSendValue 8
#define COMOBJ_btnShortValue 9
#define COMOBJ_btnShortInput 10
#define COMOBJ_btnShortScene 11
#define COMOBJ_btnLongValue 12
#define COMOBJ_btnLongInput 13
#define COMOBJ_btnLongScene 14
#define COMOBJ_btnDimSw 15
#define COMOBJ_btnDimSwInput 16
#define COMOBJ_btnDim 17
#define COMOBJ_binD0SendValue 18
#define COMOBJ_binD0ValueInput 19
#define COMOBJ_binD0Scene 20
#define COMOBJ_binD1SendValue 21
#define COMOBJ_binD1ValueInput 22
#define COMOBJ_binD1Scene 23
#define COMOBJ_nightMode 24
#define PARAM_tempSendUpdate 0
#define PARAM_tempDiff 1
#define PARAM_tempCycle 2
#define PARAM_tempOffset 3
#define PARAM_tempMinValue 4
#define PARAM_tempMinLimit 5
#define PARAM_tempMaxValue 6
#define PARAM_tempMaxLimit 7
#define PARAM_rhSendUpdate 8
#define PARAM_rhDiff 9
#define PARAM_rhCycle 10
#define PARAM_rhOffset 11
#define PARAM_rhMinValue 12
#define PARAM_rhMinLimit 13
#define PARAM_rhMaxValue 14
#define PARAM_rhMaxLimit 15
#define PARAM_vocSendUpdate 16
#define PARAM_vocDiff 17
#define PARAM_vocPollingTime 18
#define PARAM_vocOffset 19
#define PARAM_vocMinValue 20
#define PARAM_vocMinLimit 21
#define PARAM_vocMaxValue 22
#define PARAM_vocMaxLimit 23
#define PARAM_owtempSendUpdate 24
#define PARAM_owtempDiff 25
#define PARAM_owtempCycle 26
#define PARAM_owtempOffset 27
#define PARAM_owtempMinValue 28
#define PARAM_owtempMinLimit 29
#define PARAM_owtempMaxValue 30
#define PARAM_owtempMaxLimit 31
#define PARAM_btnType 32
#define PARAM_btnLongClickDuration 33
#define PARAM_btnValueShortClick 34
#define PARAM_btnValueLongClick 35
#define PARAM_binD0type 36
#define PARAM_binD0cycle 37
#define PARAM_binD0delay 38
#define PARAM_binD0open 39
#define PARAM_binD0close 40
#define PARAM_binD1type 41
#define PARAM_binD1cycle 42
#define PARAM_binD1delay 43
#define PARAM_binD1open 44
#define PARAM_binD1close 45
#define PARAM_rgbType 46
#define PARAM_rgbBrightnessDay 47
#define PARAM_rgbBrightnessNight 48
#define PARAM_rgbColorOnClick 49
#define PARAM_rgbStateShortColor 50
#define PARAM_rgbStateLongColor 51
        
KnxComObject KnxDevice::_comObjectsList[] = {
    /* Index 0 - tempValue */ KnxComObject(KNX_DPT_9_001, 0x34),
    /* Index 1 - tempSendValue */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 2 - rhValue */ KnxComObject(KNX_DPT_9_007, 0x34),
    /* Index 3 - rhSendValue */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 4 - vocValue */ KnxComObject(KNX_DPT_9_008, 0x34),
    /* Index 5 - vocSendValue */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 6 - tvocValue */ KnxComObject(KNX_DPT_9_008, 0x34),
    /* Index 7 - owtempValue */ KnxComObject(KNX_DPT_9_001, 0x34),
    /* Index 8 - owtempSendValue */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 9 - btnShortValue */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 10 - btnShortInput */ KnxComObject(KNX_DPT_1_001, 0x2b),
    /* Index 11 - btnShortScene */ KnxComObject(KNX_DPT_17_001, 0x34),
    /* Index 12 - btnLongValue */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 13 - btnLongInput */ KnxComObject(KNX_DPT_1_001, 0x2b),
    /* Index 14 - btnLongScene */ KnxComObject(KNX_DPT_17_001, 0x34),
    /* Index 15 - btnDimSw */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 16 - btnDimSwInput */ KnxComObject(KNX_DPT_1_001, 0x2b),
    /* Index 17 - btnDim */ KnxComObject(KNX_DPT_3_007, 0x34),
    /* Index 18 - binD0SendValue */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 19 - binD0ValueInput */ KnxComObject(KNX_DPT_1_001, 0x2b),
    /* Index 20 - binD0Scene */ KnxComObject(KNX_DPT_17_001, 0x34),
    /* Index 21 - binD1SendValue */ KnxComObject(KNX_DPT_1_001, 0x34),
    /* Index 22 - binD1ValueInput */ KnxComObject(KNX_DPT_1_001, 0x2b),
    /* Index 23 - binD1Scene */ KnxComObject(KNX_DPT_17_001, 0x34),
    /* Index 24 - nightMode */ KnxComObject(KNX_DPT_1_001, 0x2b)
};
const byte KnxDevice::_numberOfComObjects = sizeof (_comObjectsList) / sizeof (KnxComObject); // do not change this code
       
byte KonnektingDevice::_paramSizeList[] = {
    /* Index 0 - tempSendUpdate */ PARAM_UINT8,
    /* Index 1 - tempDiff */ PARAM_UINT8,
    /* Index 2 - tempCycle */ PARAM_UINT16,
    /* Index 3 - tempOffset */ PARAM_INT8,
    /* Index 4 - tempMinValue */ PARAM_UINT8,
    /* Index 5 - tempMinLimit */ PARAM_INT16,
    /* Index 6 - tempMaxValue */ PARAM_UINT8,
    /* Index 7 - tempMaxLimit */ PARAM_INT16,
    /* Index 8 - rhSendUpdate */ PARAM_UINT8,
    /* Index 9 - rhDiff */ PARAM_UINT8,
    /* Index 10 - rhCycle */ PARAM_UINT16,
    /* Index 11 - rhOffset */ PARAM_INT8,
    /* Index 12 - rhMinValue */ PARAM_UINT8,
    /* Index 13 - rhMinLimit */ PARAM_INT16,
    /* Index 14 - rhMaxValue */ PARAM_UINT8,
    /* Index 15 - rhMaxLimit */ PARAM_INT16,
    /* Index 16 - vocSendUpdate */ PARAM_UINT8,
    /* Index 17 - vocDiff */ PARAM_UINT8,
    /* Index 18 - vocPollingTime */ PARAM_UINT16,
    /* Index 19 - vocOffset */ PARAM_INT16,
    /* Index 20 - vocMinValue */ PARAM_UINT8,
    /* Index 21 - vocMinLimit */ PARAM_INT16,
    /* Index 22 - vocMaxValue */ PARAM_UINT8,
    /* Index 23 - vocMaxLimit */ PARAM_INT16,
    /* Index 24 - owtempSendUpdate */ PARAM_UINT8,
    /* Index 25 - owtempDiff */ PARAM_UINT8,
    /* Index 26 - owtempCycle */ PARAM_UINT16,
    /* Index 27 - owtempOffset */ PARAM_INT8,
    /* Index 28 - owtempMinValue */ PARAM_UINT8,
    /* Index 29 - owtempMinLimit */ PARAM_INT16,
    /* Index 30 - owtempMaxValue */ PARAM_UINT8,
    /* Index 31 - owtempMaxLimit */ PARAM_INT16,
    /* Index 32 - btnType */ PARAM_UINT8,
    /* Index 33 - btnLongClickDuration */ PARAM_UINT16,
    /* Index 34 - btnValueShortClick */ PARAM_UINT8,
    /* Index 35 - btnValueLongClick */ PARAM_UINT8,
    /* Index 36 - binD0type */ PARAM_UINT8,
    /* Index 37 - binD0cycle */ PARAM_UINT16,
    /* Index 38 - binD0delay */ PARAM_INT16,
    /* Index 39 - binD0open */ PARAM_UINT8,
    /* Index 40 - binD0close */ PARAM_UINT8,
    /* Index 41 - binD1type */ PARAM_UINT8,
    /* Index 42 - binD0cycle */ PARAM_UINT16,
    /* Index 43 - binD1delay */ PARAM_INT16,
    /* Index 44 - binD1open */ PARAM_UINT8,
    /* Index 45 - binD1close */ PARAM_UINT8,
    /* Index 46 - rgbType */ PARAM_UINT8,
    /* Index 47 - rgbBrightnessDay */ PARAM_UINT8,
    /* Index 48 - rgbBrightnessNight */ PARAM_UINT8,
    /* Index 49 - rgbColorOnClick */ PARAM_UINT8,
    /* Index 50 - rgbStateShortColor */ PARAM_UINT8,
    /* Index 51 - rgbStateLongColor */ PARAM_UINT8
};
const int KonnektingDevice::_numberOfParams = sizeof (_paramSizeList); // do not change this codeo not change this code
