/**
*   @file    SwcRte_PBcfg.c
*   @version 0.8.1
*
*   @brief   Integration Framework - Swc Rte Glue-layer configuration source file
*   @details This file implements the RTE configuration source file.
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

/**
* @page misra_violations MISRA-C:2004 violations
*
* @section [global]
*     Violates MISRA 2004 Required Rule 5.1, Identifiers (internal and external) shall not rely
*     on the significance of more than 31 characters. The used compilers use more than 31 chars for
*     identifiers.
*
*/

[!IF "(IntegrationApp_FeatureList/EnableLightingApp = 'true') or (IntegrationApp_FeatureList/EnableVdrApp = 'true')"!]
/*==================================================================================================
*                                        INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "typedefs.h"
#include "SwcRte_Cfg.h"
#include "SwcRte_Types.h"

#if (SWCRTE_USE_IODAL == SWCRTE_STD_ON)
    #include "IoDal_Cfg.h"
#endif

#if (SWCRTE_USE_COMDAL == SWCRTE_STD_ON)
    #include "ComDal_Cfg.h"
#endif
/*==================================================================================================
*                              SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define SWCRTE_VENDOR_ID_PBCFG_C                      43

#define SWCRTE_SW_MAJOR_VERSION_PBCFG_C               0
#define SWCRTE_SW_MINOR_VERSION_PBCFG_C               8
#define SWCRTE_SW_PATCH_VERSION_PBCFG_C               1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
/* Check if SwcRte_PBcfg.c file and SwcRte_Types.h header file are of the same vendor */
#if ( SWCRTE_VENDOR_ID_PBCFG_C != SWCRTE_CFG_VENDOR_ID)
    #error "SwcRte_PBcfg.c and SwcRte_Cfg.h have different vendor ids"
#endif

/* Check if SwcRte_PBcfg.c and SwcRte_Cfg.h header files are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_PBCFG_C != SWCRTE_CFG_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_PBCFG_C != SWCRTE_CFG_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_PBCFG_C != SWCRTE_CFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of SwcRte_PBcfg.c and SwcRte_Cfg.h are different"
#endif

/* Check if SwcRte_PBcfg.c file and SwcRte_Types.h header file are of the same vendor */
#if ( SWCRTE_VENDOR_ID_PBCFG_C != SWCRTE_TYPES_VENDOR_ID)
    #error "SwcRte_PBcfg.c and SwcRte_Types.h have different vendor ids"
#endif

/* Check if SwcRte_PBcfg.c and SwcRte_Types.h header files are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_PBCFG_C != SWCRTE_TYPES_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_PBCFG_C != SWCRTE_TYPES_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_PBCFG_C != SWCRTE_TYPES_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of SwcRte_PBcfg.c and SwcRte_Types.h are different"
#endif

#if (SWCRTE_USE_IODAL == SWCRTE_STD_ON)
/* Check if SwcRte_PBcfg.c file and SwcRte_Types.h header file are of the same vendor */
#if ( SWCRTE_VENDOR_ID_PBCFG_C != IODAL_CFG_VENDOR_ID)
    #error "SwcRte_PBcfg.c and IoDal_Cfg.h have different vendor ids"
#endif

/* Check if SwcRte_PBcfg.c and IoDal_Cfg.h header files are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_PBCFG_C != IODAL_CFG_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_PBCFG_C != IODAL_CFG_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_PBCFG_C != IODAL_CFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of SwcRte_PBcfg.c and IoDal_Cfg.h are different"
#endif
#endif

#if (SWCRTE_USE_COMDAL == SWCRTE_STD_ON)
/* Check if SwcRte_PBcfg.c file and SwcRte_Types.h header file are of the same vendor */
#if ( SWCRTE_VENDOR_ID_PBCFG_C != COMDAL_CFG_VENDOR_ID)
    #error "SwcRte_PBcfg.c and ComDal_Cfg.h have different vendor ids"
#endif

/* Check if SwcRte_PBcfg.c and IoDal_Cfg.h header files are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_PBCFG_C != COMDAL_CFG_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_PBCFG_C != COMDAL_CFG_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_PBCFG_C != COMDAL_CFG_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of SwcRte_PBcfg.c and ComDal_Cfg.h are different"
#endif
#endif
/*==================================================================================================
*                                      GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                       LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

/*==================================================================================================
*                                      GLOBAL CONSTANTS
==================================================================================================*/

[!AUTOSPACING!]
[!NOCODE!]

[!SELECT "IntegrationAppFeaturesConfig/IntegrationAppDataConfig/*/AppConfig/*"!]
    [!VAR "VDR_InstanceCount" = "num:i(count(VirtualDataRouterApp/*))"!]    
    [!VAR "LI_InstanceCount" = "num:i(count(LightingControlApp/*))"!]    
    [!VAR "MC_InstanceCount" = "num:i(count(MotorControlApp/*))"!] 
    [!VAR "All_InstanceCount" = "num:i($VDR_InstanceCount + $LI_InstanceCount + $MC_InstanceCount)"!]    
    [!VAR "NumberLightingInstances" = "num:i(0)"!]
    [!VAR "Vdr_RxMsgCount" = "num:i(0)"!]
    [!VAR "Vdr_TxMsgCount" = "num:i(0)"!]

    [!LOOP "VirtualDataRouterApp/*"!]
        [!IF "VdrMessageType = 'RX_MESSAGE'"!]
            [!VAR "Vdr_RxMsgCount" = "$Vdr_RxMsgCount + 1"!]
        [!ELSE!]    
            [!VAR "Vdr_TxMsgCount" = "$Vdr_TxMsgCount + 1"!]
        [!ENDIF!]      [!// VdrSignalDirection!= 'RX_REPLY'

        [!IF "(VdrMessageType = 'TX_REPLY') or ((VdrMessageType = 'TX_MESSAGE') and (VdrMessageScope = 'APP_EVENT_NOTIFICATION'))"!] 
            [!VAR "ComTxDataLen" = "node:value(DefaultDataLength)"!]
            
[!CODE!]
SwcRte_DataMessageType SwcRte_VdrTxMessage_[!"num:i(VdrMessageId)"!][[!"num:i($ComTxDataLen)"!]];
[!ENDCODE!]        
        [!ENDIF!]       [!// VdrSignalDirection = 'TX_REPLY'


        [!IF "(VdrMessageType = 'TX_MESSAGE')"!]
            [!IF "(VdrMessageScope = 'APP_EVENT_FORWARD_MSG')"!]
                [!VAR "ComTxDataLen" = "node:value(DefaultDataLength)"!]
                [!VAR "Vdr_TxDefaultData" = "node:value(DefaultTxData)"!]
                [!VAR "Vdr_TxStringData" = "$Vdr_TxDefaultData"!]
                [!VAR "DataTxData" = "text:split($Vdr_TxDefaultData, ',')"!]
                [!VAR "StringLen" = "string-length($Vdr_TxDefaultData)"!]

                [!FOR "idx" = "1" TO "$StringLen - 2"!]
                    [!VAR "DataByIndex" = "$Vdr_TxDefaultData/*[position()=$idx]"!]
                    [!VAR "DataByIndex1" = "$Vdr_TxDefaultData/*[position()=($idx+1)]"!]
                    [!VAR "DataByIndex2" = "$Vdr_TxDefaultData/*[position()=($idx+2)]"!]
                 
                    [!IF "($DataByIndex = '44')"!] [!//44 is the ascii code for ','
                        [!IF "($DataByIndex1 = '48') and ($DataByIndex2 != '44')"!] [!//44 is the ascii code for ','
                            [!IF "($DataByIndex2 != '0')"!]
[!CODE!]                         
    [!ERROR!] The data string may only use integer data. Char [!"num:i($DataByIndex1 - 48)"!][!"num:i($DataByIndex2 - 48)"!] - at index [!"num:i($idx + 1)"!] is not valid![!ENDERROR!]                     
[!ENDCODE!]                          
                            [!ENDIF!]
                        [!ENDIF!]
                    [!ENDIF!]
                [!ENDFOR!]
           
                [!VAR "ActualStringLength" = "num:i(0)"!]
                [!VAR "CommaIndexFirst" = "num:i(0)"!]
                [!VAR "CommaIndexLast" = "num:i(0)"!]
                [!FOR "idx" = "1" TO "$StringLen"!]
                    [!VAR "DataByIndex" = "$Vdr_TxDefaultData/*[position()=$idx]"!]
                    [!VAR "DataByIndex1" = "$Vdr_TxDefaultData/*[position()=$idx+1]"!]

                    [!IF "($DataByIndex != '44')"!]  [!//check if the current char is not ',' (ascii code for ',' is 44)
                         [!IF "($DataByIndex < '48') or ($DataByIndex > '57')"!]
[!CODE!]  
    [!ERROR!] Data value is not a number. Char at index [!"num:i($idx + 1)"!] is not valid! [!ENDERROR!]
[!ENDCODE!]                     
                         [!ENDIF!]
                    [!ELSE!]
                         [!IF "($DataByIndex1 > '48') or ($DataByIndex1 < '57')"!]  [!//check if the current char is a number between 0 - 9
                             [!VAR "ActualStringLength" = "$ActualStringLength + 1"!]
                             [!VAR "CommaIndexLast" = "$idx"!]
                             [!VAR "CommaIndexDiff" = "$CommaIndexLast - $CommaIndexFirst - 1"!]
                             [!VAR "CalcNumber" = "num:i(0)"!]
                             [!VAR "Multiplier" = "num:i(1)"!]
                             [!VAR "intIdx" = "$idx - 1"!]
                         
                             [!FOR "chidx" = "$idx - $CommaIndexDiff"  TO "$idx - 1"!]
                                 [!VAR "charByIndex" = "($Vdr_TxDefaultData/*[position()=$intIdx] - 48)"!]
                                 [!VAR "CalcNumber" = "$CalcNumber  + ($charByIndex * $Multiplier)"!]
                                 [!VAR "Multiplier" = "num:i($Multiplier  * 10)"!]
                                 [!VAR "intIdx" = "$intIdx - 1"!]
                             [!ENDFOR!]

                             [!IF "$CalcNumber > num:i(255)"!]
[!CODE!]
   [!ERROR!] Char at index [!"num:i($ActualStringLength - 1)"!] is not valid! Data value is not unsigned char type value ([!"num:i($CalcNumber)"!]) > 255!  [!ENDERROR!]     
[!ENDCODE!]
                             [!ENDIF!] [!//check CalcNumber > 255

                             [!VAR "CommaIndexFirst" = "$CommaIndexLast"!]
                         [!ENDIF!] [!//check data is number
                     [!ENDIF!]
                 [!ENDFOR!] [!//idx = 1 TO StringLen

                 [!VAR "ActualStringLength" = "$ActualStringLength + 1"!]
                 [!VAR "CalcNumber" = "num:i(0)"!]
                 [!VAR "Multiplier" = "num:i(1)"!]
                 [!VAR "intIdx" = "$StringLen"!]

                 [!FOR "chidx" = "$CommaIndexLast + 1"  TO "$StringLen"!] [!//validate the last data index
                     [!VAR "charByIndex" = "($Vdr_TxDefaultData/*[position()=$intIdx] - 48)"!]
                     [!VAR "CalcNumber" = "$CalcNumber  + ($charByIndex * $Multiplier)"!]
                     [!VAR "Multiplier" = "num:i($Multiplier  * 10)"!]
                     [!VAR "intIdx" = "$intIdx - 1"!]
                 [!ENDFOR!]

                 [!IF "$CalcNumber > num:i(255)"!]
[!CODE!]
    [!ERROR!] Char at index [!"num:i($ActualStringLength - 1)"!] is not valid! Data value is not unsigned char type value ([!"$CalcNumber"!]) > 255!  [!ENDERROR!]
[!ENDCODE!]
                 [!ENDIF!]

                 [!IF "($ActualStringLength > ($ComTxDataLen - 1))"!]
[!CODE!]                 
    [!ERROR!] Default Data String Length should be equal to Default Data Lenght ([!"$ComTxDataLen"!]) minus 1! [!ENDERROR!]
[!ENDCODE!] 
                 [!ENDIF!]

                 [!//format TX data string by adding Message ID and Message Type to first and second TX data Index        
                 [!VAR "msgIdByte" = "string(VdrMessageId)"!]        
                 [!VAR "msgTypeByte" = "'SCWRTE_TX_SEND_MSG'"!]
[!CODE!]
SwcRte_DataMessageType SwcRte_VdrTxMessage_[!"num:i(VdrMessageId)"!][[!"$ComTxDataLen"!]] = {[!"$msgIdByte"!],  [!"substring(substring-before($DataTxData ,']'), 2)"!]};
[!ENDCODE!]
            [!ENDIF!]  [!// VdrMessageScope = 'APP_EVENT_FORWARD_MSG'
        [!ENDIF!]  [!// VdrSignalDirection = 'TX_MESSAGE'
    [!ENDLOOP!]  [!// VirtualDataRouterApp/*
    
    
    
    [!// INPUTS FOR LIGHTING APP
    [!LOOP "LightingControlApp/*"!]
        [!VAR "LI_ChannelCount" = "num:i(count(LightingChannels/*))"!]
        [!VAR "LI_ChannelIndex" = "num:i(0)"!]
        [!VAR "LI_FeedbackIndex" = "0"!]
[!CODE!]

/*array of configuration data containing the configuration for each input channel (sensors and feedback channels) for instance [!"num:i($NumberLightingInstances)"!]*/
const SwcRte_InputChannelConfigType SwcRte_LightingInputChannelMap_[!"num:i($NumberLightingInstances)"!]_PB[[!"num:i($LI_ChannelCount +1)"!]] = 
{
    /*Sensor channel*/
    {
[!ENDCODE!]
       [!IF "LightCtrlUserInterface/LightCtrlInputSignalType = 'DIGITAL_INPUT'"!]
           [!VAR "ChannelRef" = "node:name(node:ref(LightCtrlUserInterface/LightControlInput))"!]
           [!VAR "ChannelType" = "'SWCRTE_DIGITAL_SENS'"!]
       [!ELSEIF "LightCtrlUserInterface/LightCtrlInputSignalType = 'ANALOG_INPUT'"!]
           [!VAR "ChannelRef" = "node:name(node:ref(LightCtrlUserInterface/LightControlInput))"!]
           [!VAR "ChannelType" = "'SWCRTE_ANALOG_POT_SENS'"!]
       [!ELSE!]
           [!VAR "ChannelRef" = "num:i(255)"!]
           [!VAR "ChannelType" = "'SWCRTE_COM_DATA_INPUT'"!]
       [!ENDIF!]
[!CODE!]
        [!"$ChannelRef"!],    /*IO Channel ID*/
        [!"$ChannelType"!]        /*IO Channel Type*/
    }[!IF "not(num:i(count(LightingChannels/*)) = num:i(0))"!],[!ENDIF!][!//
[!ENDCODE!]
        [!LOOP "LightingChannels/*"!]
             [!IF "ChannelHasFeedback = 'true'"!]
                 [!VAR "LI_FeedbackIndex" = "$LI_FeedbackIndex+1"!]
                 [!VAR "ChannelRef" = "concat(node:name(node:ref(LightFeedbackChannel)), ',        /*IO Channel ID*/')"!]
                 [!VAR "ChannelType" = "concat('SWCRTE_ANALOG_FDBK_SENS', '        /*IO Channel Type*/')"!]
             [!ELSE!]
                 [!VAR "ChannelRef" = "concat(num:i(255),',        /*Channel has no configured feedback, thus no input channel*/')"!]
                 [!VAR "ChannelType" = "'SWCRTE_NO_SENS'"!]
             [!ENDIF!]
[!CODE!]
    
    /*feedback channel for channel [!"num:i($LI_ChannelIndex)"!]*/
    {
        [!"$ChannelRef"!]
        [!"$ChannelType"!]
    }[!IF "not($LI_ChannelIndex = num:i(count(../../LightingChannels/*)-1))"!],[!ENDIF!][!CR!]
[!ENDCODE!]
             [!VAR "LI_ChannelIndex" = "num:i($LI_ChannelIndex + 1)"!]
        [!ENDLOOP!]
        [!VAR "NumberLightingInstances" = "$NumberLightingInstances + 1"!] 
[!CODE!]
            
};            
[!ENDCODE!]
    [!ENDLOOP!]
       
    [!VAR "NumberLightingInstances" = "num:i(0)"!]
[!// OUTPUTS FOR LIGHTING APP
    [!LOOP "LightingControlApp/*"!]
        [!VAR "LI_ChannelCount" = "num:i(count(LightingChannels/*))"!]
        [!VAR "LI_ChannelIndex" = "0"!]
        [!IF "not($LI_ChannelCount = num:i(0))"!]
[!CODE!]

const SwcRte_OutputChannelConfigType SwcRte_LightingOutputChannelMap_[!"num:i($NumberLightingInstances)"!]_PB[[!"num:i($LI_ChannelCount)"!]] = 
{[!//
[!ENDCODE!]
        [!LOOP "LightingChannels/*"!]
            [!VAR "ChannelRef" = "node:name(node:ref(LightOutputChannel))"!]
           
[!CODE!]
        
    /*Output Channel [!"num:i($LI_ChannelIndex)"!]*/
    {
        [!"$ChannelRef"!]    /*IO Channel ID*/
    }[!IF "not(num:i($LI_ChannelIndex + 1) = $LI_ChannelCount)"!],[!ENDIF!][!CR!][!//
[!ENDCODE!]
        [!VAR "LI_ChannelIndex" = "num:i($LI_ChannelIndex + 1)"!][!//
        [!ENDLOOP!][!//
[!CODE!]

};
[!ENDCODE!]
        [!VAR "NumberLightingInstances" = "$NumberLightingInstances + 1"!] 
    [!ELSE!]
        [!ERROR!]
            "No configured channels for Lighting instance [!"num:i($NumberLightingInstances)"!]. "
        [!ENDERROR!]
    [!ENDIF!]
    [!ENDLOOP!]


    [!IF "not($Vdr_RxMsgCount = num:i(0))"!]
[!CODE!]

/*RX Message List*/
const SwcRte_MessgeRxBuffConfigType SwcRte_RxMessageList_PB[[!"num:i($Vdr_RxMsgCount)"!]] = 
{[!// 
[!ENDCODE!]
        [!FOR "RxMsgIdx" = "num:i(0)"  TO "num:i($Vdr_RxMsgCount - 1)"!] 
            [!LOOP "VirtualDataRouterApp/*"!]
                [!VAR "ComTxReplyId" = "num:i(0)"!]
                [!VAR "ComRxDataLen" = "num:i(0)"!]
                [!IF "VdrMessageType = 'RX_MESSAGE'"!]
                    [!VAR "ComChannelRef" = "node:name(node:ref(ComdalSignalRef))"!]

                    [!IF "VdrMessageScope != 'APP_REQUEST_OUTPUT_UPDATE'"!]                       
                        [!VAR "ComTxReplyId" = "node:value(node:ref(ReplaySignalRef)/VdrMessageId)"!]                   
                    [!ELSE!]                        
                        [!VAR "ComTxReplyId" = "num:i(255)"!]                   
                    [!ENDIF!]

                    [!IF "num:i($RxMsgIdx) = num:i(VdrMessageId)"!]   
[!CODE!][!//
    /*RX Message [!"num:i(VdrMessageId)"!]*/
    {
        [!"$ComChannelRef"!],    /*COMDAL Channel ID*/
        [!"$ComTxReplyId"!],           /*Tx Replay Message ID*/
        [!"DefaultDataLength"!]           /*Rx Data Length*/
    }[!IF "num:i($RxMsgIdx) < num:i($Vdr_RxMsgCount - 1)"!],[!ENDIF!][!CR!]

[!ENDCODE!]  
                    [!ENDIF!]                   
                [!ENDIF!]   
            [!ENDLOOP!]
        [!ENDFOR!]
[!CODE!]
};
[!ENDCODE!]   
    [!ENDIF!]  [!// END if not($Vdr_RxMsgCount = num:i(0))
       
    
    [!IF "not($Vdr_TxMsgCount = num:i(0))"!]

[!CODE!]

/*TX Message List*/
const SwcRte_MessgeTxBuffConfigType SwcRte_TxMessageList_PB[[!"num:i($Vdr_TxMsgCount)"!]] = 
{
[!ENDCODE!]
        [!FOR "TxMsgIdx" = "num:i(0)"  TO "num:i($Vdr_TxMsgCount - 1)"!]    
            [!LOOP "VirtualDataRouterApp/*"!]   
                [!VAR "ComTxReplyId" = "num:i(0)"!]    
                [!VAR "ComTxDataLen" = "num:i(0)"!]
   
                [!IF "VdrMessageType != 'RX_MESSAGE'"!]     [!//  VdrSignalDirection = 'TX_MESSAGE' or 'TX_REPLY'
                    [!IF "VdrMessageScope = 'APP_EVENT_FORWARD_MSG'"!]
                        [!VAR "ComTxType" = "'SCWRTE_TX_SEND_MSG'"!]                   
                    [!ELSE!] 
                        [!IF "VdrMessageScope = 'APP_EVENT_NOTIFICATION'"!]
                             [!VAR "ComTxType" = "'SCWRTE_TX_ON_EVENT'"!]
                        [!ELSE!]
                              [!VAR "ComTxType" = "'SCWRTE_TX_ON_REQUEST'"!] 
                        [!ENDIF!]
                    [!ENDIF!]

                    [!VAR "ComChannelRef" = "node:name(node:ref(ComdalSignalRef))"!]

                    [!IF "num:i($TxMsgIdx) = num:i(VdrMessageId)"!]   
[!CODE!][!//
    /*TX Message [!"num:i(VdrMessageId)"!]*/
    {
        [!"$ComTxType"!],         /*TX message Type*/
        [!"$ComChannelRef"!],    /*COMDAL Channel ID*/
        [!"DefaultDataLength"!],          /*Rx Data Length*/
        SwcRte_VdrTxMessage_[!"num:i(VdrMessageId)"!] 
    }[!IF "num:i($TxMsgIdx) < num:i($Vdr_TxMsgCount - 1)"!],[!ENDIF!][!CR!]

[!ENDCODE!]  
                    [!ENDIF!]                                     
                [!ENDIF!]      
            [!ENDLOOP!]     
       [!ENDFOR!]
[!CODE!]
};

[!ENDCODE!]

   [!ENDIF!]  [!// END if not($Vdr_TxMsgCount = num:i(0))


[!// General configuration structure for all lighting instances
[!VAR "AppIdx" = "num:i(0)"!]
[!VAR "IndexLightingInstances" = "num:i(0)"!]
[!VAR "CountLightingInstances" = "num:i(count(LightingControlApp/*))"!]
[!VAR "NoLightingChannels" = "num:i(1)"!]

[!CODE!]
/*Global configuration Data for RTE*/
const SwcRte_GlobalConfigType SwcRte_AppInstanceMapPB[SWCRTE_MAX_APP_INSTANCES] = 
{
[!ENDCODE!]
    [!LOOP "LightingControlApp/*"!]   
        [!IF "num:i($CountLightingInstances) != num:i(0)"!]
            [!IF "node:value(./LightCtrlOutputSignalType) = 'DIGITAL_OUTPUT'"!]
                [!VAR "OutputType" = "'SWCRTE_DIGITAL_OUT'"!]
            [!ELSEIF "node:value(./LightCtrlOutputSignalType) = 'PWM'"!]
                [!VAR "OutputType" = "'SWCRTE_PWM_OUT'"!] 
            [!ELSE!]
                [!VAR "OutputType" = "'SWCRTE_OCU_OUT'"!]
            [!ENDIF!]
            
            [!LOOP "LightingChannels/*"!]
                [!IF "ChannelHasFeedback = 'true'"!]
                     [!VAR "NoLightingChannels" = "num:i($NoLightingChannels + 1)"!]             
                [!ENDIF!]
            [!ENDLOOP!]
 
[!CODE!]
 
    {
        SWCRTE_LIGHTING,        /*Application type*/
        [!"$OutputType"!],        /*Output signal type*/
        [!"num:i($NoLightingChannels)"!]U,                /*Number of input channels*/ [!// TO DO Input channels input + feedback
        [!"num:i(count(./LightingChannels/*))"!]U,                /*Number of output channels*/        
        0U,               /*Number of Rx Messages*/        
        0U,               /*Number of Tx Messages*/
        SwcRte_LightingInputChannelMap_[!"num:i($AppIdx)"!]_PB,               /*Input channel map configuration structure*/
        SwcRte_LightingOutputChannelMap_[!"num:i($AppIdx)"!]_PB,              /*Output channel map configuration structure*/
        NULL_PTR,              /*Rx message list*/
        NULL_PTR               /*Tx message list*/
    }[!IF "(num:i($AppIdx) < num:i($CountLightingInstances - 1)) or 
           (num:i($Vdr_RxMsgCount) != num:i(0)) or (num:i($Vdr_TxMsgCount) != num:i(0)) "!],[!ENDIF!]

[!ENDCODE!]
        [!VAR "NoLightingChannels" = "num:i(1)"!] 
        [!VAR "AppIdx" = "num:i($AppIdx + 1)"!]    
        [!ENDIF!]  
    [!ENDLOOP!]   

        [!IF "(num:i($Vdr_RxMsgCount) != num:i(0)) or (num:i($Vdr_TxMsgCount) != num:i(0)) "!]
 [!//  Test VDR exists
[!CODE!]

    {
        SWCRTE_VDR,        /*Application type*/
        SWCRTE_COM,        /*Output signal type*/
        0U,                /*Number of input channels*/
        0U,               /*Number of output channels*/        
        [!"num:i($Vdr_RxMsgCount)"!]U,               /*Number of Rx Messages*/        
        [!"num:i($Vdr_TxMsgCount)"!]U,               /*Number of Tx Messages*/
        NULL_PTR,               /*Input channel map configuration structure*/
        NULL_PTR,               /*Output channel map configuration structure*/
        SwcRte_RxMessageList_PB,               /*Rx message list*/
        SwcRte_TxMessageList_PB               /*Tx message list*/
    }     
[!ENDCODE!]
        [!ENDIF!]
[!CODE!]
};

[!ENDCODE!]

[!ENDSELECT!]
[!ENDNOCODE!]


/*PostBuild configuration structure.*/
/** @violates @ref SWCRTE_PBCFG_C_REF_4 Violates MISRA 2004 Required Rule 8.10 could be made static*/

/*==================================================================================================
*                                      GLOBAL VARIABLES
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
[!ENDIF!]

#ifdef __cplusplus
}
#endif

/** @} */
