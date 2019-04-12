/**
*    @file        SwcLighting.h
*    @version     0.8.1
*
*    @brief       Integration Framework - Lighting SW component.
*
*    @details     Implementation of the header file for the lighting application.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup SWCLIGHTING
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
#ifndef SWCLIGHTING_H
#define SWCLIGHTING_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "SwcRte_Types.h"
#include "SwcRte_Cfg.h"
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define SWCLIGHTING_VENDOR_ID                          43

#define SWCLIGHTING_SW_MAJOR_VERSION                   0
#define SWCLIGHTING_SW_MINOR_VERSION                   8
#define SWCLIGHTING_SW_PATCH_VERSION                   1
/*==================================================================================================
*                                     FILE VERSION CHECKS
===================================================================================================*/
/* Check if header file and SWCRTE TYPES header file are of the same vendor */

#if (SWCLIGHTING_VENDOR_ID != SWCRTE_TYPES_VENDOR_ID)
    #error "SwcLighting.h and SwcRte_Types.h have different vendor ids"
#endif


/* Check if header file and SWCRTE TYPES header file are of the same Software version */
#if ((SWCLIGHTING_SW_MAJOR_VERSION != SWCRTE_TYPES_SW_MAJOR_VERSION) || \
     (SWCLIGHTING_SW_MINOR_VERSION != SWCRTE_TYPES_SW_MINOR_VERSION) || \
     (SWCLIGHTING_SW_PATCH_VERSION != SWCRTE_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcLighting.h and SwcRte_Types.h are different"
#endif

#if (SWCLIGHTING_VENDOR_ID != SWCRTE_CFG_VENDOR_ID)
    #error "SwcLighting.h and SwcRte_Cfg.h have different vendor ids"
#endif


/* Check if header file and SWCRTE TYPES header file are of the same Software version */
#if ((SWCLIGHTING_SW_MAJOR_VERSION != SWCRTE_CFG_SW_MAJOR_VERSION) || \
     (SWCLIGHTING_SW_MINOR_VERSION != SWCRTE_CFG_SW_MINOR_VERSION) || \
     (SWCLIGHTING_SW_PATCH_VERSION != SWCRTE_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcLighting.h and SwcRte_Cfg.h are different"
#endif

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
extern void  SwcLighting_Init(const SwcRte_GlobalConfigType * ConfigPtr);
extern void  SwcLighting_WriteSensorData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingSensorValueType  * InputValue);
extern void  SwcLighting_ReadSensorData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingSensorValueType  * OutputValue); 
extern void  SwcLighting_ReadOutputRequest(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingActuatorValueType * OutputValue);
extern void  SwcLighting_WriteOutputRequest(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingActuatorValueType * InputValue);
extern void  SwcLighting_MainRunnable(SwcRte_AppInstanceIdType LightingInstance);
#if (SWCRTE_VDR_APP_ENABLED  == SWCRTE_STD_ON)   
void SwcLighting_WriteComData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingComDataType  * InputValue);    
void SwcLighting_FetchComInfo(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingComInfoType  * InputValue); 
extern boolean_t SwcLighting_GetComInfoEvent(SwcRte_AppInstanceIdType RteAppInstance);
extern void SwcLighting_SetComInfoEvent(SwcRte_AppInstanceIdType LightingInstance, boolean_t RequestTx);
#endif
/*================================================================================================*/

#ifdef __cplusplus
}
#endif
#endif /*SWCLIGHTING_H*/
/** @} */