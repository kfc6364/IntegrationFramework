/**
*   @file    IoDal.c
*   @version 0.8.1
*
*   @brief   Integration Framework - IO Driver Abstraction Layer component configuration file
*   @details This file implements the IODAL configuration interface to application layer.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*/
/*=========================================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : CORTEXM
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   
*   SW Version           : 0.8.1
*   Build Version        : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
*
============================================================================================================================*/
/*============================================================================================================================
==============================================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

[!IF "num:i(count(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/IoDAL/*)) != num:i(0)"!]

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
 ==================================================================================================*/
#include "IoDal_Drv_Cfg.h"
#include "IoDal_Cfg.h"

/*===================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
====================================================================================================================*/
#define IODAL_PBCFG_VENDOR_ID_C                       43

#define IODAL_PBCFG_AR_RELEASE_MAJOR_VERSION_C        4
#define IODAL_PBCFG_AR_RELEASE_MINOR_VERSION_C        3
#define IODAL_PBCFG_AR_RELEASE_REVISION_VERSION_C     1

#define IODAL_PBCFG_SW_MAJOR_VERSION_C                0
#define IODAL_PBCFG_SW_MINOR_VERSION_C                8
#define IODAL_PBCFG_SW_PATCH_VERSION_C                1

/*===================================================================================================================
*                                     FILE VERSION CHECKS
====================================================================================================================*/
/* Check if source file and IoDal_Cfg.h header file are of the same vendor */
#if (IODAL_PBCFG_VENDOR_ID_C != IODAL_CFG_VENDOR_ID)
    #error "IoDal.c and IoDal_Cfg.h have different vendor ids"
#endif

/* Check if source file and IoDal_Cfg.h header file are of the same Autosar version */
#if ((IODAL_PBCFG_AR_RELEASE_MAJOR_VERSION_C != IODAL_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (IODAL_PBCFG_AR_RELEASE_MINOR_VERSION_C != IODAL_CFG_AR_RELEASE_MINOR_VERSION) || \
     (IODAL_PBCFG_AR_RELEASE_REVISION_VERSION_C != IODAL_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of IoDal.c and IoDal_Cfg.h are different"
#endif

/* Check if source file and IoDal_Cfg.h header file are of the same Software version */
#if ((IODAL_PBCFG_SW_MAJOR_VERSION_C != IODAL_CFG_SW_MAJOR_VERSION) || \
     (IODAL_PBCFG_SW_MINOR_VERSION_C != IODAL_CFG_SW_MINOR_VERSION) || \
     (IODAL_PBCFG_SW_PATCH_VERSION_C != IODAL_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of IoDal.c and IoDal_Cfg.h are different"
#endif


/* Check if source file and IoDal_Drv_Cfg.h header file are of the same vendor */
#if (IODAL_PBCFG_VENDOR_ID_C != IODAL_DRV_CFG_VENDOR_ID)
    #error "IoDal.c and IoDal_Drv_Cfg.h have different vendor ids"
#endif

/* Check if source file and IoDal_Drv_Cfg.h header file are of the same Autosar version */
#if ((IODAL_PBCFG_AR_RELEASE_MAJOR_VERSION_C != IODAL_DRV_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (IODAL_PBCFG_AR_RELEASE_MINOR_VERSION_C != IODAL_DRV_CFG_AR_RELEASE_MINOR_VERSION) || \
     (IODAL_PBCFG_AR_RELEASE_REVISION_VERSION_C != IODAL_DRV_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of IoDal.c and IoDal_Drv_Cfg.h are different"
#endif

/* Check if source file and IoDal_Drv_Cfg.h header file are of the same Software version */
#if ((IODAL_PBCFG_SW_MAJOR_VERSION_C != IODAL_DRV_CFG_SW_MAJOR_VERSION) || \
     (IODAL_PBCFG_SW_MINOR_VERSION_C != IODAL_DRV_CFG_SW_MINOR_VERSION) || \
     (IODAL_PBCFG_SW_PATCH_VERSION_C != IODAL_DRV_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of IoDal.c and IoDal_Drv_Cfg.h are different"
#endif



/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
[!AUTOSPACING!]
[!NOCODE!]
[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]
    [!VAR "AllChannelCount" = "num:i(count(IoDAL/*))"!]
    [!VAR "IndexDigital" = "num:i(0)"!]
    [!VAR "IndexAnalog" = "num:i(0)"!]
    [!VAR "IndexPwm" = "num:i(0)"!]
    [!VAR "IndexOcu" = "num:i(0)"!]
    [!VAR "IndexIcu" = "num:i(0)"!]
    [!VAR "HW_Variants" = "num:i(0)"!]
    [!VAR "SwTriggerCount" = "num:i(0)"!]
    [!LOOP "IoDAL/*"!]
        [!IF "ReferenceType = 'Digital'"!]
            [!VAR "IndexDigital" = "num:i($IndexDigital + 1)"!]
            [!VAR "DioChannelCount" = "$IndexDigital"!]
        [!ELSEIF "ReferenceType = 'Analog'"!]
            [!VAR "IndexAnalog" = "num:i($IndexAnalog + 1)"!]
            [!VAR "AnalogChannelCount" = "$IndexAnalog"!]
        [!ELSEIF "ReferenceType = 'Pwm'"!]
            [!VAR "IndexPwm" = "num:i($IndexPwm + 1)"!]
            [!VAR "PwmChannelCount" = "$IndexPwm"!]
        [!ELSEIF "ReferenceType = 'Icu'"!]
            [!VAR "IndexIcu" = "num:i($IndexIcu + 1)"!]
            [!VAR "IcuChannelCount" = "$IndexIcu"!]
        [!ELSE!]
            [!IF "ReferenceDirection = 'Trigger'"!]
                [!IF "$SwTriggerCount = num:i(0)"!]
                    [!VAR "SwTriggerCount" = "node:name(.)"!]
                [!ELSE!]
                    [!ERROR!]
                        "[!"node:name(.)"!] is the second SW trigger encountered, besides [!"$SwTriggerCount"!]. There shall be only one ADC SW trigger in the configuration"
                    [!ENDERROR!]
                [!ENDIF!]
            [!ENDIF!]
            [!VAR "IndexOcu" = "num:i($IndexOcu + 1)"!]
            [!VAR "OcuChannelCount" = "$IndexOcu"!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]

#define    IODAL_MAX_CHANNELS_HW_VAR_0                [!"$AllChannelCount"!]U

[!ENDCODE!]
[!CODE!]
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
[!ENDCODE!]
    [!VAR "Array" = "''"!]
    [!VAR "UniqueGroupCount" = "num:i(0)"!]
    
    [!LOOP "IoDAL/*"!]
    
        [!IF "ReferenceType = 'Analog'"!]
            [!IF "not(contains($Array,node:name(node:ref(AnalogRef))))"!]
            [!VAR "GroupChannelCounter" = "num:i(0)"!]
                [!VAR "Array" = "concat($Array, node:name(node:ref(AnalogRef)), '_')"!]
                [!VAR "Group" = "node:name(node:ref(AnalogRef))"!]
                [!LOOP "../../IoDAL/*"!]
                    [!IF "ReferenceType = 'Analog'"!]
                        [!IF "node:name(node:ref(AnalogRef)) = $Group"!]
                            [!VAR "GroupChannelCounter" = "num:i($GroupChannelCounter + 1)"!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDLOOP!]
                [!VAR "UniqueGroupCount" = "num:i($UniqueGroupCount + 1)"!]
[!CODE!]
static Adc_ValueGroupType IoDal_AniDescriptor_[!"$Group"!]_HW_VAR_0[[!"$GroupChannelCounter"!]]    =    {[!//
[!/*            */!][!FOR "idx" = "1" TO "$GroupChannelCounter"!][!//
[!/*                */!]0[!//
[!/*                */!][!IF "not($idx = $GroupChannelCounter)"!][!//
[!/*                    */!], [!//
[!/*                */!][!ENDIF!][!//
[!/*            */!][!ENDFOR!]};
[!ENDCODE!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]

/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/

/*Critical Note: A BSW analog input using SW trigger can only reference TT elements FROM ONE TABLE... 
               if analog inputs use different OCU channels/TT Table than the generation tool should report an Error.
            
                The  Time-Triggered Table used by Analog input has the exact size determined by the number of inputs that have as referees
                entries in the TT Tab
                Basically if a user defines 10 entries and only uses 5 inputs than the size of the OcuTimeTable will be 5 and only the entries referenced will be printed in the Table; all other will be ignored.
 */
           
[!ENDCODE!]
[!ENDSELECT!]
[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*"!]
[!LOOP "TimeTriggerTable/*"!]
    [!VAR "OcuChannel" = "node:name(.)"!]
    [!VAR "Counter" = "num:i(0)"!]

    [!LOOP "../../GeneralConfig/*/IoDAL/*"!]
        [!IF "(ReferenceType = 'Analog') and (TriggerType = 'SW')"!]
            [!VAR "String" = "substring-before(node:value(OcuScheduling),node:name(node:ref(OcuScheduling)))"!]
            [!VAR "Length" = "(string-length($String))"!]
            [!VAR "String" = "substring($String,0,$Length)"!]
            [!IF "node:name(node:ref($String)) = $OcuChannel"!]
                [!VAR "Counter" = "num:i($Counter + 1)"!]
            [!ENDIF!]
        
        [!ENDIF!]
    [!ENDLOOP!]
    [!IF "not(num:i('0')= $Counter)"!]    [!//If the Analog Group of this IoDAL channel uses OCU trigger points

[!CODE!]

/*Entries for [!"$OcuChannel"!] scheduling points used as SW trigger by ADC*/
static CONST(uint16, IODAL_CONST) IoDal_OcuTimeTable_[!"$OcuChannel"!]_HW_VAR_0[[!"$UniqueGroupCount"!]] = {[!ENDCODE!]
        [!VAR "CounterAdc" = "num:i(0)"!]
        [!VAR "GroupString" = "''"!]
        [!LOOP "../../GeneralConfig/*/IoDAL/*"!]
            [!IF "(ReferenceType = 'Analog') and (TriggerType = 'SW') and (not(contains($GroupString,node:name(node:ref(AnalogRef)))))"!]
                [!VAR "GroupString" = "concat($GroupString,node:name(node:ref(AnalogRef)))"!]
                [!VAR "CounterAdc" = "num:i($CounterAdc + 1)"!]
                [!VAR "String" = "substring-before(node:value(OcuScheduling),node:name(node:ref(OcuScheduling)))"!]
                [!VAR "Length" = "(string-length($String))"!]
                [!VAR "String" = "substring($String,0,$Length)"!]
                [!IF "node:name(node:ref($String)) = $OcuChannel"!]
[!CODE!]
[!"node:value(node:ref(OcuScheduling)/ValueInTicks)"!][!IF "not($UniqueGroupCount = $CounterAdc)"!], [!ENDIF!]
[!ENDCODE!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDLOOP!]
[!CODE!]
};
[!ENDCODE!]
    [!ELSE!]    [!//If no Analog IoDAL channels use OCU trigger points
        [!VAR "Counter" = "num:i(count(SchedulePoints/*))"!]
        [!VAR "CounterOcu" = "num:i(0)"!]
[!CODE!]

/*Entries for [!"$OcuChannel"!] scheduling points NOT used as SW trigger by ADC*/
static CONST(uint16, IODAL_CONST) IoDal_OcuTimeTable_[!"$OcuChannel"!]_HW_VAR_0[[!"$Counter"!]] = {[!ENDCODE!]
        [!LOOP "SchedulePoints/*"!]
        [!VAR "CounterOcu" = "num:i($CounterOcu + 1)"!]        
[!CODE!]
[!"node:value(ValueInTicks)"!][!IF "not($Counter = $CounterOcu)"!], [!ENDIF!]
[!ENDCODE!]
        [!ENDLOOP!]
[!CODE!]
};
[!ENDCODE!]
    [!ENDIF!]
[!ENDLOOP!]
[!ENDSELECT!]

[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]

[!//PWM HW Config
[!CODE!]

/*SYNC PWM HW CONFIGURATIONS*/

[!ENDCODE!]
[!VAR "PwmString" = "''"!]
[!LOOP "IoDAL/*"!]
    [!IF "ReferenceType = 'Pwm'"!]
        [!IF "(PwmType = 'SYNC')"!] 
        [!VAR "PwmFtm" = "node:value(node:ref(substring-before(node:value(node:ref(PwmRef)/PwmFtmChannel),node:name(node:ref(PwmRef)/PwmFtmChannel)))/FtmModule)"!]
            [!IF "not(contains($PwmString,$PwmFtm))"!]
[!CODE!]
static CONST(IoDal_InternalPwmConfig, IODAL_CONST)  IoDal_PwmHwConfig_[!"$PwmFtm"!]_HW_VAR_0 =
{
    [!"$PwmFtm"!],
    [!"PwmMask"!]
};
[!ENDCODE!]
            [!VAR "PwmString" = "concat($PwmString,$PwmFtm)"!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDIF!]
[!ENDLOOP!]



[!//Code for generating DIO Channel Descriptor
[!CODE!]

#if IODAL_MAX_DIO_CHANNELS_HW_VAR_0 > 0U
/*DIO Channel descriptor*/
static CONST(IoDal_DigitalDescriptorType, IODAL_CONST) IoDal_DioChannelDescriptor_HW_VAR_0[IODAL_MAX_DIO_CHANNELS_HW_VAR_0] =
{[!ENDCODE!]
    [!VAR "IndexDigital" = "num:i(0)"!]
    [!LOOP "IoDAL/*"!]
        [!IF "ReferenceType = 'Digital'"!]
            [!IF "UseExternalDevice = 'false'"!]
                [!VAR "ChannelRef" = "node:name(node:ref(DioRef))"!]
            [!ELSE!]
                [!VAR "ChannelRef" = "node:name(node:ref(ExtDevRef))"!]
            [!ENDIF!]
            [!VAR "IndexDigital" = "num:i($IndexDigital + 1)"!]
[!CODE!] [!CR!] 
    {
        DioConf_DioChannel_[!"$ChannelRef"!],        /*DIO Channel ID*/
        [!"DigitalSignalLevel"!],
        NULL_PTR                /*External Device*/
    }[!IF "not($IndexDigital = $DioChannelCount)"!],
     [!ENDIF!]
[!ENDCODE!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]

};
#endif
[!ENDCODE!]

[!//Code for generating PWM Channel Descriptor
[!CODE!]
#if IODAL_MAX_PWM_CHANNELS_HW_VAR_0 > 0U
/*PWM Channel descriptor*/
static CONST(IoDal_PwmDescriptorType, IODAL_CONST) IoDal_PwmChannelDescriptor_HW_VAR_0[IODAL_MAX_PWM_CHANNELS_HW_VAR_0] =
{[!ENDCODE!]
    [!VAR "IndexPwm" = "num:i(0)"!]
    [!LOOP "IoDAL/*"!]
        [!IF "ReferenceType = 'Pwm'"!]
            [!VAR "ChannelRef" = "node:name(node:ref(PwmRef))"!]
            [!VAR "IndexPwm" = "num:i($IndexPwm + 1)"!]
            [!IF "(PwmType = 'SYNC')"!] 
                [!VAR "PwmFtm" = "node:value(node:ref(substring-before(node:value(node:ref(PwmRef)/PwmFtmChannel),node:name(node:ref(PwmRef)/PwmFtmChannel)))/FtmModule)"!]
                [!VAR "PwmFtm" = "concat('IoDal_PwmHwConfig_',$PwmFtm,'_HW_VAR_0,                /*Sync FTM Configuration*/')"!]
            [!ELSE!]
            [!VAR "PwmFtm"    =    "'NULL_PTR,                /*Sync FTM not used. No additional configuration required*/'"!]
            [!ENDIF!]
            
[!CODE!] [!CR!]
    {
        [!"$ChannelRef"!],        /*PWM Channel ID*/ 
        [!"$PwmFtm"!]
        NULL_PTR                /*External Device*/
    }[!IF "not($IndexPwm = $PwmChannelCount)"!],
     [!ENDIF!]
[!ENDCODE!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]

};
#endif
[!ENDCODE!]


[!//Code for generating Analog Channel Descriptor
[!CODE!]

#if IODAL_MAX_ANALOG_CHANNELS_HW_VAR_0 > 0U
/*Analog Channel descriptor*/
static CONST(IoDal_AnalogDescriptorType, IODAL_CONST) IoDal_AdcChannelDescriptor_HW_VAR_0[IODAL_MAX_ANALOG_CHANNELS_HW_VAR_0] =
{[!ENDCODE!]
    [!VAR "IndexAnalog" = "num:i(0)"!]
    [!VAR "IndexTT" = "num:i(0)"!]
    [!LOOP "IoDAL/*"!]
        [!IF "ReferenceType = 'Analog'"!]
            [!VAR "GroupRef" = "node:name(node:ref(AnalogRef))"!]
            [!VAR "ChannelRef" = "node:name(node:ref(AnalogChRef))"!]
            [!VAR "IndexAnalog" = "num:i($IndexAnalog + 1)"!]
            [!VAR "ChInGroup" = "num:i(count(node:ref(AnalogRef)/AdcGroupDefinition/*))"!]
            [!VAR "GroupConvTime" = "num:i(node:value(ConvTime))"!] 
            [!VAR "GroupTTIndex" = "num:i( node:ref(OcuScheduling)/@index)"!] 
            
            [!FOR "x" = "1" TO "$ChInGroup"!]
            
            [!ENDFOR!]

            [!IF "(TriggerType = 'SW')"!]
                [!VAR "Path" = "substring-before(node:value(OcuScheduling),node:name(node:ref(OcuScheduling)))"!]
                [!VAR "OcuAnalogCheck" = "''"!]
                [!VAR "OcuAnalogChannel" = "node:name(.)"!]
                [!VAR "Length" = "(string-length($Path))"!]
                [!LOOP "../../IoDAL/*"!]
                    [!IF "(ReferenceType = 'Ocu')"!]
                        [!IF "(node:value(OcuRef) = substring($Path,0,$Length))"!]
                            [!IF "not(ReferenceDirection = 'Trigger')"!]
                                [!ERROR!]
                                    "[!"$OcuAnalogChannel"!] references the [!"node:name(.)"!] OCU TimeTable which is not configured as a SW trigger, but  as an output. The ADC SW Trigger Ocu channel shall be used exclusively by the ADC!"
                                [!ENDERROR!]
                            [!ELSE!]
                                [!VAR "OcuAnalogCheck" = "'match'"!]
                            [!ENDIF!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDLOOP!]
                [!IF "not($OcuAnalogCheck = 'match')"!]
                        [!ERROR!] 
                            "There is no configured Trigger OCU channel for Analog Channel [!"node:name(.)"!] SW trigger. Create a dedicated Trigger type(select this from Referenced Signal Direction) OCU channel corresponding to the SW trigger table the ADC channel is using."  
                        [!ENDERROR!]  
                [!ENDIF!]
                
            [!ENDIF!]
            
            [!// Code to identify the position of the ADC Channel in the ADC Group Definition within the ADC module
            [!LOOP "/AUTOSAR/TOP-LEVEL-PACKAGES/Adc/ELEMENTS/Adc/AdcConfigSet/AdcHwUnit/AdcHwUnit_0"!]    
                [!LOOP "AdcGroup/*"!]
                    [!VAR "ChannelIndexCounter" =  "num:i(0)"!]
                    [!LOOP "AdcGroupDefinition/*"!]
                        [!IF "node:name(node:ref(.)) = $ChannelRef"!]
                            [!VAR "ChannelRef" =  "num:i($ChannelIndexCounter)"!]
                        [!ENDIF!]
                        [!VAR "ChannelIndexCounter" =  "num:i($ChannelIndexCounter + 1)"!]
                    [!ENDLOOP!]
                [!ENDLOOP!]
            [!ENDLOOP!]
[!CODE!] [!CR!]   
    {
        [!"$GroupRef"!],        /*ADC Group ID*/     
        [!"$ChannelRef"!],         /*ADC Channel Position in the ADC [!"$GroupRef"!] Group definition*/
        [!"$GroupConvTime"!],        /*ADC Conversion Time(in ticks)*/
        IoDal_AniDescriptor_[!"$GroupRef"!]_HW_VAR_0,    /**ADC result data array */
        [!IF "(TriggerType = 'SW')"!]        [!"$GroupTTIndex"!]    /*Time trigger entry index within IoDal_OcuTimeTable_*_HW_VAR_0*/[!ELSE!]255    /*SW Trigger not configured*/[!ENDIF!][!//
            
    }[!IF "not($IndexAnalog = $AnalogChannelCount)"!],[!ENDIF!]

[!ENDCODE!]
    
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]

};
#endif
[!ENDCODE!]

[!//Code for generating Icu Channel Descriptor
[!CODE!]

#if  IODAL_MAX_ICU_CHANNELS_HW_VAR_0 > 0U
/*ICU Channel descriptor*/
static CONST(IoDal_IcuDescriptorType, IODAL_CONST) IoDal_IcuChannelDescriptor_HW_VAR_0[IODAL_MAX_ICU_CHANNELS_HW_VAR_0] =
{[!ENDCODE!]
    [!VAR "IndexIcu" = "num:i(0)"!]
    [!LOOP "IoDAL/*"!]
        [!IF "ReferenceType = 'Icu'"!]
            [!VAR "ChannelRef" = "node:name(node:ref(IcuRef))"!]
            [!VAR "IndexIcu" = "num:i($IndexIcu + 1)"!]
[!CODE!]    [!"$ChannelRef"!][!IF "not($IndexIcu = $IcuChannelCount)"!],[!ENDIF!]        /*ICU Channel ID*/ 
[!ENDCODE!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]
};
#endif
[!ENDCODE!]

[!//Code for generating Ocu Channel Descriptor
[!CODE!]

#if  IODAL_MAX_OCU_CHANNELS_HW_VAR_0 > 0U
/*OCU Channel descriptor*/
static CONST(IoDal_OcuDescriptorType, IODAL_CONST) IoDal_OcuChannelDescriptor_HW_VAR_0[IODAL_MAX_OCU_CHANNELS_HW_VAR_0] =
{[!ENDCODE!]
    [!VAR "IndexOcu" = "num:i(0)"!]
    [!LOOP "IoDAL/*"!]
        [!IF "ReferenceType = 'Ocu'"!]
            [!VAR "OcuTable" = "node:name(node:ref(OcuRef))"!]
            [!IF "not(num:i('0')= $UniqueGroupCount)"!]
                [!VAR "SizeTT" = "$UniqueGroupCount"!]
            [!ELSE!]
                [!VAR "SizeTT" = "count(node:ref(OcuRef)/SchedulePoints/*)"!]
            [!ENDIF!]
            [!VAR "ChannelRef" = "node:name(node:ref(node:value(node:ref(OcuRef)/OcuRef)))"!]
            [!VAR "IndexOcu" = "num:i($IndexOcu + 1)"!]
[!CODE!] [!CR!]   
    {
        [!"$ChannelRef"!],        /*OCU Channel ID*/[!//
[!//    [!"node:value(node:ref(OcuRef)/OutputBehaviour)"!],        /*Default output behaviour*/
        [!"num:i($SizeTT)"!],        /*Size of the timetable*/
        IoDal_OcuTimeTable_[!"node:name(node:ref(OcuRef))"!]_HW_VAR_0
    }[!IF "not($IndexOcu = $OcuChannelCount)"!],
     [!ENDIF!]
[!ENDCODE!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]

};
#endif
[!ENDCODE!]

[!CODE!]

/*Mapping of BSW Channels to Specific Channel Descriptors*/
static CONST(IoDal_BswChannelMapType, IODAL_CONST) IoDal_BswChannelMap_HW_VAR_0[IODAL_MAX_CHANNELS_HW_VAR_0] = 
{[!ENDCODE!]
[!// Reinitialize indexes in order to map them to their respective configuration structures
[!VAR "IndexAll" = "num:i(0)"!]
[!VAR "IndexDigital" = "num:i(0)"!]
[!VAR "IndexAnalog" = "num:i(0)"!]
[!VAR "IndexPwm" = "num:i(0)"!]
[!VAR "IndexOcu" = "num:i(0)"!]
[!VAR "IndexIcu" = "num:i(0)"!]
[!VAR "IndexSwTrigger" = "concat(num:i(255), ',    /*There is no configured SW Trigger*/')"!]
[!LOOP "IoDAL/*"!]
    [!IF "ReferenceType = 'Digital'"!]
        [!IF "ReferenceDirection = 'Input'"!]
            [!VAR "IndexType" = "'IODAL_DIO_INPUT'"!]
        [!ELSE!]
            [!VAR "IndexType" = "'IODAL_DIO_OUTPUT'"!]
        [!ENDIF!]
        [!VAR "IndexGlobal" = "num:i($IndexDigital)"!]
        [!VAR "IndexDigital" = "num:i($IndexDigital + 1)"!]
    [!ELSEIF "ReferenceType = 'Analog'"!]
        [!IF "TriggerType = 'SW'"!]
            [!VAR "IndexType" = "'IODAL_ANALOG_SW_TRIG'"!]
        [!ELSE!]
            [!VAR "IndexType" = "'IODAL_ANALOG_HW_TRIG'"!]
        [!ENDIF!]
        [!VAR "IndexGlobal" = "num:i($IndexAnalog)"!]
        [!VAR "IndexAnalog" = "num:i($IndexAnalog + 1)"!]
    [!ELSEIF "ReferenceType = 'Pwm'"!]
        [!IF "UseExternalDevice = 'true'"!]
            [!VAR "IndexType" = "'IODAL_PWM_EXT_DEV_OUTPUT'"!]
        [!ELSE!]
            [!IF "PwmType = 'SYNC'"!]
                [!VAR "IndexType" = "'IODAL_PWM_SYNC_OUTPUT'"!]
            [!ELSE!]
                [!IF "node:value(node:ref(PwmRef)/PwmChannelClass) = 'PWM_VARIABLE_PERIOD'"!]
                    [!VAR "IndexType" = "'IODAL_PWM_VARIBLE_PERIOD_OUTPUT'"!]
                [!ELSE!]
                    [!VAR "IndexType" = "'IODAL_PWM_FIXED_PERIOD_OUTPUT'"!]
                [!ENDIF!]
            [!ENDIF!]
        [!ENDIF!]
        [!VAR "IndexGlobal" = "num:i($IndexPwm)"!]
        [!VAR "IndexPwm" = "num:i($IndexPwm + 1)"!]
    [!ELSEIF "ReferenceType = 'Icu'"!]
        [!VAR "IndexType" = "'IODAL_TIMER_CAPTURE'"!]
        [!VAR "IndexGlobal" = "num:i($IndexIcu)"!]
        [!VAR "IndexIcu" = "num:i($IndexIcu + 1)"!]
    [!ELSE!]
        [!VAR "IndexType" = "'IODAL_TIMER_OUTPUT'"!]
        [!VAR "IndexGlobal" = "num:i($IndexOcu)"!]
        [!VAR "IndexOcu" = "num:i($IndexOcu + 1)"!]
        [!IF "ReferenceDirection = 'Trigger'"!]
            [!VAR "IndexSwTrigger" = "concat(num:i($IndexOcu - 1), ',    /*Index of Analog SW Trigger descriptor*/')"!]
        [!ENDIF!]
    [!ENDIF!]
    [!VAR "IndexAll" = "num:i($IndexAll + 1)"!]    [!//index to keep count of the last element in the array
[!CODE!]
    /*[!"node:name(.)"!]*/
    {
        [!"$IndexType"!],        /*Datatype of current channel*/
        [!"$IndexGlobal"!]        /*Index of current channel in own Datatype Channel Descriptor*/
    }[!IF "not($IndexAll = $AllChannelCount)"!],[!ENDIF!]
    
[!ENDCODE!]
[!ENDLOOP!]
[!CODE!]
};
[!ENDCODE!]

[!CODE!]
/*=====================================================================================================================*/
/**
@brief      IoDal_AdcBufferSetup - callout to initialize ADC buffers
@details    This function is used to setup external buffers for ADC results for each configured ADC group

@return     void

@pre None
@post None
*/
/*=====================================================================================================================*/
FUNC(void, SAMPLE_APP_CODE) IoDal_AdcBufferSetup(void)
{
[!ENDCODE!]

    [!VAR "Array" = "''"!]
    [!VAR "Group" = "num:i(0)"!]

    
    [!LOOP "IoDAL/*"!]
        [!IF "ReferenceType = 'Analog'"!]
            [!IF "not(contains($Array,node:name(node:ref(AnalogRef))))"!]
                [!VAR "Array" = "concat($Array, node:name(node:ref(AnalogRef)), '_')"!]
                [!VAR "Group" = "node:name(node:ref(AnalogRef))"!]
                [!LOOP "../../IoDAL/*"!]
                    [!IF "ReferenceType = 'Analog'"!]
                        [!IF "node:name(node:ref(AnalogRef)) = $Group"!]
                            [!BREAK!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDLOOP!]
[!CODE!]
    (void)Adc_SetupResultBuffer([!"$Group"!], &IoDal_AniDescriptor_[!"$Group"!]_HW_VAR_0[0]);
[!ENDCODE!]
            [!ENDIF!]
        [!ENDIF!]
    [!ENDLOOP!]

[!CODE!]
}
[!ENDCODE!]


[!CODE!]

CONST(IoDal_BswIoConfigType, IODAL_CONST) IoDal_Config[IODAL_MAX_HW_VARIANTS] = 
{    
    {
        [!"$IndexAnalog"!], /*Number of Analog channels*/
        [!"$IndexSwTrigger"!]
        [!"$IndexPwm"!], /*Number of Pwm channels*/
        [!"$IndexDigital"!], /*Number of Digital channels*/
        [!"$IndexOcu"!], /*Number of Output Compare  channels*/
        [!"$IndexIcu"!], /*Number of input Capture channels*/
#if IODAL_MAX_ANALOG_CHANNELS_HW_VAR_0 > 0U
        IoDal_AdcChannelDescriptor_HW_VAR_0,
        &IoDal_AdcBufferSetup,
#endif
#if IODAL_MAX_PWM_CHANNELS_HW_VAR_0 > 0U
        IoDal_PwmChannelDescriptor_HW_VAR_0,
#endif
#if IODAL_MAX_DIO_CHANNELS_HW_VAR_0 > 0U        
        IoDal_DioChannelDescriptor_HW_VAR_0,
#endif
#if IODAL_MAX_OCU_CHANNELS_HW_VAR_0 > 0U        
        IoDal_OcuChannelDescriptor_HW_VAR_0,
#endif
#if IODAL_MAX_ICU_CHANNELS_HW_VAR_0 > 0U        
        IoDal_IcuChannelDescriptor_HW_VAR_0,
#endif        
        IoDal_BswChannelMap_HW_VAR_0
    }    
};
[!ENDCODE!]
[!ENDSELECT!]       
[!ENDNOCODE!]
[!ENDIF!]

