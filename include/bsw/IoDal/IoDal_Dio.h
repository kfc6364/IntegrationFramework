/**
*   @file       IoDal_Dio.h
*   @version    0.8.1
*
*   @brief      AUTOSAR - Integration Framework - IO Driver Abstraction Layer component for digital
*               input/output channels
*   @details    This file implements the IODAL interface to application layer to lower layers                  
*               DIO, ICU, OCU
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

#ifndef IODAL_DIO_H
#define IODAL_DIO_H

#ifdef __cplusplus
extern "C"{
#endif

/*===============================================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
================================================================================================================================*/


/*===============================================================================================================================
                                       SOURCE FILE VERSION INFORMATION
================================================================================================================================*/
#define IODAL_DIO_VENDOR_ID                       43

#define IODAL_DIO_AR_RELEASE_MAJOR_VERSION        4
#define IODAL_DIO_AR_RELEASE_MINOR_VERSION        3
#define IODAL_DIO_AR_RELEASE_REVISION_VERSION     1

#define IODAL_DIO_SW_MAJOR_VERSION                0
#define IODAL_DIO_SW_MINOR_VERSION                8
#define IODAL_DIO_SW_PATCH_VERSION                1

/*================================================================================================================================
                                       GLOBAL FUNCTIONS
=================================================================================================================================*/
#if IODAL_MAX_DIO_DESCRIPTORS > 0U
FUNC(void, IODAL_APP_CODE) IoDal_Dio_Init(P2CONST(IoDal_BswIoConfigType, AUTOMATIC, IODAL_APP_CONST) ConfigPtr);
FUNC(void, IODAL_APP_CODE) IoDal_Dio_DeInit(void);
FUNC(Std_ReturnType, IODAL_APP_CODE) IoDal_Dio_ReadInputs(IoDal_BswChannelIdType BswIoChannel, IoDal_BswValueType  * InputValue);
#if (IODAL_DIO_EXT_DEV == STD_ON)
FUNC(void, IODAL_APP_CODE) IoDal_Dio_ExtDevHandler(IoDal_BswChannelIdType BswIoChannel);
#endif
FUNC(void, IODAL_APP_CODE) IoDal_Dio_WriteOutputs(IoDal_BswChannelIdType BswIoChannel, IoDal_BswValueType  OutputValue);
#endif
/*===============================================================================================================================*/

#ifdef __cplusplus
}
#endif

#endif /*IODAL_DIO_H*/
/** @} */
