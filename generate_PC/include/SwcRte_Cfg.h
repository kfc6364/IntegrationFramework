/**
*   @file    SwcRte_Cfg.h
*   @version 0.8.1
*
*   @brief   Integration Framework - Sec Rte glue-layer configuration header file
*   @details This file implements the Rte configuration header.
*
*   @addtogroup IODAL
*   @{
*/
/*===================================================================================================================
*   Platform             : CORTEXM
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*
*   SW Version           : 0.8.1
*   Build Version        : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*
*   All Rights Reserved.
*
*   This file contains sample code only. It is not part of the production code deliverables.
====================================================================================================================*/
/*===================================================================================================================
====================================================================================================================*/
#ifndef SWCRTE_CFG_H
#define SWCRTE_CFG_H

#ifdef __cplusplus
extern "C"{
#endif



[!IF "(IntegrationApp_FeatureList/EnableLightingApp = 'true') or (IntegrationApp_FeatureList/EnableVdrApp = 'true')"!]
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "SwcRte_Types.h"
#include "Compiler.h"
/*===================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
====================================================================================================================*/

#define SWCRTE_CFG_VENDOR_ID                      43

#define SWCRTE_CFG_SW_MAJOR_VERSION               0
#define SWCRTE_CFG_SW_MINOR_VERSION               8
#define SWCRTE_CFG_SW_PATCH_VERSION               1


/*===================================================================================================================
*                                     FILE VERSION CHECKS
====================================================================================================================*/
/* Check if SwcRte_Cfg.h header file and SwcRte_Types.h header file are of the same vendor */
#if (SWCRTE_CFG_VENDOR_ID != SWCRTE_TYPES_VENDOR_ID)
    #error "SwcRte_Cfg.h and SwcRte_Types.h have different vendor ids"
#endif


/* Check if SwcRte_Cfg.h header file and SwcRte_Types.h header file are of the same Software version */
#if ((SWCRTE_CFG_SW_MAJOR_VERSION != SWCRTE_TYPES_SW_MAJOR_VERSION) || \
     (SWCRTE_CFG_SW_MINOR_VERSION != SWCRTE_TYPES_SW_MINOR_VERSION) || \
     (SWCRTE_CFG_SW_PATCH_VERSION != SWCRTE_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte_Types.h and SwcRte_Cfg.h are different"
#endif



/*==================================================================================================
                                       GLOBAL MACROS
==================================================================================================*/
[!NOCODE!]

[!SELECT "IntegrationApp_FeatureList"!]
[!CODE!]

#define SWCRTE_LIGTHING_APP_ENABLED     [!IF "EnableLightingApp = 'true'"!] (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!] [!CR!]
#define SWCRTE_MOTORCTRL_APP_ENABLED    [!IF "EnableMotorControlApp = 'true'"!] (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]  [!CR!]
#define SWCRTE_VDR_APP_ENABLED          [!IF "EnableVdrApp = 'true'"!] (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]  [!CR!]
#define SWCRTE_USE_RTE_BUFFERS          [!IF "EnableRteBuffers = 'true'"!] (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]  [!CR!]
#define SWCRTE_SINGLE_TASK_APPLICATION  [!IF "EnableSingleTaskAppRunnable = 'true'"!] (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]  [!CR!]
#define SWCRTE_ENABLE_POWER_MODE        [!IF "EnablePowerManagement = 'true'"!] (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]  [!CR!]
[!ENDCODE!]
[!ENDSELECT!]

[!SELECT "IntegrationAppGeneral"!]
[!CODE!]
#define SWCRTE_RTM_ENABLE               [!IF "UseRTM   = 'true'"!] (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]  [!CR!]
[!ENDCODE!]
[!ENDSELECT!]

[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/AppConfig/*"!]

[!VAR "MaxLightingCh" = "num:i(0)"!]
[!LOOP "LightingControlApp/*"!] 
   [!VAR "LightingChannelscount" = "num:i(count(LightingChannels/*))"!]

   [!IF "$MaxLightingCh < $LightingChannelscount"!]   
       [!VAR "MaxLightingCh" = "$LightingChannelscount"!]
   [!ENDIF!]

[!ENDLOOP!]

[!CODE!]
#define SWCRTE_MAX_LIGHTING_CHANNELS        [!"(num:i($MaxLightingCh))"!]U
#define SWCRTE_MAX_LIGHTING_INSTANCES       [!"(num:i(count(LightingControlApp/*)))"!]U 

#define SWCRTE_MAX_MOTORCTRL_INSTANCES      [!"(num:i(count(MotorControlApp/*)))"!]U 
#define SWCRTE_MOTORCTRL_INSTANCE_OFFSET    [!"(num:i(count(LightingControlApp/*)))"!]U
#define SWCRTE_MOTORCTRL_FBK_LINES          0U

#define SWCRTE_MAX_VDR_INSTANCES            [!IF "(num:i(count(VirtualDataRouterApp/*))) > num:i(0) "!]1U [!ELSE!]0U [!ENDIF!]
#define SWCRTE_VDR_INSTANCE_OFFSET          [!"(num:i(count(MotorControlApp/*) + count(LightingControlApp/*)))"!]U

#define SWCRTE_MAX_APP_INSTANCES            (SWCRTE_MAX_LIGHTING_INSTANCES + SWCRTE_MAX_MOTORCTRL_INSTANCES + SWCRTE_MAX_VDR_INSTANCES)    

#define SWCRTE_MAX_APP_CTRL_INSTANCES       [!"(num:i(count(MotorControlApp/*) + count(LightingControlApp/*)))"!]U

#define SWCVDR_INSTANCE_ID         [!"(num:i(count(MotorControlApp/*) + count(LightingControlApp/*)))"!]U
[!ENDCODE!]        
[!ENDSELECT!]


[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/AppConfig/*"!]
[!VAR "RxDataLenMax" = "num:i(0)"!]
[!VAR "TxDataLenMax" = "num:i(0)"!]
[!VAR "Vdr_TxMsgCount" = "num:i(0)"!]
[!VAR "Vdr_RxMsgCount" = "num:i(0)"!]

[!LOOP "VirtualDataRouterApp/*"!]
    [!IF "VdrMessageType = 'RX_MESSAGE'"!]
        [!VAR "Vdr_RxMsgCount" = "$Vdr_RxMsgCount + 1"!]
    [!ELSE!]    
        [!VAR "Vdr_TxMsgCount" = "$Vdr_TxMsgCount + 1"!]
    [!ENDIF!]  
[!ENDLOOP!]

[!VAR "Vdr_RxMsgIndex" = "num:i(0)"!]
[!VAR "Vdr_TxMsgIndex" = "num:i(0)"!]    

[!LOOP "VirtualDataRouterApp/*"!]    
    [!VAR "MsgId" = "num:i(node:value(VdrMessageId))"!]
    [!VAR "MsgContainerName" = "node:name(.)"!]
    [!IF "VdrMessageType = 'RX_MESSAGE'"!]
        [!IF "num:i($RxDataLenMax) < num:i(node:value(DefaultDataLength))"!]
            [!VAR "RxDataLenMax" = "num:i(node:value(DefaultDataLength))"!]
        [!ENDIF!]     

        [!LOOP "../../VirtualDataRouterApp/*"!]  
            [!VAR "AltRxMsgId" = "node:value(VdrMessageId)"!]    

            [!IF "(num:i($AltRxMsgId) = $MsgId) and ($MsgContainerName != node:name(.)) and (VdrMessageType = 'RX_MESSAGE')"!]            
[!CODE!][!ERROR!]Rx Message Id [!"VdrMessageId"!] in [!"node:name(.)"!] is was already configured for container [!"$MsgContainerName"!]   [!ENDERROR!] 
[!ENDCODE!]      
            [!ENDIF!]
        [!ENDLOOP!]

        [!VAR "Vdr_RxMsgIndex" = "$Vdr_RxMsgIndex + 1"!]
    [!ELSE!]  

        [!LOOP "../../VirtualDataRouterApp/*"!]  
            [!VAR "AltTxMsgId" = "node:value(VdrMessageId)"!]    

            [!IF "(num:i($AltTxMsgId) = $MsgId) and ($MsgContainerName != node:name(.)) and (VdrMessageType != 'RX_MESSAGE')"!]           
[!CODE!][!ERROR!]Tx Message Id [!"VdrMessageId"!] in [!"node:name(.)"!] is was already configured for container [!"$MsgContainerName"!]   [!ENDERROR!] 
[!ENDCODE!]       
            [!ENDIF!]
        [!ENDLOOP!]     
         
        [!VAR "Vdr_TxMsgIndex" = "$Vdr_TxMsgIndex + 1"!]
    [!ENDIF!]      [!// VdrSignalDirection!= 'RX_REPLY'   

[!ENDLOOP!]      
[!ENDSELECT!]

[!CODE!]

#define  SWCRTE_MAX_TX_MESSAGE_IDS           [!"num:i($Vdr_TxMsgCount)"!]U
#define  SWCRTE_MAX_RX_DATA_LEN              [!"num:i($RxDataLenMax)"!]U

[!ENDCODE!]

[!CODE!]
#define SWCLIGHTING_MAXIMUM_ANALOG_FDBK_VALUE   3000U 
#define SWCLIGHTING_MINIMUM_ANALOG_FDBK_VALUE   500U

[!ENDCODE!]

[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/AppConfig/*"!]

[!VAR "MaxLightingAnalogInCh" = "num:i(0)"!]
[!VAR "MaxLightingDigInCh" = "num:i(0)"!]
[!LOOP "LightingControlApp/*"!] 
   [!IF "LightCtrlUserInterface/LightCtrlInputSignalType = 'ANALOG_INPUT'"!]
       [!VAR "MaxLightingAnalogInCh" = "num:i($MaxLightingAnalogInCh + 1)"!]
   [!ELSEIF "LightCtrlUserInterface/LightCtrlInputSignalType = 'DIGITAL_INPUT'"!]
       [!VAR "MaxLightingDigInCh" = "num:i($MaxLightingDigInCh + 1)"!]
   [!ELSE!]
   [!ENDIF!]

[!ENDLOOP!]
[!ENDSELECT!]
[!CODE!]
#define SWCRTE_MAX_ANSENS_INSTANCES         [!"$MaxLightingAnalogInCh"!]
#define SWCRTE_MAX_DISENS_INSTANCES         [!"$MaxLightingDigInCh"!]
[!ENDCODE!]
[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]
[!CODE!]
#define SWCRTE_ADC_RESOLUTION               12U      

#define SWCRTE_USE_IODAL   [!IF "num:i(count(IoDAL/*))>num:i(0)"!]    (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!] 
#define SWCRTE_USE_SYSDAL  [!IF "num:i(count(SysDAL/*))>num:i(0)"!]   (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]
#define SWCRTE_USE_MEMDAL  [!IF "num:i(count(MEMDAL/*))>num:i(0)"!]   (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]
#define SWCRTE_USE_COMDAL  [!IF "num:i(count(ComDAL/*))>num:i(0)"!]   (SWCRTE_STD_ON)[!ELSE!]  (SWCRTE_STD_OFF)[!ENDIF!]
 
[!ENDCODE!]
[!ENDSELECT!]

[!ENDNOCODE!]        


/*==================================================================================================
                                       GLOBAL RUN-TIME VARIABLE TYPES
==================================================================================================*/
#if SWCRTE_MAX_LIGHTING_INSTANCES > 0
typedef struct 
{
    uint32_t                   u32LightingSensorValue;   /**< @brief Value measured by input sensor */
    boolean_t                  bSensorValueUpdated;      /**< @brief Status of the Sensor*/
} SwcRte_AppLightingSensorChannelType; 


typedef struct 
{
    SwcRte_AppLightingSensorChannelType LightInputSensorData; /**< @brief Values for each FBK Channel*/
    SwcRte_AppLightingSensorChannelType aLightChannelSensorData[SWCRTE_MAX_LIGHTING_CHANNELS]; /**< @brief Values for each FBK Channel*/
} SwcRte_AppLightingSensorValueType; 


typedef struct 
{
    uint32_t aLightingOutputIntesity[SWCRTE_MAX_LIGHTING_CHANNELS]; /**< @brief Values for the output light intesity*/
    SwcRte_ChannelStateType aChannelState[SWCRTE_MAX_LIGHTING_CHANNELS];
} SwcRte_AppLightingActuatorValueType; 



#if SWCRTE_MAX_VDR_INSTANCES > 0
typedef struct
{
    SwcRte_ChannelStateType            Status;
    uint16_t                           FbkVoltage;
    uint32_t                           ActiveCommand;
    boolean_t                          RequestTx;
}SwcRte_AppLightingChanInfoType;

typedef struct 
{    
    SwcRte_AppLightingChanInfoType aLightingChanInfo[SWCRTE_MAX_LIGHTING_CHANNELS];
} SwcRte_AppLightingComInfoType; 


typedef struct
{
    boolean_t bComValueUpdated;
    uint16_t aLightChannelValue[SWCRTE_MAX_LIGHTING_CHANNELS];
} SwcRte_AppLightingComDataType; 
#endif

#endif /*SWCRTE_MAX_LIGHTING_INSTANCES*/


#if SWCRTE_MAX_MOTORCTRL_INSTANCES > 0
typedef struct 
{
    uint8_t  u8NoMotorCtrlFbkChannels;      /**< @brief Mask of Indexes used for Feedback Channels*/
    uint32_t u32MotorCtrlSensorValue;         /**< @brief Value measured by input sensor */   
    uint32_t aMotorCtrlOutputFeedback[SWCRTE_MAX_MOTORCTRL_FBK_LINES]; /**< @brief Values for each FBK Channel*/
} SwcRte_AppMotorCtrlSensorValueType; 


typedef struct 
{
    SwcRte_AppMotorDirectionType   eMotorCtrlOutputDirection; /**< @brief Values for each FBK Channel*/
    uint32_t                u32MotorCtrlOutputSpeed;      /**< @brief Expected motor speed*/    
} SwcRte_AppMotorCtrlActuatorValueType; 


#if SWCRTE_MAX_VDR_INSTANCES > 0

typedef struct 
{    
    uint16_t                         FbkVoltage;
}
SwcRte_AppMotorCtrlComInfoType; 

typedef SwcRte_AppMotorCtrlActuatorValueType SwcRte_AppMotorCtrlComDataType; 
#endif
#endif /*SWCRTE_MAX_MOTORCTRL_INSTANCES*/



/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
extern const SwcRte_GlobalConfigType SwcRte_AppInstanceMapPB[SWCRTE_MAX_APP_INSTANCES];






[!ENDIF!]
/*================================================================================================*/
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
#endif /*SWCRTE_CFG_H*/