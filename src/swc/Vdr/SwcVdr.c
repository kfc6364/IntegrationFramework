/**
*    @file        SwcVdr.c
*    @version     0.8.1
*
*    @brief       Integration Framework - VDR SW component.
*
*    @details     Implementation from the VDR application.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup SWCVDR
*   @{
*/
/*==================================================================================================
*   Project              : AUTOSAR 4.3 MCAL
*   Platform             : CORTEXM
*   SW Version           : 0.8.1
*   Build Version        : S32K2XXS32K2XX_MCAL_0_8_1_EAR_ASR_REL_4_3_REV_0001_20180420
==================================================================================================*/
/*==================================================================================================
==================================================================================================*/

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

#include "SwcRte_Types.h"
#include "SwcRte.h"
#include "SwcRte_Cfg.h"
#include "SwcVdr.h"
#include "StringLib.h"
/*==================================================================================================
                                       SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define SWCVDR_VENDOR_ID_C                          43

#define SWCVDR_SW_MAJOR_VERSION_C                   0
#define SWCVDR_SW_MINOR_VERSION_C                   8
#define SWCVDR_SW_PATCH_VERSION_C                   1
/*==================================================================================================
*                                     FILE VERSION CHECKS
===================================================================================================*/
/* Check if SwcVdr.c source file and SwcVdr.h header file are of the same vendor */
#if (SWCVDR_VENDOR_ID_C != SWCVDR_VENDOR_ID)
    #error "SwcVdr.c and SwcVdr.h have different vendor ids"
#endif

/* Check if SwcVdr.c source file and SwcVdr.h header file are of the same Software version */
#if ((SWCVDR_SW_MAJOR_VERSION_C != SWCVDR_SW_MAJOR_VERSION) || \
     (SWCVDR_SW_MINOR_VERSION_C != SWCVDR_SW_MINOR_VERSION) || \
     (SWCVDR_SW_PATCH_VERSION_C != SWCVDR_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcVdr.c and SwcVdr.h are different"
#endif

/* Check if SwcVdr.c source file and  SwcRte.h header file are of the same vendor */
#if (SWCVDR_VENDOR_ID_C != SWCRTE_VENDOR_ID)
    #error "SwcVdr.c and SwcRte.h have different vendor ids"
#endif

/* Check if SwcVdr.c source file and SwcRte.h header file are of the same Software version */
#if ((SWCVDR_SW_MAJOR_VERSION_C != SWCRTE_SW_MAJOR_VERSION) || \
     (SWCVDR_SW_MINOR_VERSION_C != SWCRTE_SW_MINOR_VERSION) || \
     (SWCVDR_SW_PATCH_VERSION_C != SWCRTE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcVdr.c and SwcRte.h are different"
#endif


/* Check if SwcVdr.c source file and SwcRte_Cfg.h header file are of the same vendor */
#if (SWCVDR_VENDOR_ID_C != SWCRTE_CFG_VENDOR_ID)
    #error "SwcVdr.c and SwcRte_Cfg.h have different vendor ids"
#endif

/* Check if SwcVdr.c source file and SwcRte_Cfg.h header file are of the same Software version */
#if ((SWCVDR_SW_MAJOR_VERSION_C != SWCRTE_CFG_SW_MAJOR_VERSION) || \
     (SWCVDR_SW_MINOR_VERSION_C != SWCRTE_CFG_SW_MINOR_VERSION) || \
     (SWCVDR_SW_PATCH_VERSION_C != SWCRTE_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcVdr.c and SwcRte_Cfg.h are different"
#endif


/* Check if SwcVdr.c source file and SwcRte_Types.h header file are of the same vendor */
#if (SWCVDR_VENDOR_ID_C != SWCRTE_TYPES_VENDOR_ID)
    #error "SwcVdr.c and SwcRte_Types.h have different vendor ids"
#endif

/* Check if SwcVdr.c source file and SwcRte_Types.h header file are of the same Software version */
#if ((SWCVDR_SW_MAJOR_VERSION_C != SWCRTE_TYPES_SW_MAJOR_VERSION) || \
     (SWCVDR_SW_MINOR_VERSION_C != SWCRTE_TYPES_SW_MINOR_VERSION) || \
     (SWCVDR_SW_PATCH_VERSION_C != SWCRTE_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcVdr.c and SwcRte_Types.h are different"
#endif



/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define SWCVDR_DATABYTE_INSTANCE_MASK     (0x3FU)
#define SWCVDR_DATABYTE_COMTYPE_MASK       (0xC0U)
#define SWCVDR_DATABYTE_COMTYPE_SHIFT      (0x6U)

#define SWCVDR_MESSAGE_ID_BYTE             (0U) 
#define SWCVDR_MESSAGE_TYPE_BYTE           (1U)
#define SWCVDR_RESPONSE_MSG_ID_BYTE        (2U)
#define SWCVDR_INSTANCEID_COMTYPE_BYTE     (3U)
#define SWCVDR_CHANNELID_PWRMODE_BYTE      (4U) 

#define SWCVDR_DATABYTE_COMTYPE_UNICAST    (0U) 
#define SWCVDR_DATABYTE_COMTYPE_MULTICAST  (1U)
#define SWCVDR_DATABYTE_COMTYPE_BROADCAST  (2U)

#define SWCVDR_MAX_DUTYVALUE_PER           (100U)
#define SWCVDR_MAX_DUTYVALUE_PWM           (0x8000U)  
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/

#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/
typedef enum
{    
    SWCRTE_TX_REQ_PENDING = 0U,      /**< @brief Application uses analog potentiometer as sensor. */
    SWCRTE_TX_REQ_OBSOLETE,
    SWCRTE_NO_REQ_PENDING,    
    SWCRTE_TX_REQ_INVALID,    
} SwcRte_TxReqStateType;


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/
#if (SWCRTE_MAX_TX_MESSAGE_IDS !=0)
 static SwcRte_TxReqStateType   SwcVdr_TxRequestState[SWCRTE_MAX_TX_MESSAGE_IDS];
#endif

#if (SWCRTE_MAX_RX_DATA_LEN !=0)
 static SwcRte_DataMessageType  SwcVdr_RxInputData[SWCRTE_MAX_RX_DATA_LEN];
#endif
/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
const SwcRte_GlobalConfigType * SwcVdr_GlobalCfgPtr;
/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/
 
 static void SwcVdr_ProcessReqStatusMessage(SwcRte_DataMessageType *  pRxDataMessagePtr);
 
#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
 static void SwcVdr_ProcessEventStatusMessage(SwcRte_AppMessageIdType  AppResponseMessageId);
 static void SwcVdr_SetLightingCommandFromMessage(SwcRte_AppInstanceIdType RteAppInstance, SwcRte_DataMessageType * pRxDataMessagePtr);
 static void SwcVdr_AppandLightingInfoToReplyMessage(SwcRte_AppInstanceIdType RteAppInstance, SwcRte_AppMessageIdType AppResponseMessageId, SwcRte_DataMessageType * pReplyDataMessagePtr);
#endif 

 static void SwcVdr_ProcessSendMessage(SwcRte_AppMessageIdType  AppTxMessageId);
 static void SwcVdr_ProcessForwardMessage(SwcRte_DataMessageType *  pRxDataMessagePtr);
 static uint16_t SwcVdr_CalculateLightingCommand(uint8_t u8ReceviceDataValue);
 static void SwcVdr_ProcessSetOutputMessage(SwcRte_DataMessageType *  pRxDataMessagePtr);
 static void SwcVdr_ProcessDiscoveryMessage(SwcRte_DataMessageType *  pRxDataMessagePtr);
#if (SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON)
 static void SwcVdr_ProcessReqPowerModeChange(SwcRte_DataMessageType *  pDataMessagePtr);
#endif/*SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON*/
#if (SWCRTE_ENABLE_HW_VARIANT == SWCRTE_STD_ON)
 static void SwcVdr_ProcessReqHwVariantChange(SwcRte_DataMessageType *  pDataMessagePtr);
#endif/*SWCRTE_ENABLE_HW_VARIANT == SWCRTE_STD_ON*/
 static boolean_t SwcRte_IsResponseMsgIdValid(SwcRte_DataMessageType * pDataMessagePtr);
 
/*===============================================================================================================*/
/**
@brief      SwcVdr_Init - Initialize the VDR
@details    After global data is initialized this function shall also clear all pending TX requests

@param[in]  ConfigPtr    Pointer to configuration data (this data is shared between all IODAL components)        

@return     void
@retval     

@pre None
@post None
*/
/*===============================================================================================================*/
void SwcVdr_Init(const SwcRte_GlobalConfigType * ConfigPtr)
{
    uint8_t AppMessageId;
    
    SwcVdr_GlobalCfgPtr = ConfigPtr;        
#if (SWCRTE_MAX_TX_MESSAGE_IDS !=0)
    for(AppMessageId = 0; AppMessageId < SWCRTE_MAX_TX_MESSAGE_IDS; AppMessageId++)
    {
        SwcVdr_TxRequestState[AppMessageId] = SWCRTE_NO_REQ_PENDING;     
    }
#endif    
    for(AppMessageId = 0; AppMessageId < SWCRTE_MAX_RX_DATA_LEN; AppMessageId++)
    {
        SwcVdr_RxInputData[AppMessageId] = 0;        
    }    
}


/*===============================================================================================================*/
/**
@brief      SwcVdr_ClearDataMessageBuffer - clears the TX request buffer
@details    The clears the TX buffer on demand
            
@param[in]  AppTxMessageId    Application message Id.

@return     none
*/
/*===============================================================================================================*/
void SwcVdr_ClearDataMessageBuffer(SwcRte_AppMessageIdType  AppTxMessageId)
{
    uint8_t DataLen = 0U;
    volatile uint8_t DataIndex = 0U;
    SwcRte_DataMessageType * DataMessagePtr;
    
    DataLen = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).u8VdrTxMessageDataLen;    
    DataMessagePtr = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).pDataMessagePtr;
    
    for(DataIndex=0; DataIndex < DataLen; DataIndex++)
    {
        DataMessagePtr[DataIndex] =  '\0';        
    }    
}


/*===============================================================================================================*/
/**
@brief      SwcVdr_MainRunnable - reads all received data, processes any received requests and send them to their
            users and write transmission requests.

@details    The function handles both RX inputs and TX requests;
            RX data is read from COMDAL via RTE and processed based on the type of the received data:
            SWCVDR_REQ_STATUS        - Shall process any requests to send user the status information
            SWCVDR_REQ_OUTPUT_UPDATE - Shall update the output of the instance/channels given in the 
                                       received message 
            SWCVDR_REQ_SYS_GO_SLEEP  - Shall process the 'go-to-sleep' requests                           
            
            TX data is written to COMDAL via RTE based on the TX-event type:
            SCWRTE_TX_ON_EVENT       - Shall be used to transmit data based on events set by application
            SCWRTE_TX_ON_REQUEST     - Shall be used to transmit data based on requests received from 
                                       COMDAL.
            
@param[in]  RteAppInstance    Instance Index.

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*===============================================================================================================*/
void SwcVdr_MainRunnable()
{    
    SwcRte_AppMessageIdType  AppRxMessageId;
    SwcRte_AppMessageIdType  AppTxMessageId;
    SwcRte_RxMessageType     ReceivedMessageType = SWCRTE_RX_REQ_INVALID;


    /*process RX messages -- read all ComDal inputs*/
    for(AppRxMessageId = 0; AppRxMessageId < SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].u8NoRxMessages; AppRxMessageId++)
    {
        /*read data received from BSW (through RTE) and check if new and valid message arrived*/
        if(SWCRTE_E_OK == SwcRte_ReadComData(AppRxMessageId, SwcVdr_RxInputData))
        {
            /*get RX message type*/
            ReceivedMessageType = (SwcRte_RxMessageType)SwcVdr_RxInputData[SWCVDR_MESSAGE_TYPE_BYTE];

            switch(ReceivedMessageType)
            {
                case SWCRTE_RX_REQ_STATUS:
                    SwcVdr_ProcessReqStatusMessage(SwcVdr_RxInputData);
                break;
                
                case SWCRTE_RX_FORWARD_MSG:
                    SwcVdr_ProcessForwardMessage(SwcVdr_RxInputData);
                break;
                    
                case SWCRTE_RX_REQ_OUTPUT_UPDATE:
                    SwcVdr_ProcessSetOutputMessage(SwcVdr_RxInputData);
                break;
                
                case SWCRTE_RX_REQ_DISCOVERY: 
                    SwcVdr_ProcessDiscoveryMessage(SwcVdr_RxInputData);
                break;
                
#if (SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON)
                case SWCRTE_RX_REQ_SYS_GO_SLEEP:
                    SwcVdr_ProcessReqPowerModeChange(SwcVdr_RxInputData);
                break;
#endif /*SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON*/
#if (SWCRTE_ENABLE_HW_VARIANT == SWCRTE_STD_ON)
                case SWCVDR_RX_REQ_CHANGE_HW_VARIANT:
                    SwcVdr_ProcessReqHwVariantChange(SwcVdr_RxInputData);
                break;
#endif /*SWCRTE_ENABLE_HW_VARIANT == SWCRTE_STD_ON*/           
                case SWCRTE_RX_REQ_PRINT_RTM_MEAS:
#if (SWCRTE_RTM_ENABLE == SWCRTE_STD_ON)
                    SwcVdr_ProcessReqRtmMessage(SwcVdr_RxInputData); 
#endif
                break;

                default:
                break;
            }            
            
        }    


    }

    /*process all TX requests -- write COMDAL data*/    
    for(AppTxMessageId = 0; AppTxMessageId < SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].u8NoTxMessages; AppTxMessageId++)
    {
          /*gather COM output requests from other applications and */            
        /*check if there are on-request type messages that need to be written*/
        if(SCWRTE_TX_ON_EVENT == (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).eMessageReplyType)                                  
        {
            SwcVdr_ProcessEventStatusMessage(AppTxMessageId);
        }
        
        if(SCWRTE_TX_SEND_MSG == (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).eMessageReplyType)                                  
        {
            SwcVdr_ProcessSendMessage(AppTxMessageId);
        }        
#if (SWCRTE_MAX_TX_MESSAGE_IDS !=0)
        if (SWCRTE_TX_REQ_PENDING == SwcVdr_TxRequestState[AppTxMessageId])
        {
            SwcVdr_TxRequestState[AppTxMessageId] = SWCRTE_TX_REQ_OBSOLETE;  
            SwcRte_WriteComData(AppTxMessageId);                  
        }
#endif		
    }   

}


/*===============================================================================================================*/
/**
@brief      SwcVdr_ProcessSendMessage - This function is called to send to ComDal a preconfigured message 
            
@details    The received RX request has the following format:              
            TX: byte 0 - Tx Message Id
                byte 1 - Tx Type: Send Message
                byte 2 - Data payload
                ...    
                byte N - Data payload                   
                (payload data come from configuration)
                
            
@param[in]  SwcRte_AppMessageIdType    AppTxMessageId

@return     void

@pre None
@post None
*/
/*===============================================================================================================*/
static void SwcVdr_ProcessSendMessage(SwcRte_AppMessageIdType  AppTxMessageId)
{    
    SwcRte_DataMessageType * pDataMessagePtr;

    /*get address */
    pDataMessagePtr = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).pDataMessagePtr;
    
    /*validate Tx Message Id and Tx Type*/
#if (SWCRTE_MAX_TX_MESSAGE_IDS !=0)	
    if((pDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE] == AppTxMessageId) && (SCWRTE_TX_SEND_MSG == pDataMessagePtr[SWCVDR_MESSAGE_TYPE_BYTE]))
    {
         SwcVdr_TxRequestState[AppTxMessageId] = SWCRTE_TX_REQ_PENDING;        
    }
#endif	
}




#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
/*===============================================================================================================*/
/**
@brief      SwcVdr_AppandLightingInfoToReplyMessage - internal function called to setup the TX message
            
@details    This functions can be called either when a Rx request status message is received or when an internal 
            Tx event was detected by VDR coming from one of the application instances. 
      
            All Send status TX messages shall have the following format:
                byte 0 - Tx Message Id
                byte 1 - Tx Type: On Request, On Event
                byte 2 - 'L' (for Lighting application) or 'M' (for Motor Control application)
                byte 3 - Application Instance Id 
                byte 4 - ' ' (empty space char)
                --- next bytes shall contain the same information format for each application channel that 
                exists within that instance
                byte 5: 'C' 
                byte 6: Channel_0 
                byte 7:' ' 
                byte 8:'S' 
                byte 9: StatusInfo 
                byte 10:' ' 
                byte 11:'V' 
                byte 12-13:FeedbackVoltage 
                byte 14:' ' 
                byte 15:'A' 
                byte 16-17: ActiveCommand 
                byte 18:' ' 
                byte 19:'C' Channel_1 
                byte 20:' ' 
                byte 21:'S'
                ... and so on for each requested channel                      

@param[in]  SwcRte_AppInstanceIdType    Application Instance Id            
@param[in]  SwcRte_DataMessageType      Pointer to data message
 
@return     void

@pre None
@post None
*/
/*===============================================================================================================*/
static void SwcVdr_AppandLightingInfoToReplyMessage(SwcRte_AppInstanceIdType RteAppInstance,  SwcRte_AppMessageIdType  AppResponseMessageId, SwcRte_DataMessageType * pReplyDataMessagePtr)
{
    SwcRte_AppChannelIdType RteAppChannel;
    SwcRte_ChannelStateType StatusInfo;
    SwcRte_AppLightingComInfoType  InputValue;
    uint16_t VoltageInfo;
    uint16_t ActiveCommand;
    uint8_t  AppendedLen = 0U;
    uint8_t  Index = 6U;

    /*get latest available status info*/
    SwcRte_FetchLightingComInfo(RteAppInstance, AppResponseMessageId, &InputValue);

    if (NULL_PTR != pReplyDataMessagePtr)
    {
        pReplyDataMessagePtr[2U] =  ' ';
        pReplyDataMessagePtr[3U] = 'L';
         (void)StrLib_Itoa((RteAppInstance & SWCVDR_DATABYTE_INSTANCE_MASK), &pReplyDataMessagePtr[4], 10);
        pReplyDataMessagePtr[5U] =  ' ';

        /*get status info value for the given instance and channels*/
        for (RteAppChannel = 0U; RteAppChannel < SwcVdr_GlobalCfgPtr[RteAppInstance].u8NoOutputChannel; RteAppChannel++)
        {
            /*if status was requested for the current channel*/
            StatusInfo    = InputValue.aLightingChanInfo[RteAppChannel].Status;
            VoltageInfo   = InputValue.aLightingChanInfo[RteAppChannel].FbkVoltage;
            ActiveCommand = InputValue.aLightingChanInfo[RteAppChannel].ActiveCommand;
            
            ActiveCommand = (ActiveCommand * 100U) >> 15U; /*calculate command a percent based on maximum PWM value of 0x8000 (ASR standard)*/

            Index = Index + RteAppChannel + AppendedLen;            
            pReplyDataMessagePtr[Index] = 'C';

            Index++;
            AppendedLen = StrLib_Itoa(RteAppChannel, &pReplyDataMessagePtr[Index], 10);

            Index = Index + AppendedLen;
            pReplyDataMessagePtr[Index] = ' ';

            Index++;  
            pReplyDataMessagePtr[Index] = 'S';

            Index++;
            AppendedLen = StrLib_Itoa(StatusInfo, &pReplyDataMessagePtr[Index], 10);

            Index = Index + AppendedLen;
            pReplyDataMessagePtr[Index] = ' ';

            Index++;   
            pReplyDataMessagePtr[Index] = 'A';

            Index++;
            AppendedLen = StrLib_Itoa(ActiveCommand, &pReplyDataMessagePtr[Index], 10);

            Index = Index + AppendedLen;            
            pReplyDataMessagePtr[Index] = '%';
            
            Index++;   
            pReplyDataMessagePtr[Index] = ' ';

            Index++;   
            pReplyDataMessagePtr[Index] = 'F';
            
            Index++;
            AppendedLen = StrLib_Itoa(VoltageInfo, &pReplyDataMessagePtr[Index], 10);
            

            Index = Index + AppendedLen;               
            pReplyDataMessagePtr[Index] = 'm';

            Index++;   
            pReplyDataMessagePtr[Index] = 'V';
            
        
            Index++; 
            pReplyDataMessagePtr[Index] = ' ';
            AppendedLen = 0;
        }
    }
}
#endif


/*===============================================================================================================*/
/**
@brief      SwcVdr_ProcessForwardMessage - This function is called to process a received request coming from any COMDAL source 
            to forword the given message to a given COMDAL destination
@details    The received RX request has the following format:
            RX: byte 0 - Rx Message Id
                byte 1 - Rx Message Type: SWCVDR_REQ_STATUS, SWCVDR_REQ_OUTPUT_UPDATE, SWCVDR_REQ_SYS_GO_SLEEP
                byte 2 - Associated TX message Id
                byte 3 - Data payload
                ...    
                byte N+1 - Data payload
                
            TX: byte 0 - Tx Message Id
                byte 1 - Tx Type: On Request
                byte 2 - Data payload
                ...    
                byte N - Data payload                   
                
                
            
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     Message type
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*===============================================================================================================*/
static void SwcVdr_ProcessForwardMessage(SwcRte_DataMessageType *  pRxDataMessagePtr)
{    
    volatile SwcRte_AppMessageIdType  AppResponseMessageId;
    SwcRte_DataMessageType *  pReplyDataMessagePtr;
    uint8_t DataCharIndex;
    uint8_t DataLen = 0U;


    if (NULL_PTR != pRxDataMessagePtr)
    {
        /*get TX response message ID corresponding to the current received status request*/
        AppResponseMessageId = pRxDataMessagePtr[SWCVDR_RESPONSE_MSG_ID_BYTE];
             
        if(SWCRTE_TRUE == SwcRte_IsResponseMsgIdValid(pRxDataMessagePtr))
        {
            pReplyDataMessagePtr = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppResponseMessageId]).pDataMessagePtr;

            /*get Tx replay data lengh*/
            DataLen = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppResponseMessageId]).u8VdrTxMessageDataLen;
             
            /*set request TX flag within message*/        
            pReplyDataMessagePtr[SWCVDR_MESSAGE_TYPE_BYTE] = SWCRTE_RX_FORWARD_MSG;

            /*copy received data payload to reply message buffer*/
            for(DataCharIndex = 2U; DataCharIndex < DataLen; DataCharIndex++)
            {
                pReplyDataMessagePtr[DataCharIndex] = pRxDataMessagePtr[DataCharIndex + 1U];
            }   
			
#if (SWCRTE_MAX_TX_MESSAGE_IDS !=0)                                   
            /*set TX message ID*/
            SwcVdr_TxRequestState[AppResponseMessageId] = SWCRTE_TX_REQ_PENDING;
#endif
		}        
    }
}




/*===============================================================================================================*/
/**
@brief      SwcVdr_ProcessReqStatusMessage - This function is called to process a received request coming from any COMDAL source to transmit back the         
            status information for any application instance
@details    The received RX request has the following format:
            RX: byte 0 - Rx Message Id
                byte 1 - Rx Message Type: SWCVDR_REQ_STATUS, SWCVDR_REQ_OUTPUT_UPDATE, SWCVDR_REQ_SYS_GO_SLEEP
                byte 2 - Associated TX message Id
                byte 3 - LSB 0..5 Application Instance Id  

                
            TX: byte 0 - Tx Message Id
                byte 1 - Tx Type: On Request, On Event
                byte 2 - 'L' (for Lighting application) or 'M' (for Motor Control application)
                byte 3 - Application Instance Id 
                byte 4 - ' ' (empty space char)
                byte 5 - 18: 'C' Channel_0 ' ' 'S' StatusInfo ' ' 'F' FeedbackVoltage ' ' 'A' ActiveCommand ' ' 
                byte 19 - 33: 'C' Channel_1 ' ' 'S' StatusInfo ' ' 'F' FeedbackVoltage ' ' 'A' ActiveCommand ' '
                ... and so on for each requested channel
                                   
            
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     Message type
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*===============================================================================================================*/
static void SwcVdr_ProcessReqStatusMessage(SwcRte_DataMessageType *  pRxDataMessagePtr)
{    
    volatile SwcRte_AppInstanceIdType RteAppInstance;
    volatile SwcRte_AppMessageIdType  AppResponseMessageId;
    SwcRte_DataMessageType *  pReplyDataMessagePtr;

    if (NULL_PTR != pRxDataMessagePtr)
    {
        /*get TX response message ID corresponding to the current received status request*/
        AppResponseMessageId = pRxDataMessagePtr[SWCVDR_RESPONSE_MSG_ID_BYTE];

        RteAppInstance = (SwcRte_AppInstanceIdType)(pRxDataMessagePtr[SWCVDR_INSTANCEID_COMTYPE_BYTE] & SWCVDR_DATABYTE_INSTANCE_MASK);
        
        if(SWCRTE_TRUE == SwcRte_IsResponseMsgIdValid(pRxDataMessagePtr))
        {
            pReplyDataMessagePtr = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppResponseMessageId]).pDataMessagePtr;

            /*check if the instance ID is valid */
            if(RteAppInstance < (SWCRTE_MAX_APP_INSTANCES - 1U))
            {
#if (SWCRTE_MAX_TX_MESSAGE_IDS !=0)                
				/*set TX message ID*/				
                SwcVdr_TxRequestState[AppResponseMessageId] = SWCRTE_TX_REQ_PENDING;
#endif                
                /*pReplyDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE] = AppResponseMessageId;*/
                StrLib_Itoa(AppResponseMessageId, &pReplyDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE], 10);

                /*set request TX flag within message*/        
                pReplyDataMessagePtr[SWCVDR_MESSAGE_TYPE_BYTE] = SCWRTE_TX_ON_REQUEST;

#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)                        
                if(SWCRTE_LIGHTING == SwcVdr_GlobalCfgPtr[RteAppInstance].eInstanceType)
                {
                    /*append lighting info to TX replay-data */
                    SwcVdr_AppandLightingInfoToReplyMessage(RteAppInstance, AppResponseMessageId, pReplyDataMessagePtr);

                    SwcRte_SetLightingComInfoEvent(RteAppInstance, SWCRTE_FALSE);                    

                }
#endif
            }
        }        
    }
}

/*===============================================================================================================*/
/**
@brief      SwcVdr_ProcessDiscoveryMessage - This function is called to process a received discovery request coming from any COMDAL source to transmit back the         
            status information for any application instance
@details    The received RX request has the following format:
            RX: byte 0 - Rx Message Id
                byte 1 - Rx Message Type: SWCRTE_RX_REQ_DISCOVERY
                byte 2 - Associated TX message Id
                
            TX: byte 0 - Tx Message Id
                byte 1 - Tx Type: On Request, On Event
                Per each App instance: 
                    byte 2 - 
                    byte 3 - Application Instance Id 
                    byte 4 - Input type, describing how the current instance is controlled
                    byte 5 - Number of input channels describing how many separate inputs can 
                             control the application via a message of appropriate type
                    byte 6 - Output channel type how the application outputs data upon responding to an external request 
                    byte 7 - Number of output channels which are capable of responding to a request
                    byte 8 - Feedback parameter description
                    byte 9 - End of instance description delimiter: 0xFD
                last byte - End of message delimiter: 0xFE
                            
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     void

@pre None
@post None
*/
/*===============================================================================================================*/
static void SwcVdr_ProcessDiscoveryMessage(SwcRte_DataMessageType *  pRxDataMessagePtr)
{    
    volatile SwcRte_AppMessageIdType  AppResponseMessageId;
    SwcRte_DataMessageType *  pReplyDataMessagePtr;
    uint8_t SwcRte_ChannelIndex = 0;
    uint8_t SwcRte_InstanceIndex = 0;
    uint8_t SwcRte_ReplyIndex = 2;    

    if (NULL_PTR != pRxDataMessagePtr)
    {
        /*get TX response message ID corresponding to the current received status request*/
        AppResponseMessageId = pRxDataMessagePtr[SWCVDR_RESPONSE_MSG_ID_BYTE];

        if(SWCRTE_TRUE == SwcRte_IsResponseMsgIdValid(pRxDataMessagePtr))
        {
            pReplyDataMessagePtr = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppResponseMessageId]).pDataMessagePtr;
#if (SWCRTE_MAX_TX_MESSAGE_IDS !=0)
            /*set TX message ID*/
            SwcVdr_TxRequestState[AppResponseMessageId] = SWCRTE_TX_REQ_PENDING;
#endif            
            /*pReplyDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE] = AppResponseMessageId;*/
            StrLib_Itoa(AppResponseMessageId, &pReplyDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE], 10);

            /*set request TX flag within message*/        
            pReplyDataMessagePtr[SWCVDR_MESSAGE_TYPE_BYTE] = SCWRTE_TX_ON_REQUEST;
            
            /* iterate through all the instances but VDR app instance */
            for (SwcRte_InstanceIndex = 0; SwcRte_InstanceIndex < SWCRTE_MAX_APP_INSTANCES - SWCRTE_MAX_VDR_INSTANCES; SwcRte_InstanceIndex++)
            {    
                /* Add instance type parameter */
                pReplyDataMessagePtr[SwcRte_ReplyIndex] = (uint8_t)SwcVdr_GlobalCfgPtr[SwcRte_InstanceIndex].eInstanceType;
                SwcRte_ReplyIndex++; 
                
                /* Add input command type*/
                pReplyDataMessagePtr[SwcRte_ReplyIndex] = (uint8_t)SwcVdr_GlobalCfgPtr[SwcRte_InstanceIndex].pInstanceInputSensor[0].eInputType;
                SwcRte_ReplyIndex++; 
                
                /* Add input channel count */
                pReplyDataMessagePtr[SwcRte_ReplyIndex] = (uint8_t)SwcVdr_GlobalCfgPtr[SwcRte_InstanceIndex].u8NoInputChannel;
                SwcRte_ReplyIndex++; 
                
                /* Add output type */
                pReplyDataMessagePtr[SwcRte_ReplyIndex] = (uint8_t)SwcVdr_GlobalCfgPtr[SwcRte_InstanceIndex].eOutputType;
                SwcRte_ReplyIndex++; 
                
                /* Add output channel count */
                pReplyDataMessagePtr[SwcRte_ReplyIndex] = (uint8_t)SwcVdr_GlobalCfgPtr[SwcRte_InstanceIndex].u8NoOutputChannel;

                
                if(SwcVdr_GlobalCfgPtr[SwcRte_InstanceIndex].u8NoInputChannel > 1)
                {
                    for(SwcRte_ChannelIndex = 1; SwcRte_ChannelIndex < SwcVdr_GlobalCfgPtr[SwcRte_InstanceIndex].u8NoInputChannel; SwcRte_ChannelIndex++)
                    {
                        if((SwcRte_ChannelIndex - 1) % 8 == 0)
                        {
                            SwcRte_ReplyIndex++; 
                        }

                        if(SwcVdr_GlobalCfgPtr[SwcRte_InstanceIndex].pInstanceInputSensor[SwcRte_ChannelIndex].eInputType == SWCRTE_ANALOG_FDBK_SENS)
                        {
                            pReplyDataMessagePtr[SwcRte_ReplyIndex] |= (1 << (SwcRte_ChannelIndex - 1));
                        }
                    }
                }
                SwcRte_ReplyIndex++;                        

                /* Add instance termination character */
                pReplyDataMessagePtr[SwcRte_ReplyIndex] = 0xFD;
                SwcRte_ReplyIndex ++; 
            }
            
            /* Add message termination character */
            pReplyDataMessagePtr[SwcRte_ReplyIndex] = 0xFE;
            SwcRte_ReplyIndex++;
        }
    }        
}

/*===============================================================================================================*/
/**
@brief      SwcVdr_ProcessEventStatusMessage - This function is used to process TX request that where issues by 
            events within the running applications (i.e. on event status information due to different failures)
@details    For on event Tx message there are no (prior) Rx messages that trigger requests, so VDR shall "scan"
            all instances of applications and search for active TX request generated by them.
            The Tx message format is the following    
            TX: byte 0 - Tx Message Id
                byte 1 - Tx Type: On Request, On Event
                byte 2 - 'L' (for Lighting application) or 'M' (for Motor Control application)
                byte 3 - Application Instance Id 
                byte 4 - ' ' (empty space char)
                byte 5 - 18: 'C' Channel_0 ' ' 'S' StatusInfo ' ' 'V' FeedbackVoltage ' ' 'A' ActiveCommand ' ' 
                byte 19 - 33: 'C' Channel_1 ' ' 'S' StatusInfo ' ' 'V' FeedbackVoltage ' ' 'A' ActiveCommand ' '
                ... and so on for each requested channel
                        
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     Message type
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*===============================================================================================================*/
static void SwcVdr_ProcessEventStatusMessage(SwcRte_AppMessageIdType  AppTxMessageId)
{
    SwcRte_AppInstanceIdType RteAppInstance;
    SwcRte_DataMessageType *  pDataMessagePtr;

    /*get address */
    pDataMessagePtr = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).pDataMessagePtr;
    
    /*set TX message ID*/
    pDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE] = AppTxMessageId;

    /*set request TX flag within message*/        
    pDataMessagePtr[SWCVDR_MESSAGE_TYPE_BYTE] = SCWRTE_TX_ON_EVENT;     
        
    for (RteAppInstance = 0U; RteAppInstance < (SWCRTE_MAX_APP_INSTANCES - 1U); RteAppInstance++)
    {
#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)         
        if(SWCRTE_LIGHTING == SwcVdr_GlobalCfgPtr[RteAppInstance].eInstanceType)
        { 
            /*append lighting info to TX replay-data */
            if(SWCRTE_TRUE == SwcRte_GetLightingComInfoEvent(RteAppInstance))
            {    
                SwcVdr_AppandLightingInfoToReplyMessage(RteAppInstance, AppTxMessageId, pDataMessagePtr);

#if (SWCRTE_MAX_TX_MESSAGE_IDS !=0)                
                SwcVdr_TxRequestState[AppTxMessageId] = SWCRTE_TX_REQ_PENDING;
#endif			
            }
        }
#endif

#if (SWCRTE_MOTORCTRL_APP_ENABLED == SWCRTE_STD_ON)
        if(SWCRTE_MOTORCTRL == SwcVdr_GlobalCfgPtr[RteAppInstance].eInstanceType)
        {
            /*TODO: add support for Motor control app*/
        }    
#endif        
    } 
}

#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
/*===============================================================================================================*/
/**
@brief      SwcVdr_SetLightingCommandFromMessage - sets output parameters within given instance data block

@details    Output data is processed based on type of communication:
            - UNICAST - only the output from the channels given in the RX message is updated
            - MULTICAST - list of channels given in the RX message are updated
            - BROADCAST - all channels of the instance are updated
                        
@param[in]  SwcRte_AppMessageIdType    Pointer to data message

@return     void

@pre None
@post None
*/
/*===============================================================================================================*/
static void SwcVdr_SetLightingCommandFromMessage(SwcRte_AppInstanceIdType RteAppInstance, SwcRte_DataMessageType * pRxDataMessagePtr)
{
    SwcRte_AppChannelIdType  RteAppChannel;
    SwcRte_AppLightingComDataType   OutputValue;
    volatile uint8_t   u8Index = 0;
    volatile uint8_t   u8CharIndex = 0;
    volatile uint8_t   u8CharValue = 0;
    volatile uint8_t  u8DataLen = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pRxMessageList[pRxDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE]]).u8VdrRxMessageDataLen;  
    volatile uint8_t  u8MaxChannels =  SwcVdr_GlobalCfgPtr[RteAppInstance].u8NoOutputChannel;
    
    /*check if update duty request is done for ONLY one channel in that instance*/
    if(((pRxDataMessagePtr[SWCVDR_INSTANCEID_COMTYPE_BYTE] & SWCVDR_DATABYTE_COMTYPE_MASK) >> SWCVDR_DATABYTE_COMTYPE_SHIFT) == SWCVDR_DATABYTE_COMTYPE_UNICAST)
    {
        RteAppChannel = pRxDataMessagePtr[SWCVDR_CHANNELID_PWRMODE_BYTE];
 
        /*validate received channel ID*/ 
        if(RteAppChannel < u8MaxChannels)
        {    
            u8CharValue = (uint8_t)pRxDataMessagePtr[SWCVDR_CHANNELID_PWRMODE_BYTE + 1U]; 
            
            /*calculate Duty value*/
            OutputValue.aLightChannelValue[RteAppChannel] = SwcVdr_CalculateLightingCommand(u8CharValue);        
        }            
    }
    /*check if update duty request is done for ALL channels in that instance*/
    else if(((pRxDataMessagePtr[SWCVDR_INSTANCEID_COMTYPE_BYTE] & SWCVDR_DATABYTE_COMTYPE_MASK) >> SWCVDR_DATABYTE_COMTYPE_SHIFT) == SWCVDR_DATABYTE_COMTYPE_BROADCAST)
    {       
        u8CharValue = (uint8_t)pRxDataMessagePtr[SWCVDR_CHANNELID_PWRMODE_BYTE + 1U]; 
        
        /*for every channel in that instance */ 
        for (RteAppChannel = 0; RteAppChannel < u8MaxChannels; RteAppChannel++)
        {                
            /*calculate Duty value*/
            OutputValue.aLightChannelValue[RteAppChannel] = SwcVdr_CalculateLightingCommand(u8CharValue);
        }        
    }    
    else /*check if update duty request is done for a given list of channels in that instance*/
    { 
        /*every second byte from the received message list (starting with 5h byte)*/ 
        for (u8CharIndex = SWCVDR_CHANNELID_PWRMODE_BYTE; u8CharIndex < u8DataLen; u8CharIndex = u8CharIndex + 2U)
        {            
            RteAppChannel = pRxDataMessagePtr[u8CharIndex];
           
            /*validate received channel ID*/
            if(RteAppChannel < u8MaxChannels)
            {
                   u8CharValue = (uint8_t)pRxDataMessagePtr[u8CharIndex + 1U]; 
                    
                /*calculate Duty value*/
                OutputValue.aLightChannelValue[RteAppChannel] = SwcVdr_CalculateLightingCommand(u8CharValue);    
            }           
        }
    }
        
    SwcRte_WriteLightingComData(RteAppInstance, &OutputValue);
}


/*================================================================================================*/
/**
@brief      SwcVdr_ProcessSetOutputMessage - shall process any request to change the output value for the 
            instance and channels provided by the RX message.
@details    This function shall process received bytes depending on the type of the requested communication
            to update output value for instance (both found in byte 3).
            Output value is stored in (the next) two consecutive received bytes. The number of bytes required to write  
            all outputs is 2 x number_of_channels to be updated.
            The Rx message has the following format:
            RX: byte 0 - Rx Message Id
                byte 1 - Rx Message Type: SWCVDR_REQ_STATUS, SWCVDR_REQ_OUTPUT_UPDATE, SWCVDR_REQ_SYS_GO_SLEEP
                byte 2 - Does not matter
                byte 3 - Instance Id and requested update type (UNICAST, MULTICAST, BROADCAST)                
                byte 4 - OutputValue first byte
                byte 5 - OutputValue second byte
                        
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     Message type
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
static uint16_t SwcVdr_CalculateLightingCommand(uint8_t u8ReceviceDataValue)
{
    uint8_t u8CharValue =  u8ReceviceDataValue;
    if(u8CharValue > SWCVDR_MAX_DUTYVALUE_PER)
    {
        u8CharValue = SWCVDR_MAX_DUTYVALUE_PER;
    }     
    
    /*calculate Duty value*/
    return ((uint16_t)u8CharValue * (uint16_t)SWCVDR_MAX_DUTYVALUE_PWM) / (uint16_t)SWCVDR_MAX_DUTYVALUE_PER;       
}
#endif


/*================================================================================================*/
/**
@brief      SwcVdr_ProcessSetOutputMessage - shall process any request to change the output value for the 
            instance and channels provided by the RX message.
@details    This function shall process received bytes depending on the type of the requested communication
            to update output value for instance (both found in byte 3).
            Output value is stored in (the next) two consecutive received bytes. The number of bytes required to write  
            all outputs is 2 x number_of_channels to be updated.
            The Rx message has the following format:
            RX: byte 0 - Rx Message Id
                byte 1 - Rx Message Type: SWCVDR_REQ_STATUS, SWCVDR_REQ_OUTPUT_UPDATE, SWCVDR_REQ_SYS_GO_SLEEP
                byte 2 - Does not matter
                byte 3 - Instance Id and requested update type (UNICAST, MULTICAST, BROADCAST)                
                byte 4 - OutputValue first byte
                byte 5 - OutputValue second byte
                        
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     Message type
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
static void SwcVdr_ProcessSetOutputMessage(SwcRte_DataMessageType *  pRxDataMessagePtr)
{
    SwcRte_AppInstanceIdType RteAppInstance;
    /*SwcRte_AppMessageIdType  AppResponseMessageId;*/

    /*get TX response message ID corresponding to the current received status request*/
    /*AppResponseMessageId = SWCRTE_TX_REQ_INVALID;*/

    if (NULL_PTR != pRxDataMessagePtr)
    {
        /*get the destination application instance for which the request to send status info was received */
        RteAppInstance = pRxDataMessagePtr[SWCVDR_INSTANCEID_COMTYPE_BYTE] & SWCVDR_DATABYTE_INSTANCE_MASK;

        /*check if the instance ID corresponds to a */
        if (RteAppInstance < (SWCRTE_MAX_APP_INSTANCES - 1U))
        {
#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)                        
            if(SWCRTE_LIGHTING == SwcVdr_GlobalCfgPtr[RteAppInstance].eInstanceType)
            {
                /*write new output command for all channel given in the command */
                SwcVdr_SetLightingCommandFromMessage(RteAppInstance, pRxDataMessagePtr);
            }
#endif
        }
    }
}

#if (SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON)
/*================================================================================================*/
/**
@brief      SwcVdr_ProcessReqPowerModeChange - this function shall process received requests to change current 
            power mode or to execute a software reset.
@details    Based on the value of byte 3 in the received message the following operation may happen;
            - if ASCII code for 'R' is received the application shall issues a request for system reset.
            - if ASCII code for 'S' is received the application shall issue a request to change current 
            power mode to the value provided by byte 4 of the received message
            - if ASCII code for 'P' is received the application fetch the curret run-mode for the BSW (via RTE)
            and request the transition of the value of the current mode to the user.
            
            The Rx message has the following format:
            RX: byte 0 - Rx Message Id
                byte 1 - Rx Message Type: SWCVDR_REQ_STATUS, SWCVDR_REQ_OUTPUT_UPDATE, SWCVDR_REQ_SYS_GO_SLEEP
                byte 2 - Tx Replay Message Id
                byte 3 - Request Type (see above)    
                byte 4 - Requested power mode
            
            TX: byte 0 - Tx Message Id (same as Rx byte 3)
                byte 1 - Tx replay type: SCWRTE_TX_ON_REQUEST
                byte 2 - Value of the current power mode
            
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     Message type
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
static void SwcVdr_ProcessReqPowerModeChange(SwcRte_DataMessageType *  pRxDataMessagePtr)
{
    SwcRte_AppMessageIdType  AppResponseMessageId;
    SwcRte_DataMessageType * pTxReplayDataMessagePtr;
    SwcRte_PowerModeType PowerModeId;
    char RequestType;
   
    if (NULL_PTR != pRxDataMessagePtr)
    {
        RequestType = pRxDataMessagePtr[SWCVDR_INSTANCEID_COMTYPE_BYTE];
        
        switch (RequestType)
        {
            case 'R': 
                /*Call SysDal to request a SW Reset*/
                SwcRte_ExecuteSwReset(); 
            break;
            
            case 'S':
                /*Call SysDal to request a desired LowPower Mode*/
			    {
                 PowerModeId = (SwcRte_PowerModeType)pRxDataMessagePtr[SWCVDR_CHANNELID_PWRMODE_BYTE];
                 SwcRte_SetPowerMode(PowerModeId); 
                }
            break;    
            
            case 'P':
                {    
                 /*get TX response message ID corresponding to the current received status request*/
                 AppResponseMessageId = pRxDataMessagePtr[SWCVDR_RESPONSE_MSG_ID_BYTE]; 
                
                 /*validate response message Id agains configuration*/
                 if(SWCRTE_TRUE == SwcRte_IsResponseMsgIdValid(pRxDataMessagePtr))
                 {            
                   pTxReplayDataMessagePtr = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppResponseMessageId]).pDataMessagePtr;
                                 
                   pTxReplayDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE] = AppResponseMessageId;
                    
                   pTxReplayDataMessagePtr[SWCVDR_MESSAGE_TYPE_BYTE] = SCWRTE_TX_ON_REQUEST;
                    
                   PowerModeId = SwcRte_GetCurrentPowerMode(); /* RTE/SysDal function not yet defined*/
                    
                   pTxReplayDataMessagePtr[SWCVDR_RESPONSE_MSG_ID_BYTE] = (char)PowerModeId;
                  }
                }    
            break;
                
            default :
            break;         
        }        
    }
}

#endif/*SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON*/
/*================================================================================================*/
/**
@brief      SwcVdr_ProcessReqHwVariantChange - this function shall process received requests to change HW 
            Variant with an other predefined HW variant
@details    Based on the value of byte 3 in the received message the following operation may happen;
            - if ASCII code for 'V' is received the application shall issues a request for changing the 
            current HW Variant to the one given in the next byte
            - if ASCII code for 'P' is received the application fetch the curret run-mode for the BSW (via RTE)
            and request the transition of the value of the current mode to the user.
               
            
            The Rx message has the following format:
            RX: byte 0 - Rx Message Id
                byte 1 - Rx Message Type: SWCVDR_REQ_STATUS, SWCVDR_REQ_OUTPUT_UPDATE, SWCVDR_REQ_SYS_GO_SLEEP
                byte 2 - Tx Replay Message Id
                byte 3 - Request Type (see above)    
                byte 4 - Requested Hw variant
            
            TX: byte 0 - Tx Message Id (same as Rx byte 3)
                byte 1 - Tx replay type: SCWRTE_TX_ON_REQUEST
                byte 2 - Value of the current power mode
               
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     Message type
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
#if (SWCRTE_ENABLE_HW_VARIANT == SWCRTE_STD_ON)
static void SwcVdr_ProcessReqHwVariantChange(SwcRte_DataMessageType *  pDataMessagePtr)
{
    SwcRte_AppMessageIdType  AppResponseMessageId;
    SwcRte_DataMessageType * pReplyDataMessagePtr;
    uint8_t                  HwVariantId;
    char RequestType;
   
    if (NULL_PTR != pDataMessagePtr)
    {
        RequestType= pDataMessagePtr[SWCVDR_INSTANCEID_COMTYPE_BYTE];
        
        switch (RequestType)
        {            
            case 'V':
            {
                HwVariantId = (uint8_t)pDataMessagePtr[SWCVDR_CHANNELID_PWRMODE_BYTE];
                 
                SwcRte_SetNextHwVariant(HwVariantId); /* RTE/SysDal function not yet defined*/
            }
            break;    
            
            case 'P':
            {    
                /*get TX response message ID corresponding to the current received status request*/
                AppResponseMessageId = pDataMessagePtr[SWCVDR_RESPONSE_MSG_ID_BYTE]; 
                
                /*validate respoinse message id against configuration*/ 
                if(SWCRTE_TRUE == SwcRte_IsResponseMsgIdValid(pDataMessagePtr))
                {            
                    pReplyDataMessagePtr = (SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pMessgeList[AppTxMessageId]).pDataMessagePtr;
            
                    pReplyDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE] = AppResponseMessageId;
                    
                    pReplyDataMessagePtr[SWCVDR_MESSAGE_TYPE_BYTE] = SCWRTE_TX_ON_REQUEST;
                    
                    HwVariantId = SwcRte_GetCurrentHwVariant();/* RTE/SysDal function not yet defined*/
                    
                    pReplyDataMessagePtr[SWCVDR_RESPONSE_MSG_ID_BYTE] = (char)HwVariantId;
                }
            }    
            break;
                
            default :
            break;         
        }        
    }
}
#endif /*SWCRTE_ENABLE_HW_VARIANT == SWCRTE_STD_ON*/


/*================================================================================================*/
/**
@brief      SwcRte_IsResponseMsgIdValid - this function is used to check if a given Rx message 
            contains valid TX response characteristics 
@details    In order to have a correct TX response to a given RX request:
            - The RX request should correct a valid TX message ID
            - the configuration data for the contained TX message ID should, also, contain the 
            original message ID 
                        
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     boolean_t
@retval     SWCRTE_TRUE or SWCRTE_FALSE

@pre None
@post None
*/
/*================================================================================================*/
static boolean_t SwcRte_IsResponseMsgIdValid(SwcRte_DataMessageType * pRxDataMessagePtr)
{
    boolean_t RetVal = SWCRTE_FALSE;
    SwcRte_AppMessageIdType  AppTxResponseMessageId = pRxDataMessagePtr[SWCVDR_RESPONSE_MSG_ID_BYTE];
    SwcRte_AppMessageIdType  AppRxMessageId         = pRxDataMessagePtr[SWCVDR_MESSAGE_ID_BYTE];
    
    if(AppTxResponseMessageId < SWCRTE_MAX_TX_MESSAGE_IDS)
    {
        if((SwcVdr_GlobalCfgPtr[SWCVDR_INSTANCE_ID].pRxMessageList[AppRxMessageId]).AssociatedTxMsgId == AppTxResponseMessageId)
        {
            RetVal = SWCRTE_TRUE;
        }    
    }
        
    return RetVal;
}

#if (SWCRTE_RTM_ENABLE == SWCRTE_STD_ON)
/*================================================================================================*/
/**
@brief      SwcVdr_ProcessReqRtmMessage - return the Command that was remotely issues to VDR and decode it
@details    
                        
@param[in]  SwcRte_DataMessageType    Pointer to data message

@return     Message type
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
static void SwcVdr_ProcessReqRtmMessage(SwcRte_DataMessageType *  pDataMessagePtr)
{
    /*To Do: add RTM specific TX-info*/    
}
#endif


#endif


/*================================================================================================*/

#ifdef __cplusplus
}
#endif
/** @} */
