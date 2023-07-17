///////////////////////////////////////////////////////////////////////////////////////////////////
// � NXP B.V. 2013. All rights reserved.
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

#ifndef __TJA1145FD_configurations_h
#define __TJA1145FD_configurations_h

#include "NXP_TJA1145FD_Functions.h"
#include "NXP_TJA1145FD_Sim.h"

/********** TJA1145 Normal Mode configuration ***********/

// System Event Enable in Normal Mode
TJA1145FD_System_Event_Enable_Reg_t TJA1145FD_SYS_EVENT_EN_NORMAL = {TJA1145FD_OTWE_OVER_TEMPERATURE_WARNING_ENABLED, TJA1145FD_SPIFE_SPI_FAILURE_DETECTION_ENABLED};   
// Transceiver Event Enable in Normal Mode
TJA1145FD_Transceiver_Event_Enable_Reg_t TJA1145FD_TRX_EVENT_EN_NORMAL = {TJA1145FD_CBSE_CAN_BUS_SILENCE_DETECTION_DISABLED, TJA1145FD_CFE_CAN_FAILURE_DETECTION_ENABLE, TJA1145FD_CWE_CAN_WAKEUP_DETECTION_DISABLE};
// WAKE Pin Enable in Normal Mode
TJA1145FD_Wake_Pin_Enable_Reg_t TJA1145FD_WAKE_PIN_EN_NORMAL = {TJA1145FD_WPRE_WAKEPIN_RISING_EDGE_DETECT_DISABLE, TJA1145FD_WPFE_WAKEPIN_FALLING_EDGE_DETECT_DISABLE};


/********** TJA1145 Standby configuration ***********/

// System Event Enabled in Standby Mode
TJA1145FD_System_Event_Enable_Reg_t TJA1145FD_SYS_EVENT_EN_STANDBY = {TJA1145FD_OTWE_OVER_TEMPERATURE_WARNING_ENABLED, TJA1145FD_SPIFE_SPI_FAILURE_DETECTION_ENABLED};   
// Transceiver Event Enable in Standby Mode
TJA1145FD_Transceiver_Event_Enable_Reg_t TJA1145FD_TRX_EVENT_EN_STANDBY = {TJA1145FD_CBSE_CAN_BUS_SILENCE_DETECTION_ENABLED, TJA1145FD_CFE_CAN_FAILURE_DETECTION_DISABLE, TJA1145FD_CWE_CAN_WAKEUP_DETECTION_ENABLE};
// WAKE Pin Enable in Standby Mode
TJA1145FD_Wake_Pin_Enable_Reg_t TJA1145FD_WAKE_PIN_EN_STANDBY = {TJA1145FD_WPRE_WAKEPIN_RISING_EDGE_DETECT_DISABLE, TJA1145FD_WPFE_WAKEPIN_FALLING_EDGE_DETECT_ENABLE};
// CAN PN Control in Standby Mode
TJA1145FD_CAN_Selective_WakeUp_t TJA1145FD_CPNC_STANDBY = TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_ENABLE;                                                             

/********** TJA1145 Sleep configuration ***********/

// System Event Enabled in Sleep Mode
TJA1145FD_System_Event_Enable_Reg_t TJA1145FD_SYS_EVENT_EN_SLEEP = {TJA1145FD_OTWE_OVER_TEMPERATURE_WARNING_ENABLED, TJA1145FD_SPIFE_SPI_FAILURE_DETECTION_ENABLED};
// Transceiver Event Enable in Sleep Mode
TJA1145FD_Transceiver_Event_Enable_Reg_t TJA1145FD_TRX_EVENT_EN_SLEEP = {TJA1145FD_CBSE_CAN_BUS_SILENCE_DETECTION_DISABLED, TJA1145FD_CFE_CAN_FAILURE_DETECTION_DISABLE, TJA1145FD_CWE_CAN_WAKEUP_DETECTION_ENABLE};
// WAKE Pin Enable in Sleep Mode
TJA1145FD_Wake_Pin_Enable_Reg_t TJA1145FD_WAKE_PIN_EN_SLEEP = {TJA1145FD_WPRE_WAKEPIN_RISING_EDGE_DETECT_ENABLE, TJA1145FD_WPFE_WAKEPIN_FALLING_EDGE_DETECT_DISABLE};
// CAN PN Control in Sleep Mode
TJA1145FD_CAN_Selective_WakeUp_t TJA1145FD_CPNC_SLEEP = TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_DISABLE;  

/********** TJA1145 init configuration ***********/

// System Event Enable initialisation value
TJA1145FD_System_Event_Enable_Reg_t TJA1145FD_SYS_EVENT_EN_INIT = {TJA1145FD_OTWE_OVER_TEMPERATURE_WARNING_ENABLED, TJA1145FD_SPIFE_SPI_FAILURE_DETECTION_ENABLED};
// GPM initialisation value
TJA1145FD_RAM_Memory_0700_t TJA1145FD_GPM0_INIT = 0x0;
TJA1145FD_RAM_Memory_0815_t TJA1145FD_GPM1_INIT = 0x0;
TJA1145FD_RAM_Memory_1623_t TJA1145FD_GPM2_INIT = 0x0;
TJA1145FD_RAM_Memory_1623_t TJA1145FD_GPM3_INIT = 0x0; 

// CAN Control initialisation value
TJA1145FD_CAN_Control_Reg_t TJA1145FD_CAN_CONTROL_INIT = {
	TJA1145FD_CFDC_CAN_FD_TOLERANCE_DISABLED, 
	TJA1145FD_PNCOK_PARTIAL_NETWORK_CONFIGURATION_INVALID, 
	TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_DISABLE, 
	TJA1145FD_CMC_ACTIVE_WITH_VCC_UNDERVOLTAGE_DETECTION_OFF
};        
// Transceiver Event Enable initialisation value
TJA1145FD_Transceiver_Event_Enable_Reg_t TJA1145FD_TRX_EVENT_EN_INIT = {TJA1145FD_CBSE_CAN_BUS_SILENCE_DETECTION_DISABLED, TJA1145FD_CFE_CAN_FAILURE_DETECTION_DISABLE, TJA1145FD_CWE_CAN_WAKEUP_DETECTION_DISABLE};

// Partial Networking Configuration
TJA1145FD_CAN_Data_Rate_t TJA1145FD_CAN_DATA_RATE = TJA1145FD_CDR_500_KBIT_PER_S;	//26
Word UJA116FDVX_CAN_ID = 0x660;
Word TJA1145FD_CAN_ID_MASK = 0x400;
TJA1145FD_Frame_Control_Reg_t TJA1145FD_CAN_FRAME_CONTROL = {TJA1145FD_IDE_STANDARD_FRAME_FORMAT_11_BIT, TJA1145FD_PNDM_DATA_LENGTH_CODE_AND_DATA_FIELD_ARE_EVALUATED_AT_WAKE_UP, TJA1145FD_DLC_EXPECTED_CAN_FRAME_BYTES_8};	//2F
TJA1145FD_Data_Mask_0_Config_t TJA1145FD_CAN_DATA_MASK0 = 0x0;	//68  // 1st byte on the bus; if DLC = 1, last byte on the bus 
TJA1145FD_Data_Mask_1_Config_t TJA1145FD_CAN_DATA_MASK1 = 0x0;	//69  // 2nd byte on the bus; if DLC = 2, last byte on the bus 
TJA1145FD_Data_Mask_2_Config_t TJA1145FD_CAN_DATA_MASK2 = 0x0;	//6A	// 3rd byte on the bus; if DLC = 3, last byte on the bus
TJA1145FD_Data_Mask_3_Config_t TJA1145FD_CAN_DATA_MASK3 = 0x0;	//6B	// 4th byte on the bus; if DLC = 4, last byte on the bus
TJA1145FD_Data_Mask_4_Config_t TJA1145FD_CAN_DATA_MASK4 = 0x1;	//6C	// 5th byte on the bus; if DLC = 5, last byte on the bus
TJA1145FD_Data_Mask_5_Config_t TJA1145FD_CAN_DATA_MASK5 = 0x0;	//6D	// 6th byte on the bus; if DLC = 6, last byte on the bus
TJA1145FD_Data_Mask_6_Config_t TJA1145FD_CAN_DATA_MASK6 = 0x0;	//6E	// 7th byte on the bus; if DLC = 7, last byte on the bus
TJA1145FD_Data_Mask_7_Config_t TJA1145FD_CAN_DATA_MASK7 = 0x1;	//6F	// 8th byte on the bus; if DLC = 8, last byte on the bus

// WAKE Pin Enable initialisation value
TJA1145FD_Wake_Pin_Enable_Reg_t TJA1145FD_WAKE_PIN_INIT = {TJA1145FD_WPRE_WAKEPIN_RISING_EDGE_DETECT_DISABLE, TJA1145FD_WPFE_WAKEPIN_FALLING_EDGE_DETECT_DISABLE};


#endif