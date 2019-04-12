/*==================================================================================================
*   @file    sys_init.h
*   @version 0.8.1
*
*   @brief   AUTOSAR IntegrationFramework - MCAL auxiliary APIs used for MCAL testing
*   @details MCAL auxiliary APIs used for MCAL testing
*            This file contains sample code only. It is not part of the production code deliverables
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

#ifndef SYS_INIT_H
#define SYS_INIT_H

#ifdef __cplusplus
extern "C"
{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "typedefs.h"
#include "Std_Types.h"
/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/

#define CODE_CACHE  0
#define SYS_CACHE   1
#define TAG_SEL         1
#define WAY0_SEL        0
#define WAY1_SEL        1

#define CACHE_OK               0
#define CACHE_INVALID_PARAM    1

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/


/*==================================================================================================
*                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                     FUNCTION PROTOTYPES
==================================================================================================*/

    uint8_t m4_cache_init(uint8_t cache);
    uint8_t m4_cache_disable(uint8_t cache);
    uint8_t m4_cache_invalidate(uint8_t cache);
    uint8_t m4_cache_flush(uint8_t cache);
    uint8_t m4_cache_invalidate_buffer(uint32_t start_addr, long size);
    uint8_t m4_cache_flush_buffer(uint32_t start_addr, long size);


/** 
* @brief Scatter_Loading
* @details function used to initialize RAM variables and RAM functions 
*/
#ifdef __ICCARM__ 
    void Scatter_Loading(void);
#endif    
void SystemInit(void);
    
/** 
* @brief sys_disableIsrSource
* @details function used to disable the interrupt number id
*/
void sys_disableIsrSource(uint8 id);  
/** 
* @brief sys_init
* @details function used to enable the interrupt number id and set up the priority
*/
void sys_enableIsrSource(uint8 id, uint8 prio);
/** 
* @brief sys_init
* @details function used to register the interrupt handler in the interrupt vectors
*/
void sys_registerIsrHandler(uint8_t irq_id, uint32 isr_handler);
/** 
* @brief sys_init
* @details function used to enable all interrupts
*/
void sys_enableAllInterrupts(void);
/** 
* @brief sys_init
* @details function used to disable all interrupts
*/
void sys_disableAllInterrupts(void);

/** 
* @brief sys_init
* @details function used to initiatialize clocks, system clock is system Pll 120 MHz
*/
extern Std_ReturnType sys_init(void);

/** 
* @brief sys_halt
* @details function used to enter halt mode
*/
extern void sys_halt(void);

/** 
* @brief sys_stop
* @details function used to enter stop mode
*/
extern void sys_stop(void);

#ifdef __cplusplus
}
#endif

#endif /*SYS_INIT_H*/
