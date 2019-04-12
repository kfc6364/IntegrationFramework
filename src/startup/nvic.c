/**
*   @file    nvic.c
*   @version 0.8.1
*
*   @brief   AUTOSAR IntegrationFramework - nvic driver
*   @details Functions that manage interrupts and exceptions via the NVIC (adapted from CMSIS_core)

*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup BUILD_ENV
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : CORTEXM
*   Peripheral           : Pit
*   Dependencies         : none
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
#include "typedefs.h"
#include "StdRegMacros.h"
#include "Std_Types.h"
#include "nvic.h"
#include "Mcal.h"
#include "S32K2TV.h"



/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/


/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/** 
* @brief Set Priority Grouping
* @details The function sets the priority grouping field using the required unlock sequence.
*  The parameter PriorityGroup is assigned to the field SCB->AIRCR [10:8] PRIGROUP field.
*   Only values from 0..7 are used.
*   In case of a conflict between priority grouping and available
*   priority bits (__NVIC_PRIO_BITS), the smallest possible priority group is set
*/
/*================================================================================================*/
void NVIC_SetPriorityGrouping(uint32 PriorityGroup)
{
    /* Set the PRIGROUP[10:8] bits according to NVIC_PriorityGroup value */
    S32_SCB->AIRCR = (S32_SCB->AIRCR & (~S32_SCB_AIRCR_PRIGROUP_MASK)) | PriorityGroup;
}
 
/*================================================================================================*/
/** 
* @brief Enable External Interrupt
* @details The function enables a device-specific interrupt in the NVIC interrupt controller.
*/
/*================================================================================================*/ 
void NVIC_EnableIRQ(uint8 IRQn)
 {
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
	Mcal_goToSupervisor();
#endif
    REG_BIT_SET32((NVIC_BASEADDR + NVIC_ISER_OFFSET(IRQn)), 1 << (IRQn % 32) ); /* enable interrupt */
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
	Mcal_goToUser();
#endif
 }
 
/*================================================================================================*/
/** 
* @brief Disable External Interrupt
* @details The function disables a device-specific interrupt in the NVIC interrupt controller
*/
/*================================================================================================*/  
void NVIC_DisableIRQ(uint8 IRQn)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
	Mcal_goToSupervisor();
#endif
	REG_WRITE32((NVIC_BASEADDR + NVIC_ICER_OFFSET(IRQn)), 1 << (IRQn % 32) );
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
	Mcal_goToUser();
#endif

}
 
 
/*================================================================================================*/
/** 
* @brief Set Interrupt Priority
* @details The function sets the priority of an interrupt.
*/
/*================================================================================================*/  
void NVIC_SetPriority(uint8 IRQn, uint8 priority)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
	Mcal_goToSupervisor();
#endif
	REG_RMW32((NVIC_BASEADDR + NVIC_IPRO_OFFSET(IRQn)), NVIC_IPRO_MASK(IRQn), priority <<  ((IRQn % 4)*8) );
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
	Mcal_goToUser();
#endif

}
 
 
 
