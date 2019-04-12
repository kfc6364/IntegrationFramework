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
/*===================================================================================================================================
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
#include "Mcal.h"
#include "Compiler.h"

#include "ComDal_Types.h"
#include "ComDal_Cfg.h"
#include "ComDal.h"
#include "ComDal_Can.h"
#include "ComDal_Nfc.h"
#include "ComDal_Uart.h"

#if (COMDAL_DEV_ERROR_DETECT == STD_ON)
    #include "Det.h"
#endif /* COMDAL_DEV_ERROR_DETECT == STD_ON */



/*=================================================================================================================================
*                              SOURCE FILE VERSION INFORMATION
===================================================================================================================================*/
#define COMDAL_VENDOR_ID_C                       43

#define COMDAL_AR_RELEASE_MAJOR_VERSION_C        4
#define COMDAL_AR_RELEASE_MINOR_VERSION_C        3
#define COMDAL_AR_RELEASE_REVISION_VERSION_C     1

#define COMDAL_SW_MAJOR_VERSION_C                0
#define COMDAL_SW_MINOR_VERSION_C                8
#define COMDAL_SW_PATCH_VERSION_C                1


/*=================================================================================================================================
*                                     FILE VERSION CHECKS
===================================================================================================================================*/

/* Check if source file and ComDal header file are of the same vendor */
#if (COMDAL_VENDOR_ID_C != COMDAL_VENDOR_ID)
    #error "ComDal.c and ComDal.h have different vendor ids"
#endif

/* Check if source file and ComDal header file are of the same Autosar version */
#if ((COMDAL_AR_RELEASE_MAJOR_VERSION_C != COMDAL_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_AR_RELEASE_MINOR_VERSION_C != COMDAL_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_AR_RELEASE_REVISION_VERSION_C != COMDAL_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal.c and ComDal.h are different"
#endif

/* Check if source file and ComDal header file are of the same Software version */
#if ((COMDAL_SW_MAJOR_VERSION_C != COMDAL_SW_MAJOR_VERSION) || \
     (COMDAL_SW_MINOR_VERSION_C != COMDAL_SW_MINOR_VERSION) || \
     (COMDAL_SW_PATCH_VERSION_C != COMDAL_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal.c and ComDal.h are different"
#endif

/* Check if source file and ComDal Types header file are from the same vendor */
#if (COMDAL_VENDOR_ID_C != COMDAL_TYPES_VENDOR_ID)
    #error "ComDal.c and ComDal_Types.h have different vendor ids"
#endif

/* Check if source file and ComDal Types header file are of the same Autosar version */
#if ((COMDAL_AR_RELEASE_MAJOR_VERSION_C != COMDAL_TYPES_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_AR_RELEASE_MINOR_VERSION_C != COMDAL_TYPES_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_AR_RELEASE_REVISION_VERSION_C != COMDAL_TYPES_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal.c and ComDal_Types.h are different"
#endif

/* Check if source file and ComDal Types headerr file are of the same Software version */
#if ((COMDAL_SW_MAJOR_VERSION_C != COMDAL_TYPES_SW_MAJOR_VERSION) || \
     (COMDAL_SW_MINOR_VERSION_C != COMDAL_TYPES_SW_MINOR_VERSION) || \
     (COMDAL_SW_PATCH_VERSION_C != COMDAL_TYPES_SW_PATCH_VERSION) \
    )
  #error "Software Version Numbers of ComDal.c and ComDal_Types.h are different"
#endif


 /* Check if source file and DET header file are of the same version */
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)
    #if ((COMDAL_AR_RELEASE_MAJOR_VERSION_C != DET_AR_RELEASE_MAJOR_VERSION) || \
         (COMDAL_AR_RELEASE_MINOR_VERSION_C != DET_AR_RELEASE_MINOR_VERSION) \
        )
    #error "AutoSar Version Numbers of ComDal.c and Det.h are different"
    #endif
#endif


/* Check if source file and ComDal configuration header file are of the same vendor */
#if (COMDAL_VENDOR_ID_C != COMDAL_CFG_VENDOR_ID)
    #error "ComDal.c and ComDal_Cfg.h have different vendor ids"
#endif

/* Check if source file and ComDal configuration header file are of the same Autosar version */
#if ((COMDAL_AR_RELEASE_MAJOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_AR_RELEASE_MINOR_VERSION_C != COMDAL_CFG_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_AR_RELEASE_REVISION_VERSION_C != COMDAL_CFG_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and ComDal configuration header file are of the same software version */
#if ((COMDAL_SW_MAJOR_VERSION_C != COMDAL_CFG_SW_MAJOR_VERSION) || \
     (COMDAL_SW_MINOR_VERSION_C != COMDAL_CFG_SW_MINOR_VERSION) || \
     (COMDAL_SW_PATCH_VERSION_C != COMDAL_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal.c and ComDal_Cfg.h are different"
#endif

/* Check if source file and ComDal Can header file are of the same vendor */
#if (COMDAL_VENDOR_ID_C != COMDAL_CAN_VENDOR_ID)
    #error "ComDal.c and ComDal_Can.h have different vendor ids"
#endif

/* Check if source file and ComDal Can header file are of the same Autosar version */
#if ((COMDAL_AR_RELEASE_MAJOR_VERSION_C != COMDAL_CAN_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_AR_RELEASE_MINOR_VERSION_C != COMDAL_CAN_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_AR_RELEASE_REVISION_VERSION_C != COMDAL_CAN_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal.c and ComDal_Can.h are different"
#endif

/* Check if source file and ComDal Can header file are of the same software version */
#if ((COMDAL_SW_MAJOR_VERSION_C != COMDAL_CAN_SW_MAJOR_VERSION) || \
     (COMDAL_SW_MINOR_VERSION_C != COMDAL_CAN_SW_MINOR_VERSION) || \
     (COMDAL_SW_PATCH_VERSION_C != COMDAL_CAN_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal.c and ComDal_Can.h are different"
#endif


/* Check if source file and ComDal Uart header file are of the same vendor */
#if (COMDAL_VENDOR_ID_C != COMDAL_UART_VENDOR_ID)
    #error "ComDal.c and ComDal_Uart.h have different vendor ids"
#endif

/* Check if source file and ComDal Uart header file are of the same Autosar version */
#if ((COMDAL_AR_RELEASE_MAJOR_VERSION_C != COMDAL_UART_AR_RELEASE_MAJOR_VERSION) || \
     (COMDAL_AR_RELEASE_MINOR_VERSION_C != COMDAL_UART_AR_RELEASE_MINOR_VERSION) || \
     (COMDAL_AR_RELEASE_REVISION_VERSION_C != COMDAL_UART_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of ComDal.c and ComDal_Uart.h are different"
#endif

/* Check if source file and ComDal Uart header file are of the same software version */
#if ((COMDAL_SW_MAJOR_VERSION_C != COMDAL_UART_SW_MAJOR_VERSION) || \
     (COMDAL_SW_MINOR_VERSION_C != COMDAL_UART_SW_MINOR_VERSION) || \
     (COMDAL_SW_PATCH_VERSION_C != COMDAL_UART_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of ComDal.c and ComDal_Uart.h are different"
#endif



/*=================================================================================================================================
*                                       LOCAL TYPES
===================================================================================================================================*/
typedef enum
{
    COMDAL_INIT     = 0U,     /**< @brief mark No error detected for analog descriptor. */
    COMDAL_DEINIT,            /**< @brief mark conversion on-going for analog descriptor. */
    COMDAL_UNINIT,            /**< @brief mark conversion error detected for analog descriptor. */ 
}ComDal_aeModuleStateType;


/*=================================================================================================================================
                                       GLOBAL CONSTANTS
===================================================================================================================================*/
/**
* @brief          Global Configuration Pointer.
* @details        Data structure containing the set of configuration parameters required for
*                 initializing the COMDAL components.
*
*/
P2CONST(ComDal_ConfigType, COMDAL_VAR, COMDAL_APP_CONST) ComDal_pGlobalConfigPtr = NULL_PTR;


/**
* @brief          Variable storing ComDal module state 
* @details        Possible values: UNIT, INIT, DEINIT
*/
static VAR(ComDal_aeModuleStateType,  AUTOMATIC) ComDal_aeModuleState = COMDAL_UNINIT;
/*=================================================================================================================================
*                                   LOCAL FUNCTION PROTOTYPES
===================================================================================================================================*/


/*=================================================================================================================================
*                                       LOCAL FUNCTIONS
===================================================================================================================================*/
static inline FUNC(Std_ReturnType, IODAL_APP_CODE) ComDal_ValidateComChannel(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, VAR(uint8, AUTOMATIC) ApiId);
/*=================================================================================================================================
*                                       GLOBAL FUNCTIONS
===================================================================================================================================*/

/*=================================================================================================================================*/
/**
@brief      ComDal_Init - Initialization function for Communications Driver abstraction module
@details    Shall be used to initialize all subcomponents

@param[in]  ConfigPtr    Pointer to configuration data (this data is shared between all CAMDAL components)    
            
@return     None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_Init(P2CONST(ComDal_ConfigType, AUTOMATIC, COMDAL_APP_CONST) ConfigPtr)
{
    if(COMDAL_INIT != ComDal_aeModuleState)
    {    
        if(NULL_PTR != ConfigPtr)
        {            
            ComDal_pGlobalConfigPtr = ConfigPtr;

#if COMDAL_MAX_CAN_DESCRIPTORS > 0U
            /*initialize CAN channels */ 
            if(ComDal_pGlobalConfigPtr->CanChannelCount != 0)
            {    
                ComDal_Can_Init(ComDal_pGlobalConfigPtr); 
            }
#endif            

#if COMDAL_MAX_LIN_DESCRIPTORS > 0U
            /*initialize LIN channels */ 
            if(ComDal_pGlobalConfigPtr->LinChannelCount != 0)
            {            
                ComDal_Lin_Init(ComDal_pGlobalConfigPtr);
            }
#endif            

#if (COMDAL_MAX_ETH_DESCRIPTORS > 0U) 
            /*initialize LIN channels */ 
            if(ComDal_pGlobalConfigPtr->EthChannelCount != 0)
            {    
                ComDal_Eth_Init(ComDal_pGlobalConfigPtr);
            }
#endif    

#if (COMDAL_MAX_UART_DESCRIPTORS > 0U) 
            /*initialize digital i/o components if DIO, OCU or ICU channels are used */ 
            if(ComDal_pGlobalConfigPtr->UartChannelCount != 0)
            {    
                ComDal_Uart_Init(ComDal_pGlobalConfigPtr);
            }
#endif            

#if (COMDAL_MAX_NFC_DESCRIPTORS > 0U) 
            /* initialize nfc component */ 
            if(ComDal_pGlobalConfigPtr->NfcChannelCount != 0)
            {    
                ComDal_Nfc_Init(ComDal_pGlobalConfigPtr);
            }
#endif             
            ComDal_aeModuleState = COMDAL_INIT;        
        }
        else
        {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
        Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_INIT_API_ID, COMDAL_E_PARAM_CONFIG);
#endif            
        }    
    }
    else
    {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
        Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_INIT_API_ID, COMDAL_E_ALREADY_INITIALIZED);
#endif    
    }

}


/*================================================================================================================================*/
/**
@brief      ComDal_DeInit - De-Initialization function for Communications Driver abstraction module
@details    Shall be used to deinitialize all subcomponents

            
@return     None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_DeInit(void)
{
    if(COMDAL_DEINIT != ComDal_aeModuleState)
    {        
#if COMDAL_MAX_CAN_DESCRIPTORS > 0U
        /*initialize CAN channels */ 
        if(ComDal_pGlobalConfigPtr->CanChannelCount != 0)
        {    
            ComDal_Can_DeInit(); 
        }
#endif            

#if COMDAL_MAX_LIN_DESCRIPTORS > 0U
        /*initialize LIN channels */ 
        if(ComDal_pGlobalConfigPtr->LinChannelCount != 0)
        {            
            ComDal_Lin_DeInit();
        }
#endif            

#if (COMDAL_MAX_ETH_DESCRIPTORS > 0U) 
        /*initialize LIN channels */ 
        if(ComDal_pGlobalConfigPtr->EthChannelCount != 0)
        {    
            ComDal_Eth_DeInit();
        }
#endif    

#if (COMDAL_MAX_UART_DESCRIPTORS > 0U) 
        /*initialize digital i/o components if DIO, OCU or ICU channels are used */ 
        if(ComDal_pGlobalConfigPtr->UartChannelCount != 0)
        {    
            ComDal_Uart_DeInit();
        }
#endif            

#if COMDAL_MAX_NFC_DESCRIPTORS > 0U
        /*de-initialize NFC channels */ 
        if(ComDal_pGlobalConfigPtr->NfcChannelCount != 0)
        {    
            ComDal_Nfc_DeInit(); 
        }
#endif 
        ComDal_pGlobalConfigPtr = NULL_PTR;
        ComDal_aeModuleState = COMDAL_DEINIT;
        
    }
    else
    {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
        Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_DEINIT_API_ID, COMDAL_E_UNINIT);
#endif    
    }
}


/*=================================================================================================================================*/
/**
@brief      ComDal_Main - Main function for COMDAL
@details    Shall be used to handle cyclic functions for each COMDAL channel
            
@return     None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_MainFunction(void)
{
    VAR(uint8, AUTOMATIC)  ComDalChannel;
    VAR(ComDal_BswChannelType, AUTOMATIC)  ChannelType;
    VAR(uint8, AUTOMATIC)  MaxComChannels = ComDal_pGlobalConfigPtr->CanChannelCount + ComDal_pGlobalConfigPtr->LinChannelCount + \
                                            ComDal_pGlobalConfigPtr->EthChannelCount + ComDal_pGlobalConfigPtr->UartChannelCount + \
                                            ComDal_pGlobalConfigPtr->NfcChannelCount;
   
    if(COMDAL_INIT == ComDal_aeModuleState)
    {
        for(ComDalChannel = 0U; ComDalChannel < MaxComChannels; ComDalChannel++)
        {
            ChannelType = ((ComDal_pGlobalConfigPtr->pComChannelMap))[ComDalChannel].ComChannelType;

            switch(ChannelType)
            {
#if (COMDAL_MAX_CAN_DESCRIPTORS > 0U)                
                case COMDAL_CAN_CHANNEL:
                {
                    ComDal_Can_MainFunction(ComDalChannel);
                }
                break;
#endif

#if (COMDAL_MAX_NFC_DESCRIPTORS > 0U)                
                case COMDAL_NFC_CHANNEL:
                {
                    ComDal_Nfc_Main(ComDalChannel);
                }
                break;
#endif


                default:
                {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
                    Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_MAINFUNCTION_API_ID, COMDAL_E_INVALID_CHANNEL_TYPE);
#endif            
                }
            }
        }
    }
    else
    {
        /*call Det: module not initialized*/
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
        Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_MAINFUNCTION_API_ID, COMDAL_E_UNINIT);
#endif    
    }   
}

/*=================================================================================================================================*/
/**
@brief      ComDal_ControllerReset - controller reset
@details    Shall be used to reset the NFC controller, overcoming hardware limitations
            NFC controller power line is kept on GND for 20 milliseconds.
            
@return     None

@pre None
@post None
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_ControllerReset(void)
{
#if (COMDAL_MAX_NFC_DESCRIPTORS > 0U)
    ComDal_Nfc_Controller_Reset();
#endif
}

/*=================================================================================================================================*/
/**
@brief      ComDal_WriteData - API by application to request transmision of new data on the give of the COMDAL channel
  
@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  RxDataLen      Maximum data length provided for that channel
@param[out] WriteBuffer     Data to be sent on the COMDAL channel.
*/
/*=================================================================================================================================*/
FUNC(void, COMDAL_APP_CODE) ComDal_WriteData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA)  WriteBuffer, VAR(uint8, AUTOMATIC) TxDataLen)
{
    VAR(ComDal_BswChannelType, AUTOMATIC) ComChannelType;

    if(COMDAL_INIT == ComDal_aeModuleState)
    {
        if(NULL_PTR != WriteBuffer)
        {        
            if(E_OK == ComDal_ValidateComChannel(ComChannel, COMDAL_WRITEDATA_API_ID))
            {
                ComChannelType = (ComDal_pGlobalConfigPtr->pComChannelMap)[ComChannel].ComChannelType;
              
                switch(ComChannelType)
                {
#if COMDAL_MAX_CAN_DESCRIPTORS > 0U                
                    case COMDAL_CAN_CHANNEL:
                    {
                        ComDal_Can_WriteData(ComChannel, WriteBuffer, TxDataLen);                    
                    }break;
#endif

#if COMDAL_MAX_UART_DESCRIPTORS > 0U           
                    case COMDAL_UART_CHANNEL:
                    {                    
                        ComDal_Uart_WriteData(ComChannel, WriteBuffer, TxDataLen);  
                    }break;    
#endif

#if COMDAL_MAX_NFC_DESCRIPTORS > 0U           
                    case COMDAL_NFC_CHANNEL:
                    {
                        ComDal_Nfc_WriteData(ComChannel, WriteBuffer, TxDataLen);
                    }break;
#endif

#if COMDAL_MAX_ETH_DESCRIPTORS > 0U
                    case COMDAL_ETH_CHANNEL:
                    break;
#endif

#if COMDAL_MAX_LIN_DESCRIPTORS > 0U          
                    case COMDAL_LIN_CHANNEL:
                    break;
#endif
                    
                    default :
                    {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
                        Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_WRITEDATA_API_ID, COMDAL_E_INVALID_CHANNEL_TYPE);
#endif            
                    }
                }    
            }            
            else
            {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
            Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_WRITEDATA_API_ID, COMDAL_E_INVALID_CHANNEL_ID);
#endif    
            }
        }
        else
        {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
            Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_WRITEDATA_API_ID, COMDAL_E_PARAM_POINTER);
#endif            
        }        
    }
    else
    {
        /*call Det: module not initialized*/
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
        Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_WRITEDATA_API_ID, COMDAL_E_UNINIT);
#endif    
    }    
}


/*=================================================================================================================================*/
/**
@brief      ComDal_ReadData - API used to provide application with data read from any of the comunication lines

@details      If the content of the provided ReadBuffer is equal to current content of the channel buffer
            this function shall return  COMDAL_OBSOLETE; if COMDAL was not properly initialized it shall 
            return COMDAL_INVALID. 
            This function shall return COMDAL_NO_ERROR whenever the data received has be updated.
  
@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  RxDataLen      Maximum data length provided for that channel
@param[out] ReadBuffer     Data read from the COMDAL channel.

  
@return     ComDal_ReturnType: COMDAL_NO_ERROR, COMDAL_OBSOLETE, COMDAL_INVALID
*/
/*=================================================================================================================================*/
FUNC(ComDal_ReturnType, COMDAL_APP_CODE) ComDal_ReadData(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, P2VAR(char, AUTOMATIC, COMDAL_APPL_DATA) ReadBuffer, VAR(uint8, AUTOMATIC) RxDataLen)
{
    VAR(ComDal_BswChannelType, AUTOMATIC) ComChannelType;
    VAR(ComDal_ReturnType, AUTOMATIC) ReturnValue = COMDAL_BUSY;

    if(COMDAL_INIT == ComDal_aeModuleState)
    {
        if(NULL_PTR != ReadBuffer)
        {    
            if(E_OK == ComDal_ValidateComChannel(ComChannel, COMDAL_READDATA_API_ID))
            {
                ComChannelType = (ComDal_pGlobalConfigPtr->pComChannelMap)[ComChannel].ComChannelType;
              
                switch(ComChannelType)
                {
#if COMDAL_MAX_CAN_DESCRIPTORS > 0U                
                    case COMDAL_CAN_CHANNEL:
                    {
                        ReturnValue = ComDal_Can_ReadData(ComChannel, ReadBuffer, RxDataLen);                    
                    }break;
#endif

#if COMDAL_MAX_UART_DESCRIPTORS > 0U           
                    case COMDAL_UART_CHANNEL:
                    {
                        ReturnValue = ComDal_Uart_ReadData(ComChannel, ReadBuffer, RxDataLen);
                    }break;    
#endif
                    
#if COMDAL_MAX_ETH_DESCRIPTORS > 0U                      
                    case COMDAL_ETH_CHANNEL:
                    break;
#endif

#if COMDAL_MAX_NFC_DESCRIPTORS > 0U           
                    case COMDAL_NFC_CHANNEL:
                    {
                        ReturnValue = ComDal_Nfc_ReadData(ComChannel, ReadBuffer, RxDataLen);
                    }
                    break;    
#endif

#if COMDAL_MAX_LIN_DESCRIPTORS > 0U                      
                    case COMDAL_LIN_CHANNEL:
                    break;
#endif                    
                    default :
                    {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
                        Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_READDATA_API_ID, COMDAL_E_INVALID_CHANNEL_TYPE);
#endif            
                    }break;
                }
            }
            else
            {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
            Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_READDATA_API_ID, COMDAL_E_INVALID_CHANNEL_ID);
#endif    
            }
        }
        else
        {
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
            Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_READDATA_API_ID, COMDAL_E_PARAM_POINTER);
#endif            
        }        
    }
    else
    {
        /*call Det: module not initialized*/
#if (COMDAL_DEV_ERROR_DETECT == STD_ON)        
        Det_ReportError((uint16)COMDAL_MODULE_ID, (uint8)0U, COMDAL_READDATA_API_ID, COMDAL_E_UNINIT);
#endif    
    }
    
    return ReturnValue;
    
}

/*=================================================================================================================================*/
/**
@brief      ComDal_ValidateComChannel - Validate com channel
@details    shall check if the given channel index is less than the maximum number of channels and also check if the channel is 
            configured to be used for read or write.

@param[in]  ComChannel     Logical BSW ComDal channel id.
@param[in]  ApiId          API id for which this function is called.
            
@return     Std_ReturnType: E_OK or E_NOT_OK
*/
/*=================================================================================================================================*/
static inline FUNC(Std_ReturnType, IODAL_APP_CODE) ComDal_ValidateComChannel(VAR(ComDal_ChannelType, AUTOMATIC) ComChannel, VAR(uint8, AUTOMATIC) ApiId)
{
    Std_ReturnType ReturnValue = E_OK;
    VAR(ComDal_AccessType, AUTOMATIC) AccessType;
    VAR(uint8, AUTOMATIC)  MaxComChannels = ComDal_pGlobalConfigPtr->CanChannelCount + ComDal_pGlobalConfigPtr->LinChannelCount + \
                                            ComDal_pGlobalConfigPtr->EthChannelCount  + ComDal_pGlobalConfigPtr->UartChannelCount + \
                                            ComDal_pGlobalConfigPtr->NfcChannelCount;
    
    AccessType = ((ComDal_pGlobalConfigPtr->pComChannelMap))[ComChannel].AccessType;
    
    if(ComChannel > MaxComChannels)
    {
        ReturnValue = E_NOT_OK;        
    } 
    else
    {
        if(((COMDAL_READDATA_API_ID == ApiId) && (AccessType != COMDAL_RXCHANNEL)) || 
           ((COMDAL_WRITEDATA_API_ID == ApiId) && (AccessType != COMDAL_TXCHANNEL)))
        {
            ReturnValue = E_NOT_OK;
        }
    }    

    return ReturnValue;    
}

#ifdef __cplusplus
}
#endif
/** @} */
