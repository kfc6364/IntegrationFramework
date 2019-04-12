[!AUTOSPACING!]
#====================================================================================================
#
#    @file        Modules.mak
#    @version     0.8.1
#
#    @brief       Integration Framework - Files used to define all components required to be build
#
#    Platform        : CORTEXM
#    Build Version   : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
#
#   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
#       Copyright 2017 - 2018 NXP
#       All Rights Reserved.
#
#    This file contains sample code only. It is not part of the production code deliverables.
#
#====================================================================================================
#
# specify modules which will be compiled and linked
[!NOCODE!]
[!SELECT "IntegrationAppGeneral"!]
[!CODE!]
MCAL_MODULE_LIST :=  [!//
[!IF "UseAdc = 'true'"!]
 Adc[!//
[!ENDIF!]
 Base[!//
[!IF "UseCan = 'true'"!]
 Can CanIf[!//
[!ENDIF!]
[!IF "UseDio = 'true'"!]
 Dio[!//
[!ENDIF!]
[!IF "UseEth = 'true'"!]
 Eth[!//
[!ENDIF!]
[!IF "UseFee = 'true'"!]
 Fee[!//
[!ENDIF!]
[!IF "UseFls = 'true'"!]
 Fls[!//
[!ENDIF!]
[!IF "UseFr = 'true'"!]
 Fr FrIf[!//
[!ENDIF!]
[!IF "UseGpt = 'true'"!]
 Gpt[!//
[!ENDIF!]
[!IF "UseIcu = 'true'"!]
 Icu[!//
[!ENDIF!]
[!IF "UseLin = 'true'"!]
 Lin LinIf[!//
[!ENDIF!]
[!IF "UseMcu = 'true'"!]
 Mcu[!//
[!ENDIF!]
[!IF "UseMcl = 'true'"!]
 Mcl[!//
[!ENDIF!]
[!IF "(UseFls = 'true') or (UseFee = 'true')"!]
 MemIf[!//
[!ENDIF!]
[!IF "UseOcu = 'true'"!]
 Ocu[!//
[!ENDIF!]
[!IF "UsePort = 'true'"!]
 Port[!//
[!ENDIF!]
[!IF "UsePwm = 'true'"!]
 Pwm[!//
[!ENDIF!]
 Rte[!//
[!IF "UseSpi = 'true'"!]
 Spi[!//
[!ENDIF!]
[!IF "UseWdg = 'true'"!]
 Wdg WdgIf[!//
 [!ENDIF!]
 Dem Det Ecum[!//
[!ENDCODE!]
[!ENDSELECT!]

[!SELECT "IntegrationApp_FeatureList"!]
[!IF "EnableNfc  = 'true'"!]
[!CODE!]
 Anfc[!//

[!ENDCODE!]
[!ENDIF!] 
[!ENDSELECT!]

[!SELECT "IntegrationAppFeaturesConfig"!]
[!VAR "IoDalCount" = "num:i(count(IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/IoDAL/*))"!]
[!VAR "SysDalCount" = "num:i(count(IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*))"!]
[!VAR "ComDalCount" = "num:i(count(IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/ComDAL/*))"!]
[!CODE!]

APP_BSW_LIST :=[!//
[!IF "not($IoDalCount = num:i(0))"!]
 IoDal[!//
[!ENDIF!]
[!IF "not($SysDalCount = num:i(0))"!]
 SysDal[!//
[!ENDIF!]
[!IF "not($ComDalCount = num:i(0))"!]
 ComDal[!//
[!ENDIF!]

[!ENDCODE!]
[!ENDSELECT!]


[!SELECT "IntegrationApp_FeatureList"!]
[!CODE!]

APP_SWC_LIST :=[!//
[!IF "(EnableLightingApp = 'true') or (EnableMotorControlApp = 'true') "!]
 Actuators[!//
 [!ENDIF!]
[!IF "EnableLightingApp = 'true'"!]
 Lighting[!//
[!ENDIF!]
[!IF "EnableMotorControlApp = 'true'"!]
 MotorControl[!//
[!ENDIF!]
[!IF "(EnableLightingApp = 'true') or (EnableMotorControlApp = 'true') or (EnableVdrApp = 'true') "!]
 Rte[!//
 [!ENDIF!]
 [!IF "(EnableLightingApp = 'true') or (EnableMotorControlApp = 'true') "!]
 Sensors[!//
 [!ENDIF!]
[!IF "EnableVdrApp = 'true'"!]
 Vdr[!//
[!ENDIF!]
    
[!ENDCODE!]
[!ENDSELECT!]
[!CODE!]

SAMPLE_APP_NAME := IntegrationFramework

ANFC_BUILD = $(findstring Anfc, $(MCAL_MODULE_LIST))
[!ENDCODE!]
[!ENDNOCODE!]