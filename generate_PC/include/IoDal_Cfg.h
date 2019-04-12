/**
*   @file    IoDal_Cfg.h
*   @version 0.8.1
*
*   @brief   Integration Framework - IO Driver Abstraction Layer component configuration file
*   @details This file implements the IODAL configuration header.
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
#ifndef IODAL_Cfg_H
#define IODAL_Cfg_H

#ifdef __cplusplus
extern "C"{
#endif

[!IF "num:i(count(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/IoDAL/*)) != num:i(0)"!]

#include "IoDal_Types.h"
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#define IODAL_CFG_VENDOR_ID                       43

#define IODAL_CFG_AR_RELEASE_MAJOR_VERSION        4
#define IODAL_CFG_AR_RELEASE_MINOR_VERSION        3
#define IODAL_CFG_AR_RELEASE_REVISION_VERSION     1

#define IODAL_CFG_SW_MAJOR_VERSION                0
#define IODAL_CFG_SW_MINOR_VERSION                8
#define IODAL_CFG_SW_PATCH_VERSION                1


/*===================================================================================================================
*                                     FILE VERSION CHECKS
====================================================================================================================*/
/* Check if IoDal_Cfg.h header file and IoDal_Types.h header file are of the same vendor */
#if (IODAL_CFG_VENDOR_ID != IODAL_TYPES_VENDOR_ID)
    #error "IoDal_Cfg.h and IoDal_Types.h have different vendor ids"
#endif

/* Check if IoDal_Cfg.h header file and IoDal_Types.h header file are of the same Autosar version */
#if ((IODAL_CFG_AR_RELEASE_MAJOR_VERSION != IODAL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (IODAL_CFG_AR_RELEASE_MINOR_VERSION != IODAL_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (IODAL_CFG_AR_RELEASE_REVISION_VERSION != IODAL_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of IoDal_Cfg.h and IoDal_Types.h are different"
#endif

/* Check if IoDal_Cfg.h header file and IoDal_Types.h header file are of the same Software version */
#if ((IODAL_CFG_SW_MAJOR_VERSION != IODAL_TYPES_SW_MAJOR_VERSION) || \
     (IODAL_CFG_SW_MINOR_VERSION != IODAL_TYPES_SW_MINOR_VERSION) || \
     (IODAL_CFG_SW_PATCH_VERSION != IODAL_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of IoDal_Cfg.h and IoDal_Cfg.h are different"
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
    [!VAR "HW_Variants" = "num:i(1)"!]
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
            [!VAR "IndexOcu" = "num:i($IndexOcu + 1)"!]
            [!VAR "OcuChannelCount" = "$IndexOcu"!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]
#define    IODAL_MAX_DIO_CHANNELS_HW_VAR_0            [!"$IndexDigital"!]U
#define    IODAL_MAX_DIO_DESCRIPTORS                [!"$IndexDigital"!]U
    
#define    IODAL_MAX_PWM_CHANNELS_HW_VAR_0            [!"$IndexPwm"!]U
#define    IODAL_MAX_PWM_DESCRIPTORS                [!"$IndexPwm"!]U
    
#define    IODAL_MAX_ANALOG_CHANNELS_HW_VAR_0        [!"$IndexAnalog"!]U
#define    IODAL_MAX_ANI_DESCRIPTORS                [!"$IndexAnalog"!]U
    
#define    IODAL_MAX_OCU_CHANNELS_HW_VAR_0            [!"$IndexOcu"!]U
#define    IODAL_MAX_OCU_DESCRIPTORS                [!"$IndexOcu"!]U
    
#define    IODAL_MAX_ICU_CHANNELS_HW_VAR_0            [!"$IndexIcu"!]U
#define    IODAL_MAX_ICU_DESCRIPTORS                [!"$IndexIcu"!]U
    
#define    IODAL_MAX_CHANNELS_HW_VAR_0                [!"$AllChannelCount"!]U

#define    IODAL_MAX_HW_VARIANTS                    [!"$HW_Variants"!]U

#define IODAL_DEV_ERROR_DETECT                  (STD_OFF)
#define IODAL_ENABLE_DEM_REPORT_ERROR_STATUS    (STD_OFF)

/**
    * @brief          Symbolic name for the configuration IoDal channels.
*
*/
[!ENDCODE!]
[!ENDSELECT!]       
[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]
    [!VAR "IndexAll" = "num:i(0)"!]
    [!VAR "IndexDigital" = "num:i(0)"!]
    [!VAR "IndexAnalog" = "num:i(0)"!]
    [!VAR "IndexPwm" = "num:i(0)"!]
    [!VAR "IndexOcu" = "num:i(0)"!]
    [!LOOP "IoDAL/*"!]
[!CODE!]
#define    [!"node:name(.)"!]        ([!"num:i($IndexAll)"!]U)
[!ENDCODE!]
        [!VAR "IndexAll" = "num:i($IndexAll + 1)"!]
    [!ENDLOOP!]

    [!VAR "DioExtDev" = "'(STD_OFF)'"!]
    [!VAR "PwmExtDev" = "'(STD_OFF)'"!]
    [!VAR "PwmSync" = "'(STD_OFF)'"!]
    [!VAR "PwmVariablePeriod" = "'(STD_OFF)'"!]
    [!LOOP "IoDAL/*"!]
        [!IF "ReferenceType = 'Digital'"!]
            [!IF "UseExternalDevice = 'true'"!]
                [!VAR "DioExtDev" = "'(STD_ON)'"!]
            [!ENDIF!]
        [!ELSEIF "ReferenceType = 'Pwm'"!]
            [!IF "UseExternalDevice = 'true'"!]
                [!VAR "PwmExtDev" = "'(STD_ON)'"!]
            [!ENDIF!]
            [!IF "(PwmType = 'SYNC')"!] 
                [!VAR "PwmSync" = "'(STD_ON)'"!]
            [!ENDIF!]
            [!IF "node:value(node:ref(PwmRef)/PwmChannelClass) = 'PWM_VARIABLE_PERIOD'"!]
                [!VAR "PwmVariablePeriod" = "'(STD_ON)'"!]
            [!ENDIF!]
        [!ELSE!]
            [!// nothing to do
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]

#define IODAL_PWM_EXT_DEV          [!"$PwmExtDev"!]
#define IODAL_PWM_SYNC             [!"$PwmSync"!]      
#define IODAL_DIO_EXT_DEV          [!"$DioExtDev"!]
#define IODAL_VARIABLE_PERIOD      [!"$PwmVariablePeriod"!]
[!ENDCODE!]
[!ENDSELECT!]       
[!ENDNOCODE!]

extern void IoDal_AdcBufferSetup(void);
extern const IoDal_BswIoConfigType IoDal_Config[IODAL_MAX_HW_VARIANTS];

[!ENDIF!]
/*================================================================================================*/
#ifdef __cplusplus
}
#endif

#endif  /* IODAL_TYPES_H*/