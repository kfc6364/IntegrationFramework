[!NOCODE!]
[!CODE!]
/**
*   @file    ComDal_Cfg.h
*   @version 0.8.1
*
*   @brief   Integration Framework - IO Driver Abstraction Layer component configuration file
*   @details This file implements the COMDAL configuration header.
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
#ifndef COMDAL_CFG_H
#define COMDAL_CFG_H

#ifdef __cplusplus
extern "C"{
#endif

[!ENDCODE!]
[!VAR "Comdal_CanDataLen" = "num:i(0)"!]
[!VAR "Comdal_UartDataLen" = "num:i(0)"!]
[!VAR "Comdal_Max_Can_chans" = "num:i(0)"!]
[!VAR "Comdal_Max_Eth_chans" = "num:i(0)"!]
[!VAR "Comdal_Max_Uart_chans" = "num:i(0)"!]
[!VAR "Comdal_Max_Lin_chans" = "num:i(0)"!]
[!VAR "Comdal_Max_Nfc_chans" = "num:i(0)"!]

[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]

[!LOOP "ComDAL/*"!]
   [!IF "ComChannelType = 'CAN'"!]
       [!VAR "Comdal_Max_Can_chans" = "num:i($Comdal_Max_Can_chans + 1)"!]
   [!ELSEIF "ComChannelType = 'UART'"!] 
       [!VAR "Comdal_Max_Uart_chans" = "num:i($Comdal_Max_Uart_chans + 1)"!]
   [!ELSEIF "ComChannelType = 'NFC'"!]
       [!VAR "Comdal_Max_Nfc_chans" = "num:i($Comdal_Max_Nfc_chans + 1)"!]
   [!ELSE!]

   [!ENDIF!] 
[!ENDLOOP!]
[!VAR "Comdal_Max_Comdal_chans" = "num:i($Comdal_Max_Can_chans + $Comdal_Max_Eth_chans + $Comdal_Max_Uart_chans + $Comdal_Max_Lin_chans + $Comdal_Max_Nfc_chans)"!]
[!ENDSELECT!]
[!IF "$Comdal_Max_Comdal_chans != num:i('0')"!]
[!CODE!]
#include "Std_Types.h"
#include "Mcal.h"
#include "ComDal_Types.h"
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#define COMDAL_CFG_VENDOR_ID                       43

#define COMDAL_CFG_AR_RELEASE_MAJOR_VERSION        4
#define COMDAL_CFG_AR_RELEASE_MINOR_VERSION        3
#define COMDAL_CFG_AR_RELEASE_REVISION_VERSION     1

#define COMDAL_CFG_SW_MAJOR_VERSION                0
#define COMDAL_CFG_SW_MINOR_VERSION                8
#define COMDAL_CFG_SW_PATCH_VERSION                1


/*===================================================================================================================
*                                     FILE VERSION CHECKS
====================================================================================================================*/
/* Check if ComDal_Cfg.h header file and ComDal_Types.h header file are of the same vendor */
#if (COMDAL_CFG_VENDOR_ID != COMDAL_TYPES_VENDOR_ID)
    #error "ComDal_Cfg.h and ComDal_Types.h have different vendor ids"
#endif

/* Check if ComDal_Cfg.h header file and ComDal_Types.h header file are of the same Autosar version */
#if ((COMDAL_CFG_AR_RELEASE_MAJOR_VERSION != COMDAL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_CFG_AR_RELEASE_MINOR_VERSION != COMDAL_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_CFG_AR_RELEASE_REVISION_VERSION != COMDAL_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Cfg.h and ComDal_Types.h are different"
#endif

/* Check if ComDal_Cfg.h header file and ComDal_Types.h header file are of the same Software version */
#if ((COMDAL_CFG_SW_MAJOR_VERSION != COMDAL_TYPES_SW_MAJOR_VERSION) || \
     (COMDAL_CFG_SW_MINOR_VERSION != COMDAL_TYPES_SW_MINOR_VERSION) || \
     (COMDAL_CFG_SW_PATCH_VERSION != COMDAL_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal_Cfg.h and ComDal_Cfg.h are different"
#endif


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/

#define    COMDAL_MAX_UART_CHANNELS_HW_VAR_0   [!"$Comdal_Max_Uart_chans"!]U
#define    COMDAL_MAX_UART_DESCRIPTORS         [!"$Comdal_Max_Uart_chans"!]U [!CR!]
    
#define    COMDAL_MAX_CAN_CHANNELS_HW_VAR_0    [!"$Comdal_Max_Can_chans"!]U
#define    COMDAL_MAX_CAN_DESCRIPTORS          [!"$Comdal_Max_Can_chans"!]U [!CR!]
    
#define    COMDAL_MAX_LIN_CHANNELS_HW_VAR_0    [!"$Comdal_Max_Lin_chans"!]U
#define    COMDAL_MAX_LIN_DESCRIPTORS          [!"$Comdal_Max_Lin_chans"!]U [!CR!]

#define    COMDAL_MAX_ETH_CHANNELS_HW_VAR_0    [!"$Comdal_Max_Eth_chans"!]U
#define    COMDAL_MAX_ETH_DESCRIPTORS          [!"$Comdal_Max_Eth_chans"!]U [!CR!]

#define    COMDAL_MAX_NFC_CHANNELS_HW_VAR_0    [!"$Comdal_Max_Nfc_chans"!]U
#define    COMDAL_MAX_NFC_DESCRIPTORS          [!"$Comdal_Max_Nfc_chans"!]U [!CR!]
    
#define    COMDAL_MAX_CHANNELS_HW_VAR_0        [!"num:i($Comdal_Max_Comdal_chans)"!]U

[!ENDCODE!]

[!SELECT "/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/UartDriverConfig/*[1]"!]    

[!VAR "Uart_max_tx_chans" = "num:i(count(UartChannelConfig/*/UartSignalDirection[.='TX_SIGNAL']))"!] 
[!VAR "Uart_clk_value" = "num:i(node:value(node:ref(UartMcuClockRef)/McuClockReferencePointFrequency))"!] 
[!VAR "Uart_boud_value" = "num:i(substring-after(node:value(UartBaudRate),'BR_'))"!] 
[!VAR "Uart_osr_value" = "num:i('7')"!]
[!VAR "Uart_sbr_value" = "num:i('0')"!] 

[!FOR "Uart_osr_value" = "7" TO "num:i('31')"!]

    [!VAR "Uart_sbr_value" = "num:i(($Uart_clk_value div  $Uart_boud_value) div ($Uart_osr_value + num:i(1)))"!] 
     
    [!IF "$Uart_sbr_value < num:i('8191')"!]
         [!BREAK!]  

    [!ENDIF!]         
[!ENDFOR!]

[!IF "$Uart_sbr_value = num:i(0) or $Uart_sbr_value > num:i('8191')"!]
[!CODE!] [!ERROR!] A valid OSR value cannot be found! Input clock value is too small or too big in raport with the desired BourRate value! [!ENDERROR!][!ENDCODE!]               
[!ENDIF!]

[!IF "$Comdal_Max_Uart_chans > num:i(0)"!]
[!CODE!]
#define    COMDAL_LPUART_PORT         [!"node:value(UartHwUnitIndex)"!]U [!CR!]
/* LPUart IPG Clock in Hz*/
#define    LPUART_ASYNCH_CLK           [!"$Uart_clk_value"!]UL  [!CR!]
/* LPUart Baudrate */
#define    LPUART_BAUDRATE             [!"$Uart_boud_value"!]UL   [!CR!]
/* LPUart_OSR */
#define    LPUART_OSR                  [!"$Uart_osr_value"!]UL                    [!CR!]      
/* Calculate LINBRR value by the formula */
#define    LPUART_SBR              ((LPUART_ASYNCH_CLK / LPUART_BAUDRATE) / (LPUART_OSR+1U))  /*SVR value = [!"$Uart_sbr_value"!]*/

#define    COMDAL_UART_MAX_BUFF_SIZE                [!"num:i(node:value(UartPayloadSize))"!]U  [!CR!]
#define    COMDAL_UART_MAX_REQUESTS                 [!"num:i($Uart_max_tx_chans + 1) "!]U     

#define    COMDAL_EOT_CHAR         [!"num:inttohex(num:i(node:value(EndOfMessageChar)))"!]
[!ENDCODE!]
[!ENDIF!]
[!ENDSELECT!]

   
[!CODE!]
#define    COMDAL_MAX_HW_VARIANTS           [!"num:i(count(/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*))"!]U  [!CR!]
[!ENDCODE!]


[!SELECT "IntegrationApp_FeatureList"!]
[!CODE!]

#define    COMDAL_DEV_ERROR_DETECT     [!IF "EnableDevErrorDetect   = 'true'"!] (STD_ON)[!ELSE!]  (STD_OFF)[!ENDIF!] [!CR!]
#define    COMDAL_ENABLE_DEM_REPORT_ERROR_STATUS    (STD_OFF)  [!CR!]
[!ENDCODE!]
[!ENDSELECT!]


[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]

[!CODE!]/*COMDAL Channel Id's*/[!ENDCODE!][!CR!]
[!LOOP "ComDAL/*"!]
[!CODE!]#define    [!"node:name(.)"!]           [!"node:current()/@index"!]U[!CR!][!ENDCODE!]
[!ENDLOOP!]

[!VAR "Comdal_Can_Hw_Controller_Id" = "num:i(0)"!]
[!VAR "Comdal_Can_Hw_Controller_Id_old" = "num:i(0)"!]
[!VAR "Comdal_Can_Hw_Controller_Id_count" = "num:i(0)"!]


[!LOOP "/AUTOSAR/TOP-LEVEL-PACKAGES/Can/ELEMENTS/Can/CanConfigSet/CanController/*"!] 
    [!VAR "Comdal_Can_Hw_Controller_Id" = "node:value(CanControllerId)"!] 
    
    [!LOOP "/AUTOSAR/TOP-LEVEL-PACKAGES/IntegrationFramework/ELEMENTS/IntegrationFramework/IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*[1]/ComDAL/*"!]

        [!IF "ComChannelType = 'CAN'"!]
            [!VAR "Comdal_Can_Hw_Controller_Id_Ref" = "node:value(node:ref(node:ref(CanHwObjectRef)/CanControllerRef)/CanControllerId)"!]
     
            [!IF "$Comdal_Can_Hw_Controller_Id_Ref =  $Comdal_Can_Hw_Controller_Id"!] 
                [!VAR "Comdal_Can_Hw_Controller_Id_count" = "num:i($Comdal_Can_Hw_Controller_Id_count + 1)"!]

                [!BREAK!]
            [!ENDIF!]  

        [!ENDIF!]
    [!ENDLOOP!]
[!ENDLOOP!]

[!IF "$Comdal_Max_Can_chans != num:i(0)"!]
[!CODE!]
#define    COMDAL_MAX_CAN_HW_CONTROLERS              [!CODE!] [!"$Comdal_Can_Hw_Controller_Id_count"!]U [!ENDCODE!]

#define    COMDAL_MAX_CAN_DATALEN                    [!"num:i(substring-before(substring-after(node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Can/ELEMENTS/Can/CanGeneral/MBDSR),'_'), '_'))"!]U

#define    COMDAL_CAN_TRANSMIT_TIMEOUT               [!"node:value(ComDAL/*[1]/ComDalCanTxTimeout)"!]
[!ENDCODE!]
[!ENDIF!]

[!ENDSELECT!]

[!CODE!]

extern const ComDal_ConfigType ComDal_Config[COMDAL_MAX_HW_VARIANTS];
[!ENDCODE!]
[!ENDIF!]
[!CODE!]
/*================================================================================================*/
#ifdef __cplusplus
}
#endif

#endif  /* COMDAL_TYPES_H*/
[!ENDCODE!]
[!ENDNOCODE!]