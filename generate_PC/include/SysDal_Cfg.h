[!NOCODE!]

[!CODE!]
/**
*   @file           SysDal_Cfg.h
*   @version        0.8.1
*
*   @brief          AUTOSAR IntegrationFramework - SysDal pre configuration file.
*   @details        Pre configuration structure instances
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
#ifndef SYSDAL_CFG_H
#define SYSDAL_CFG_H

#ifdef __cplusplus
extern "C"{
#endif
/*===================================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
====================================================================================================================*/
#include "Std_Types.h"
/*===================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
====================================================================================================================*/
/**
* @file          SysDal_Cfg.h
*/
#define SYSDAL_CFG_VENDOR_ID                           43
#define SYSDAL_CFG_MODULE_ID                           100

#define SYSDAL_CFG_AR_RELEASE_MAJOR_VERSION            4
#define SYSDAL_CFG_AR_RELEASE_MINOR_VERSION            3
#define SYSDAL_CFG_AR_RELEASE_REVISION_VERSION         1

#define SYSDAL_CFG_SW_MAJOR_VERSION                    0
#define SYSDAL_CFG_SW_MINOR_VERSION                    8
#define SYSDAL_CFG_SW_PATCH_VERSION                    1
/*===================================================================================================================
*                                       FILE VERSION CHECKS
====================================================================================================================*/
/**
* @file          SysDal_Cfg.h
*/
/* Check if source file and SYSDAL header file are of the same vendor */
#if (SYSDAL_CFG_VENDOR_ID != STD_VENDOR_ID)
    #error "SysDal_Cfg.h and Std_Types.h have different vendor ids"
#endif

/* Check if source file and SYSDAL header file are of the same Autosar version */
#if ((SYSDAL_CFG_AR_RELEASE_MAJOR_VERSION != STD_AR_RELEASE_MAJOR_VERSION) || \
     (SYSDAL_CFG_AR_RELEASE_MINOR_VERSION != STD_AR_RELEASE_MINOR_VERSION) || \
     (SYSDAL_CFG_AR_RELEASE_REVISION_VERSION != STD_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of SysDal_Cfg.h and Std_Types.h are different"
#endif

/* Check if source file and SYSDAL header file are of the same Software version */
#if ((SYSDAL_CFG_SW_MAJOR_VERSION != STD_SW_MAJOR_VERSION) || \
     (SYSDAL_CFG_SW_MINOR_VERSION != STD_SW_MINOR_VERSION) || \
     (SYSDAL_CFG_SW_PATCH_VERSION != STD_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SysDal_Cfg.h and Std_Types.h are different"
#endif
[!ENDCODE!]

[!CODE!]
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppGeneral/UseWdg) = 'true'"!]
#define IFWK_USE_WDG  
[!ENDIF!]
[!IF "node:exists(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/EnableWdgResetTest)"!]
#define ENABLE_WDG_EXPIRE_TEST            [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/EnableWdgResetTest) = 'true'"!](STD_ON)[!ELSE!]            (STD_OFF)[!ENDIF!]
[!ELSE!]
#define    ENABLE_WDG_EXPIRE_TEST            (STD_OFF)
[!ENDIF!]
[!ENDCODE!]

[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppGeneral/UseWdg) = 'true'"!]
[!CODE!]
#define    SysDal_Wdg_SetMode                Wdg_SetMode
extern FUNC(void, SYSDAL_APP_CODE)      Wdg_Cbk_GptNotification0(void);
extern FUNC(void, SYSDAL_APP_CODE)      SysDal_Wdg_SetTriggerCondition(uint16 TimeOut);
[!ENDCODE!]
[!ENDIF!]

[!CR!]
[!CR!]


[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*[1]"!]    
[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppGeneral/UseWdg) = 'true'"!]
[!CODE!]
#define    SYSDAL_WDG_TRIGGER_VALUE           [!"num:i(node:value(WdgTriggerTime))"!]U
[!ENDCODE!]
[!ENDIF!]
[!ENDSELECT!]

[!CODE!]
#define    SYSDAL_LOW_POWER_MODE              [!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/EnablePowerManagement) = 'true'"!](STD_ON)[!ELSE!](STD_OFF)[!ENDIF!]
[!ENDCODE!]
[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/PowerManagement/*/ModeSettingsConfig/*"!]
(node:value(node:ref(node:value(node:ref('/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/PowerManagement/*/ModeSettingsConfig/*/McuConfiguredModes')))/McuMode))
[!VAR "McuModId" = "num:i(node:value(node:ref(McuConfiguredModes)/McuMode))"!]
[!CODE!]
#define    [!"node:value(SystemModes)"!]                 [!"$McuModId"!]U[!//
[!ENDCODE!]
[!ENDLOOP!]

[!IF "node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationApp_FeatureList/UseAutosarOS) = 'false'"!]

[!VAR "Period"= "num:i(node:value(/AUTOSAR/TOP-LEVEL-PACKAGES//IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/IntegrationAppOSConfig/IntegrationAppSchedulingTime))"!]
[!VAR "Freq" = "num:i(node:value(node:ref(node:value(node:ref('/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/IntegrationAppOSConfig/GptTimer')))/GptChannelTickFrequency))"!]
[!VAR "GptChId" = "num:i(node:value(node:ref(node:value(node:ref('/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/IntegrationAppOSConfig/GptTimer')))/GptChannelId))"!]
[!VAR "Ticks" =  "($Freq * $Period) div num:i(1000000)"!]
[!CODE!]
#define    GPT_SCH_TICKS                       [!"num:i($Ticks)"!]U
#define    SYSDAL_SCH_GPT_TIMER_CHANNEL        [!"$GptChId"!]U
[!ENDCODE!]

[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/IntegrationAppTaskList/*"!]
    [!IF "node:value(AppTaskId) != 'INTAPP_PREHOOK_TASK'"!]
[!CODE!]
#define    [!"node:value(AppTaskId)"!]_ACTIVATION_TIME       [!"num:i(node:value(TaskActivationTime) div $Period)"!] [!//
[!ENDCODE!]
    [!ENDIF!]
[!ENDLOOP!]

[!CR!]
[!CR!]

[!VAR "Array" = "concat('INTAPP_TASK_1,','INTAPP_TASK_2,','INTAPP_TASK_3,','INTAPP_TASK_4,','INTAPP_TASK_5,','INTAPP_TASK_6,','INTAPP_TASK_7,','INTAPP_PREHOOK_TASK,')"!]
[!VAR "ArrayOn" = "''"!]

[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/IntegrationAppTaskList/*"!]
[!CODE!]
#define    [!"node:value(AppTaskId)"!]_ENABLE                STD_ON [!//
[!ENDCODE!]
[!VAR "ArrayOn" = "concat($ArrayOn,node:value(AppTaskId),',')"!]
[!ENDLOOP!]

[!FOR "idx" = "1" TO "num:div(string-length($Array),8)"!]
    [!VAR "ArrEl" = "substring-before($Array, ',')"!]
    [!IF "not(contains($ArrayOn,$ArrEl))"!]
[!CODE!]
#define    [!"$ArrEl"!]_ENABLE                STD_OFF [!//
[!ENDCODE!]
    [!ENDIF!]
    [!VAR "Array" = "substring-after($Array, ',')"!]
[!ENDFOR!]

[!CODE!]
[!"$Array"!]
[!ENDCODE!][!//

[!LOOP "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*/SysDAL/*/IntegrationAppTaskList/*"!]
[!CODE!]
extern void [!"node:value(AppTaskId)"!](void); [!//
[!ENDCODE!]
[!ENDLOOP!]

[!ENDIF!]

[!CODE!]

FUNC (void, SAMPLE_APP_CODE)SysDal_InitBlockZero(void);
FUNC (void, SAMPLE_APP_CODE)SysDal_InitBlockOne(void);
FUNC (void, SAMPLE_APP_CODE) SysDal_SetAllProgrammableInterrupts(void);
#if (SYSDAL_LOW_POWER_MODE == STD_ON)
FUNC (void, SAMPLE_APP_CODE) SysDal_DeinitBlockOne(void);
FUNC (void, SAMPLE_APP_CODE) SysDal_SetWakeupEvents(void);
FUNC (void, SAMPLE_APP_CODE) SysDal_ClearWakeupEvents(void);
#endif

#ifdef __cplusplus
}
#endif

#endif /* SYSDAL_CFG_H */
[!ENDCODE!]
[!ENDNOCODE!]