/**
*   @file           ComDal_Uart.c
*   @version        0.8.1
*
*   @brief          Integration Framework - ComDal Abstraction Layer internal Uart driver component
*   @details        This file implements the Uart driver for the ComDal interface to application layer.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup COMDAL
*   @{
*/
/*=================================================================================================================================
*   Platform             : CORTEXM
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   SW Version           : 0.8.1
*   Build Version        : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
*
===================================================================================================================================*/
/*=================================================================================================================================
===================================================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*=================================================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
===================================================================================================================================*/
#include "StdRegMacros.h"
#include "Reg_eSys.h"

#include "modules.h"
#include "Std_Types.h"
#include "Mcal.h"
#include "ComDal_Types.h"
#include "ComDal_Cfg.h"
#include "ComDal_Uart.h"
#include "StringLib.h"

#if (USE_LIN_MODULE==STD_ON)
#include "Reg_eSys_LINFlex.h"
#endif

/*=================================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
===================================================================================================================================*/
#define COMDAL_UART_VENDOR_ID_C                       43

#define COMDAL_UART_AR_RELEASE_MAJOR_VERSION_C        4
#define COMDAL_UART_AR_RELEASE_MINOR_VERSION_C        3
#define COMDAL_UART_AR_RELEASE_REVISION_VERSION_C     1

#define COMDAL_UART_SW_MAJOR_VERSION_C                0
#define COMDAL_UART_SW_MINOR_VERSION_C                8
#define COMDAL_UART_SW_PATCH_VERSION_C                1

/*=================================================================================================================================
*                                     FILE VERSION CHECKS
===================================================================================================================================*/
/* Check if source file and Comdal configuration header file are of the same vendor */
#if (COMDAL_UART_VENDOR_ID_C != COMDAL_CFG_VENDOR_ID)
    #error "ComDal_Uart.c and ComDal_Cfg.h have different vendor ids"
#endif

/* Check if source file and Comdal configuration header file are of the same Autosar version */
#if ((COMDAL_UART_AR_RELEASE_MAJOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_UART_AR_RELEASE_MINOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_UART_AR_RELEASE_REVISION_VERSION_C != COMDAL_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Uart.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and Comdal configuration header file are of the same Software version */
#if ((COMDAL_UART_SW_MAJOR_VERSION_C != COMDAL_CFG_SW_MAJOR_VERSION) || \
     (COMDAL_UART_SW_MINOR_VERSION_C != COMDAL_CFG_SW_MINOR_VERSION) || \
     (COMDAL_UART_SW_PATCH_VERSION_C != COMDAL_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal_Uart.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and Comdal types header file are of the same vendor */
#if (COMDAL_UART_VENDOR_ID_C != COMDAL_TYPES_VENDOR_ID)
    #error "ComDal_Uart.c and ComDal_Types.h have different vendor ids"
#endif

/* Check if source file and Comdal types header file are of the same Autosar version */
#if ((COMDAL_UART_AR_RELEASE_MAJOR_VERSION_C != COMDAL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_UART_AR_RELEASE_MINOR_VERSION_C != COMDAL_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_UART_AR_RELEASE_REVISION_VERSION_C != COMDAL_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Uart.c and ComDal_Types.h are different"
#endif

/* Check if source file and Comdal types header file are of the same Software version */
#if ((COMDAL_UART_SW_MAJOR_VERSION_C != COMDAL_TYPES_SW_MAJOR_VERSION) || \
     (COMDAL_UART_SW_MINOR_VERSION_C != COMDAL_TYPES_SW_MINOR_VERSION) || \
     (COMDAL_UART_SW_PATCH_VERSION_C != COMDAL_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal_Uart.c and ComDal_Types.h are different"
#endif

/* Check if source file and Comdal Can header file are from the same vendor */
#if (COMDAL_UART_VENDOR_ID_C != COMDAL_UART_VENDOR_ID)
    #error "ComDal_Uart.c and ComDal_Uart.h have different vendor ids"
#endif

/* Check if source file and Comdal Can header file are of the same Autosar version */
#if ((COMDAL_UART_AR_RELEASE_MAJOR_VERSION_C != COMDAL_UART_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_UART_AR_RELEASE_MINOR_VERSION_C != COMDAL_UART_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_UART_AR_RELEASE_REVISION_VERSION_C != COMDAL_UART_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Uart.c and ComDal_Uart.h are different"
#endif

/* Check if source file and Comdal Can header file are of the same Software version */
#if ((COMDAL_UART_SW_MAJOR_VERSION_C != COMDAL_UART_SW_MAJOR_VERSION) || \
     (COMDAL_UART_SW_MINOR_VERSION_C != COMDAL_UART_SW_MINOR_VERSION) || \
     (COMDAL_UART_SW_PATCH_VERSION_C != COMDAL_UART_SW_PATCH_VERSION) \
    )
  #error "Software Version Numbers of ComDal_Uart.c and ComDal_Uart.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 /* Check if source file and Std_Types header file are of the same AutoSar version */
 #if ((COMDAL_UART_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
      (COMDAL_UART_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of ComDal_Uart.c and Std_Types.h are different"
 #endif
 /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((COMDAL_UART_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (COMDAL_UART_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of ComDal_Uart.c and Mcal.h are different"
 #endif 
#endif

#if COMDAL_MAX_UART_DESCRIPTORS > 0U
/*=================================================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
===================================================================================================================================*/
typedef enum
{
    UART_INIT  = 0U,          /**< @brief UART channel is of Initialized. */
    UART_BUSY,                /**< @brief UART channel is of Busy.*/
    UART_IDLE,                /**< @brief UART channel is of Idle. */
    UART_ERROR,              /**< @brief  UART channel is in a error state. */
    UART_UNINIT = 255,       /**< @brief UART channel is not initialized. */
} ComDal_UartStateType;

/*=================================================================================================================================
                                       LOCAL CONSTANTS
===================================================================================================================================*/

/*TODO: move these defines to configuration data (ComDal_Cfg.h)*/
/* LINFLEX IPG Clock in Hz*/
#define LIN_IPG_CLK           150000000UL
/* LINFLEX Baudrate */
#define LIN_BAUDRATE        115200UL
/* Calculate LINBRR value by the formula */
#define LINBRR              ((LIN_IPG_CLK / 16 ) / LIN_BAUDRATE)
/* Calculate LINFBRR value by the formula */
#define LINFBRR100_EXACT    (((LIN_IPG_CLK / 16 ) * 100) / LIN_BAUDRATE)
#define LINFBRR             (((LINFBRR100_EXACT - (LINBRR * 100)) * 16) / 100)


#if (USE_LIN_MODULE==STD_ON)
extern CONST(uint32, LIN_CONST) Linflex_au32BaseAddrs[];

#else /*(USE_LIN_MODULE!=STD_ON)*/
CONST(uint32, LIN_CONST) Linflex_au32BaseAddrs[] =
{
    #ifdef  LINFLEX0_BASEADDR
        LINFLEX0_BASEADDR,
    #else
        ((uint32)0x40118000L),
    #endif /* LINFLEX0_BASEADDR */
    #ifdef  LINFLEX1_BASEADDR
        LINFLEX1_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX1_BASEADDR */
    #ifdef  LINFLEX2_BASEADDR
        LINFLEX2_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX2_BASEADDR */
    #ifdef  LINFLEX3_BASEADDR
        LINFLEX3_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX3_BASEADDR */
    #ifdef  LINFLEX4_BASEADDR
        LINFLEX4_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX4_BASEADDR */
    #ifdef  LINFLEX5_BASEADDR
        LINFLEX5_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX5_BASEADDR */
    #ifdef  LINFLEX6_BASEADDR
        LINFLEX6_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX6_BASEADDR */
    #ifdef  LINFLEX7_BASEADDR
        LINFLEX7_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX7_BASEADDR */
    #ifdef  LINFLEX8_BASEADDR
        LINFLEX8_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX8_BASEADDR */
    #ifdef  LINFLEX9_BASEADDR
        LINFLEX9_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX9_BASEADDR */
    #ifdef  LINFLEX10_BASEADDR
        LINFLEX10_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX10_BASEADDR */
    #ifdef  LINFLEX11_BASEADDR
        LINFLEX11_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX11_BASEADDR */
    #ifdef  LINFLEX12_BASEADDR
        LINFLEX12_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX12_BASEADDR */
    #ifdef  LINFLEX13_BASEADDR
        LINFLEX13_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX13_BASEADDR */
    #ifdef  LINFLEX14_BASEADDR
        LINFLEX14_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX14_BASEADDR */
    #ifdef  LINFLEX15_BASEADDR
        LINFLEX15_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX15_BASEADDR */
    #ifdef  LINFLEX16_BASEADDR
        LINFLEX16_BASEADDR,
    #else
        ((uint32)0x00000000UL),
    #endif /* LINFLEX16_BASEADDR */
    #ifdef  LINFLEX17_BASEADDR
        LINFLEX17_BASEADDR
    #else
        ((uint32)0x00000000UL)
    #endif /* LINFLEX17_BASEADDR */
};


/*=================================================================================================================================
                                        LOCAL MACROS
===================================================================================================================================*/

/**
* @brief    IPV_LINFLEX macro definition.
* @details  Generic define for LINFLEX2 IP class.
*/
#define IPV_LINFLEX_00_10_00  (0x00001000UL)

/**
* @brief    IPV_LINFLEX macro definition.
* @details  Generic define for LINFLEX3 IP class.
*/
#define IPV_LINFLEX_03_00_00  (0x00030000UL)

#define IPV_LINFLEX_04_00_00  (0x00040000UL)

/**
* @brief    IPV_LINFLEX macro definition.
* @details  Specific define for LINFLEX3_IPS v5.4.h
*/
#define IPV_LINFLEX_05_04_68  (0x00050468UL)

/* sveral settings of the low level driver depends on the LINFlex IP hw version                   */
/* IPV_LINFLEX_00_10_00 - Spectrum/Bolero implementation                                          */
/* IPV_LINFLEX_03_00_00 - Leopard implementation                                                  */
/* IPV_LINFLEX_xx_xx_xx - ....                                                                    */
/*                                                                                                */
/* IPV_LINFLEX shall be defined in Reg_eSys.h file with the appropriate value                     */
/* because this convention started with Leopard and in order to keep the backward compatibility   */
/* the following 3 lines defines the default value for IPV_LINFLEX                                */
/* the only rule you need to follow is to include Reg_eSys.h before Reg_eSys_LINFlex.h in any     */
/* c source file                                                                                  */
/*#ifndef IPV_LINFLEX
    #error "IPV_LINFLEX not defined" ytza
#endif*/

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access base addresses of LINFlex IPs.
*/
#define LIN_GET_BASE_ADDRESS(offset) ((uint32)( Linflex_au32BaseAddrs[(offset)] ))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Control Register 1 (LINCR1).
*/
#define LINFLEX_LINCR1_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x00uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Interrupt Enable Register (LINIER).
*/
#define LINFLEX_LINIER_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x04uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Status Register (LINSR).
*/
#define LINFLEX_LINSR_ADDR32(offset)     ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x08uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Error Status Register (LINESR).
*/
#define LINFLEX_LINESR_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x0CuL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register UART Mode Control Register (UARTCR).
*/
#define LINFLEX_UARTCR_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x10uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register UART Mode Status Register (UARTSR).
*/
#define LINFLEX_UARTSR_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x14uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Time-Out Control Status Register (LINTCSR).
*/
#define LINFLEX_LINTCSR_ADDR32(offset)   ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x18uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Output Compare Register (LINOCR).
*/
#define LINFLEX_LINOCR_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x1CuL))


/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Fractional Baud Rate Register (LINFBRR).
*/
#define LINFLEX_LINFBRR_ADDR32(offset)   ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x24uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Integer Baud Rate Register (LINIBRR).
*/
#define LINFLEX_LINIBRR_ADDR32(offset)   ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x28uL))


/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register LIN Control Register 2 (LINCR2).
*/
#define LINFLEX_LINCR2_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x30uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register Buffer Identifier Register (BIDR).
*/
#define LINFLEX_BIDR_ADDR32(offset)      ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x34uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register Buffer Data Register Least Significant (BDRL).
*/
#define LINFLEX_BDRL_ADDR32(offset)      ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x38uL))

/**
* @brief    LINFLEX Registers macro definition.
* @details  LINFLEX macro to access register Buffer Data Register Most Significant (BDRM).
*/
#define LINFLEX_BDRM_ADDR32(offset)      ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x3CuL))


/*=============== additional registers for LINFlex3 IP ================================*/
#if IPV_LINFLEX >= IPV_LINFLEX_03_00_00

    /**
    * @brief    LINFLEX Registers macro definition.
    * @details  LINFLEX macro to access register Global control register (GCR).
    */
    #define LINFLEX_GCR_ADDR32(offset)       ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x8CuL))

    /**
    * @brief    LINFLEX Registers macro definition.
    * @details  LINFLEX macro to access register UART preset timeout register (UARTPTO).
    */
    #define LINFLEX_UARTPTO_ADDR32(offset)   ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x90uL))

    /**
    * @brief    LINFLEX Registers macro definition.
    * @details  LINFLEX macro to access register UART current timeout register (UARTCTO).
    */
    #define LINFLEX_UARTCTO_ADDR32(offset)   ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x94uL))

    /**
    * @brief    LINFLEX Registers macro definition.
    * @details  LINFLEX macro to access register DMA Tx enable register (DMATXE).
    */
    #define LINFLEX_DMATXE_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x98uL))

    /**
    * @brief    LINFLEX Registers macro definition.
    * @details  LINFLEX macro to access register DMA Rx enable register (DMARXE).
    */
    #define LINFLEX_DMARXE_ADDR32(offset)    ((uint32)((uint32)( Linflex_au32BaseAddrs[(offset)] ) + 0x9CuL))

#endif
/*=============== end additional registers for LINFlex3 IP ============================*/

/**
* @brief    LINFLEX Registers bits.
* @details  LINCR1 register bit masks.
*/
#define LINFLEX_LINCR1_INIT_MASK_U32          ((uint32)0x00000001UL)
#define LINFLEX_LINCR1_SLEEP_MASK_U32         ((uint32)0x00000002UL)
#define LINFLEX_LINCR1_RBLM_MASK_U32          ((uint32)0x00000004UL)
#define LINFLEX_LINCR1_SSBL_MASK_U32          ((uint32)0x00000008UL)
#define LINFLEX_LINCR1_MME_MASK_U32           ((uint32)0x00000010UL)
#define LINFLEX_LINCR1_LBKM_MASK_U32          ((uint32)0x00000020UL)
#define LINFLEX_LINCR1_BF_MASK_U32            ((uint32)0x00000080UL)
#define LINFLEX_LINCR1_MBL_MASK_U32           ((uint32)0x00000F00UL)
#define LINFLEX_LINCR1_AWUM_MASK_U32          ((uint32)0x00001000UL)
#define LINFLEX_LINCR1_LASE_MASK_U32          ((uint32)0x00002000UL)
#define LINFLEX_LINCR1_CFD_MASK_U32           ((uint32)0x00004000UL)
#define LINFLEX_LINCR1_CCD_MASK_U32           ((uint32)0x00008000UL)
#define LINFLEX_LINCR1_RESET_MASK_U32         ((uint32)0x00000083UL)

#define LINFLEX_LINCR1_RESERVED_MASK_U32      ((uint32)0x00000040UL)

/**
* @brief    LINFLEX Registers bits.
* @details  LIN master break length selection register bit masks.
*/
#define LINFLEX_LINCR1_MBL_10_BITS_MASK_U32   ((uint32)0x00000000UL)
#define LINFLEX_LINCR1_MBL_11_BITS_MASK_U32   ((uint32)0x00000100UL)
#define LINFLEX_LINCR1_MBL_12_BITS_MASK_U32   ((uint32)0x00000200UL)
#define LINFLEX_LINCR1_MBL_13_BITS_MASK_U32   ((uint32)0x00000300UL)
#define LINFLEX_LINCR1_MBL_14_BITS_MASK_U32   ((uint32)0x00000400UL)
#define LINFLEX_LINCR1_MBL_15_BITS_MASK_U32   ((uint32)0x00000500UL)
#define LINFLEX_LINCR1_MBL_16_BITS_MASK_U32   ((uint32)0x00000600UL)
#define LINFLEX_LINCR1_MBL_17_BITS_MASK_U32   ((uint32)0x00000700UL)
#define LINFLEX_LINCR1_MBL_18_BITS_MASK_U32   ((uint32)0x00000800UL)
#define LINFLEX_LINCR1_MBL_19_BITS_MASK_U32   ((uint32)0x00000900UL)
#define LINFLEX_LINCR1_MBL_20_BITS_MASK_U32   ((uint32)0x00000A00UL)
#define LINFLEX_LINCR1_MBL_21_BITS_MASK_U32   ((uint32)0x00000B00UL)
#define LINFLEX_LINCR1_MBL_22_BITS_MASK_U32   ((uint32)0x00000C00UL)
#define LINFLEX_LINCR1_MBL_23_BITS_MASK_U32   ((uint32)0x00000D00UL)
#define LINFLEX_LINCR1_MBL_36_BITS_MASK_U32   ((uint32)0x00000E00UL)
#define LINFLEX_LINCR1_MBL_50_BITS_MASK_U32   ((uint32)0x00000F00UL)

/**
* @brief    LINFLEX Registers bits.
* @details  LINIER register bit masks.
*/
#define LINFLEX_LINIER_HRIE_MASK_U32   ((uint32)0x00000001UL)
#define LINFLEX_LINIER_DTIE_MASK_U32   ((uint32)0x00000002UL)
#define LINFLEX_LINIER_DRIE_MASK_U32   ((uint32)0x00000004UL)
#define LINFLEX_LINIER_DBEIE_MASK_U32  ((uint32)0x00000008UL)
#define LINFLEX_LINIER_DBFIE_MASK_U32  ((uint32)0x00000010UL)
#define LINFLEX_LINIER_WUIE_MASK_U32   ((uint32)0x00000020UL)
#define LINFLEX_LINIER_LSIE_MASK_U32   ((uint32)0x00000040UL)
#define LINFLEX_LINIER_BOIE_MASK_U32   ((uint32)0x00000080UL)
#define LINFLEX_LINIER_FEIE_MASK_U32   ((uint32)0x00000100UL)
#define LINFLEX_LINIER_HEIE_MASK_U32   ((uint32)0x00000800UL)
#define LINFLEX_LINIER_CEIE_MASK_U32   ((uint32)0x00001000UL)
#define LINFLEX_LINIER_BEIE_MASK_U32   ((uint32)0x00002000UL)
#define LINFLEX_LINIER_OCIE_MASK_U32   ((uint32)0x00004000UL)
#define LINFLEX_LINIER_SZIE_MASK_U32   ((uint32)0x00008000UL)

/**
* @brief    LINFLEX Registers bits.
* @details  LINSR register bit masks.
*/
#define LINFLEX_LINSR_HRF_MASK_U32     ((uint32)0x00000001UL)
#define LINFLEX_LINSR_DTF_MASK_U32     ((uint32)0x00000002UL)
#define LINFLEX_LINSR_DRF_MASK_U32     ((uint32)0x00000004UL)
#define LINFLEX_LINSR_DBEF_MASK_U32    ((uint32)0x00000008UL)
#define LINFLEX_LINSR_DBFF_MASK_U32    ((uint32)0x00000010UL)
#define LINFLEX_LINSR_WUF_MASK_U32     ((uint32)0x00000020UL)
#define LINFLEX_LINSR_RPS_MASK_U32     ((uint32)0x00000040UL)
#define LINFLEX_LINSR_RBSY_MASK_U32    ((uint32)0x00000080UL)
#define LINFLEX_LINSR_RMB_MASK_U32     ((uint32)0x00000200UL)
#define LINFLEX_LINSR_LINS_MASK_U32    ((uint32)0x0000F000UL)
#define LINFLEX_LINSR_FLAGS_MASK_U32   ((uint32)0x0000033FUL)

/**
* @brief    LINFLEX LIN states.
* @details  Sleep mode: LINFlex is in Sleep mode to save power consumption.
*
*/
#define LINFLEX_LINSR_SLEEP_MODE_U8          ((uint8)0x00U)

/**
* @brief    LINFLEX LIN states.
* @details  Initialization mode: LINFlex is in Initialization mode.
*
*/
#define LINFLEX_LINSR_INIT_MODE_U8           ((uint8)0x01U)

/**
* @brief    LINFLEX LIN states.
* @details  Idle mode: This state is entered on several events:
*                - SLEEP bit and INIT in LINCR1 register have been cleared by software
*                - A falling edge has been received on RX pin and AWUM bit is set
*                - The previous frame reception or transmission has been completed or aborted.
*
*/
#define LINFLEX_LINSR_IDLE_MODE_U8           ((uint8)0x02U)

/**
* @brief    LINFLEX LIN states.
* @details  Break transmission ongoing.
*
*/
#define LINFLEX_LINSR_BREAK_TX_MODE_U8       ((uint8)0x03U)

/**
* @brief    LINFLEX LIN states.
* @details  Break transmission has been completed.Break Delimiter transmission is ongoing.
*
*/
#define LINFLEX_LINSR_BREAK_DEL_TX_MODE_U8   ((uint8)0x04U)

/**
* @brief    LINFLEX LIN states.
* @details  Synch Field transmission is ongoing.
*
*/
#define LINFLEX_LINSR_SYNC_FIELD_TX_MODE_U8  ((uint8)0x05U)

/**
* @brief    LINFLEX LIN states.
* @details  Identifier transmission is ongoing.
*
*/
#define LINFLEX_LINSR_ID_FIELD_TX_MODE_U8    ((uint8)0x06U)

/**
* @brief    LINFLEX LIN states.
* @details  Header transmission is completed.
*
*/
#define LINFLEX_LINSR_HEADER_TX_MODE_U8      ((uint8)0x07U)

/**
* @brief    LINFLEX LIN states.
* @details  Response reception/transmission is ongoing.
*
*/
#define LINFLEX_LINSR_DATA_RX_TX_MODE_U8     ((uint8)0x08U)

/**
* @brief    LINFLEX LIN states.
* @details  Data reception/transmission completed. Checksum RX/TX ongoing.
*
*/
#define LINFLEX_LINSR_CHECKSUM_RX_TX_MODE_U8 ((uint8)0x09U)

/**
* @brief    LINFLEX LIN states.
* @details  Reset LIN State Interrupt (generated on LIN state change).
*
*/
#define LINFLEX_LINSR_RESET_LSIE_MODE_U8     ((uint8)0x0FU)

/**
* @brief    LINFLEX Registers bits.
* @details  LINESR register bit masks.
*/
#define LINFLEX_LINESR_NF_MASK_U32     ((uint32)0x00000001UL)
#define LINFLEX_LINESR_BOF_MASK_U32    ((uint32)0x00000080UL)
#define LINFLEX_LINESR_FEF_MASK_U32    ((uint32)0x00000100UL)
#define LINFLEX_LINESR_IDPEF_MASK_U32  ((uint32)0x00000200UL)
#define LINFLEX_LINESR_BDEF_MASK_U32   ((uint32)0x00000400UL)
#define LINFLEX_LINESR_SFEF_MASK_U32   ((uint32)0x00000800UL)
#define LINFLEX_LINESR_CEF_MASK_U32    ((uint32)0x00001000UL)
#define LINFLEX_LINESR_BEF_MASK_U32    ((uint32)0x00002000UL)
#define LINFLEX_LINESR_OCF_MASK_U32    ((uint32)0x00004000UL)
#define LINFLEX_LINESR_SZF_MASK_U32    ((uint32)0x00008000UL)
#define LINFLEX_LINESR_FLAGS_MASK_U32  ((uint32)0x0000FF81UL)

/**
* @brief    LINFLEX Registers bits.
* @details  UARTCR register bit masks.
*/
#define LINFLEX_UARTCR_UART_MASK_U32   ((uint32)0x00000001UL)
#if IPV_LINFLEX <= IPV_LINFLEX_00_10_00
    #define LINFLEX_UARTCR_WL_MASK_U32  ((uint32)0x00000002UL)
#elif IPV_LINFLEX >= IPV_LINFLEX_03_00_00
    #define LINFLEX_UARTCR_WL0_MASK_U32 ((uint32)0x00000002UL)
#endif
#define LINFLEX_UARTCR_PCE_MASK_U32    ((uint32)0x00000004UL)
#if IPV_LINFLEX <= IPV_LINFLEX_00_10_00
    #define LINFLEX_UARTCR_OP_MASK_U32 ((uint32)0x00000008UL)
#elif IPV_LINFLEX >= IPV_LINFLEX_03_00_00
    #define LINFLEX_UARTCR_PC_U32     ((uint32)0x00000008UL)
#endif
#define LINFLEX_UARTCR_TXEN_MASK_U32   ((uint32)0x00000010UL)
#define LINFLEX_UARTCR_RXEN_MASK_U32   ((uint32)0x00000020UL)
#if IPV_LINFLEX >= IPV_LINFLEX_03_00_00
    #define LINFLEX_UARTCR_PC1_U32     ((uint32)0x00000040UL)
#endif
#if IPV_LINFLEX <= IPV_LINFLEX_00_10_00
    #define LINFLEX_UARTCR_RDFL_MASK_U32   ((uint32)0x00000C00UL)
    #define LINFLEX_UARTCR_TDFL_MASK_U32   ((uint32)0x00006000UL)
#elif IPV_LINFLEX >= IPV_LINFLEX_03_00_00
    #define LINFLEX_UARTCR_WL1_MASK_U32     ((uint32)0x00000080UL)
    #define LINFLEX_UARTCR_TFBM_MASK_U32    ((uint32)0x00000100UL)
    #define LINFLEX_UARTCR_RFBM_MASK_U32    ((uint32)0x00000200UL)
    #define LINFLEX_UARTCR_RDFLRFC_MASK_U32 ((uint32)0x00001C00UL)
    #define LINFLEX_UARTCR_TDFLTFC_MASK_U32 ((uint32)0x0000E000UL)
#endif

/**
* @brief    UART mode.
* @details  Receiver Data Field length selection.
*/
#define LINFLEX_UARTCR_RX_BUFF_SIZE_1_BYTES_MASK_U32   ((uint32)0x00000000UL)
#define LINFLEX_UARTCR_RX_BUFF_SIZE_2_BYTES_MASK_U32   ((uint32)0x00000400UL)
#define LINFLEX_UARTCR_RX_BUFF_SIZE_3_BYTES_MASK_U32   ((uint32)0x00000800UL)
#define LINFLEX_UARTCR_RX_BUFF_SIZE_4_BYTES_MASK_U32   ((uint32)0x00000C00UL)

/**
* @brief    UART mode.
* @details  Transmitter Data Field length selection.
*/
#define LINFLEX_UARTCR_TX_BUFF_SIZE_1_BYTES_MASK_U32   ((uint32)0x00000000UL)
#define LINFLEX_UARTCR_TX_BUFF_SIZE_2_BYTES_MASK_U32   ((uint32)0x00002000UL)
#define LINFLEX_UARTCR_TX_BUFF_SIZE_3_BYTES_MASK_U32   ((uint32)0x00004000UL)
#define LINFLEX_UARTCR_TX_BUFF_SIZE_4_BYTES_MASK_U32   ((uint32)0x00006000UL)

/**
* @brief    LINFLEX Registers bits.
* @details  UARTSR register bit masks.
*/
#define LINFLEX_UARTSR_NF_MASK_U32     ((uint32)0x00000001UL)
#if IPV_LINFLEX <= IPV_LINFLEX_00_10_00
    #define LINFLEX_UARTSR_DTF_MASK_U32         ((uint32)0x00000002UL)
    #define LINFLEX_UARTSR_DRF_MASK_U32         ((uint32)0x00000004UL)
#elif IPV_LINFLEX >= IPV_LINFLEX_03_00_00
    #define LINFLEX_UARTSR_DTFTFF_MASK_U32      ((uint32)0x00000002UL)
    #define LINFLEX_UARTSR_DRFRFE_MASK_U32      ((uint32)0x00000004UL)
    #define LINFLEX_UARTSR_TO_MASK_U32          ((uint32)0x00000008UL)
#endif
#define LINFLEX_UARTSR_WUF_MASK_U32    ((uint32)0x00000020UL)
#define LINFLEX_UARTSR_RPS_MASK_U32    ((uint32)0x00000040UL)
#define LINFLEX_UARTSR_BOF_MASK_U32    ((uint32)0x00000080UL)
#define LINFLEX_UARTSR_FEF_MASK_U32    ((uint32)0x00000100UL)
#define LINFLEX_UARTSR_RMB_MASK_U32    ((uint32)0x00000200UL)
#define LINFLEX_UARTSR_PE0_MASK_U32    ((uint32)0x00000400UL)
#define LINFLEX_UARTSR_PE1_MASK_U32    ((uint32)0x00000800UL)
#define LINFLEX_UARTSR_PE2_MASK_U32    ((uint32)0x00001000UL)
#define LINFLEX_UARTSR_PE3_MASK_U32    ((uint32)0x00002000UL)
#define LINFLEX_UARTSR_OCF_MASK_U32    ((uint32)0x00004000UL)
#define LINFLEX_UARTSR_SZF_MASK_U32    ((uint32)0x00008000UL)

/**
* @brief    LINFLEX Registers bits.
* @details  LINTCSR register bit masks.
*/
#define LINFLEX_LINTCSR_TOCE_MASK_U32  ((uint32)0x00000100UL)
#define LINFLEX_LINTCSR_IOT_MASK_U32   ((uint32)0x00000200UL)
#define LINFLEX_LINTCSR_LTOM_MASK_U32  ((uint32)0x00000400UL)
#define LINFLEX_LINTCSR_CNT_MASK_U32   ((uint32)0x000000FFUL)
#define LINFLEX_LINTCSR_RESET_MASK_U32 ((uint32)0x00000000UL)

/**
* @brief    LINFLEX Registers bits.
* @details  LINOCR register bit masks.
*/
#define LINFLEX_LINOCR_OC1_MASK_U32    ((uint32)0x000000FFUL)
#define LINFLEX_LINOCR_OC2_MASK_U32    ((uint32)0x0000FF00UL)

/**
* @brief    LINFLEX Registers bits.
* @details  LINTOCR register bit masks.
*/
#define LINFLEX_LINTOCR_RTO_MASK_U32   ((uint32)0x00000F00UL)
#define LINFLEX_LINTOCR_HTO_MASK_U32   ((uint32)0x0000007FUL)

/**
* @brief    LINFLEX Registers bits.
* @details  LINFBRR register bit masks.
*/
#define LINFLEX_LINFBRR_DIV_F_MASK_U32 ((uint32)0x0000000FUL)

/**
* @brief    LINFLEX Registers bits.
* @details  LINIBRR register bit masks.
*/
#if IPV_LINFLEX <= IPV_LINFLEX_00_10_00
    #define LINFLEX_LINIBRR_DIV_M_MASK_U32 ((uint32)0x1FFF0000UL)
#elif ((IPV_LINFLEX >= IPV_LINFLEX_03_00_00) && (IPV_LINFLEX < IPV_LINFLEX_04_00_00))
    #define LINFLEX_LINIBRR_DIV_M_MASK_U32 ((uint32)0xFFFFF000UL)
#elif IPV_LINFLEX >= IPV_LINFLEX_04_00_00
    #define LINFLEX_LINIBRR_DIV_M_MASK_U32 ((uint32)0xFFFFFF00UL)
#endif

/**
* @brief    LINFLEX Registers bits.
* @details  LINCFR register bit masks.
*/
#define LINFLEX_LINCFR_CF_MASK_U32     ((uint32)0x000000FFUL)

/**
* @brief    LINFLEX Registers bits.
* @details  LINCR2 register bit masks.
*/
#define LINFLEX_LINCR2_HTRQ_MASK_U32   ((uint32)0x00000100UL)
#define LINFLEX_LINCR2_ABRQ_MASK_U32   ((uint32)0x00000200UL)
#define LINFLEX_LINCR2_DTRQ_MASK_U32   ((uint32)0x00000400UL)
#define LINFLEX_LINCR2_DDRQ_MASK_U32   ((uint32)0x00000800UL)
#define LINFLEX_LINCR2_WURQ_MASK_U32   ((uint32)0x00001000UL)
#define LINFLEX_LINCR2_IOPE_MASK_U32   ((uint32)0x00002000UL)
#define LINFLEX_LINCR2_IOBE_MASK_U32   ((uint32)0x00004000UL)
#define LINFLEX_LINCR2_TBDE_MASK_U32   ((uint32)0x00008000UL)

/**
* @brief    LINFLEX Registers bits.
* @details  BIDR register bit masks.
*/
#define LINFLEX_BIDR_ID_MASK_U32       ((uint32)0x0000003FUL)
#define LINFLEX_BIDR_CCS_MASK_U32      ((uint32)0x00000100UL)
#define LINFLEX_BIDR_DIR_MASK_U32      ((uint32)0x00000200UL)

#if IPV_LINFLEX >= IPV_LINFLEX_05_04_68
    #define LINFLEX_BIDR_DFL_EXT_MASK_U32  ((uint32)0x00001C00UL)
#else
    #define LINFLEX_BIDR_DFL_EXT_MASK_U32  ((uint32)0x0000FC00UL)
#endif

#define LINFLEX_BIDR_DFL_NOR_MASK_U32  ((uint32)0x00001C00UL)
#define LINFLEX_BIDR_DFL_SET_MASK_U32  ((uint32)0x00000007UL)

/**
* @brief    LINFLEX Registers bits.
* @details  BDRL register bit masks.
*/
#define LINFLEX_BDRL_DATA3_MASK_U32    ((uint32)0xFF000000UL)
#define LINFLEX_BDRL_DATA2_MASK_U32    ((uint32)0x00FF0000UL)
#define LINFLEX_BDRL_DATA1_MASK_U32    ((uint32)0x0000FF00UL)
#define LINFLEX_BDRL_DATA0_MASK_U32    ((uint32)0x000000FFUL)

/**
* @brief    LINFLEX Registers bits.
* @details  BDRM register bit masks.
*/
#define LINFLEX_BDRM_DATA7_MASK_U32    ((uint32)0xFF000000UL)
#define LINFLEX_BDRM_DATA6_MASK_U32    ((uint32)0x00FF0000UL)
#define LINFLEX_BDRM_DATA5_MASK_U32    ((uint32)0x0000FF00UL)
#define LINFLEX_BDRM_DATA4_MASK_U32    ((uint32)0x000000FFUL)
#endif


/*=================================================================================================================================
                                       LOCAL VARIABLES
===================================================================================================================================*/


/*=================================================================================================================================
                                       GLOBAL CONSTANTS
===================================================================================================================================*/
static P2CONST(ComDal_ConfigType, AUTOMATIC, COMDAL_APPL_CONST) ComDal_pUartConfigPtr;

/*=================================================================================================================================
                                       GLOBAL VARIABLES
===================================================================================================================================*/

/**
@brief This is the channel buffer which shall be processed on RX/TX interrupt for each channel. 
       For TX channels this buffer will store data to be trasmited (one element at-the-time) on ISR. 
       For RX channel this buffer filled in by RX ISR and will be read by the ComDal_Uart_ReadData()
       The channel/descriptor buffers are defined in ComDal_PBCfg.c file.
*/
static volatile P2VAR(char, AUTOMATIC, COMDAL_APPL_VAR) ComDal_paUart_Buf[COMDAL_MAX_UART_DESCRIPTORS];

/**
@brief Represents the status of the received message status. 
*/
static volatile ComDal_ReturnType ComDal_Uart_aRxMsgStatus[COMDAL_MAX_UART_DESCRIPTORS];


/**
@brief This is the internal RX buffer which temporary stores data received on RX ISR. When "Cominication has ended"
        character is received (".") the data from this buffer is copied to ComDal_paUart_Buf[ComDal_Uart_acReadBuf[0]]. 
*/
static volatile VAR(char, AUTOMATIC) ComDal_Uart_acReadBuf[COMDAL_UART_MAX_BUFF_SIZE];


/**
@brief This is the Transmition queue. This FIFO will hold all Requests for Tx.
*/
static volatile VAR(ComDal_BswDescriptorIdType, AUTOMATIC) ComDal_Uart_aTxRequestQueue[COMDAL_UART_MAX_REQUESTS];

/**
@brief This is the current index in ongoing transmited message (for the current TX request).
*/
static volatile VAR(uint8, AUTOMATIC) ComDal_Uart_au8CurrentTxByteIndex[COMDAL_UART_MAX_REQUESTS];

/**
@brief This is the data length of the current transmited message (for the current TX request).
*/
static volatile VAR(uint8, AUTOMATIC) ComDal_Uart_au8CurrentTxDataLen[COMDAL_UART_MAX_REQUESTS];


/**
@brief ComDal_Uart_u8TxHead index points to the location from the ComDal_Uart_Tx_Buf for the next char to send
*/
static volatile uint8  ComDal_Uart_u8TxHead = 0U;

/**
@brief ComDal_Uart_u8RxHead index points to the location from the ComDal_paUart_Buf for the next char to send
*/
static volatile uint8  ComDal_Uart_u8RxHead = 0U;
/**
@brief ComDal_Uart_u8TxTail index points to the location from the ComDal_paUart_Buf for the next char to put in the buffer
*/
static volatile uint8  ComDal_Uart_u8TxTail = 0U;
/**
@brief Represents the state of the Uart Tx Line. TX_BUSY if the Uart Tx Line is busy, TX_IDLE if the Uart Tx is idle,  
TX_INIT if the Uart Tx is ready for transition.
*/
static volatile ComDal_UartStateType  ComDal_Uart_eTxState;

/**
@brief Represents the state of the Uart Rx Line. RX_BUSY if the Uart Rx Line is busy, RX_IDLE if the Uart Rx is idle,  
RX_INIT if the Uart Rx is ready for transition.
*/
static volatile ComDal_UartStateType ComDal_Uart_eRxState;


/*=================================================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
===================================================================================================================================*/


/*=================================================================================================================================
                                       LOCAL FUNCTIONS
===================================================================================================================================*/
static FUNC(void, COMDAL_APP_CODE) ComDal_Uart_LLD_Init(void);
static FUNC(void, COMDAL_APP_CODE) ComDal_Uart_LLD_DeInit(void);

/*=================================================================================================================================*/
/**
@brief    ComDal_Uart_LLD_Init  - this internal function is used to create the initial setup the LPUART HW module.
@details

@return None
@retval None

*/
/*=================================================================================================================================*/
static FUNC(void, COMDAL_APP_CODE) ComDal_Uart_LLD_Init()
{
    /*clear UART control register*/
    uint16_t counter =0;
    uint32_t temp_reg = 0;

    /*tx_state = TX_OFF; ytza */

    REG_BIT_CLEAR32(LINFLEX_LINCR1_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_LINCR1_SLEEP_MASK_U32);

    /* prepare for INIT mode */
    REG_BIT_SET32(LINFLEX_LINCR1_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_LINCR1_INIT_MASK_U32);

    /* UART mode enable */
    REG_BIT_SET32(LINFLEX_UARTCR_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_UARTCR_UART_MASK_U32);

    /* word length: 8bits */
#if IPV_LINFLEX <= IPV_LINFLEX_00_10_00
    temp_reg = LINFLEX_UARTCR_WL_MASK_U32;
#elif IPV_LINFLEX == IPV_LINFLEX_03_00_00
    temp_reg = LINFLEX_UARTCR_WL0_MASK_U32;
#else
    temp_reg = 0x2UL;
#endif
    REG_BIT_SET32(LINFLEX_UARTCR_ADDR32(COMDAL_LINFLEX_PORT_PORT), temp_reg);

    for (counter=0;counter < 0x1000; counter++) {};

    /* parity odd */
#if IPV_LINFLEX <= IPV_LINFLEX_00_10_00
    temp_reg = LINFLEX_UARTCR_OP_MASK_U32;
#elif IPV_LINFLEX == IPV_LINFLEX_03_00_00
    temp_reg = LINFLEX_UARTCR_PC0;
#else
    temp_reg = 0x8UL;
#endif
    REG_BIT_SET32(LINFLEX_UARTCR_ADDR32(COMDAL_LINFLEX_PORT_PORT), temp_reg);

    /* parity enable */
    REG_BIT_CLEAR32(LINFLEX_UARTCR_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_UARTCR_PCE_MASK_U32);
    /* write Baudrate registers */
    REG_WRITE32(LINFLEX_LINFBRR_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFBRR);
    REG_WRITE32(LINFLEX_LINIBRR_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINBRR);

#if IPV_LINFLEX <= IPV_LINFLEX_00_10_00
    temp_reg = LINFLEX_UARTCR_RDFL_MASK_U32 | LINFLEX_UARTCR_TDFL_MASK_U32;
#elif IPV_LINFLEX == IPV_LINFLEX_03_00_00
    temp_reg = LINFLEX_UARTCR_RDFLRFC_MASK_U32 | LINFLEX_UARTCR_TDFLTFC_MASK_U32;
#endif

    /* buffer size is 1 byte for transmit */
    /* buffer size is 1 byte for receive */
    REG_BIT_CLEAR32(LINFLEX_UARTCR_ADDR32(COMDAL_LINFLEX_PORT_PORT), temp_reg);

    /* transmit enable */
    /* receive enable */
    REG_BIT_SET32(LINFLEX_UARTCR_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_UARTCR_TXEN_MASK_U32 | LINFLEX_UARTCR_RXEN_MASK_U32);

    /* exit from INIT mode -> NORMAL mode */
    REG_BIT_CLEAR32(LINFLEX_LINCR1_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_LINCR1_INIT_MASK_U32);

	
	/* Enable Rx interrupt */
    REG_BIT_SET32(LINFLEX_LINIER_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_LINIER_DRIE_MASK_U32);	
	
	
}


/*=================================================================================================================================*/
/**
@brief     ComDal_Uart_LLD_DeInit  - this internal function is used to deinitialize the UART driver.
@details

@return None
@retval None

*/
/*=================================================================================================================================*/
static FUNC(void, COMDAL_APP_CODE) ComDal_Uart_LLD_DeInit()
{
    /*Disable TX and RX interrupts*/
    REG_BIT_CLEAR32(LINFLEX_LINIER_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_LINIER_DRIE_MASK_U32 | LINFLEX_LINIER_DTIE_MASK_U32);
	
	
}


/*=================================================================================================================================
                                       GLOBAL FUNCTIONS
===================================================================================================================================*/
ISR(LINFLEX_SCI_Isr_UART_TX);
ISR(LINFLEX_SCI_Isr_UART_RX);


/*=================================================================================================================================*/
/**
@brief   ComDal_Uart_Init() - Initialization function for ComDal_Uart component.
@details This function shall be called during System Initialization to setup UART HW and initalize all
         global data

@param[in]  ConfigPtr    Pointer to configuration data (this data is shared between all CAMDAL components)         
         
@return None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Uart_Init(P2CONST(ComDal_ConfigType, AUTOMATIC, COMDAL_APPL_CONST) ConfigPtr)
{
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) UartDescriptorId = 0U;
    VAR(uint8, AUTOMATIC) BufIndex = 0;

    ComDal_pUartConfigPtr = ConfigPtr;   
    
    for(UartDescriptorId = 0U; UartDescriptorId <  ComDal_pUartConfigPtr->UartChannelCount; UartDescriptorId++)
    {           
        ComDal_paUart_Buf[UartDescriptorId] = (((ComDal_pUartConfigPtr->pUartChanDescriptor)[UartDescriptorId]).pDataBuffer);
        
        ComDal_Uart_aRxMsgStatus[UartDescriptorId] = COMDAL_INVALID;
    }
    
        
    for(BufIndex = 0U; BufIndex < COMDAL_UART_MAX_BUFF_SIZE; BufIndex++)
    {
        ComDal_Uart_acReadBuf[BufIndex] = '\0';
    }
    
    for(BufIndex = 0U; BufIndex < COMDAL_UART_MAX_REQUESTS; BufIndex++)
    {
        ComDal_Uart_aTxRequestQueue[BufIndex] = 255U;
		
        ComDal_Uart_au8CurrentTxByteIndex[UartDescriptorId] = 0;
        
        ComDal_Uart_au8CurrentTxDataLen[UartDescriptorId] = 0;		
    }
        
    ComDal_Uart_LLD_Init(); 

    ComDal_Uart_eTxState = UART_INIT;
    ComDal_Uart_eRxState = UART_INIT;
}


/*=================================================================================================================================*/
/**
@brief   ComDal_Uart_DeInit() - De-Initialization function for ComDal_Uart component.
@details This function shall be called during System Shut-down to disable UART HW and de-initalize all
         global data

@return None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Uart_DeInit()
{
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) UartDescriptorId = 0U;
    VAR(uint8, AUTOMATIC) BufIndex = 0;
    
    for(UartDescriptorId = 0U; UartDescriptorId < COMDAL_MAX_UART_DESCRIPTORS; UartDescriptorId++)
    {           
        ComDal_paUart_Buf[UartDescriptorId] = NULL_PTR;
        
        ComDal_Uart_au8CurrentTxByteIndex[UartDescriptorId] = 0;
        
        ComDal_Uart_au8CurrentTxDataLen[UartDescriptorId] = 0;
        
        ComDal_Uart_aRxMsgStatus[UartDescriptorId] = COMDAL_INVALID;
    }
          
    for(BufIndex = 0U; BufIndex < COMDAL_UART_MAX_BUFF_SIZE; BufIndex++)
    {
        ComDal_Uart_acReadBuf[BufIndex] = '\0';
    }
    
    for(BufIndex = 0U; BufIndex < COMDAL_UART_MAX_REQUESTS; BufIndex++)
    {
        ComDal_Uart_aTxRequestQueue[BufIndex] = 255U;
    }        
        
    ComDal_Uart_LLD_DeInit(); 
    
    ComDal_pUartConfigPtr = NULL_PTR;   
    
    ComDal_Uart_eTxState = UART_UNINIT;
    ComDal_Uart_eRxState = UART_UNINIT;
}



/*=================================================================================================================================*/
/**
@brief      ComDal_Uart_ReadData - API used to provide data that was read from the UART lines.
@details    This function will provide users with the data received on the UART line for the provided
            input channel.
            If the content of the provided ReadBuffer is equal to current content of the channel buffer
            this function shall return  COMDAL_OBSOLETE; if COMDAL was not properly initialized it shall 
            return COMDAL_INVALID. 
            This function shall return COMDAL_NO_ERROR whenever the data received has be updated.
  
@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  UartDataLen    Maximum data length provided for that channel
@param[out] ReadBuffer     Data read from UART for the assigned input channel.

  
@return     ComDal_ReturnType: COMDAL_NO_ERROR, COMDAL_OBSOLETE, COMDAL_INVALID


@pre None
@post None
*/
/*=================================================================================================================================*/
FUNC(ComDal_ReturnType, COMDAL_APP_CODE) ComDal_Uart_ReadData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) ReadBuffer,  VAR(uint8, AUTOMATIC) UartDataLen)
{            
    VAR(uint8, AUTOMATIC) MsgIndex;
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) UartDescriptorId = 0;
    VAR(ComDal_ReturnType, AUTOMATIC) ReturnValue = COMDAL_OBSOLETE;  
    
    if(UART_IDLE == ComDal_Uart_eRxState)
    {
        if(NULL_PTR != ComDal_pUartConfigPtr)
        {
            UartDescriptorId = (ComDal_pUartConfigPtr->pComChannelMap)[ComChannel].ComDescriptorIndex;

            /*check if new message was received*/    
            if(COMDAL_NO_ERROR == ComDal_Uart_aRxMsgStatus[UartDescriptorId])
            {
                /*copy content of the rx buffer to the provided ReadBuffer*/                       
                for(MsgIndex =0; MsgIndex < UartDataLen; MsgIndex++)
                {   
                    ReadBuffer[MsgIndex] = (uint8)ComDal_paUart_Buf[UartDescriptorId][MsgIndex];
                                                           
                    /*clear internal Rx Data */
                    ComDal_paUart_Buf[UartDescriptorId][MsgIndex] = 255;            
                }  

                ComDal_Uart_aRxMsgStatus[UartDescriptorId] = COMDAL_OBSOLETE;
                    
                ReturnValue =  COMDAL_NO_ERROR;                           
            }
        }
        else
        {
            ReturnValue = COMDAL_INVALID;
        }    
    }
    
    return ReturnValue;
}



/*=================================================================================================================================*/
/**
@brief      ComDal_Uart_WriteData - API called from upper layer store a new TX requests and data.
@details    The Tx Queue system works as following:
            - If NO TX message is on going (basically the UART TX line is IDLE) than
                    - create a new request to send UART data for the given channel/descriptor
                    - store TX Data Lenght and Write first data byte on the UART TX register
                    - mark the TX line as BUSY.
                    - Enable Interrupts for TX confirmation.
            - If a TX message is on going (basically there is an active request for TX on a channel)
                    - store the new request in the TX request Queue.
                    - store the data len for the given request.
                    - increment the TxTail index (which marks the current request position in the Queue)
                    - check for buffer/Queue overrun.
                    
@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  UartDataLen    Maximum data length provided for that channel
@param[out] TxDataString   Data to be written on UART for the assigned input channel.

@return     none
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Uart_WriteData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) TxDataString, VAR(uint8, AUTOMATIC) UartDataLen)
{
    volatile VAR(ComDal_BswDescriptorIdType, AUTOMATIC) UartDescriptorId = 0;

    if((NULL_PTR != ComDal_pUartConfigPtr)/* && (TxDataString[0] != '\0')*/)
    {
        SuspendAllInterrupts();/*TODO: add exclusive area --*/ 
        
        /*check if not transmition is ongoing*/
        UartDescriptorId = (ComDal_pUartConfigPtr->pComChannelMap)[ComChannel].ComDescriptorIndex;    
        
        /*copy input data string content to internal buffers*/
        StrLib_StrCpy(TxDataString, (char *)ComDal_paUart_Buf[UartDescriptorId], UartDataLen);
        
        /*insert \n in the last position of the string*/
        StrLib_InsertCharToStr((char *)ComDal_paUart_Buf[UartDescriptorId], '\n', UartDataLen, UartDataLen);
        
        /*check if there are tranmision on going*/
        if(UART_BUSY == ComDal_Uart_eTxState)
        {
            ComDal_Uart_u8TxTail++;            
        
            ComDal_Uart_aTxRequestQueue[ComDal_Uart_u8TxTail] = UartDescriptorId;     
                     
            ComDal_Uart_au8CurrentTxDataLen[ComDal_Uart_u8TxTail] = UartDataLen + 1U;
            
            /* check the tail index from the buffer */
            if(COMDAL_UART_MAX_REQUESTS <= ComDal_Uart_u8TxTail)
            {
                /* adjust if necessary  for overflow*/
                if(0U == ComDal_Uart_u8TxHead)
                {
                    ComDal_Uart_u8TxTail = COMDAL_UART_MAX_REQUESTS - 1;
                }
                else
                {
                    ComDal_Uart_u8TxTail = 0;
                }
            }
            else
            {
                /* buffer full */
                if (ComDal_Uart_u8TxHead == ComDal_Uart_u8TxTail)
                {
                    ComDal_Uart_u8TxTail--;
                }
            }
        }
        else /*no transmision ongoing*/
        {
            /* mark the fact that transmition is ongoing*/
            ComDal_Uart_eTxState = UART_BUSY;
            
            ComDal_Uart_aTxRequestQueue[0] = UartDescriptorId;     
                     
            ComDal_Uart_au8CurrentTxDataLen[0] = UartDataLen + 1U;          
           
            /*set next index of the current transmision byte*/
            ComDal_Uart_au8CurrentTxByteIndex[0] = 1;
            
            /*write TX data register with the fisrt byte of the input data string */
            REG_WRITE32(LINFLEX_BDRL_ADDR32(COMDAL_LINFLEX_PORT_PORT), (uint32)TxDataString[0]);
			
		    /* Enable Tx interrupt */
            REG_BIT_SET32(LINFLEX_LINIER_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_LINIER_DTIE_MASK_U32);	

        } 
        
        ResumeAllInterrupts();/*TODO: add exclusive area --*/
    }
}
#if (LINFLEX_COMMON_INTERRUPT == STD_OFF) /*TODO: define this in ComDal_Uart to on for k2 and off for calypso*/
/*=================================================================================================================================*/
/**
@brief   Uart Tx and Rx ISR Process function.
@details For TX ISR the following activities shall ocur:
            - write next TX data char to HW registers, from the TX buffer for the current index in the tranmision FIFO
            - if all chars from current TX buffer were sent, increment index in the TX FIFO and
            continue with the next TX request untill all requests are done and (head and tail are equal)
            - if TX Queue is empty mark the TX line as IDLE and disable TX Interrupts
		  For RX ISR    the following activities shall ocur:
           - fetch each received byte from HW registers and save it to temporary buffer
           - if EOT char is detected save the content of the temporary buffer to 
           channel buffer.	
         Interrupt flags are cleared imediatly after entering ISR.    

@return None
@retval None

*/
/*=================================================================================================================================*/
ISR(LINFLEX_SCI_Isr_UART_TXRX)
{
    volatile VAR(uint32, AUTOMATIC)  u32Lin_Status;
    volatile VAR(uint32, AUTOMATIC)  u32Lin_EnabledInterrupts;
    volatile VAR(ComDal_BswDescriptorIdType, AUTOMATIC) UartDescriptorId;
    volatile VAR(char, AUTOMATIC)    DataByte;
    volatile VAR(uint8, AUTOMATIC)   MsgIndex;  
    volatile VAR(uint8, AUTOMATIC)   RxMsgId = 0U;
    /* Disable interrupts*/
    SuspendAllInterrupts();/*TODO: add exclusive area --*/
    
	
    u32Lin_Status = REG_READ32(LINFLEX_UARTSR_ADDR32(COMDAL_LINFLEX_PORT_PORT));
		
    u32Lin_EnabledInterrupts = REG_READ32(LINFLEX_LINIER_ADDR32(COMDAL_LINFLEX_PORT_PORT) & (LINFLEX_LINIER_DTIE_MASK_U32 | LINFLEX_LINIER_DRIE_MASK_U32));
	
	
    /*clear pending interrupts*/
    REG_WRITE32(LINFLEX_UARTSR_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_UARTSR_DRF_MASK_U32 | LINFLEX_UARTSR_DTF_MASK_U32);

    /*check if interrupt cause is TX confirmation*/
    if(( LINFLEX_UARTSR_DTF_MASK_U32 == (LINFLEX_UARTSR_DTF_MASK_U32 & u32Lin_Status)) &&
       (LINFLEX_LINIER_DTIE_MASK_U32 == (u32Lin_EnabledInterrupts & LINFLEX_LINIER_DTIE_MASK_U32)))
    {       
        /*get descriptor Id from request queue*/
        UartDescriptorId = ComDal_Uart_aTxRequestQueue[ComDal_Uart_u8TxHead];
                
        /*check if the current message from queue was completly transmited*/            
        if(ComDal_Uart_au8CurrentTxDataLen[ComDal_Uart_u8TxHead] > ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead])
        {
            DataByte = ComDal_paUart_Buf[UartDescriptorId][ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead]];
        
            /*write the next byte on the UART device*/
            REG_WRITE32(LINFLEX_BDRL_ADDR32(COMDAL_LINFLEX_PORT_PORT), (uint32)DataByte);
                
            ComDal_paUart_Buf[UartDescriptorId][ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead]] = 0;    
                
            /*increment index in the current TX buffer */
            ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead]++;
        }
        else
        {
            ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead] = 0U; /*reset current byte counter*/
                        
            /* check if there are other messages queued */
            if(0x0U == (ComDal_Uart_u8TxTail - ComDal_Uart_u8TxHead)) /*no other messages -- head and tail are equal*/
            {                          
                ComDal_Uart_u8TxHead = 0x0U;
                
                ComDal_Uart_u8TxTail = 0x0U;
                
                /* Disable the Tx interrupt */
                REG_BIT_CLEAR32(LINFLEX_LINIER_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_LINIER_DTIE_MASK_U32);
				
                
                ComDal_Uart_eTxState = UART_IDLE;
            }
            else /*there are other messages in queue*/
            {
                /* increment the index in tranmision queue*/
                ComDal_Uart_u8TxHead++;   
                
                /* adjust the head index if necessary */
                if (COMDAL_UART_MAX_REQUESTS <= ComDal_Uart_u8TxHead)
                {
                    ComDal_Uart_u8TxHead = 0x0U;
                }        
            }
        }    
    }
    
    
	/*check if interrupt cause is RX confirmation*/
    if(( LINFLEX_UARTSR_DRF_MASK_U32 == (LINFLEX_UARTSR_DRF_MASK_U32 & u32Lin_Status)) &&
       (LINFLEX_LINIER_DRIE_MASK_U32 == (u32Lin_EnabledInterrupts & LINFLEX_LINIER_DRIE_MASK_U32)))
    {        
        /*store current RX data*/
        ComDal_Uart_acReadBuf[ComDal_Uart_u8RxHead] = (char)(LINFLEX_UARTSR_RMB_MASK_U32 & REG_READ32(LINFLEX_UARTSR_ADDR32(COMDAL_LINFLEX_PORT_PORT)));

        ComDal_Uart_eRxState = UART_BUSY;
        
        /*check if End of Transmision char was received*/
        if(COMDAL_EOT_CHAR == ComDal_Uart_acReadBuf[ComDal_Uart_u8RxHead])
        {
            /*get descriptor ID from first received byte of the current tranmision*/
            RxMsgId = StrLib_Ctoi(ComDal_Uart_acReadBuf[0U]);
                  
            if(NULL_PTR != ComDal_pUartConfigPtr)
            {
                UartDescriptorId =  (ComDal_pUartConfigPtr->pComChannelMap)[(ComDal_pUartConfigPtr->pUartMsgToChannelDescrMap)[RxMsgId]].ComDescriptorIndex;
          
                if(UartDescriptorId < COMDAL_MAX_UART_DESCRIPTORS)
                {
                   /*store RX data to decriptor read buffers*/
                   for(MsgIndex =0; MsgIndex < ComDal_Uart_u8RxHead; MsgIndex++)
                   {
                      ComDal_paUart_Buf[UartDescriptorId][MsgIndex] = ComDal_Uart_acReadBuf[MsgIndex];
                   }
                   
                   ComDal_Uart_aRxMsgStatus[UartDescriptorId] = COMDAL_NO_ERROR; 
                   
                   ComDal_Uart_eRxState = UART_IDLE;                 
                }
                else
                {
                   ComDal_Uart_eRxState = UART_ERROR;
                }   
                
				ComDal_Uart_u8RxHead = 0; /*reset RX index*/                
            }
            else
            {
                ComDal_Uart_eRxState = UART_ERROR;
            }
        }
        else
        {
            ComDal_Uart_u8RxHead++;
        }
    }    
	
	
	/* Enable interrupts */
    ResumeAllInterrupts();/*TODO: add exclusive area --*/
    
    EXIT_INTERRUPT();
}

#else
/*=================================================================================================================================*/
/**
@brief   Uart Tx ISR Process function.
@details For TX ISR the following activities shall ocur:
            - write next TX data char to HW registers, from the TX buffer for the current index in the tranmision FIFO
            - if all chars from current TX buffer were sent, increment index in the TX FIFO and
            continue with the next TX request untill all requests are done and (head and tail are equal)
            - if TX Queue is empty mark the TX line as IDLE and disable TX Interrupts
         Interrupt flags are cleared imediatly after entering ISR.    

@return None
@retval None

*/
/*=================================================================================================================================*/
ISR(LINFLEX_SCI_Isr_UART_TX)
{
    volatile VAR(uint32, AUTOMATIC)  u32Lin_Status;
    volatile VAR(uint32, AUTOMATIC)  u32Lin_EnabledInterrupts;
    volatile VAR(ComDal_BswDescriptorIdType, AUTOMATIC) UartDescriptorId;
    volatile VAR(char, AUTOMATIC)    DataByte;
    volatile VAR(uint8, AUTOMATIC)   MsgIndex;  
    volatile VAR(uint8, AUTOMATIC)   RxMsgId = 0U;
    /* Disable interrupts*/
    SuspendAllInterrupts();/*TODO: add exclusive area --*/
    
	
    u32Lin_Status = REG_READ32(LINFLEX_UARTSR_ADDR32(COMDAL_LINFLEX_PORT_PORT));
		
    u32Lin_EnabledInterrupts = REG_READ32(LINFLEX_LINIER_ADDR32(COMDAL_LINFLEX_PORT_PORT) & LINFLEX_LINIER_DTIE_MASK_U32);
	
	
    /*clear pending interrupts*/
    REG_WRITE32(LINFLEX_UARTSR_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_UARTSR_DTF_MASK_U32);

    /*check if interrupt cause is TX confirmation*/
    if(( LINFLEX_UARTSR_DTF_MASK_U32 == (LINFLEX_UARTSR_DTF_MASK_U32 & u32Lin_Status)) &&
       (LINFLEX_LINIER_DTIE_MASK_U32 == (u32Lin_EnabledInterrupts & LINFLEX_LINIER_DTIE_MASK_U32)))
    {       
        /*get descriptor Id from request queue*/
        UartDescriptorId = ComDal_Uart_aTxRequestQueue[ComDal_Uart_u8TxHead];
                
        /*check if the current message from queue was completly transmited*/            
        if(ComDal_Uart_au8CurrentTxDataLen[ComDal_Uart_u8TxHead] > ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead])
        {
            DataByte = ComDal_paUart_Buf[UartDescriptorId][ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead]];
        
            /*write the next byte on the UART device*/
            REG_WRITE32(LINFLEX_BDRL_ADDR32(COMDAL_LINFLEX_PORT_PORT), (uint32)DataByte);
                
            ComDal_paUart_Buf[UartDescriptorId][ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead]] = 0;    
                
            /*increment index in the current TX buffer */
            ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead]++;
        }
        else
        {
            ComDal_Uart_au8CurrentTxByteIndex[ComDal_Uart_u8TxHead] = 0U; /*reset current byte counter*/
                        
            /* check if there are other messages queued */
            if(0x0U == (ComDal_Uart_u8TxTail - ComDal_Uart_u8TxHead)) /*no other messages -- head and tail are equal*/
            {                          
                ComDal_Uart_u8TxHead = 0x0U;
                
                ComDal_Uart_u8TxTail = 0x0U;
                
                /* Disable the Tx interrupt */
                REG_BIT_CLEAR32(LINFLEX_LINIER_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_LINIER_DTIE_MASK_U32);
				
                
                ComDal_Uart_eTxState = UART_IDLE;
            }
            else /*there are other messages in queue*/
            {
                /* increment the index in tranmision queue*/
                ComDal_Uart_u8TxHead++;   
                
                /* adjust the head index if necessary */
                if (COMDAL_UART_MAX_REQUESTS <= ComDal_Uart_u8TxHead)
                {
                    ComDal_Uart_u8TxHead = 0x0U;
                }        
            }
        }    
    }
  
	/* Enable interrupts */
    ResumeAllInterrupts();/*TODO: add exclusive area --*/
    
    EXIT_INTERRUPT();
}



/*=================================================================================================================================*/
/**
@brief   Uart Rx ISR Process function.
@details For RX ISR    the following activities shall ocur:
           - fetch each received byte from HW registers and save it to temporary buffer
           - if EOT char is detected save the content of the temporary buffer to 
           channel buffer.
         Interrupt flags are cleared imediatly after entering ISR.    

*/
/*=================================================================================================================================*/
ISR(LINFLEX_SCI_Isr_UART_RX)
{
    volatile VAR(uint32, AUTOMATIC)  u32Lin_Status;
    volatile VAR(uint32, AUTOMATIC)  u32Lin_EnabledInterrupts;
    volatile VAR(ComDal_BswDescriptorIdType, AUTOMATIC) UartDescriptorId;
    volatile VAR(char, AUTOMATIC)    DataByte;
    volatile VAR(uint8, AUTOMATIC)   MsgIndex;  
    volatile VAR(uint8, AUTOMATIC)   RxMsgId = 0U;
    /* Disable interrupts*/
    SuspendAllInterrupts();/*TODO: add exclusive area --*/
    
    u32Lin_Status = REG_READ32(LINFLEX_UARTSR_ADDR32(COMDAL_LINFLEX_PORT_PORT));
		
    u32Lin_EnabledInterrupts = REG_READ32(LINFLEX_LINIER_ADDR32(COMDAL_LINFLEX_PORT_PORT) & LINFLEX_LINIER_DRIE_MASK_U32);
	
	
    /*clear pending interrupts*/
    REG_WRITE32(LINFLEX_UARTSR_ADDR32(COMDAL_LINFLEX_PORT_PORT), LINFLEX_UARTSR_DRF_MASK_U32 /*TODO: add RX status interrupt*/);

    /*check if interrupt cause is RX confirmation*/
    if(( LINFLEX_UARTSR_DRF_MASK_U32 == (LINFLEX_UARTSR_DRF_MASK_U32 & u32Lin_Status)) &&
       (LINFLEX_LINIER_DRIE_MASK_U32 == (u32Lin_EnabledInterrupts & LINFLEX_LINIER_DRIE_MASK_U32)))
    {        
        /*store current RX data*/
        ComDal_Uart_acReadBuf[ComDal_Uart_u8RxHead] = (char)(LINFLEX_UARTSR_RMB_MASK_U32 & REG_READ32(LINFLEX_UARTSR_ADDR32(COMDAL_LINFLEX_PORT_PORT)));

        ComDal_Uart_eRxState = UART_BUSY;
        
        /*check if End of Transmision char was received*/
        if(COMDAL_EOT_CHAR == ComDal_Uart_acReadBuf[ComDal_Uart_u8RxHead])
        {
            /*get descriptor ID from first received byte of the current tranmision*/
            RxMsgId = StrLib_Ctoi(ComDal_Uart_acReadBuf[0U]);
                  
            if(NULL_PTR != ComDal_pUartConfigPtr)
            {
                UartDescriptorId =  (ComDal_pUartConfigPtr->pComChannelMap)[(ComDal_pUartConfigPtr->pUartMsgToChannelDescrMap)[RxMsgId]].ComDescriptorIndex;
          
                if(UartDescriptorId < COMDAL_MAX_UART_DESCRIPTORS)
                {
                   /*store RX data to decriptor read buffers*/
                   for(MsgIndex =0; MsgIndex < ComDal_Uart_u8RxHead; MsgIndex++)
                   {
                      ComDal_paUart_Buf[UartDescriptorId][MsgIndex] = ComDal_Uart_acReadBuf[MsgIndex];
                   }
                   
                   ComDal_Uart_aRxMsgStatus[UartDescriptorId] = COMDAL_NO_ERROR; 
                   
                   ComDal_Uart_eRxState = UART_IDLE;                 
                }
                else
                {
                   ComDal_Uart_eRxState = UART_ERROR;
                }   
                
				ComDal_Uart_u8RxHead = 0; /*reset RX index*/                
            }
            else
            {
                ComDal_Uart_eRxState = UART_ERROR;
            }
        }
        else
        {
            ComDal_Uart_u8RxHead++;
        }
    }    
    /* Enable interrupts */
    ResumeAllInterrupts();/*TODO: add exclusive area --*/
    
    EXIT_INTERRUPT();	
}
#endif

/*=================================================================================================================================*/

#endif

#ifdef __cplusplus
}
#endif
/** @} */
