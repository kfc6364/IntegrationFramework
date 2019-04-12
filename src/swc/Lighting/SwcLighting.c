/**
*    @file        SwcLighting.c
*    @version     0.8.1
*
*    @brief       Integration Framework - Lighting SW component.
*
*    @details     Implementation from the lighting application.
*
*   (c) Copyright 2006-2016 Freescale Semiconductor, Inc. 
*       Copyright 2017-2018 NXP
*   All Rights Reserved.
*   This file contains sample code only. It is not part of the production code deliverables.
*
*   @addtogroup SWCLIGHTING
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
#include "SwcLighting.h"
#include "SwcRte.h"


/*==================================================================================================
                                       SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define SWCLIGHTING_VENDOR_ID_C                          43

#define SWCLIGHTING_SW_MAJOR_VERSION_C                   0
#define SWCLIGHTING_SW_MINOR_VERSION_C                   8
#define SWCLIGHTING_SW_PATCH_VERSION_C                   1
/*==================================================================================================
*                                     FILE VERSION CHECKS
===================================================================================================*/
/* Check if SwcLighting.c source file and SwcLighting.h header file are of the same vendor */
#if (SWCLIGHTING_VENDOR_ID_C != SWCLIGHTING_VENDOR_ID)
    #error "SwcLighting.c and SwcLighting.h have different vendor ids"
#endif

/* Check if SwcLighting.c source file and SwcLighting.h header file are of the same Software version */
#if ((SWCLIGHTING_SW_MAJOR_VERSION_C != SWCLIGHTING_SW_MAJOR_VERSION) || \
     (SWCLIGHTING_SW_MINOR_VERSION_C != SWCLIGHTING_SW_MINOR_VERSION) || \
     (SWCLIGHTING_SW_PATCH_VERSION_C != SWCLIGHTING_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcLighting.c and SwcLighting.h are different"
#endif

/* Check if SwcLighting.c source file and  SwcRte.h header file are of the same vendor */
#if (SWCLIGHTING_VENDOR_ID_C != SWCRTE_VENDOR_ID)
    #error "SwcLighting.c and SwcRte.h have different vendor ids"
#endif

/* Check if SwcLighting.c source file and SwcRte.h header file are of the same Software version */
#if ((SWCLIGHTING_SW_MAJOR_VERSION_C != SWCRTE_SW_MAJOR_VERSION) || \
     (SWCLIGHTING_SW_MINOR_VERSION_C != SWCRTE_SW_MINOR_VERSION) || \
     (SWCLIGHTING_SW_PATCH_VERSION_C != SWCRTE_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcLighting.c and SwcRte.h are different"
#endif


/* Check if SwcLighting.c source file and SwcRte_Cfg.h header file are of the same vendor */
#if (SWCLIGHTING_VENDOR_ID_C != SWCRTE_CFG_VENDOR_ID)
    #error "SwcLighting.c and SwcRte_Cfg.h have different vendor ids"
#endif

/* Check if SwcLighting.c source file and SwcRte_Cfg.h header file are of the same Software version */
#if ((SWCLIGHTING_SW_MAJOR_VERSION_C != SWCRTE_CFG_SW_MAJOR_VERSION) || \
     (SWCLIGHTING_SW_MINOR_VERSION_C != SWCRTE_CFG_SW_MINOR_VERSION) || \
     (SWCLIGHTING_SW_PATCH_VERSION_C != SWCRTE_CFG_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcLighting.c and SwcRte_Cfg.h are different"
#endif


/* Check if SwcLighting.c source file and SwcRte_Types.h header file are of the same vendor */
#if (SWCLIGHTING_VENDOR_ID_C != SWCRTE_TYPES_VENDOR_ID)
    #error "SwcLighting.c and SwcRte_Types.h have different vendor ids"
#endif

/* Check if SwcLighting.c source file and SwcRte_Types.h header file are of the same Software version */
#if ((SWCLIGHTING_SW_MAJOR_VERSION_C != SWCRTE_TYPES_SW_MAJOR_VERSION) || \
     (SWCLIGHTING_SW_MINOR_VERSION_C != SWCRTE_TYPES_SW_MINOR_VERSION) || \
     (SWCLIGHTING_SW_PATCH_VERSION_C != SWCRTE_TYPES_SW_PATCH_VERSION) \
    )
    #error "Software Version Numbers of SwcLighting.c and SwcRte_Types.h are different"
#endif



/*==================================================================================================
                                        LOCAL MACROS
==================================================================================================*/
#define SWCLIGHTING_DIMMING_FACTOR           (4096U)
#define SWCLIGHTING_FIRST_BUTTON_PRESS       (1U)
#define SWCLIGHTING_SECOND_BUTTON_PRESS      (2U)
#define SWCLIGHTING_MAX_DIMMING_INCREMENT    (8U)
#define SWCLIGHTING_PWM_MAX_DUTY_CYCLE       (0x8000U) 
#define SWCLIGHTING_AVG_SUM_COUNT             4U
#define SWCLIGHTING_AVG_DENOMINATOR_SHIFT     2U
#define SWCLIGHTING_MAX_TRANSIENT_ERR_COUNT   2U
#define SWCLIGHTING_MAX_FBK_ERR_VALUE         100U
#define SWCLIGHTING_MIN_FBK_DUTY_VALUE       2000U
/*==================================================================================================
                                      FILE VERSION CHECKS
==================================================================================================*/


/*==================================================================================================
                          LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/


/*==================================================================================================
                                       LOCAL CONSTANTS
==================================================================================================*/


/*==================================================================================================
                                       LOCAL VARIABLES
==================================================================================================*/

#if (SWCRTE_LIGTHING_APP_ENABLED == SWCRTE_STD_ON)
/*==================================================================================================
                                       GLOBAL CONSTANTS
==================================================================================================*/
/**
* @brief          Local variable holding the pointer to RTE configuration data.                  
*/
static const SwcRte_GlobalConfigType * SwcLighting_ConfigPtr;
/*==================================================================================================
                                       GLOBAL VARIABLES
==================================================================================================*/
#if (SWCRTE_USE_RTE_BUFFERS == SWCRTE_STD_OFF)

/**
* @brief          Global variable holding Lighting Actuator Data   
*/
volatile SwcRte_AppLightingActuatorValueType    SwcRte_aLightingActuatorData[SWCRTE_MAX_LIGHTING_INSTANCES];


/**
* @brief          Global variable holding Lighting Sensor Data  
*/
volatile SwcRte_AppLightingSensorValueType      SwcRte_aLightingSensorData[SWCRTE_MAX_LIGHTING_INSTANCES];


#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
/**
* @brief          Global variable holding Lighting Data to be sent to VDR  
*/
volatile SwcRte_AppLightingComInfoType          SwcRte_aLightingInfoData[SWCRTE_MAX_LIGHTING_INSTANCES];

/**
* @brief          Global variable holding Lighting Data provided by VDR  
*/
volatile SwcRte_AppLightingComDataType          SwcRte_aLightingComData[SWCRTE_MAX_LIGHTING_INSTANCES];
#endif
#endif

/**
* @brief          Local variable holding current state for the given instance ID
*/
volatile static SwcRte_InstanceStateType SwcLightning_InstanceState[SWCRTE_MAX_LIGHTING_INSTANCES];

/**
* @brief          Local variable holding previos state for a Logical Type input (On-off) on the current insance
*/
volatile static SwcRte_InputStateType    SwcLighting_PreviosButtonState[SWCRTE_MAX_LIGHTING_INSTANCES];

/**
* @brief          Local variable holding current state for a Logical Type input (On-off) on the current insance
*/
volatile static SwcRte_InputStateType    SwcLighting_ButtonState[SWCRTE_MAX_LIGHTING_INSTANCES];

/**
* @brief          Local variable holding output value (either logical or analog) on the current insance
*/
volatile static uint16_t                 SwcLighting_OutputValue[SWCRTE_MAX_LIGHTING_INSTANCES];

/**
* @brief          Local variable holding Sum of Feedback vlaues for each Channel of each instance.
                  This value is used to calculate average feedback value for a given channel.
*/
volatile static uint32_t                 SwcLighting_SumFeedbackValue[SWCRTE_MAX_LIGHTING_INSTANCES][SWCRTE_MAX_LIGHTING_CHANNELS];

/**
* @brief          Local variable holding current agerage index counter value for a given instance and channel. 
                  The Avarage is calculate as Sum = (FV1 + FV2 + ... FVn) / n; 
				  Where FVi is the current Feedback value read for current channel.
				  Note: in our case n = 4;                  
*/
volatile static uint8_t                  SwcLighting_AvgValueCounter[SWCRTE_MAX_LIGHTING_INSTANCES][SWCRTE_MAX_LIGHTING_CHANNELS];

/**
* @brief          Local variable holding current agerage feedback value for a given instance and channel.                  
*/
volatile static uint16_t                 SwcLighting_AvgFeedbackValue[SWCRTE_MAX_LIGHTING_INSTANCES][SWCRTE_MAX_LIGHTING_CHANNELS];

/**
* @brief          Local variable holding the counter for the consecutive transient error. If a given number of consecutive transient errors           
                  is detected, then a fault error is reported.                  
*/
volatile static uint8_t                  SwcLighting_CountTransientError[SWCRTE_MAX_LIGHTING_INSTANCES][SWCRTE_MAX_LIGHTING_CHANNELS];

/**
* @brief          Local variable holding the debounce coutner for logical buttons (on-off) type.              
*/
volatile static uint8_t                  SwcLighting_CountButtonPressed[SWCRTE_MAX_LIGHTING_INSTANCES];
/*==================================================================================================
                                   LOCAL FUNCTION PROTOTYPES
==================================================================================================*/
static void SwcLighting_CalculateOuputValue(SwcRte_AppInstanceIdType RteAppInstance);
static void SwcLighting_ProcessFeedback(SwcRte_AppInstanceIdType RteAppInstance);
/*==================================================================================================
                                       LOCAL FUNCTIONS
==================================================================================================*/

/*================================================================================================*/
/**
@brief      SwcLighting_CalculateOuputValue - calculate the next output value for all channels
            of a given instance
@details    Depending on the channels type this function shall calculate the next output value for 
            all channels of the given instance.
                        
@param[in]  RteAppInstance    Instance Index.

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
static void SwcLighting_CalculateOuputValue(SwcRte_AppInstanceIdType RteAppInstance)
{
    uint8_t ChIndex = 0;
    uint32_t PotValue   = 0;
    
    /*get sensor type*/ 
    SwcRte_AppInputSensorType SensorType = SwcLighting_ConfigPtr[RteAppInstance].pInstanceInputSensor[0].eInputType;
        
    switch(SensorType)
    {
        case SWCRTE_DIGITAL_SENS:  /*if sensor is digital buttons*/
        {
            /*if button was pressed and than released */
            SwcLighting_ButtonState[RteAppInstance] = (SwcRte_InputStateType)SwcRte_aLightingSensorData[RteAppInstance].LightInputSensorData.u32LightingSensorValue;

            if(SWCRTE_BUTTON_ON == SwcLighting_ButtonState[RteAppInstance])
            {
                if(SWCRTE_BUTTON_ON == SwcLighting_PreviosButtonState[RteAppInstance])
                {    
                    SwcLighting_CountButtonPressed[RteAppInstance]++;
                    SwcLighting_PreviosButtonState[RteAppInstance] = SWCRTE_BUTTON_OFF;
                }
            }
            else
            {
                if(SWCRTE_BUTTON_OFF == SwcLighting_PreviosButtonState[RteAppInstance])
                {                        
                    SwcLighting_PreviosButtonState[RteAppInstance] = SWCRTE_BUTTON_ON;                                
                }                    
            }

            if(SwcLighting_ConfigPtr[RteAppInstance].eOutputType == SWCRTE_PWM_OUT)
            {
                if(SwcLighting_CountButtonPressed[RteAppInstance] > SWCLIGHTING_MAX_DIMMING_INCREMENT)
                {
                    SwcLighting_CountButtonPressed[RteAppInstance] = 0;
                    SwcLighting_OutputValue[RteAppInstance] = SWCRTE_BUTTON_OFF;
                }
                else
                {
                    SwcLighting_OutputValue[RteAppInstance] = (SwcLighting_CountButtonPressed[RteAppInstance] * SWCLIGHTING_DIMMING_FACTOR);
                }                
            }
            else
            {
                if(SWCLIGHTING_FIRST_BUTTON_PRESS == SwcLighting_CountButtonPressed[RteAppInstance])
                {    
                    SwcLighting_OutputValue[RteAppInstance] = SWCRTE_BUTTON_ON;
                }
                
                if(SWCLIGHTING_SECOND_BUTTON_PRESS == SwcLighting_CountButtonPressed[RteAppInstance])
                {    
                    SwcLighting_OutputValue[RteAppInstance] = SWCRTE_BUTTON_OFF;
                    SwcLighting_CountButtonPressed[RteAppInstance] = 0U;
                }    
            }            
        } break;
        
        case SWCRTE_ANALOG_POT_SENS: /*if sensor is analog potentiometer*/
        {
            /*calculate dimming based of sensor_value*/
            PotValue = SwcRte_aLightingSensorData[RteAppInstance].LightInputSensorData.u32LightingSensorValue;

            SwcLighting_OutputValue[RteAppInstance] = ((PotValue * SWCLIGHTING_PWM_MAX_DUTY_CYCLE) >> SWCRTE_ADC_RESOLUTION);
       } break;
        

        default:
        break;
    }
     

    /*TODO:  ALL THE output requests need to be marked as atomic operations*/    
    /*The output are handled based on the previos feedback result*/
    /*If any error was detected/reported on an output channle than that output channel shall be removed from output update table*/
    for(ChIndex = 0U; ChIndex < SwcLighting_ConfigPtr[RteAppInstance].u8NoOutputChannel; ChIndex++)
    {        
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)      
        if (SWCRTE_COM_DATA_INPUT == SensorType)
        {
            SwcRte_aLightingActuatorData[RteAppInstance].aLightingOutputIntesity[ChIndex] = SwcRte_aLightingComData[RteAppInstance].aLightChannelValue[ChIndex];
        } 
        else
        {
#endif    
            SwcRte_aLightingActuatorData[RteAppInstance].aLightingOutputIntesity[ChIndex] = SwcLighting_OutputValue[RteAppInstance];
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)            
        }
#endif            
        	
	    if((0U == SwcRte_aLightingActuatorData[RteAppInstance].aLightingOutputIntesity[ChIndex]) &&  
		   (SWCRTE_CHANNEL_ACTIVE == SwcRte_aLightingActuatorData[RteAppInstance].aChannelState[ChIndex]))
        {             
            SwcRte_aLightingActuatorData[RteAppInstance].aChannelState[ChIndex] = SWCRTE_CHANNEL_STOPPED;
        }
		
		if((0U != SwcRte_aLightingActuatorData[RteAppInstance].aLightingOutputIntesity[ChIndex]) &&  
		   (SWCRTE_CHANNEL_ACTIVE >= SwcRte_aLightingActuatorData[RteAppInstance].aChannelState[ChIndex]))
        {             
            SwcRte_aLightingActuatorData[RteAppInstance].aChannelState[ChIndex] = SWCRTE_CHANNEL_ACTIVE;
        }
    }    
}

/*================================================================================================*/
/**
@brief      SwcLighting_ProcessFeedback - shall process feedback information for all channels 
            of a given instance that have analog feedback


@param[in]  RteAppInstance    Instance Index.

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
static void SwcLighting_ProcessFeedback(SwcRte_AppInstanceIdType RteAppInstance)
{
    uint16_t ChFbkValue = 0;
    uint8_t ChIndex;
    
    /*get current fdbk value (amperes) for each feedback channel*/

    for(ChIndex=0U; ChIndex < SwcLighting_ConfigPtr[RteAppInstance].u8NoOutputChannel; ChIndex++)
    {          
        /*check if current channel is a Feedback channel and if analog value was updated*/    
        if((SWCRTE_ANALOG_FDBK_SENS == SwcLighting_ConfigPtr[RteAppInstance].pInstanceInputSensor[ChIndex + 1U].eInputType) &&
           (SWCRTE_TRUE == SwcRte_aLightingSensorData[RteAppInstance].aLightChannelSensorData[ChIndex].bSensorValueUpdated))
        {
            ChFbkValue = SwcRte_aLightingSensorData[RteAppInstance].aLightChannelSensorData[ChIndex].u32LightingSensorValue;

            if(ChFbkValue > SWCLIGHTING_MAXIMUM_ANALOG_FDBK_VALUE) /*if value over maximum limit and channel is used and operational*/
            {
                /*mark output channel as having: short circuit to gnd*/    
                SwcRte_aLightingActuatorData[RteAppInstance].aChannelState[ChIndex] = SWCRTE_CHANNEL_SHORT2GND;

                /*set output to OFF*/
                SwcRte_aLightingActuatorData[RteAppInstance].aLightingOutputIntesity[ChIndex] = SWCRTE_BUTTON_OFF;    
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)
                SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].RequestTx = SWCRTE_TRUE;
#endif
                SwcLighting_AvgFeedbackValue[RteAppInstance][ChIndex] = 0U;
            }
            else if(ChFbkValue < SWCLIGHTING_MINIMUM_ANALOG_FDBK_VALUE) /*if value is 0 and channel is used and operational*/
            {
                /*check if channel has an active command*/
                if(SWCLIGHTING_MIN_FBK_DUTY_VALUE < SwcLighting_OutputValue[RteAppInstance])
                {
                    /*mark output channel as having: open load*/
                    SwcRte_aLightingActuatorData[RteAppInstance].aChannelState[ChIndex] = SWCRTE_CHANNEL_OPEN_LOAD;

                    /*set output to OFF*/
                    SwcRte_aLightingActuatorData[RteAppInstance].aLightingOutputIntesity[ChIndex] = SWCRTE_BUTTON_OFF;         
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)                    
                    SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].RequestTx = SWCRTE_TRUE;
#endif				
                }
                
                SwcLighting_AvgFeedbackValue[RteAppInstance][ChIndex] = 0U;
            }
            else
            {
                /*calculate avarage feedback for each channel*/
                SwcLighting_SumFeedbackValue[RteAppInstance][ChIndex] = SwcLighting_SumFeedbackValue[RteAppInstance][ChIndex] + ChFbkValue;
                
                SwcLighting_AvgValueCounter[RteAppInstance][ChIndex]++;                
                
                if(SwcLighting_AvgValueCounter[RteAppInstance][ChIndex] >= SWCLIGHTING_AVG_SUM_COUNT)
                {
                    SwcLighting_AvgFeedbackValue[RteAppInstance][ChIndex] = (SwcLighting_SumFeedbackValue[RteAppInstance][ChIndex] >> SWCLIGHTING_AVG_DENOMINATOR_SHIFT);
                    SwcLighting_AvgValueCounter[RteAppInstance][ChIndex] = 0U;
                    
                    /*update sum value with average feedback for each channel*/
                    SwcLighting_SumFeedbackValue[RteAppInstance][ChIndex] = 0U;                    

                    if (((ChFbkValue > (SwcLighting_AvgFeedbackValue[RteAppInstance][ChIndex] + SWCLIGHTING_MAX_FBK_ERR_VALUE))) || 
                        (ChFbkValue < (SwcLighting_AvgFeedbackValue[RteAppInstance][ChIndex] - SWCLIGHTING_MAX_FBK_ERR_VALUE)))
                    {
                        SwcLighting_CountTransientError[RteAppInstance][ChIndex]++;
                    }
                    else
                    {
                        SwcLighting_CountTransientError[RteAppInstance][ChIndex] = 0;
                    }
                }
                
                if(SwcLighting_CountTransientError[RteAppInstance][ChIndex] > SWCLIGHTING_MAX_TRANSIENT_ERR_COUNT)
                {
                    /*reset transient error counter*/
                    SwcLighting_CountTransientError[RteAppInstance][ChIndex] = 0;
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)                    
                    SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].RequestTx = SWCRTE_TRUE;
#endif
                }
            }
        }

#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)            
        /*Set Com info regarding current status to be sent to user via VDR*/
        if (SWCRTE_TRUE == SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].RequestTx)
        {    
            SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].Status = SwcRte_aLightingActuatorData[RteAppInstance].aChannelState[ChIndex];        
            SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].FbkVoltage = SwcLighting_AvgFeedbackValue[RteAppInstance][ChIndex];    
            SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].ActiveCommand = SwcRte_aLightingActuatorData[RteAppInstance].aLightingOutputIntesity[ChIndex];                
            SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[ChIndex].RequestTx = SWCRTE_FALSE;
        }
#endif    
    } 
}

/*==================================================================================================
                                       GLOBAL FUNCTIONS
==================================================================================================*/
/*================================================================================================*/
/**
@brief      SwcLighting_Init - Initialization function for Lighting
@details    This function shall be used to initialize global data used by SwcSensor

@param[in]  ConfigPtr    Pointer to configuration data (this data is shared between all SWC components)

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_Init(const SwcRte_GlobalConfigType * ConfigPtr)
{
    SwcRte_AppInstanceIdType InstanceId;
    SwcRte_AppChannelIdType  CharsIndex;
    
    SwcLighting_ConfigPtr = ConfigPtr;

    for(InstanceId = 0; InstanceId < SWCRTE_MAX_LIGHTING_INSTANCES; InstanceId++)
    {
        SwcLightning_InstanceState[InstanceId] = SWCRTE_READINPUTS;
        SwcLighting_PreviosButtonState[InstanceId] = SWCRTE_BUTTON_OFF;
        SwcLighting_ButtonState[InstanceId] = SWCRTE_BUTTON_OFF;
        SwcLighting_OutputValue[InstanceId]  = SWCRTE_BUTTON_OFF;
        SwcLighting_CountButtonPressed[InstanceId]  = 0;
        SwcRte_aLightingSensorData[InstanceId].LightInputSensorData.bSensorValueUpdated =  SWCRTE_FALSE;
        SwcRte_aLightingSensorData[InstanceId].LightInputSensorData.u32LightingSensorValue =  0U;
        
        for(CharsIndex = 0; CharsIndex < SWCRTE_MAX_LIGHTING_CHANNELS; CharsIndex++)
        {
            /*initialize channel state*/
            SwcRte_aLightingActuatorData[InstanceId].aChannelState[CharsIndex] = SWCRTE_CHANNEL_STOPPED;
            
            /*initialize actuator request data*/
            SwcRte_aLightingActuatorData[InstanceId].aLightingOutputIntesity[CharsIndex] = 0;
            
            /*initialize sensor data*/
            SwcRte_aLightingSensorData[InstanceId].aLightChannelSensorData[CharsIndex].u32LightingSensorValue =  0;
            SwcRte_aLightingSensorData[InstanceId].aLightChannelSensorData[CharsIndex].bSensorValueUpdated =  SWCRTE_FALSE;
            
            SwcLighting_SumFeedbackValue[InstanceId][CharsIndex] = 0U;
            SwcLighting_AvgValueCounter[InstanceId][CharsIndex] = 0U;
            SwcLighting_AvgFeedbackValue[InstanceId][CharsIndex] = 0U;
            SwcLighting_CountTransientError[InstanceId][CharsIndex] = 0U;   
            
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)    
            SwcRte_aLightingInfoData[InstanceId].aLightingChanInfo[CharsIndex].Status = SWCRTE_CHANNEL_STOPPED;        
            SwcRte_aLightingInfoData[InstanceId].aLightingChanInfo[CharsIndex].FbkVoltage = 0;    
            SwcRte_aLightingInfoData[InstanceId].aLightingChanInfo[CharsIndex].ActiveCommand = 0;                
            SwcRte_aLightingInfoData[InstanceId].aLightingChanInfo[CharsIndex].RequestTx = SWCRTE_FALSE;
#endif            
        }        
    }    
}

#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)    
/*================================================================================================*/
/**
@brief      SwcLighting_WriteComData – shall write the sensor value for the given instance
            of the Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] InputValue          Data read from Sensors that has to be written for this instance.

@return     Returns the value of success of executing the code 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_WriteComData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingComDataType  * InputValue) 
{    
    uint8_t CharsIndex = 0; 
     
    SwcRte_aLightingComData[LightingInstance].bComValueUpdated = SWCRTE_TRUE;
    
    for(CharsIndex = 0; CharsIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoOutputChannel; CharsIndex++)
    {
        SwcRte_aLightingComData[LightingInstance].aLightChannelValue[CharsIndex] = InputValue->aLightChannelValue[CharsIndex];
    }
}

/*================================================================================================*/
/**
@brief      SwcLighting_ReadComInfo – shall write the sensor value for the given instance
            of the Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] InputValue          Data read from Sensors that has to be written for this instance.

@return     Returns the value of success of executing the code 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_FetchComInfo(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingComInfoType  * InputValue)
{    
    uint8_t CharsIndex = 0;

    for(CharsIndex = 0; CharsIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoOutputChannel; CharsIndex++)
    {
        InputValue->aLightingChanInfo[CharsIndex].Status = SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[CharsIndex].Status;
        InputValue->aLightingChanInfo[CharsIndex].FbkVoltage = SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[CharsIndex].FbkVoltage;
        InputValue->aLightingChanInfo[CharsIndex].ActiveCommand = SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[CharsIndex].ActiveCommand;
        InputValue->aLightingChanInfo[CharsIndex].RequestTx =  SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[CharsIndex].RequestTx;    
    }
}

/*================================================================================================*/
/**
@brief      SwcLighting_SetComInfoEvent – shall write the sensor value for the given instance
            of the Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] InputValue          Data read from Sensors that has to be written for this instance.

@return     Returns the value of success of executing the code 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_SetComInfoEvent(SwcRte_AppInstanceIdType LightingInstance, boolean_t RequestTx) 
{    
    uint8_t CharsIndex = 0;

    for(CharsIndex = 0; CharsIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoOutputChannel; CharsIndex++)
    {         
        SwcRte_aLightingInfoData[LightingInstance].aLightingChanInfo[CharsIndex].RequestTx = RequestTx;        
    }
}

/*================================================================================================*/
/**
@brief      SwcLighting_GetComInfoEvent – return the boolean value of the request Tx value for the current 
            instance.

@param[in]  LightingInstance    Instance Index.

@return     Returns SWCRTE_TRUE if request TX is SWCRTE_TRUE for at least one channel and SWCRTE_FALSE otherwise.
@retval     SWCRTE_TRUE or SWCRTE_FALSE

@pre None
@post None
*/
/*================================================================================================*/
boolean_t SwcLighting_GetComInfoEvent(SwcRte_AppInstanceIdType RteAppInstance) 
{    
    uint8_t CharsIndex = 0;
    boolean_t retVal = SWCRTE_FALSE;
    
    for(CharsIndex = 0; CharsIndex < SwcLighting_ConfigPtr[RteAppInstance].u8NoOutputChannel; CharsIndex++)
    {
        if (SWCRTE_TRUE == SwcRte_aLightingInfoData[RteAppInstance].aLightingChanInfo[CharsIndex].RequestTx)
        {
            retVal = SWCRTE_TRUE;
            break;
        }    
    }    
    return retVal;
}
#endif


/*================================================================================================*/
/**
@brief      SwcLighting_WriteSensorData – shall write the sensor value for the given instance
            of the Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] InputValue          Data read from Sensors that has to be written for this instance.

@return     Returns the value of success of executing the code 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_WriteSensorData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingSensorValueType  * InputValue) 
{    
    uint8_t CharsIndex = 0;   
  
    SwcRte_aLightingSensorData[LightingInstance].LightInputSensorData.u32LightingSensorValue =  InputValue->LightInputSensorData.u32LightingSensorValue;
    SwcRte_aLightingSensorData[LightingInstance].LightInputSensorData.bSensorValueUpdated  =  InputValue->LightInputSensorData.bSensorValueUpdated;
    
    for(CharsIndex = 0; CharsIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoInputChannel; CharsIndex++)
    {
        SwcRte_aLightingSensorData[LightingInstance].aLightChannelSensorData[CharsIndex].u32LightingSensorValue =  InputValue->aLightChannelSensorData[CharsIndex].u32LightingSensorValue;
        SwcRte_aLightingSensorData[LightingInstance].aLightChannelSensorData[CharsIndex].bSensorValueUpdated  =  InputValue->aLightChannelSensorData[CharsIndex].bSensorValueUpdated;        
    }
}

/*================================================================================================*/
/**
@brief      SwcLighting_ReadSensorData – shall write the sensor value for the given instance 
            of the Lighting application.

@param[in]  LightingInstance    Instance Index.
@param[out] OutputValue          Data read from Lighting that has to be provided for other applications
                                 for this instance.

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_ReadSensorData(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingSensorValueType  * OutputValue) 
{    
    uint8_t CharsIndex = 0;  
  
    OutputValue->LightInputSensorData.u32LightingSensorValue = SwcRte_aLightingSensorData[LightingInstance].LightInputSensorData.u32LightingSensorValue;    
    OutputValue->LightInputSensorData.bSensorValueUpdated = SwcRte_aLightingSensorData[LightingInstance].LightInputSensorData.bSensorValueUpdated;
    
    for(CharsIndex = 0; CharsIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoInputChannel; CharsIndex++)
    {
        OutputValue->aLightChannelSensorData[CharsIndex].u32LightingSensorValue = SwcRte_aLightingSensorData[LightingInstance].aLightChannelSensorData[CharsIndex].u32LightingSensorValue;          
        OutputValue->aLightChannelSensorData[CharsIndex].bSensorValueUpdated = SwcRte_aLightingSensorData[LightingInstance].aLightChannelSensorData[CharsIndex].bSensorValueUpdated;       
    }
}

/*================================================================================================*/
/**
@brief      SwcRte_WriteLightingOutputRequest - This function shall read any output change request 
            coming from the Lighting Application, process these request and store the values in 
            the internal data so it will be sent to IoDal via SwcActuator_WriteOutputs().

@param[in]  LightingInstance    Instance Index.
@param[out] OutputValue         Value of the output request that is sent to Actuators for this instance

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_ReadOutputRequest(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingActuatorValueType * OutputValue)
{    
    uint8_t ChIndex = 0;     
     
    for(ChIndex = 0; ChIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoOutputChannel; ChIndex++)
    { 
        OutputValue->aLightingOutputIntesity[ChIndex] = SwcRte_aLightingActuatorData[LightingInstance].aLightingOutputIntesity[ChIndex];
        OutputValue->aChannelState[ChIndex] = SwcRte_aLightingActuatorData[LightingInstance].aChannelState[ChIndex];
    }
}

/*================================================================================================*/
/**
@brief      SwcRte_WriteLightingOutputRequest - This function shall read any output change request coming from the Lighting Application,
                                                 process these request and store the values in the internal data so it will be sent to IoDal via SwcActuator_WriteOutputs().
                                                 
@param[in]  LightingInstance    Instance Index.
@param[out] OutputValue         Value of the (forced) output written in Lighting instance by other application

@return     Returns the value of success of executing the - 
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_WriteOutputRequest(SwcRte_AppInstanceIdType LightingInstance, SwcRte_AppLightingActuatorValueType * InputValue)
{    
    uint8_t ChIndex = 0;     
     
    for(ChIndex = 0; ChIndex < SwcLighting_ConfigPtr[LightingInstance].u8NoOutputChannel; ChIndex++)
    { 
        SwcRte_aLightingActuatorData[LightingInstance].aLightingOutputIntesity[ChIndex] = InputValue->aLightingOutputIntesity[ChIndex];
        SwcRte_aLightingActuatorData[LightingInstance].aChannelState[ChIndex] = InputValue->aChannelState[ChIndex];
    }    
}

/*================================================================================================*/
/**
@brief      SwcLighting_MainRunnable - main processing function for VDR
@details    This function is called periodically by the OS or by the main() function.

@param[in]  LightingInstance    Instance Index.

@return     Returns the value of success
@retval     E_OK or E_NOT_OK

@pre None
@post None
*/
/*================================================================================================*/
void SwcLighting_MainRunnable(SwcRte_AppInstanceIdType RteAppInstance)
{
    switch(SwcLightning_InstanceState[RteAppInstance])
    {
        case  SWCRTE_READINPUTS: 
        {
            if((SWCRTE_TRUE == SwcRte_aLightingSensorData[RteAppInstance].LightInputSensorData.bSensorValueUpdated) 
#if (SWCRTE_VDR_APP_ENABLED == SWCRTE_STD_ON)                    
                ||
                (SWCRTE_TRUE == SwcRte_aLightingComData[RteAppInstance].bComValueUpdated)
#endif                
              )               
            {    
                /*read all inputs and calculate possible outputs*/
                SwcLighting_CalculateOuputValue(RteAppInstance);

                SwcRte_aLightingSensorData[RteAppInstance].LightInputSensorData.bSensorValueUpdated = SWCRTE_FALSE;

                SwcLightning_InstanceState[RteAppInstance] = SWCRTE_PROCESSFEEDBACK;
            }
        } break;

        case SWCRTE_PROCESSFEEDBACK:
        {                         
            /*process feedback values and reset state machine*/
            SwcLighting_ProcessFeedback(RteAppInstance);

            SwcLightning_InstanceState[RteAppInstance] = SWCRTE_READINPUTS; 
        } break;

        default :
           SwcLightning_InstanceState[RteAppInstance] = SWCRTE_READINPUTS; 
           break;
    }
}
#endif


/*================================================================================================*/

#ifdef __cplusplus
}
#endif
/** @} */

