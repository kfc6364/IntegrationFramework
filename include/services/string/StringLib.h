/**
*   @file           StringLib.h
*   @version        0.8.1
*
*   @brief          AUTOSAR IntegrationFramework - String Operations Library interface header.
*   @details        String Library Operations interface header.
*
*This file contains sample code only. It is not part of the production code deliverables.
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : CORTEXM
*   Peripheral           : Pit
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   Autosar Conf.Variant :
*   SW Version           : 0.8.1
*   Build Version        : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

#ifndef STRINGLIB_H
#define STRINGLIB_H

#ifdef __cplusplus
extern "C"{
#endif

#include "typedefs.h"
/*===============================================================================================
                                     FUNCTION PROTOTYPES
===============================================================================================*/
uint8_t  StrLib_Ctoi(char DataChar);
uint32_t StrLib_StringLen(char * DataStr);
void StrLib_ReverseString(char * DataStr, uint32_t length);
int StrLib_Itoa(uint32_t num, char * DataStr, uint8_t base);
uint32_t StrLib_Atoi(char * DataChar);
void StrLib_StrCpy(char* InputStr, char * OututStr, uint8_t StrLen);
void StrLib_InsertCharToStr(char * InputStr, char DataChar, uint8_t CharPosition, uint8_t StrLen);
uint8_t StrLib_StrCmp(char * DataStr1, char * DataStr2);
void StrLib_StrCat(char *DestStr, const char *SrcStr);
uint8_t StrLib_GetCharIndex(char * DataString, char DataChar);
/*================================================================================================*/
#ifdef __cplusplus
}
#endif

#endif  /* STRINGLIB_H*/