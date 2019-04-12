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
#include "Std_Types.h"
#include "Mcal.h"
#include "ComDal_Types.h"
#include "ComDal_Cfg.h"
#include "ComDal_Can.h"



#ifdef IFWK_USE_CAN
    #include "Can.h"
    #include "CanIf_Cbk.h"
    #include "Can_GeneralTypes.h"
#endif 
/*=================================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
===================================================================================================================================*/
#define COMDAL_CAN_VENDOR_ID_C                       43

#define COMDAL_CAN_AR_RELEASE_MAJOR_VERSION_C        4
#define COMDAL_CAN_AR_RELEASE_MINOR_VERSION_C        3
#define COMDAL_CAN_AR_RELEASE_REVISION_VERSION_C     1

#define COMDAL_CAN_SW_MAJOR_VERSION_C                0
#define COMDAL_CAN_SW_MINOR_VERSION_C                8
#define COMDAL_CAN_SW_PATCH_VERSION_C                1

/*=================================================================================================================================
*                                     FILE VERSION CHECKS
===================================================================================================================================*/
#if COMDAL_MAX_CAN_DESCRIPTORS > 0 
/* Check if source file and Comdal configuration header file are of the same vendor */
#if (COMDAL_CAN_VENDOR_ID_C != COMDAL_CFG_VENDOR_ID)
    #error "ComDal_Can.c and ComDal_Cfg.h have different vendor ids"
#endif

/* Check if source file and Comdal configuration header file are of the same Autosar version */
#if ((COMDAL_CAN_AR_RELEASE_MAJOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_CAN_AR_RELEASE_MINOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_CAN_AR_RELEASE_REVISION_VERSION_C != COMDAL_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Can.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and Comdal configuration header file are of the same Software version */
#if ((COMDAL_CAN_SW_MAJOR_VERSION_C != COMDAL_CFG_SW_MAJOR_VERSION) || \
     (COMDAL_CAN_SW_MINOR_VERSION_C != COMDAL_CFG_SW_MINOR_VERSION) || \
     (COMDAL_CAN_SW_PATCH_VERSION_C != COMDAL_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal_Can.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and Comdal types header file are of the same vendor */
#if (COMDAL_CAN_VENDOR_ID_C != COMDAL_TYPES_VENDOR_ID)
    #error "ComDal_Can.c and ComDal_Types.h have different vendor ids"
#endif

/* Check if source file and Comdal types header file are of the same Autosar version */
#if ((COMDAL_CAN_AR_RELEASE_MAJOR_VERSION_C != COMDAL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_CAN_AR_RELEASE_MINOR_VERSION_C != COMDAL_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_CAN_AR_RELEASE_REVISION_VERSION_C != COMDAL_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Can.c and ComDal_Types.h are different"
#endif

/* Check if source file and Comdal types header file are of the same Software version */
#if ((COMDAL_CAN_SW_MAJOR_VERSION_C != COMDAL_TYPES_SW_MAJOR_VERSION) || \
     (COMDAL_CAN_SW_MINOR_VERSION_C != COMDAL_TYPES_SW_MINOR_VERSION) || \
     (COMDAL_CAN_SW_PATCH_VERSION_C != COMDAL_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal_Can.c and ComDal_Types.h are different"
#endif

/* Check if source file and Comdal Can header file are from the same vendor */
#if (COMDAL_CAN_VENDOR_ID_C != COMDAL_CAN_VENDOR_ID)
    #error "ComDal_Can.c and ComDal_Can.h have different vendor ids"
#endif

/* Check if source file and Comdal Can header file are of the same Autosar version */
#if ((COMDAL_CAN_AR_RELEASE_MAJOR_VERSION_C != COMDAL_CAN_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_CAN_AR_RELEASE_MINOR_VERSION_C != COMDAL_CAN_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_CAN_AR_RELEASE_REVISION_VERSION_C != COMDAL_CAN_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal_Can.c and ComDal_Can.h are different"
#endif

/* Check if source file and Comdal Can header file are of the same Software version */
#if ((COMDAL_CAN_SW_MAJOR_VERSION_C != COMDAL_CAN_SW_MAJOR_VERSION) || \
     (COMDAL_CAN_SW_MINOR_VERSION_C != COMDAL_CAN_SW_MINOR_VERSION) || \
     (COMDAL_CAN_SW_PATCH_VERSION_C != COMDAL_CAN_SW_PATCH_VERSION) \
    )
  #error "Software Version Numbers of ComDal_Can.c and ComDal_Can.h are different"
#endif

#ifndef DISABLE_MCAL_INTERMODULE_ASR_CHECK
 /* Check if source file and Std_Types header file are of the same AutoSar version */
 #if ((COMDAL_CAN_AR_RELEASE_MAJOR_VERSION_C != STD_AR_RELEASE_MAJOR_VERSION) || \
      (COMDAL_CAN_AR_RELEASE_MINOR_VERSION_C != STD_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of ComDal_Can.c and Std_Types.h are different"
 #endif
 /* Check if source file and Mcal header file are of the same AutoSar version */
 #if ((COMDAL_CAN_AR_RELEASE_MAJOR_VERSION_C != MCAL_AR_RELEASE_MAJOR_VERSION) || \
      (COMDAL_CAN_AR_RELEASE_MINOR_VERSION_C != MCAL_AR_RELEASE_MINOR_VERSION) \
     )
 #error "AutoSar Version Numbers of ComDal_Can.c and Mcal.h are different"
 #endif 
#endif
#endif

/*=================================================================================================================================
*                                   LOCAL TYPES
===================================================================================================================================*/

typedef enum
{
    TX_INITIALIZED_STATE  = 0U,       /**< @brief CAN Tx channel is initialized. */
    TX_REQUESTED_STATE,               /**< @brief CAN Tx channel has a requested transmision*/
    TX_IDLE_STATE,                    /**< @brief CAN Tx channel is IDLE*/
    TX_PENDING_STATE,                 /**< @brief CAN Tx channel is Pending transmission */
    TX_ERROR_STATE = 255,             /**< @brief CAN Tx channel is in an error state*/
} ComDal_Can_aeTxStateType;

#if COMDAL_MAX_CAN_DESCRIPTORS > 0 
/*=================================================================================================================================
                                       GLOBAL CONSTANTS
===================================================================================================================================*/
static P2CONST(ComDal_ConfigType, AUTOMATIC, CAN_APPL_CONST) ComDal_pCanConfigPtr;

/*=================================================================================================================================
                                       GLOBAL VARIABLES
===================================================================================================================================*/
static VAR(ComDal_Can_aeTxStateType, AUTOMATIC) ComDal_Can_aeTxState[COMDAL_MAX_CAN_DESCRIPTORS];

static VAR(uint8, AUTOMATIC)   ComDal_Can_au8TxConfirmation[COMDAL_MAX_CAN_DESCRIPTORS];
static VAR(uint8, AUTOMATIC)   ComDal_Can_au8TxTimeout[COMDAL_MAX_CAN_DESCRIPTORS];
static VAR(boolean, AUTOMATIC) ComDal_Can_abTxFlag[COMDAL_MAX_CAN_DESCRIPTORS];

static VAR(ComDal_ReturnType, AUTOMATIC) ComDal_Can_aeRxState[COMDAL_MAX_CAN_DESCRIPTORS];

/*=================================================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
===================================================================================================================================*/

/*=================================================================================================================================
*                                       LOCAL FUNCTIONS
===================================================================================================================================*/
static FUNC(void, COMDAL_APP_CODE) ComDal_Can_PrepareTxMessage(VAR(ComDal_ChannelType, AUTOMATIC)  ComChannel, P2VAR(Can_PduType, AUTOMATIC, CAN_APPL_VAR) PduInfo);


/*==================================================================================================================================
*                                       GLOBAL FUNCTIONS
===================================================================================================================================*/
/*=================================================================================================================================*/
/**
@brief      ComDal_Can_Init - Initialization function for COMDAL CAN components
@details    This function shall:
             - initialize all global variables used by CAN component.
             - enable interrupts for channels NOT using polling mode  
             - Start CAN controller. 
            
@return     None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Can_Init(P2CONST(ComDal_ConfigType, AUTOMATIC, CAN_APPL_CONST) ConfigPtr)
{
    static VAR(boolean, AUTOMATIC) ComDal_Can_abControllerModeState[COMDAL_MAX_CAN_HW_CONTROLERS];
    VAR(Can_ReturnType, AUTOMATIC) ReturnValue = CAN_OK;
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) CanDescriptorId = 0;
    VAR(uint8, AUTOMATIC) HwUnitindex;
    
    ComDal_pCanConfigPtr = ConfigPtr;   

    for(HwUnitindex = 0; HwUnitindex < COMDAL_MAX_CAN_HW_CONTROLERS; HwUnitindex++)
    {
        ComDal_Can_abControllerModeState[HwUnitindex] = FALSE;
    }    
    
    
    for(CanDescriptorId = 0; CanDescriptorId < ComDal_pCanConfigPtr->CanChannelCount; CanDescriptorId++)
    {
        ComDal_Can_aeTxState[CanDescriptorId] = TX_INITIALIZED_STATE;
        
        ComDal_Can_aeRxState[CanDescriptorId] = COMDAL_INVALID;
   
        ComDal_Can_au8TxConfirmation[CanDescriptorId] = 0;

        ComDal_Can_au8TxTimeout[CanDescriptorId] = 0;
        
        if((FALSE == ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).bPollingEnabled)) 
        {
            Can_EnableControllerInterrupts(((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanControllerId);
        }   
        else
        {
            Can_DisableControllerInterrupts(((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanControllerId);
        }    
        
        
        if(FALSE == ComDal_Can_abControllerModeState[((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanControllerId])
        {    
            ComDal_Can_abControllerModeState[((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanControllerId] = TRUE;
            ReturnValue = Can_SetControllerMode(((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanControllerId, CAN_T_START);
            
            if(ReturnValue != CAN_OK)
            {
                ComDal_Can_aeTxState[CanDescriptorId] = TX_ERROR_STATE;     
            }
        }    

    }
}

/*=================================================================================================================================*/
/**
@brief      ComDal_Can_DeInit - DeInitialization function for COMDAL CAN components
@details    This function shall:
             - deinitialize all global variables used by CAN component.
             - disnable all interrupts used by CAN channels
             - STOP CAN controller. 
@return     None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Can_DeInit(void)
{
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) CanDescriptorId = 0;
    
    for(CanDescriptorId = 0; CanDescriptorId <  ComDal_pCanConfigPtr->CanChannelCount; CanDescriptorId++)
    {
        ComDal_Can_aeTxState[CanDescriptorId] = TX_INITIALIZED_STATE;
        
        ComDal_Can_aeRxState[CanDescriptorId] = COMDAL_INVALID;
   
        ComDal_Can_au8TxConfirmation[CanDescriptorId] = 0;

        ComDal_Can_au8TxTimeout[CanDescriptorId] = 0;
        
        if((FALSE == ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).bPollingEnabled)) 
        {
            Can_DisableControllerInterrupts(((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanControllerId);
        }    
        
        (void)Can_SetControllerMode((((ComDal_pCanConfigPtr->pCanChanDescriptor))[CanDescriptorId]).CanControllerId, CAN_T_STOP);
    }    
          
    ComDal_pCanConfigPtr = NULL_PTR;
}


/*=================================================================================================================================*/
/**
@brief      ComDal_Main - Main function used to handle state-machine of each CAN channel 
@details    For each CAN channel, this function shall:
            - check if a new TX request was issued and if Yes, prepare TX message
            - when polling mode is used, cyclicly check if message was transmited succesfully by calling Can_MainFunction_Write
            - when polling mode is used, cyclicly check if a new RX message was received succesfully by calling Can_MainFunction_Read
            
@return     None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Can_MainFunction(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel)
{
    /* local variables here */
    VAR(Can_PduType, AUTOMATIC) CanMessage;
    VAR(Can_HwHandleType, AUTOMATIC) CanHardwareObject;
    VAR(Can_ReturnType, AUTOMATIC) ReturnValue = CAN_OK;
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) CanDescriptorId = 0;

    CanDescriptorId = (ComDal_pCanConfigPtr->pComChannelMap)[ComChannel].ComDescriptorIndex; 
    /* state-machine logic */
    switch(ComDal_Can_aeTxState[CanDescriptorId])
    {
        case TX_REQUESTED_STATE:
        {
            ComDal_Can_PrepareTxMessage(ComChannel, &CanMessage);
            
            CanHardwareObject = ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanHwObject;
            
            ReturnValue = Can_Write(CanHardwareObject, &CanMessage);

            if(CAN_OK == ReturnValue)
            {
                ComDal_Can_au8TxTimeout[CanDescriptorId] = 0;
                
                ComDal_Can_abTxFlag[CanDescriptorId] = FALSE;
                
                /* the message was prepared for transmission - proceed to transmit state */
                ComDal_Can_aeTxState[CanDescriptorId] = TX_PENDING_STATE;
            }
            else
            {
                 ComDal_Can_aeTxState[CanDescriptorId] = TX_ERROR_STATE;
            }
        } break;

        case TX_PENDING_STATE:
        {
            /** Wait for  Tx confirmation */
            if((FALSE == ComDal_Can_abTxFlag[CanDescriptorId]) && (ComDal_Can_au8TxTimeout[CanDescriptorId] < COMDAL_CAN_TRANSMIT_TIMEOUT))
            {
                /*check if Pooling is used*/                
                if(TRUE == ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).bPollingEnabled)
                {    
                    Can_MainFunction_Write();
                }
                
                /*increment the timeout*/
                ComDal_Can_au8TxTimeout[CanDescriptorId]++;
            }
            else
            {
                if(FALSE == ComDal_Can_abTxFlag[CanDescriptorId])
                {
                    ComDal_Can_aeTxState[CanDescriptorId] = TX_ERROR_STATE;                  
                }
            }
        } break;

        default:
        {
            /* if we got here, something went terribly wrong*/
        }
        break;        
    }     
    
    if(TRUE == ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).bPollingEnabled)
    {
        /** Wait for  Rx confirmation */
        Can_MainFunction_Read();        
    }
}


/*=================================================================================================================================*/
/**
@brief      ComDal_Can_ReadData - API used to provide data that was read from the CAN.
@details    This function will provide users with the data received on the CAN line for the provided
            input channel.
            This function shall return  COMDAL_OBSOLETE if no new CAN message was received for that channel; 
            if COMDAL was not properly initialized it shall return COMDAL_INVALID. 
            This function shall return COMDAL_NO_ERROR whenever the data received has be updated.
  
@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  CanDataLen     Maximum data length provided for that channel
@param[out] ReadBuffer     Data read from CAN for the assigned input channel.

  
@return     ComDal_ReturnType: COMDAL_NO_ERROR, COMDAL_OBSOLETE, COMDAL_INVALID
*/
/*=================================================================================================================================*/
FUNC(ComDal_ReturnType, COMDAL_APP_CODE) ComDal_Can_ReadData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) ReadBuffer, VAR(uint8, AUTOMATIC) CanDataLen)
{
    VAR(uint8, AUTOMATIC) MsgIndex;
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) CanDescriptorId = 0;
    VAR(ComDal_ReturnType, AUTOMATIC) ReturnValue = COMDAL_NO_ERROR;
    
    if(NULL_PTR != ComDal_pCanConfigPtr)
    {
        CanDescriptorId   =  (ComDal_pCanConfigPtr->pComChannelMap)[ComChannel].ComDescriptorIndex;

        if(COMDAL_NO_ERROR == ComDal_Can_aeRxState[CanDescriptorId] )
        {
            /*write external buffer */
            for(MsgIndex =0; MsgIndex < CanDataLen; MsgIndex++)
            {   
                ReadBuffer[MsgIndex] = (char)(((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).pDataBuffer[MsgIndex]);             
            }
            
            ComDal_Can_aeRxState[CanDescriptorId] = COMDAL_OBSOLETE;
        }
        else
        {
            ReturnValue = ComDal_Can_aeRxState[CanDescriptorId];            
        }
    }
    
    return ReturnValue;
}


/*=================================================================================================================================*/
/**
@brief      ComDal_Can_WriteData - function used to create a CAN write request if no CAN TX is ongoing

@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  CanDataLen     Maximum data length provided for that channel
@param[out] TxDataString   Data to be written on CAN for the assigned input channel.


@return     none
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Can_WriteData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) TxDataString, VAR(uint8, AUTOMATIC) CanDataLen)
{
    VAR(uint8, AUTOMATIC) index;
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) CanDescriptorId = 0;

    if(NULL_PTR != ComDal_pCanConfigPtr)
    {
        CanDescriptorId = (ComDal_pCanConfigPtr->pComChannelMap)[ComChannel].ComDescriptorIndex;
        
        /*check if not transmition is ongoing*/
        if((TX_IDLE_STATE == ComDal_Can_aeTxState[CanDescriptorId]) || (TX_INITIALIZED_STATE == ComDal_Can_aeTxState[CanDescriptorId]))
        {
            /*update Tx data buffer with new data */ 
            for(index =0; index < CanDataLen; index++)
            {   
                (((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).pDataBuffer)[index] = (uint8)TxDataString[index];   
            }

           /*enable a new transmition*/
           ComDal_Can_aeTxState[CanDescriptorId] = TX_REQUESTED_STATE;           
        }
    }
}

/*=================================================================================================================================*/
/**
@brief      CanIf_TxConfirmation - callback function to simulate CanIf
@details    This callback is called from CAN driver whenever a new TX message was succesfully 
            transmited.
            On TX complete the TX line becomes IDLE and current TX request buffer is cleared. 
            
@return     none
*/
/*=================================================================================================================================*/
FUNC(void, CANIF_CODE) CanIf_TxConfirmation(VAR(PduIdType, AUTOMATIC) CanTxPduId)
{
    volatile VAR(uint8, AUTOMATIC) index;
    volatile VAR(PduIdType, AUTOMATIC) swPduHandle;
    volatile VAR(ComDal_BswDescriptorIdType, AUTOMATIC) CanDescriptorId = 0;    
    
    for(CanDescriptorId = 0; CanDescriptorId < COMDAL_MAX_CAN_DESCRIPTORS; CanDescriptorId++)
    {
        swPduHandle = ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).SwPduHandle;
    
        /*get the decriptor that matches in id and Handle**/ 
        if(CanTxPduId == swPduHandle)
        {
            /* Increment counter to record transmission of a message */
            ComDal_Can_au8TxConfirmation[CanDescriptorId]++;
            
            ComDal_Can_abTxFlag[CanDescriptorId] = TRUE;
    
            ComDal_Can_aeTxState[CanDescriptorId] = TX_IDLE_STATE;
            
            /*clear internal Tx Data */
            for(index =0; index < ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanDataLen; index++)
            {   
                (((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).pDataBuffer)[index] = (char)0U;   
            }
    
            /*intentional loop break to reduce run-time since only one match is expected*/
            break;
        }
    }
}


/*=================================================================================================================================*/
/**
@brief      CanIf_RxIndication - callback function to simulate CanIf
@details    This callback is called from CAN driver whenever a new RX message was succesfully 
            received.
            This function will identify the channel descriptor for which this message was sent
            and store received data in its allocated buffer.            

@return     none            
*/
/*=================================================================================================================================*/
FUNC(void, CANIF_CODE) CanIf_RxIndication(P2CONST(Can_HwType, AUTOMATIC, COMDAL_APPL_DATA) mailbox, P2CONST(PduInfoType, AUTOMATIC, COMDAL_APPL_DATA) Rx_Pdu)
{
    /** Local variable */
    /*volatile VAR(PduIdType, AUTOMATIC) swPduHandle;*/
    volatile VAR(Can_IdType, AUTOMATIC) id;
    volatile VAR(uint8, AUTOMATIC) index = 0U;
    volatile VAR(ComDal_BswDescriptorIdType, AUTOMATIC) CanDescriptorId = 0;    
    
    for(CanDescriptorId = 0; CanDescriptorId < COMDAL_MAX_CAN_DESCRIPTORS; CanDescriptorId++)
    {
        /*swPduHandle = ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).SwPduHandle;*/
        id = ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).PduId;
    
        /*get the decriptor that matches in id and Handle**/ 
        if(mailbox->CanId == id)
        {                      
            /*copy received data to internal Rx buffer */
            for(index =0; index < Rx_Pdu->SduLength; index++)
            {
                (((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).pDataBuffer)[index] = (char)(Rx_Pdu->SduDataPtr[index]);                 
            }
            
            ComDal_Can_aeRxState[CanDescriptorId] = COMDAL_NO_ERROR;    
    
            /*intentional loop break to reduce run-time since only one match is expected*/
            break;
        }
    }
}


/*=================================================================================================================================*/
/**
@brief      ComDal_Can_PrepareTxMessage internal function used to setup the CAN message with specific parameters

@return     none
*/
/*=================================================================================================================================*/
static FUNC(void, COMDAL_APP_CODE) ComDal_Can_PrepareTxMessage(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(Can_PduType, AUTOMATIC, CAN_APPL_VAR) PduInfo)
{
    VAR(ComDal_BswDescriptorIdType, AUTOMATIC) CanDescriptorId = 0;
    CanDescriptorId = (ComDal_pCanConfigPtr->pComChannelMap)[ComChannel].ComDescriptorIndex;

    /* Disable interrupts*/
    SuspendAllInterrupts(); /*TODO: add exclusive area */
    
    /** ID, length, etc. */
    PduInfo->length = ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).CanDataLen;
    PduInfo->swPduHandle = ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).SwPduHandle;
    PduInfo->sdu = (uint8 *)(((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).pDataBuffer);
    PduInfo->id = ((ComDal_pCanConfigPtr->pCanChanDescriptor)[CanDescriptorId]).PduId;
    
    /*Re-enable Interrupts*/    
    ResumeAllInterrupts(); /*TODO: add exclusive area */
}



#if (CAN_BUSOFFPOLL_SUPPORTED == STD_ON)
/*=================================================================================================================================*/
/**
@brief      CanIf_ControllerBusOff - callback function to simulate CanIf
@details    This callback can be called to handle Bus Off request if BusOff is handled in polling mode
            The definition of this function is required by Can driver

@return     none
*/
/*=================================================================================================================================*/
FUNC(void, CANIF_CODE) CanIf_ControllerBusOff(VAR(uint8, AUTOMATIC) Controller)
{
    /*stub function definition required by Can driver - this function is not currently used*/
    (void)Controller; /*parameter currently not used*/
}
#endif

/*=================================================================================================================================*/
/**
@brief      CanIf_RxIndication - callback function to simulate CanIf
@details    This callback is called from Can Driver: Can_SetControllerMode to inform higher levels about the controller state.
            The definition of this function is required by Can driver

@return     none 
*/        
/*=================================================================================================================================*/    
FUNC(void, CANIF_CODE) CanIf_ControllerModeIndication(VAR(uint8, AUTOMATIC) Controller, VAR(CanIf_ControllerModeType, AUTOMATIC) ControllerMode)
{
    /*stub function definition required by Can driver  - this function is not currently used*/
    (void)Controller;      /*parameter currently not used*/
    (void)ControllerMode;  /*parameter currently not used*/
}

#endif /*COMDAL_MAX_CAN_DESCRIPTORS*/
/*=================================================================================================================================*/
#ifdef __cplusplus
}
#endif
/** @} */
