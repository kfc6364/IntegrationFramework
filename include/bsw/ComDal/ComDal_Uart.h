/**
*   @file           ComDal.h
*   @version        0.8.1
*
*   @brief          Integration Framework - ComDal high level interface implementation.
*   @details        ComDal high level interface implementation.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup COMDAL
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

#ifndef COMDAL_UART_H
#define COMDAL_UART_H

#ifdef __cplusplus
extern "C"{
#endif
/*===================================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
====================================================================================================================*/

/*===================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
====================================================================================================================*/
/**
* @file          ComDal_Uart.h
*/
#define COMDAL_UART_VENDOR_ID                           43
#define COMDAL_UART_MODULE_ID                           100

#define COMDAL_UART_AR_RELEASE_MAJOR_VERSION            4
#define COMDAL_UART_AR_RELEASE_MINOR_VERSION            3
#define COMDAL_UART_AR_RELEASE_REVISION_VERSION         1

#define COMDAL_UART_SW_MAJOR_VERSION                    0
#define COMDAL_UART_SW_MINOR_VERSION                    8
#define COMDAL_UART_SW_PATCH_VERSION                    1
/*===================================================================================================================
*                                       FILE VERSION CHECKS
====================================================================================================================*/
#if COMDAL_MAX_UART_DESCRIPTORS > 0U

FUNC(void, COMDAL_APP_CODE) ComDal_Uart_Init(P2CONST(ComDal_ConfigType, AUTOMATIC, COMDAL_APPL_CONST) ConfigPtr);
FUNC(void, COMDAL_APP_CODE) ComDal_Uart_DeInit(void);
FUNC(void, COMDAL_APP_CODE) ComDal_Uart_WriteData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) TxDataString, VAR(uint8, AUTOMATIC) UartDataLen);
FUNC(ComDal_ReturnType, COMDAL_APP_CODE) ComDal_Uart_ReadData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) ReadBuffer, VAR(uint8, AUTOMATIC) UartDataLen);

#endif

#ifdef __cplusplus
}
#endif

#endif /*COMDAL_UART_H*/
/** @} */

