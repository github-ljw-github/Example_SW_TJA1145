///////////////////////////////////////////////////////////////////////////////////////////////////
// © NXP B.V. 2013. All rights reserved.
// Disclaimer
// 1.         The NXP Software/Source Code is provided to Licensee "AS IS" without any warranties of
// any kind. NXP makes no warranties to Licensee and shall not indemnify Licensee or hold it harmless
// for any reason related to the NXP Software/Source Code or otherwise be liable to the NXP customer.
// The NXP customer acknowledges and agrees that the NXP Software/Source Code is provided AS-IS and
// accepts all risks of utilizing the NXP Software under the conditions set forth according to this
// disclaimer.
//
// 2.         NXP EXPRESSLY DISCLAIMS ALL WARRANTIES, EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED
// TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE, AND
// NON-INFRINGEMENT OF INTELLECTUAL PROPERTY RIGHTS. NXP SHALL HAVE NO LIABILITY TO THE NXP CUSTOMER,
// OR ITS SUBSIDIARIES, AFFILIATES, OR ANY OTHER THIRD PARTY FOR ANY DAMAGES, INCLUDING WITHOUT
// LIMITATION, DAMAGES RESULTING OR ALLEGDED TO HAVE RESULTED FROM ANY DEFECT, ERROR OR OMMISSION IN
// THE NXP SOFTWARE/SOURCE CODE, THIRD PARTY APPLICATION SOFTWARE AND/OR DOCUMENTATION, OR AS A
// RESULT OF ANY INFRINGEMENT OF ANY INTELLECTUAL PROPERTY RIGHT OF ANY THIRD PARTY. IN NO EVENT
// SHALL NXP BE LIABLE FOR ANY INCIDENTAL, INDIRECT, SPECIAL, EXEMPLARY, PUNITIVE, OR CONSEQUENTIAL
// DAMAGES (INCLUDING LOST PROFITS) SUFFERED BY NXP CUSTOMER OR ITS SUBSIDIARIES, AFFILIATES,
// OR ANY OTHER THIRD PARTY ARISING OUT OF OR RELATED TO THE NXP SOFTWARE/SOURCE CODE EVEN IF
// NXP HAS BEEN ADVISED OF THE POSSIBILITY OF SUCH DAMAGES.
///////////////////////////////////////////////////////////////////////////////////////////////////

// $id:$
// XML Version: V1.2  Software Version: V1.1  Date: 05/16/2013  Time: 10:08

//--------------------------------------------------------------------------------
// pre-processor directive
#ifndef NXP_TJA1145FD_FUNCTIONS_H
#define NXP_TJA1145FD_FUNCTIONS_H

//--------------------------------------------------------------------------------
// general header include
#include "NXP_UJA11XX_defines.h"

//--------------------------------------------------------------------------------
// register depending enumerations
//--------------------------------------------------------------------------------
// register 0x01
//---------------------------------------------------
#define TJA1145FD_MODE_CONTROL_REG      (0x01)
#define TJA1145FD_MODE_CONTROL_REG_MASK (0x07)
//--------------------------------------
typedef enum
{
	TJA1145FD_MC_SLEEP_MODE	= 1,
	TJA1145FD_MC_STANDBY_MODE	= 4,
	TJA1145FD_MC_NORMAL_MODE	= 7
}TJA1145FD_Mode_Control_t;

#define TJA1145FD_MC_MASK   (0x07)   // bit [2:0]
#define TJA1145FD_MC_SHIFT  (0)

//---------------------------------------------------
// register 0x03
//---------------------------------------------------
#define TJA1145FD_MAIN_STATUS_REG      (0x03)
#define TJA1145FD_MAIN_STATUS_REG_MASK (0xE0)
//--------------------------------------
typedef enum
{
	TJA1145FD_FSMS_AN_UNDERVOLTAGE_ON_VCC_AND_OR_VIO_FORCED_A_TRANSITION_TO_SLEEP_MODE	= 1,
	TJA1145FD_FSMS_TRANSITION_TO_SLEEP_MODE_WAS_NOT_TRIGGERED_BY_AN_UNDERVOLTAGE_ON_VCC_AND_OR_VIO	= 0
}TJA1145FD_Forced_Sleep_Mode_Status_t;

#define TJA1145FD_FSMS_MASK   (0x80)   // bit [7]
#define TJA1145FD_FSMS_SHIFT  (7)
//--------------------------------------
typedef enum
{
	TJA1145FD_OTWS_TEMP_ABOVE	= 1,
	TJA1145FD_OTWS_TEMP_BELOW	= 0
}TJA1145FD_Over_Temperature_Warning_Status_t;

#define TJA1145FD_OTWS_MASK   (0x40)   // bit [6]
#define TJA1145FD_OTWS_SHIFT  (6)
//--------------------------------------
typedef enum
{
	TJA1145FD_NMS_NORMAL_MODE_NOT_ENTERED	= 1,
	TJA1145FD_NMS_NORMAL_MODE_ENTERED	= 0
}TJA1145FD_Normal_Mode_Status_t;

#define TJA1145FD_NMS_MASK   (0x20)   // bit [5]
#define TJA1145FD_NMS_SHIFT  (5)

//---------------------------------------------------
// register 0x04
//---------------------------------------------------
#define TJA1145FD_SYSTEM_EVENT_ENABLE_REG      (0x04)
#define TJA1145FD_SYSTEM_EVENT_ENABLE_REG_MASK (0x06)
//--------------------------------------
typedef enum
{
	TJA1145FD_OTWE_OVER_TEMPERATURE_WARNING_ENABLED	= 1,
	TJA1145FD_OTWE_OVER_TEMPERATURE_WARNING_DISABLED	= 0
}TJA1145FD_Over_Temperature_Warning_Enable_t;

#define TJA1145FD_OTWE_MASK   (0x04)   // bit [2]
#define TJA1145FD_OTWE_SHIFT  (2)
//--------------------------------------
typedef enum
{
	TJA1145FD_SPIFE_SPI_FAILURE_DETECTION_ENABLED	= 1,
	TJA1145FD_SPIFE_SPI_FAILURE_DETECTION_DISABLED	= 0
}TJA1145FD_SPI_Failure_Detect_Enable_t;

#define TJA1145FD_SPIFE_MASK   (0x02)   // bit [1]
#define TJA1145FD_SPIFE_SHIFT  (1)

//---------------------------------------------------
// register 0x06
//---------------------------------------------------
#define TJA1145FD_MEMORY_0_REG      (0x06)
#define TJA1145FD_MEMORY_0_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_RAM_Memory_0700_t;

#define TJA1145FD_GPM0_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_GPM0_SHIFT  (0)

//---------------------------------------------------
// register 0x07
//---------------------------------------------------
#define TJA1145FD_MEMORY_1_REG      (0x07)
#define TJA1145FD_MEMORY_1_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_RAM_Memory_0815_t;

#define TJA1145FD_GPM1_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_GPM1_SHIFT  (0)

//---------------------------------------------------
// register 0x08
//---------------------------------------------------
#define TJA1145FD_MEMORY_2_REG      (0x08)
#define TJA1145FD_MEMORY_2_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_RAM_Memory_1623_t;

#define TJA1145FD_GPM2_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_GPM2_SHIFT  (0)

//---------------------------------------------------
// register 0x09
//---------------------------------------------------
#define TJA1145FD_MEMORY_3_REG      (0x09)
#define TJA1145FD_MEMORY_3_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_RAM_Memory_2431_t;

#define TJA1145FD_GPM3_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_GPM3_SHIFT  (0)

//---------------------------------------------------
// register 0x0A
//---------------------------------------------------
#define TJA1145FD_LOCK_CONTROL_REG      (0x0A)
#define TJA1145FD_LOCK_CONTROL_REG_MASK (0x7F)
//--------------------------------------
typedef enum
{
	TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F	= 1,
	TJA1145FD_LK6C_SPI_WRITE_ACCESS_ENABLED_0X68_TO_0X6F	= 0
}TJA1145FD_Lock_Control_6_t;

#define TJA1145FD_LK6C_MASK   (0x40)   // bit [6]
#define TJA1145FD_LK6C_SHIFT  (6)
//--------------------------------------
typedef enum
{
	TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F	= 1,
	TJA1145FD_LK5C_SPI_WRITE_ACCESS_ENABLED_0X50_TO_0X5F	= 0
}TJA1145FD_Lock_Control_5_t;

#define TJA1145FD_LK5C_MASK   (0x20)   // bit [5]
#define TJA1145FD_LK5C_SHIFT  (5)
//--------------------------------------
typedef enum
{
	TJA1145FD_LK4C_SPI_WRITE_ACCESS_DISABLED_0X40_TO_0X4F	= 1,
	TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F	= 0
}TJA1145FD_Lock_Control_4_t;

#define TJA1145FD_LK4C_MASK   (0x10)   // bit [4]
#define TJA1145FD_LK4C_SHIFT  (4)
//--------------------------------------
typedef enum
{
	TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F	= 1,
	TJA1145FD_LK3C_SPI_WRITE_ACCESS_ENABLED_0X30_TO_0X3F	= 0
}TJA1145FD_Lock_Control_3_t;

#define TJA1145FD_LK3C_MASK   (0x08)   // bit [3]
#define TJA1145FD_LK3C_SHIFT  (3)
//--------------------------------------
typedef enum
{
	TJA1145FD_LK2C_SPI_WRITE_ACCESS_DISABLED_0X20_TO_0X2F	= 1,
	TJA1145FD_LK2C_SPI_WRITE_ACCESS_ENABLED_0X20_TO_0X2F	= 0
}TJA1145FD_Lock_Control_2_t;

#define TJA1145FD_LK2C_MASK   (0x04)   // bit [2]
#define TJA1145FD_LK2C_SHIFT  (2)
//--------------------------------------
typedef enum
{
	TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F	= 1,
	TJA1145FD_LK1C_SPI_WRITE_ACCESS_ENABLED_0X10_TO_0X1F	= 0
}TJA1145FD_Lock_Control_1_t;

#define TJA1145FD_LK1C_MASK   (0x02)   // bit [1]
#define TJA1145FD_LK1C_SHIFT  (1)
//--------------------------------------
typedef enum
{
	TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09	= 1,
	TJA1145FD_LK0C_SPI_WRITE_ACCESS_ENABLED_0X06_TO_0X09	= 0
}TJA1145FD_Lock_Control_0_t;

#define TJA1145FD_LK0C_MASK   (0x01)   // bit [0]
#define TJA1145FD_LK0C_SHIFT  (0)

//---------------------------------------------------
// register 0x20
//---------------------------------------------------
#define TJA1145FD_CAN_CONTROL_REG      (0x20)
#define TJA1145FD_CAN_CONTROL_REG_MASK (0x73)
//--------------------------------------
typedef enum
{
	TJA1145FD_CFDC_CAN_FD_TOLERANCE_ENABLED	= 1,
	TJA1145FD_CFDC_CAN_FD_TOLERANCE_DISABLED	= 0
}TJA1145FD_CAN_FD_tolerance_t;

#define TJA1145FD_CFDC_MASK   (0x40)   // bit [6]
#define TJA1145FD_CFDC_SHIFT  (6)
//--------------------------------------
typedef enum
{
	TJA1145FD_PNCOK_PARTIAL_NETWORK_CONFIGURATION_SUCCESSFUL	= 1,
	TJA1145FD_PNCOK_PARTIAL_NETWORK_CONFIGURATION_INVALID	= 0
}TJA1145FD_Partial_Network_Config_t;

#define TJA1145FD_PNCOK_MASK   (0x20)   // bit [5]
#define TJA1145FD_PNCOK_SHIFT  (5)
//--------------------------------------
typedef enum
{
	TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_ENABLE	= 1,
	TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_DISABLE	= 0
}TJA1145FD_CAN_Selective_WakeUp_t;

#define TJA1145FD_CPNC_MASK   (0x10)   // bit [4]
#define TJA1145FD_CPNC_SHIFT  (4)
//--------------------------------------
typedef enum
{
	TJA1145FD_CMC_OFFLINE_MODE	= 0,
	TJA1145FD_CMC_ACTIVE_WITH_VCC_UNDERVOLTAGE_DETECTION_ACTIVE	= 1,
	TJA1145FD_CMC_ACTIVE_WITH_VCC_UNDERVOLTAGE_DETECTION_OFF	= 2,
	TJA1145FD_CMC_LISTEN_ONLY_MODE	= 3
}TJA1145FD_CAN_Mode_Selection_t;

#define TJA1145FD_CMC_MASK   (0x03)   // bit [1:0]
#define TJA1145FD_CMC_SHIFT  (0)

//---------------------------------------------------
// register 0x22
//---------------------------------------------------
#define TJA1145FD_TRANSCEIVER_STATUS_REG      (0x22)
#define TJA1145FD_TRANSCEIVER_STATUS_REG_MASK (0xFB)
//--------------------------------------
typedef enum
{
	TJA1145FD_CTS_CAN_TRANSMITTER_READY_TO_TRANSMIT_DATA	= 1,
	TJA1145FD_CTS_CAN_TRANSMITTER_DISABLED	= 0
}TJA1145FD_CAN_Transmitter_Status_t;

#define TJA1145FD_CTS_MASK   (0x80)   // bit [7]
#define TJA1145FD_CTS_SHIFT  (7)
//--------------------------------------
typedef enum
{
	TJA1145FD_CPNERR_PARTIAL_NETWORK_ERROR_DETECTED	= 1,
	TJA1145FD_CPNERR_NO_PARTIAL_NETWORK_ERROR	= 0
}TJA1145FD_Partial_Network_Error_t;

#define TJA1145FD_CPNERR_MASK   (0x40)   // bit [6]
#define TJA1145FD_CPNERR_SHIFT  (6)
//--------------------------------------
typedef enum
{
	TJA1145FD_CPNS_PARTIAL_NETWORK_CONFIGURATION_OK	= 1,
	TJA1145FD_CPNS_PARTIAL_NETWORK_CONFIGURATION_ERROR	= 0
}TJA1145FD_Partial_Network_Config_Error_t;

#define TJA1145FD_CPNS_MASK   (0x20)   // bit [5]
#define TJA1145FD_CPNS_SHIFT  (5)
//--------------------------------------
typedef enum
{
	TJA1145FD_COSCS_OSCILLATOR_RUNNING_ON_TARGET_FREQ	= 1,
	TJA1145FD_COSCS_OSCILLATOR_NOT_RUNNING_ON_TARGET_FREQ	= 0
}TJA1145FD_Partial_Network_Osc_t;

#define TJA1145FD_COSCS_MASK   (0x10)   // bit [4]
#define TJA1145FD_COSCS_SHIFT  (4)
//--------------------------------------
typedef enum
{
	TJA1145FD_CBSS_CAN_BUS_INACTIVE	= 1,
	TJA1145FD_CBSS_CAN_BUS_ACTIVE	= 0
}TJA1145FD_CAN_Bus_Status_t;

#define TJA1145FD_CBSS_MASK   (0x08)   // bit [3]
#define TJA1145FD_CBSS_SHIFT  (3)
//--------------------------------------
typedef enum
{
	TJA1145FD_VCS_OUTPUT_VOLTAGE_ON_V1_IS_BELOW_THE_90_THRESHOLD	= 1,
	TJA1145FD_VCS_OUTPUT_VOLTAGE_ON_V1_IS_ABOVE_THE_90_THRESHOLD	= 0
}TJA1145FD_VCAN_Status_t;

#define TJA1145FD_VCS_MASK   (0x02)   // bit [1]
#define TJA1145FD_VCS_SHIFT  (1)
//--------------------------------------
typedef enum
{
	TJA1145FD_CFS_TIMEOUT_EVENT_DISABLED_CAN_TRANSMITTER	= 1,
	TJA1145FD_CFS_NO_TXD_TIMEOUT_EVENT	= 0
}TJA1145FD_Dominant_Timeout_Event_t;

#define TJA1145FD_CFS_MASK   (0x01)   // bit [0]
#define TJA1145FD_CFS_SHIFT  (0)

//---------------------------------------------------
// register 0x23
//---------------------------------------------------
#define TJA1145FD_TRANSCEIVER_EVENT_ENABLE_REG      (0x23)
#define TJA1145FD_TRANSCEIVER_EVENT_ENABLE_REG_MASK (0x13)
//--------------------------------------
typedef enum
{
	TJA1145FD_CBSE_CAN_BUS_SILENCE_DETECTION_ENABLED	= 1,
	TJA1145FD_CBSE_CAN_BUS_SILENCE_DETECTION_DISABLED	= 0
}TJA1145FD_CAN_Bus_Silence_Detect_t;

#define TJA1145FD_CBSE_MASK   (0x10)   // bit [4]
#define TJA1145FD_CBSE_SHIFT  (4)
//--------------------------------------
typedef enum
{
	TJA1145FD_CFE_CAN_FAILURE_DETECTION_ENABLE	= 1,
	TJA1145FD_CFE_CAN_FAILURE_DETECTION_DISABLE	= 0
}TJA1145FD_CAN_Failure_Detect_t;

#define TJA1145FD_CFE_MASK   (0x02)   // bit [1]
#define TJA1145FD_CFE_SHIFT  (1)
//--------------------------------------
typedef enum
{
	TJA1145FD_CWE_CAN_WAKEUP_DETECTION_ENABLE	= 1,
	TJA1145FD_CWE_CAN_WAKEUP_DETECTION_DISABLE	= 0
}TJA1145FD_CAN_WakeUp_Detect_t;

#define TJA1145FD_CWE_MASK   (0x01)   // bit [0]
#define TJA1145FD_CWE_SHIFT  (0)

//---------------------------------------------------
// register 0x26
//---------------------------------------------------
#define TJA1145FD_DATA_RATE_REG      (0x26)
#define TJA1145FD_DATA_RATE_REG_MASK (0x07)
//--------------------------------------
typedef enum
{
	TJA1145FD_CDR_50_KBIT_PER_S	= 0,
	TJA1145FD_CDR_100_KBIT_PER_S	= 1,
	TJA1145FD_CDR_125_KBIT_PER_S	= 2,
	TJA1145FD_CDR_250_KBIT_PER_S	= 3,
	TJA1145FD_CDR_500_KBIT_PER_S	= 5,
	TJA1145FD_CDR_1000_KBIT_PER_S	= 7
}TJA1145FD_CAN_Data_Rate_t;

#define TJA1145FD_CDR_MASK   (0x07)   // bit [2:0]
#define TJA1145FD_CDR_SHIFT  (0)

//---------------------------------------------------
// register 0x27
//---------------------------------------------------
#define TJA1145FD_CAN_IDENTIFIER_0_REG      (0x27)
#define TJA1145FD_CAN_IDENTIFIER_0_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_ID0700_t;

#define TJA1145FD_ID0700_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_ID0700_SHIFT  (0)

//---------------------------------------------------
// register 0x28
//---------------------------------------------------
#define TJA1145FD_CAN_IDENTIFIER_1_REG      (0x28)
#define TJA1145FD_CAN_IDENTIFIER_1_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_ID1508_t;

#define TJA1145FD_ID1508_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_ID1508_SHIFT  (0)

//---------------------------------------------------
// register 0x29
//---------------------------------------------------
#define TJA1145FD_CAN_IDENTIFIER_2_REG      (0x29)
#define TJA1145FD_CAN_IDENTIFIER_2_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_ID2318_t;

#define TJA1145FD_ID2318_MASK   (0xFC)   // bit [7:2]
#define TJA1145FD_ID2318_SHIFT  (2)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_ID1716_t;

#define TJA1145FD_ID1716_MASK   (0x03)   // bit [1:0]
#define TJA1145FD_ID1716_SHIFT  (0)

//---------------------------------------------------
// register 0x2A
//---------------------------------------------------
#define TJA1145FD_CAN_IDENTIFIER_3_REG      (0x2A)
#define TJA1145FD_CAN_IDENTIFIER_3_REG_MASK (0x1F)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_ID2824_t;

#define TJA1145FD_ID2824_MASK   (0x1F)   // bit [4:0]
#define TJA1145FD_ID2824_SHIFT  (0)

//---------------------------------------------------
// register 0x2B
//---------------------------------------------------
#define TJA1145FD_CAN_MASK_0_REG      (0x2B)
#define TJA1145FD_CAN_MASK_0_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_M0700_t;

#define TJA1145FD_M0700_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_M0700_SHIFT  (0)

//---------------------------------------------------
// register 0x2C
//---------------------------------------------------
#define TJA1145FD_CAN_MASK_1_REG      (0x2C)
#define TJA1145FD_CAN_MASK_1_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_M1508_t;

#define TJA1145FD_M1508_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_M1508_SHIFT  (0)

//---------------------------------------------------
// register 0x2D
//---------------------------------------------------
#define TJA1145FD_CAN_MASK_2_REG      (0x2D)
#define TJA1145FD_CAN_MASK_2_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_M2318_t;

#define TJA1145FD_M2318_MASK   (0xFC)   // bit [7:2]
#define TJA1145FD_M2318_SHIFT  (2)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_M1716_t;

#define TJA1145FD_M1716_MASK   (0x03)   // bit [1:0]
#define TJA1145FD_M1716_SHIFT  (0)

//---------------------------------------------------
// register 0x2E
//---------------------------------------------------
#define TJA1145FD_CAN_MASK_3_REG      (0x2E)
#define TJA1145FD_CAN_MASK_3_REG_MASK (0x1F)
//--------------------------------------
typedef unsigned char TJA1145FD_CAN_M2824_t;

#define TJA1145FD_M2824_MASK   (0x1F)   // bit [4:0]
#define TJA1145FD_M2824_SHIFT  (0)

//---------------------------------------------------
// register 0x2F
//---------------------------------------------------
#define TJA1145FD_FRAME_CONTROL_REG      (0x2F)
#define TJA1145FD_FRAME_CONTROL_REG_MASK (0xCF)
//--------------------------------------
typedef enum
{
	TJA1145FD_IDE_EXTENDED_FRAME_FORMAT_29_BIT	= 1,
	TJA1145FD_IDE_STANDARD_FRAME_FORMAT_11_BIT	= 0
}TJA1145FD_Identifier_Format_t;

#define TJA1145FD_IDE_MASK   (0x80)   // bit [7]
#define TJA1145FD_IDE_SHIFT  (7)
//--------------------------------------
typedef enum
{
	TJA1145FD_PNDM_DATA_LENGTH_CODE_AND_DATA_FIELD_ARE_EVALUATED_AT_WAKE_UP	= 1,
	TJA1145FD_PNDM_DATA_LENGTH_CODE_AND_DATA_FIELD_ARE_DO_NOT_CARE_FOR_WAKE_UP	= 0
}TJA1145FD_Partial_Network_Data_Mask_t;

#define TJA1145FD_PNDM_MASK   (0x40)   // bit [6]
#define TJA1145FD_PNDM_SHIFT  (6)
//--------------------------------------
typedef enum
{
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_0	= 0,
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_1	= 1,
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_2	= 2,
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_3	= 3,
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_4	= 4,
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_5	= 5,
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_6	= 6,
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_7	= 7,
	TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_8	= 8
}TJA1145FD_CAN_Data_Length_t;

#define TJA1145FD_DLC_MASK   (0x0F)   // bit [3:0]
#define TJA1145FD_DLC_SHIFT  (0)

//---------------------------------------------------
// register 0x4B
//---------------------------------------------------
#define TJA1145FD_WAKE_STATUS_REG      (0x4B)
#define TJA1145FD_WAKE_STATUS_REG_MASK (0x02)
//--------------------------------------
typedef enum
{
	TJA1145FD_WPVS_VOLTAGE_ABOVE_SWITCHING_THRESHOLD	= 1,
	TJA1145FD_WPVS_VOLTAGE_BELOW_SWITCHING_THRESHOLD	= 0
}TJA1145FD_Wake_Pin_Status_t;

#define TJA1145FD_WPVS_MASK   (0x02)   // bit [1]
#define TJA1145FD_WPVS_SHIFT  (1)

//---------------------------------------------------
// register 0x4C
//---------------------------------------------------
#define TJA1145FD_WAKE_PIN_ENABLE_REG      (0x4C)
#define TJA1145FD_WAKE_PIN_ENABLE_REG_MASK (0x03)
//--------------------------------------
typedef enum
{
	TJA1145FD_WPRE_WAKEPIN_RISING_EDGE_DETECT_ENABLE	= 1,
	TJA1145FD_WPRE_WAKEPIN_RISING_EDGE_DETECT_DISABLE	= 0
}TJA1145FD_Wake_Pin_Rising_Edge_Detect_t;

#define TJA1145FD_WPRE_MASK   (0x02)   // bit [1]
#define TJA1145FD_WPRE_SHIFT  (1)
//--------------------------------------
typedef enum
{
	TJA1145FD_WPFE_WAKEPIN_FALLING_EDGE_DETECT_ENABLE	= 1,
	TJA1145FD_WPFE_WAKEPIN_FALLING_EDGE_DETECT_DISABLE	= 0
}TJA1145FD_Wake_Pin_Falling_Edge_Detect_t;

#define TJA1145FD_WPFE_MASK   (0x01)   // bit [0]
#define TJA1145FD_WPFE_SHIFT  (0)

//---------------------------------------------------
// register 0x60
//---------------------------------------------------
#define TJA1145FD_GLOBAL_EVENT_STATUS_REG      (0x60)
#define TJA1145FD_GLOBAL_EVENT_STATUS_REG_MASK (0x0D)
//--------------------------------------
typedef enum
{
	TJA1145FD_WPE_WAKE_PIN_EVENT_PENDING	= 1,
	TJA1145FD_WPE_NO_WAKE_PIN_EVENT	= 0
}TJA1145FD_Wake_Pin_Event_t;

#define TJA1145FD_WPE_MASK   (0x08)   // bit [3]
#define TJA1145FD_WPE_SHIFT  (3)
//--------------------------------------
typedef enum
{
	TJA1145FD_TRXE_TRANSCEIVER_EVENT_PENDING	= 1,
	TJA1145FD_TRXE_NO_TRANSCEIVER_EVENT	= 0
}TJA1145FD_Transceiver_Event_t;

#define TJA1145FD_TRXE_MASK   (0x04)   // bit [2]
#define TJA1145FD_TRXE_SHIFT  (2)
//--------------------------------------
typedef enum
{
	TJA1145FD_SYSE_SYSTEM_EVENT_PENDING	= 1,
	TJA1145FD_SYSE_NO_SYSTEM_EVENT	= 0
}TJA1145FD_System_Event_t;

#define TJA1145FD_SYSE_MASK   (0x01)   // bit [0]
#define TJA1145FD_SYSE_SHIFT  (0)

//---------------------------------------------------
// register 0x61
//---------------------------------------------------
#define TJA1145FD_SYSTEM_EVENT_STATUS_REG      (0x61)
#define TJA1145FD_SYSTEM_EVENT_STATUS_REG_MASK (0x16)
//--------------------------------------
typedef enum
{
	TJA1145FD_PO_OFF_MODE_LEFT	= 1,
	TJA1145FD_PO_NO_POWER_ON	= 0
}TJA1145FD_Power_On_t;

#define TJA1145FD_PO_MASK   (0x10)   // bit [4]
#define TJA1145FD_PO_SHIFT  (4)
//--------------------------------------
typedef enum
{
	TJA1145FD_OTW_TEMPERATURE_EXCEEDS_WARNING_LEVEL	= 1,
	TJA1145FD_OTW_NO_OVER_TEMPERATURE	= 0
}TJA1145FD_Over_Temperature_Warning_t;

#define TJA1145FD_OTW_MASK   (0x04)   // bit [2]
#define TJA1145FD_OTW_SHIFT  (2)
//--------------------------------------
typedef enum
{
	TJA1145FD_SPIF_SPI_FAILURE_DETECTED	= 1,
	TJA1145FD_SPIF_NO_SPI_FAILURE	= 0
}TJA1145FD_SPI_Failure_t;

#define TJA1145FD_SPIF_MASK   (0x02)   // bit [1]
#define TJA1145FD_SPIF_SHIFT  (1)

//---------------------------------------------------
// register 0x63
//---------------------------------------------------
#define TJA1145FD_TRANSCEIVER_EVENT_STATUS_REG      (0x63)
#define TJA1145FD_TRANSCEIVER_EVENT_STATUS_REG_MASK (0x33)
//--------------------------------------
typedef enum
{
	TJA1145FD_PNFDE_PARTIAL_NETWORK_FRAME_ERROR_DETECTED	= 1,
	TJA1145FD_PNFDE_NO_PARTIAL_NETWORK_FRAME_ERROR	= 0
}TJA1145FD_Partial_Network_Frame_Detect_t;

#define TJA1145FD_PNFDE_MASK   (0x20)   // bit [5]
#define TJA1145FD_PNFDE_SHIFT  (5)
//--------------------------------------
typedef enum
{
	TJA1145FD_CBS_NO_CAN_BUS_ACTIVITY	= 1,
	TJA1145FD_CBS_CAN_BUS_ACTIVE	= 0
}TJA1145FD_CAN_Bus_Active_t;

#define TJA1145FD_CBS_MASK   (0x10)   // bit [4]
#define TJA1145FD_CBS_SHIFT  (4)
//--------------------------------------
typedef enum
{
	TJA1145FD_CF_CAN_FAILURE_DETECTED	= 1,
	TJA1145FD_CF_NO_CAN_FAILURE	= 0
}TJA1145FD_CAN_Failure_t;

#define TJA1145FD_CF_MASK   (0x02)   // bit [1]
#define TJA1145FD_CF_SHIFT  (1)
//--------------------------------------
typedef enum
{
	TJA1145FD_CW_CAN_WAKEUP_EVENT	= 1,
	TJA1145FD_CW_NO_CAN_WAKEUP	= 0
}TJA1145FD_CAN_WakeUp_t;

#define TJA1145FD_CW_MASK   (0x01)   // bit [0]
#define TJA1145FD_CW_SHIFT  (0)

//---------------------------------------------------
// register 0x64
//---------------------------------------------------
#define TJA1145FD_WAKE_PIN_EVENT_REG      (0x64)
#define TJA1145FD_WAKE_PIN_EVENT_REG_MASK (0x03)
//--------------------------------------
typedef enum
{
	TJA1145FD_WPR_WAKEPIN_RISING_EDGE_DETECTED	= 1,
	TJA1145FD_WPR_NO_WAKEPIN_RISING_EDGE	= 0
}TJA1145FD_Rising_Wake_Pin_Event_t;

#define TJA1145FD_WPR_MASK   (0x02)   // bit [1]
#define TJA1145FD_WPR_SHIFT  (1)
//--------------------------------------
typedef enum
{
	TJA1145FD_WPF_WAKEPIN_FALLING_EDGE_DETECTED	= 1,
	TJA1145FD_WPF_NO_WAKEPIN_FALLING_EDGE	= 0
}TJA1145FD_Falling_Wake_Pin_Event_t;

#define TJA1145FD_WPF_MASK   (0x01)   // bit [0]
#define TJA1145FD_WPF_SHIFT  (0)

//---------------------------------------------------
// register 0x68
//---------------------------------------------------
#define TJA1145FD_DATA_MASK_0_REG      (0x68)
#define TJA1145FD_DATA_MASK_0_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_Data_Mask_0_Config_t;

#define TJA1145FD_DM0_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_DM0_SHIFT  (0)

//---------------------------------------------------
// register 0x69
//---------------------------------------------------
#define TJA1145FD_DATA_MASK_1_REG      (0x69)
#define TJA1145FD_DATA_MASK_1_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_Data_Mask_1_Config_t;

#define TJA1145FD_DM1_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_DM1_SHIFT  (0)

//---------------------------------------------------
// register 0x6A
//---------------------------------------------------
#define TJA1145FD_DATA_MASK_2_REG      (0x6A)
#define TJA1145FD_DATA_MASK_2_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_Data_Mask_2_Config_t;

#define TJA1145FD_DM2_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_DM2_SHIFT  (0)

//---------------------------------------------------
// register 0x6B
//---------------------------------------------------
#define TJA1145FD_DATA_MASK_3_REG      (0x6B)
#define TJA1145FD_DATA_MASK_3_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_Data_Mask_3_Config_t;

#define TJA1145FD_DM3_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_DM3_SHIFT  (0)

//---------------------------------------------------
// register 0x6C
//---------------------------------------------------
#define TJA1145FD_DATA_MASK_4_REG      (0x6C)
#define TJA1145FD_DATA_MASK_4_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_Data_Mask_4_Config_t;

#define TJA1145FD_DM4_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_DM4_SHIFT  (0)

//---------------------------------------------------
// register 0x6D
//---------------------------------------------------
#define TJA1145FD_DATA_MASK_5_REG      (0x6D)
#define TJA1145FD_DATA_MASK_5_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_Data_Mask_5_Config_t;

#define TJA1145FD_DM5_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_DM5_SHIFT  (0)

//---------------------------------------------------
// register 0x6E
//---------------------------------------------------
#define TJA1145FD_DATA_MASK_6_REG      (0x6E)
#define TJA1145FD_DATA_MASK_6_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_Data_Mask_6_Config_t;

#define TJA1145FD_DM6_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_DM6_SHIFT  (0)

//---------------------------------------------------
// register 0x6F
//---------------------------------------------------
#define TJA1145FD_DATA_MASK_7_REG      (0x6F)
#define TJA1145FD_DATA_MASK_7_REG_MASK (0xFF)
//--------------------------------------
typedef unsigned char TJA1145FD_Data_Mask_7_Config_t;

#define TJA1145FD_DM7_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_DM7_SHIFT  (0)

//---------------------------------------------------
// register 0x7E
//---------------------------------------------------
#define TJA1145FD_IDENTIFICATION_REG      (0x7E)
#define TJA1145FD_IDENTIFICATION_REG_MASK (0xFF)
//--------------------------------------
typedef enum
{
	TJA1145FD_IDS_DEVICE_ID_TJA1145FD	= 116
}TJA1145FD_Device_ID_t;

#define TJA1145FD_IDS_MASK   (0xFF)   // bit [7:0]
#define TJA1145FD_IDS_SHIFT  (0)

//---------------------------------------------------
//--------------------------------------------------------------------------------
// function prototypes
//--------------------------------------------------------------------------------

NXP_UJA11XX_Error_Code_t TJA1145FD_getModeControlReg(TJA1145FD_Mode_Control_t* penMC );
NXP_UJA11XX_Error_Code_t TJA1145FD_setModeControlReg(TJA1145FD_Mode_Control_t enMC );

NXP_UJA11XX_Error_Code_t TJA1145FD_getMainStatus(TJA1145FD_Forced_Sleep_Mode_Status_t* penFSMS, TJA1145FD_Over_Temperature_Warning_Status_t* penOTWS, TJA1145FD_Normal_Mode_Status_t* penNMS );

NXP_UJA11XX_Error_Code_t TJA1145FD_getSystemEventEnable(TJA1145FD_Over_Temperature_Warning_Enable_t* penOTWE, TJA1145FD_SPI_Failure_Detect_Enable_t* penSPIFE );
NXP_UJA11XX_Error_Code_t TJA1145FD_setSystemEventEnable(TJA1145FD_Over_Temperature_Warning_Enable_t enOTWE, TJA1145FD_SPI_Failure_Detect_Enable_t enSPIFE );

NXP_UJA11XX_Error_Code_t TJA1145FD_getMemory0(TJA1145FD_RAM_Memory_0700_t* penGPM0 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setMemory0(TJA1145FD_RAM_Memory_0700_t enGPM0 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getMemory1(TJA1145FD_RAM_Memory_0815_t* penGPM1 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setMemory1(TJA1145FD_RAM_Memory_0815_t enGPM1 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getMemory2(TJA1145FD_RAM_Memory_1623_t* penGPM2 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setMemory2(TJA1145FD_RAM_Memory_1623_t enGPM2 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getMemory3(TJA1145FD_RAM_Memory_2431_t* penGPM3 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setMemory3(TJA1145FD_RAM_Memory_2431_t enGPM3 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getLockControl(TJA1145FD_Lock_Control_6_t* penLK6C, TJA1145FD_Lock_Control_5_t* penLK5C, TJA1145FD_Lock_Control_4_t* penLK4C, TJA1145FD_Lock_Control_3_t* penLK3C, TJA1145FD_Lock_Control_2_t* penLK2C, TJA1145FD_Lock_Control_1_t* penLK1C, TJA1145FD_Lock_Control_0_t* penLK0C );
NXP_UJA11XX_Error_Code_t TJA1145FD_setLockControl(TJA1145FD_Lock_Control_6_t enLK6C, TJA1145FD_Lock_Control_5_t enLK5C, TJA1145FD_Lock_Control_4_t enLK4C, TJA1145FD_Lock_Control_3_t enLK3C, TJA1145FD_Lock_Control_2_t enLK2C, TJA1145FD_Lock_Control_1_t enLK1C, TJA1145FD_Lock_Control_0_t enLK0C );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANControl(TJA1145FD_CAN_FD_tolerance_t* penCFDC, TJA1145FD_Partial_Network_Config_t* penPNCOK, TJA1145FD_CAN_Selective_WakeUp_t* penCPNC, TJA1145FD_CAN_Mode_Selection_t* penCMC );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANControl(TJA1145FD_CAN_FD_tolerance_t enCFDC, TJA1145FD_Partial_Network_Config_t enPNCOK, TJA1145FD_CAN_Selective_WakeUp_t enCPNC, TJA1145FD_CAN_Mode_Selection_t enCMC );

NXP_UJA11XX_Error_Code_t TJA1145FD_getTransceiverStatus(TJA1145FD_CAN_Transmitter_Status_t* penCTS, TJA1145FD_Partial_Network_Error_t* penCPNERR, TJA1145FD_Partial_Network_Config_Error_t* penCPNS, TJA1145FD_Partial_Network_Osc_t* penCOSCS, TJA1145FD_CAN_Bus_Status_t* penCBSS, TJA1145FD_VCAN_Status_t* penVCS, TJA1145FD_Dominant_Timeout_Event_t* penCFS );

NXP_UJA11XX_Error_Code_t TJA1145FD_getTransceiverEventEnable(TJA1145FD_CAN_Bus_Silence_Detect_t* penCBSE, TJA1145FD_CAN_Failure_Detect_t* penCFE, TJA1145FD_CAN_WakeUp_Detect_t* penCWE );
NXP_UJA11XX_Error_Code_t TJA1145FD_setTransceiverEventEnable(TJA1145FD_CAN_Bus_Silence_Detect_t enCBSE, TJA1145FD_CAN_Failure_Detect_t enCFE, TJA1145FD_CAN_WakeUp_Detect_t enCWE );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataRate(TJA1145FD_CAN_Data_Rate_t* penCDR );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataRate(TJA1145FD_CAN_Data_Rate_t enCDR );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANIdentifier0(TJA1145FD_CAN_ID0700_t* penID0700 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANIdentifier0(TJA1145FD_CAN_ID0700_t enID0700 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANIdentifier1(TJA1145FD_CAN_ID1508_t* penID1508 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANIdentifier1(TJA1145FD_CAN_ID1508_t enID1508 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANIdentifier2(TJA1145FD_CAN_ID2318_t* penID2318, TJA1145FD_CAN_ID1716_t* penID1716 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANIdentifier2(TJA1145FD_CAN_ID2318_t enID2318, TJA1145FD_CAN_ID1716_t enID1716 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANIdentifier3(TJA1145FD_CAN_ID2824_t* penID2824 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANIdentifier3(TJA1145FD_CAN_ID2824_t enID2824 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANMask0(TJA1145FD_CAN_M0700_t* penM0700 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANMask0(TJA1145FD_CAN_M0700_t enM0700 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANMask1(TJA1145FD_CAN_M1508_t* penM1508 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANMask1(TJA1145FD_CAN_M1508_t enM1508 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANMask2(TJA1145FD_CAN_M2318_t* penM2318, TJA1145FD_CAN_M1716_t* penM1716 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANMask2(TJA1145FD_CAN_M2318_t enM2318, TJA1145FD_CAN_M1716_t enM1716 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getCANMask3(TJA1145FD_CAN_M2824_t* penM2824 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANMask3(TJA1145FD_CAN_M2824_t enM2824 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getFrameControl(TJA1145FD_Identifier_Format_t* penIDE, TJA1145FD_Partial_Network_Data_Mask_t* penPNDM, TJA1145FD_CAN_Data_Length_t* penDLC );
NXP_UJA11XX_Error_Code_t TJA1145FD_setFrameControl(TJA1145FD_Identifier_Format_t enIDE, TJA1145FD_Partial_Network_Data_Mask_t enPNDM, TJA1145FD_CAN_Data_Length_t enDLC );

NXP_UJA11XX_Error_Code_t TJA1145FD_getWakeStatus(TJA1145FD_Wake_Pin_Status_t* penWPVS );

NXP_UJA11XX_Error_Code_t TJA1145FD_getWakePinEnable(TJA1145FD_Wake_Pin_Rising_Edge_Detect_t* penWPRE, TJA1145FD_Wake_Pin_Falling_Edge_Detect_t* penWPFE );
NXP_UJA11XX_Error_Code_t TJA1145FD_setWakePinEnable(TJA1145FD_Wake_Pin_Rising_Edge_Detect_t enWPRE, TJA1145FD_Wake_Pin_Falling_Edge_Detect_t enWPFE );

NXP_UJA11XX_Error_Code_t TJA1145FD_getGlobalEventStatus(TJA1145FD_Wake_Pin_Event_t* penWPE, TJA1145FD_Transceiver_Event_t* penTRXE, TJA1145FD_System_Event_t* penSYSE );

NXP_UJA11XX_Error_Code_t TJA1145FD_getSystemEventStatus(TJA1145FD_Power_On_t* penPO, TJA1145FD_Over_Temperature_Warning_t* penOTW, TJA1145FD_SPI_Failure_t* penSPIF );
NXP_UJA11XX_Error_Code_t TJA1145FD_setSystemEventStatus(TJA1145FD_Power_On_t enPO, TJA1145FD_Over_Temperature_Warning_t enOTW, TJA1145FD_SPI_Failure_t enSPIF );

NXP_UJA11XX_Error_Code_t TJA1145FD_getTransceiverEventStatus(TJA1145FD_Partial_Network_Frame_Detect_t* penPNFDE, TJA1145FD_CAN_Bus_Active_t* penCBS, TJA1145FD_CAN_Failure_t* penCF, TJA1145FD_CAN_WakeUp_t* penCW );
NXP_UJA11XX_Error_Code_t TJA1145FD_setTransceiverEventStatus(TJA1145FD_Partial_Network_Frame_Detect_t enPNFDE, TJA1145FD_CAN_Bus_Active_t enCBS, TJA1145FD_CAN_Failure_t enCF, TJA1145FD_CAN_WakeUp_t enCW );

NXP_UJA11XX_Error_Code_t TJA1145FD_getWakePinEvent(TJA1145FD_Rising_Wake_Pin_Event_t* penWPR, TJA1145FD_Falling_Wake_Pin_Event_t* penWPF );
NXP_UJA11XX_Error_Code_t TJA1145FD_setWakePinEvent(TJA1145FD_Rising_Wake_Pin_Event_t enWPR, TJA1145FD_Falling_Wake_Pin_Event_t enWPF );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask0(TJA1145FD_Data_Mask_0_Config_t* penDM0 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask0(TJA1145FD_Data_Mask_0_Config_t enDM0 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask1(TJA1145FD_Data_Mask_1_Config_t* penDM1 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask1(TJA1145FD_Data_Mask_1_Config_t enDM1 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask2(TJA1145FD_Data_Mask_2_Config_t* penDM2 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask2(TJA1145FD_Data_Mask_2_Config_t enDM2 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask3(TJA1145FD_Data_Mask_3_Config_t* penDM3 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask3(TJA1145FD_Data_Mask_3_Config_t enDM3 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask4(TJA1145FD_Data_Mask_4_Config_t* penDM4 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask4(TJA1145FD_Data_Mask_4_Config_t enDM4 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask5(TJA1145FD_Data_Mask_5_Config_t* penDM5 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask5(TJA1145FD_Data_Mask_5_Config_t enDM5 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask6(TJA1145FD_Data_Mask_6_Config_t* penDM6 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask6(TJA1145FD_Data_Mask_6_Config_t enDM6 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask7(TJA1145FD_Data_Mask_7_Config_t* penDM7 );
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask7(TJA1145FD_Data_Mask_7_Config_t enDM7 );

NXP_UJA11XX_Error_Code_t TJA1145FD_getIdentification(TJA1145FD_Device_ID_t* penIDS );


//--------------------------------------------------------------------------------
#endif

