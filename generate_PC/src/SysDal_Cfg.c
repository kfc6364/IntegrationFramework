[!AUTOSPACING!]
[!NOCODE!]
[!CODE!]
/**
*   @file           SysDal_Cfg.c
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
[!ENDCODE!]
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/UseAutosarOS) = 'true'"!]   
[!CODE!]
#include "Os.h"
[!ENDCODE!]
[!ENDIF!]
[!CODE!]
/*===================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
====================================================================================================================*/
#define SYSDAL_CFG_VENDOR_ID_C                       43

#define SYSDAL_CFG_AR_RELEASE_MAJOR_VERSION_C        4
#define SYSDAL_CFG_AR_RELEASE_MINOR_VERSION_C        3
#define SYSDAL_CFG_AR_RELEASE_REVISION_VERSION_C     1

#define SYSDAL_CFG_SW_MAJOR_VERSION_C                0
#define SYSDAL_CFG_SW_MINOR_VERSION_C                8
#define SYSDAL_CFG_SW_PATCH_VERSION_C                1
[!ENDCODE!]

[!VAR "Array" = "'SysDal.h'"!]
[!VAR "ComDalWasIncluded" = "num:i(0)"!]
[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/PowerManagement/*/InitList/*"!]
    [!IF "not(contains($Array,node:value(CalloutHeader)))"!]
        [!VAR "Array" = "concat($Array, node:value(CalloutHeader))"!]
[!CODE!]
#include "[!"node:value(CalloutHeader)"!]"
[!ENDCODE!]
    [!ENDIF!]   
    [!IF "node:value(CalloutHeader) = 'ComDal.h'"!]
        [!VAR "ComDalWasIncluded" = "num:i(1)"!]
    [!ENDIF!]
[!ENDLOOP!]

[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/UseAutosarOS) = 'false'"!]   
[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/InterruptList/*"!]
    [!IF "not(contains($Array,node:value(ISR_HandlerHeader)))"!]
        [!VAR "Array" = "concat($Array, node:value(ISR_HandlerHeader))"!]
[!CODE!]
#include "[!"node:value(ISR_HandlerHeader)"!]"
[!ENDCODE!]
    [!ENDIF!]
[!ENDLOOP!]
[!ENDIF!]

[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/IntegrationAppTaskList/*"!]
    [!LOOP "TaskFunctionList/*"!]
        [!IF "not(contains($Array,node:value(FunctionHeader)))"!]
            [!VAR "Array" = "concat($Array, node:value(FunctionHeader))"!]
[!CODE!]
#include "[!"node:value(FunctionHeader)"!]"
[!ENDCODE!]
        [!ENDIF!]
    [!ENDLOOP!]
[!ENDLOOP!]

[!CODE!]

[!ENDCODE!]
[!IF "$ComDalWasIncluded = num:i(1)"!]
[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*[1]"!]    
    [!IF "node:refexists(StartMessageRef)"!] 
    [!CODE!]
#define    SYSDAL_STARTUP_MSG_CHANNEL   [!"node:name(node:ref(StartMessageRef))"!]
#define    SYSDAL_STARUP_MESSAGE_LEN          9U
#define    SYSDAL_SHUTDOWN_MESSAGE      "Good Bye"
#define    SYSDAL_SHUTDOWN_MESSAGE_LEN        8U
VAR(char, AUTOMATIC) WriteBuffer[SYSDAL_STARUP_MESSAGE_LEN]={"System Up"}; 

    [!ENDCODE!]
    [!ENDIF!]
[!ENDSELECT!]
[!ENDIF!]

[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/UseAutosarOS) = 'false'"!]
[!CODE!]
#include "sys_init.h"
[!ENDCODE!]
    [!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/InterruptList/*"!]
[!CODE!]
extern ISR ([!"node:name(.)"!]);
[!ENDCODE!]
    [!ENDLOOP!]

[!CODE!]

[!ENDCODE!]

[!CODE!]
FUNC(void, SAMPLE_APP_CODE)SysDal_SetAllProgrammableInterrupts(void)
{
    sys_disableAllInterrupts();
[!ENDCODE!]
    [!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/InterruptList/*"!]
[!CODE!]
    sys_enableIsrSource([!"node:value(InterruptNumber)"!], [!"num:inttohex(node:value(InterruptPriority))"!]);
    sys_registerIsrHandler([!"node:value(InterruptNumber)"!], (uint32) & [!"node:name(.)"!]);
[!ENDCODE!]
    [!ENDLOOP!]
[!CODE!]
    sys_enableAllInterrupts();
}

[!CR!]
[!ENDCODE!]
[!ENDIF!]

[!CODE!]
/**
@brief      SysDal_InitBlockZero - Function used for initialising the system
@details    Shall be used to init module that will not be deinitialised when go to sleep
            
@return     None
*/
FUNC (void, SAMPLE_APP_CODE)SysDal_InitBlockZero(void)
{
[!ENDCODE!]
[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/PowerManagement/*/InitList/*"!]
    [!IF "(node:value(CalloutApplicability) = 'InitBlockZero')"!]
[!CODE!]
    [!"node:name(.)"!]([!"node:value(Parameters)"!]);
[!ENDCODE!]
    [!ENDIF!]
[!ENDLOOP!]
[!CODE!]
}
[!CR!]
[!ENDCODE!]

[!CODE!]
/**
@brief      SysDal_InitBlockOne - Function used for initialising the system
@details    Shall be used to init module that will be deinitialised when go to sleep
            Shall be used to invoke callouts used for System initialisation
            
@return     None
*/
FUNC (void, SAMPLE_APP_CODE)SysDal_InitBlockOne(void)
{
[!ENDCODE!]
[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/PowerManagement/*/InitList/*"!]
    [!IF "(node:value(CalloutApplicability) = 'InitBlockOne')"!]
[!CODE!]
    [!"node:name(.)"!]([!"node:value(Parameters)"!]);
[!ENDCODE!]
    [!ENDIF!]
[!ENDLOOP!]
[!CODE!]
}
[!CR!]
[!ENDCODE!]



[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/EnablePowerManagement) = 'true'"!]
[!CODE!]
/**
@brief      SysDal_DeinitBlockOne - Function used for deinitialising the system
@details    Shall be used to deinit module when go to sleep
            Shall be used to invoke callouts used for setting the configured low power mode
            
@return     None
*/
FUNC (void, SAMPLE_APP_CODE)SysDal_DeinitBlockOne(void)
{
[!ENDCODE!]
[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/PowerManagement/*/DeinitList/*"!]
[!CODE!]
    [!"node:name(.)"!]([!"node:value(Parameters)"!]);
[!ENDCODE!]
[!ENDLOOP!]
[!CODE!]
}
[!CR!]
[!ENDCODE!]    
    
[!CODE!]
/**
@brief      SysDal_SetWakeupEvents - Function used for setting the wakeup sources
@details    Shall be used to set the wakeup sources before system go to configured Low Power mode
            
@return     None
*/
FUNC (void, SAMPLE_APP_CODE)SysDal_SetWakeupEvents(void)
{
[!ENDCODE!]

[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/PowerManagement/*/WakeUpRelatedEvents/*"!]
    [!IF "(node:value(CalloutApplicability) = 'SetWakeupEvents')"!]
[!CODE!]
    [!"node:name(.)"!]([!"node:value(Parameters)"!]);
[!ENDCODE!]
    [!ENDIF!]
[!ENDLOOP!]

[!CODE!]
}
[!CR!]
[!ENDCODE!]

[!CODE!]
/**
@brief      SysDal_ClearWakeupEvents - Function used for clear the wakeup sources
@details    Shall be used to clear the wakeup sources when transition from configured Low Power mode to normal Run
            
@return     None
*/
FUNC (void, SAMPLE_APP_CODE)SysDal_ClearWakeupEvents(void)
{
[!ENDCODE!]

[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/PowerManagement/*/WakeUpRelatedEvents/*"!]
    [!IF "(node:value(CalloutApplicability) = 'ClearWakeupEvents')"!]
[!CODE!]
    [!"node:name(.)"!]([!"node:value(Parameters)"!]);
[!ENDCODE!]
    [!ENDIF!]
[!ENDLOOP!]

[!CODE!]
}
[!CR!]
[!ENDCODE!]
[!ENDIF!]


[!//Loop all configured tasks
[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/IntegrationAppTaskList/*"!]
[!//Check if AUTOSAR OS was NOT configured
    [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/UseAutosarOS) = 'false'"!]    
[!CODE!]void [!"node:value(AppTaskId)"!](void)
{
[!ENDCODE!]
        [!LOOP "TaskFunctionList/*"!]
    [!CODE!]
    [!"node:value(UserFunction)"!];
    [!ENDCODE!]
        [!ENDLOOP!]
[!CODE!]
}
[!CR!]
[!ENDCODE!]

[!ELSE!]  [!//Check if AUTOSAR OS was configured

    [!IF "node:value(AppTaskId) = 'INTAPP_PREHOOK_TASK'"!] [!//Check if configured task is set as PRE_HOOK (startup hook)
[!CODE!]void StartupHook(void)
{
[!ENDCODE!]
       [!LOOP "TaskFunctionList/*"!]
    [!CODE!]
    [!"node:value(UserFunction)"!];
    [!ENDCODE!]
        [!ENDLOOP!]
[!CODE!]
}

[!CR!]
[!ENDCODE!]
    [!ELSE!]  [!//Check if configured task is a normal task
    
[!CODE!]TASK([!"node:value(AppTaskId)"!])
{
    while(1)
    {
        ClearEvent([!"node:value(OsEventName)"!]);
[!ENDCODE!]
        [!LOOP "TaskFunctionList/*"!]
    [!CODE!]
        [!"node:value(UserFunction)"!];
    [!ENDCODE!]
        [!ENDLOOP!]        
[!CODE!]
        WaitEvent([!"node:value(OsEventName)"!]);
    }
}    
[!CR!]
[!ENDCODE!]
    [!ENDIF!] [!//Check if configured task is set as PRE_HOOK (startup hook)
[!ENDIF!] [!//Check if AUTOSAR OS was NOT configured
[!ENDLOOP!]  [!//Loop all configured tasks

[!//Check if AUTOSAR OS was enabled
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/UseAutosarOS) = 'true'"!]
[!CODE!]
void ErrorHook(StatusType myError)
{
    if (myError == E_OS_LIMIT) return; /* Can happen after debugger break */
    ShutdownOS(myError);
}

[!ENDCODE!]
[!ENDIF!] [!//Check if AUTOSAR OS was NOT configured

[!CODE!]

#ifdef IFWK_USE_WDG
#if (ENABLE_WDG_EXPIRE_TEST == STD_ON)
FUNC (void, SYSDAL_APP_CODE) WdgExpire_Callback(void)
{
    #ifdef SYSDAL_STARTUP_MSG_CHANNEL    
    ComDal_WriteData(SYSDAL_STARTUP_MSG_CHANNEL, "WatchDog EVENT!", 13U);
    #endif    
    SysDal_Wdg_SetMode(WDGIF_SLOW_MODE);
}
#endif 

FUNC(void, SYSDAL_APP_CODE) SysDal_Wdg_SetTriggerCondition(uint16 TimeOut) 
{
     Wdg_SetTriggerCondition(TimeOut);
}
 
#endif  
[!ENDCODE!]

[!CODE!]
[!CR!]
const SysDal_ConfigType SysDal_Config=
{
    &SysDal_InitBlockZero,
    &SysDal_InitBlockOne,
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/UseAutosarOS) = 'false'"!]    
    &SysDal_SetAllProgrammableInterrupts
[!ELSE!]
    NULL_PTR
[!ENDIF!]    
#if (SYSDAL_LOW_POWER_MODE == STD_ON)     
    ,
    &SysDal_DeinitBlockOne,
    &SysDal_SetWakeupEvents,
    &SysDal_ClearWakeupEvents
#endif
};

#ifdef __cplusplus
}
#endif
[!ENDCODE!]
[!ENDNOCODE!]