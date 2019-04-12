/**
*   @file    IoDal_Ani.h
*   @version 0.8.1
*
*   @brief   AUTOSAR - Integration Framework - IO Driver Abstraction Layer component for analog
*            input channels
*   @details This file implements the IODAL interface to application layer to lower layers                  
*            ADC, OCU
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup IODAL
*   @{
*/
/*=========================================================================================================================
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
#ifndef IODAL_ANI_H
#define IODAL_ANI_H

#ifdef __cplusplus
extern "C"{
#endif


/*==============================================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
================================================================================================================================*/

/*===============================================================================================================================
                                       SOURCE FILE VERSION INFORMATION
================================================================================================================================*/
#define IODAL_ANI_VENDOR_ID                       43

#define IODAL_ANI_AR_RELEASE_MAJOR_VERSION        4
#define IODAL_ANI_AR_RELEASE_MINOR_VERSION        3
#define IODAL_ANI_AR_RELEASE_REVISION_VERSION     1

#define IODAL_ANI_SW_MAJOR_VERSION                0
#define IODAL_ANI_SW_MINOR_VERSION                8
#define IODAL_ANI_SW_PATCH_VERSION                1

/*==============================================================================================================
                                                   GLOBAL FUNCTIONS
==============================================================================================================*/
#if IODAL_MAX_ANI_DESCRIPTORS > 0U
FUNC(void, IODAL_APP_CODE) IoDal_Ani_Init(P2CONST(IoDal_BswIoConfigType, AUTOMATIC, IODAL_APP_CONST) ConfigPtr);
FUNC(void, IODAL_APP_CODE) IoDal_Ani_DeInit(void);
FUNC(void, IODAL_APP_CODE) IoDal_Ani_AdcHwTriggerHandler(void);
FUNC(Std_ReturnType, IODAL_APP_CODE) IoDal_Ani_ReadInputs(IoDal_BswChannelIdType BswIoChannel, IoDal_BswValueType  * InputValue);
extern FUNC (void, IODAL_APP_CODE) IoDal_Ani_AdcSwTriggerTable(void);
#endif
/*=============================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /*IODAL_ANI_H*/
/** @} */