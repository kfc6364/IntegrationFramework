/**
*   @file    ComDal_Drv_Cfg.h
*   @version 0.8.1
*
*   @brief   Integration Framework - COM Driver Abstraction Layer component low-level configuration file
*   @details This file implements the COMDAL configuration header for connection to low-level drivers.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
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
#ifndef COMDAL_DRV_CFG_H
#define COMDAL_DRV_CFG_H

#ifdef __cplusplus
extern "C"{
#endif


/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
[!NOCODE!]
[!SELECT "IntegrationAppGeneral"!]

[!IF "UseCan = 'true'"!]
[!CODE!]
#define IFWK_USE_CAN
[!ENDCODE!]
[!ENDIF!]
 
[!IF "UseLin = 'true'"!]
[!CODE!]
#define IFWK_USE_LIN
[!ENDCODE!]
[!ENDIF!]

[!IF "UseEth = 'true'"!]
[!CODE!]
#define IFWK_USE_ETH
[!ENDCODE!]
[!ENDIF!]

[!ENDSELECT!]

[!SELECT "IntegrationApp_FeatureList"!]

[!IF "EnableNfc = 'true'"!]
[!CODE!]
#define IFWK_USE_NFC
[!ENDCODE!]
[!ENDIF!]

[!IF "EnableUart   = 'true'"!]
[!CODE!]
#define IFWK_USE_UART
[!ENDCODE!]
[!ENDIF!]

[!ENDSELECT!]
[!ENDNOCODE!]

#ifdef IFWK_USE_CAN
    #include "Can.h"
    #include "Can_GeneralTypes.h"
#endif 

#ifdef IFWK_USE_NFC
    #include "Anfc.h"
#endif 

/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
==================================================================================================*/
#define COMDAL_DRV_CFG_VENDOR_ID                       43

#define COMDAL_DRV_CFG_AR_RELEASE_MAJOR_VERSION        4
#define COMDAL_DRV_CFG_AR_RELEASE_MINOR_VERSION        3
#define COMDAL_DRV_CFG_AR_RELEASE_REVISION_VERSION     1

#define COMDAL_DRV_CFG_SW_MAJOR_VERSION                0
#define COMDAL_DRV_CFG_SW_MINOR_VERSION                8
#define COMDAL_DRV_CFG_SW_PATCH_VERSION                1    
    
/*================================================================================================*/
#ifdef IFWK_USE_NFC
extern Anfc_ConfigType ANFC_PreCompileConfig;
#endif

#ifdef __cplusplus
}
#endif

#endif  /* COMDAL_TYPES_H*/
