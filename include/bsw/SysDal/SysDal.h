/**
*   @file           SysDal.h
*   @version        0.8.1
*
*   @brief          Integration Framework - SysDal high level interface implementation.
*   @details        SysDal high level interface implementation.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup SYSDAL
*   @{
*/
/*==================================================================================================
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
==================================================================================================*/

#ifndef SYSDAL_H
#define SYSDAL_H

#ifdef __cplusplus
extern "C"{
#endif
/*===================================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
====================================================================================================================*/
#include "SysDal_Cfg.h"
#include "SysDal_IntSch.h"
/*===================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
====================================================================================================================*/
/**
* @file          SysDal.h
*/
#define SYSDAL_VENDOR_ID                           43
#define SYSDAL_MODULE_ID                           100

#define SYSDAL_AR_RELEASE_MAJOR_VERSION            4
#define SYSDAL_AR_RELEASE_MINOR_VERSION            3
#define SYSDAL_AR_RELEASE_REVISION_VERSION         1

#define SYSDAL_SW_MAJOR_VERSION                    0
#define SYSDAL_SW_MINOR_VERSION                    8
#define SYSDAL_SW_PATCH_VERSION                    1
/*===================================================================================================================
*                                       FILE VERSION CHECKS
====================================================================================================================*/
/**
* @file           SysDal.h
*/
/* Check if source file and SYSDAL header file are of the same vendor */
#if (SYSDAL_VENDOR_ID != SYSDAL_CFG_VENDOR_ID)
    #error "SysDal.h and SysDal_Cfg.h have different vendor ids"
#endif

/* Check if source file and SYSDAL header file are of the same Autosar version */
#if ((SYSDAL_AR_RELEASE_MAJOR_VERSION != SYSDAL_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (SYSDAL_AR_RELEASE_MINOR_VERSION != SYSDAL_CFG_AR_RELEASE_MINOR_VERSION) || \
     (SYSDAL_AR_RELEASE_REVISION_VERSION != SYSDAL_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of SysDal.h and SysDal_Cfg.h are different"
#endif

/* Check if source file and SYSDAL header file are of the same Software version */
#if ((SYSDAL_SW_MAJOR_VERSION != SYSDAL_CFG_SW_MAJOR_VERSION) || \
     (SYSDAL_SW_MINOR_VERSION != SYSDAL_CFG_SW_MINOR_VERSION) || \
     (SYSDAL_SW_PATCH_VERSION != SYSDAL_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SysDal.h and SysDal_Cfg.h are different"
#endif
/*===================================================================================================================
                          GLOBAL TYPEDEFS
====================================================================================================================*/
/**
* @brief          Structure to define run States of the system
* @details        Data structure containing all the states the System can be. 
*/
typedef enum
{
    SYSDAL_STATE_OFF = 0,    /**< @brief PowerOff state of the system. */
    SYSDAL_STATE_RUN,        /**< @brief configured Run state of the system. */
    SYSDAL_STATE_SLEEP,      /**< @brief configured LowPower state of the system. */
    SYSDAL_STATE_DEEPSLEEP,  /**< @brief configured LowPower state of the system. */
    SYSDAL_STATE_STARTUP,    /**< @brief StartUp state of the system. */
    SYSDAL_STATE_WAKEUP,     /**< @brief WakeUp state of the system. */
    SYSDAL_STATE_SHUTDOWN    /**< @brief PowerDown state of the system. */
}SysDal_EcuModeType;

typedef void (*SysDal_CalloutType)(void);    /**< @brief pointer to configured collouts functions of SysDal. */

/**
* @brief          Structure to configure PWM internal channels
* @details        Data structure containing the callout functions of SysDal
*                 to enable the system and change the states
*/
typedef struct
{
    CONST(SysDal_CalloutType, SAMPLE_APP_CONST) InitBlockZeroCallout;             /**< @brief callout function used to Init the System. */
    CONST(SysDal_CalloutType, SAMPLE_APP_CONST) InitBlockOneCallout;              /**< @brief callout function used to Init the System. */
    CONST(SysDal_CalloutType, SAMPLE_APP_CONST) SetProgrammableInterruptsCallout; /**< @brief callout function to set the interrupts used by the System. */
#if (SYSDAL_LOW_POWER_MODE == STD_ON)                   
    CONST(SysDal_CalloutType, SAMPLE_APP_CONST) DeInitBlockOneCallout;            /**< @brief callout function used before going to sleep to deinit the system. */
    CONST(SysDal_CalloutType, SAMPLE_APP_CONST) SetWakeupEventsCallout;           /**< @brief callout function used before going to sleep to set WakeUp sources. */
    CONST(SysDal_CalloutType, SAMPLE_APP_CONST) ClearWakeupEventsCallout;          /**< @brief callout function use at wakeup to clear WakeUp sources. */
#endif
}SysDal_ConfigType;
/*===================================================================================================================
                                       LOCAL CONSTANTS
====================================================================================================================*/

/*===================================================================================================================
                                       LOCAL VARIABLES
====================================================================================================================*/


/*===================================================================================================================
                                       GLOBAL CONSTANTS
====================================================================================================================*/


/*===================================================================================================================
                                       GLOBAL VARIABLES
====================================================================================================================*/


/*===================================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
====================================================================================================================*/


/*===================================================================================================================
                                       LOCAL FUNCTIONS
====================================================================================================================*/

/*===================================================================================================================
                                       GLOBAL FUNCTIONS
====================================================================================================================*/

FUNC(void, SAMPLE_APP_CODE) SysDal_Init(void);
FUNC(void, SAMPLE_APP_CODE) SysDal_MainFunction(void);

#if (SYSDAL_LOW_POWER_MODE == STD_ON)
FUNC(void, SAMPLE_APP_CODE) SysDal_WriteModeRequest(SysDal_EcuModeType Mode);
FUNC(SysDal_EcuModeType, SAMPLE_APP_CODE) SysDal_GetCurrentPowerMode(void);
FUNC(void, SAMPLE_APP_CODE) SysDal_ExecuteSwReset(void);
#endif /*SYSDAL_LOW_POWER_MODE == STD_ON*/

#ifdef __cplusplus
}
#endif

#endif /*SYSDAL_H*/
/** @} */
