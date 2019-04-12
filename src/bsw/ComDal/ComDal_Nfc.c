/**
*   @file           ComDal.c
*   @version        0.8.1
*
*   @brief          Integration Framework - ComDal Abstraction Layer component
*   @details        This file implements the ComDal interface to application layer.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup COMDAL
*   @{
*/
/*==================================================================================================
*   Platform             : CORTEXM
*
*   Autosar Version      : 4.3.1
*   Autosar Revision     : ASR_REL_4_3_REV_0001
*   SW Version           : 0.8.1
*   Build Version        : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
*
============================================================================================================================*/
/*============================================================================================================================
==================================================================================================*/

#ifdef __cplusplus
extern "C"{
#endif

/*===================================================================================================================
                                         INCLUDE FILES
 1) system and project includes
 2) needed interfaces from external units
 3) internal and external interfaces from this unit
====================================================================================================================*/
#include "Std_Types.h"
#include "Mcal.h"
#include "ComDal_Types.h"
#include "ComDal_Cfg.h"
#include "ComDal_Nfc.h"

#ifdef IFWK_USE_NFC
    #include "Anfc.h"
    #include "Anfc_Cbk.h"
    #include "Anfc_Types.h"
#endif 
/*====================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
=====================================================================================================================*/
#define COMDAL_NFC_VENDOR_ID_C                       43

#define COMDAL_NFC_AR_RELEASE_MAJOR_VERSION_C        4
#define COMDAL_NFC_AR_RELEASE_MINOR_VERSION_C        3
#define COMDAL_NFC_AR_RELEASE_REVISION_VERSION_C     1

#define COMDAL_NFC_SW_MAJOR_VERSION_C                0
#define COMDAL_NFC_SW_MINOR_VERSION_C                8
#define COMDAL_NFC_SW_PATCH_VERSION_C                1

/*====================================================================================================================
*                                     FILE VERSION CHECKS
=====================================================================================================================*/
#if (COMDAL_MAX_NFC_DESCRIPTORS > 0U)
/* Check if source file and Comdal configuration header file are of the same vendor */
#if (COMDAL_NFC_VENDOR_ID_C != COMDAL_CFG_VENDOR_ID)
    #error "ComDal_Nfc.c and ComDal_Cfg.h have different vendor ids"
#endif

/* Check if source file and Comdal configuration header file are of the same Autosar version */
#if ((COMDAL_NFC_AR_RELEASE_MAJOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_NFC_AR_RELEASE_MINOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_NFC_AR_RELEASE_REVISION_VERSION_C != COMDAL_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Can.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and Comdal configuration header file are of the same Software version */
#if ((COMDAL_NFC_SW_MAJOR_VERSION_C != COMDAL_CFG_SW_MAJOR_VERSION) || \
     (COMDAL_NFC_SW_MINOR_VERSION_C != COMDAL_CFG_SW_MINOR_VERSION) || \
     (COMDAL_NFC_SW_PATCH_VERSION_C != COMDAL_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal_Nfc.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and Comdal types header file are of the same vendor */
#if (COMDAL_NFC_VENDOR_ID_C != COMDAL_TYPES_VENDOR_ID)
    #error "ComDal_Nfc.c and ComDal_Types.h have different vendor ids"
#endif

/* Check if source file and Comdal types header file are of the same Autosar version */
#if ((COMDAL_NFC_AR_RELEASE_MAJOR_VERSION_C != COMDAL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_NFC_AR_RELEASE_MINOR_VERSION_C != COMDAL_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_NFC_AR_RELEASE_REVISION_VERSION_C != COMDAL_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Nfc.c and ComDal_Types.h are different"
#endif

/* Check if source file and Comdal types header file are of the same Software version */
#if ((COMDAL_NFC_SW_MAJOR_VERSION_C != COMDAL_TYPES_SW_MAJOR_VERSION) || \
     (COMDAL_NFC_SW_MINOR_VERSION_C != COMDAL_TYPES_SW_MINOR_VERSION) || \
     (COMDAL_NFC_SW_PATCH_VERSION_C != COMDAL_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal_Nfc.c and ComDal_Types.h are different"
#endif

/* Check if source file and Comdal Can header file are from the same vendor */
#if (COMDAL_NFC_VENDOR_ID_C != COMDAL_NFC_VENDOR_ID)
    #error "ComDal_Nfc.c and ComDal_Nfc.h have different vendor ids"
#endif

/* Check if source file and Comdal Can header file are of the same Autosar version */
#if ((COMDAL_NFC_AR_RELEASE_MAJOR_VERSION_C != COMDAL_NFC_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_NFC_AR_RELEASE_MINOR_VERSION_C != COMDAL_NFC_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_NFC_AR_RELEASE_REVISION_VERSION_C != COMDAL_NFC_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Nfc.c and ComDal_Nfc.h are different"
#endif

/* Check if source file and Comdal Can header file are of the same Software version */
#if ((COMDAL_NFC_SW_MAJOR_VERSION_C != COMDAL_NFC_SW_MAJOR_VERSION) || \
     (COMDAL_NFC_SW_MINOR_VERSION_C != COMDAL_NFC_SW_MINOR_VERSION) || \
     (COMDAL_NFC_SW_PATCH_VERSION_C != COMDAL_NFC_SW_PATCH_VERSION) \
    )
  #error "Software Version Numbers of ComDal_Nfc.c and ComDal_Nfc.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 /* Check if source file and Std_Types header file are of the same AutoSar version */
 #if ((COMDAL_NFC_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
      (COMDAL_NFC_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of ComDal_Nfc.c and Std_Types.h are different"
 #endif
 /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((COMDAL_NFC_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (COMDAL_NFC_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of ComDal_Nfc.c and Mcal.h are different"
 #endif 
#endif
#endif

/*===============================================================================================
*                                   LOCAL TYPES
===============================================================================================*/
typedef enum
{
    /* Activate NFC discovery */
    NFC_STATE_DISCOVERY = 0,
    
    /* Register server handle for reception*/
    NFC_STATE_REGISTER_SERVER,
    
    /* Nfc Idle state, in order to allow reception/transmission */
    NFC_STATE_IDLE,
    
    /* Wait for upper layer app to write data */
    NFC_STATE_WAIT_DATA,    
    
    /* Close server handle state */
    NFC_STATE_SNEP_CLOSE_SERVER,
    
    /* Wait for client to send message state */
    NFC_STATE_SNEP_WAIT_CLIENT,
    
    /* Actual transmission from Client to Server */
    NFC_STATE_SNEP_REQUEST,
    
    /* Finish client state */
    NFC_STATE_CLIENT_FINISHED,
    
    /* Error state, Anfc controller will be reset */
    NFC_STATE_ERROR = 0xFF
} ComDal_Nfc_State_Type;
/*==================================================================================================
                                       LOCAL MACROS
==================================================================================================*/
/* Snep mode selection, as in Anfc State Machine */
#define COMDAL_NFC_SNEP_MODE             3U

/* Maximum size of message which can be sent/received */
#define COMDAL_NFC_SNEP_DATA_LENGTH     128U

/* Maximum size of message which can be sent/received by the Nfc stack*/
#define COMDAL_NDEF_BUF_LENGTH           1024U

/* Reset delay in order to overcome hardware capabilities */
#define COMDAL_NFC_RESET_TICKS             200000

/* Maximum timeout for each state in the state machine*/
#define COMDAL_NFC_MAX_RETRIES            200

/* Ndef standard header size */
#define COMDAL_NDEF_HEADER_SIZE         5

/* Ndef Payload index, used for sending messages with any size */
#define COMDAL_PAYLOAD_LENGTH_INDEX     2

/* Ndef Payload Received header length, received from NFC device */
#define NDEF_APP_HEADER_RECORD_LENGTH     11


/*  Ndef Buffer used for writing messages of type Text. This will be shipped via NFC 
    to receiver. In order to send a different message to the receiver, one must update 
    the payload length and the payload, bytes.  
*/
VAR(uint8, ANFC_APPL_DATA)  NDEF_Buffer_Write[COMDAL_NFC_SNEP_DATA_LENGTH] = {     
                            0xD1, /* MB/ME/CF/1/IL/TNF */
                            0x01, /* TYPE LENGTH  */
                            0x16, /* PAYLOAD LENTGH */
                            0x54, /* TYPE */
                            0x06, /* ID */
                            /* Start of payload*/
                            0xFF,0xFF,0xFF,0x01,0x02,0x01,0xFD,
                            0xFF,0xFF,0xFF,0xFF,0xFD, 
                            0x01,0xFF,0x01,0xFF,0x36,0x37,0x38,0xFD, 0xFE 
                            /* End of payload*/};

        
/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#if (COMDAL_MAX_NFC_DESCRIPTORS > 0U)
/* Current state of the Anfc state machine*/
VAR(ComDal_Nfc_State_Type, AUTOMATIC) ComDal_Nfc_State;

/* Server handle used for receiving messages */
VAR(Anfc_SNEP_Handle_Type, AUTOMATIC) Nfc_SNEPServerHandle;

/* Server handle used for sending messages */
VAR(Anfc_SNEP_Handle_Type, AUTOMATIC) Nfc_SNEPClientHandle;

/* In this buffer the Anfc state machine updates data received via NFC */
VAR(uint8, AUTOMATIC) ComDal_Nfc_Server_Data[COMDAL_NFC_SNEP_DATA_LENGTH];

/* In this buffer the Anfc state machine updates data sent via NFC */
VAR(uint8, AUTOMATIC) ComDal_Nfc_Client_Data[COMDAL_NFC_SNEP_DATA_LENGTH];

/* Received data length. This variable is updated every time data is received*/
VAR(uint8, AUTOMATIC) ComDal_Nfc_Server_Data_Len;

/* Disc info structure used for Anfc server configuration. */
VAR(Anfc_DiscInfoType, ANFC_APPL_DATA) ComDal_Nfc_DiscInfo;

/* Timeout variable, this is used in order to avoid deadlocks in Anfc state machine*/
volatile VAR(uint8, AUTOMATIC) ComDal_Nfc_Retries = 0;

/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
/**
@brief      ComDal_NfcConfigPtr - Initialization pointer for NFC stack configuration
*/
static P2CONST(ComDal_ConfigType, AUTOMATIC, CAN_APPL_CONST) ComDal_NfcConfigPtr;
extern Anfc_ConfigType ANFC_PreCompileConfig;

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/


/*===============================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
===============================================================================================*/


/*===============================================================================================
*                                       LOCAL FUNCTIONS
===============================================================================================*/
FUNC(inline void, AUTOMATIC) ComDal_Nfc_Check_Timeout (void);

/*===============================================================================================
*                                       GLOBAL FUNCTIONS
===============================================================================================*/
/**
@brief      ComDal_Main - Main function for System Driver abstraction module
@details    Shall be used to compute the request for LowPower mode based on users request (from SWC)
            Shall be used to set the request LowPower 
            
@return     None

@pre None
@post None
*/
void sci_a_putchar(char ch)
{
    /* Empty implementation */
}

/*=================================================================================================================================*/
/**
@brief      ComDal_Nfc_Controller_Reset - Nfc controller reset
@details    Shall be used to reset the NFC controller, overcoming hardware limitations
            NFC controller power line is kept on GND for 20 milliseconds.
            
@return     None

@pre None
@post None
*/
/*=================================================================================================================================*/
FUNC(void, AUTOMATIC) ComDal_Nfc_Controller_Reset(void)
{
    Gpt_StopTimer(GptConf_GptChannelConfiguration_GPT_NFC_DELAY);
    /*Set VEN pin High*/
    Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_NFC_VEN, STD_HIGH);
    Gpt_StartTimer(GptConf_GptChannelConfiguration_GPT_NFC_DELAY, COMDAL_NFC_RESET_TICKS);
    /*Set VEN pin Low*/
    Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_NFC_VEN, STD_LOW);
    while(0 != Gpt_GetTimeRemaining(GptConf_GptChannelConfiguration_GPT_NFC_DELAY))
    {}
    Gpt_StopTimer(GptConf_GptChannelConfiguration_GPT_NFC_DELAY);
    /*Set VEN pin High*/
    Dio_WriteChannel((Dio_ChannelType)DioConf_DioChannel_NFC_VEN, STD_HIGH);
    Gpt_StartTimer(GptConf_GptChannelConfiguration_GPT_NFC_DELAY, COMDAL_NFC_RESET_TICKS);
    while(0 != Gpt_GetTimeRemaining(GptConf_GptChannelConfiguration_GPT_NFC_DELAY))
    {}
    Gpt_StopTimer(GptConf_GptChannelConfiguration_GPT_NFC_DELAY);
    ComDal_Nfc_State = NFC_STATE_DISCOVERY;
}

/*=================================================================================================================================*/
/**
@brief      ComDal_Nfc_Init - Initialization function for COMDAL NFC components
@details    This function shall:
             - initialize all global variables used by NFC component.
             - enable interrupts for channels NOT using polling mode
             - Start NFC controller.

@return     None
*/
/*=================================================================================================================================*/
FUNC(void, AUTOMATIC) ComDal_Nfc_Init(P2CONST(ComDal_ConfigType, AUTOMATIC, CAN_APPL_CONST) ConfigPtr)
{
    VAR(uint8, AUTOMATIC) ind;
    ComDal_NfcConfigPtr = ConfigPtr; 
    ComDal_Nfc_State = NFC_STATE_DISCOVERY;
    ComDal_Nfc_Server_Data_Len = 0U;
    for(ind = 0U; ind < COMDAL_NFC_SNEP_DATA_LENGTH; ind++)
    {
        ComDal_Nfc_Server_Data[ind] = 0U;
    }
    
}

/*=================================================================================================================================*/
/**
@brief      ComDal_NFC_DeInit - DeInitialization function for COMDAL NFC components
@details    This function shall:
             - DeInit Anfc stack and all the components.
@return     None
*/
/*=================================================================================================================================*/

FUNC(void, AUTOMATIC) ComDal_Nfc_DeInit(void)
{
    Anfc_DeInit();
}

/*=================================================================================================================================*/
/**
@brief      ComDal_NFC_Main - Main function used to handle state-machine of each NFC channel
@details    For each NFC channel, this function shall:
            - check if a new TX request was issued and if Yes, prepare TX message
            - when polling mode is used, cyclicly check if message was transmited succesfully by calling Can_MainFunction_Write
            - when polling mode is used, cyclicly check if a new RX message was received succesfully by calling Can_MainFunction_Read
            
@return     None
*/
/*=================================================================================================================================*/

FUNC(void, AUTOMATIC) ComDal_Nfc_Main(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel)
{
    VAR(Anfc_ReturnType, AUTOMATIC) anfcret = Anfc_GetStatus();
    if(ANFC_OK == anfcret)
    {
        switch(ComDal_Nfc_State)
        {
            case NFC_STATE_DISCOVERY:
                if(ANFC_OK == Anfc_DiscoveryActivateConfig(COMDAL_NFC_SNEP_MODE))
                {
                    ComDal_Nfc_State = NFC_STATE_REGISTER_SERVER;
                }
                else
                {
                    ComDal_Nfc_State = NFC_STATE_ERROR;
                }
                break;
            
            case NFC_STATE_REGISTER_SERVER:
                if(ANFC_OK == Anfc_SNEP_RegisterServer(&Nfc_SNEPServerHandle, ANFC_SNEP_DEFAULT_SAP, NULL_PTR, ComDal_Nfc_Server_Data))
                {
                    ComDal_Nfc_State = NFC_STATE_IDLE;
                }
                else
                {
                    ComDal_Nfc_State = NFC_STATE_ERROR;
                }
                break;
            
            case NFC_STATE_SNEP_CLOSE_SERVER:
                anfcret = Anfc_SNEP_CloseHandle(Nfc_SNEPServerHandle);
                if(ANFC_OK == anfcret)
                {
                    ComDal_Nfc_Retries = 0;
                    ComDal_Nfc_State =  NFC_STATE_WAIT_DATA;
                }
                else if(ANFC_NOT_OK == anfcret)
                    {
                        ComDal_Nfc_Retries = 0;
                        ComDal_Nfc_State = NFC_STATE_ERROR;
                    }
                    else if(ANFC_BUSY == anfcret)
                    {    
                        ComDal_Nfc_Check_Timeout();
                    }
                
                break;

            /* server has finished */
            case NFC_STATE_SNEP_WAIT_CLIENT: 
                /* open SNEP Client to send NDEF message */
                anfcret = Anfc_SNEP_OpenClient(&Nfc_SNEPClientHandle, ANFC_LLCP_SDP_SAP, "urn:nfc:sn:snep", ComDal_Nfc_Client_Data);
                if(ANFC_OK == anfcret)
                {
                    ComDal_Nfc_State = NFC_STATE_SNEP_REQUEST;
                }
                else if(ANFC_NOT_OK == anfcret)
                {
                    ComDal_Nfc_State = NFC_STATE_ERROR;
                }
                else
                {
                    ComDal_Nfc_State = NFC_STATE_SNEP_WAIT_CLIENT;
                }
                break;
                
            case NFC_STATE_WAIT_DATA:
                ComDal_Nfc_Check_Timeout();
                break; 
                
            case NFC_STATE_SNEP_REQUEST:
                /* Response to Connection request */
                anfcret = Anfc_SNEP_SendReq(Nfc_SNEPClientHandle, ANFC_SNEP_REQUEST_PUT, 0U, NDEF_Buffer_Write, NDEF_Buffer_Write[COMDAL_PAYLOAD_LENGTH_INDEX] + COMDAL_NDEF_HEADER_SIZE -1);
                
                if(ANFC_OK == anfcret)
                {
                    ComDal_Nfc_State = NFC_STATE_CLIENT_FINISHED;
                    ComDal_Nfc_Retries = 0;
                }
                else
                {
                    if(ANFC_NOT_OK == anfcret)
                    {
                        ComDal_Nfc_State = NFC_STATE_SNEP_CLOSE_SERVER;
                        ComDal_Nfc_Retries = 0;
                    }
                    else if(ANFC_BUSY == anfcret)
                    {    
                         ComDal_Nfc_Check_Timeout();
                    }
                }
                break;
            
            case NFC_STATE_CLIENT_FINISHED: 
                anfcret = Anfc_SNEP_CloseHandle(Nfc_SNEPClientHandle);
                if(ANFC_NOT_OK == anfcret)
                {
                    ComDal_Nfc_State = NFC_STATE_IDLE;
                    ComDal_Nfc_Retries = 0;
                }
                else
                {
                    if(ANFC_OK == anfcret)
                    {
                        ComDal_Nfc_Retries = 0;
                        ComDal_Nfc_State = NFC_STATE_ERROR;
                    }
                    else if(ANFC_BUSY == anfcret)
                    {    
                        ComDal_Nfc_Check_Timeout();
                    }
                }
                break;
            
            case NFC_STATE_IDLE:
                ComDal_Nfc_Check_Timeout();
                break;
                
            case NFC_STATE_ERROR:
                ComDal_Nfc_State = NFC_STATE_DISCOVERY;
                ComDal_Nfc_Controller_Reset();
                Anfc_Init(&ANFC_PreCompileConfig);
                Anfc_NFCCInit();
                break; 
            default:
                /* Report DET Error */
                break;
        }
    }
    else if(ANFC_NOT_OK == anfcret)
    {
        ComDal_Nfc_Controller_Reset();
        Anfc_Init(&ANFC_PreCompileConfig);
        Anfc_NFCCInit();
    }
}



/*=================================================================================================================================*/
/**
@brief      ComDal_Nfc_ReadData - API used to provide data that was read from the Nfc.
@details    This function will provide users with the data received on the NFC line for the provided
            input channel.
            This function shall return  COMDAL_OBSOLETE if no new NFC message was received for that channel;
            if COMDAL was not properly initialized it shall return COMDAL_INVALID.
            This function shall return COMDAL_NO_ERROR whenever the data received has be updated.

@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  CanDataLen     Maximum data length provided for that channel
@param[out] ReadBuffer     Data read from NFC for the assigned input channel.


@return     ComDal_ReturnType: COMDAL_NO_ERROR, COMDAL_OBSOLETE, COMDAL_INVALID
*/
/*=================================================================================================================================*/

FUNC(ComDal_ReturnType, AUTOMATIC) ComDal_Nfc_ReadData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) ReadBuffer, VAR(uint8, AUTOMATIC) DataLen)
{
    VAR(uint8, AUTOMATIC) MsgIndex;
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) NfcDescriptorId = 0;
    VAR(ComDal_ReturnType, AUTOMATIC) ReturnVal = COMDAL_NO_ERROR;
    
    if(NULL_PTR != ComDal_NfcConfigPtr)
    {
        NfcDescriptorId   =  (ComDal_NfcConfigPtr->pComChannelMap)[ComChannel].ComDescriptorIndex;

        if (NFC_STATE_WAIT_DATA == ComDal_Nfc_State)
        {
            if (DataLen < COMDAL_NFC_SNEP_DATA_LENGTH)
            {
                /*write external buffer, and remove header from data */
                for(MsgIndex = 0; MsgIndex < DataLen; MsgIndex++)
                {   
                    ReadBuffer[MsgIndex] = (char)ComDal_Nfc_Server_Data[MsgIndex + NDEF_APP_HEADER_RECORD_LENGTH];
                }
            }
            else
            {
                ReturnVal = COMDAL_INVALID;
            }
        }
        else
        {

            ReturnVal = COMDAL_INVALID;
        }
    }
    
    return ReturnVal;
}

/*=================================================================================================================================*/
/**
@brief      ComDal_Nfc_WriteData - function used to send data via NFC. Actual sending is done in Comdal_Nfc_MainFunction, this function is
used to create an NDEF message and update Nfc buffers.

@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  CanDataLen     Maximum data length provided for that channel
@param[in]     TxDataString   Data to be written on Nfc for the assigned input channel.


@return     none
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Nfc_WriteData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) TxDataString, VAR(uint8, AUTOMATIC) DataLen)
{
    VAR(uint8, AUTOMATIC) MsgIndex;
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) NfcDescriptorId = 0;
    
    if(NULL_PTR != ComDal_NfcConfigPtr)
    {
        NfcDescriptorId  =  (ComDal_NfcConfigPtr->pComChannelMap)[ComChannel].ComDescriptorIndex;
        
        if (NFC_STATE_WAIT_DATA == ComDal_Nfc_State)
        {    
            if (DataLen < COMDAL_NFC_SNEP_DATA_LENGTH)
            {        
                /* Cleanup before writing to buffer */
                for (MsgIndex = COMDAL_NDEF_HEADER_SIZE; MsgIndex < COMDAL_NFC_SNEP_DATA_LENGTH; MsgIndex++)
                {
                    NDEF_Buffer_Write[MsgIndex] = 0;
                }

                /* Update size of message */
                NDEF_Buffer_Write[COMDAL_PAYLOAD_LENGTH_INDEX] = DataLen + 1;
                
                /* Update message */
                for (MsgIndex = 0; MsgIndex < DataLen; MsgIndex++)
                {
                    NDEF_Buffer_Write[COMDAL_NDEF_HEADER_SIZE + MsgIndex] = TxDataString[MsgIndex];
                }    
            }
            ComDal_Nfc_State = NFC_STATE_SNEP_WAIT_CLIENT;
        }
        else 
        {
            ComDal_Nfc_State = NFC_STATE_ERROR;
        }
    }
}
/*=================================================================================================================================*/
/**
@brief      ComDal_Nfc_Check_Timeout - function used to check if a certain period of time has been elapsed since current state has been
            set in the state machine. If maximum timeout value has been reached, the state machine will be reset to error state.

@param[in]  none

@return     none
*/
/*=================================================================================================================================*/

FUNC(inline void, AUTOMATIC) ComDal_Nfc_Check_Timeout(void)
{
    ComDal_Nfc_Retries += 1; 
    if(COMDAL_NFC_MAX_RETRIES == ComDal_Nfc_Retries)
    {
        ComDal_Nfc_Retries = 0;
        ComDal_Nfc_State = NFC_STATE_ERROR;
    }    
}

/*==================================================================================================
                                       ANFC Callbacks
==================================================================================================*/

FUNC(Anfc_ReturnType, ANFC_CODE) Anfc_SNEP_Get_NDEF_Message(VAR(uint8, AUTOMATIC) Handle,
                                                            VAR(uint8, AUTOMATIC) NDEF_Message[],
                                                            VAR(uint32, AUTOMATIC) NDEF_Length,
                                                            P2CONST(uint8, AUTOMATIC, ANFC_APPL_DATA) NDEF_Ptr[],
                                                            P2VAR(uint32, AUTOMATIC, ANFC_APPL_DATA) NDEF_Ptr_Len)
{
    VAR(uint32, ANFC_APPL_DATA)  ComDal_SNEP_NDEF_Len = 0;
    Anfc_ReturnType ret = ANFC_NOT_OK;
    if (Handle == Nfc_SNEPServerHandle)
    {
        /* Fill the send message pointer and length */
        if(NULL_PTR != NDEF_Ptr)
        {
            *NDEF_Ptr = NDEF_Buffer_Write;
        }
        if(NULL_PTR != NDEF_Ptr_Len)
        {
            ComDal_SNEP_NDEF_Len = (uint32)sizeof(NDEF_Buffer_Write);
            *NDEF_Ptr_Len = ComDal_SNEP_NDEF_Len;
        }
        if((NULL_PTR != NDEF_Ptr)  && (NULL_PTR != NDEF_Ptr_Len))
        {
            ret = ANFC_OK;
        }
    }
    return ret;
}

FUNC(Anfc_ReturnType, ANFC_CODE) Anfc_SNEP_Received_NDEF_Message(VAR(uint8, AUTOMATIC) Handle,
                                                                 VAR(uint8, AUTOMATIC) NDEF_Message[],
                                                                 VAR(uint32, AUTOMATIC) NDEF_Length)
{
    Anfc_ReturnType ret = ANFC_NOT_OK;
    uint16 index;
    
    if (Handle == Nfc_SNEPServerHandle)
    {
        for(index = 0U; index < NDEF_Length; index++)
        {
            ComDal_Nfc_Server_Data[index] = NDEF_Message[index];
        }
        ComDal_Nfc_Server_Data_Len = NDEF_Length;
        ret = ANFC_OK;
        ComDal_Nfc_State = NFC_STATE_SNEP_CLOSE_SERVER;
    }
    return ret;
}

FUNC(Anfc_ReturnType, ANFC_CODE) Anfc_SNEP_Check_NDEF_Message(VAR(uint8, AUTOMATIC) Handle,
                                                              VAR(uint32, AUTOMATIC) NDEF_Length,
                                                              P2VAR(uint32, AUTOMATIC, ANFC_APPL_DATA) MaxBufferLength)
{
    Anfc_ReturnType ret = ANFC_NOT_OK;

    /* Set MaxBufferLength to a value & return ANFC_OK if you want to truncate the NDEF message to your length. */
    (void) MaxBufferLength;
    if (Handle == Nfc_SNEPServerHandle)
    {
        if (NDEF_Length <= COMDAL_NDEF_BUF_LENGTH)
        {
            ret = ANFC_OK;
        }
    }
    return ret;
}

FUNC(uint8, ANFC_CODE) Anfc_RFDiscoveryNtf(VAR(uint8, AUTOMATIC) nb_disc)
{
    uint8 ret_disc_id;
    Std_ReturnType stdRet = E_OK;

    stdRet = Anfc_GetDiscoveryInfo(&ComDal_Nfc_DiscInfo);
    if (E_OK == stdRet)
    {
        uint8 index;
        /* search for RF protocol equal to NFC_DEP */
        for(index = 1; index <= nb_disc; index++)
        {
            if (ANFC_NCI_PROTOCOL_NFC_DEP == ComDal_Nfc_DiscInfo.RfDiscoveryData[index - 1U].RfProtocol)
            {
                break;
            }
        }
        ret_disc_id = index;
    }
    else
    {
        ret_disc_id = 1U;
    }
    
    return ret_disc_id;
}

FUNC(void, ANFC_CODE) Anfc_P2P_ConnectNotification(VAR(Anfc_P2P_Handle_Type, AUTOMATIC) Handle, VAR(Anfc_P2P_ConnectionNtfType, AUTOMATIC) ConnNtf)
{
    switch(ConnNtf)
    {
        case ANFC_P2P_CONNECTION_REQUEST:
            Anfc_P2P_Accept(Handle);
            break;
        case ANFC_P2P_CONNECTION_COMPLETED:
        case ANFC_P2P_CONNECTION_DISCONECTED:
        case ANFC_P2P_CONNECTION_DISCONECTED_R1:
        case ANFC_P2P_CONNECTION_DISCONECTED_R2:
        case ANFC_P2P_CONNECTION_DISCONECTED_R3:
        case ANFC_P2P_CONNECTION_DISCONECTED_R10:
        case ANFC_P2P_CONNECTION_DISCONECTED_R11:
        case ANFC_P2P_CONNECTION_DISCONECTED_R20:
        case ANFC_P2P_CONNECTION_DISCONECTED_R21:
        default:
            break;
    }
}

FUNC(void, ANFC_CODE) Anfc_P2P_ReceiveNotification(VAR(Anfc_P2P_Handle_Type, AUTOMATIC) Handle,
                                                   CONST(uint8, AUTOMATIC) Data[],
                                                   CONST(uint16, AUTOMATIC) DataLength)
{
    /* Empty implementation */
}

FUNC(void, ANFC_CODE) Anfc_P2P_SDPResponseNtf(VAR(uint8, AUTOMATIC) sap, VAR(uint8, AUTOMATIC) csn)
{
    /* Empty implementation */
}

FUNC(void, ANFC_CODE) Anfc_P2P_TxCompleteNotification(VAR(Anfc_P2P_Handle_Type, AUTOMATIC) handle)
{
    /* Empty implementation */
}
#endif /* COMDAL_MAX_NFC_DESCRIPTORS > 0U */
#ifdef __cplusplus
}
#endif