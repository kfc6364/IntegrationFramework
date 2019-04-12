/**
*   @file           SysDal.c
*   @version        0.8.1
*
*   @brief          Integration Framework - SysDal Abstraction Layer component
*   @details        This file implements the SysDal interface to application layer.
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
*   SW Version           : 0.8.1
*   Build Version        : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
*
============================================================================================================================*/
/*============================================================================================================================
==============================================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*===================================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
====================================================================================================================*/
#include "SysDal.h"
#include "Mcu.h"
#include "sys_init.h"
#include "typedefs.h"
#include "modules.h"
#if defined(AUTOSAR_OS_NOT_USED)
#include "SysDal_IntSch.h"
#include "Gpt.h"
#endif/*AUTOSAR_OS_NOT_USED*/
#if(SYSDAL_LOW_POWER_MODE == STD_ON)
#include "Icu.h"
#endif/*SYSDAL_LOW_POWER_MODE == STD_ON*/
/*===================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
====================================================================================================================*/
#define SYSDAL_VENDOR_ID_C                       43

#define SYSDAL_AR_RELEASE_MAJOR_VERSION_C        4
#define SYSDAL_AR_RELEASE_MINOR_VERSION_C        3
#define SYSDAL_AR_RELEASE_REVISION_VERSION_C     1

#define SYSDAL_SW_MAJOR_VERSION_C                0
#define SYSDAL_SW_MINOR_VERSION_C                8
#define SYSDAL_SW_PATCH_VERSION_C                1
/*===================================================================================================================
*                                     FILE VERSION CHECKS
====================================================================================================================*/
/* Check if source file and SYSDAL header file are of the same vendor */
#if (SYSDAL_VENDOR_ID_C != SYSDAL_VENDOR_ID)
    #error "SysDal.c and SysDal.h have different vendor ids"
#endif

/* Check if source file and SYSDAL header file are of the same Autosar version */
#if ((SYSDAL_AR_RELEASE_MAJOR_VERSION_C != SYSDAL_AR_RELEASE_MAJOR_VERSION) || \
     (SYSDAL_AR_RELEASE_MINOR_VERSION_C != SYSDAL_AR_RELEASE_MINOR_VERSION) || \
     (SYSDAL_AR_RELEASE_REVISION_VERSION_C != SYSDAL_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of SysDal.c and SysDal.h are different"
#endif

/* Check if source file and SYSDAL header file are of the same Software version */
#if ((SYSDAL_SW_MAJOR_VERSION_C != SYSDAL_SW_MAJOR_VERSION) || \
     (SYSDAL_SW_MINOR_VERSION_C != SYSDAL_SW_MINOR_VERSION) || \
     (SYSDAL_SW_PATCH_VERSION_C != SYSDAL_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SysDal.c and SysDal.h are different"
#endif

/* Check if source file and SYSDAL configuration header file are of the same vendor */
#if (SYSDAL_VENDOR_ID_C != SYSDAL_CFG_VENDOR_ID)
    #error "SysDal.c and SysDal_Cfg.h have different vendor ids"
#endif

/* Check if source file and SYSDAL configuration header file are of the same Autosar version */
#if ((SYSDAL_AR_RELEASE_MAJOR_VERSION_C != SYSDAL_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (SYSDAL_AR_RELEASE_MINOR_VERSION_C != SYSDAL_CFG_AR_RELEASE_MINOR_VERSION) || \
     (SYSDAL_AR_RELEASE_REVISION_VERSION_C != SYSDAL_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of SysDal.c and SysDal_Cfg.h are different"
#endif

/* Check if source file and SYSDAL configuration header file are of the same software version */
#if ((SYSDAL_SW_MAJOR_VERSION_C != SYSDAL_CFG_SW_MAJOR_VERSION) || \
     (SYSDAL_SW_MINOR_VERSION_C != SYSDAL_CFG_SW_MINOR_VERSION) || \
     (SYSDAL_SW_PATCH_VERSION_C != SYSDAL_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SysDal.c and SysDal_Cfg.h are different"
#endif
/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
SysDal_EcuModeType SysDal_EcuMode = SYSDAL_STATE_STARTUP;
SysDal_EcuModeType SysDal_EcuModeRequest = SYSDAL_STATE_RUN;
extern const SysDal_ConfigType SysDal_Config;

#if defined(AUTOSAR_OS_NOT_USED)
extern const vuint32_t IntcVectorTableHw[];
#endif /*AUTOSAR_OS_NOT_USED)*/

#ifdef IFWK_USE_WDG
    #if (ENABLE_WDG_EXPIRE_TEST == STD_ON)
    boolean SysDal_RequestWdgRst = FALSE;
    #endif /*(ENABLE_WDG_EXPIRE_TEST == STD_ON)*/
#endif /*IFWK_USE_WDG*/
/*===============================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
===============================================================================================*/
#if (SYSDAL_LOW_POWER_MODE == STD_ON)
FUNC (void, SAMPLE_APP_CODE) SysDal_PrepareGoToSleep(SysDal_EcuModeType SleepMode);
#endif /*#if (SYSDAL_LOW_POWER_MODE == STD_ON)*/

FUNC (void, SAMPLE_APP_CODE) SysDal_StartUpInit(void);
FUNC (void, SAMPLE_APP_CODE) SysDal_WakeUpInit(void);
FUNC (void, SAMPLE_APP_CODE) SysDal_PrepareGoToRun(void);
/*===============================================================================================
*                                       LOCAL FUNCTIONS
===============================================================================================*/
/**
@brief      SysDal_StartUpInit - System initialization function
@details    Shall be used to initialize clock sources and block zero drivers 
            
@return     None
*/
void SysDal_StartUpInit()
{
#if (USE_MCU_MODULE == STD_ON)

    Mcu_Init(&McuModuleConfiguration);
	Mcu_InitClock(McuClockSettingConfig_0);
#if(MCU_NO_PLL==STD_OFF)
    while ( MCU_PLL_LOCKED != Mcu_GetPllStatus() ) 
    {
    /* wait until all enabled PLLs are locked */
    }
    /* switch system clock tree to PLL */
    Mcu_DistributePllClock();
#endif/*MCU_NO_PLL == STD_OFF*/
    Mcu_SetMode((Mcu_ModeType) SYSDAL_MCU_RUN_MODE);
#endif/*USE_MCU_MODULE == STD_ON*/
       
   SysDal_Config.InitBlockZeroCallout();
   
   SysDal_EcuMode = SYSDAL_STATE_STARTUP;
}

/**
@brief      SysDal_WakeUpInit - System initialization function called after StartUpInit 
@details    Shall be used to reinitialise the sistem after transition from a Low Power mode 
            
@return     None

@pre None
@post None
*/
void SysDal_WakeUpInit()
{
    SysDal_Config.InitBlockOneCallout();
#if defined(AUTOSAR_OS_NOT_USED)      
    SysDal_Config.SetProgrammableInterruptsCallout();
#endif /*(AUTOSAR_OS_NOT_USED == STD_ON)*/   
    SysDal_PrepareGoToRun();
}

/**
@brief      SysDal_PrepareGoToRun - Function used to prepare entering the configured Run mode
@details    Actions before entering RUN mode:
            -Disable Wakeup
            -Start scheduling
            
@return     None
*/
FUNC (void, SAMPLE_APP_CODE) SysDal_PrepareGoToRun(void)
{
#if (SYSDAL_LOW_POWER_MODE == STD_ON)
   SysDal_Config.ClearWakeupEventsCallout();
#endif /*SYSDAL_LOW_POWER_MODE == STD_ON*/
   if(SYSDAL_STATE_STARTUP != SysDal_EcuMode)
   {
      Mcu_SetMode((Mcu_ModeType)SYSDAL_MCU_RUN_MODE);
   }
   else
   {
       /*Do nothing*/
   }
#if defined(AUTOSAR_OS_NOT_USED)        
   SysDal_IntSch_StartScheduler();
#else 
   StartOS(Mode01);
#endif /*(AUTOSAR_OS_NOT_USED == STD_ON)*/  
   SysDal_EcuModeRequest = SYSDAL_STATE_RUN;
}

#if (SYSDAL_LOW_POWER_MODE == STD_ON)
/**
@brief      SysDal_PrepareGoToSleep - Function used to prepare entering the configured LowPower mode
@details    Actions before going to sleep:
            -Stop scheduling
            -Enable wakeup
            -Deinit software modules
            
@return     None
*/
FUNC (void, SAMPLE_APP_CODE) SysDal_PrepareGoToSleep(SysDal_EcuModeType SysDalSleep)
{
    SysDal_IntSch_StopScheduler();
    SysDal_Config.SetWakeupEventsCallout();
    sys_disableAllInterrupts();/*exclusive area*/
    SysDal_Config.DeInitBlockOneCallout();
    sys_enableAllInterrupts();/*exclusive area*/
    if(SysDalSleep == SYSDAL_STATE_SLEEP)
    {   
        SysDal_EcuMode = SYSDAL_STATE_SLEEP;
        Mcu_SetMode((Mcu_ModeType)SYSDAL_MCU_SLEEP_MODE);
    }
    else
    {
        SysDal_EcuMode = SYSDAL_STATE_DEEPSLEEP;
        Mcu_SetMode((Mcu_ModeType)SYSDAL_MCU_DEEPSLEEP_MODE);
   }
}
#endif /*SYSDAL_LOW_POWER_MODE == STD_ON*/

/*===============================================================================================
*                                       GLOBAL FUNCTIONS
===============================================================================================*/

/**
@brief      WakeUpNotification - Notification called by the configured wakeup source
@details    Shall be used to reinitialise the system from configured Low Power mode 
            
@return     None
*/
FUNC (void, ICU_CODE) SysDal_Init(void)
{
    SysDal_StartUpInit();
    
    SysDal_WakeUpInit();
}

/**
@brief      WakeUpNotification - Notification called by the configured wakeup source
@details    Shall be used to reinitialise the system from configured Low Power mode 
            
@return     None
*/
#if (SYSDAL_LOW_POWER_MODE == STD_ON)

FUNC (void, ICU_CODE) WakeUpNotification(void)
{
    SysDal_WakeUpInit();
}
#endif/*SYSDAL_LOW_POWER_MODE == STD_ON*/

/**
@brief      SysDal_Main - Main function for System Driver abstraction module
@details    Shall be used to compute the desired LowPower mode based on request (from VDR)
            Shall be used to set the request LowPower 
            
@return     None
*/
FUNC (void, SAMPLE_APP_CODE) SysDal_MainFunction(void)
{
#if (SYSDAL_LOW_POWER_MODE == STD_ON)
    SysDal_EcuMode =  SysDal_EcuModeRequest;
    if(SYSDAL_STATE_SLEEP == SysDal_EcuModeRequest)
    {
        SysDal_PrepareGoToSleep(SYSDAL_STATE_SLEEP);
    }
    else if(SYSDAL_STATE_DEEPSLEEP == SysDal_EcuModeRequest)
    {
        SysDal_PrepareGoToSleep(SYSDAL_STATE_DEEPSLEEP);
    }
    else 
    {
        /*Do nothing*/
    }
#endif /*SYSDAL_LOW_POWER_MODE == STD_ON*/

#ifdef IFWK_USE_WDG
    #if (ENABLE_WDG_EXPIRE_TEST == STD_ON)
        if(TRUE == SysDal_RequestWdgRst)
        {    
            SysDal_RequestWdgRst = FALSE;
            SysDal_Wdg_SetTriggerCondition(0);
        }
        else
        {
    #endif  /*(ENABLE_WDG_EXPIRE_TEST == STD_ON)*/        
            SysDal_Wdg_SetTriggerCondition(SYSDAL_WDG_TRIGGER_VALUE);
    #if (ENABLE_WDG_EXPIRE_TEST == STD_ON)            
        }              
    #endif /*(ENABLE_WDG_EXPIRE_TEST == STD_ON)*/  
#endif  
#if (SYSDAL_LOW_POWER_MODE == STD_ON)  
    }
#endif /*(SYSDAL_LOW_POWER_MODE == STD_ON)*/  
}

/**
@brief      SysDal_WriteModeRequest - Function used to request for setting a Power mode
@details    Shall be used to request a configured LowPower mode
            
@return     None
*/
FUNC(void, SAMPLE_APP_CODE) SysDal_WriteModeRequest(SysDal_EcuModeType Mode)
{
    SysDal_EcuModeRequest = Mode;
}

/**
@brief      SysDal_GetPowerMode - Function used to get current power mode
@details    This function is currently a stub.
            
@return     None
*/

FUNC(SysDal_EcuModeType, SAMPLE_APP_CODE) SysDal_GetCurrentPowerMode(void)
{
    return SysDal_EcuMode;
}

/**
@brief      SysDal_ExecuteSwReset - Function used to request a SW reset.
@details    This function is currently a stub.
            
@return     None
*/
FUNC(void, SAMPLE_APP_CODE) SysDal_ExecuteSwReset()
{
#ifdef IFWK_USE_WDG
    #if (ENABLE_WDG_EXPIRE_TEST == STD_ON)	
    SysDal_RequestWdgRst = TRUE;
	#endif /*(ENABLE_WDG_EXPIRE_TEST == STD_ON)*/  
#endif	/*(IFWK_USE_WDG)*/ 
}

#ifdef __cplusplus
}
#endif
/** @} */
