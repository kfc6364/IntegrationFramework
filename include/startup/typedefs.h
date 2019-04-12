/**
*    @file        typedefs.h
*    @version     0.8.1
*
*    @brief       Integration Framework - global type definition header
*     
*    (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*    All Rights Reserved.
*
*    This file contains sample code only. It is not part of the production code deliverables.
*/       
/*=================================================================================================
*    Platform      :      CORTEXM
*    Build Version :      S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
*
==================================================================================================*/
/*==================================================================================================
====================================================================================================*/

#ifndef _TYPEDEFS_H_
#define _TYPEDEFS_H_

    #define SWCRTE_STD_ON   1U
	#define SWCRTE_STD_OFF  0U
    #define SWCRTE_TRUE   1U
	#define SWCRTE_FALSE  0U

	
    typedef unsigned char boolean_t;
    typedef unsigned char uint8_t;
    typedef unsigned short uint16_t;
    typedef unsigned int uint32_t;
    typedef unsigned long long uint64_t;
    
    typedef signed char         int8_t;
    typedef signed short        int16_t;
    typedef signed int         int32_t;
    typedef signed long long    int64_t;

    /* Standard typedefs used by header files, based on ISO C standard */
    typedef volatile int8_t vint8_t;
    typedef volatile uint8_t vuint8_t;

    typedef volatile int16_t vint16_t;
    typedef volatile uint16_t vuint16_t;

    typedef volatile int32_t vint32_t;
    typedef volatile uint32_t vuint32_t;
    
    typedef volatile int64_t vint64_t;
    typedef volatile uint64_t vuint64_t;

#endif





