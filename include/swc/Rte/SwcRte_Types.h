/**
    @file        SwcRte_Types.h
*   @version     0.8.1
*
*   @brief       Integration Framework - SW component RTE TYPES header file
*
*   @details     This file implements SwcRte types header file.  
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
#ifndef SWCRTE_TYPES_H
#define SWCRTE_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

#include "typedefs.h"


/*==================================================================================================
                                       SOURCE FILE VERSION INFORMATION
====================================================================================================*/
#define SWCRTE_TYPES_VENDOR_ID                          43

#define SWCRTE_TYPES_SW_MAJOR_VERSION                   0
#define SWCRTE_TYPES_SW_MINOR_VERSION                   8
#define SWCRTE_TYPES_SW_PATCH_VERSION                   1

/*==================================================================================================
*                                     FILE VERSION CHECKS
==================================================================================================*/
 

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define SWCRTE_MEAS_OK       0U
#define SWCRTE_MEAS_NOT_OK   1U
/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
typedef uint8_t SwcRte_PowerModeType;

typedef enum
{
    SWCRTE_BUTTON_OFF = 0U,
    SWCRTE_BUTTON_ON  = 1U
}SwcRte_InputStateType;


typedef enum
{
    SWCRTE_CHANNEL_IDLE   = 0U,
    SWCRTE_CHANNEL_ACTIVE = 1U,
    SWCRTE_CHANNEL_STOPPED  = 2U,
    SWCRTE_CHANNEL_SHORT2GND = 4U,
    SWCRTE_CHANNEL_OPEN_LOAD = 8U
}SwcRte_ChannelStateType;


typedef enum
{
    SWCRTE_READINPUTS = 0U,
    SWCRTE_PROCESSFEEDBACK  = 1U
}SwcRte_InstanceStateType;


typedef enum
{
    SWCRTE_MC_CW  = 0U,    /**< @brief Motor rotation direction is Clock-Wise. */
    SWCRTE_MC_CCW,         /**< @brief Motor rotation direction is Counter Clock-Wise.  */
    SWCRTE_MC_STOP         /**< @brief Motor Stopped  */
} SwcRte_AppMotorDirectionType;


typedef enum
{
    SWCRTE_LIGHTING  = 0U,    /**< @brief Motor rotation direction is Clock-Wise. */
    SWCRTE_MOTORCTRL,         /**< @brief Motor rotation direction is Counter Clock-Wise.  */
    SWCRTE_VDR                /**< @brief Motor Stopped  */
} SwcRte_AppInstanceType;


typedef enum
{
    SWCRTE_DIGITAL_SENS  = 0U,   /**< @brief Application uses digital buttons (inputs) as sensor. */
    SWCRTE_ANALOG_POT_SENS,      /**< @brief Application uses analog potentiometer as sensor. */
    SWCRTE_ANALOG_FDBK_SENS,     /**< @brief Application has analog feedback. */
    SWCRTE_INPUT_CAPTURE_SENS,   /**< @brief Application has inpuc capture feedback. */
    SWCRTE_COM_DATA_INPUT,       /**< @brief Application uses a communication channel as 'sensor'. */   
    SWCRTE_NO_SENS,	
} SwcRte_AppInputSensorType;

typedef enum
{
    SWCRTE_UART_CHANNEL  = 0U,    /**< @brief Application uses UART as COM Channel. */
    SWCRTE_CAN_CHANNEL,           /**< @brief Application uses CAN as COM Channel. */
    SWCRTE_LIN_CHANNEL,           /**< @brief Application uses LIN as COM Channel. */
    SWCRTE_ETH_CHANNEL,           /**< @brief Application uses ETH as COM Channel. */
    SWCRTE_NO_CHANNEL,    
} SwcRte_AppComChannelType;

typedef enum
{
    SWCRTE_RX_REQ_STATUS = 1U,             /**< @brief  RX message is used to request STATUS. */
    SWCRTE_RX_REQ_OUTPUT_UPDATE = 2U,      /**< @brief  RX message is used to request OUTPUT UPDATE. */
    SWCRTE_RX_REQ_SYS_GO_SLEEP = 4U,       /**< @brief  RX message is used to request SYSTEM SWITCH TO POWER. */
    SWCVDR_RX_REQ_CHANGE_HW_VARIANT = 8U,  /**< @brief  RX message is used to request TO CHANGE HW VARIANT. */
    SWCRTE_RX_FORWARD_MSG = 16U,           /**< @brief  RX message is used to request TO FORWARD MESSAGE. */
    SWCRTE_RX_REQ_PRINT_RTM_MEAS = 32U,    /**< @brief  RX message is used to request TO PRINT RTM RESULTS. */
    SWCRTE_RX_REQ_DISCOVERY = 64U,         /**< @brief  RX message is used to request INSTANCES DISCOVERY */
    SWCRTE_RX_REQ_INVALID,    
} SwcRte_RxMessageType;


typedef enum
{    
    SCWRTE_TX_ON_EVENT = 1U,     /**< @brief  TX message is used ON EVENT TO SEND STATUS. */
    SCWRTE_TX_SEND_MSG= 16U,   /**< @brief  TX message is used ON EVENT TO FORWARD MESSAGE. */
    SCWRTE_TX_ON_REQUEST = 32U,   /**< @brief  TX message is used ON REQUEST TO SEND SPECIFIC DATA. */ 
    SWCRTE_TX_TYPE_INVALID,    
} SwcRte_TxMessageType;


typedef enum
{    
    SCWRTE_TX_MSG = 1U,       /**< @brief  Application uses a Transmit only message . */
    SCWRTE_RX_MSG = 2U,        /**< @brief  Application uses a Receive only message . */
    SWCRTE_INVALID_MESSAGETYPE,    
} SwcRte_MessageDirType;

typedef enum
{
    SWCRTE_DIGITAL_OUT  = 0U,      /**< @brief Application uses full-on/full-off actuator. */
    SWCRTE_PWM_OUT,                /**< @brief Application uses PWM controlled actuator. */
    SWCRTE_EXTDEV_OUT,              /**< @brief Application uses external device controlled actuator. */
    SWCRTE_COM,
} SwcRte_AppActuatorType;

typedef enum
{
    SWCRTE_E_OK = 0U,
    SWCRTE_E_NOT_OK  = 1U
}SwcRte_AppReturnType;


/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef uint8_t SwcRte_AppInstanceIdType;                /**< @brief Number of instances of each application */

typedef uint8_t SwcRte_AppMessageIdType;

typedef uint8_t SwcRte_AppChannelIdType;                /**< @brief Number of channels of each application */

typedef uint16_t SwcRte_OutputValueType;                 /**< @brief Application output value request type */

typedef char  SwcRte_DataMessageType;                   /**< @brief Application data type used to store COM messages */
/**< @brief Type used to define all output channels of a given application instance*/
typedef struct 
{
    const SwcRte_AppChannelIdType  u8OutputChannel;              /**< @brief Id of used the BSW output channel */
} SwcRte_OutputChannelConfigType; 

/**< @brief Type used to define all input channels of a given application instance*/
typedef struct 
{
    const SwcRte_AppChannelIdType   u8InputChannel;               /**< @brief Id of used the BSW input channel */
    const SwcRte_AppInputSensorType eInputType;                   /**< @brief Type of the input channel*/
} SwcRte_InputChannelConfigType; 

/**< @brief Type used to define the configuration for RX messages*/
typedef struct 
{
    uint8_t                    u8BswComChannelId;               /**< @brief Id of used the BSW COM channel */
    SwcRte_AppMessageIdType    AssociatedTxMsgId;               /**< @brief Associated TX message ID - if the message requires a TX-Reply  */
    uint8_t                    u8VdrRxMessageDataLen;           /**< @brief RX message data length  */
} SwcRte_MessgeRxBuffConfigType; 

/**< @brief Type used to define the configuration for TX messages*/
typedef struct 
{
    SwcRte_TxMessageType       eMessageReplyType;              /**< @brief TX-Reply type:  */    
    uint8_t                    u8BswComChannelId;              /**< @brief Id of used the BSW COM channel */
    uint8_t                    u8VdrTxMessageDataLen;          /**< @brief TX message data length  */
    SwcRte_DataMessageType   * pDataMessagePtr;                /**< @brief Pointer to the pre-allocated TX buffer  */
} SwcRte_MessgeTxBuffConfigType; 


 /**< @brief Global Application configuration structure type*/
typedef struct 
{
    const SwcRte_AppInstanceType           eInstanceType;          /**< @brief Type of the current instance */
    const SwcRte_AppActuatorType           eOutputType;                  /**< @brief Type of the output channel*/
    const uint8_t                          u8NoInputChannel;       /**< @brief Number of input channels for current instance */
    const uint8_t                          u8NoOutputChannel;      /**< @brief Number of output channels for current instance */
    const uint8_t                          u8NoRxMessages;           /**< @brief Number of messages in the list*/
    const uint8_t                          u8NoTxMessages;           /**< @brief Number of messages in the list*/     
    const SwcRte_InputChannelConfigType  * pInstanceInputSensor;      /**< @brief Pointer to the input channel configuration  */
    const SwcRte_OutputChannelConfigType * pInstanceActuator;   /**< @brief Pointer to the output channel configuration */
    const SwcRte_MessgeRxBuffConfigType  * pRxMessageList;   /**< @brief Pointer to the output channel configuration */
    const SwcRte_MessgeTxBuffConfigType  * pTxMessageList;   /**< @brief Pointer to the output channel configuration */
} SwcRte_GlobalConfigType; 

 /**< @brief RTE abstraction type used to pass sensor information from lower layer to application layer.*/
typedef struct
{
    uint16_t  Value;
    uint8_t   Status;        
}SwcRte_AppInputValueType;

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/




/*================================================================================================*/
/*================================================================================================*/
#ifdef __cplusplus
}
#endif
#endif /*SWCRTE_TYPES_H*/
/** @} */
