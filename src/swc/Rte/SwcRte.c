/**
    @file        SwcRte.c
*   @version     0.8.1
*
*   @brief       Integration Framework - SW component RTE file
*
*   @details     This file implements SwcRte file.  
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup SWCRTE
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
#include "Std_Types.h"
#include "SwcRte.h"
#include "SwcRte_Types.h"
#include "SwcSensors.h"
#include "SwcActuators.h"


#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
#include "SwcLighting.h"
#endif

#if (SWCRTE_MOTORCTRL_APP_ENABLED == SWCRTE_STD_ON)
#include "SwcMotorCtrl.h"
#endif

#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
#include "SwcVdr.h"
#endif

#if (SWCRTE_USE_IODAL == SWCRTE_STD_ON)
#include "IoDal.h"    
#endif

#if (SWCRTE_USE_SYSDAL == SWCRTE_STD_ON)
#include "SysDal.h"    
#endif

#if (SWCRTE_USE_MEMDAL == SWCRTE_STD_ON)
    
#endif

#if (SWCRTE_USE_COMDAL == SWCRTE_STD_ON)
#include "ComDal_Types.h"
#include "ComDal_Cfg.h"    
#include "ComDal.h"    
#endif

/*==================================================================================================
                                       SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define SWCRTE_VENDOR_ID_C                          43

#define SWCRTE_SW_MAJOR_VERSION_C                   0
#define SWCRTE_SW_MINOR_VERSION_C                   8
#define SWCRTE_SW_PATCH_VERSION_C                   1

/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/
/* Check if SwcRte.c source file and SwcRte.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID_C != SWCRTE_VENDOR_ID)
    #error "SwcRte.c and SwcRte.h have different vendor ids"
#endif

/* Check if SwcRte.c source file and SwcRte.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_C != SWCRTE_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_C != SWCRTE_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_C != SWCRTE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.c and SwcRte.h are different"
#endif

/* Check if SwcRte.c source file and  SwcRte_Types.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID_C != SWCRTE_TYPES_VENDOR_ID)
    #error "SwcRte.c and SwcRte_Types.h have different vendor ids"
#endif

/* Check if SwcRte.c source file and SwcRte_Types.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_C != SWCRTE_TYPES_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_C != SWCRTE_TYPES_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_C != SWCRTE_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.c and SwcRte_Types.h are different"
#endif

/* Check if SwcRte.c source file and SwcSensors.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID_C != SWCSENSORS_VENDOR_ID)
    #error "SwcRte.c and SwcSensors.h have different vendor ids"
#endif

/* Check if SwcLighting.c source file and SwcSensors.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_C != SWCSENSORS_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_C != SWCSENSORS_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_C != SWCSENSORS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.c and SwcSensors.h are different"
#endif

/* Check if SwcRte.c source file and SwcActuators.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID_C != SWCACTUATORS_VENDOR_ID)
    #error "SwcRte.c and SwcActuators.h have different vendor ids"
#endif

/* Check if SwcLighting.c source file and SwcActuators.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_C != SWCACTUATORS_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_C != SWCACTUATORS_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_C != SWCACTUATORS_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.c and SwcActuators.h are different"
#endif

#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
/* Check if SwcRte.c source file and SwcLighting.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID_C != SWCLIGHTING_VENDOR_ID)
    #error "SwcRte.c and SwcLighting.h have different vendor ids"
#endif

/* Check if SwcLighting.c source file and SwcLighting.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_C != SWCLIGHTING_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_C != SWCLIGHTING_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_C != SWCLIGHTING_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.c and SwcLighting.h are different"
#endif
#endif

#if (SWCRTE_MOTORCTRL_APP_ENABLED == SWCRTE_STD_ON)
/* Check if SwcRte.c source file and SwcMotorCtrl.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID_C != SWCMOTORCTRL_TYPES_VENDOR_ID)
    #error "SwcRte.c and SwcMotorCtrl.h have different vendor ids"
#endif

/* Check if SwcRte.c source file and SwcMotorCtrl.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_C != SWCMOTORCTRL_TYPES_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_C != SWCMOTORCTRL_TYPES_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_C != SWCMOTORCTRL_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.c and SwcMotorCtrl.h are different"
#endif
#endif

#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
/* Check if SwcRte.c source file and SwcVdr.h header file are of the same vendor */
#if (SWCRTE_VENDOR_ID_C != SWCVDR_VENDOR_ID)
    #error "SwcRte.c and SwcVdr.h have different vendor ids"
#endif

/* Check if SwcRte.c source file and SwcVdr.h header file are of the same Software version */
#if ((SWCRTE_SW_MAJOR_VERSION_C != SWCVDR_SW_MAJOR_VERSION) || \
     (SWCRTE_SW_MINOR_VERSION_C != SWCVDR_SW_MINOR_VERSION) || \
     (SWCRTE_SW_PATCH_VERSION_C != SWCVDR_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcRte.c and SwcVdr.h are different"
#endif
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
const SwcRte_GlobalConfigType * SwcRte_pGlobalCfgPtr = NULL_PTR;

/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)
#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
/*Global variable holding Lighting Actuator Data*/
volatile SwcRte_AppLightingActuatorValueType   SwcRte_aLightingActuatorData[SWCRTE_MAX_LIGHTING_INSTANCES];

/*Global variable holding Lighting Sensor Data*/
volatile SwcRte_AppLightingSensorValueType     SwcRte_aLightingSensorData[SWCRTE_MAX_LIGHTING_INSTANCES];

#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
/*Global variable holding Lighting COM Data*/
volatile SwcRte_AppLightingComDataType         SwcRte_aLightingComData[SWCRTE_MAX_LIGHTING_INSTANCES];

/*Global variable holding Lighting Info Data*/
volatile SwcRte_AppLightingComInfoType         SwcRte_aLightingInfoData[SWCRTE_MAX_LIGHTING_INSTANCES];
#endif /*(SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)*/
#endif /*(SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)*/

#if (SWCRTE_MOTORCTRL_APP_ENABLED == SWCRTE_STD_ON)
/*Global variable holding Lighting Actuator Data*/
volatile SwcRte_AppMotorCtrlActuatorValueType  SwcRte_aMotorCtrlActuatorData[SWCRTE_MAX_MOTORCTRL_INSTANCES];

/*Global variable holding Lighting Sensor Data*/
volatile SwcRte_AppMotorCtrlSensorValueType    SwcRte_aMotorCtrlSensorData[SWCRTE_MAX_MOTORCTRL_INSTANCES];

#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
/*Global variable holding Lighting COM Data*/
volatile SwcRte_AppMotorCtrlComDataType        SwcRte_aMotorCtrlComData[SWCRTE_MAX_MOTORCTRL_INSTANCES];

/*Global variable holding Lighting Info Data*/
volatile SwcRte_AppMotorCtrlComDataType        SwcRte_aMotorCtrlInfoData[SWCRTE_MAX_MOTORCTRL_INSTANCES];
#endif  /*(SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)*/
#endif /*(SWCRTE_MOTORCTRL_APP_ENABLED == SWCRTE_STD_ON)*/
#endif /*(SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)*/

/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/


/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/


/*=================================================================================================*/
/**
@brief      SwcSensors_Init - Initialization function for Rte
@details    This function shall be used to initialize global data used by SwcRte

@param[in]  ConfigPtr    Pointer to configuration data (this data is shared between all SWC components)

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*===================================================================================================*/
void SwcRte_Init(const SwcRte_GlobalConfigType * ConfigPtr)
{
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t InstanceIdx = 0;
#endif

    if(NULL_PTR != ConfigPtr) 
    {    
        SwcRte_pGlobalCfgPtr = ConfigPtr;
        
        SwcSensors_Init(ConfigPtr);        

#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
        SwcLighting_Init(ConfigPtr);
#endif

#if (SWCRTE_MOTORCTRL_APP_ENABLED == SWCRTE_STD_ON)
        SwcMotorCtrl_Init(ConfigPtr);
#endif

#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
        SwcVdr_Init(ConfigPtr);
#endif
    
        SwcActuators_Init(ConfigPtr);

#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)        
#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)    
        for (InstanceIdx = 0; InstanceIdx < SWCRTE_MAX_LIGHTING_INSTANCES; InstanceIdx++)
        {
            /*initialize all lighting data*/
        }
#endif

#if (SWCRTE_MOTORCTRL_APP_ENABLED == SWCRTE_STD_ON)        
        for (InstanceIdx = 0; InstanceIdx < SWCRTE_MAX_MOTORCTRL_INSTANCES; InstanceIdx++)
        {
            /*initialize all mc data*/
        }
#endif 
#endif/*SWCRTE_USE_RTE_BUFFERS*/      
    }
}

#if (SWCRTE_SINGLE_TASK_APPLICATION == SWCRTE_STD_ON)        
/*===================================================================================================*/
/**
@brief      SwcRte_MainRunnable - main processing function for Rte
@details    This function is called periodically by the OS or by the main() function.
            On each entry, the RTE runnable will process all other application runnables.

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*===================================================================================================*/
void SwcRte_MainRunnable()
{
    uint8_t InstanceIdx = 0;

    SwcSensors_MainRunnable();
        
#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)        
    for(InstanceIdx = 0; InstanceIdx < SWCRTE_MAX_LIGHTING_INSTANCES; InstanceIdx++)
    {
        SwcLighting_MainRunnable(InstanceIdx);
    }
#endif

#if (SWCRTE_VDR_APP_ENABLED  == SWCRTE_STD_ON)      
    SwcVdr_MainRunnable();
#endif

    SwcActuators_MainRunnable();
}
#endif/*SWCRTE_SINGLE_TASK_APPLICATION*/

#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)        
#if (SWCRTE_VDR_APP_ENABLED  == SWCRTE_STD_ON)   
    
/*======================================================================================================
                                            GOBAL FUNCTIONS FOR LIGHTING APP
=======================================================================================================*/

/*======================================================================================================*/
/**
@brief      SwcRte_ReadLightingComData – shall read any COM data provided by the VDR application. 

@param[in]  LightingInstance    Instance Index.
@param[out] Value               Data read from COM for that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void  SwcRte_ReadLightingComData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingComDataType * Value) 
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t ChIndex = 0;
     
    Value->u8LightingOutputChannels =  SwcRte_aLightingComData[LightingInstance].u8LightingOutputChannels;
     
    for(ChIndex = 0; ChIndex < SWCRTE_MAX_LIGHTING_CHANNELS; ChIndex++)
    {
        Value->aLightingOutputIntesity[ChIndex] = SwcRte_aLightingComData[LightingInstance].aLightingOutputIntesity[ChIndex];
    }
#endif 
}

/*==========================================================================================================*/
/**
@brief      SwcRte_WriteLightingComData - shall write a value required to update a state of the light
            source associated to the given Lighting application instance, which was requested by a COM message.

@param[in]  LightingInstance    Instance Index.
@param[out] Value               Data written to COM by that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void  SwcRte_WriteLightingComData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingComDataType * Value)
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)   
    uint8_t ChIndex = 0;
     
    SwcRte_aLightingComData[LightingInstance].u8LightingOutputChannels = Value->u8LightingOutputChannels;
     
    for(ChIndex = 0; ChIndex < SWCRTE_MAX_LIGHTING_CHANNELS; ChIndex++)
    {
        SwcRte_aLightingComData[LightingInstance].aLightingOutputIntesity[ChIndex] = Value->aLightingOutputIntesity[ChIndex];
    }
#else
    SwcLighting_WriteComData(LightingInstance,  Value);
#endif
}

/*==========================================================================================================*/
/**
@brief      SwcRte_ReadLightingComInfo - shall read any COM data provided by the VDR application. 

@param[in]  LightingInstance    Instance Index.
@param[out] Value               Data read from COM by that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_FetchLightingComInfo(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppMessageIdType  AppMessageId, SwcRte_AppLightingComInfoType * InputValue)
{
    uint8_t CharsIndex = 0;    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    for(CharsIndex = 0; CharsIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoInputChannel; CharsIndex++)
    {
        SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[ChIndex].Status = InputValue->aLightChannelValue[CharsIndex].Status;
        SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[ChIndex].FbkVoltage = InputValue->aLightChannelValue[CharsIndex].FbkVoltage;
        SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[ChIndex].ActiveCommand = InputValue->aLightChannelValue[CharsIndex].ActiveCommand;
    
        if(SCWRTE_TX_ON_EVENT == ((SwcRte_pGlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppMessageId]).eMessageReplyType))
        {
            SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[ChIndex].RequestTx = TRUE;
        }
        else
        {
            SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[ChIndex].RequestTx = FALSE;
        }
    }
#else    
    SwcLighting_FetchComInfo(LightingInstance,  InputValue);

    if(SCWRTE_TX_ON_EVENT == ((SwcRte_pGlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppMessageId]).eMessageReplyType))
    {
        InputValue->aLightingChanInfo[CharsIndex].RequestTx= TRUE;
    }
    else
    {
        InputValue->aLightingChanInfo[CharsIndex].RequestTx = FALSE;
    }    

#endif
}

/*==========================================================================================================*/
/**
@brief      SwcRte_WriteLightingComInfo  - shall write the data containing request to send relevant 
            status information regarding the light sources associated to current instance, 
            to any connected communication port.
            
@param[in]  LightingInstance    Instance Index.
@param[out] Value               Data written to COM by that instance.
            
@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_WriteLightingComInfo(SwcRte_AppInstanceIdType LightingInstance,  SwcRte_AppLightingComInfoType * Value)
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t CharsIndex = 0;

    SwcRte_aLightingInfoData[LightingInstance].u8NoOfInfoChars = Value->u8NoOfInfoChars;
    SwcRte_aLightingInfoData[LightingInstance].eComChannel     = Value->eComChannel;
     
    for(CharsIndex = 0; CharsIndex < Value.u8LightingOutputChannels; CharsIndex++)
    {
        SwcRte_aLightingInfoData[LightingInstance].pComInfoString[CharsIndex] = Value->pComInfoString[CharsIndex];
    }
#endif
}
#endif /*SWCRTE_VDR_APP_ENABLED*/

/*==========================================================================================================*/
/**
@brief      SwcRte_WriteLightingSensorData – shall write the sensor value for the given instance 
            of the Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] Value               Data written to Lighting application by Sensors for that instance.
            
@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_WriteLightingSensorData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingSensorValueType *Value) 
{   
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t CharsIndex = 0;    

    SwcRte_aLightingSensorData[LightingInstance].LightInputSensorData.u32LightingSensorValue =  Value->LightInputSensorData.u32LightingSensorValue;
    SwcRte_aLightingSensorData[LightingInstance].LightInputSensorData.bSensorValueUpdated = Value->LightInputSensorData.bSensorValueUpdated;
    
    for(CharsIndex = 0; CharsIndex < SwcRte_pGlobalCfgPtr[LightingInstance].u8NoInputChannel; CharsIndex++)
    {
        SwcRte_aLightingSensorData[LightingInstance].aLightChannelSensorData[SensorChannelId].u32LightingSensorValue =  Value->aLightChannelSensorData[SensorChannelId].u32LightingSensorValue;         
        SwcRte_aLightingSensorData[LightingInstance].aLightChannelSensorData[SensorChannelId].bSensorValueUpdated  =  Value->aLightChannelSensorData[SensorChannelId].bSensorValueUpdated;
    }  
#else    
   SwcLighting_WriteSensorData(LightingInstance, Value);
#endif   
   
}

/*==========================================================================================================*/
/**
@brief      SwcRte_ReadLightingOutputRequest – shall write the sensor value for the given instance 
            of the Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] Value               Data read from Sensors application by that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_ReadLightingSensorData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingSensorValueType *Value) 
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t CharsIndex = 0;    

    Value->LightInputSensorData.u32LightingSensorValue = SwcRte_aLightingSensorData[LightingInstance].LightInputSensorData.u32LightingSensorValue;
    Value->LightInputSensorData.bSensorValueUpdated = SwcRte_aLightingSensorData[LightingInstance].LightInputSensorData.bSensorValueUpdated;
    
    for(CharsIndex = 0; CharsIndex < SwcRte_pGlobalCfgPtr[LightingInstance].u8NoInputChannel; CharsIndex++)
    {
            Value->aLightChannelSensorData[SensorChannelId].u32LightingSensorValue = SwcRte_aLightingSensorData[LightingInstance].aLightChannelSensorData[SensorChannelId].u32LightingSensorValue;
            Value->aLightChannelSensorData[SensorChannelId].bSensorValueUpdated = SwcRte_aLightingSensorData[LightingInstance].aLightChannelSensorData[SensorChannelId].bSensorValueUpdated;
    }  

#else
   SwcLighting_ReadSensorData(LightingInstance, Value);
#endif
}

/*==========================================================================================================*/
/**
@brief      SwcRte_ReadLightingOutputRequest – shall read the sensor value for the given instance of 
            the Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] Value               Data read from Lighting application by that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_ReadLightingOutputRequest(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingActuatorValueType *Value) 
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t ChIndex = 0;

    for(ChIndex = 0; ChIndex < SwcRte_pGlobalCfgPtr[LightingInstance].u8NoOutputChannel; ChIndex++)
    { 
        Value->aLightingOutputIntesity[ChIndex] = SwcRte_aLightingActuatorData[LightingInstance].aLightingOutputIntesity[ChIndex];
        Value->aChannelState[ChIndex] = SwcRte_aLightingActuatorData[LightingInstance].aChannelState[ChIndex];
    }
#else
   SwcLighting_ReadOutputRequest(LightingInstance, Value);
#endif
}

/*==========================================================================================================*/
/**
@brief      SwcRte_WriteLightingOutputRequest – shall write the sensor value for the given instance of the
            Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] Value          Data written by Lighting for Actuators application for that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_WriteLightingOutputRequest(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingActuatorValueType *Value) 
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t ChIndex = 0;     
     
    for(ChIndex = 0; ChIndex < SwcRte_pGlobalCfgPtr[LightingInstance].u8NoOutputChannel; ChIndex++)
    { 
        SwcRte_aLightingActuatorData[LightingInstance].aLightingOutputIntesity[ChIndex] = Value->aLightingOutputIntesity[ChIndex];
        SwcRte_aLightingActuatorData[LightingInstance].aChannelState[ChIndex] = Value->aChannelState[ChIndex];
    }

#else
   SwcLighting_WriteOutputRequest(LightingInstance, Value);
#endif   
}

/*==========================================================================================================*/
/**
@brief      SwcRte_WriteLightingOutputRequest – shall write the sensor value for the given instance of the
            Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] Value          Data written by Lighting for Actuators application for that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
void SwcRte_SetLightingComInfoEvent(SwcRte_AppInstanceIdType LightingInstance, boolean_t RequestTx)
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t CharsIndex = 0;

    for(CharsIndex = 0; CharsIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoInputChannel; CharsIndex++)
    {          
        SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].RequestTx = RequestTx;        
    }
#else
	SwcLighting_SetComInfoEvent(LightingInstance, RequestTx);
#endif
}
#endif 
/*==========================================================================================================*/
/**
@brief      SwcRte_GetLightingComInfoEvent – return the boolean value of the request Tx value for the current 
            instance. 

@param[in]  LightingInstance    Instance Index.

@return     Returns TRUE if request TX is TRUE for at least one channel and FALSE otherwise.
@retval     TRUE or FALSE

@pre None
@post None
*/
/*==========================================================================================================*/
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
boolean_t SwcRte_GetLightingComInfoEvent(SwcRte_AppInstanceIdType LightingInstance) 
{    
   boolean_t retVal = FALSE;
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t CharsIndex = 0;
    
    for(CharsIndex = 1; CharsIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoInputChannel; CharsIndex++)
    {
        if (TRUE == SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].RequestTx)
        {
            retVal = TRUE;
            break;
        }    
    }
    
#else	
   retVal = SwcLighting_GetComInfoEvent(LightingInstance);
#endif
   return retVal;
}
#endif


#endif/*SWCRTE_LIGTHING_APP_ENABLED*/


#if (SWCRTE_MOTORCTRL_APP_ENABLED == SWCRTE_STD_ON)
/*===========================================================================================================
                                 GOBAL FUNCTIONS FOR MOTOR CONTROL APP
============================================================================================================*/

/*==========================================================================================================*/
/**
@brief      SwcRte_ReadMotorCtrlSensorData – shall read the sensors value associated to the Motor Control application

@details    The Data provided by Sensor Application shall contain two distinct types of information:
              -  Output update requests coming from HW buttons or potentiometers needed to change the output of the motor
              -  Feedback information coming from the motor. 

@param[in]  MotorCtrlInstance    Instance Index.
@param[out] Value                Data read by MotorControl from Sensors application for that instance.              
              
@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_ReadMotorCtrlSensorData(SwcRte_AppInstanceIdType MotorCtrlInstance, SwcRte_AppMotorCtrlSensorValueType * Value)
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t ChIndex = 0;
     
    Value->u8NoMotorCtrlFbkChannels   =  SwcRte_aMotorCtrlSensorData[LightingInstance].u8NoMotorCtrlFbkChannels;
    Value->u32MotorCtrlSensorValue    =  SwcRte_aMotorCtrlSensorData[LightingInstance].u32MotorCtrlSensorValue;
     
    for(ChIndex = 0; ChIndex < SWCRTE_MOTORCTRL_FBK_LINES; ChIndex++)
    {
        if (0 != ((Value->u8NoMotorCtrlFbkChannels) & (1 << ChIndex)))
        {        
            Value->aMotorCtrlOutputFeedback[ChIndex] = SwcRte_aMotorCtrlSensorData[LightingInstance].aMotorCtrlOutputFeedback[ChIndex];
        }
    }
#endif
}

/*==========================================================================================================*/
/**
@brief      SwcRte_WriteMotorCtrlSensorData – shall write the sensor value for the given instance of the 
            Motor Control application.


@param[in]  MotorCtrlInstance    Instance Index.
@param[out] Value                Data written by Sensors for MotorControl application for that instance.    

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_WriteMotorCtrlSensorData(SwcRte_AppInstanceIdType MotorCtrlInstance, SwcRte_AppMotorCtrlSensorValueType * Value) 
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t CharsIndex = 0;
     
    SwcRte_aMotorCtrlSensorData[LightingInstance].u8NoMotorCtrlFbkChannels = Value->u8NoMotorCtrlFbkChannels;
    SwcRte_aMotorCtrlSensorData[LightingInstance].u32MotorCtrlSensorValue   = Value->u32MotorCtrlSensorValue;
         
    for(CharsIndex = 0; CharsIndex < SWCRTE_MOTORCTRL_FBK_LINES; CharsIndex++)
    {
        if (0 != ((Value->u8NoMotorCtrlFbkChannels) & (1 << ChIndex)))
        {
            SwcRte_aMotorCtrlSensorData[LightingInstance].aMotorCtrlOutputFeedback[ChIndex] = Value->aMotorCtrlOutputFeedback[ChIndex];
        }
    }
#endif
}

/*==========================================================================================================*/
/**
@brief      SwcRte_ReadMotorCtrlOutputRequest – This function shall read any output change request coming from the 
            Motor-Control Application, process these request and store the values in the internal data 
            so it will be sent to IoDal via SwcActuator_WriteOutputs().

@param[in]  MotorCtrlInstance    Instance Index.
@param[out] Value                Data read by Actuators from MotorControl application for that instance.    

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_ReadMotorCtrlOutputRequest(SwcRte_AppInstanceIdType MotorCtrlInstance, SwcRte_AppMotorCtrlActuatorValueType  * Value)
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)
    Value->u32MotorCtrlOutputSpeed =  SwcRte_aMotorCtrlActuatorData[MotorCtrlInstance].u32MotorCtrlOutputSpeed;
    Value->u32MotorCtrlOutputSpeed =  SwcRte_aMotorCtrlActuatorData[MotorCtrlInstance].eMotorCtrlOutputDirection;

#else    
    SwcMotorCtrl_ReadOutputRequest(MotorCtrlInstance, Value);
#endif
}


/*==========================================================================================================*/
/**
@brief      SwcRte_WriteMotorCtrlOutputRequest - shall write the data containing request to change the output values for the 
                                                 motor associated to current application  instance.

@details    Any output request should contain the following information:
                -    “Direction for rotation” (CW/CCW) or “Stop”      
                -    New Motor Speed (percent from maximum value) if command is not “Stop”

@param[in]  MotorCtrlInstance    Instance Index.
@param[out] Value                Data written by Actuators from MotorControl application for that instance.    
                
@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_WriteMotorCtrlOutputRequest(SwcRte_AppInstanceIdType MotorCtrlInstance,  SwcRte_AppMotorCtrlActuatorValueType * Value) 
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)      
    SwcRte_aMotorCtrlActuatorData[MotorCtrlInstance].u32MotorCtrlOutputSpeed   = Value->u32MotorCtrlOutputSpeed;
    SwcRte_aMotorCtrlActuatorData[MotorCtrlInstance].eMotorCtrlOutputDirection = Value->u32MotorCtrlOutputSpeed;
#endif    
}

#if (SWCRTE_VDR_APP_ENABLED  ==SWCRTE_STD_ON)
/*==========================================================================================================*/
/**
@brief      SwcRte_ReadMotorCtrlComData  –  shall read any COM data provided by the VDR application required by Motor Control
                                            to update the output parameter of the motor associated to the current instance. 

@param[in]  MotorCtrlInstance    Instance Index.
@param[out] OutputValue          Data read by COM for that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_ReadMotorCtrlComData(SwcRte_AppInstanceIdType MotorCtrlInstance, SwcRte_AppMotorCtrlComDataType * OutputValue) 
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    OutputValue->u32MotorCtrlOutputSpeed =  SwcRte_aMotorCtrlComData[MotorCtrlInstance].u32MotorCtrlOutputSpeed;
    OutputValue->u32MotorCtrlOutputSpeed =  SwcRte_aMotorCtrlComData[MotorCtrlInstance].eMotorCtrlOutputDirection;
#endif    
}

/*==========================================================================================================*/
/**
@brief      SwcRte_WriteMotorCtrlComData shall write a value required to update a state of the light source associated to the given
             Motor-control application instance, which was requested by a COM message.
             
@param[in]  MotorCtrlInstance    Instance Index.
@param[out] Value                Data written to COM by that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_WriteMotorCtrlComData(SwcRte_AppInstanceIdType MotorCtrlInstance, SwcRte_AppMotorCtrlComDataType * Value)
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    SwcRte_aMotorCtrlComData[MotorCtrlInstance].u32MotorCtrlOutputSpeed   = Value->u32MotorCtrlOutputSpeed;
    SwcRte_aMotorCtrlComData[MotorCtrlInstance].eMotorCtrlOutputDirection = Value->u32MotorCtrlOutputSpeed;
#endif    
}

/*==========================================================================================================*/
/**
@brief      SwcRte_ReadMotorCtrlComInfo - shall write the data containing request to change the output values 
            for the light sourcecs (LEDs) associated to current application instance. 
            
@param[in]  MotorCtrlInstance    Instance Index.
@param[out] Value                Data read by COM for that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_ReadMotorCtrlComInfo(SwcRte_AppInstanceIdType MotorCtrlInstance,  SwcRte_AppMotorCtrlInfoType * Value)
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t CharsIndex = 0;
    
    Value->u8NoOfInfoChars =  SwcRte_aMotorCtrlInfoData[LightingInstance].u8NoOfInfoChars;
    Value->eComChannel     =  SwcRte_aMotorCtrlInfoData[LightingInstance].eComChannel;     
    
    for(CharsIndex = 0; CharsIndex < Value->u8NoOfInfoChars; CharsIndex++)
    {
        Value->pComInfoString[CharsIndex] = SwcRte_aMotorCtrlInfoData[LightingInstance].pComInfoString[CharsIndex];
    }
#endif
}


/*==========================================================================================================*/
/**
@brief      SwcRte_WriteMotorCtrlSensorData  - shall write the data containing request to send relevant 
            status information regarding the motor associated to current instance,
            to any connected communication port.

@param[in]  MotorCtrlInstance    Instance Index.
@param[out] Value                Data written by COM for that instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==========================================================================================================*/
void SwcRte_WriteMotorCtrlComInfo(SwcRte_AppInstanceIdType MotorCtrlInstance,  SwcRte_AppMotorCtrlInfoType * Value) 
{    
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_ON)  
    uint8_t CharsIndex = 0;

    SwcRte_aLightingInfoData[LightingInstance].u8NoOfInfoChars = Value->u8NoOfInfoChars;
    SwcRte_aLightingInfoData[LightingInstance].eComChannel     = Value->eComChannel;

    for(CharsIndex = 0; CharsIndex < Value.u8LightingOutputChannels; CharsIndex++)
    {
        SwcRte_aLightingInfoData[LightingInstance].pComInfoString[CharsIndex] = Value->pComInfoString[CharsIndex];
    }
#endif
}
#endif /*SWCRTE_VDR_APP_ENABLED*/
#endif /*SWCRTE_MOTORCTRL_APP_ENABLED*/

#if (SWCRTE_VDR_APP_ENABLED  ==SWCRTE_STD_ON)    
/*==============================================================================================================
                                 GOBAL FUNCTIONS FOR BSW INTERFACE
===============================================================================================================*/

/*=============================================================================================================*/
/**
@brief      SwcRte_ReadComData - shall read the value associated to a Actuator channel which determined by the ComDal component. 

@details

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*=============================================================================================================*/
SwcRte_AppReturnType SwcRte_ReadComData(SwcRte_AppMessageIdType AppRxMessageId, SwcRte_DataMessageType * DataMessagePtr)
{    
    volatile ComDal_ChannelType ComChannel;    
    volatile uint8_t DataLen = 0U;
    volatile SwcRte_AppReturnType ReturnVal = SWCRTE_E_NOT_OK;
    ComChannel = (SwcRte_pGlobalCfgPtr[SWCVDR_INSTANCE_ID].pRxMessageList[AppRxMessageId]).u8BswComChannelId;
    DataLen = (SwcRte_pGlobalCfgPtr[SWCVDR_INSTANCE_ID].pRxMessageList[AppRxMessageId]).u8VdrRxMessageDataLen;    
     
    /*save received from data from COMDAL (via RTE) to application buffers*/ 
    if(COMDAL_NO_ERROR == ComDal_ReadData(ComChannel, DataMessagePtr, DataLen))
    {
        ReturnVal = SWCRTE_E_OK;
    }

    return ReturnVal;
}

/*==============================================================================================================*/
/**
@brief      SwcRte_WriteComData - shall write the value associated to a Actuator channel which determined by the ComDal component. 

@details

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==============================================================================================================*/
void SwcRte_WriteComData(SwcRte_AppMessageIdType  AppTxMessageId)
{
    
    volatile ComDal_ChannelType ComChannel;
    SwcRte_DataMessageType * DataMessagePtr;
    volatile uint8_t DataLen = 0U;
    ComChannel = (SwcRte_pGlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).u8BswComChannelId;    
    DataLen = (SwcRte_pGlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).u8VdrTxMessageDataLen;    
    DataMessagePtr = (SwcRte_pGlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).pDataMessagePtr;
    
    /*save received from data from COMDAL (via RTE) to application buffers*/ 
    ComDal_WriteData(ComChannel, DataMessagePtr, DataLen);
    
    /*clear Application data buffer*/
    if(SCWRTE_TX_SEND_MSG != (SwcRte_pGlobalCfgPtr[SWCVDR_INSTANCE_ID].pTxMessageList[AppTxMessageId]).eMessageReplyType)                                  
    {
        SwcVdr_ClearDataMessageBuffer(AppTxMessageId);
    }	
}

#endif


/*==============================================================================================================*/
/**
@brief      SwcRte_ReadLightingComInfo - shall read the value associated to a Sensor channel which determined by the IoDal component. 

@details

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==============================================================================================================*/
void SwcRte_ReadInputs(SwcRte_AppInstanceIdType AppInstance, SwcRte_AppChannelIdType SensorChannel, SwcRte_AppInputValueType * InputValue) 
{        
    volatile SwcRte_AppChannelIdType InputSensor; 
    volatile Std_ReturnType Ret_Val = E_NOT_OK;
    IoDal_BswValueType IoDalInputValue = 0;
    InputSensor = (SwcRte_pGlobalCfgPtr[AppInstance].pInstanceInputSensor[SensorChannel]).u8InputChannel;
    
    Ret_Val = IoDal_ReadInputs(InputSensor, &IoDalInputValue);    
    
    if (E_OK == Ret_Val)
    {    
        InputValue->Status = SWCRTE_MEAS_OK;    
        InputValue->Value =  (uint16)IoDalInputValue;
    }
    else
    {
        InputValue->Status = SWCRTE_MEAS_NOT_OK;        
        InputValue->Value = 0U;
    }
}


/*==============================================================================================================*/
/**
@brief      SwcRte_WriteOutputs - shall write the value associated to a Actuator channel which is determined by the IoDal component. 


@details

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*==============================================================================================================*/
void SwcRte_WriteOutputs(SwcRte_AppInstanceIdType AppInstance, SwcRte_AppChannelIdType ActuatorChannel, SwcRte_OutputValueType OutputValue) 
{    
    volatile SwcRte_AppChannelIdType OutputChannel;
    
    /*get output channel from the actuator channel in configuration */ 
    OutputChannel = SwcRte_pGlobalCfgPtr[AppInstance].pInstanceActuator[ActuatorChannel].u8OutputChannel;
    IoDal_WriteOutputs(OutputChannel, OutputValue);
}

#if (SWCRTE_ENABLE_POWER_MODE == SWCRTE_STD_ON)
/*==============================================================================================================*/
/**
@brief      SwcRte_SetPowerMode - shall request a power mode change in SYSDAL 


@return     void

@pre None
@post None
*/
/*==============================================================================================================*/
void SwcRte_SetPowerMode(SwcRte_PowerModeType PowerModeId)
{
    SysDal_WriteModeRequest(PowerModeId);    
}

/*==============================================================================================================*/
/**
@brief      SwcRte_ExecuteSwReset - shall request system reset in SYSDAL

@return     void

@pre None
@post None
*/
/*==============================================================================================================*/
void SwcRte_ExecuteSwReset()
{
    SysDal_ExecuteSwReset();    
}

/*==============================================================================================================*/
/**
@brief      SwcRte_SetPowerMode - shall get the current run-mode from SYSDAL 


@return     void

@pre None
@post None
*/
/*==============================================================================================================*/
SwcRte_PowerModeType SwcRte_GetCurrentPowerMode()
{
    return (SysDal_GetCurrentPowerMode());    
}
#endif

/*================================================================================================*/
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
/** @} */
