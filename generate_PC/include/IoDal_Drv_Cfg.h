/**
*   @file    IoDal_Drv_Cfg.h
*   @version 0.8.1
*
*   @brief   Integration Framework - IO Driver Abstraction Layer component low-level configuration file
*   @details This file implements the IODAL configuration header for connection to low-level drivers.
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
#ifndef IODAL_DRV_CFG_H
#define IODAL_DRV_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
[!NOCODE!]
[!SELECT "IntegrationAppGeneral"!]

[!IF "UseAdc = 'true'"!]
[!CODE!]
#define IFWK_USE_ADC
[!ENDCODE!]
[!ENDIF!]
 
[!IF "UsePwm = 'true'"!]
[!CODE!]
#define IFWK_USE_PWM
[!ENDCODE!]
[!ENDIF!]

[!IF "UseOcu = 'true'"!]
[!CODE!]
#define IFWK_USE_OCU
[!ENDCODE!]
[!ENDIF!]

[!IF "UseDio = 'true'"!]
[!CODE!]
#define IFWK_USE_DIO
[!ENDCODE!]
[!ENDIF!]

[!ENDSELECT!]
[!ENDNOCODE!]

#ifdef IFWK_USE_DIO
    #include "Dio.h"
    #include "Port.h"
#endif

#ifdef IFWK_USE_ADC
    #include "Adc.h"
#endif

#ifdef IFWK_USE_PWM
    #include "Pwm.h"
#endif

#ifdef IFWK_USE_OCU
    #include "Ocu.h"
#endif    
    
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#define IODAL_DRV_CFG_VENDOR_ID                       43

#define IODAL_DRV_CFG_AR_RELEASE_MAJOR_VERSION        4
#define IODAL_DRV_CFG_AR_RELEASE_MINOR_VERSION        3
#define IODAL_DRV_CFG_AR_RELEASE_REVISION_VERSION     1

#define IODAL_DRV_CFG_SW_MAJOR_VERSION                0
#define IODAL_DRV_CFG_SW_MINOR_VERSION                8
#define IODAL_DRV_CFG_SW_PATCH_VERSION                1    
    
    
typedef uint16 IoDal_PwmPeriodType;
    
    
typedef uint16 IoDal_Dio_ExtDev_Config;
typedef uint16 IoDal_Pwm_ExtDev_Config;

typedef void (*IoDal_Dio_InitCalloutType)(const IoDal_Dio_ExtDev_Config *);
typedef void (*IoDal_Dio_DeInitCalloutType)(void);
typedef void (*IoDal_Dio_UpdateCalloutType)(uint8, uint8 *);

typedef void (*IoDal_Pwm_InitCalloutType)(const IoDal_Pwm_ExtDev_Config *);
typedef void (*IoDal_Pwm_DeInitCalloutType)(void);
typedef void (*IoDal_Pwm_UpdateCalloutType)(uint8, uint16 *);


/**
* @brief          Structure to configure external devices (SPI).
* @details        Data structure containing the set of configuration parameters required 
*                 for initializin external SPI devices.
*/
typedef struct
{  
   /**< @brief Pointer to configuration data of external (SPI) device */
   P2CONST(IoDal_Dio_ExtDev_Config, AUTOMATIC, IODAL_APPL_CONST)   pExtDioChannelCfg;
  
   CONST(IoDal_Dio_InitCalloutType,       IODAL_CONST) pfDio_ExtDev_InitHandler;
   CONST(IoDal_Dio_DeInitCalloutType,     IODAL_CONST) pfDio_ExtDev_DeInitHandler;
   CONST(IoDal_Dio_UpdateCalloutType,     IODAL_CONST) pfDio_ExtDev_UpdateHandler;
} IoDal_ExternalDioDeviceConfig;

/**
* @brief          Structure to configure external devices (SPI).
* @details        Data structure containing the set of configuration parameters required 
*                 for initializin external SPI devices.
*/
typedef struct
{  
   /**< @brief Pointer to configuration data of external (SPI) device */
   P2CONST(IoDal_Pwm_ExtDev_Config, AUTOMATIC, IODAL_APPL_CONST)   pExtPwmChannelCfg;
   
   CONST(IoDal_Pwm_InitCalloutType,        IODAL_CONST) pfPwm_ExtDev_InitHandler;
   CONST(IoDal_Pwm_DeInitCalloutType,      IODAL_CONST) pfPwm_ExtDev_DeInitHandler;
   CONST(IoDal_Pwm_UpdateCalloutType,      IODAL_CONST) pfPwm_ExtDev_UpdateHandler;
} IoDal_ExternalPwmDeviceConfig;    

/*================================================================================================*/
#ifdef __cplusplus
}
#endif

#endif  /* IODAL_TYPES_H*/
