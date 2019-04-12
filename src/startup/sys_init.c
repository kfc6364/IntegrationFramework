/*================================================================================================*/
/**
*   @file    sys_init.c
*   @version 0.8.1
*
*   @brief   AUTOSAR IntegrationFramework - MCAL auxiliary APIs used for MCAL testing
*   @details MCAL auxiliary APIs used for MCAL testing
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

#ifdef __cplusplus
extern "C" {
#endif

    
/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "sys_init.h"
#include "Mcal.h"
#include "StdRegMacros.h"
#include "S32K2TV.h"

#include "nvic.h"
/*==================================================================================================
*                                        LOCAL MACROS
==================================================================================================*/
#define NUM_MSCM_SPI_IRQ               ((uint32)240U)

#define SIUL2_PTB5_ADDR32       ((uint32)0x400902D4UL)
#define SIUL2_PTD10_ADDR32      ((uint32)0x400903E8UL)
#define SIUL2_PTD14_ADDR32      ((uint32)0x400903F8UL) 
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
uint32_t  DummyVar=0x56788765;
uint32_t  RESET_CATCH_CORE=0x00U;     /*Allocate a global variable which will be overwritten by the debugger if attached(in CMM), to catcht the core after reset.*/
/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    extern uint32 startup_getControlRegisterValue(void);
    extern uint32 startup_getAipsRegisterValue(void);
#endif
void startup_go_to_user_mode(void);

/*================================================================================================*/
/**
* @brief    startup_go_to_user_mode
* @details  Function called from startup.s to switch to user mode if MCAL_ENABLE_USER_MODE_SUPPORT
*           is defined
*/
/*================================================================================================*/
void startup_go_to_user_mode(void)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
    ASM_KEYWORD("svc 0x1");
#endif
}

/*================================================================================================*/
/**
* @brief Sys_GoToSypervisor
* @details function used to enter to supervisor mode.
            check if it's needed to switch to supervisor mode and make the switch.
            Return 1 if switch was done
*/
/*================================================================================================*/

#ifdef MCAL_ENABLE_USER_MODE_SUPPORT

/* check if it's needed to switch to supervisor mode and make the switch.
Return 1 if switch was done */
uint8 Sys_GoToSupervisor(void)
{
    VAR(uint32, MCU_VAR) u32ControlRegValue;
    VAR(uint32, MCU_VAR) u32AipsRegValue;
    VAR(uint8, MCU_VAR)  u8SwithcToSupervisor;
    /* if it's 0 then Thread mode is already in supervisor mode */
    u32ControlRegValue = startup_getControlRegisterValue();
    /* if it's 0 the core is in Thread mode, otherwise in Handler mode */
    u32AipsRegValue = startup_getAipsRegisterValue();
    /* if core is already in supervisor mode for Thread mode, or running form Handler mode, there is no need to make the switch */
    if((0UL == (u32ControlRegValue & 1)) || (0 < (u32AipsRegValue & 0xFF)))
    {
        u8SwithcToSupervisor = 0U;
    }
    else
    {
        u8SwithcToSupervisor = 1U;
        Mcal_goToSupervisor();
    }
    return u8SwithcToSupervisor;
}

/*================================================================================================*/
/**
* @brief Sys_ToUser_Return
* @details function used to switch back to user mode for Thread mode, return a uint32 value passed as parameter
*/
/*================================================================================================*/
uint32 Sys_GoToUser_Return(uint8 u8SwithcToSupervisor, uint32 u32returnValue)
{
      if(1UL == u8SwithcToSupervisor)
      {
        Mcal_goToUser();
      }
      return u32returnValue;
}
/*make the switch back to user mode for Thread mode, return 0. */
 uint32 Sys_GoToUser(void)
{
        Mcal_goToUser();
        return 0UL;
}
#endif
/*=================================================================================================*/

/* To Initialize both caches, make these two function calls
 *  m4_cache_init(CODE_CACHE);
 *  m4_cache_init(SYS_CACHE);
 */

uint8_t m4_cache_init(uint8_t cache)
{
#if 0
  if (cache == CODE_CACHE)
  {
      /* Code Cache Init */

      /* Cache Set Command: set command bits in CCR */
      /* set invalidate way 1 and invalidate way 0 bits */
      LMEM->PCCCR = 0x05000000;

      /* set ccr[go] bit to initiate command to invalidate cache */
      LMEM->PCCCR |= LMEM_PCCCR_GO(1);

      /* wait until the ccr[go] bit clears to indicate command complete */
      while((LMEM->PCCCR & LMEM_PCCCR_GO_MASK) == LMEM_PCCCR_GO_MASK);

      /* enable cache */
      LMEM->PCCCR |= LMEM_PCCCR_ENCACHE(1);

  }else if (cache == SYS_CACHE)
  {
#if 0
      /* System Cache Init */

      /* Cache Set Command: set command bits in CCR */
      /* set invalidate way 1 and invalidate way 0 bits */
      LMEM->PSCCR = 0x05000000;

      /* set ccr[go] bit to initiate command to invalidate cache */
      LMEM->PSCCR |= LMEM_PSCCR_GO(1);

      /* wait until the ccr[go] bit clears to indicate command complete */
      while((LMEM->PSCCR & LMEM_PSCCR_GO_MASK) == LMEM_PSCCR_GO_MASK);

      /* enable write buffer */
      LMEM->PSCCR |= LMEM_PSCCR_ENWRBUF(1);

      /* enable cache */
      LMEM->PSCCR |= LMEM_PSCCR_ENCACHE(1);
#endif
  } else
  {
     return CACHE_INVALID_PARAM;
  }
#endif
  (void)cache;

  return CACHE_OK;
}


uint8_t m4_cache_disable(uint8_t cache)
{
#if 0
  if (cache == CODE_CACHE)
  {
       /* Disable code cache */
       LMEM->PCCCR = 0;

  }else if (cache == SYS_CACHE)
  {
       /* Disable system cache */
       /*LMEM->PSCCR = 0; */

  } else
  {
     return CACHE_INVALID_PARAM;
  }
#endif
  (void)cache;
  return CACHE_OK;
}


uint8_t m4_cache_invalidate(uint8_t cache)
{
#if 0
  if (cache == CODE_CACHE)
  {
      /* Cache Set Command: set command bits in CCR */
      /* set invalidate way 1 and invalidate way 0 bits */
      LMEM->PCCCR = 0x05000000; /* set INVW0 and INVW1 */

      /* set ccr[go] bit to initiate command to invalidate cache */
      LMEM->PCCCR |= LMEM_PCCCR_GO(1);

      /* wait until the ccr[go] bit clears to indicate command complete */
      while((LMEM->PCCCR & LMEM_PCCCR_GO_MASK) == LMEM_PCCCR_GO_MASK);

  }else if (cache == SYS_CACHE)
  {
#if 0
      /* Cache Set Command: set command bits in CCR */
      /* set invalidate way 1 and invalidate way 0 bits */
      LMEM.PSCCR.R = 0x05000000; /* set INVW0 and INVW1 */

      /* set ccr[go] bit to initiate command to invalidate cache */
      LMEM->PSCCR |= LMEM_PSCCR_GO(1);

      /* wait until the ccr[go] bit clears to indicate command complete */
      while((LMEM->PSCCR & LMEM_PSCCR_GO_MASK) == LMEM_PSCCR_GO_MASK);
#endif
  } else
  {
     return CACHE_INVALID_PARAM;
  }
#endif
  (void)cache;
  return CACHE_OK;

}

uint8_t m4_cache_flush(uint8_t cache)
{
#if 0
  if (cache == CODE_CACHE)
  {
      /* Cache Set Command: set command bits in CCR */
      /* set invalidate way 1 and invalidate way 0 bits */
      LMEM->PCCCR = 0x0A000000; /* set INVW0 and INVW1 */

      /* set ccr[go] bit to initiate command to invalidate cache */
      LMEM->PCCCR |= LMEM_PCCCR_GO(1);

      /* wait until the ccr[go] bit clears to indicate command complete */
      while((LMEM->PCCCR & LMEM_PCCCR_GO_MASK) == LMEM_PCCCR_GO_MASK);

  }else if (cache == SYS_CACHE)
  {
#if 0     
      /* Cache Set Command: set command bits in CCR */
      /* set invalidate way 1 and invalidate way 0 bits */
      LMEM->PSCCR = 0x0A000000; /* set INVW0 and INVW1 */

      /* set ccr[go] bit to initiate command to invalidate cache */
      LMEM->PSCCR |= LMEM_PSCCR_GO(1);

      /* wait until the ccr[go] bit clears to indicate command complete */
      while((LMEM->PSCCR & LMEM_PSCCR_GO_MASK) == LMEM_PSCCR_GO_MASK);
#endif      
  } else
  {
     return CACHE_INVALID_PARAM;
  }
#endif
  (void)cache;
  return CACHE_OK;
}

uint8_t m4_cache_invalidate_buffer(uint32_t start_addr, long size)
{
#if 0    
  /* 32B line size => number of loops = size to invalidate divided by line size in bits plus 1 */
  uint32_t loops = size/32;
  uint32_t addr = start_addr;
  uint32_t i;
  
  for (i=0; i<loops; i++,addr+=32){
    /* LACC 27        - Read:             0x0  */
    /* LADSEL 26      - Physical Address: 0x1  */
    /* LCMD 25-24     - Invalidate:       0x01 */
    /* TDSEL 16       - Data:             0x0  */
    /* WSEL 14        - Way 0:            0x0  */
    LMEM->PCCLCR = 0x05000000;
    
    /* set physical address as start address with 2 LSB dropped */
    LMEM->PCCSAR = addr&0xFFFFFFFC;
    
    /* set csar[lgo] to initiate command indicated by bits 27-24 in clcr */
    LMEM->PCCSAR |= LMEM_PCCSAR_LGO(1);
    
    /* wait until the csar[lgo] bit clears to indicate command complete */
    while((LMEM->PCCSAR & LMEM_PCCSAR_LGO_MASK) == LMEM_PCCSAR_LGO_MASK);
  }
#endif  
  (void)start_addr;
  (void)size;
  return CACHE_OK;
}

uint8_t m4_cache_flush_buffer(uint32_t start_addr, long size)
{
#if 0    
  /* 32B line size => number of loops = size to invalidate divided by line size in bits plus 1 */
  uint32_t loops = size/32;
  uint32_t addr = start_addr;
  uint32_t i;
  
  for (i=0; i<loops; i++,addr+=32){
    /* LACC 27        - Read:             0x0  */
    /* LADSEL 26      - Physical Address: 0x1  */
    /* LCMD 25-24     - Push:             0x10 */
    /* TDSEL 16       - Data:             0x0  */
    /* WSEL 14        - Way 0:            0x0  */
    LMEM->PCCLCR = 0x06000000;
    
    /* set physical address as start address with 2 LSB dropped */
    LMEM->PCCSAR = addr&0xFFFFFFFC;
    
    /* set csar[lgo] to initiate command indicated by bits 27-24 in clcr */ 
    LMEM->PCCSAR |= LMEM_PCCSAR_LGO(1);
    
    /* wait until the csar[lgo] bit clears to indicate command complete */
    while((LMEM->PCCSAR & LMEM_PCCSAR_LGO_MASK) == LMEM_PCCSAR_LGO_MASK);
  }
#endif  
  (void)start_addr;
  (void)size;
  
  return CACHE_OK;
}

/** 
* @brief sys_init
* @details function used to enable all interrupts
*/
void sys_enableAllInterrupts(void)
{
    ResumeAllInterrupts();
}
/** 
* @brief sys_init
* @details function used to disable all interrupts
*/
void sys_disableAllInterrupts(void)
{
    SuspendAllInterrupts();
}
/** 
* @brief sys_init
* @details function used to disable the interrupt number id
*/
void sys_disableIsrSource(uint8 id)
{
    NVIC_DisableIRQ(id);
}
/** 
* @brief sys_init
* @details function used to enable the interrupt number id and set up the priority
*/
void sys_enableIsrSource(uint8 id, uint8 prio)
{
    NVIC_SetPriority(id, prio);
    NVIC_EnableIRQ(id);
}
/** 
* @brief sys_init
* @details function used to register the interrupt handler in the interrupt vector
*/
void  sys_registerIsrHandler(uint8_t irq_id, uint32 isr_handler)
{
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
	Mcal_goToSupervisor();
#endif
   REG_WRITE32(S32_SCB->VTOR + ((16 + irq_id) << 2), isr_handler);
#ifdef MCAL_ENABLE_USER_MODE_SUPPORT
	Mcal_goToUser();
#endif  
}
    
#ifdef __ICCARM__ 
    #pragma default_function_attributes = @ ".systeminit"
#else
    __attribute__ ((section (".systeminit")))
#endif 

#ifdef __ICCARM__ 
/* Initialize RAM variables and RAM functions */
void Scatter_Loading(void)
{

    volatile char * from; 
    volatile char * to;     
    volatile uint32 length;   
    
    #pragma segment = "AppBSS"
    from = (char *)__segment_begin("AppBSS");
    to = (char *)__segment_end("AppBSS");
    length = __segment_size("AppBSS");
    while(length--)
    {
        *from++ = 0U;
    }
    
#ifndef SINTRAM  /* SINTRAM defined by compiler option -DSINTRAM only for INTRAM build */    
    /* Zero fill the entire RAM */
    /* from = (char *)__region_begin("int_sram_region");
    to = (char *)__region_limit("int_results_region");
    length = __region_size("int_sram_region") + __region_size("int_stack_region") + __region_size("int_results_region");
    while(length--)
    {
        *from++ = 0U;
    } */
    
#pragma language=extended 
    /* Relocate the INT Vect table */
    #pragma section = "AppIntVec_Init"
    #pragma section = "AppIntVec"
    from = (char *)__segment_begin("AppIntVec_Init");
    to = (char *)__segment_begin("AppIntVec");
    length = __segment_size("AppIntVec");

     while(length--)
    {
        *to++ = *from++;

    }
    
    /* Relocate the  RAM code */
    #pragma section = "AppRAMCode"
    #pragma section = "AppRAMCode_Init"
    from = (char *)__segment_begin("AppRAMCode_Init");
    to = (char *)__segment_begin("AppRAMCode");
    length = __segment_size("AppRAMCode");
    while(length--)
    {
        *to++ = *from++;
    }
        
    /* Init DATA section */
    #pragma section = "AppData"
    #pragma section = "AppData_Init"
    from = (char *)__segment_begin("AppData_Init");
    to = (char *)__segment_begin("AppData");
    length = __segment_size("AppData");
    while(length--)
    {
        *to++ = *from++;
    }
    
    /* Init DATA NO_CACHE section */
    #pragma section = "AppData_NO_CACHE"
    #pragma section = "AppData_NO_CACHE_Init"
    from = (char *)__segment_begin("AppData_NO_CACHE_Init");
    to = (char *)__segment_begin("AppData_NO_CACHE");
    length = __segment_size("AppData_NO_CACHE");
    while(length--)
    {
        *to++ = *from++;
    }
    #pragma language=default
    
#endif    /*#ifndef SINTRAM*/

}
#endif /* #ifdef __ICCARM__ */


/*
 * system initialization : system clock, interrupt router ...
 */
void SystemInit(void)
{
/*uint8 i = 0U;*/

    NVIC_SetPriorityGrouping(0); /* 0 means 7 bits for prio, 1 for sub-prio */

    /**< NONBASETHRDENA = 1; processor can enter Thread mode from any level under the control of an EXC_RETURN value.*/
    S32_SCB->CCR |=  1;       
    /** Set PendSV priority set to 0, to ensure the software triggered interrupt, for user mode entry,*/   
    REG_BIT_CLEAR32(&(S32_SCB->SHPR3), S32_SCB_SHPR3_PRI_14_MASK); 
#if 0    
    /* Configure multicore interrupt routing. */
    for(i=0U; i < NUM_MSCM_SPI_IRQ; i++)
    {
        /* Route the interrupt lines to all three cores. */
        MSCM.IRSPRC[i].R = (uint16)0x0007UL;     
    }
    
    
    /* enable the AIPS */
    AIPS->MPRA = 0x77777777;      
    AIPS->PACR[0]  = 0x0; 
    AIPS->PACR[1]  = 0x0; 
    AIPS->PACR[2]  = 0x0;  
    AIPS->PACR[3]  = 0x0; 
    AIPS->OPACR[0] = 0x0; 
    AIPS->OPACR[1] = 0x0; 
    AIPS->OPACR[2] = 0x0; 
    AIPS->OPACR[3] = 0x0; 
    AIPS->OPACR[4] = 0x0; 
    AIPS->OPACR[5] = 0x0; 
    AIPS->OPACR[6] = 0x0; 
    AIPS->OPACR[7] = 0x0; 
    AIPS->OPACR[8] = 0x0; 
    AIPS->OPACR[9] = 0x0; 
    AIPS->OPACR[10] = 0x0;
    AIPS->OPACR[11] = 0x0;
   
  
#if 0
    /* Enable speculative prefetching for program flash (flash bank 0) */
	MSCM->OCMDR[0] |= MSCM_OCMDR_OCMC1(2);
	/* Enable speculative prefetching for data flash (flash bank 1) */
	MSCM->OCMDR[1] |= MSCM_OCMDR_OCMC1(2);
#endif
	/* Configure slave ports to fixed-priority arbitration (default after reset) */
	MCM->CPCR &= ~MCM_CPCR_CBRR_MASK;

	/* Configure the SRAM_L and SRAM_U arbitration scheme to fixed priority (processor has highest, backdoor has lowest) */
	MCM->CPCR = MCM_CPCR_SRAMLAP(2) | MCM_CPCR_SRAMUAP(2); 
 
    
#ifdef D_CACHE_ENABLE    
    /*init Data caches*/
    m4_cache_init(SYS_CACHE);
#endif

#ifdef I_CACHE_ENABLE  
    /*init Code caches*/
    m4_cache_init(CODE_CACHE);
#endif

#endif    
}


/**
* @brief sys_init
* @details function used to initiatialize clocks, system clock is system Pll 120 MHz
* @return E_NOT_OK/E_OK
*/
/*================================================================================================*/
Std_ReturnType sys_init(void)
{
/* Summary:
*  SysClk_Source = PLL_CLK, M7_CLK = 48MHz, M33_CLK = 48MHz, AIPS_PLAT_CLK = 48MHz, AIPS_SLOW_CLK = 24MHz, QSPI_MEM_CLK = 48MHz, HSE_IPS_CLK = 24MHz, LBIST_CLK = 48MHz
*  FLEXCAN0_PE_CLK_Source = AIPS_SLOW_CLK, FLEXCAN0_PE_CLK = 24MHz
*  FLEXCAN1_PE_CLK_Source = AIPS_SLOW_CLK, FLEXCAN1_PE_CLK = 24MHz
*  FLEXCAN2_PE_CLK_Source = AIPS_SLOW_CLK, FLEXCAN2_PE_CLK = 24MHz
*  FLEXCAN3_PE_CLK_Source = AIPS_SLOW_CLK, FLEXCAN3_PE_CLK = 24MHz
*  FLEXCAN4_PE_CLK_Source = AIPS_SLOW_CLK, FLEXCAN4_PE_CLK = 24MHz
*  FLEXCAN5_PE_CLK_Source = AIPS_SLOW_CLK, FLEXCAN5_PE_CLK = 24MHz
*  FLEXCAN6_PE_CLK_Source = AIPS_SLOW_CLK, FLEXCAN6_PE_CLK = 24MHz
*  FLEXCAN7_PE_CLK_Source = AIPS_SLOW_CLK, FLEXCAN7_PE_CLK = 24MHz
*  FLEXRAY_PE_CLK_Source  = AIPS_PLAT_CLK, FLEXRAY_PE_CLK  = 48MHz
*  CLKOUT_STBY        = Disabled
*  CLKOUT_RUN         = Disabled
*  ENET_RX_CLK_Source = FIRC_CLK,      ENET_RX_CLK = 24MHz (Assuming FIRC is trimmed).
*  ENET_TX_CLK_Source = FIRC_CLK,      ENET_TX_CLK = 24MHz (Assuming FIRC is trimmed).
*  ENET_TS_CLK_Source = FXOSC_CLK,     ENET_TS_CLK = 16MHz
*  SDHC_CLK_Source    = AIPS_PLAT_CLK, SDHC_CLK    = 48MHz
*  QSPI_SFCK_Source   = PLL_CLK,       QSPI_SFCK   = 48MHz
*  TRACE_CLK          = Disabled
*/    
        
    /* Configure FXOSC (16MHz) */
    /* FXOSC_CTRL[OSC_BYP] = 0 and FXOSC_CTRL[COMP_EN] = 1 and FXOSC_CTRL[OSC_EOCV] = 157 and FXOSC_CTRL[GM_SEL] = 12 and FXOSC_CTRL[OSCON] = 1 */
    /*REG_WRITE32(0x400D4000U, 0x019D00C1U);*/
    FXOSC.FXOSC_CTRL.B.OSC_BYP = 0;
    FXOSC.FXOSC_CTRL.B.COMP_EN = 1;
    FXOSC.FXOSC_CTRL.B.EOCV = 157;
    FXOSC.FXOSC_CTRL.B.GM_SEL = 12;
    FXOSC.FXOSC_CTRL.B.OSCON = 1;
    
    
    /* Wait for FXOSC to stabilize */
    /*while ( 0U == (REG_READ32(0x400D4004U) & 0x80000000U))*/
    while ( 0U == FXOSC.FXOSC_STAT.B.OSC_STAT)
    {
        /* Busy wait until the update has finished */
    }



    /* Configure SXOSC (32768Hz) - needs two resistors removed from daughter card. */
    /* SXOSC_CTRL[EOCV] = 125 and SXOSC_CTRL[GM_SEL] = 0 and SXOSC_CTRL[EOCV] = 1 */
    /*REG_WRITE32(0x402A8000U, 0x007D00C1U);*/

    /* Wait for SXOSC to stabilize */
    /*while ( 0U == (REG_READ32(0x402A8004U) & 0x80000000U))*/
    /*{*/
        /* Busy wait until the update has finished */
    /*}*/



    /* Configure PLLDIG (VCO = 720MHz, PLL_CLK = 48MHz) */

    /* Disable PLLODIV_0 (PLLDIG_PLLODIV_0[DE] = 0 and PLLDIG_PLLODIV_0[DIV] = 0) */
    /*REG_WRITE32(0x400E0080U, 0x0U);*/
    PLL.PLLODIV_PLLODIV[0].B.DE = 0U;
    PLL.PLLODIV_PLLODIV[0].B.DIV = 0U;
    
    /* Disable ANALOG_PLL (PLLDIG_PLLCR[PLLPD] = 1) */
    /*REG_WRITE32(0x400E0000U, 0x80000000U);*/
    PLL.PLLCR.B.PLLPD = 1U;
    
    /* Update PLLDV (PLLDIG_PLLDV[RDIV] = 2, PLLDIG_PLLDV[MFI] = 90, PLLDIG_PLLDV[ODIV2] = 15) */
    /*REG_WRITE32(0x400E0008U, 0x1E3F205AU);*/
    PLL.PLLDV.B.RDIV = 2U;
    PLL.PLLDV.B.MFI = 90U;
    PLL.PLLDV.B.ODIV2 = 15U;
        
    /* Enable ANALOG_PLL (PLLDIG_PLLCR[PLLPD] = 0) */
    /*REG_WRITE32(0x400E0000U, 0x0U);*/
    PLL.PLLCR.B.PLLPD = 0U;

    /* Enable PLLODIV_0 (PLLDIG_PLLODIV_0[DE] = 1 and PLLDIG_PLLODIV_0[DIV] = 0) */
    /*REG_WRITE32(0x400E0080U, 0x80000000U);*/
    PLL.PLLODIV_PLLODIV[0].B.DE = 1U;
    

    /* Wait for PLL to lock */
    /*while ( 0U == (REG_READ32(0x400E0004U) & 0x00000004U))*/
    while ( 0U == (PLL.PLLSR.B.LOCK) )
    {
        /* Busy wait until the PLL has locked */
    }



    /* Configure MC_CGM Dividers */

    /* Update dividers alignment policy (MC_CGM_0_MUX_0_DIV_TRIG_CTRL[HHEN] = 1 && MC_CGM_0_MUX_0_DIV_TRIG_CTRL[TCTL] = 1) */
    /*REG_WRITE32(0x400D8334U, 0X80000001U);*/
    MC_CGM.MUX_0_DIV_TRIG_CTRL.B.HHEN = 1U;
    MC_CGM.MUX_0_DIV_TRIG_CTRL.B.TCTL = 1U;
    
    /* MC_CGM_0_MUX_0_DC_0[DIV] = 0 (M33_CORE_CLK) */
    /*REG_WRITE32(0x400D8308U, 0x00000000U);*/
    MC_CGM.MUX_0_DC_0.B.DIV = 0U;
    
    /* MC_CGM_0_MUX_0_DC_1[DIV] = 0 (AIPS_PLAT_CLK) */
    /*REG_WRITE32(0x400D830CU, 0x00000000U);*/
    MC_CGM.MUX_0_DC_1.B.DIV = 0U;

    /* MC_CGM_0_MUX_0_DC_2[DIV] = 1 (AIPS_SLOW_CLK) */
    /*REG_WRITE32(0x400D8310U, 0x00010000U);*/
    MC_CGM.MUX_0_DC_2.B.DIV = 1U;
    
    /* MC_CGM_0_MUX_0_DC_3[DIV] = 0 (QSPI_MEM_CLK) */
    /*REG_WRITE32(0x400D8314U, 0x00000000U);*/
    MC_CGM.MUX_0_DC_3.B.DIV = 0U;

    /* MC_CGM_0_MUX_0_DC_4[DIV] = 1 (HSE_IPS_CLK) */
    /*REG_WRITE32(0x400D8318U, 0x00010000U);*/
    MC_CGM.MUX_0_DC_4.B.DIV = 1U;

    /* MC_CGM_0_MUX_0_DC_5[DIV] = 0 (LBIST_CLK) */
    /*REG_WRITE32(0x400D831CU, 0x00000000U);*/
    MC_CGM.MUX_0_DC_5.B.DIV = 0U;

    /* Wait until MC_CGM_0_MUX_0_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D833CU) & 0x00000001U))*/
    while ( 1U == (MC_CGM.MUX_0_DIV_UPD_STAT.B.DIV_STAT))
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_0_DC_0[DE] = 1 (M33_CORE_CLK) */
    /*REG_RMW32(0x400D8308U, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_0_DC_0.B.DE = 1U;
    
    /* MC_CGM_0_MUX_0_DC_1[DE] = 1 (AIPS_PLAT_CLK) */
    /*REG_RMW32(0x400D830CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_0_DC_1.B.DE = 1U;

    /* MC_CGM_0_MUX_0_DC_2[DE] = 1 (AIPS_SLOW_CLK) */
    /*REG_RMW32(0x400D8310U, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_0_DC_2.B.DE = 1U;

    /* MC_CGM_0_MUX_0_DC_3[DE] = 1 (QSPI_MEM_CLK) */
    /*REG_RMW32(0x400D8314U, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_0_DC_3.B.DE = 1U;

    /* MC_CGM_0_MUX_0_DC_4[DE] = 1 (HSE_IPS_CLK) */
    /*REG_RMW32(0x400D8318U, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_0_DC_4.B.DE = 1U;

    /* MC_CGM_0_MUX_0_DC_5[DE] = 1 (LBIST_CLK) */
    /*REG_RMW32(0x400D831CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_0_DC_5.B.DE = 1U;

    /* Trigger dividers update */
    /*REG_WRITE32(0x400D8338U, 0xFFFFFFFFU);*/
    MC_CGM.MUX_0_DIV_TRIG.R = 0xFFFFFFFFU;
    
    /* Wait until MC_CGM_0_MUX_0_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D833CU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_0_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }



    /* MC_CGM_0_MUX_1_DC_1[DIV] = 0 (FLEXCAN0_PE_CLK) */
    /*REG_WRITE32(0x400D834CU, 0x00000000U);*/
    MC_CGM.MUX_1_DC_1.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_1_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D837CU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_1_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_1_DC_1[DE] = 1 (FLEXCAN0_PE_CLK) */
    /*REG_RMW32(0x400D834CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_1_DC_1.B.DE = 1U;


    /* MC_CGM_0_MUX_2_DC_1[DIV] = 0 (FLEXCAN1_PE_CLK) */
    /*REG_WRITE32(0x400D838CU, 0x00000000U);*/
    MC_CGM.MUX_2_DC_1.B.DIV = 0U;

    /* Wait until MC_CGM_0_MUX_2_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D83BCU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_2_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_2_DC_1[DE] = 1 (FLEXCAN1_PE_CLK) */
    /*REG_RMW32(0x400D838CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_2_DC_1.B.DE = 1U;



    /* MC_CGM_0_MUX_3_DC_1[DIV] = 0 (FLEXCAN2_PE_CLK) */
    /*REG_WRITE32(0x400D83CCU, 0x00000000U);*/
    MC_CGM.MUX_3_DC_1.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_3_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D83FCU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_3_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_3_DC_1[DE] = 1 (FLEXCAN2_PE_CLK) */
    /*REG_RMW32(0x400D83CCU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_3_DC_1.B.DE = 1U;


    /* MC_CGM_0_MUX_4_DC_1[DIV] = 0 (FLEXCAN3_PE_CLK) */
    /*REG_WRITE32(0x400D840CU, 0x00000000U);*/
    MC_CGM.MUX_4_DC_1.B.DIV = 0U;

    /* Wait until MC_CGM_0_MUX_4_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D843CU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_4_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_4_DC_1[DE] = 1 (FLEXCAN3_PE_CLK) */
    /*REG_RMW32(0x400D840CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_4_DC_1.B.DE = 1U;



    /* MC_CGM_0_MUX_5_DC_1[DIV] = 0 (FLEXCAN4_PE_CLK) */
    /*REG_WRITE32(0x400D844CU, 0x00000000U);*/
    MC_CGM.MUX_5_DC_1.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_5_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D847CU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_5_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_5_DC_1[DE] = 1 (FLEXCAN4_PE_CLK) */
    /*REG_RMW32(0x400D844CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_5_DC_1.B.DE = 1U;



    /* MC_CGM_0_MUX_6_DC_1[DIV] = 0 (FLEXCAN5_PE_CLK) */
    /*REG_WRITE32(0x400D848CU, 0x00000000U);*/
    MC_CGM.MUX_6_DC_1.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_6_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D84BCU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_6_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_6_DC_1[DE] = 1 (FLEXCAN5_PE_CLK) */
    /*REG_RMW32(0x400D848CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_6_DC_1.B.DE = 1U;



    /* MC_CGM_0_MUX_7_DC_1[DIV] = 0 (FLEXCAN6_PE_CLK) */
    /*REG_WRITE32(0x400D84CCU, 0x00000000U);*/
    MC_CGM.MUX_7_DC_1.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_7_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D84FCU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_7_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_7_DC_1[DE] = 1 (FLEXCAN6_PE_CLK) */
    /*REG_RMW32(0x400D84CCU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_7_DC_1.B.DE = 1U;


    /* MC_CGM_0_MUX_8_DC_1[DIV] = 0 (FLEXCAN7_PE_CLK) */
    /*REG_WRITE32(0x400D850CU, 0x00000000U);*/
    MC_CGM.MUX_8_DC_1.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_8_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D853CU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_8_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_8_DC_1[DE] = 1 (FLEXCAN7_PE_CLK) */
    /*REG_RMW32(0x400D850CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_8_DC_1.B.DE = 1U;


    /* MC_CGM_0_MUX_9_DC_1[DIV] = 0 (FLEXRAY_PE_CLK) */
    /*REG_WRITE32(0x400D854CU, 0x00000000U);*/
    MC_CGM.MUX_9_DC_1.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_9_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D857CU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_9_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_9_DC_1[DE] = 1 (FLEXRAY_PE_CLK) */
    /*REG_RMW32(0x400D854CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_9_DC_1.B.DE = 1U;


    /* MC_CGM_0_MUX_10_DC_6[DE] = 0 and MC_CGM_0_MUX_10_DC_6[DIV] = 0 (CLKOUT_STBY) */
    /*REG_WRITE32(0x400D85A0U, 0x00000000U);*/
    MC_CGM.MUX_10_DC_6.B.DE = 0U;
    MC_CGM.MUX_10_DC_6.B.DIV = 0U;
    
    /* MC_CGM_0_MUX_11_DC_6[DE] = 0 and MC_CGM_0_MUX_11_DC_6[DIV] = 0 (CLKOUT_RUN) */
    /*REG_WRITE32(0x400D85E0U, 0x00000000U);*/
    MC_CGM.MUX_11_DC_6.B.DE = 0U;
    MC_CGM.MUX_11_DC_6.B.DIV = 0U;


    /* MC_CGM_0_MUX_14_DC_6[DIV] = 0 (ENET_CLK_RX) */
    /*REG_WRITE32(0x400D86A0U, 0x00000000U);*/
    MC_CGM.MUX_14_DC_6.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_14_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D86BCU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_14_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_14_DC_6[DE] = 1 (ENET_CLK_RX) */
    /*REG_RMW32(0x400D86A0U, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_14_DC_6.B.DE = 1U;


    /* MC_CGM_0_MUX_15_DC_6[DIV] = 0 (ENET_CLK_TX) */
    /*REG_WRITE32(0x400D86E0U, 0x00000000U);*/
    MC_CGM.MUX_15_DC_6.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_15_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D86FCU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_15_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_15_DC_6[DE] = 1 (ENET_CLK_TX) */
    /*REG_RMW32(0x400D86E0U, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_15_DC_6.B.DE = 1U;


    /* MC_CGM_0_MUX_16_DC_6[DIV] = 0 (ENET_CLK_TS) */
    /*REG_WRITE32(0x400D8720U, 0x00000000U);*/
    MC_CGM.MUX_16_DC_6.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_16_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D873CU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_16_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_16_DC_6[DE] = 1 (ENET_CLK_TS) */
    /*REG_RMW32(0x400D8720U, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_16_DC_6.B.DE = 1U;


    /* MC_CGM_0_MUX_17_DC_1[DIV] = 0 (SDHC_CLK) */
    /*REG_WRITE32(0x400D874CU, 0x00000000U);*/
    MC_CGM.MUX_17_DC_1.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_17_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D877CU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_17_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_17_DC_1[DE] = 1 (SDHC_CLK) */
    /*REG_RMW32(0x400D874CU, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_17_DC_1.B.DE = 1U;


    /* MC_CGM_0_MUX_18_DC_3[DIV] = 0 (QSPI_SFCK) */
    /*REG_WRITE32(0x400D8794U, 0x00000000U);*/
    MC_CGM.MUX_18_DC_3.B.DIV = 0U;
    
    /* Wait until MC_CGM_0_MUX_18_DIV_UPD_STAT[DIV_STAT] = 0 (i.e. divider configuration update has finished) */
    /*while ( 1U == (REG_READ32(0x400D87BCU) & 0x00000001U))*/
    while ( 1U == MC_CGM.MUX_18_DIV_UPD_STAT.B.DIV_STAT)
    {
        /* Busy wait until the update has finished */
    }

    /* MC_CGM_0_MUX_18_DC_3[DE] = 1 (QSPI_SFCK) */
    /*REG_RMW32(0x400D8794U, 0x80000000U, 0x80000000U);*/
    MC_CGM.MUX_18_DC_3.B.DE = 1U;


    /* MC_CGM_0_MUX_19_DC_3[DE] = 0 and MC_CGM_0_MUX_19_DC_3[DIV] = 0 (TRACE_CLK) */
    /*REG_WRITE32(0x400D87D4U, 0x00000000U);*/
    MC_CGM.MUX_19_DC_3.B.DE = 0U;
    MC_CGM.MUX_19_DC_3.B.DIV = 0U;
    
    /* Configure the embedded flash wait states - should be done from RAM */

    /* C40ASF_CTL[RWSC] = 3 */
    /*REG_RMW32(0x4028C00CU, 0x00001F00U, 0x00000300U);*/


    /* Switch MC_CGM sources */

    /* MC_CGM_0_MUX_0_CSC[SELCTL] = PLL and MC_CGM_0_MUX_0_CSC[CLK_SW] = 1 and MC_CGM_0_MUX_0_CSC[RAMPDOWN,RAMPUP] = 1 */
    /*REG_WRITE32(0x400D8300U, 0x08000007U);*/
    /*MC_CGM.MUX_0_CSC.B.SELCTL = 8U;
    MC_CGM.MUX_0_CSC.B.RAMPDOWN = 1U;
    MC_CGM.MUX_0_CSC.B.RAMPUP = 1U;
    MC_CGM.MUX_0_CSC.B.CLK_SW = 1U;*/
    MC_CGM.MUX_0_CSC.R = 0x08000007U;
    
    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8304U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_0_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8304U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_0_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_1_CSC[SELCTL] = AIPS_SLOW_CLK and MC_CGM_0_MUX_1_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8340U, 0x17000004U);*/
    MC_CGM.MUX_1_CSC.B.SELCTL = 0x17U;
    MC_CGM.MUX_1_CSC.B.CLK_SW = 1U;
    
    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8344U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_1_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8344U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_1_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_2_CSC[SELCTL] = AIPS_SLOW_CLK and MC_CGM_0_MUX_2_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8380U, 0x17000004U);*/
    MC_CGM.MUX_2_CSC.B.SELCTL = 0x17U;
    MC_CGM.MUX_2_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8384U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_2_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8384U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_2_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_3_CSC[SELCTL] = AIPS_SLOW_CLK and MC_CGM_0_MUX_3_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D83C0U, 0x17000004U);*/
    MC_CGM.MUX_3_CSC.B.SELCTL = 0x17U;
    MC_CGM.MUX_3_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D83C4U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_3_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D83C4U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_3_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_4_CSC[SELCTL] = AIPS_SLOW_CLK and MC_CGM_0_MUX_4_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8400U, 0x17000004U);*/
    MC_CGM.MUX_4_CSC.B.SELCTL = 0x17U;
    MC_CGM.MUX_4_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8404U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_4_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8404U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_4_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_5_CSC[SELCTL] = AIPS_SLOW_CLK and MC_CGM_0_MUX_5_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8440U, 0x17000004U);*/
    MC_CGM.MUX_5_CSC.B.SELCTL = 0x17U;
    MC_CGM.MUX_5_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8444U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_5_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8444U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_5_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_6_CSC[SELCTL] = AIPS_SLOW_CLK and MC_CGM_0_MUX_6_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8480U, 0x17000004U);*/
    MC_CGM.MUX_6_CSC.B.SELCTL = 0x17U;
    MC_CGM.MUX_6_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8484U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_6_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8484U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_6_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_7_CSC[SELCTL] = AIPS_SLOW_CLK and MC_CGM_0_MUX_7_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D84C0U, 0x17000004U);*/
    MC_CGM.MUX_7_CSC.B.SELCTL = 0x17U;
    MC_CGM.MUX_7_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D84C4U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_7_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D84C4U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_7_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_8_CSC[SELCTL] = AIPS_SLOW_CLK and MC_CGM_0_MUX_8_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8500U, 0x17000004U);*/
    MC_CGM.MUX_8_CSC.B.SELCTL = 0x17U;
    MC_CGM.MUX_8_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8504U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_8_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8504U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_8_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_9_CSC[SELCTL] = AIPS_PLAT_CLK and MC_CGM_0_MUX_9_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8540U, 0x16000004U);*/
    MC_CGM.MUX_9_CSC.B.SELCTL = 0x16U;
    MC_CGM.MUX_9_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
   /* while ( 0U == (REG_READ32(0x400D8544U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_9_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8544U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_9_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_14_CSC[SELCTL] = FIRC_CLK and MC_CGM_0_MUX_14_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8680U, 0x00000004U);*/
    MC_CGM.MUX_14_CSC.B.SELCTL = 0x0U;
    MC_CGM.MUX_14_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8684U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_14_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8684U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_14_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_15_CSC[SELCTL] = FIRC_CLK and MC_CGM_0_MUX_15_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D86C0U, 0x00000004U);*/
    MC_CGM.MUX_15_CSC.B.SELCTL = 0x0U;
    MC_CGM.MUX_15_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D86C4U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_15_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D86C4U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_15_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_16_CSC[SELCTL] = FIRC_CLK and MC_CGM_0_MUX_16_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8700U, 0x00000004U);*/
    MC_CGM.MUX_16_CSC.B.SELCTL = 0x0U;
    MC_CGM.MUX_16_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8704U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_16_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8704U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_16_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_17_CSC[SELCTL] = AIPS_PLAT_CLK and MC_CGM_0_MUX_17_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8740U, 0x16000004U);*/
    MC_CGM.MUX_17_CSC.B.SELCTL = 0x16U;
    MC_CGM.MUX_17_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8744U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_17_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8744U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_17_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }



    /* MC_CGM_0_MUX_18_CSC[SELCTL] = PLL_CLK and MC_CGM_0_MUX_18_CSC[CLK_SW] = 1 */
    /*REG_WRITE32(0x400D8780U, 0x08000004U);*/
    MC_CGM.MUX_18_CSC.B.SELCTL = 0x08U;
    MC_CGM.MUX_18_CSC.B.CLK_SW = 1U;

    /* Wait for configuration bit to auto-clear */
    /*while ( 0U == (REG_READ32(0x400D8784U) & 0x00000004U))*/
    while ( 0U == (MC_CGM.MUX_18_CSS.B.CLK_SW) )
    {
        /* Busy wait until configuration bit has auto-cleared */
    }

    /* Wait for the clock switch to complete. */
    /*while ( 0x00010000U == (REG_READ32(0x400D8784U) & 0x00010000U))*/
    while ( 1U == (MC_CGM.MUX_18_CSS.B.SWIP) )
    {
        /* Busy wait until the clock switch has completed. */
    }    
    
    
    /* Set PTB5 to CLKOUT_RUN */
    /*REG_WRITE32(SIUL2_PTB5_ADDR32, 0x00204105UL);*/

    /* Set PTD10 to CLKOUT_RUN */
    /*REG_WRITE32(SIUL2_PTD10_ADDR32, 0x00204106UL);*/
    
    /* Set PTD14 to CLKOUT_RUN */
    /*REG_WRITE32(SIUL2_PTD14_ADDR32, 0x00204107UL);*/
    
    /*MUX_11_CSC[SELCTL_16] = M7_CLK*/
    /*REG_WRITE32(0x400D85C0U,0x10000000U);*/
    
    /*MUX_11_DC_6[DE=1][DIV=17]*/
    /*REG_WRITE32(0x400D85E0U,0x80170000U);*/
    
    return E_OK;      
}

/*================================================================================================*/
/**
* @brief sys_halt
* @details function used to enter halt mode
*/
/*================================================================================================*/
void sys_halt(void)
{
 
    EXECUTE_WAIT();
}
/*================================================================================================*/
/**
* @brief sys_stop
* @details function used to enter stop mode
*/
/*================================================================================================*/
void sys_stop(void)
{
    EXECUTE_WAIT();
}

#ifdef __ICCARM__ 
    #pragma default_function_attributes =
#endif

#ifdef __cplusplus
}
#endif
