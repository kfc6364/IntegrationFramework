[!NOCODE!]
[!CODE!]
/**
*   @file    ComDal_PbCfg.c
*   @version 0.8.1
*
*   @brief   Integration Framework - IO Driver Abstraction Layer component configuration file
*   @details This file implements the COMDAL configuration interface to application layer.
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
#ifdef __cplusplus
extern "C"{
#endif

[!ENDCODE!]
[!VAR "Comdal_CanDataLen" = "num:i(0)"!]
[!VAR "Comdal_UartDataLen" = "num:i(0)"!]
[!VAR "Comdal_NfcDataLen" = "num:i(0)"!]
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
[!ENDSELECT!]
[!VAR "Comdal_Max_Comdal_chans" = "num:i($Comdal_Max_Can_chans + $Comdal_Max_Eth_chans + $Comdal_Max_Uart_chans + $Comdal_Max_Lin_chans + $Comdal_Max_Nfc_chans)"!]

[!IF "$Comdal_Max_Comdal_chans != num:i('0')"!]
[!CODE!]
/*==================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
 ==================================================================================================*/
#include "ComDal_Drv_Cfg.h"
#include "ComDal_Cfg.h"

/*===================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
====================================================================================================================*/
#define COMDAL_PBCFG_VENDOR_ID_C                       43
#define COMDAL_CFG_MODULE_ID                           100

#define COMDAL_PBCFG_AR_RELEASE_MAJOR_VERSION_C        4
#define COMDAL_PBCFG_AR_RELEASE_MINOR_VERSION_C        3
#define COMDAL_PBCFG_AR_RELEASE_REVISION_VERSION_C     1

#define COMDAL_PBCFG_SW_MAJOR_VERSION_C                0
#define COMDAL_PBCFG_SW_MINOR_VERSION_C                8
#define COMDAL_PBCFG_SW_PATCH_VERSION_C                1

/*===================================================================================================================
*                                     FILE VERSION CHECKS
====================================================================================================================*/
/* Check if source file and ComDal_Cfg.h header file are of the same vendor */
#if (COMDAL_PBCFG_VENDOR_ID_C != COMDAL_CFG_VENDOR_ID)
    #error "ComDal.c and ComDal_Cfg.h have different vendor ids"
#endif

/* Check if source file and ComDal_Cfg.h header file are of the same Autosar version */
#if ((COMDAL_PBCFG_AR_RELEASE_MAJOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_PBCFG_AR_RELEASE_MINOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_PBCFG_AR_RELEASE_REVISION_VERSION_C != COMDAL_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and ComDal_Cfg.h header file are of the same Software version */
#if ((COMDAL_PBCFG_SW_MAJOR_VERSION_C != COMDAL_CFG_SW_MAJOR_VERSION) || \
     (COMDAL_PBCFG_SW_MINOR_VERSION_C != COMDAL_CFG_SW_MINOR_VERSION) || \
     (COMDAL_PBCFG_SW_PATCH_VERSION_C != COMDAL_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal.c and ComDal_Cfg.h are different"
#endif


/* Check if source file and ComDal_Drv_Cfg.h header file are of the same vendor */
#if (COMDAL_PBCFG_VENDOR_ID_C != COMDAL_DRV_CFG_VENDOR_ID)
    #error "ComDal.c and ComDal_Drv_Cfg.h have different vendor ids"
#endif

/* Check if source file and ComDal_Drv_Cfg.h header file are of the same Autosar version */
#if ((COMDAL_PBCFG_AR_RELEASE_MAJOR_VERSION_C != COMDAL_DRV_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_PBCFG_AR_RELEASE_MINOR_VERSION_C != COMDAL_DRV_CFG_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_PBCFG_AR_RELEASE_REVISION_VERSION_C != COMDAL_DRV_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal.c and ComDal_Drv_Cfg.h are different"
#endif

/* Check if source file and ComDal_Drv_Cfg.h header file are of the same Software version */
#if ((COMDAL_PBCFG_SW_MAJOR_VERSION_C != COMDAL_DRV_CFG_SW_MAJOR_VERSION) || \
     (COMDAL_PBCFG_SW_MINOR_VERSION_C != COMDAL_DRV_CFG_SW_MINOR_VERSION) || \
     (COMDAL_PBCFG_SW_PATCH_VERSION_C != COMDAL_DRV_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal.c and ComDal_Drv_Cfg.h are different"
#endif



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
                                       LOCAL VARIABLES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/


[!ENDCODE!]


[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]

[!CODE!]/*COMDAL Channel Buffers*/[!ENDCODE!][!CR!]
[!LOOP "ComDAL/*"!]
    [!VAR "Comdal_DataLen" = "num:i(0)"!]
    [!IF "ComChannelType = 'CAN'"!]
        [!VAR "Comdal_DataLen" = "num:i(substring-before(substring-after(node:value(/AUTOSAR/TOP-LEVEL-PACKAGES/Can/ELEMENTS/Can/CanGeneral/MBDSR),'_'), '_'))"!]
        [!VAR "Comdal_CanDataLen" = "num:i($Comdal_DataLen)"!]
    [!ELSEIF "ComChannelType = 'UART'"!]       
        [!VAR "Comdal_DataLen" = "num:i(node:value(node:path(node:ref(UartHwUnitRef)/../../UartPayloadSize)))"!]
        [!VAR "Comdal_UartDataLen" = "num:i($Comdal_DataLen)"!]
    [!ELSE!]        
        [!VAR "Comdal_DataLen" = "num:i(node:value((node:ref(AnfcChannelRef))/NFCPayloadSize))"!]
        [!VAR "Comdal_NfcDataLen" = "num:i($Comdal_DataLen)"!]    
    [!ENDIF!] 
    [!CODE!]static char ComDal_ChannelDataBuffer_[!"node:current()/@index"!][[!"$Comdal_DataLen"!]];  [!CR!][!ENDCODE!]
[!ENDLOOP!]

[!VAR "CanChannelIndex" = "num:i(0)"!]
[!IF "$Comdal_Max_Can_chans != num:i(0)"!]
[!CODE!]

#if COMDAL_MAX_CAN_CHANNELS_HW_VAR_0 > 0U
/*CAN Channel descriptor*/
static CONST(ComDal_CanDescriptorType, COMDAL_CONST) ComDal_CanChannelDescriptor_HW_VAR_0[[!"$Comdal_Max_Can_chans"!]] =
{ 
[!ENDCODE!]

[!LOOP "ComDAL/*"!]
    [!IF "ComChannelType = 'CAN'"!]
        [!VAR "Comdal_Can_Hw_Controller_Id_Ref" = "node:value(node:ref(node:ref(CanHwObjectRef)/CanControllerRef)/CanControllerId)"!]
        [!VAR "Comdal_Can_Hw_Object_Id_Ref" = "node:name(node:ref(CanHwObjectRef))"!] 
        [!VAR "Comdal_Can_Pdu_Id_Ref" = "node:value(node:ref(CanHwObjectRef)/CanObjectId)"!] 
        [!VAR "Comdal_Can_SwHandle_Id_Ref" = "node:value(node:ref(CanHwObjectRef)/CanObjectId)"!] 

        [!IF "node:value(node:ref(CanHwObjectRef)/CanObjectType) = 'TRANSMIT'"!]
            [!VAR "Comdal_Can_Pooling_Ref" = "node:value(node:ref(node:ref(CanHwObjectRef)/CanControllerRef)/CanTxProcessing)"!]
        [!ELSE!]
            [!VAR "Comdal_Can_Pooling_Ref" = "node:value(node:ref(node:ref(CanHwObjectRef)/CanControllerRef)/CanRxProcessing)"!] 
        [!ENDIF!]

        [!IF "$Comdal_Can_Pooling_Ref = 'POLLING'"!]
           [!VAR "Comdal_Can_Pooling_Val" = "'TRUE'"!]
        [!ELSE!]
           [!VAR "Comdal_Can_Pooling_Val" = "'FALSE'"!]   
        [!ENDIF!] 


[!CODE!]
    /*CAN descriptor [!"$CanChannelIndex"!]*/ 
    {
        ComDal_ChannelDataBuffer_[!"node:current()/@index"!],      /*Data buffer*/
        [!"$Comdal_Can_Hw_Object_Id_Ref"!],             /*Can Hw Object Id*/ 
        [!"$Comdal_Can_Pdu_Id_Ref"!],                               /* Pdu Id */
        [!"$Comdal_Can_SwHandle_Id_Ref"!],                               /*Sw Pdu Handle*/                
        [!"$Comdal_CanDataLen"!],                               /*Can Data Len*/
        [!"$Comdal_Can_Hw_Controller_Id_Ref"!],                               /*controller id*/
        [!"$Comdal_Can_Pooling_Val"!],                            /*Polling*/
    }[!IF "not($CanChannelIndex = num:i($Comdal_Max_Can_chans - 1))"!],[!ENDIF!]
[!ENDCODE!]

        [!VAR "CanChannelIndex" = "num:i($CanChannelIndex + 1)"!]
    [!ENDIF!] [!//ComChannelType = 'CAN'
     
[!ENDLOOP!]
[!CODE!]
};
#endif

[!ENDCODE!]
[!ENDIF!]


[!VAR "UartChannelIndex" = "num:i(0)"!]
[!IF "$Comdal_Max_Uart_chans != num:i(0)"!]
[!CODE!]
#if COMDAL_MAX_UART_CHANNELS_HW_VAR_0 > 0U

/*UART Channel descriptor*/
static CONST(ComDal_UartDescriptorType, COMDAL_CONST) ComDal_UartChannelDescriptor_HW_VAR_0[[!"$Comdal_Max_Uart_chans"!]] =
{ 
[!ENDCODE!]

[!LOOP "ComDAL/*"!]
    [!IF "ComChannelType = 'UART'"!]        
[!CODE!]
    /*UART descriptor [!"$UartChannelIndex"!]*/
    {
        ComDal_ChannelDataBuffer_[!"node:current()/@index"!],      /*Data buffer*/               
        [!"$Comdal_UartDataLen"!],                              /*UART Data Len*/     
    }[!IF "not($UartChannelIndex = num:i($Comdal_Max_Uart_chans - 1))"!],[!ENDIF!]
[!ENDCODE!]

           [!VAR "UartChannelIndex" = "num:i($UartChannelIndex + 1)"!]
    [!ENDIF!] [!//ComChannelType = 'UART'

[!ENDLOOP!]
[!CODE!]
};

[!ENDCODE!]
[!ENDIF!]
[!ENDSELECT!]

[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/AppConfig/*"!]
[!VAR "Vdr_RxMsgCount" = "num:i(count(VirtualDataRouterApp/*/VdrMessageType[.='RX_MESSAGE']))"!]
[!VAR "CanChannelIndex" = "num:i(0)"!]
[!IF "$Vdr_RxMsgCount != num:i(0)"!]
[!CODE!]

/* Uart message to descriptor map*/
static CONST(uint8, COMDAL_CONST) ComDal_UartMsgToDecriptorId_HW_VAR_0[[!"num:i($Vdr_RxMsgCount)"!]] =
{ [!ENDCODE!][!//
    [!LOOP "VirtualDataRouterApp/*"!] 
        [!IF "VdrMessageType = 'RX_MESSAGE'"!]
            [!VAR "Comdal_ChanName" = "node:name(node:ref(ComdalSignalRef)) "!]
            [!VAR "MsgIndex" = "num:i(255)"!] 
            [!LOOP "../../../../BswConfig/*/GeneralConfig/*/ComDAL/*"!]
                [!IF "(node:name(.) = $Comdal_ChanName) and (ComChannelType = 'UART')"!] [!//
                    [!VAR "MsgIndex" = "node:name(.)"!]
                    [!BREAK!]
                [!ENDIF!]
            [!ENDLOOP!]
    [!CODE!] [!"$MsgIndex"!][!IF "not($CanChannelIndex = num:i($Vdr_RxMsgCount - 1))"!],[!ENDIF!] [!ENDCODE!]   [!//
            [!VAR "CanChannelIndex" = "num:i($CanChannelIndex + 1)"!]
        [!ENDIF!]
    [!ENDLOOP!]
[!CODE!]};
[!ENDCODE!]
[!ENDIF!]
[!ENDSELECT!]
[!CODE!]
#endif
[!ENDCODE!]


[!VAR "NfcChannelIndex" = "num:i(0)"!]
[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]
[!IF "$Comdal_Max_Nfc_chans != num:i(0)"!]
[!CODE!]
#if COMDAL_MAX_NFC_CHANNELS_HW_VAR_0 > 0U

/*NFC Channel descriptor*/
static CONST(ComDal_NfcDescriptorType, COMDAL_CONST) ComDal_NfcChannelDescriptor_HW_VAR_0[[!"$Comdal_Max_Nfc_chans"!]] =
{ 
[!ENDCODE!]

[!LOOP "ComDAL/*"!]
    [!IF "ComChannelType = 'NFC'"!]        
[!CODE!]
    /*NFC descriptor [!"$NfcChannelIndex"!]*/
    {
        ComDal_ChannelDataBuffer_[!"node:current()/@index"!],      /*Data buffer*/               
        [!"num:i(node:value((node:ref(AnfcChannelRef))/NFCPayloadSize))"!],                              /*NFC Data Len*/     
    }[!IF "not($NfcChannelIndex = num:i($Comdal_Max_Nfc_chans - 1))"!],[!ENDIF!]
[!ENDCODE!]

           [!VAR "NfcChannelIndex" = "num:i($NfcChannelIndex + 1)"!]
    [!ENDIF!] [!//ComChannelType = 'NFC'

[!ENDLOOP!]
[!CODE!]
};
#endif
[!ENDCODE!]
[!ENDIF!]
[!ENDSELECT!]

[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/BswConfig/*/GeneralConfig/*"!]

[!VAR "CanChannelIndex" = "num:i(0)"!]
[!VAR "UartChannelIndex" = "num:i(0)"!]
[!VAR "NfcChannelIndex" = "num:i(0)"!]
[!VAR "ComdalChannelIndex" = "num:i(0)"!]
[!CODE!]

/*Mapping of BSW Channels to Specific Channel Descriptors*/
static CONST(ComDal_BswChannelMapType, COMDAL_CONST) ComDal_ChannelDescriptorMap_HW_VAR_0[COMDAL_MAX_CHANNELS_HW_VAR_0] = 
{  
[!ENDCODE!]
[!LOOP "ComDAL/*"!]
    [!IF "ComChannelType = 'CAN'"!] 
        [!VAR "Comdal_ChannelType" = "'COMDAL_CAN_CHANNEL'"!]
         
        [!IF "node:value(node:ref(CanHwObjectRef)/CanObjectType) = 'TRANSMIT'"!]
            [!VAR "Comdal_ChannelDirection" = "'COMDAL_TXCHANNEL'"!] 
        [!ELSE!]
            [!VAR "Comdal_ChannelDirection" = "'COMDAL_RXCHANNEL'"!] 
        [!ENDIF!]   
    
        [!VAR "Comdal_SpecificDescriptorIndex" = "$CanChannelIndex"!]
        [!VAR "CanChannelIndex" = "num:i($CanChannelIndex + 1)"!] 
    [!ELSEIF "ComChannelType = 'UART'"!]
        [!VAR "Comdal_ChannelType" = "'COMDAL_UART_CHANNEL'"!]

        [!IF "node:value(node:ref(UartHwUnitRef)/UartSignalDirection) = 'TX_SIGNAL'"!]
            [!VAR "Comdal_ChannelDirection" = "'COMDAL_TXCHANNEL'"!] 
        [!ELSE!]
            [!VAR "Comdal_ChannelDirection" = "'COMDAL_RXCHANNEL'"!] 
        [!ENDIF!]           

        [!VAR "Comdal_SpecificDescriptorIndex" = "$UartChannelIndex"!]
        [!VAR "UartChannelIndex" = "num:i($UartChannelIndex + 1)"!] 
     [!ELSEIF "ComChannelType = 'LIN'"!]
        [!VAR "Comdal_ChannelType" = "'COMDAL_LIN_CHANNEL'"!]
    
     [!ELSEIF "ComChannelType = 'NFC'"!]
      [!VAR "Comdal_ChannelType" = "'COMDAL_NFC_CHANNEL'"!]
        [!VAR "Comdal_ChannelDirection" = "(node:value((node:ref(AnfcChannelRef))/NFCAccessType))"!] 
        [!VAR "Comdal_SpecificDescriptorIndex" = "$NfcChannelIndex"!]
        
        [!VAR "NfcChannelIndex" = "num:i($NfcChannelIndex + 1)"!] 
     [!ELSE!] [!//ETH channel    
    
     [!ENDIF!]

[!CODE!]
    /*[!"node:name(.)"!] -- ComDal channel index [!"node:current()/@index"!]*/
    {
        [!"$Comdal_ChannelType"!],       /*Datatype of current channel*/
        [!"$Comdal_ChannelDirection"!],          /*channel type*/      
        [!"$Comdal_SpecificDescriptorIndex"!]                         /*Index of current channel in own Datatype Channel Descriptor*/
    }[!IF "not($ComdalChannelIndex = num:i($Comdal_Max_Comdal_chans - 1))"!],[!ENDIF!]
[!ENDCODE!]

    [!VAR "ComdalChannelIndex" = "num:i($ComdalChannelIndex + 1)"!]

[!ENDLOOP!]
[!CODE!]    
};
[!ENDCODE!]  

[!ENDSELECT!]

[!CODE!]

CONST(ComDal_ConfigType, COMDAL_CONST) ComDal_Config[COMDAL_MAX_HW_VARIANTS] = 
{    
    {
        [!"$Comdal_Max_Can_chans"!], /*Number of Can channels*/
        [!"$Comdal_Max_Lin_chans"!], /*Number of Lin channels*/
        [!"$Comdal_Max_Eth_chans"!], /*Number of Eth channels*/
        [!"$Comdal_Max_Uart_chans"!], /*Number of Uart  channels*/
        [!"$Comdal_Max_Nfc_chans"!], /*Number of NFC  channels*/  
            
#if COMDAL_MAX_CAN_CHANNELS_HW_VAR_0 > 0U
        ComDal_CanChannelDescriptor_HW_VAR_0,
#endif

#if COMDAL_MAX_LIN_CHANNELS_HW_VAR_0 > 0U
        ComDal_LinChannelDescriptor_HW_VAR_0,
#endif

#if COMDAL_MAX_ETH_CHANNELS_HW_VAR_0 > 0U
        ComDal_EthChannelDescriptor_HW_VAR_0,
#endif

#if COMDAL_MAX_UART_CHANNELS_HW_VAR_0 > 0U
        ComDal_UartChannelDescriptor_HW_VAR_0,
[!IF "$Vdr_RxMsgCount != num:i(0)"!]        ComDal_UartMsgToDecriptorId_HW_VAR_0,[!ELSE!]        NULL_PTR,[!ENDIF!]
#endif

#if COMDAL_MAX_NFC_CHANNELS_HW_VAR_0 > 0U
        ComDal_NfcChannelDescriptor_HW_VAR_0,
#endif

        ComDal_ChannelDescriptorMap_HW_VAR_0
    }    
};

[!ENDCODE!]
[!ENDIF!]
[!CODE!]
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
[!ENDCODE!]
[!ENDNOCODE!]