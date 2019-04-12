/*=================================================================================================*/
/**
*   @file    Startup.c
*   @version 0.8.1
*
*   @brief   AUTOSAR IntegrationFramework - Startup file for ARM.
*   @details Startup file for ARM.
*            This file contains sample code only. It is not part of the production code deliverables
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
.globl VTABLE
.globl RESET_CATCH_CORE

.section ".startup","ax"
.thumb
/************************************************************************/
/* Autosar synopsis of startup code (See MCU Specification):            */
/*                                                                      */
/*   Before the MCU driver can be initialized, a basic initialization   */
/*   of the MCU has to be executed. This MCU specific initialization is */
/*   typically executed in a start-up code. The start-up code of the    */
/*   MCU shall be executed after power up and any kind of micro-        */
/*   controller reset. It shall perform very basic and microcontroller  */
/*   specific start-up initialization and shall be kept short, because  */
/*   the MCU clock and PLL is not yet initialized. The start-up code    */
/*   shall cover MCU specific initialization, which is not part of      */
/*   other MCU services or other MCAL drivers. The following steps      */
/*   summarizes basic functionality which shall be included in the      */
/*   start-up code. They are listed for guidance, because some          */
/*   functionality might not be supported. No code will be found in     */
/*   case.                                                              */
/************************************************************************/
.set VTOR_REG, 0xE000ED08
.align 2

.globl Reset_Handler 
Reset_Handler:
.globl _start
_start:
/*****************************************************/
/* Skip normal entry point as nothing is initialized */
/*****************************************************/
 mov   r0, #0
 mov   r1, #0
 mov   r2, #0
 mov   r3, #0
 mov   r4, #0
 mov   r5, #0
 mov   r6, #0
 mov   r7, #0

/*********************************/
/* Set a loop which is supposed to catch the core if the debugger is attached. */ 
/* If debugger is not attached, default RAM value is supposed to exit from this loop. */
/*********************************/ 
DebugerHeldCoreLoop: 
 ldr  r0, =RESET_CATCH_CORE 
 ldr  r0, [r0]
 ldr  r1, =0x5A5A5A5A
 cmp  r0, r1
 beq	DebugerHeldCoreLoop
 
/*******************************************************************/
/* Freescale Guidance 1 - Init registers to avoid lock-step issues */
/* N/A                                                             */
/*******************************************************************/

/*******************************************************************/
/* Freescale Guidance 2 - MMU Initialization for CPU               */
/*  TLB0 - PbridgeB                                                */
/*  TLB1 - Internal Flash                                          */
/*  TLB2 - External SRAM                                           */
/*  TLB3 - Internal SRAM                                           */
/*  TLB4 - PbridgeA                                                */ 
/*******************************************************************/
    
/******************************************************************/
/* Autosar Guidance 1 - The start-up code shall initialize the    */
/* base addresses for interrupt and trap vector tables. These base*/
/* addresses are provided as configuration parameters or          */
/* linker/locator setting.                                        */
/******************************************************************/

/* relocate vector table to RAM */
ldr  r0, =VTOR_REG
ldr  r1, =VTABLE
/* ;ldr  r2, =(1 << 29) */
/*;orr  r1, r2 *//* r1 = r1 | r2 */
str  r1,[r0]

/******************************************************************/
/* Autosar Guidance 2 - The start-up code shall initialize the    */
/* interrupt stack pointer, if an interrupt stack is              */
/* supported by the MCU. The interrupt stack pointer base address */
/* and the stack size are provided as configuration parameter or  */
/* linker/locator setting.                                        */
/*                                                                */
/******************************************************************/


/******************************************************************/
/* Autosar Guidance 3 - The start-up code shall initialize the    */
/* user stack pointer. The user stack pointer base address and    */
/* the stack size are provided as configuration parameter or      */
/* linker/locator setting.                                        */
/******************************************************************/

/* set up stack; r13 SP*/
ldr  r0, =_Stack_start
msr MSP, r0

/******************************************************************/
/* Autosar Guidance 4 - If the MCU supports context save          */
/* operation, the start-up code shall initialize the memory which */
/* is used for context save operation. The maximum amount of      */
/* consecutive context save operations is provided as             */
/* configuration parameter or linker/locator setting.             */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 5 - The start-up code shall ensure that the   */
/* MCU internal watchdog shall not be serviced until the watchdog */
/* is initialized from the MCAL watchdog driver. This can be      */
/* done for example by increasing the watchdog service time.      */
/*                                                                */
/******************************************************************/


/* disable WDG */
/* The watchdog has a restrictive timing. It has to be configured and unlocked within a peripod
  of 128 cycles. Therefor the unlock sequence need to be done by a small target program. */

/*;ldr  r0, =0x40052004*/
/*;ldr  r1, =0xD928C520*/
/*;ldr  r2, =0x40052008*/
/*;ldr  r3, =0x0000FFFF*/
/*;ldr  r4, =0x40052000*/
/*;ldr  r5, =0x00002120*/
/*;                    */ 
/*;str  r1, [r0] */  /* SD:0x40052004 = 0xD928C520   Unlock */
/*;str  r3, [r2] */  /* SD:0x40052008 = 0xD928       maximum timeout value*/
/*;str  r5, [r4] */  /* SD:0x40052000 = 0x2120       disable Wdg */





/******************************************************************/
/* Autosar Guidance 6 - If the MCU supports cache memory for data */
/* and/or code, it shall be initialized and enabled in the        */
/* start-up code.                                                 */
/*                                                                */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 7 - The start-up code shall initialize MCU    */
/* specific features of internal memory like memory protection.   */
/*                                                                */
/******************************************************************/
 
/******************************************************************/
/* Autosar Guidance 8 - If external memory is used, the memory    */
/* shall be initialized in the start-up code. The start-up code   */
/* shall be prepared to support different memory configurations   */
/* depending on code location. Different configuration options    */
/* shall be taken into account for code execution from            */
/* external/internal memory.                                      */
/* N/A - external memory is not used                              */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 9 - The settings of the different memories    */
/* shall be provided to the start-up code as configuration        */
/* parameters.                                                    */
/* N/A - all memories are already configured                      */
/******************************************************************/
 
/******************************************************************/
/* Autosar Guidance 10 - In the start-up code a default           */
/* initialization of the MCU clock system shall be performed      */
/* including global clock prescalers.                             */
/******************************************************************/
bl SystemInit

/******************************************************************/
/* Autosar Guidance 11 - The start-up code shall enable           */
/* protection mechanisms for special function registers(SFR�s),   */
/* if supported by the MCU.                                       */
/* N/A - will be handled by Autosar OS                            */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 12 - The start-up code shall initialize all   */
/* necessary write once registers or registers common to several  */
/* drivers where one write, rather than repeated writes, to the   */
/* register is required or highly desirable.                      */
/******************************************************************/

/******************************************************************/
/* Autosar Guidance 13 - The start-up code shall initialize a     */
/* minimum amount of RAM in order to allow proper execution of    */
/* the MCU driver services and the caller of these services.      */
/******************************************************************/
/* MPC574xP - internal ram must be initialized for error correction*/
/******************************************************************/

/************************/
/* Erase ".bss Sections" */
/************************/
  ldr  r2, =BSS_SRAM_START
  ldr  r4, =BSS_SRAM_END

  mov   r3, #0
FillZerobss:
  str   r3, [r2]
  add   r2, r2, #4
  cmp   r2, r4
  bcc   FillZerobss
  
  
#ifndef SINTRAM  /* SINTRAM defined by compiler option -DSINTRAM only for INTRAM build */

  ldr  r2, =INT_SRAM_START
  ldr  r4, =INT_SRAM_END

  mov   r3, #0
FillZeroRam:
  str   r3, [r2]
  add   r2, r2, #4
  cmp   r2, r4
  bcc   FillZeroRam
  
    
/******************************************************************/
/* Copy  initialized data from Flash to SRAM                      */
/******************************************************************/
/*******************/
/* .PPC.EMB.sdata0 */
/*******************/
  
/**********/
/* .sdata */
/**********/
  
/************/
/* .data */
/************/
/* nothing will be copied for linaro linker */
    ldr r3, = RC_DATA_SIZE
    ldr r2, = RC_DATA_SRC
    ldr r4, = RC_DATA_DEST
    
    cmp r3, #0
    beq CopyRamData_LoopDone
    
.globl CopyRamData    
CopyRamData:    
    ldr   r5, [r2]
    str   r5, [r4]
    add   r2, r2, #4
    add   r4, r4, #4
    sub   r3, r3, #1
    cmp   r3, #0
    bgt CopyRamData  
CopyRamData_LoopDone:

/**********************/
/* .data_no_cacheable */
/**********************/
    ldr r3, = RC_DATA_NO_CACHEABLE_SIZE
    ldr r2, = RC_DATA_NO_CACHEABLE_SRC
    ldr r4, = RC_DATA_NO_CACHEABLE_DEST
    
    cmp	r3, #0
    beq	CopyRamDataNoCacheable_LoopDone
    
.globl CopyRamDataNoCacheable   
CopyRamDataNoCacheable:    
    ldr   r5, [r2]
    str   r5, [r4]
    add   r2, r2, #4
    add   r4, r4, #4
    sub   r3, r3, #1
    cmp   r3, #0
    bgt CopyRamDataNoCacheable  
CopyRamDataNoCacheable_LoopDone:

/************/
/* .ramcode */
/************/
    ldr r3, = RC_RAMCODE_SIZE
    ldr r2, = RC_RAMCODE_SRC
    ldr r4, = RC_RAMCODE_DEST

    cmp	r3, #0
    beq	CopyRamCode_LoopDone
    
.globl CopyRamCode   
CopyRamCode:    
    ldr   r5, [r2]
    str   r5, [r4]
    add   r2, r2, #4
    add   r4, r4, #4
    sub   r3, r3, #1
    cmp   r3, #0
    bgt CopyRamCode
CopyRamCode_LoopDone:
   
/****************/
/* .intc_vector */
/****************/
    ldr r3, = RC_INTC_VECTOR_SIZE
    ldr r2, = RC_INTC_VECTOR_SRC
    ldr r4, = RC_INTC_VECTOR_DEST

    cmp	r3, #0
    beq	CopyRamVector_LoopDone

.globl CopyRamVector
CopyRamVector:    
    ldr   r5, [r2]
    str   r5, [r4]
    add   r2, r2, #4
    add   r4, r4, #4
    sub   r3, r3, #1
    cmp   r3, #0
    bgt CopyRamVector    
CopyRamVector_LoopDone:

#endif


/*********************************/
/* Set the small ro data pointer */
/*********************************/
 

/*********************************/
/* Set the small rw data pointer */
/*********************************/


/******************************************************************/
/* Go to user mode and Call Main Routine                          */
/******************************************************************/
bl startup_go_to_user_mode
bl main

/******************************************************************/
/* Init runtime check data space                                  */
/******************************************************************/

.globl MCAL_LTB_TRACE_OFF
 MCAL_LTB_TRACE_OFF:
    nop
    
#ifdef CCOV_ENABLE
    /* code coverage is requested */
    bl ccov_main
#endif


.globl _end_of_eunit_test
_end_of_eunit_test:
 
    BKPT #1 /* last instruction for the debugger to dump results data */

    b . 

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
.globl startup_getControlRegisterValue
startup_getControlRegisterValue:
mrs r0, CONTROL
bx r14

.globl startup_getAipsRegisterValue
startup_getAipsRegisterValue:
mrs r0, IPSR
bx r14
#endif

.globl HSE_CORE_LOOP
HSE_CORE_LOOP:
    b HSE_CORE_LOOP


/*.section  ".rcw", "aw"*/
/*.align 2*/

/* configure boot, by setting the first words from address 0x0000_0000.*/
/*.long     _Stack_start*/	  /* Set word 0, the initial SP. */

/* configure the reset handler address, startup place. ensure the LSB bit is set to 1 for Thumb mode.*/
/*#ifdef __GNUC__*/
/* GNU compiler does not add +1 to _start label for Thumb mode */
/*.long     _start+0x01	*/  /* Reset handler address, force thumb mode(last bit must be 1) */
/*#else*/
/*.long     _start*/    	  
/*#endif*/
   
    
.section ".stack_main","aw"
.thumb
.align 4

#ifdef __STACK_SIZE
.set Stack_Size, __STACK_SIZE
#else
.set Stack_Size, 0x1000
#endif

.space Stack_Size

