/**
*   @file        SwcRte.h
*   @version     0.8.1
*
*   @brief       Integration Framework - SW component RTE header file
*
*   @details     This file implements SwcRte header file.  
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup SWCRTE
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : CORTEXM
*   SW Version           : 0.8.1
*   Build Version        : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/
#ifndef SWCRTE_H
#define SWCRTE_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "typedefs.h"
#include "SwcRte_Types.h"
#include "SwcRte_Cfg.h"


/*==================================================================================================
                                       SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define SWCRTE_VENDOR_ID                          43

#define SWCRTE_SW_MAJOR_VERSION                   0
#define SWCRTE_SW_MINOR_VERSION                   8
#define SWCRTE_SW_PATCH_VERSION                   1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if SwcRte.h header file and SwcRte_Types.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID != SWCRTE_TYPES_VENDOR_ID)
    #error "SwcRte.h and SwcRte_Types.h have different vendor ids"
#endif


/* Check if SwcRte.h header file and SwcRte_Types.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION != SWCRTE_TYPES_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION != SWCRTE_TYPES_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION != SWCRTE_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.h and SwcRte_Types.h are different"
#endif

/* Check if SwcRte.h header file and  SwcRte_Cfg.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID != SWCRTE_CFG_VENDOR_ID)
    #error "SwcRte.h and SwcRte_Cfg.h have different vendor ids"
#endif


/* Check if SwcRte.h header file and SwcRte_Cfg.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION != SWCRTE_CFG_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION != SWCRTE_CFG_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION != SWCRTE_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.h and SwcRte_Cfg.h are different"
#endif



/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/



/*================================================================================================*/
void SwcRte_Init( const SwcRte_GlobalConfigType * ConfigPtr);
#if (SWCRTE_SINGLE_TASK_APPLICATION == SWCRTE_STD_ON)	
void SwcRte_MainRunnable(void);
#endif
/*==================================================================================================
                                 GOBAL FUNCTIONS FOR LIGHTING APP
==================================================================================================*/

#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
	
#if (SWCRTE_VDR_APP_ENABLED  == SWCRTE_STD_ON)
void SwcRte_ReadLightingComData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingComDataType * Value);

void SwcRte_WriteLightingComData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingComDataType * Value);

void SwcRte_FetchLightingComInfo(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppMessageIdType  AppMessageId, SwcRte_AppLightingComInfoType * InputValue);

void SwcRte_WriteLightingComInfo(SwcRte_AppInstanceIdType LightingInstance,  SwcRte_AppLightingComInfoType * Value);

boolean_t SwcRte_GetLightingComInfoEvent(SwcRte_AppInstanceIdType LightingInstance);

void SwcRte_SetLightingComInfoEvent(SwcRte_AppInstanceIdType LightingInstance, boolean_t RequestTx);
#endif

void SwcRte_ReadLightingSensorData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingSensorValueType *OutputValue) ;

void SwcRte_WriteLightingSensorData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingSensorValueType *InputValue) ;

void SwcRte_ReadLightingOutputRequest(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingActuatorValueType * OutputValue);

void SwcRte_WriteLightingOutputRequest(SwcRte_AppInstanceIdType LightingInstance,  SwcRte_AppLightingActuatorValueType * OututValue); 
#endif
/*==================================================================================================
                                 GOBAL FUNCTIONS FOR MOTOR CONTROL APP
==================================================================================================*/
#if (SWCRTE_MOTORCTRL_APP_ENABLED ==SWCRTE_STD_ON)
#if (SWCRTE_VDR_APP_ENABLED  ==SWCRTE_STD_ON)
void SwcRte_ReadMotorCtrlComData(SwcRte_AppInstanceIdType MCInstance, SwcRte_AppMotorCtrlComDataType * Value);

void SwcRte_WriteMotorCtrlComData(SwcRte_AppInstanceIdType MCInstance, SwcRte_AppMotorCtrlComDataType Value);

void SwcRte_ReadMotorCtrlComInfo(SwcRte_AppInstanceIdType MCInstance,  SwcRte_AppMotorCtrlComInfoType * Value);

void SwcRte_WriteMotorCtrlComInfo(SwcRte_AppInstanceIdType MCInstance,  SwcRte_AppMotorCtrlComInfoType OututValue);
#endif

void SwcRte_ReadMotorCtrlSensorData(SwcRte_AppInstanceIdType MCInstance, SwcRte_AppMotorCtrlSensorValueType * Value);

void SwcRte_WriteMotorCtrlSensorData(SwcRte_AppInstanceIdType MCInstance, SwcRte_AppMotorCtrlSensorValueType Value);

void SwcRte_ReadMotorCtrlOutputRequest(SwcRte_AppInstanceIdType MCInstance, SwcRte_AppMotorCtrlActuatorValueType  *OutputValue);

void SwcRte_WriteMotorCtrlOutputRequest(SwcRte_AppInstanceIdType MCInstance,  SwcRte_AppMotorCtrlActuatorValueType * OututValue);
#endif

/*==================================================================================================
                                 GOBAL FUNCTIONS FOR BSW INTERFACE
==================================================================================================*/
#if (SWCRTE_VDR_APP_ENABLED  ==SWCRTE_STD_ON)
SwcRte_AppReturnType SwcRte_ReadComData(SwcRte_AppMessageIdType AppRxMessageId, SwcRte_DataMessageType * DataMessagePtr);

void SwcRte_WriteComData(SwcRte_AppMessageIdType  AppRxMessageId);

#if (SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON)
void SwcRte_SetPowerMode(SwcRte_PowerModeType PowerModeId);
SwcRte_PowerModeType SwcRte_GetCurrentPowerMode(void);
#endif/*SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON*/
void SwcRte_ExecuteSwReset(void);
#endif

void SwcRte_ReadInputs(SwcRte_AppInstanceIdType AppInstance, SwcRte_AppChannelIdType SensorChannel, SwcRte_AppInputValueType * InputValue);

void SwcRte_WriteOutputs(SwcRte_AppInstanceIdType AppInstance, SwcRte_AppChannelIdType ActuatorChannel, SwcRte_OutputValueType OutputValue);

/*================================================================================================*/
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
#endif /*SWCRTE_H*/
/** @} */
