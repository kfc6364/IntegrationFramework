/**
*    @file        SwcVdr.h
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
*   @addtogroup SWCVDR
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
#ifndef SWCVDR_H
#define SWCVDR_H

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
/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
                                       SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define SWCVDR_VENDOR_ID                          43

#define SWCVDR_SW_MAJOR_VERSION                   0
#define SWCVDR_SW_MINOR_VERSION                   8
#define SWCVDR_SW_PATCH_VERSION                   1
/*==================================================================================================
*                                     FILE VERSION CHECKS
===================================================================================================*/
/* Check if header file and SWCRTE TYPES header file are of the same vendor */
#if (SWCVDR_VENDOR_ID != SWCRTE_TYPES_VENDOR_ID)
    #error "SwcVdr.h and SwcRte.h have different vendor ids"
#endif


/* Check if header file and SWCRTE TYPES header file are of the same Software version */
#if ((SWCVDR_SW_MAJOR_VERSION != SWCRTE_TYPES_SW_MAJOR_VERSION) || \
     (SWCVDR_SW_MINOR_VERSION != SWCRTE_TYPES_SW_MINOR_VERSION) || \
     (SWCVDR_SW_PATCH_VERSION != SWCRTE_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcVdr.h and SwcRte_Types.h are different"
#endif



/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
extern void SwcVdr_Init(const SwcRte_GlobalConfigType * ConfigPtr);
extern void SwcVdr_MainRunnable(void);
extern void SwcVdr_ClearDataMessageBuffer(SwcRte_AppMessageIdType  AppTxMessageId);

/*================================================================================================*/

#ifdef __cplusplus
}
#endif
#endif /*SWCVDR_H*/
/** @} */