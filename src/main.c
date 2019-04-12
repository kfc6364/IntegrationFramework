/**
*    @file        main.c
*    @version     0.8.1
*
*    @brief       Integration Framework -  main function
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

#include "SysDal.h"
#if defined(AUTOSAR_OS_NOT_USED)
#include "SysDal_IntSch.h"
#endif
#include "Mcal.h"

#include "modules.h"


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/**
@brief This is the global variable that holds all the sample app specific data
*/
/*
extern volatile SampleAppData_T  stSampleAppData;
static SampleAppData_T * p_stSampleAppData = (SampleAppData_T *)&stSampleAppData;
*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
@brief   Main function of the sample application using Leds.
@details The sample configures the processor and uses leds and keys from the mainboard the following way:
                LED1 - Light intensity controlled by Potentiometer
                LED2 - Will stay ON while Key1 is pressed and will go OFF when watchdog will run out
                LED3 - Blinking driven by GPT
                LED4 - Always ON
                KEY1 - disable watchdog and switch on the LED2
          The function will never return.
@return Returns ok
@retval 0 - Ok
@pre None
@post None
*/
int main( )
{
#if defined(AUTOSAR_OS_NOT_USED)
#endif  /* AUTOSAR_OS_NOT_USED */
    /* OS/stand-alone initialization - prepare the tasks(for OS), or the threads when no OS is used(uses Timers) */
    
#ifdef D_CACHE_ENABLE  
    /*init Data caches*/
    m4_cache_init(SYS_CACHE);
#endif

#ifdef I_CACHE_ENABLE
    /*init Code caches*/
    m4_cache_init(CODE_CACHE);
#endif
    SysDal_Init();
#if defined(AUTOSAR_OS_NOT_USED)
    SysDal_IntSch_TaskScheduler();
#endif
    return 0;
}

#ifdef __cplusplus
}
#endif
