/**
*   @file        ComDal_Types.h
*   @version     0.8.1
*
*   @brief       AUTOSAR - Integration Framework - Types file for IO Driver Abstraction Layer
*   @details     This file implements the COMDAL Types
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup COMDAL
*   @{
*/
/*=========================================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
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
==============================================================================================================================*/
#ifndef COMDAL_TYPES_H
#define COMDAL_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#include "ComDal_Drv_Cfg.h"

/*==================================================================================================
                                       SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define COMDAL_TYPES_VENDOR_ID                           43
#define COMDAL_TYPES_MODULE_ID                           100

#define COMDAL_TYPES_AR_RELEASE_MAJOR_VERSION            4
#define COMDAL_TYPES_AR_RELEASE_MINOR_VERSION            3
#define COMDAL_TYPES_AR_RELEASE_REVISION_VERSION         1

#define COMDAL_TYPES_SW_MAJOR_VERSION                    0
#define COMDAL_TYPES_SW_MINOR_VERSION                    8
#define COMDAL_TYPES_SW_PATCH_VERSION                    1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if types header file and COMDAL driver configuration header file are of the same vendor */
#if (COMDAL_TYPES_VENDOR_ID != COMDAL_DRV_CFG_VENDOR_ID)
    #error "ComDal_Types.h and ComDal_Drv_Cfg.h have different vendor ids"
#endif

/* Check if types header file and COMDAL driver configuration header file are of the same Autosar version */
#if ((COMDAL_TYPES_AR_RELEASE_MAJOR_VERSION != COMDAL_DRV_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_TYPES_AR_RELEASE_MINOR_VERSION != COMDAL_DRV_CFG_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_TYPES_AR_RELEASE_REVISION_VERSION != COMDAL_DRV_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Types.h and ComDal_Drv_Cfg.h are different"
#endif

/* Check if header file and COMDAL driver configuration header file are of the same software version */
#if ((COMDAL_TYPES_SW_MAJOR_VERSION != COMDAL_DRV_CFG_SW_MAJOR_VERSION) || \
     (COMDAL_TYPES_SW_MINOR_VERSION != COMDAL_DRV_CFG_SW_MINOR_VERSION) || \
     (COMDAL_TYPES_SW_PATCH_VERSION != COMDAL_DRV_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal_Types.h and ComDal_Drv_Cfg.h are different"
#endif

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

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/

typedef enum
{
    COMDAL_CAN_CHANNEL  = 0U,        /**< @brief COMDAL channel is of type CAN. */
    COMDAL_LIN_CHANNEL,                /**< @brief COMDAL channel is of type LIN.*/
    COMDAL_ETH_CHANNEL,                /**< @brief COMDAL channel is of type ETHERNET. */
    COMDAL_UART_CHANNEL,                /**< @brief COMDAL channel is of type UART. */
    COMDAL_NFC_CHANNEL,               /**< @brief COMDAL channel is of type NFC. */
    COMDAL_CHANNEL_INVALID             /**< @brief COMDAL channel is not valid. */
} ComDal_BswChannelType;

typedef enum
{
    COMDAL_RXCHANNEL  = 0U,       /**< @brief UART channel is used for receiving data */
    COMDAL_TXCHANNEL              /**< @brief UART channel is used for transmiting data */
} ComDal_AccessType;

typedef enum
{
    COMDAL_NO_ERROR  = 0U,       /**< @brief channel had detected NO ERROR. */
    COMDAL_OBSOLETE,             /**< @brief channel contains OBSOLETE data (RX data was not update since last read).*/
    COMDAL_INVALID,              /**< @brief channel state is INVALID (COM channel was not properly initialized).*/
    COMDAL_BUSY                  /**< @brief channel is BUSY.*/ 
} ComDal_ReturnType;
/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/

/**
* @brief          ComDal Basic Software channel Id type
* @details        Type used for Bsw ComDal channels;
*/
typedef uint16                                                ComDal_BswDescriptorIdType;

/**
* @brief          ComDal UART Buffer type
* @details        Type used to define UART data buffers;
*/
typedef char                                                 ComDal_UartBufferType;

/**
* @brief          ComDal Basic Software channel Id type
* @details
*/
typedef uint16                                               ComDal_ChannelType;

 #ifdef IFWK_USE_CAN
/**
* @brief          Structure to configure CAN channel descriptors
* @details        Data structure containing the set of configuration parameters required 
*                 for setting up CAN channels.
*/
typedef struct
{ 
  /**< @brief Buffer to store CAN Data for TX or RX data depending on channed direction*/
  P2VAR(char, AUTOMATIC, FW_APPL_DATA)                       pDataBuffer;
  
  /**< @brief Can Hw oject Id*/
  VAR(Can_HwHandleType, AUTOMATIC)                           CanHwObject;
  
  /**< @brief SW Handler Id*/
  VAR(Can_IdType, AUTOMATIC)                                 PduId; 

   /**< @brief Pdu Id*/
  VAR(PduIdType, AUTOMATIC)                                  SwPduHandle; 
  
   /**< @brief Can Data Len*/ 
  VAR(uint8, AUTOMATIC)                                      CanDataLen; 
    
  /**< @brief Can Commnunication handling type for Tx */
  VAR(uint8, AUTOMATIC)                                      CanControllerId;

  /**< @brief Can channel using interrupts or polling */
  VAR(boolean, AUTOMATIC)                                    bPollingEnabled;

} ComDal_CanDescriptorType;
#endif


 #ifdef IFWK_USE_UART
/**
* @brief          Structure to configure UART channel descriptors
* @details        Data structure containing the set of configuration parameters required 
*                 for setting up UART channels.
*/
typedef struct
{  
   
  /**< @brief Buffer to store UART received Data*/
  P2VAR(char, AUTOMATIC,  FW_APPL_DATA)                  pDataBuffer;
  
  /**< @brief UART Data Len*/ 
  VAR(uint8, AUTOMATIC)                                  UartDataLen; 

} ComDal_UartDescriptorType;
#endif
 

/**
* @brief          Structure used for COMDAL channel mapping.
* @details        
*/
typedef struct
{  
  /**< @brief Bsw channel type*/
  CONST(ComDal_BswChannelType, AUTOMATIC)                ComChannelType;
  
    /**< @brief Can channel direction (TX or RX) */
  VAR(ComDal_AccessType, AUTOMATIC)                      AccessType;

  /**< @brief Bsw channel id*/
  CONST(ComDal_BswDescriptorIdType, AUTOMATIC)           ComDescriptorIndex;
 
} ComDal_BswChannelMapType;


#ifdef IFWK_USE_NFC
/**
* @brief          Structure to configure digital channels
* @details        Data structure containing the set of configuration parameters required 
*                 for setting up digital input-output channels.
*/
typedef struct
{  
   
  /**< @brief Buffer to store Nfc received Data*/
  P2VAR(char, AUTOMATIC,  FW_APPL_DATA)                  pDataBuffer;
  
  /**< @brief Nfc Data Len*/ 
  VAR(uint8, AUTOMATIC)                                  DataLen; 

} ComDal_NfcDescriptorType;
#endif

/**
* @brief          Structure containing configuration data for the initialization of COMDAL .
* @details        Data structure containing the set of configuration parameters required
*                 for initializing the COMDAL.
*/
typedef struct
{
    /**< @brief Total number of CAN channels */
    CONST(uint8, AUTOMATIC)                                           CanChannelCount;
    /**< @brief Total number of LIN channels */
    CONST(uint8, AUTOMATIC)                                           LinChannelCount;
    /**< @brief Total number of Ethernet channels */
    CONST(uint8, AUTOMATIC)                                           EthChannelCount;
    /**< @brief Total number of UART channels */
    CONST(uint8, AUTOMATIC)                                           UartChannelCount;
    /**< @brief Total number of NFC channels */
    CONST(uint8, AUTOMATIC)                                           NfcChannelCount;

#ifdef IFWK_USE_CAN
    /**< @brief pointer to CAN channel descriptor*/
    P2CONST(ComDal_CanDescriptorType, AUTOMATIC,  COMDAL_APPL_CONST)  pCanChanDescriptor;
#endif    

#ifdef IFWK_USE_LIN
    /**< @brief pointer to LIN channel descriptor*/
    P2CONST(ComDal_LinDescriptorType, AUTOMATIC,  COMDAL_APPL_CONST)  pLinChanDescriptor;
#endif    

#ifdef IFWK_USE_ETH
    /**< @brief pointer to ETHERNET channel descriptor*/
    P2CONST(ComDal_EthDescriptorType, AUTOMATIC,  COMDAL_APPL_CONST)  pEthChanDescriptor;
#endif

#ifdef IFWK_USE_UART
    /**< @brief pointer to UART channel descriptor*/
    P2CONST(ComDal_UartDescriptorType, AUTOMATIC,  COMDAL_APPL_CONST) pUartChanDescriptor;
    P2CONST(uint8, AUTOMATIC,  COMDAL_APPL_CONST) pUartMsgToChannelDescrMap;
#endif

#ifdef IFWK_USE_NFC
    /**< @brief pointer to NFC channel descriptor*/
    P2CONST(ComDal_NfcDescriptorType, AUTOMATIC,  COMDAL_APPL_CONST) pNfcChanDescriptor;
#endif       
    /**< @brief pointer to COM channel map*/    
    P2CONST(ComDal_BswChannelMapType,  AUTOMATIC, ADC_APPL_CONST) pComChannelMap;

} ComDal_ConfigType;



/*================================================================================================*/
#ifdef __cplusplus
}
#endif

#endif  /* COMDAL_TYPES_H*/
/** @} */

