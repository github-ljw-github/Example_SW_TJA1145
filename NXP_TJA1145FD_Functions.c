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

/** NXP TJA1145FD Example Code
*
* This is the TJA1145FD example driver to get access to all registers and logical values
*
* \author XML Parser V1.2
* \version V1.1
* \date 05/16/2013
*
* - The following registers are supported:
*   - <b>Mode Control Reg</b> - Address = 0x01, Access = READ/WRITE, This register controls the Sleep, Standby and Normal operation mode
*   - <b>Main Status</b> - Address = 0x03, Access = READ, This register can be accessed to monitor main status information
*   - <b>System Event Enable</b> - Address = 0x04, Access = READ/WRITE, This register is used to enable or disable the system event
*   - <b>Memory 0</b> - Address = 0x06, Access = READ/WRITE, This register is used to access the general purpose memory bits [0-7] of the user RAM
*   - <b>Memory 1</b> - Address = 0x07, Access = READ/WRITE, This register is used to access the general purpose memory bits [8-15] of the user RAM
*   - <b>Memory 2</b> - Address = 0x08, Access = READ/WRITE, This register is used to access the general purpose memory bits [16-23] of the user RAM
*   - <b>Memory 3</b> - Address = 0x09, Access = READ/WRITE, This register is used to access the general purpose memory bits [24-31] of the user RAM
*   - <b>Lock Control</b> - Address = 0x0A, Access = READ/WRITE, This register is used to protect registers against unintended modifications
*   - <b>CAN Control</b> - Address = 0x20, Access = READ/WRITE, This register is used to control the CAN bus
*   - <b>Transceiver Status</b> - Address = 0x22, Access = READ, This register is used to control the transceiver status
*   - <b>Transceiver Event Enable</b> - Address = 0x23, Access = READ/WRITE, This register is used to enable or disable the transceiver event
*   - <b>Data Rate</b> - Address = 0x26, Access = READ/WRITE/TRIGGER, This register is used to control the CAN bus data rate
*   - <b>CAN Identifier 0</b> - Address = 0x27, Access = READ/WRITE/TRIGGER, This register is used to access the CAN ID bits [0-7] of the extended frame format
*   - <b>CAN Identifier 1</b> - Address = 0x28, Access = READ/WRITE/TRIGGER, This register is used to access the CAN ID bits [8-15] of the extended frame format
*   - <b>CAN Identifier 2</b> - Address = 0x29, Access = READ/WRITE/TRIGGER, This register is used to access the CAN ID bits [16-23] of the extended and the bits [0-5] of the standard frame format
*   - <b>CAN Identifier 3</b> - Address = 0x2A, Access = READ/WRITE/TRIGGER, This register is used to access the CAN ID bits [24-28] of the extended and the bits [6-10] of the standard frame format
*   - <b>CAN Mask 0</b> - Address = 0x2B, Access = READ/WRITE/TRIGGER, This register is used to access the CAN mask bits [0-7] of the extended frame format
*   - <b>CAN Mask 1</b> - Address = 0x2C, Access = READ/WRITE/TRIGGER, This register is used to access the CAN mask bits [8-15] of the extended frame format
*   - <b>CAN Mask 2</b> - Address = 0x2D, Access = READ/WRITE/TRIGGER, This register is used to access the CAN mask bits [16-23] of the extended and the bits [0-5] of the standard frame format
*   - <b>CAN Mask 3</b> - Address = 0x2E, Access = READ/WRITE/TRIGGER, This register is used to access the CAN mask bits [24-28] of the extended frame format
*   - <b>Frame Control</b> - Address = 0x2F, Access = READ/WRITE/TRIGGER, This register is used to control the CAN frame
*   - <b>Wake Status</b> - Address = 0x4B, Access = READ, This register is used to control the status of the WakeUp pin
*   - <b>Wake Pin Enable</b> - Address = 0x4C, Access = READ/WRITE, This register is used to enable or disable the WakePin event
*   - <b>Global Event Status</b> - Address = 0x60, Access = READ, This register is used to check the global event status
*   - <b>System Event Status</b> - Address = 0x61, Access = READ/WRITE/INTERRUPT, This register is used to control the system event status
*   - <b>Transceiver Event Status</b> - Address = 0x63, Access = READ/WRITE/INTERRUPT, This register is used to control the transceiver event status
*   - <b>Wake Pin Event</b> - Address = 0x64, Access = READ/WRITE/INTERRUPT, This register is used to control the WakePin event status
*   - <b>Data Mask 0</b> - Address = 0x68, Access = READ/WRITE, This register is used to access the data mask 0 configuration
*   - <b>Data Mask 1</b> - Address = 0x69, Access = READ/WRITE, This register is used to access the data mask 1 configuration
*   - <b>Data Mask 2</b> - Address = 0x6A, Access = READ/WRITE, This register is used to access the data mask 2 configuration
*   - <b>Data Mask 3</b> - Address = 0x6B, Access = READ/WRITE, This register is used to access the data mask 3 configuration
*   - <b>Data Mask 4</b> - Address = 0x6C, Access = READ/WRITE, This register is used to access the data mask 4 configuration
*   - <b>Data Mask 5</b> - Address = 0x6D, Access = READ/WRITE, This register is used to access the data mask 5 configuration
*   - <b>Data Mask 6</b> - Address = 0x6E, Access = READ/WRITE, This register is used to access the data mask 6 configuration
*   - <b>Data Mask 7</b> - Address = 0x6F, Access = READ/WRITE, This register is used to access the data mask 7 configuration
*   - <b>Identification</b> - Address = 0x7E, Access = READ, This register is used to access the device identification code
*
* - The following functions are available to get register access:  (each function uses the return type [<b>NXP_UJA11XX_Error_Code_t</b>])
*   -  TJA1145FD_getModeControlReg(TJA1145FD_Mode_Control_t* penMC )
*   -  TJA1145FD_setModeControlReg(TJA1145FD_Mode_Control_t enMC )
*   -  TJA1145FD_getMainStatus(TJA1145FD_Forced_Sleep_Mode_Status_t* penFSMS, TJA1145FD_Over_Temperature_Warning_Status_t* penOTWS, TJA1145FD_Normal_Mode_Status_t* penNMS )
*   -  TJA1145FD_getSystemEventEnable(TJA1145FD_Over_Temperature_Warning_Enable_t* penOTWE, TJA1145FD_SPI_Failure_Detect_Enable_t* penSPIFE )
*   -  TJA1145FD_setSystemEventEnable(TJA1145FD_Over_Temperature_Warning_Enable_t enOTWE, TJA1145FD_SPI_Failure_Detect_Enable_t enSPIFE )
*   -  TJA1145FD_getMemory0(TJA1145FD_RAM_Memory_0700_t* penGPM0 )
*   -  TJA1145FD_setMemory0(TJA1145FD_RAM_Memory_0700_t enGPM0 )
*   -  TJA1145FD_getMemory1(TJA1145FD_RAM_Memory_0815_t* penGPM1 )
*   -  TJA1145FD_setMemory1(TJA1145FD_RAM_Memory_0815_t enGPM1 )
*   -  TJA1145FD_getMemory2(TJA1145FD_RAM_Memory_1623_t* penGPM2 )
*   -  TJA1145FD_setMemory2(TJA1145FD_RAM_Memory_1623_t enGPM2 )
*   -  TJA1145FD_getMemory3(TJA1145FD_RAM_Memory_2431_t* penGPM3 )
*   -  TJA1145FD_setMemory3(TJA1145FD_RAM_Memory_2431_t enGPM3 )
*   -  TJA1145FD_getLockControl(TJA1145FD_Lock_Control_6_t* penLK6C, TJA1145FD_Lock_Control_5_t* penLK5C, TJA1145FD_Lock_Control_4_t* penLK4C, TJA1145FD_Lock_Control_3_t* penLK3C, TJA1145FD_Lock_Control_2_t* penLK2C, TJA1145FD_Lock_Control_1_t* penLK1C, TJA1145FD_Lock_Control_0_t* penLK0C )
*   -  TJA1145FD_setLockControl(TJA1145FD_Lock_Control_6_t enLK6C, TJA1145FD_Lock_Control_5_t enLK5C, TJA1145FD_Lock_Control_4_t enLK4C, TJA1145FD_Lock_Control_3_t enLK3C, TJA1145FD_Lock_Control_2_t enLK2C, TJA1145FD_Lock_Control_1_t enLK1C, TJA1145FD_Lock_Control_0_t enLK0C )
*   -  TJA1145FD_getCANControl(TJA1145FD_CAN_FD_tolerance_t* penCFDC, TJA1145FD_Partial_Network_Config_t* penPNCOK, TJA1145FD_CAN_Selective_WakeUp_t* penCPNC, TJA1145FD_CAN_Mode_Selection_t* penCMC )
*   -  TJA1145FD_setCANControl(TJA1145FD_CAN_FD_tolerance_t enCFDC, TJA1145FD_Partial_Network_Config_t enPNCOK, TJA1145FD_CAN_Selective_WakeUp_t enCPNC, TJA1145FD_CAN_Mode_Selection_t enCMC )
*   -  TJA1145FD_getTransceiverStatus(TJA1145FD_CAN_Transmitter_Status_t* penCTS, TJA1145FD_Partial_Network_Error_t* penCPNERR, TJA1145FD_Partial_Network_Config_Error_t* penCPNS, TJA1145FD_Partial_Network_Osc_t* penCOSCS, TJA1145FD_CAN_Bus_Status_t* penCBSS, TJA1145FD_VCAN_Status_t* penVCS, TJA1145FD_Dominant_Timeout_Event_t* penCFS )
*   -  TJA1145FD_getTransceiverEventEnable(TJA1145FD_CAN_Bus_Silence_Detect_t* penCBSE, TJA1145FD_CAN_Failure_Detect_t* penCFE, TJA1145FD_CAN_WakeUp_Detect_t* penCWE )
*   -  TJA1145FD_setTransceiverEventEnable(TJA1145FD_CAN_Bus_Silence_Detect_t enCBSE, TJA1145FD_CAN_Failure_Detect_t enCFE, TJA1145FD_CAN_WakeUp_Detect_t enCWE )
*   -  TJA1145FD_getDataRate(TJA1145FD_CAN_Data_Rate_t* penCDR )
*   -  TJA1145FD_setDataRate(TJA1145FD_CAN_Data_Rate_t enCDR )
*   -  TJA1145FD_getCANIdentifier0(TJA1145FD_CAN_ID0700_t* penID0700 )
*   -  TJA1145FD_setCANIdentifier0(TJA1145FD_CAN_ID0700_t enID0700 )
*   -  TJA1145FD_getCANIdentifier1(TJA1145FD_CAN_ID1508_t* penID1508 )
*   -  TJA1145FD_setCANIdentifier1(TJA1145FD_CAN_ID1508_t enID1508 )
*   -  TJA1145FD_getCANIdentifier2(TJA1145FD_CAN_ID2318_t* penID2318, TJA1145FD_CAN_ID1716_t* penID1716 )
*   -  TJA1145FD_setCANIdentifier2(TJA1145FD_CAN_ID2318_t enID2318, TJA1145FD_CAN_ID1716_t enID1716 )
*   -  TJA1145FD_getCANIdentifier3(TJA1145FD_CAN_ID2824_t* penID2824 )
*   -  TJA1145FD_setCANIdentifier3(TJA1145FD_CAN_ID2824_t enID2824 )
*   -  TJA1145FD_getCANMask0(TJA1145FD_CAN_M0700_t* penM0700 )
*   -  TJA1145FD_setCANMask0(TJA1145FD_CAN_M0700_t enM0700 )
*   -  TJA1145FD_getCANMask1(TJA1145FD_CAN_M1508_t* penM1508 )
*   -  TJA1145FD_setCANMask1(TJA1145FD_CAN_M1508_t enM1508 )
*   -  TJA1145FD_getCANMask2(TJA1145FD_CAN_M2318_t* penM2318, TJA1145FD_CAN_M1716_t* penM1716 )
*   -  TJA1145FD_setCANMask2(TJA1145FD_CAN_M2318_t enM2318, TJA1145FD_CAN_M1716_t enM1716 )
*   -  TJA1145FD_getCANMask3(TJA1145FD_CAN_M2824_t* penM2824 )
*   -  TJA1145FD_setCANMask3(TJA1145FD_CAN_M2824_t enM2824 )
*   -  TJA1145FD_getFrameControl(TJA1145FD_Identifier_Format_t* penIDE, TJA1145FD_Partial_Network_Data_Mask_t* penPNDM, TJA1145FD_CAN_Data_Length_t* penDLC )
*   -  TJA1145FD_setFrameControl(TJA1145FD_Identifier_Format_t enIDE, TJA1145FD_Partial_Network_Data_Mask_t enPNDM, TJA1145FD_CAN_Data_Length_t enDLC )
*   -  TJA1145FD_getWakeStatus(TJA1145FD_Wake_Pin_Status_t* penWPVS )
*   -  TJA1145FD_getWakePinEnable(TJA1145FD_Wake_Pin_Rising_Edge_Detect_t* penWPRE, TJA1145FD_Wake_Pin_Falling_Edge_Detect_t* penWPFE )
*   -  TJA1145FD_setWakePinEnable(TJA1145FD_Wake_Pin_Rising_Edge_Detect_t enWPRE, TJA1145FD_Wake_Pin_Falling_Edge_Detect_t enWPFE )
*   -  TJA1145FD_getGlobalEventStatus(TJA1145FD_Wake_Pin_Event_t* penWPE, TJA1145FD_Transceiver_Event_t* penTRXE, TJA1145FD_System_Event_t* penSYSE )
*   -  TJA1145FD_getSystemEventStatus(TJA1145FD_Power_On_t* penPO, TJA1145FD_Over_Temperature_Warning_t* penOTW, TJA1145FD_SPI_Failure_t* penSPIF )
*   -  TJA1145FD_setSystemEventStatus(TJA1145FD_Power_On_t enPO, TJA1145FD_Over_Temperature_Warning_t enOTW, TJA1145FD_SPI_Failure_t enSPIF )
*   -  TJA1145FD_getTransceiverEventStatus(TJA1145FD_Partial_Network_Frame_Detect_t* penPNFDE, TJA1145FD_CAN_Bus_Active_t* penCBS, TJA1145FD_CAN_Failure_t* penCF, TJA1145FD_CAN_WakeUp_t* penCW )
*   -  TJA1145FD_setTransceiverEventStatus(TJA1145FD_Partial_Network_Frame_Detect_t enPNFDE, TJA1145FD_CAN_Bus_Active_t enCBS, TJA1145FD_CAN_Failure_t enCF, TJA1145FD_CAN_WakeUp_t enCW )
*   -  TJA1145FD_getWakePinEvent(TJA1145FD_Rising_Wake_Pin_Event_t* penWPR, TJA1145FD_Falling_Wake_Pin_Event_t* penWPF )
*   -  TJA1145FD_setWakePinEvent(TJA1145FD_Rising_Wake_Pin_Event_t enWPR, TJA1145FD_Falling_Wake_Pin_Event_t enWPF )
*   -  TJA1145FD_getDataMask0(TJA1145FD_Data_Mask_0_Config_t* penDM0 )
*   -  TJA1145FD_setDataMask0(TJA1145FD_Data_Mask_0_Config_t enDM0 )
*   -  TJA1145FD_getDataMask1(TJA1145FD_Data_Mask_1_Config_t* penDM1 )
*   -  TJA1145FD_setDataMask1(TJA1145FD_Data_Mask_1_Config_t enDM1 )
*   -  TJA1145FD_getDataMask2(TJA1145FD_Data_Mask_2_Config_t* penDM2 )
*   -  TJA1145FD_setDataMask2(TJA1145FD_Data_Mask_2_Config_t enDM2 )
*   -  TJA1145FD_getDataMask3(TJA1145FD_Data_Mask_3_Config_t* penDM3 )
*   -  TJA1145FD_setDataMask3(TJA1145FD_Data_Mask_3_Config_t enDM3 )
*   -  TJA1145FD_getDataMask4(TJA1145FD_Data_Mask_4_Config_t* penDM4 )
*   -  TJA1145FD_setDataMask4(TJA1145FD_Data_Mask_4_Config_t enDM4 )
*   -  TJA1145FD_getDataMask5(TJA1145FD_Data_Mask_5_Config_t* penDM5 )
*   -  TJA1145FD_setDataMask5(TJA1145FD_Data_Mask_5_Config_t enDM5 )
*   -  TJA1145FD_getDataMask6(TJA1145FD_Data_Mask_6_Config_t* penDM6 )
*   -  TJA1145FD_setDataMask6(TJA1145FD_Data_Mask_6_Config_t enDM6 )
*   -  TJA1145FD_getDataMask7(TJA1145FD_Data_Mask_7_Config_t* penDM7 )
*   -  TJA1145FD_setDataMask7(TJA1145FD_Data_Mask_7_Config_t enDM7 )
*   -  TJA1145FD_getIdentification(TJA1145FD_Device_ID_t* penIDS )
*/
//******************************************************************
// function header include
#include "NXP_TJA1145FD_Functions.h"

//******************************************************************

//Extern declaration of SPI communiaction function 
extern NXP_UJA11XX_Error_Code_t SPI_Send(Byte CanTrcvIndex, Byte* data,NXP_UJA11XX_SPI_Msg_Length_t length ,Byte mask, NXP_UJA11XX_Access_t access);

/// This function is used to set data of the Mode Control Reg register
/** The function supports the following parameter:
* \param enMC  possible values:  Sleep Mode, Standby Mode, Normal Mode
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setModeControlReg(Byte CanTrcvIndex, TJA1145FD_Mode_Control_t enMC )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_MODE_CONTROL_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enMC << TJA1145FD_MC_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MODE_CONTROL_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Mode Control Reg register
/** The function supports the following parameter:
* \param *penMC  possible values:  Sleep Mode, Standby Mode, Normal Mode
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getModeControlReg(Byte CanTrcvIndex, TJA1145FD_Mode_Control_t* penMC )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_MODE_CONTROL_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MODE_CONTROL_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_MC_MASK;					// mask desired bits
	*penMC = (TJA1145FD_Mode_Control_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the Main Status register
/** The function supports the following parameter:
* \param *penFSMS  possible values:  an undervoltage on VCC and or VIO forced a transition to Sleep mode, transition to Sleep mode was not triggered by an undervoltage on VCC and or VIO
* \param *penOTWS  possible values:  Temp Above, Temp Below
* \param *penNMS  possible values:  Normal Mode not entered, Normal Mode entered
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getMainStatus(Byte CanTrcvIndex, TJA1145FD_Forced_Sleep_Mode_Status_t* penFSMS, TJA1145FD_Over_Temperature_Warning_Status_t* penOTWS, TJA1145FD_Normal_Mode_Status_t* penNMS )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_MAIN_STATUS_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MAIN_STATUS_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_FSMS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_FSMS_SHIFT;				// shift to right aligned position
	*penFSMS = (TJA1145FD_Forced_Sleep_Mode_Status_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_OTWS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_OTWS_SHIFT;				// shift to right aligned position
	*penOTWS = (TJA1145FD_Over_Temperature_Warning_Status_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_NMS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_NMS_SHIFT;				// shift to right aligned position
	*penNMS = (TJA1145FD_Normal_Mode_Status_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the System Event Enable register
/** The function supports the following parameter:
* \param enOTWE  possible values:  Over temperature warning enabled, Over temperature warning disabled
* \param enSPIFE  possible values:  SPI Failure detection enabled, SPI Failure detection disabled
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setSystemEventEnable(Byte CanTrcvIndex, TJA1145FD_Over_Temperature_Warning_Enable_t enOTWE, TJA1145FD_SPI_Failure_Detect_Enable_t enSPIFE )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_SYSTEM_EVENT_ENABLE_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enOTWE << TJA1145FD_OTWE_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enSPIFE << TJA1145FD_SPIFE_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_SYSTEM_EVENT_ENABLE_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the System Event Enable register
/** The function supports the following parameter:
* \param *penOTWE  possible values:  Over temperature warning enabled, Over temperature warning disabled
* \param *penSPIFE  possible values:  SPI Failure detection enabled, SPI Failure detection disabled
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getSystemEventEnable(Byte CanTrcvIndex, TJA1145FD_Over_Temperature_Warning_Enable_t* penOTWE, TJA1145FD_SPI_Failure_Detect_Enable_t* penSPIFE )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_SYSTEM_EVENT_ENABLE_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_SYSTEM_EVENT_ENABLE_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_OTWE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_OTWE_SHIFT;				// shift to right aligned position
	*penOTWE = (TJA1145FD_Over_Temperature_Warning_Enable_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_SPIFE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_SPIFE_SHIFT;				// shift to right aligned position
	*penSPIFE = (TJA1145FD_SPI_Failure_Detect_Enable_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Memory 0 register
/** The function supports the following parameter:
* \param enGPM0  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setMemory0(Byte CanTrcvIndex, TJA1145FD_RAM_Memory_0700_t enGPM0 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_MEMORY_0_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enGPM0 << TJA1145FD_GPM0_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MEMORY_0_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Memory 0 register
/** The function supports the following parameter:
* \param *penGPM0  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getMemory0(Byte CanTrcvIndex, TJA1145FD_RAM_Memory_0700_t* penGPM0 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_MEMORY_0_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MEMORY_0_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penGPM0 = (TJA1145FD_RAM_Memory_0700_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Memory 1 register
/** The function supports the following parameter:
* \param enGPM1  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setMemory1(Byte CanTrcvIndex, TJA1145FD_RAM_Memory_0815_t enGPM1 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_MEMORY_1_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enGPM1 << TJA1145FD_GPM1_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MEMORY_1_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Memory 1 register
/** The function supports the following parameter:
* \param *penGPM1  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getMemory1(Byte CanTrcvIndex, TJA1145FD_RAM_Memory_0815_t* penGPM1 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_MEMORY_1_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MEMORY_1_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penGPM1 = (TJA1145FD_RAM_Memory_0815_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Memory 2 register
/** The function supports the following parameter:
* \param enGPM2  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setMemory2(Byte CanTrcvIndex, TJA1145FD_RAM_Memory_1623_t enGPM2 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_MEMORY_2_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enGPM2 << TJA1145FD_GPM2_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MEMORY_2_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Memory 2 register
/** The function supports the following parameter:
* \param *penGPM2  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getMemory2(Byte CanTrcvIndex, TJA1145FD_RAM_Memory_1623_t* penGPM2 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_MEMORY_2_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MEMORY_2_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penGPM2 = (TJA1145FD_RAM_Memory_1623_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Memory 3 register
/** The function supports the following parameter:
* \param enGPM3  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setMemory3(Byte CanTrcvIndex, TJA1145FD_RAM_Memory_2431_t enGPM3 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_MEMORY_3_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enGPM3 << TJA1145FD_GPM3_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MEMORY_3_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Memory 3 register
/** The function supports the following parameter:
* \param *penGPM3  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getMemory3(Byte CanTrcvIndex, TJA1145FD_RAM_Memory_2431_t* penGPM3 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_MEMORY_3_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_MEMORY_3_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penGPM3 = (TJA1145FD_RAM_Memory_2431_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Lock Control register
/** The function supports the following parameter:
* \param enLK6C  possible values:  SPI write access disabled 0x68 to 0x6F, SPI write access enabled 0x68 to 0x6F
* \param enLK5C  possible values:  SPI write access disabled 0x50 to 0x5F, SPI write access enabled 0x50 to 0x5F
* \param enLK4C  possible values:  SPI write access disabled 0x40 to 0x4F, SPI write access enabled 0x40 to 0x4F
* \param enLK3C  possible values:  SPI write access disabled 0x30 to 0x3F, SPI write access enabled 0x30 to 0x3F
* \param enLK2C  possible values:  SPI write access disabled 0x20 to 0x2F, SPI write access enabled 0x20 to 0x2F
* \param enLK1C  possible values:  SPI write access disabled 0x10 to 0x1F, SPI write access enabled 0x10 to 0x1F
* \param enLK0C  possible values:  SPI write access disabled 0x06 to 0x09, SPI write access enabled 0x06 to 0x09
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setLockControl(Byte CanTrcvIndex, TJA1145FD_Lock_Control_6_t enLK6C, TJA1145FD_Lock_Control_5_t enLK5C, TJA1145FD_Lock_Control_4_t enLK4C, TJA1145FD_Lock_Control_3_t enLK3C, TJA1145FD_Lock_Control_2_t enLK2C, TJA1145FD_Lock_Control_1_t enLK1C, TJA1145FD_Lock_Control_0_t enLK0C )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_LOCK_CONTROL_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enLK6C << TJA1145FD_LK6C_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enLK5C << TJA1145FD_LK5C_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enLK4C << TJA1145FD_LK4C_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enLK3C << TJA1145FD_LK3C_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enLK2C << TJA1145FD_LK2C_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enLK1C << TJA1145FD_LK1C_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enLK0C << TJA1145FD_LK0C_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_LOCK_CONTROL_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Lock Control register
/** The function supports the following parameter:
* \param *penLK6C  possible values:  SPI write access disabled 0x68 to 0x6F, SPI write access enabled 0x68 to 0x6F
* \param *penLK5C  possible values:  SPI write access disabled 0x50 to 0x5F, SPI write access enabled 0x50 to 0x5F
* \param *penLK4C  possible values:  SPI write access disabled 0x40 to 0x4F, SPI write access enabled 0x40 to 0x4F
* \param *penLK3C  possible values:  SPI write access disabled 0x30 to 0x3F, SPI write access enabled 0x30 to 0x3F
* \param *penLK2C  possible values:  SPI write access disabled 0x20 to 0x2F, SPI write access enabled 0x20 to 0x2F
* \param *penLK1C  possible values:  SPI write access disabled 0x10 to 0x1F, SPI write access enabled 0x10 to 0x1F
* \param *penLK0C  possible values:  SPI write access disabled 0x06 to 0x09, SPI write access enabled 0x06 to 0x09
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getLockControl(Byte CanTrcvIndex, TJA1145FD_Lock_Control_6_t* penLK6C, TJA1145FD_Lock_Control_5_t* penLK5C, TJA1145FD_Lock_Control_4_t* penLK4C, TJA1145FD_Lock_Control_3_t* penLK3C, TJA1145FD_Lock_Control_2_t* penLK2C, TJA1145FD_Lock_Control_1_t* penLK1C, TJA1145FD_Lock_Control_0_t* penLK0C )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_LOCK_CONTROL_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_LOCK_CONTROL_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_LK6C_MASK;					// mask desired bits
	cResult >>= TJA1145FD_LK6C_SHIFT;				// shift to right aligned position
	*penLK6C = (TJA1145FD_Lock_Control_6_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_LK5C_MASK;					// mask desired bits
	cResult >>= TJA1145FD_LK5C_SHIFT;				// shift to right aligned position
	*penLK5C = (TJA1145FD_Lock_Control_5_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_LK4C_MASK;					// mask desired bits
	cResult >>= TJA1145FD_LK4C_SHIFT;				// shift to right aligned position
	*penLK4C = (TJA1145FD_Lock_Control_4_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_LK3C_MASK;					// mask desired bits
	cResult >>= TJA1145FD_LK3C_SHIFT;				// shift to right aligned position
	*penLK3C = (TJA1145FD_Lock_Control_3_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_LK2C_MASK;					// mask desired bits
	cResult >>= TJA1145FD_LK2C_SHIFT;				// shift to right aligned position
	*penLK2C = (TJA1145FD_Lock_Control_2_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_LK1C_MASK;					// mask desired bits
	cResult >>= TJA1145FD_LK1C_SHIFT;				// shift to right aligned position
	*penLK1C = (TJA1145FD_Lock_Control_1_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_LK0C_MASK;					// mask desired bits
	*penLK0C = (TJA1145FD_Lock_Control_0_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Control register
/** The function supports the following parameter:
* \param enCFDC  possible values:  CAN FD tolerance enabled, CAN FD tolerance disabled
* \param enPNCOK  possible values:  Partial Network configuration successful, Partial Network configuration invalid
* \param enCPNC  possible values:  CAN selective WakeUp enable, CAN selective WakeUp disable
* \param enCMC  possible values:  Offline mode, Active with VCC undervoltage detection active, Active with VCC undervoltage detection off, Listen only mode
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANControl(Byte CanTrcvIndex, TJA1145FD_CAN_FD_tolerance_t enCFDC, TJA1145FD_Partial_Network_Config_t enPNCOK, TJA1145FD_CAN_Selective_WakeUp_t enCPNC, TJA1145FD_CAN_Mode_Selection_t enCMC )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_CONTROL_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enCFDC << TJA1145FD_CFDC_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enPNCOK << TJA1145FD_PNCOK_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enCPNC << TJA1145FD_CPNC_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enCMC << TJA1145FD_CMC_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_CONTROL_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Control register
/** The function supports the following parameter:
* \param *penCFDC  possible values:  CAN FD tolerance enabled, CAN FD tolerance disabled
* \param *penPNCOK  possible values:  Partial Network configuration successful, Partial Network configuration invalid
* \param *penCPNC  possible values:  CAN selective WakeUp enable, CAN selective WakeUp disable
* \param *penCMC  possible values:  Offline mode, Active with VCC undervoltage detection active, Active with VCC undervoltage detection off, Listen only mode
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANControl(Byte CanTrcvIndex, TJA1145FD_CAN_FD_tolerance_t* penCFDC, TJA1145FD_Partial_Network_Config_t* penPNCOK, TJA1145FD_CAN_Selective_WakeUp_t* penCPNC, TJA1145FD_CAN_Mode_Selection_t* penCMC )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_CONTROL_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_CONTROL_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CFDC_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CFDC_SHIFT;				// shift to right aligned position
	*penCFDC = (TJA1145FD_CAN_FD_tolerance_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_PNCOK_MASK;					// mask desired bits
	cResult >>= TJA1145FD_PNCOK_SHIFT;				// shift to right aligned position
	*penPNCOK = (TJA1145FD_Partial_Network_Config_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CPNC_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CPNC_SHIFT;				// shift to right aligned position
	*penCPNC = (TJA1145FD_CAN_Selective_WakeUp_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CMC_MASK;					// mask desired bits
	*penCMC = (TJA1145FD_CAN_Mode_Selection_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the Transceiver Status register
/** The function supports the following parameter:
* \param *penCTS  possible values:  CAN Transmitter ready to transmit data, CAN Transmitter disabled
* \param *penCPNERR  possible values:  Partial Network error detected, No Partial Network error
* \param *penCPNS  possible values:  Partial Network configuration OK, Partial Network configuration error
* \param *penCOSCS  possible values:  Oscillator running on target freq, Oscillator not running on target freq
* \param *penCBSS  possible values:  CAN Bus inactive, CAN Bus active
* \param *penVCS  possible values:  output voltage on V1 is below the 90 threshold, output voltage on V1 is above the 90 threshold
* \param *penCFS  possible values:  Timeout Event disabled CAN Transmitter, No TXD timeout event
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getTransceiverStatus(Byte CanTrcvIndex, TJA1145FD_CAN_Transmitter_Status_t* penCTS, TJA1145FD_Partial_Network_Error_t* penCPNERR, TJA1145FD_Partial_Network_Config_Error_t* penCPNS, TJA1145FD_Partial_Network_Osc_t* penCOSCS, TJA1145FD_CAN_Bus_Status_t* penCBSS, TJA1145FD_VCAN_Status_t* penVCS, TJA1145FD_Dominant_Timeout_Event_t* penCFS )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_TRANSCEIVER_STATUS_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_TRANSCEIVER_STATUS_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CTS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CTS_SHIFT;				// shift to right aligned position
	*penCTS = (TJA1145FD_CAN_Transmitter_Status_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CPNERR_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CPNERR_SHIFT;				// shift to right aligned position
	*penCPNERR = (TJA1145FD_Partial_Network_Error_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CPNS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CPNS_SHIFT;				// shift to right aligned position
	*penCPNS = (TJA1145FD_Partial_Network_Config_Error_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_COSCS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_COSCS_SHIFT;				// shift to right aligned position
	*penCOSCS = (TJA1145FD_Partial_Network_Osc_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CBSS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CBSS_SHIFT;				// shift to right aligned position
	*penCBSS = (TJA1145FD_CAN_Bus_Status_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_VCS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_VCS_SHIFT;				// shift to right aligned position
	*penVCS = (TJA1145FD_VCAN_Status_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CFS_MASK;					// mask desired bits
	*penCFS = (TJA1145FD_Dominant_Timeout_Event_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Transceiver Event Enable register
/** The function supports the following parameter:
* \param enCBSE  possible values:  CAN Bus silence detection enabled, CAN Bus silence detection disabled
* \param enCFE  possible values:  CAN failure detection enable, CAN failure detection disable
* \param enCWE  possible values:  CAN WakeUp detection enable, CAN WakeUp detection disable
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setTransceiverEventEnable(Byte CanTrcvIndex, TJA1145FD_CAN_Bus_Silence_Detect_t enCBSE, TJA1145FD_CAN_Failure_Detect_t enCFE, TJA1145FD_CAN_WakeUp_Detect_t enCWE )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_TRANSCEIVER_EVENT_ENABLE_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enCBSE << TJA1145FD_CBSE_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enCFE << TJA1145FD_CFE_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enCWE << TJA1145FD_CWE_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_TRANSCEIVER_EVENT_ENABLE_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Transceiver Event Enable register
/** The function supports the following parameter:
* \param *penCBSE  possible values:  CAN Bus silence detection enabled, CAN Bus silence detection disabled
* \param *penCFE  possible values:  CAN failure detection enable, CAN failure detection disable
* \param *penCWE  possible values:  CAN WakeUp detection enable, CAN WakeUp detection disable
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getTransceiverEventEnable(Byte CanTrcvIndex, TJA1145FD_CAN_Bus_Silence_Detect_t* penCBSE, TJA1145FD_CAN_Failure_Detect_t* penCFE, TJA1145FD_CAN_WakeUp_Detect_t* penCWE )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_TRANSCEIVER_EVENT_ENABLE_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_TRANSCEIVER_EVENT_ENABLE_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CBSE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CBSE_SHIFT;				// shift to right aligned position
	*penCBSE = (TJA1145FD_CAN_Bus_Silence_Detect_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CFE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CFE_SHIFT;				// shift to right aligned position
	*penCFE = (TJA1145FD_CAN_Failure_Detect_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CWE_MASK;					// mask desired bits
	*penCWE = (TJA1145FD_CAN_WakeUp_Detect_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Rate register
/** The function supports the following parameter:
* \param enCDR  possible values:  50 kbit per s, 100 kbit per s, 125 kbit per s, 250 kbit per s, 500 kbit per s, 1000 kbit per s
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataRate(Byte CanTrcvIndex, TJA1145FD_CAN_Data_Rate_t enCDR )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_RATE_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enCDR << TJA1145FD_CDR_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_RATE_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Rate register
/** The function supports the following parameter:
* \param *penCDR  possible values:  50 kbit per s, 100 kbit per s, 125 kbit per s, 250 kbit per s, 500 kbit per s, 1000 kbit per s
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataRate(Byte CanTrcvIndex, TJA1145FD_CAN_Data_Rate_t* penCDR )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_RATE_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_RATE_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CDR_MASK;					// mask desired bits
	*penCDR = (TJA1145FD_CAN_Data_Rate_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Identifier 0 register
/** The function supports the following parameter:
* \param enID0700  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANIdentifier0(Byte CanTrcvIndex, TJA1145FD_CAN_ID0700_t enID0700 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_IDENTIFIER_0_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enID0700 << TJA1145FD_ID0700_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_IDENTIFIER_0_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Identifier 0 register
/** The function supports the following parameter:
* \param *penID0700  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANIdentifier0(Byte CanTrcvIndex, TJA1145FD_CAN_ID0700_t* penID0700 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_IDENTIFIER_0_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_IDENTIFIER_0_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penID0700 = (TJA1145FD_CAN_ID0700_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Identifier 1 register
/** The function supports the following parameter:
* \param enID1508  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANIdentifier1(Byte CanTrcvIndex, TJA1145FD_CAN_ID1508_t enID1508 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_IDENTIFIER_1_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enID1508 << TJA1145FD_ID1508_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_IDENTIFIER_1_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Identifier 1 register
/** The function supports the following parameter:
* \param *penID1508  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANIdentifier1(Byte CanTrcvIndex, TJA1145FD_CAN_ID1508_t* penID1508 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_IDENTIFIER_1_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_IDENTIFIER_1_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penID1508 = (TJA1145FD_CAN_ID1508_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Identifier 2 register
/** The function supports the following parameter:
* \param enID2318  possible values: [0 - 255]
* \param enID1716  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANIdentifier2(Byte CanTrcvIndex, TJA1145FD_CAN_ID2318_t enID2318, TJA1145FD_CAN_ID1716_t enID1716 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_IDENTIFIER_2_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enID2318 << TJA1145FD_ID2318_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enID1716 << TJA1145FD_ID1716_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_IDENTIFIER_2_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Identifier 2 register
/** The function supports the following parameter:
* \param *penID2318  possible values: [0 - 255]
* \param *penID1716  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANIdentifier2(Byte CanTrcvIndex, TJA1145FD_CAN_ID2318_t* penID2318, TJA1145FD_CAN_ID1716_t* penID1716 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_IDENTIFIER_2_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_IDENTIFIER_2_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_ID2318_MASK;					// mask desired bits
	cResult >>= TJA1145FD_ID2318_SHIFT;				// shift to right aligned position
	*penID2318 = (TJA1145FD_CAN_ID2318_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_ID1716_MASK;					// mask desired bits
	*penID1716 = (TJA1145FD_CAN_ID1716_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Identifier 3 register
/** The function supports the following parameter:
* \param enID2824  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANIdentifier3(Byte CanTrcvIndex, TJA1145FD_CAN_ID2824_t enID2824 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_IDENTIFIER_3_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enID2824 << TJA1145FD_ID2824_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_IDENTIFIER_3_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Identifier 3 register
/** The function supports the following parameter:
* \param *penID2824  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANIdentifier3(Byte CanTrcvIndex, TJA1145FD_CAN_ID2824_t* penID2824 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_IDENTIFIER_3_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_IDENTIFIER_3_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_ID2824_MASK;					// mask desired bits
	*penID2824 = (TJA1145FD_CAN_ID2824_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Mask 0 register
/** The function supports the following parameter:
* \param enM0700  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANMask0(Byte CanTrcvIndex, TJA1145FD_CAN_M0700_t enM0700 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_MASK_0_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enM0700 << TJA1145FD_M0700_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_MASK_0_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Mask 0 register
/** The function supports the following parameter:
* \param *penM0700  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANMask0(Byte CanTrcvIndex, TJA1145FD_CAN_M0700_t* penM0700 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_MASK_0_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_MASK_0_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penM0700 = (TJA1145FD_CAN_M0700_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Mask 1 register
/** The function supports the following parameter:
* \param enM1508  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANMask1(Byte CanTrcvIndex, TJA1145FD_CAN_M1508_t enM1508 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_MASK_1_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enM1508 << TJA1145FD_M1508_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_MASK_1_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Mask 1 register
/** The function supports the following parameter:
* \param *penM1508  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANMask1(Byte CanTrcvIndex, TJA1145FD_CAN_M1508_t* penM1508 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_MASK_1_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_MASK_1_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penM1508 = (TJA1145FD_CAN_M1508_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Mask 2 register
/** The function supports the following parameter:
* \param enM2318  possible values: [0 - 255]
* \param enM1716  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANMask2(Byte CanTrcvIndex, TJA1145FD_CAN_M2318_t enM2318, TJA1145FD_CAN_M1716_t enM1716 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_MASK_2_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enM2318 << TJA1145FD_M2318_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enM1716 << TJA1145FD_M1716_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_MASK_2_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Mask 2 register
/** The function supports the following parameter:
* \param *penM2318  possible values: [0 - 255]
* \param *penM1716  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANMask2(Byte CanTrcvIndex, TJA1145FD_CAN_M2318_t* penM2318, TJA1145FD_CAN_M1716_t* penM1716 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_MASK_2_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_MASK_2_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_M2318_MASK;					// mask desired bits
	cResult >>= TJA1145FD_M2318_SHIFT;				// shift to right aligned position
	*penM2318 = (TJA1145FD_CAN_M2318_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_M1716_MASK;					// mask desired bits
	*penM1716 = (TJA1145FD_CAN_M1716_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the CAN Mask 3 register
/** The function supports the following parameter:
* \param enM2824  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setCANMask3(Byte CanTrcvIndex, TJA1145FD_CAN_M2824_t enM2824 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_CAN_MASK_3_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enM2824 << TJA1145FD_M2824_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_MASK_3_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the CAN Mask 3 register
/** The function supports the following parameter:
* \param *penM2824  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getCANMask3(Byte CanTrcvIndex, TJA1145FD_CAN_M2824_t* penM2824 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_CAN_MASK_3_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_CAN_MASK_3_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_M2824_MASK;					// mask desired bits
	*penM2824 = (TJA1145FD_CAN_M2824_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Frame Control register
/** The function supports the following parameter:
* \param enIDE  possible values:  Extended Frame Format 29 Bit, Standard Frame Format 11 Bit
* \param enPNDM  possible values:  data length code and data field are evaluated at wake up, data length code and data field are do not care for wake up
* \param enDLC  possible values:  Expected CAN frame bytes 0, Expected CAN frame bytes 1, Expected CAN frame bytes 2, Expected CAN frame bytes 3, Expected CAN frame bytes 4, Expected CAN frame bytes 5, Expected CAN frame bytes 6, Expected CAN frame bytes 7, Expected CAN frame bytes 8
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setFrameControl(Byte CanTrcvIndex, TJA1145FD_Identifier_Format_t enIDE, TJA1145FD_Partial_Network_Data_Mask_t enPNDM, TJA1145FD_CAN_Data_Length_t enDLC )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_FRAME_CONTROL_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enIDE << TJA1145FD_IDE_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enPNDM << TJA1145FD_PNDM_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enDLC << TJA1145FD_DLC_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_FRAME_CONTROL_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Frame Control register
/** The function supports the following parameter:
* \param *penIDE  possible values:  Extended Frame Format 29 Bit, Standard Frame Format 11 Bit
* \param *penPNDM  possible values:  data length code and data field are evaluated at wake up, data length code and data field are do not care for wake up
* \param *penDLC  possible values:  Expected CAN frame bytes 0, Expected CAN frame bytes 1, Expected CAN frame bytes 2, Expected CAN frame bytes 3, Expected CAN frame bytes 4, Expected CAN frame bytes 5, Expected CAN frame bytes 6, Expected CAN frame bytes 7, Expected CAN frame bytes 8
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getFrameControl(Byte CanTrcvIndex, TJA1145FD_Identifier_Format_t* penIDE, TJA1145FD_Partial_Network_Data_Mask_t* penPNDM, TJA1145FD_CAN_Data_Length_t* penDLC )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_FRAME_CONTROL_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_FRAME_CONTROL_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_IDE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_IDE_SHIFT;				// shift to right aligned position
	*penIDE = (TJA1145FD_Identifier_Format_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_PNDM_MASK;					// mask desired bits
	cResult >>= TJA1145FD_PNDM_SHIFT;				// shift to right aligned position
	*penPNDM = (TJA1145FD_Partial_Network_Data_Mask_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_DLC_MASK;					// mask desired bits
	*penDLC = (TJA1145FD_CAN_Data_Length_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the Wake Status register
/** The function supports the following parameter:
* \param *penWPVS  possible values:  Voltage above switching threshold, Voltage below switching threshold
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getWakeStatus(Byte CanTrcvIndex, TJA1145FD_Wake_Pin_Status_t* penWPVS )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_WAKE_STATUS_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_WAKE_STATUS_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_WPVS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_WPVS_SHIFT;				// shift to right aligned position
	*penWPVS = (TJA1145FD_Wake_Pin_Status_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Wake Pin Enable register
/** The function supports the following parameter:
* \param enWPRE  possible values:  WakePin rising edge detect enable, WakePin rising edge detect disable
* \param enWPFE  possible values:  WakePin falling edge detect enable, WakePin falling edge detect disable
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setWakePinEnable(Byte CanTrcvIndex, TJA1145FD_Wake_Pin_Rising_Edge_Detect_t enWPRE, TJA1145FD_Wake_Pin_Falling_Edge_Detect_t enWPFE )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_WAKE_PIN_ENABLE_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enWPRE << TJA1145FD_WPRE_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enWPFE << TJA1145FD_WPFE_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_WAKE_PIN_ENABLE_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Wake Pin Enable register
/** The function supports the following parameter:
* \param *penWPRE  possible values:  WakePin rising edge detect enable, WakePin rising edge detect disable
* \param *penWPFE  possible values:  WakePin falling edge detect enable, WakePin falling edge detect disable
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getWakePinEnable(Byte CanTrcvIndex, TJA1145FD_Wake_Pin_Rising_Edge_Detect_t* penWPRE, TJA1145FD_Wake_Pin_Falling_Edge_Detect_t* penWPFE )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_WAKE_PIN_ENABLE_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_WAKE_PIN_ENABLE_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_WPRE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_WPRE_SHIFT;				// shift to right aligned position
	*penWPRE = (TJA1145FD_Wake_Pin_Rising_Edge_Detect_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_WPFE_MASK;					// mask desired bits
	*penWPFE = (TJA1145FD_Wake_Pin_Falling_Edge_Detect_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the Global Event Status register
/** The function supports the following parameter:
* \param *penWPE  possible values:  Wake Pin event pending, No Wake Pin event
* \param *penTRXE  possible values:  Transceiver event pending, No Transceiver event
* \param *penSYSE  possible values:  System event pending, No System event
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getGlobalEventStatus(Byte CanTrcvIndex, TJA1145FD_Wake_Pin_Event_t* penWPE, TJA1145FD_Transceiver_Event_t* penTRXE, TJA1145FD_System_Event_t* penSYSE )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_GLOBAL_EVENT_STATUS_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_GLOBAL_EVENT_STATUS_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_WPE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_WPE_SHIFT;				// shift to right aligned position
	*penWPE = (TJA1145FD_Wake_Pin_Event_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_TRXE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_TRXE_SHIFT;				// shift to right aligned position
	*penTRXE = (TJA1145FD_Transceiver_Event_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_SYSE_MASK;					// mask desired bits
	*penSYSE = (TJA1145FD_System_Event_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the System Event Status register
/** The function supports the following parameter:
* \param enPO  possible values:  Off Mode left, No Power On
* \param enOTW  possible values:  Temperature exceeds warning level, No over temperature
* \param enSPIF  possible values:  SPI Failure detected, No SPI Failure
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setSystemEventStatus(Byte CanTrcvIndex, TJA1145FD_Power_On_t enPO, TJA1145FD_Over_Temperature_Warning_t enOTW, TJA1145FD_SPI_Failure_t enSPIF )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_SYSTEM_EVENT_STATUS_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enPO << TJA1145FD_PO_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enOTW << TJA1145FD_OTW_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enSPIF << TJA1145FD_SPIF_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_SYSTEM_EVENT_STATUS_REG_MASK, NXP_UJA11XX_INTERRUPT);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the System Event Status register
/** The function supports the following parameter:
* \param *penPO  possible values:  Off Mode left, No Power On
* \param *penOTW  possible values:  Temperature exceeds warning level, No over temperature
* \param *penSPIF  possible values:  SPI Failure detected, No SPI Failure
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getSystemEventStatus(Byte CanTrcvIndex, TJA1145FD_Power_On_t* penPO, TJA1145FD_Over_Temperature_Warning_t* penOTW, TJA1145FD_SPI_Failure_t* penSPIF )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_SYSTEM_EVENT_STATUS_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_SYSTEM_EVENT_STATUS_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_PO_MASK;					// mask desired bits
	cResult >>= TJA1145FD_PO_SHIFT;				// shift to right aligned position
	*penPO = (TJA1145FD_Power_On_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_OTW_MASK;					// mask desired bits
	cResult >>= TJA1145FD_OTW_SHIFT;				// shift to right aligned position
	*penOTW = (TJA1145FD_Over_Temperature_Warning_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_SPIF_MASK;					// mask desired bits
	cResult >>= TJA1145FD_SPIF_SHIFT;				// shift to right aligned position
	*penSPIF = (TJA1145FD_SPI_Failure_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Transceiver Event Status register
/** The function supports the following parameter:
* \param enPNFDE  possible values:  Partial Network frame error detected, No Partial Network frame error
* \param enCBS  possible values:  No CAN Bus activity, CAN Bus active
* \param enCF  possible values:  CAN Failure detected, No CAN Failure
* \param enCW  possible values:  CAN WakeUp event, No CAN WakeUp
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setTransceiverEventStatus(Byte CanTrcvIndex, TJA1145FD_Partial_Network_Frame_Detect_t enPNFDE, TJA1145FD_CAN_Bus_Active_t enCBS, TJA1145FD_CAN_Failure_t enCF, TJA1145FD_CAN_WakeUp_t enCW )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_TRANSCEIVER_EVENT_STATUS_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enPNFDE << TJA1145FD_PNFDE_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enCBS << TJA1145FD_CBS_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enCF << TJA1145FD_CF_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enCW << TJA1145FD_CW_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_TRANSCEIVER_EVENT_STATUS_REG_MASK, NXP_UJA11XX_INTERRUPT);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Transceiver Event Status register
/** The function supports the following parameter:
* \param *penPNFDE  possible values:  Partial Network frame error detected, No Partial Network frame error
* \param *penCBS  possible values:  No CAN Bus activity, CAN Bus active
* \param *penCF  possible values:  CAN Failure detected, No CAN Failure
* \param *penCW  possible values:  CAN WakeUp event, No CAN WakeUp
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getTransceiverEventStatus(Byte CanTrcvIndex, TJA1145FD_Partial_Network_Frame_Detect_t* penPNFDE, TJA1145FD_CAN_Bus_Active_t* penCBS, TJA1145FD_CAN_Failure_t* penCF, TJA1145FD_CAN_WakeUp_t* penCW )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_TRANSCEIVER_EVENT_STATUS_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_TRANSCEIVER_EVENT_STATUS_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_PNFDE_MASK;					// mask desired bits
	cResult >>= TJA1145FD_PNFDE_SHIFT;				// shift to right aligned position
	*penPNFDE = (TJA1145FD_Partial_Network_Frame_Detect_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CBS_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CBS_SHIFT;				// shift to right aligned position
	*penCBS = (TJA1145FD_CAN_Bus_Active_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CF_MASK;					// mask desired bits
	cResult >>= TJA1145FD_CF_SHIFT;				// shift to right aligned position
	*penCF = (TJA1145FD_CAN_Failure_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_CW_MASK;					// mask desired bits
	*penCW = (TJA1145FD_CAN_WakeUp_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Wake Pin Event register
/** The function supports the following parameter:
* \param enWPR  possible values:  WakePin rising edge detected, No WakePin rising edge
* \param enWPF  possible values:  WakePin falling edge detected, No WakePin falling edge
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setWakePinEvent(Byte CanTrcvIndex, TJA1145FD_Rising_Wake_Pin_Event_t enWPR, TJA1145FD_Falling_Wake_Pin_Event_t enWPF )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_WAKE_PIN_EVENT_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enWPR << TJA1145FD_WPR_SHIFT);	// shift valid value to correct bit position and add to data

	cData[1] |= (Byte)(enWPF << TJA1145FD_WPF_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_WAKE_PIN_EVENT_REG_MASK, NXP_UJA11XX_INTERRUPT);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Wake Pin Event register
/** The function supports the following parameter:
* \param *penWPR  possible values:  WakePin rising edge detected, No WakePin rising edge
* \param *penWPF  possible values:  WakePin falling edge detected, No WakePin falling edge
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getWakePinEvent(Byte CanTrcvIndex, TJA1145FD_Rising_Wake_Pin_Event_t* penWPR, TJA1145FD_Falling_Wake_Pin_Event_t* penWPF )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_WAKE_PIN_EVENT_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_WAKE_PIN_EVENT_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_WPR_MASK;					// mask desired bits
	cResult >>= TJA1145FD_WPR_SHIFT;				// shift to right aligned position
	*penWPR = (TJA1145FD_Rising_Wake_Pin_Event_t)( cResult );	// deliver result

	// split received byte into bit groups
	cResult = cData[1];
	cResult &= TJA1145FD_WPF_MASK;					// mask desired bits
	*penWPF = (TJA1145FD_Falling_Wake_Pin_Event_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Mask 0 register
/** The function supports the following parameter:
* \param enDM0  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask0(Byte CanTrcvIndex, TJA1145FD_Data_Mask_0_Config_t enDM0 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_MASK_0_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enDM0 << TJA1145FD_DM0_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_0_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Mask 0 register
/** The function supports the following parameter:
* \param *penDM0  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask0(Byte CanTrcvIndex, TJA1145FD_Data_Mask_0_Config_t* penDM0 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_MASK_0_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_0_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penDM0 = (TJA1145FD_Data_Mask_0_Config_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Mask 1 register
/** The function supports the following parameter:
* \param enDM1  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask1(Byte CanTrcvIndex, TJA1145FD_Data_Mask_1_Config_t enDM1 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_MASK_1_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enDM1 << TJA1145FD_DM1_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_1_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Mask 1 register
/** The function supports the following parameter:
* \param *penDM1  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask1(Byte CanTrcvIndex, TJA1145FD_Data_Mask_1_Config_t* penDM1 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_MASK_1_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_1_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penDM1 = (TJA1145FD_Data_Mask_1_Config_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Mask 2 register
/** The function supports the following parameter:
* \param enDM2  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask2(Byte CanTrcvIndex, TJA1145FD_Data_Mask_2_Config_t enDM2 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_MASK_2_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enDM2 << TJA1145FD_DM2_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_2_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Mask 2 register
/** The function supports the following parameter:
* \param *penDM2  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask2(Byte CanTrcvIndex, TJA1145FD_Data_Mask_2_Config_t* penDM2 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_MASK_2_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_2_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penDM2 = (TJA1145FD_Data_Mask_2_Config_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Mask 3 register
/** The function supports the following parameter:
* \param enDM3  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask3(Byte CanTrcvIndex, TJA1145FD_Data_Mask_3_Config_t enDM3 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_MASK_3_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enDM3 << TJA1145FD_DM3_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_3_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Mask 3 register
/** The function supports the following parameter:
* \param *penDM3  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask3(Byte CanTrcvIndex, TJA1145FD_Data_Mask_3_Config_t* penDM3 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_MASK_3_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_3_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penDM3 = (TJA1145FD_Data_Mask_3_Config_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Mask 4 register
/** The function supports the following parameter:
* \param enDM4  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask4(Byte CanTrcvIndex, TJA1145FD_Data_Mask_4_Config_t enDM4 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_MASK_4_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enDM4 << TJA1145FD_DM4_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_4_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Mask 4 register
/** The function supports the following parameter:
* \param *penDM4  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask4(Byte CanTrcvIndex, TJA1145FD_Data_Mask_4_Config_t* penDM4 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_MASK_4_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_4_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penDM4 = (TJA1145FD_Data_Mask_4_Config_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Mask 5 register
/** The function supports the following parameter:
* \param enDM5  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask5(Byte CanTrcvIndex, TJA1145FD_Data_Mask_5_Config_t enDM5 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_MASK_5_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enDM5 << TJA1145FD_DM5_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_5_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Mask 5 register
/** The function supports the following parameter:
* \param *penDM5  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask5(Byte CanTrcvIndex, TJA1145FD_Data_Mask_5_Config_t* penDM5 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_MASK_5_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_5_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penDM5 = (TJA1145FD_Data_Mask_5_Config_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Mask 6 register
/** The function supports the following parameter:
* \param enDM6  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask6(Byte CanTrcvIndex, TJA1145FD_Data_Mask_6_Config_t enDM6 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_MASK_6_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enDM6 << TJA1145FD_DM6_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_6_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Mask 6 register
/** The function supports the following parameter:
* \param *penDM6  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask6(Byte CanTrcvIndex, TJA1145FD_Data_Mask_6_Config_t* penDM6 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_MASK_6_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_6_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penDM6 = (TJA1145FD_Data_Mask_6_Config_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to set data of the Data Mask 7 register
/** The function supports the following parameter:
* \param enDM7  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR_WRITE_FAIL = 0, TJA1145FD_ERROR_READ_FAIL = 1, TJA1145FD_ERROR_SPI_HW_FAIL = 2, TJA1145FD_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_setDataMask7(Byte CanTrcvIndex, TJA1145FD_Data_Mask_7_Config_t enDM7 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;

	// create address to write data to
	cData[0] = (TJA1145FD_DATA_MASK_7_REG << 1) | NXP_UJA11XX_WRITE;

	cData[1] = 0x00;		// start value

	cData[1] |= (Byte)(enDM7 << TJA1145FD_DM7_SHIFT);	// shift valid value to correct bit position and add to data

	// write data via SPI
	enStatus = SPI_Send (CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_7_REG_MASK, NXP_UJA11XX_WRITE);

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//************************************

/// This function is used to get data from the Data Mask 7 register
/** The function supports the following parameter:
* \param *penDM7  possible values: [0 - 255]
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getDataMask7(Byte CanTrcvIndex, TJA1145FD_Data_Mask_7_Config_t* penDM7 )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_DATA_MASK_7_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_DATA_MASK_7_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penDM7 = (TJA1145FD_Data_Mask_7_Config_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************

/// This function is used to get data from the Identification register
/** The function supports the following parameter:
* \param *penIDS  possible values:  Device ID TJA1145FD
* \return <b>NXP_UJA11XX_Error_Code_t</b>  possible values: TJA1145FD_ERROR = 0, TJA1145FD_SUCCESS = 1
*/
NXP_UJA11XX_Error_Code_t TJA1145FD_getIdentification(Byte CanTrcvIndex, TJA1145FD_Device_ID_t* penIDS )
{
	Byte			cData[2];
	NXP_UJA11XX_Error_Code_t	enStatus;
	Byte			cResult;

	// create address to read data from
	cData[0] = (TJA1145FD_IDENTIFICATION_REG << 1) | NXP_UJA11XX_READ;

	// read data via SPI
	enStatus = SPI_Send(CanTrcvIndex, cData, NXP_UJA11XX_SPI_MSG_LENGTH_16, TJA1145FD_IDENTIFICATION_REG_MASK, NXP_UJA11XX_READ);

	// split received byte into bit groups
	cResult = cData[1];
	*penIDS = (TJA1145FD_Device_ID_t)( cResult );	// deliver result

	return ((NXP_UJA11XX_Error_Code_t) enStatus);
}
//******************************************************************


