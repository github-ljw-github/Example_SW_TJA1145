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

#include "TJA1145FD_Application_Specific_Functions.h"
#include "NXP_UJA11XX_defines.h"   
#include "NXP_TJA1145FD_Functions.h"
#include "NXP_TJA1145FD_Sim.h"
#include "TJA1145FD_Configuration.h"
#include "uC_Specific_Functions.h"    

extern volatile bool PendingEvent;
extern volatile bool CheckTrcvStatus;
extern PendingTask_t ApplTask[MAXTASKNO];
extern volatile int ApplTaskPt_write;
extern volatile int ApplTaskPt_read;
extern enum FailureEntries FailureMemory[MAXERRENTR];
extern volatile int FailMemPt_write;
extern Device_t DeviceType;
extern volatile CanTrcv_TrcvWakeupReasonType WuReason;
extern int OverflowCnt;
extern bool StartupReady;

/// Main Task
/** This function is entered with every timer tick and starts different processes depending on
* timer tick count and pending events:
* - starts the event handler
* - polls the CAN transceiver status,if requested
* - starts the uc port supervision
* - starts polling the WAKE pin
*
* \author   jh
* \version  1.0
* \date     2013/06/05
*/
void SchedulerOnTimerOverflow (){     
	Byte data = 0;
	int i = 0; // to be deleted

	OverflowCnt++; 

	switch (OverflowCnt) {      
	case 1: // Event Status polling
		AddTaskToScheduler(EVENT_HANDLING); 
		break;

	case 2: // Check TRCV status, if CAN failure has occured before
		if (CheckTrcvStatus == TRUE){
			CheckTrcvStatus = FALSE;
			AddTaskToScheduler(POLL_TRCV_STATUS);
		}
		break;

	case 3: // poll MCU pin status for request of mode change		  
		AddTaskToScheduler(PORT_SUPERVISION); 
		break; 

	case 4: // poll TJA1145 Wake Pin status		  
		AddTaskToScheduler(POLL_WAKE);    
		break; 

	default:
		OverflowCnt = 0; 		   
		break;
	}	     	
}


/// Read device type
/** This function reads back the device type of the SBC/Transceiver. 
* 
* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>Device_t</b> possible Values: NXP_TJA1145 = 1, NXP_TJA1145FD = 2, NXP_UJA1164 = 3, NXP_UJA1167 = 4, NXP_UJA1167VX = 5,
*                           NXP_UJA1168 = 6, NXP_UJA1168FD = 7, NXP_UJA1168FDVX = 8, NXP_UJA1168VX = 9, NXP_UNKNOWN = 0,
*/
Device_t GetDeviceType(){
	Device_t ret;
	TJA1145FD_Device_ID_t ids;            	

	// read Identification Register
	(void) TJA1145FD_getIdentification(&ids);

	// filter for IDS values  
	switch (ids){

	  case (0x70):
		  ret = NXP_TJA1145;
		  break;

	  case (0x74):
		  ret = NXP_TJA1145FD;
		  break;

	  case (0x80):
		  ret = NXP_UJA1164;
		  break;

	  case (0xD8):
		  ret = NXP_UJA1167;
		  break;

	  case (0xC8):
		  ret = NXP_UJA1167VX;
		  break;

	  case (0xF8):
		  ret = NXP_UJA1168;
		  break;

	  case (0xFC):
		  ret = NXP_UJA1168FD;
		  break;

	  case (0xEC):
		  ret = NXP_UJA1168FDVX;
		  break;

	  case (0xE8):
		  ret = NXP_UJA1168VX;
		  break;

	  default:           	  
		  ret = NXP_UNKNOWN;
		  break;	  
	}   	   
	return ret;
}

/// Initialize application
/**	This function initializes the application specific variables.
*
* \author	jh
* \version	1.0
* \date		2013/06/05
*/
void InitApplication(void){
	int i;

	// Init global variables
	InitScheduler();
	FailMemPt_write = 0;
	for(i = 0; i < MAXERRENTR; i++ ){
		FailureMemory[i] = EMPTY;
	}
	DeviceType = 0;
	PendingEvent = FALSE;
	OverflowCnt = 0;
	CheckTrcvStatus = FALSE;
	StartupReady = FALSE;
	WuReason = CANTRCV_WU_RESET;
}


/// Normal startup code of the application
/** This function performs the following actions which take place after every system reset:
* - Init microcontroller
* - Initialize the application (variables etc.)
* - Get Device Type
* - Check, if flashing is requested. If not:
*	-- Event Handling
*	-- Transition to Normal Operation Mode
*
* \author	jh
* \version	1.0
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/  
StdReturn_t StartupOperation(void){
	StdReturn_t ret = E_OK;
	Byte result;          		

	// Initialize MCU (CAN PE, UART etc.)
	(void) InitMicrocontroller(); 

	// Initialize general application variables
	(void) InitApplication(); 

	// Get Device ID
	DeviceType =	GetDeviceType();

	if (DeviceType == NXP_TJA1145FD){           	  

		// Check, if flash reprogramming is requested
		result = FlashProgramming();

		if (result == 0) {              
			// No flash reprogramming is requested

			// Check FSMS setting
			if (CheckFsmStatus() == E_NOT_OK){
				ret = E_NOT_OK;
			}

			// Event Handling
			if (EventHandling() == E_NOT_OK){
				ret = E_NOT_OK;
			}

			// Change to Normal Operation
			if (ChangeToNormalOperation() == E_NOT_OK){
				ret = E_NOT_OK;
			}
		}  else {
			(void) EnterFlashOperation();
		}     

		if (ret == E_OK){
			StartupReady = TRUE;  
		}
	} else {
		ret = E_NOT_OK;
	}

	return ret;		
}


/// TJA1145 initialization
/** This function initializes the TJA1145. Hence, all configuration registers are written with their
*	initialization values.
*
* Initialize following registers: 
* - System Event Enable
* - GPM initialization
* - CAN Control
* - Partial Networking Configuration (Data Rate, Identifier, Mask, Frame Control, Data Mask) 
* - Transceiver Event Enable
* - Wake Pin Event Enable  
* - General Purpose Memories
* - Lock Control
* 
* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t InitTJA1145() {
	StdReturn_t ret = E_OK;
	NXP_UJA11XX_Error_Code_t result = NXP_UJA11XX_SUCCESS;

	// Unlock the TJA1145 registers
	(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_ENABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_ENABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_ENABLED_0X06_TO_0X09);

	// Primary Control Registers
	(void) TJA1145FD_setSystemEventEnable(TJA1145FD_SYS_EVENT_EN_INIT.TJA1145FD_OTWE, TJA1145FD_SYS_EVENT_EN_INIT.TJA1145FD_SPIFE);
	(void) TJA1145FD_setMemory0(TJA1145FD_GPM0_INIT);
	(void) TJA1145FD_setMemory1(TJA1145FD_GPM1_INIT);
	(void) TJA1145FD_setMemory2(TJA1145FD_GPM2_INIT);
	(void) TJA1145FD_setMemory3(TJA1145FD_GPM3_INIT); 

	// Transceiver Control and PN Register Group	
	(void) TJA1145FD_setCANControl(TJA1145FD_CAN_CONTROL_INIT.TJA1145FD_CFDC, TJA1145FD_CAN_CONTROL_INIT.TJA1145FD_PNCOK, TJA1145FD_CAN_CONTROL_INIT.TJA1145FD_CPNC, TJA1145FD_CAN_CONTROL_INIT.TJA1145FD_CMC);
	(void) ConfigurePartialNetworking();

	(void) TJA1145FD_setTransceiverEventEnable(TJA1145FD_TRX_EVENT_EN_INIT.TJA1145FD_CBSE, TJA1145FD_TRX_EVENT_EN_INIT.TJA1145FD_CFE, TJA1145FD_TRX_EVENT_EN_INIT.TJA1145FD_CWE);

	// Wake Pin Control Registers
	(void) TJA1145FD_setWakePinEvent(TJA1145FD_WAKE_PIN_INIT.TJA1145FD_WPRE, TJA1145FD_WAKE_PIN_INIT.TJA1145FD_WPFE);       

	// Lock access to General Purpose Memories and Transceiver registers
	(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_DISABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);

	return ret;
}


/// Check FSMS setting
/** This function checks the status of the FSMS bit. In case TJA1145 has entered Sleep Mode due to a V1 or VIO
* undervoltage, CWE, WPFE, WPRE are reconfigured for Standby Mode, as the TJA1145 is currently in Standby Mode. 
* The CPNC is kept 0, as TJA1145 Sleep Mode has unintentionally been entered. In this example application the 
* selective wake-up behavior can only be enabled, if Low Power Operation is entered from Normal Operation.
* 
* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t CheckFsmStatus() {
	StdReturn_t ret = E_OK;
	TJA1145FD_Main_Status_Reg_t mainStatusReg;
	TJA1145FD_Transceiver_Event_Enable_Reg_t trcvEvEn = TJA1145FD_TRX_EVENT_EN_STANDBY;
	TJA1145FD_Wake_Pin_Enable_Reg_t wakeEvEn = TJA1145FD_WAKE_PIN_EN_STANDBY;

	if (TJA1145FD_getMainStatus(&mainStatusReg.TJA1145FD_FSMS, &mainStatusReg.TJA1145FD_OTWS, &mainStatusReg.TJA1145FD_NMS) != NXP_UJA11XX_SUCCESS) {
		ret = E_NOT_OK;
	}

	// If Sleep was entered due to V1 or VIO undervoltage, CWE, WPFE, WPRE have been enabled and CPNC was set to 0 
	if (mainStatusReg.TJA1145FD_FSMS == TJA1145FD_FSMS_AN_UNDERVOLTAGE_ON_VCC_AND_OR_VIO_FORCED_A_TRANSITION_TO_SLEEP_MODE){
		// Re-init bits according to Standby configuration
		// CPNC is kept 0 --> is changed by entering Standby/Sleep Operation Mode out of Normal Operation in this application 
		if (TJA1145FD_setWakePinEnable(wakeEvEn.TJA1145FD_WPRE, wakeEvEn.TJA1145FD_WPFE) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK;
		} 
		(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_ENABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);
		if (TJA1145FD_setTransceiverEventEnable(trcvEvEn.TJA1145FD_CBSE, trcvEvEn.TJA1145FD_CFE, trcvEvEn.TJA1145FD_CWE) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK;
		}  		
		(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_DISABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);  
	} 	
	return ret;
}


/// Preparation and transition to Standby Operation Mode
/**	This function manages the change of the Application to Standby Operation Mode (TJA1145 in Standby Mode, MCU in Stop Mode). 
* - Check if a regular interrupt (wake-up) would be enabled in Standby Mode (See file \link TJA1145FD_Configuration.h \endlink)
* - CAN transmission is stopped
* - Enable wake up source (Events to be captured in Standby Mode)
* - Set CPNC bit (disable/enable selective wake-up function according to configuration, See file \link TJA1145FD_Configuration.h \endlink)
* - Check if no interrupt is pending
* - If selective wake-up function is ENABLED in Standby Mode:
*	-- The WUF flag is cleared and transceiver is ready to wake up on next WUF
*	-- CAN PE is stopped
*	-- TJA1145 enters Standby Mode
*	-- CAN PE is put in Sleep Mode (wakeable)
*	-- Wake flag status of TJA1145 is checked and pending wakes are handled to avoid a deadlock
* - If selective wake-up function is DISABLED in Standby Mode:
*	-- CAN communication is stopped
*	-- CAN PE is stopped
*	-- CAN PE is put in Sleep Mode (wakeable)
*	-- TJA1145 enters Standby Mode
* If this transition is successful, the CPU is stopped (disable microcontroller oscillator or switch to sub clock). 
* If this transition is not successful, e.g. due to a a last minute wake-up the abort of low power transition is managed. 
*	This means, polling of the Event Status Register and entering Normal Operation Mode are scheduled for next main task.	
*
* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t ChangeToStandbyOperation(){
	StdReturn_t ret = E_OK;
	TJA1145FD_System_Event_Enable_Reg_t sysEvEn = TJA1145FD_SYS_EVENT_EN_STANDBY; 
	TJA1145FD_Transceiver_Event_Enable_Reg_t trcvEvEn = TJA1145FD_TRX_EVENT_EN_STANDBY;
	TJA1145FD_Wake_Pin_Enable_Reg_t wakeEvEn = TJA1145FD_WAKE_PIN_EN_STANDBY;
	TJA1145FD_Global_Event_Status_Reg_t pendingEvent;
	TJA1145FD_Mode_Control_t mc_reg; 

	// Read Mode Control Register
	(void) TJA1145FD_getModeControlReg(&mc_reg); 

	// If TJA1145 is not in Sleep Mode
	if(mc_reg != TJA1145FD_MC_STANDBY_MODE) {

		// Check interrupt configuration in Standby Mode
		// If no regular interrupt is enabled in Standby Mode, change to Standby Mode is aborted
		if ((trcvEvEn.TJA1145FD_CWE == TJA1145FD_CWE_CAN_WAKEUP_DETECTION_DISABLE) && 
			(wakeEvEn.TJA1145FD_WPFE == TJA1145FD_WPFE_WAKEPIN_FALLING_EDGE_DETECT_DISABLE) &&
			(wakeEvEn.TJA1145FD_WPRE == TJA1145FD_WPRE_WAKEPIN_RISING_EDGE_DETECT_DISABLE)) {

				ret = E_NOT_OK;      

		} else {  

			// Stop CAN transmission
			StopCAN_TX();

			// Configure to be captured events in Standby Mode
			if(TJA1145FD_setSystemEventEnable(sysEvEn.TJA1145FD_OTWE, sysEvEn.TJA1145FD_SPIFE) != NXP_UJA11XX_SUCCESS){		
				ret = E_NOT_OK;
			} 
			if (TJA1145FD_setWakePinEnable(wakeEvEn.TJA1145FD_WPRE, wakeEvEn.TJA1145FD_WPFE) != NXP_UJA11XX_SUCCESS){
				ret = E_NOT_OK;
			} 
			(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_ENABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);
			if (TJA1145FD_setTransceiverEventEnable(trcvEvEn.TJA1145FD_CBSE, trcvEvEn.TJA1145FD_CFE, trcvEvEn.TJA1145FD_CWE) != NXP_UJA11XX_SUCCESS){
				ret = E_NOT_OK;
			}  		
			if (TJA1145_SetPNActivationState((CanTrcv_PNActivationType) TJA1145FD_CPNC_STANDBY) != E_OK){
				ret = E_NOT_OK;
			}
			(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_DISABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);


			// If no interrupt is pending, enter TJA1145 Standby Mode
			(void) TJA1145FD_getGlobalEventStatus(&pendingEvent.TJA1145FD_WPE, &pendingEvent.TJA1145FD_TRXE, &pendingEvent.TJA1145FD_SYSE);
			if((pendingEvent.TJA1145FD_WPE == TJA1145FD_WPE_NO_WAKE_PIN_EVENT) &&
				(pendingEvent.TJA1145FD_TRXE == TJA1145FD_TRXE_NO_TRANSCEIVER_EVENT) &&
				(pendingEvent.TJA1145FD_SYSE == TJA1145FD_SYSE_NO_SYSTEM_EVENT)){                             

					// If PN has been activated successfully, follow defined shutdown flow for shutdown of CAN 
					// transceiver and CAN controller (source: Autosar R3.2 and higher)
					if ((ret == E_OK) && (TJA1145FD_CPNC_STANDBY == TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_ENABLE)){        
						// dedicated request to clear the WUF flag
						if (TJA1145_ClearTrcvWufFlag() == E_NOT_OK){
							ret = E_NOT_OK;
						}	
						// Disable CAN PE; wake-up disabled
						(void) CANStopMode();
						// Enter TJA1145 Standby Mode
						if (TJA1145_SetOpMode(CANTRCV_TRCVMODE_STANDBY) == E_NOT_OK){
							ret = E_NOT_OK;
						}	
						// Disable CAN PE; wake-up enabled
						(void) CANSleepMode();	
						// Check if WUF has occured meanwhile; If yes, wake up ECU again
						if (TJA1145_CheckWakeFlag() == E_NOT_OK){
							ret = E_NOT_OK;
						}
					}    	  
					// If partial networking is not activated in TJA1145 
					else if ((ret == E_OK) && (TJA1145FD_CPNC_STANDBY == TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_DISABLE)) {
						// Disable CAN PE, activate wake-up
						(void) CANStopMode();
						(void) CANSleepMode();	
						//  Enter TJA1145 Standby Mode
						if (TJA1145_SetOpMode(CANTRCV_TRCVMODE_STANDBY) == E_NOT_OK){
							ret = E_NOT_OK;
						}
					}

					// if CAN shutdown and entering Standby Mode was successful
					if (ret == E_OK){ 
						(void) ClearNormalModeLed();   

						// Check if RXD is high
						if (RXDC_GetValue() == 1){             
							// Stop CPU
							EnterMcuStopMode(); 
						} else {

							// Enter Normal Operation Mode is scheduled
							(void) AddTaskToScheduler(CHANGE_TO_NORMAL);
							PendingEvent = TRUE;
							ret = E_NOT_OK;   
						}
					} else { 

						// Enter Normal Operation Mode is scheduled
						(void) AddTaskToScheduler(CHANGE_TO_NORMAL);
						PendingEvent = TRUE;   	    		
					}   
			} else {
				// Enter Normal Operation Mode is scheduled
				(void) AddTaskToScheduler(CHANGE_TO_NORMAL);
				PendingEvent = TRUE;  
			}
		}
	}

	return ret;
}


/// Preparation and transition to Sleep Operation Mode
/**	This function manages all things that are necessary to enter Sleep Operation Mode (TJA1145 in Sleep Mode, uC unsupplied) 
* successfully:
* - Check if an regular interrupt (wake-up) would be enabled in Sleep Mode (See file \link TJA1145FD_Configuration.h \endlink)
* - If TJA1145 is in Normal Mode, stop CAN transmission
* - Enable wake up source (Events to be captured in Sleep Mode) (See file \link TJA1145FD_Configuration.h \endlink)
* - Set CPNC bit (disable/enable selective wake-up function according to configuration)
* - Check if no interrupt is pending  
* - If selective wake-up function shall be ENABLED in Sleep Mode:
*	-- The WUF flag is cleared and transceiver is ready to wake up on next WUF
*	-- CAN PE is stopped
*	-- TJA1145 enters Standby Mode
*	-- CAN PE is put in Sleep Mode (wakeable)
*	-- Wake flag status of TJA1145 is checked and pending wakes are handled to avoid a deadlock
* - If selective wake-up function shall be DISABLED in Sleep Mode:
*	-- CAN communication is stopped
*	-- CAN PE is stopped
*	-- CAN PE is put in Sleep Mode (wakeable)
*	-- TJA1145 enters Standby Mode
* If this transition is successful, the TJA1145 Sleep command is sent. 
* If Sleep transition is aborted, e.g. due to a a last minute wake-up, polling of the Event Status Register 
* and entering Normal Operation Mode are scheduled for next main task.

* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t ChangeToSleepOperation(){
	StdReturn_t ret = E_OK;
	TJA1145FD_System_Event_Enable_Reg_t sysEvEn = TJA1145FD_SYS_EVENT_EN_SLEEP; 
	TJA1145FD_Transceiver_Event_Enable_Reg_t trcvEvEn = TJA1145FD_TRX_EVENT_EN_SLEEP;
	TJA1145FD_Wake_Pin_Enable_Reg_t wakeEvEn = TJA1145FD_WAKE_PIN_EN_SLEEP;
	TJA1145FD_Global_Event_Status_Reg_t pendingEvent;
	CanTrcv_TrcvModeType pMode;
	TJA1145FD_Mode_Control_t mc_reg; 

	// Read Mode Control Register
	(void) TJA1145FD_getModeControlReg(&mc_reg); 

	// If TJA1145 is not in Sleep Mode
	if(mc_reg != TJA1145FD_MC_SLEEP_MODE) {

		// Check interrupt configuration in Sleep Mode
		// If no regular interrupt is enabled in Sleep Mode, change to Sleep Mode is aborted
		if ((trcvEvEn.TJA1145FD_CWE == TJA1145FD_CWE_CAN_WAKEUP_DETECTION_DISABLE) && 
			(wakeEvEn.TJA1145FD_WPFE == TJA1145FD_WPFE_WAKEPIN_FALLING_EDGE_DETECT_DISABLE) &&
			(wakeEvEn.TJA1145FD_WPRE == TJA1145FD_WPRE_WAKEPIN_RISING_EDGE_DETECT_DISABLE)) {
				ret = E_NOT_OK;  			

		} else {    

			// Read Mode Control Register
			(void) TJA1145_GetOpMode(&pMode);  
			if(pMode == CANTRCV_TRCVMODE_NORMAL){     
				// Stop CAN transmission
				StopCAN_TX();     	
			}     

			// Configure to be captured events in Sleep Mode
			if(TJA1145FD_setSystemEventEnable(sysEvEn.TJA1145FD_OTWE, sysEvEn.TJA1145FD_SPIFE) != NXP_UJA11XX_SUCCESS){
				ret = E_NOT_OK;
			}
			if (TJA1145FD_setWakePinEnable(wakeEvEn.TJA1145FD_WPRE, wakeEvEn.TJA1145FD_WPFE) != NXP_UJA11XX_SUCCESS){
				ret = E_NOT_OK;
			}  	

			(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_ENABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);
			if (TJA1145FD_setTransceiverEventEnable(trcvEvEn.TJA1145FD_CBSE, trcvEvEn.TJA1145FD_CFE, trcvEvEn.TJA1145FD_CWE) != NXP_UJA11XX_SUCCESS){
				ret = E_NOT_OK;
			}  		
			if (TJA1145_SetPNActivationState((CanTrcv_PNActivationType) TJA1145FD_CPNC_SLEEP) != E_OK){
				ret = E_NOT_OK;
			}
			(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_DISABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);


			// If no interrupt is pending, enter TJA1145 Standby Mode
			(void) TJA1145FD_getGlobalEventStatus(&pendingEvent.TJA1145FD_WPE, &pendingEvent.TJA1145FD_TRXE, &pendingEvent.TJA1145FD_SYSE);
			if((pendingEvent.TJA1145FD_WPE == TJA1145FD_WPE_NO_WAKE_PIN_EVENT) &&
				(pendingEvent.TJA1145FD_TRXE == TJA1145FD_TRXE_NO_TRANSCEIVER_EVENT) &&
				(pendingEvent.TJA1145FD_SYSE == TJA1145FD_SYSE_NO_SYSTEM_EVENT)){                             

					// If PN has been activated successfully, follow defined shutdown flow for shutdown of CAN 
					//  transceiver and CAN controller (source: Autosar R3.2 and higher)
					if ( ret == E_OK && (TJA1145FD_CPNC_SLEEP == TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_ENABLE)){

						// dedicated request to clear the WUF flag
						if (TJA1145_ClearTrcvWufFlag() == E_NOT_OK){
							ret = E_NOT_OK;
						}	
						// Disable CAN PE; wake-up disabled
						(void) CANStopMode();
						// Enter TJA1145 Standby Mode
						if (TJA1145_SetOpMode(CANTRCV_TRCVMODE_STANDBY) == E_NOT_OK){
							ret = E_NOT_OK;
						}	
						// Disable CAN PE; wake-up enabled
						(void) CANSleepMode();	
						// Check if WUF has occured meanwhile; If yes, wake up ECU again
						if (TJA1145_CheckWakeFlag() == E_NOT_OK){
							ret = E_NOT_OK;
						}
					}    	  
					// If partial networking is not activated in TJA1145 
					else {
						// Disable CAN PE, activate wake-up
						(void) CANStopMode();
						(void) CANSleepMode();	
						// Enter TJA1145 Standby Mode
						if (TJA1145_SetOpMode(CANTRCV_TRCVMODE_STANDBY) == E_NOT_OK){
							ret = E_NOT_OK;
						}
					}

					// if CAN shutdown and entering Standby Mode was successful
					if (ret == E_OK){          

						(void) ClearNormalModeLed();         

						// Enter TJA1145 Sleep Mode 
						(void) TJA1145_SetOpMode(CANTRCV_TRCVMODE_SLEEP);  

						// If Sleep Mode is entered SW should never enter this point in SW
	    	      	
					} else { 

						// Enter Normal Operation Mode is scheduled
						(void) AddTaskToScheduler(CHANGE_TO_NORMAL);
						PendingEvent = TRUE;   	    		
					}   
			} else {

				// Enter Normal Operation Mode is scheduled
				(void) AddTaskToScheduler(CHANGE_TO_NORMAL);
				PendingEvent = TRUE;  
			}
		}  
	}

	return ret;
}


/// Preparation and transition to Normal Operation Mode
/**	This function manages all things that are necessary to enter Normal Operation Mode.
*	If the TJA1145 is not already in Normal Mode:
* - TJA1145 Normal Mode is entered
* - Events to be captured in Normal Mode are enabled 
* - Task is scheduled that checks CAN transceiver status/supply and activates CAN controller and starts CAN transmission 
*
* \author	jh
* \version	1.0 
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t ChangeToNormalOperation(){
	StdReturn_t ret = E_OK; 
	TJA1145FD_System_Event_Enable_Reg_t sysEvEn = TJA1145FD_SYS_EVENT_EN_NORMAL; 
	TJA1145FD_Transceiver_Event_Enable_Reg_t trcvEvEn = TJA1145FD_TRX_EVENT_EN_NORMAL;
	TJA1145FD_Wake_Pin_Enable_Reg_t wakeEvEn = TJA1145FD_WAKE_PIN_EN_NORMAL;

	// Enter TJA1145 Normal Mode
	if(TJA1145FD_setModeControlReg(TJA1145FD_MC_NORMAL_MODE) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	} else {      

		// Configure to be captured events in Normal Mode
		if(TJA1145FD_setSystemEventEnable(sysEvEn.TJA1145FD_OTWE, sysEvEn.TJA1145FD_SPIFE) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK;
		}   			       
		if (TJA1145FD_setWakePinEnable(wakeEvEn.TJA1145FD_WPRE, wakeEvEn.TJA1145FD_WPFE) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK;
		}

		(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_ENABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);
		if (TJA1145FD_setTransceiverEventEnable(trcvEvEn.TJA1145FD_CBSE, trcvEvEn.TJA1145FD_CFE, trcvEvEn.TJA1145FD_CWE) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK;
		}
		(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_DISABLED_0X68_TO_0X6F, TJA1145FD_LK5C_SPI_WRITE_ACCESS_DISABLED_0X50_TO_0X5F, TJA1145FD_LK4C_SPI_WRITE_ACCESS_ENABLED_0X40_TO_0X4F, TJA1145FD_LK3C_SPI_WRITE_ACCESS_DISABLED_0X30_TO_0X3F, TJA1145FD_LK2C_SPI_WRITE_ACCESS_DISABLED_0X20_TO_0X2F, TJA1145FD_LK1C_SPI_WRITE_ACCESS_DISABLED_0X10_TO_0X1F, TJA1145FD_LK0C_SPI_WRITE_ACCESS_DISABLED_0X06_TO_0X09);

		(void) SetNormalModeLed(); 

		// check CAN and LIN transceiver and supply status; if CFS or VCS or VLINS are ok, CAN communication can be started
		PollTransceiverStatus();	
	}	   	

	return ret;
}


/// Main Event Handling function
/** This function checks whether an event is pending. It reads the Global Event Status Register 
* and the related System, Supply, Transceiver and Wake Pin Status Registers if necessary and 
* calls the according service routines.
* This function is cyclically called by the scheduler to check the TJA1145 status and handle 
* pending events. 
*
* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t EventHandling() {
	StdReturn_t ret = E_OK;
	TJA1145FD_Global_Event_Status_Reg_t pendingEv;
	TJA1145FD_System_Event_Status_Reg_t sysEv;
	TJA1145FD_Transceiver_Event_Status_Reg_t trcvEv;
	TJA1145FD_Wake_Pin_Event_Reg_t wakeEv;

	// read Global Event Status Register
	(void) TJA1145FD_getGlobalEventStatus(&pendingEv.TJA1145FD_WPE, &pendingEv.TJA1145FD_TRXE, &pendingEv.TJA1145FD_SYSE);

	// System Event pending
	if (pendingEv.TJA1145FD_SYSE == TJA1145FD_SYSE_SYSTEM_EVENT_PENDING) {
		(void) TJA1145FD_getSystemEventStatus(&sysEv.TJA1145FD_PO, &sysEv.TJA1145FD_OTW, &sysEv.TJA1145FD_SPIF);
		// PO Event pending
		if(sysEv.TJA1145FD_PO == TJA1145FD_PO_OFF_MODE_LEFT) {
			if (TJA1145_PO_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// store wake-up reason "power-on"
			WuReason = CANTRCV_WU_POWER_ON;	
		}
		// OTW Event pending
		if(sysEv.TJA1145FD_OTW == TJA1145FD_OTW_TEMPERATURE_EXCEEDS_WARNING_LEVEL) {
			if (TJA1145_OTW_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}	
		}
		// SPIF Event pending
		if(sysEv.TJA1145FD_SPIF == TJA1145FD_SPIF_SPI_FAILURE_DETECTED) {
			if (TJA1145_SPIF_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
		}		
	}
	// Transceiver Event pending
	if (pendingEv.TJA1145FD_TRXE == TJA1145FD_TRXE_TRANSCEIVER_EVENT_PENDING) {
		(void) TJA1145FD_getTransceiverEventStatus(&trcvEv.TJA1145FD_PNFDE, &trcvEv.TJA1145FD_CBS, &trcvEv.TJA1145FD_CF, &trcvEv.TJA1145FD_CW);

		// PNFD Event pending
		if(trcvEv.TJA1145FD_PNFDE == TJA1145FD_PNFDE_PARTIAL_NETWORK_FRAME_ERROR_DETECTED) {
			if (TJA1145_PNFDE_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// store wake-up reason "SYSERR"
			WuReason = CANTRCV_WU_BY_SYSERR;
		}
		// CW Event pending
		if(trcvEv.TJA1145FD_CW == TJA1145FD_CW_CAN_WAKEUP_EVENT) {
			if (TJA1145_CW_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
		}
		// CF Event pending
		if(trcvEv.TJA1145FD_CF == TJA1145FD_CF_CAN_FAILURE_DETECTED) {
			if (TJA1145_CF_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
		}
		// CBS Event pending
		if(trcvEv.TJA1145FD_CBS == TJA1145FD_CBS_NO_CAN_BUS_ACTIVITY) {
			if (TJA1145_CBS_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
		}
	}
	// Wake Pin Event pending
	if (pendingEv.TJA1145FD_WPE == TJA1145FD_WPE_WAKE_PIN_EVENT_PENDING) {
		(void) TJA1145FD_getWakePinEvent(&wakeEv.TJA1145FD_WPR, &wakeEv.TJA1145FD_WPF); 		
		if(wakeEv.TJA1145FD_WPR == TJA1145FD_WPR_WAKEPIN_RISING_EDGE_DETECTED) {
			if (TJA1145_WPR_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// save wake-up reason
			WuReason = CANTRCV_WU_BY_PIN;
		}
		// CW Event pending
		if(wakeEv.TJA1145FD_WPF == TJA1145FD_WPF_WAKEPIN_FALLING_EDGE_DETECTED) {
			if (TJA1145_WPF_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// save wake-up reason
			WuReason = CANTRCV_WU_BY_PIN;
		}
	}

	return ret;
}


/// Rxd Low Handling function
/** This function is called if RXD low is detected while TJA1145 is in low power mode. As RXD is used to signal 
* pending events to the microcontroller, the event source is determined and handled. This function reads the Global 
* Event Status Register and the related System, Transceiver and Wake Pin Capture Register and calls the 
* according service routines. This function differs slightly from the Event Handling done during Normal Operation
* because additional actions are required for some events e.g. Store Wake-Up reason, Enter Normal Operation, Enter Stop Mode.
* 
* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t RxdLowHandling() {
	StdReturn_t ret = E_OK;
	TJA1145FD_Global_Event_Status_Reg_t pendingEv;
	TJA1145FD_System_Event_Status_Reg_t sysEv;
	TJA1145FD_Transceiver_Event_Status_Reg_t trcvEv;
	TJA1145FD_Wake_Pin_Event_Reg_t wakeEv;

	WuReason = CANTRCV_WU_INTERNALLY;

	// read Global Event Status Register
	(void) TJA1145FD_getGlobalEventStatus(&pendingEv.TJA1145FD_WPE, &pendingEv.TJA1145FD_TRXE, &pendingEv.TJA1145FD_SYSE);

	// System Event pending
	if (pendingEv.TJA1145FD_SYSE == TJA1145FD_SYSE_SYSTEM_EVENT_PENDING) {
		(void) TJA1145FD_getSystemEventStatus(&sysEv.TJA1145FD_PO, &sysEv.TJA1145FD_OTW, &sysEv.TJA1145FD_SPIF);

		// Power On event cannot be pending --> can never be set during running Operation

		// OTW Event pending
		if(sysEv.TJA1145FD_OTW == TJA1145FD_OTW_TEMPERATURE_EXCEEDS_WARNING_LEVEL) {
			if (TJA1145_OTW_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// Enter Stop Mode again
			AddTaskToScheduler(CHANGE_TO_STANDBY);
		}
		// SPIF Event pending
		if(sysEv.TJA1145FD_SPIF == TJA1145FD_SPIF_SPI_FAILURE_DETECTED) {
			if (TJA1145_SPIF_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// Enter Stop Mode again
			AddTaskToScheduler(CHANGE_TO_STANDBY);
		}	
	}
	// Transceiver Event pending
	if (pendingEv.TJA1145FD_TRXE == TJA1145FD_TRXE_TRANSCEIVER_EVENT_PENDING) {
		(void) TJA1145FD_getTransceiverEventStatus(&trcvEv.TJA1145FD_PNFDE, &trcvEv.TJA1145FD_CBS, &trcvEv.TJA1145FD_CF, &trcvEv.TJA1145FD_CW);
		// PNFD Event pending
		if(trcvEv.TJA1145FD_PNFDE == TJA1145FD_PNFDE_PARTIAL_NETWORK_FRAME_ERROR_DETECTED) {
			if (TJA1145_PNFDE_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// put TJA1145 in Normal Mode
			(void) AddTaskToScheduler(CHANGE_TO_NORMAL);
			// store wake-up reason "SYSERR"
			WuReason = CANTRCV_WU_BY_SYSERR;
		}
		// CW Event pending
		if(trcvEv.TJA1145FD_CW == TJA1145FD_CW_CAN_WAKEUP_EVENT) {
			if (TJA1145_CW_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}				
			// put TJA1145 in Normal Mode
			AddTaskToScheduler(CHANGE_TO_NORMAL);			
		}
		// CF Event pending
		if(trcvEv.TJA1145FD_CF == TJA1145FD_CF_CAN_FAILURE_DETECTED) {
			if (TJA1145_CF_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// Enter Stop Mode again
			AddTaskToScheduler(CHANGE_TO_STANDBY);
		}
		// CBS Event pending
		if(trcvEv.TJA1145FD_CBS == TJA1145FD_CBS_NO_CAN_BUS_ACTIVITY) {
			if (TJA1145_CBS_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}   
			// If no CAN communication is ongoing anymore, TJA1145 is put to Sleep Mode to reduce power consumption   	
			AddTaskToScheduler(CHANGE_TO_SLEEP);  			                                             	
		}
	}
	// Wake Pin Event pending
	if (pendingEv.TJA1145FD_WPE == TJA1145FD_WPE_WAKE_PIN_EVENT_PENDING) {
		(void) TJA1145FD_getWakePinEvent(&wakeEv.TJA1145FD_WPR, &wakeEv.TJA1145FD_WPF); 		
		if(wakeEv.TJA1145FD_WPR == TJA1145FD_WPR_WAKEPIN_RISING_EDGE_DETECTED) {
			if (TJA1145_WPR_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// Enter Normal Mode
			AddTaskToScheduler(CHANGE_TO_NORMAL);
			// save wake-up reason
			WuReason = CANTRCV_WU_BY_PIN;
		}
		// CW Event pending
		if(wakeEv.TJA1145FD_WPF == TJA1145FD_WPF_WAKEPIN_FALLING_EDGE_DETECTED) {
			if (TJA1145_WPF_ServiceRoutine() == E_NOT_OK){
				ret = E_NOT_OK;
			}
			// Enter Normal Mode
			AddTaskToScheduler(CHANGE_TO_NORMAL);
			// save wake-up reason
			WuReason = CANTRCV_WU_BY_PIN;
		}			
	}  

	return ret;
}


/// Checks Transceiver failure status
/** This function checks whether the CAN and LIN transceiver status are ok. 
*	If CFS, VCS and VLINS are ok, CAN/LIN communication is activated again. If not, a new request 
*	for polling of CFS, VCS and VLINS is scheduled.
* 
* \author	jh
* \version	1.0 
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
void PollTransceiverStatus(){
	TJA1145FD_Transceiver_Status_Reg_t trcvStatus;              

	(void) TJA1145FD_getTransceiverStatus(&trcvStatus.TJA1145FD_CTS, &trcvStatus.TJA1145FD_CPNERR, &trcvStatus.TJA1145FD_CPNS, &trcvStatus.TJA1145FD_COSCS, &trcvStatus.TJA1145FD_CBSS, &trcvStatus.TJA1145FD_VCS, &trcvStatus.TJA1145FD_CFS);
	if((trcvStatus.TJA1145FD_CFS == TJA1145FD_CFS_NO_TXD_TIMEOUT_EVENT) && (trcvStatus.TJA1145FD_VCS == TJA1145FD_VCS_OUTPUT_VOLTAGE_ON_V1_IS_ABOVE_THE_90_THRESHOLD) && (trcvStatus.TJA1145FD_CTS == TJA1145FD_CTS_CAN_TRANSMITTER_READY_TO_TRANSMIT_DATA)){
		// Restart CAN communication (enable CAN PE and start transmission)
		ResumeCAN_TX(); 	 
	} else {
		// Stop CAN transmission
		(void) StopCAN_TX();
		// Stop CAN PE
		(void) CANStopMode();
		// Schedule Poll transceiver status
		CheckTrcvStatus = TRUE;   
	}
}


/// Port monitoring
/**	This function reads an input port of the microcontroller. Depending on the result 3 different
* mode changes are possible:
* - Enter Sleep Operation Mode
* - Enter Standby Operation Mode
* - Enter Normal Operation Mode
* 
* \author	jh
* \version	1.0 
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
void PortSupervisor (void){
	Byte portData = 0;

	portData = ScanPort();
	if((portData & PORTMASK_NORMAL) == 0){      
		// Normal
		AddTaskToScheduler(CHANGE_TO_NORMAL);   
	}
	else if((portData & PORTMASK_STANDBY) == 0){ 
		// Standby
		AddTaskToScheduler(CHANGE_TO_STANDBY);   
	}
	else if((portData & PORTMASK_SLEEP) == 0){
		// Sleep
		AddTaskToScheduler(CHANGE_TO_SLEEP);    
	} 
}

/// WAKE Pin monitoring
/**	This function checks the status of an Wake Pin of the TJA1145. If the Wake input value is low, 
* Standby Operation Mode is requested.
* 
* \author	jh
* \version	1.0 
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
void WakeSupervisor(void){
	TJA1145FD_Wake_Status_Reg_t wakeStatus;

	(void) TJA1145FD_getWakeStatus(&wakeStatus.TJA1145FD_WPVS);
	if (wakeStatus.TJA1145FD_WPVS == TJA1145FD_WPVS_VOLTAGE_BELOW_SWITCHING_THRESHOLD) {
		// application specific actions ...
	} 
}        


/// Set the PN identifier registers
/** This function sets the identifier of the Partial Networking Wake-up frame. 
*	The location of identifier bits in the register structure depends on the frame type (Standard/Extended). 
*	In case the Wake-up frame is an extended one, all four identifier registers are written, else
*	only the Identifier Register 2 and 3 are configured accordingly. The parameter (int id) is the 
*	real identifier value as integer. The alignments needed for the register structure are done
*	by this function.
* 
* \author	jh
* \version	1.0
* \date		2013/04/x
* \param	id: real identifier value as integer 
* \param 	idFormat: format of wake-up frame, possible values: TJA1145FD_IDE_EXTENDED_FRAME_FORMAT_29_BIT	= 1, TJA1145FD_IDE_STANDARD_FRAME_FORMAT_11_BIT	= 0
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK	
*/
StdReturn_t TJA1145_SetPnIdentifier(Word id, TJA1145FD_Identifier_Format_t idFormat){
	StdReturn_t ret = E_OK;
	Byte IdReg0, IdReg1, IdReg2_0, IdReg2_1, IdReg3 = 0x0;	

	if (idFormat == TJA1145FD_IDE_EXTENDED_FRAME_FORMAT_29_BIT){
		// configure content of identifier registers
		IdReg0 = (Byte) ((id & 0x000000ff));
		IdReg1 = (Byte) ((id & 0x0000ff00) >> 8);
		IdReg2_0 = (Byte) ((id & 0x00030000) >> 16);
		IdReg2_1 = (Byte) ((id & 0x00fc0000) >> 18);
		IdReg3 = (Byte) ((id & 0xff000000) >> 24);
		if (TJA1145FD_setCANIdentifier0(IdReg0) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
		if (TJA1145FD_setCANIdentifier1(IdReg1) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
		if (TJA1145FD_setCANIdentifier2(IdReg2_1, IdReg2_0) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
		if (TJA1145FD_setCANIdentifier3(IdReg3) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
	} else {
		// configure content of identifier registers (identifier registers 2 & 3)
		IdReg2_0 = 0x0;
		IdReg2_1 = (Byte) (id & 0x3F);
		IdReg3 = (Byte) ((id & 0x7C0) >> 6);	
		if (TJA1145FD_setCANIdentifier2(IdReg2_1, IdReg2_0) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
		if (TJA1145FD_setCANIdentifier3(IdReg3) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
	}

	return ret;
}


/// Set the PN Identifier Mask registers
/** This function sets the identifier mask of the Partial Networking Wake-up frame. 
*	The location of identifier mask bits depends on the frame type (Standard/Extended). In case
*	the Wake-up frame is an extended one, all four identifier mask registers are written, else
*	only the identifier mask registers 2 and 3 are configured accordingly. The parameter mask is the 
*	real identifier mask value as integer. The alignments needed needed for register structure are done
*	by this function.
* 
* \author	jh
* \version	1.0
* \date		2013/06/05
* \param	mask: real identifier mask value as integer 
* \param	idFormat: format of wake-up frame, possible values: TJA1145FD_IDE_EXTENDED_FRAME_FORMAT_29_BIT	= 1, TJA1145FD_IDE_STANDARD_FRAME_FORMAT_11_BIT	= 0
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK	
*/
StdReturn_t TJA1145_SetPnIdMask(Word mask, TJA1145FD_Identifier_Format_t idFormat){
	StdReturn_t ret = E_OK;
	Byte IdMaskReg0, IdMaskReg1, IdMaskReg2_0, IdMaskReg2_1, IdMaskReg3 = 0x0;		

	if (idFormat == TJA1145FD_IDE_EXTENDED_FRAME_FORMAT_29_BIT){
		// configure content of identifier registers
		IdMaskReg0 = (Byte) ((mask & 0x000000ff));
		IdMaskReg1 = (Byte) ((mask & 0x0000ff00) >> 8);
		IdMaskReg2_0 = (Byte) ((mask & 0x00030000) >> 16);
		IdMaskReg2_1 = (Byte) ((mask & 0x00fc0000) >> 18);
		IdMaskReg3 = (Byte) ((mask & 0xff000000) >> 24);
		if (TJA1145FD_setCANMask0(IdMaskReg0) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
		if (TJA1145FD_setCANMask1(IdMaskReg1) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
		if (TJA1145FD_setCANMask2(IdMaskReg2_1, IdMaskReg2_0) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
		if (TJA1145FD_setCANMask3(IdMaskReg3) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
	} else {
		// configure content of identifier registers (identifier registers 2 & 3)
		IdMaskReg2_0 = 0x0;
		IdMaskReg2_1 = (Byte) (mask & 0x3F);
		IdMaskReg3 = (Byte) ((mask & 0x7C0) >> 6);	
		if (TJA1145FD_setCANMask2(IdMaskReg2_1, IdMaskReg2_0) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
		if (TJA1145FD_setCANMask3(IdMaskReg3) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK; 
		}
	}

	return ret;
}


/// Configure partial network and check configuration in CAN HW.
/*	This function configures partial networking in the TJA1145 TJA1145. If all configuration registers are configured
*	correctly, the PNCOK bit is activated in the CAN Control Register.
* 
* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/

StdReturn_t ConfigurePartialNetworking(){
	StdReturn_t ret = E_OK;
	TJA1145FD_CAN_Control_Reg_t cc;
	TJA1145FD_Lock_Control_Reg_t lockCtrl;

	(void) TJA1145FD_getLockControl(&lockCtrl.TJA1145FD_LK6C, &lockCtrl.TJA1145FD_LK5C, &lockCtrl.TJA1145FD_LK4C, &lockCtrl.TJA1145FD_LK3C, &lockCtrl.TJA1145FD_LK2C, &lockCtrl.TJA1145FD_LK1C, &lockCtrl.TJA1145FD_LK0C);
	(void) TJA1145FD_setLockControl(TJA1145FD_LK6C_SPI_WRITE_ACCESS_ENABLED_0X68_TO_0X6F, lockCtrl.TJA1145FD_LK5C, lockCtrl.TJA1145FD_LK4C, lockCtrl.TJA1145FD_LK3C, TJA1145FD_LK2C_SPI_WRITE_ACCESS_ENABLED_0X20_TO_0X2F, lockCtrl.TJA1145FD_LK1C, lockCtrl.TJA1145FD_LK0C);

	// configure CAN data rate
	if (TJA1145FD_setDataRate(TJA1145FD_CAN_DATA_RATE) == E_NOT_OK){
		ret = E_NOT_OK;
	}
	// configure CAN ID registers
	if (TJA1145_SetPnIdentifier(UJA116FDVX_CAN_ID, TJA1145FD_CAN_FRAME_CONTROL.TJA1145FD_IDE) == E_NOT_OK){
		ret = E_NOT_OK;
	}
	// configure CAN ID mask registers
	if (TJA1145_SetPnIdMask(TJA1145FD_CAN_ID_MASK, TJA1145FD_CAN_FRAME_CONTROL.TJA1145FD_IDE) == E_NOT_OK){
		ret = E_NOT_OK;
	}
	// configure CAN Frame Control register
	if ( TJA1145FD_setFrameControl(TJA1145FD_CAN_FRAME_CONTROL.TJA1145FD_IDE, TJA1145FD_CAN_FRAME_CONTROL.TJA1145FD_PNDM, TJA1145FD_CAN_FRAME_CONTROL.TJA1145FD_DLC) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	// configure CAN Data Byte registers
	if (TJA1145FD_setDataMask0(TJA1145FD_CAN_DATA_MASK0) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_setDataMask1(TJA1145FD_CAN_DATA_MASK1) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_setDataMask2(TJA1145FD_CAN_DATA_MASK2) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_setDataMask3(TJA1145FD_CAN_DATA_MASK3) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_setDataMask4(TJA1145FD_CAN_DATA_MASK4) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_setDataMask5(TJA1145FD_CAN_DATA_MASK5) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_setDataMask6(TJA1145FD_CAN_DATA_MASK6) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_setDataMask7(TJA1145FD_CAN_DATA_MASK7) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}

	// If all registers are configured correctly, the PNCOK bit in the CAN Control register is set
	if (TJA1145FD_getCANControl(&cc.TJA1145FD_CFDC, &cc.TJA1145FD_PNCOK, &cc.TJA1145FD_CPNC, &cc.TJA1145FD_CMC)!= NXP_UJA11XX_SUCCESS) {
		ret = E_NOT_OK;
	}
	if (ret == E_OK){
		if (TJA1145FD_setCANControl(cc.TJA1145FD_CFDC, TJA1145FD_PNCOK_PARTIAL_NETWORK_CONFIGURATION_SUCCESSFUL, cc.TJA1145FD_CPNC, cc.TJA1145FD_CMC) != NXP_UJA11XX_SUCCESS) {
			ret = E_NOT_OK;
		}
	}

	(void) TJA1145FD_setLockControl(lockCtrl.TJA1145FD_LK6C, lockCtrl.TJA1145FD_LK5C, lockCtrl.TJA1145FD_LK4C, lockCtrl.TJA1145FD_LK3C, lockCtrl.TJA1145FD_LK2C, lockCtrl.TJA1145FD_LK1C, lockCtrl.TJA1145FD_LK0C);

	return ret;
}


/// SPI Failure Service Routine
/** This function handles all actions to be done if an SPI failure event has been detected:
*	- store error in failure memory
*	- clear SPIF Event flag	
*	
* \author	jh
* \version	1.0 
* \date	    2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_SPIF_ServiceRoutine() {
	StdReturn_t ret = E_OK;

	// application specific code ...    
	AddToFailureMemory(SPI_FAILURE);

	// Clear SPIF Event flag
	if (TJA1145FD_setSystemEventStatus(TJA1145FD_PO_NO_POWER_ON, TJA1145FD_OTW_NO_OVER_TEMPERATURE, TJA1145FD_SPIF_SPI_FAILURE_DETECTED) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}                 

	return ret;
}   


/// Overtemperature Warning Service Routine
/** This function handles all actions to be done if overtemperature warning on has been detected:
*	- store error in failure memory
*	- Clear OTW Event flag
* 
* \author	jh
* \version	1.0 
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_OTW_ServiceRoutine(){
	StdReturn_t ret = E_OK;

	// application specific code ...    
	// e.g. reduce SMPS output voltage, store important MCU data in EEPROM/Flash   	
	// add failure entry
	AddToFailureMemory(OVERTEMP_WARNING);  

	// Clear OTW Event flag
	if (TJA1145FD_setSystemEventStatus(TJA1145FD_PO_NO_POWER_ON, TJA1145FD_OTW_TEMPERATURE_EXCEEDS_WARNING_LEVEL, TJA1145FD_SPIF_NO_SPI_FAILURE) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}       

	return ret;
}


/// Power On Service Routine
/** This function handles all actions to be done if power-on has been detected:
*	- initialize the TJA1145
*	- clear power on status event
* 
* \author	jh
* \version	1.0 
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_PO_ServiceRoutine(){
	StdReturn_t ret = E_OK;

	// init TJA1145
	(void) InitTJA1145();

	// application specific code ...

	// Clear POS Event flag
	if (TJA1145FD_setSystemEventStatus(TJA1145FD_PO_OFF_MODE_LEFT, TJA1145FD_OTW_NO_OVER_TEMPERATURE, TJA1145FD_SPIF_NO_SPI_FAILURE) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}    

	return ret;
}


/// Partial Networking Frame Detect Error Wake Service Routine
/** This function handles all actions to be done if a PN Frame Detect Error has been detected:
*	- schedule reconfiguration of Partial Networking registers
*	- Clear PNFD Event flag
* 
* \author	jh
* \version	1.0
* \date		2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_PNFDE_ServiceRoutine(){
	StdReturn_t ret = E_OK;

	// reconfigure Partial Networking
	(void) AddTaskToScheduler(CFG_PARTIAL_NETWORKING);

	// Clear PNFDE bit
	if (TJA1145FD_setTransceiverEventStatus(TJA1145FD_PNFDE_PARTIAL_NETWORK_FRAME_ERROR_DETECTED, TJA1145FD_CBS_CAN_BUS_ACTIVE, TJA1145FD_CF_NO_CAN_FAILURE, TJA1145FD_CW_NO_CAN_WAKEUP) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	} 

	return ret;
}


/// CAN Wake Service Routine
/** This function handles all actions to be done if a CAN Wake-up has been detected:
* - determine wake-up reason (CPNC = 1: WUF or WUP, CPNC = 0: BUS)
* - Clear CW Event flag
* 
* \author	jh
* \version	1.0 
* \date     2013/06/05	
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_CW_ServiceRoutine(){
	StdReturn_t ret = E_OK;
	TJA1145FD_CAN_Control_Reg_t canCtrl;
	TJA1145FD_Transceiver_Status_Reg_t trcvStatus;	

	// read CAN ControlRegister
	if (TJA1145FD_getCANControl(&canCtrl.TJA1145FD_CFDC, &canCtrl.TJA1145FD_PNCOK, &canCtrl.TJA1145FD_CPNC, &canCtrl.TJA1145FD_CMC) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK; 
	}

	if (TJA1145FD_getTransceiverStatus(&trcvStatus.TJA1145FD_CTS, &trcvStatus.TJA1145FD_CPNERR, &trcvStatus.TJA1145FD_CPNS, &trcvStatus.TJA1145FD_COSCS, &trcvStatus.TJA1145FD_CBSS, &trcvStatus.TJA1145FD_VCS, &trcvStatus.TJA1145FD_CFS) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK; 
	}                          	

	// if CPNC == 1 --> wake via WUF 
	// if CPNC == 0 -> wake via WUP 
	if (canCtrl.TJA1145FD_CPNC == TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_ENABLE ){
		WuReason = CANTRCV_WU_BY_BUS_WUF;
	} else {
		WuReason = CANTRCV_WU_BY_BUS_WUP;
	}   

	// Clear CW Event flag
	if (TJA1145FD_setTransceiverEventStatus(TJA1145FD_PNFDE_NO_PARTIAL_NETWORK_FRAME_ERROR, TJA1145FD_CBS_CAN_BUS_ACTIVE, TJA1145FD_CF_NO_CAN_FAILURE, TJA1145FD_CW_CAN_WAKEUP_EVENT) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;        	
	}    

	return ret;
}


/// CAN Failure Service Routine
/** This function handles all actions to be done if a CAN Failure (TXD dominant failure, VCAN undervoltage, 
*  CAN Transmitter disabled) has been detected and the CAN transceiver is deactivated:
* - store error in failure memory
* - if CAN failure is still present, stop CAN communication and schedule check of transceiver status flags
* - clear CF Event flag
* 
* \author	jh
* \version	1.0 
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_CF_ServiceRoutine(){
	StdReturn_t ret = E_OK;
	TJA1145FD_Transceiver_Status_Reg_t trcvStatus;

	// application specific actions ...
	AddToFailureMemory(CAN_FAILURE);           

	// Clear CF Event flag
	if (TJA1145FD_setTransceiverEventStatus(TJA1145FD_PNFDE_NO_PARTIAL_NETWORK_FRAME_ERROR, TJA1145FD_CBS_CAN_BUS_ACTIVE, TJA1145FD_CF_CAN_FAILURE_DETECTED, TJA1145FD_CW_NO_CAN_WAKEUP) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}  

	(void) TJA1145FD_getTransceiverStatus(&trcvStatus.TJA1145FD_CTS, &trcvStatus.TJA1145FD_CPNERR, &trcvStatus.TJA1145FD_CPNS, &trcvStatus.TJA1145FD_COSCS, &trcvStatus.TJA1145FD_CBSS, &trcvStatus.TJA1145FD_VCS, &trcvStatus.TJA1145FD_CFS);
	if((trcvStatus.TJA1145FD_CFS != TJA1145FD_CFS_NO_TXD_TIMEOUT_EVENT) || (trcvStatus.TJA1145FD_VCS != TJA1145FD_VCS_OUTPUT_VOLTAGE_ON_V1_IS_ABOVE_THE_90_THRESHOLD) || (trcvStatus.TJA1145FD_CTS != TJA1145FD_CTS_CAN_TRANSMITTER_READY_TO_TRANSMIT_DATA)){
		// Stop CAN transmission
		(void) StopCAN_TX();
		// Stop CAN PE
		(void) CANStopMode();
		// schedule Poll transceiver failure status to reactivate CAN again if failures are gone
		CheckTrcvStatus = TRUE;  
	}

	return ret;
}


/// CAN Bus Silence Service Routine
/** This function handles all actions to be done if a CAN Bus Silence Wake-up has been detected:
* - Clear CBS Event flag
* - furthermore e.g. if CBS Event occurs in Standby Mode, it means no CAN communication is ongoing
* anymore and TJA1145 can be put into Sleep Mode to reduce power consumption, which means a longer 
* start-up time of the application. (Since for this application it is only valid if the CBS Event 
* occurs in Standby Mode, this functionality is part of the RxdLowHandling function) 
* 
* \author	jh
* \version	1.0 
* \date     2013/06/05	
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_CBS_ServiceRoutine() {
	StdReturn_t ret = E_OK;  

	// application specific actions ...

	// Clear CBS Event flag
	(void) TJA1145_ClearTrcvTimeoutFlag();

	return ret;
}


// Rising Wake Pin Service Routine
/** This function handles all actions to be done if a Wake-up due to rising Wake Pin has been detected:
*	- Clear WPR flag
* 
* \author	jh
* \version	1.0
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_WPR_ServiceRoutine(){
	StdReturn_t ret = E_OK;

	// application specific actions ...

	// Clear WPR bit	
	if (TJA1145FD_setWakePinEvent(TJA1145FD_WPR_WAKEPIN_RISING_EDGE_DETECTED, TJA1145FD_WPF_NO_WAKEPIN_FALLING_EDGE)  != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}

	return ret;
}


/// Falling Wake Pin Service Routine
/** This function handles all actions to be done if a wake-up due to falling wake pin has been detected:
*	- Clear WPF flag
* 
* \author	jh
* \version	1.0
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_WPF_ServiceRoutine(){
	StdReturn_t ret = E_OK;

	// application specific actions ...

	// Clear WPF bit
	if (TJA1145FD_setWakePinEvent(TJA1145FD_WPR_NO_WAKEPIN_RISING_EDGE, TJA1145FD_WPF_WAKEPIN_FALLING_EDGE_DETECTED)  != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}

	return ret;
}


/// Rxd Low Service Routine
/** This function is called when a falling edge on RXD pin has occurred in Low Power Mode.
* 
* \author	jh
* \version	1.0
* \date     2013/06/05	
*/
void RXDLow_ISR(void)
{
	// Signal that an event is pending
	PendingEvent = TRUE;
}


/// Timer Interrupt Service Routine
/** This function is called when the OS timer has elapsed. 
* The OS timer is configured to give an interrupt every ms.
* 
* \author	jh
* \version	1.0
* \date     2013/06/05		  
*/
void Timer_ISR(void)
{	
	// If startup operation is finished, scheduler is called    
	if (StartupReady == TRUE){  
		SchedulerOnTimerOverflow();
	}	 
}


/// Stop CAN message transmission
/**	This functions disables the CAN message transmission. It can be helpful to do this in case of 
* a VCAN undervoltage, a TXD dominant timeout or other transmitter errors because it prevents the 
* increase of the CAN PE internal error counters.
*
* \author   jh
* \version  1.0 
* \date     2013/06/05
*/
void StopCAN_TX(void){
	(void) AbortTransmissionCAN();
}


/// Resume CAN message transmission
/**	This function enables the CAN message transmit path (incl. CAN PE) again. 
*
* \author   jh
* \version  1.0
* \date     2013/06/05   
*/
void ResumeCAN_TX(void){
	(void) EnableTransmissionCAN();
}


/// Change to Flash Operation
/**	This function start the Programming of the Flash memory.  
*
* \author   jh
* \version  1.0
* \date     2013/06/05 
* \return   Byte  
*/
Byte EnterFlashOperation(void) {
	return FlashProgramming();
}


/// Add entry to failure memory
/** This function adds a new entry to the failure memory.
* 
* \author	jh
* \version	1.0
* \date     2013/06/05	
* \param    data: Data to be written to failure memory     	  
*/
void AddToFailureMemory(FailureEntry_t data){
	FailureMemory[FailMemPt_write] = data;
	if (FailMemPt_write < (MAXERRENTR-1)){
		FailMemPt_write = (FailMemPt_write+1) % MAXERRENTR;
	}     
}            


/// Initialize scheduler structure
/**	This function initializes the read and write pointer of the application task queue and
* inits the application task queue.
*
* \author	jh
* \version	1.0 
* \date     2013/06/05		  
*/
void InitScheduler(){
	int i;

	ApplTaskPt_read = 0;
	ApplTaskPt_write = 0;
	for(i = 0; i < MAXTASKNO; i++){
		ApplTask[i] = NO_OPERATION;
	}
}


/// Add new task to scheduler structure
/**	This function adds a new task to the application task queue, which's tasks 
*	are handled during the Main task that is scheduled cyclically.
*
* \author	jh
* \version	1.0 
* \date     2013/06/05		  
* \param    task  Task that should be added to Scheduler Queue \n
*                 possible values: NO_OPERATION, CHANGE_TO_SLEEP, CHANGE_TO_STANDBY, CHANGE_TO_NORMAL, EVENT_HANDLING, 
*                                  TRIGGER_WATCHDOG, POLL_TRCV_STATUS, POLL_GLOBAL_WAKE, PORT_SUPERVISION, HVIO_SUPERVISION 
*/
void AddTaskToScheduler(PendingTask_t task){
	StdReturn_t ret = E_OK;       

	__DI();  
	// If queue is not full, add new task to queue
	if(ApplTask[ApplTaskPt_write] == NO_OPERATION) {
		ApplTask[ApplTaskPt_write] = task;
		ApplTaskPt_write = (ApplTaskPt_write+1) % MAXTASKNO;

	} else {
		//AddToFailureMemory(task);
		AddToFailureMemory(BUFFER_OVERFLOW);
	}       	
	__EI();
}


/// Gets current task of scheduler
/**	This function return the next task of the application task queue that 
*	should be handled during the Main task that is scheduled cyclically.
*
* \author	jh
* \version	1.0 
* \date     2013/06/05		  
* \return   PendingTask_t  Task that should be handled next 
*/    
PendingTask_t GetNextTask(void){
	PendingTask_t ret;

	__DI();	
	ret = ApplTask[ApplTaskPt_read];
	if (ApplTask[ApplTaskPt_read] != NO_OPERATION){
		// clear handled entry
		ApplTask[ApplTaskPt_read] = NO_OPERATION;
		// increment read pointer
		ApplTaskPt_read++;
		if (ApplTaskPt_read == MAXTASKNO){
			ApplTaskPt_read = 0;
		} 
	}
	__EI();

	return ret;
}



// ================= APIs related to PN Autosar R4.1  =============================================================

/// Returns reason for last wake-up of TJA1145
/**	This function returns the reason for the last wake-up of the TJA1145. Wake-up can be caused by:
*	BUS, INTERNALLY (mode change by SPI), RESET, POWER_ON, PIN or SYSERROR.
*	
* \author   jh
* \version  1.0
* \date     2013/06/05
* \param	pReason: possible values: CANTRCV_WU_BY_BUS = 0, CANTRCV_WU_BY_PIN = 1, CANTRCV_WU_ERROR = 2, CANTRCV_WU_INTERNALLY = 3, CANTRCV_WU_NOT_SUPPORTED = 4,
*								    CANTRCV_WU_POWER_ON = 5, CANTRCV_WU_RESET = 6, CANTRCV_WU_BY_SYSERR = 7,  CANTRCV_WU_BY_BUS_WUF = 8, CANTRCV_WU_BY_BUS_WUP = 9
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_GetWuReason(CanTrcv_TrcvWakeupReasonType* pReason) {
	StdReturn_t ret = E_OK;

	*pReason = WuReason;

	return ret;
}


/// Clear transceiver WUF flag
/**	This function clears a pending Wake-up in the TJA1145 caused by a Wake-Up Frame (WUF).
* A WUF flag is only pending if CPNC == 1 and CPNERR == 0 (PNFDE = 0 & PNCOK = 1) and CW == 1. Therefore, 
* it must be checked if a Wake-up by frame is pending and CW bit must be cleared in the Transceiver Event
* Status Register, if WUF is pending.  	
*	
* \author   jh
* \version  1.0
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_ClearTrcvWufFlag(){
	StdReturn_t ret = E_OK;
	TJA1145FD_CAN_Control_Reg_t canCtrl;
	TJA1145FD_Transceiver_Event_Status_Reg_t trcvEv;     	

	if (TJA1145FD_getCANControl(&canCtrl.TJA1145FD_CFDC, &canCtrl.TJA1145FD_PNCOK, &canCtrl.TJA1145FD_CPNC, &canCtrl.TJA1145FD_CMC) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_getTransceiverEventStatus(&trcvEv.TJA1145FD_PNFDE, &trcvEv.TJA1145FD_CBS, &trcvEv.TJA1145FD_CF, &trcvEv.TJA1145FD_CW) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	} 

	// A WUF flag is only pending if CPNC == 1 and CPNERR == 0 (PNFDE = 0 & PNCOK = 1) and CW == 1
	// This means, check if a WUF is pending and clear, if valid  	
	if ((canCtrl.TJA1145FD_CPNC == TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_ENABLE) &&
		(trcvEv.TJA1145FD_PNFDE == TJA1145FD_PNFDE_NO_PARTIAL_NETWORK_FRAME_ERROR && canCtrl.TJA1145FD_PNCOK == TJA1145FD_PNCOK_PARTIAL_NETWORK_CONFIGURATION_SUCCESSFUL) && 
		(trcvEv.TJA1145FD_CW == TJA1145FD_CW_CAN_WAKEUP_EVENT)) {
			if (TJA1145FD_setTransceiverEventStatus(TJA1145FD_PNFDE_NO_PARTIAL_NETWORK_FRAME_ERROR, TJA1145FD_CBS_CAN_BUS_ACTIVE, TJA1145FD_CF_NO_CAN_FAILURE, TJA1145FD_CW_CAN_WAKEUP_EVENT) != NXP_UJA11XX_SUCCESS){
				ret = E_NOT_OK;
			}
	} 

	return ret;
}


/// Returns the status of the CANBUS-Timeout-Flag
/**	This function returns the status of the CAN Bus Silence event (CANBUS-Timeout-Flag) in the Transceiver 
*	Event Status Register. 
*	If the TJA1145 is in low-power mode with selective wake-up function enabled and there is no
*	communication for tSILENCE, the CANBUS-Timeout-Flag (CAN Bus Silence event) shall be set. 
*	The flag is set by the hardware and shall be reset by microcontroller only.
*	
* \author   jh
* \version  1.0
* \date     2013/06/05
* \param	pCbs: CAN BUS Silence Event flag; possible value: TJA1145FD_CBS_NO_CAN_BUS_ACTIVITY	= 1, TJA1145FD_CBS_CAN_BUS_ACTIVE	= 0
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_ReadTrcvTimeoutFlag(TJA1145FD_CAN_Bus_Active_t* pCbs){
	StdReturn_t ret = E_OK;    
	TJA1145FD_Transceiver_Event_Status_Reg_t trcvEv;

	if (TJA1145FD_getTransceiverEventStatus(&trcvEv.TJA1145FD_PNFDE, &trcvEv.TJA1145FD_CBS, &trcvEv.TJA1145FD_CF, &trcvEv.TJA1145FD_CW) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	*pCbs = trcvEv.TJA1145FD_CBS;

	return ret;	
}


/// Clear CANBUS-Timeout-Flag
/**	This function clears the CAN Bus Silence event in the Transceiver Event Status Register 
*	(CANBUS-Timeout-Flag). 
*	If the TJA1145 is in low-power mode with selective wake-up function enabled and there is no
*	communication for tSILENCE, the CANBUS-Timeout-Flag (CAN Bus Silence event) shall be set. 
*	The flag is set by the hardware and shall be reset by microcontroller only.
*	
* \author   jh
* \version  1.0
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_ClearTrcvTimeoutFlag() {
	StdReturn_t ret = E_OK;
	TJA1145FD_Transceiver_Event_Status_Reg_t trcvEv;

	if (TJA1145FD_getTransceiverEventStatus(&trcvEv.TJA1145FD_PNFDE, &trcvEv.TJA1145FD_CBS, &trcvEv.TJA1145FD_CF, &trcvEv.TJA1145FD_CW) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	if (TJA1145FD_setTransceiverEventStatus(trcvEv.TJA1145FD_PNFDE, TJA1145FD_CBSS_CAN_BUS_INACTIVE, trcvEv.TJA1145FD_CF, trcvEv.TJA1145FD_CW) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}

	return ret;
}


/// Returns the status of the CANBUS-Silent-Flag
/**	This function returns the status of the CAN Bus Silence flag in the Transceiver Status
*	Register. 
*	If there is no activity on the bus, the flag is set after tSILENCE expired. If any 
*	activity is detected on the bus, the flag shall be reset automatically by hardware.
*	
* \author   jh
* \version  1.0
* \date     2013/06/05
* \param	pCbss: CAN bus silence status; possible values:	TJA1145FD_CBSS_CAN_BUS_INACTIVE = 1, TJA1145FD_CBSS_CAN_BUS_ACTIVE	= 0
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_ReadTrcvSilenceFlag(TJA1145FD_CAN_Bus_Status_t* pCbss) {
	StdReturn_t ret = E_OK;      
	TJA1145FD_Transceiver_Status_Reg_t trcvSt;

	if (TJA1145FD_getTransceiverStatus(&trcvSt.TJA1145FD_CTS, &trcvSt.TJA1145FD_CPNERR, &trcvSt.TJA1145FD_CPNS, &trcvSt.TJA1145FD_COSCS, &trcvSt.TJA1145FD_CBSS, &trcvSt.TJA1145FD_VCS, &trcvSt.TJA1145FD_CFS) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}
	*pCbss = trcvSt.TJA1145FD_CBSS;

	return ret;
}


/// Check the wake flag status of the TJA1145
/**	This function checks the status of the wake-up flag of the transceiver hardware.
*	This function is called only if selective wake-up function is enabled, TJA1145 has entered 
*	Standby mode and CAN Controller is set to Stopped Mode. It prevents, that the system runs into 
*	a deadlock in case the transceiver signals a wake-up at the RXD pin, but the CAN
*	controller is not yet able to detect this event, as it is still in Stopped Mode and not wakeable.
*	- In case a bus wake-up occurs in between change of the MCU from Normal to Standby Operation, 
*	ECU shall be woken-up again. This is signalled by return value E_NOT_OK.
*	- In case a pin or any other wake-up occurs in between change of the MCU from Normal to Standby Operation,
* in this example software the ECU shall also be woken up. This is signalled by return value E_NOT_OK.
*	
* \author   jh
* \version  1.0
* \date     2013/06/05
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_CheckWakeFlag(){
	StdReturn_t ret = E_OK;
	TJA1145FD_Global_Event_Status_Reg_t ev;

	if (TJA1145FD_getGlobalEventStatus(&ev.TJA1145FD_WPE, &ev.TJA1145FD_TRXE, &ev.TJA1145FD_SYSE) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}

	if ((ev.TJA1145FD_WPE == TJA1145FD_WPE_WAKE_PIN_EVENT_PENDING) || 
		(ev.TJA1145FD_TRXE == TJA1145FD_TRXE_TRANSCEIVER_EVENT_PENDING) || 
		(ev.TJA1145FD_SYSE == TJA1145FD_SYSE_SYSTEM_EVENT_PENDING)){
			ret = E_NOT_OK;
	}

	return E_OK;
}


/// Activate/Deactivate CAN Selective Wake-up in TJA1145
/** This function configures the CPNC bit in the CAN Mode Control Register.
* 
* \author   jh
* \version  1.0
* \date     2013/06/05
* \param    actState: TJA1145 PN activation state; possible values:PN_ENABLED, PN_DISABLED 
* \return	  <b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_SetPNActivationState(CanTrcv_PNActivationType actState) {
	StdReturn_t ret = E_OK;
	TJA1145FD_CAN_Control_Reg_t canCtrl;  	

	if (TJA1145FD_getCANControl(&canCtrl.TJA1145FD_CFDC, &canCtrl.TJA1145FD_PNCOK, &canCtrl.TJA1145FD_CPNC, &canCtrl.TJA1145FD_CMC) != NXP_UJA11XX_SUCCESS){
		ret = E_NOT_OK;
	}

	if (actState == PN_ENABLED){
		if (TJA1145FD_setCANControl(canCtrl.TJA1145FD_CFDC, canCtrl.TJA1145FD_PNCOK, TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_ENABLE, canCtrl.TJA1145FD_CMC) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK;
		}     
	} else {
		if (TJA1145FD_setCANControl(canCtrl.TJA1145FD_CFDC, canCtrl.TJA1145FD_PNCOK, TJA1145FD_CPNC_CAN_SELECTIVE_WAKEUP_DISABLE, canCtrl.TJA1145FD_CMC) != NXP_UJA11XX_SUCCESS){
			ret = E_NOT_OK;
		} 
	}

	return ret;  
}


/// Read current TJA1145 Mode
/** This function returns the current TJA1145 operating mode.
* 
* \author   jh
* \version  1.0
* \date     2013/06/05
* \param    pMode: TJA1145 mode read from Mode Control Register; possible values: CANTRCV_TRCVMODE_SLEEP, CANTRCV_TRCVMODE_STANDBY, CANTRCV_TRCVMODE_NORMAL 
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK
*/
StdReturn_t TJA1145_GetOpMode(CanTrcv_TrcvModeType* pMode){
	StdReturn_t ret = E_OK;
	TJA1145FD_Mode_Control_t mc;       

	if (TJA1145FD_getModeControlReg(&mc) != NXP_UJA11XX_SUCCESS) {
		ret = E_NOT_OK;
	}

	if (mc ==  TJA1145FD_MC_SLEEP_MODE) {
		*pMode = CANTRCV_TRCVMODE_SLEEP;                 
	} else if (mc == TJA1145FD_MC_STANDBY_MODE) {
		*pMode = CANTRCV_TRCVMODE_STANDBY; 
	} else if (mc == TJA1145FD_MC_NORMAL_MODE) {
		*pMode = CANTRCV_TRCVMODE_NORMAL;     
	}  	

	return ret;
}


/// Set TJA1145 Operating Mode
/** This function sets the TJA1145 to the desired operating mode.
* 
* \author   jh
* \version  1.0
* \date     2013/06/05
* \param	mode: mode that shall be entered by TJA1145; possible values: CANTRCV_TRCVMODE_SLEEP, CANTRCV_TRCVMODE_STANDBY, CANTRCV_TRCVMODE_NORMAL 
* \return	<b>StdReturn_t</b>  Function executed successfully or not
*                               possible values: E_OK, E_NOT_OK

*/
StdReturn_t TJA1145_SetOpMode(CanTrcv_TrcvModeType mode){
	StdReturn_t ret = E_OK;

	switch (mode) {
	  case (CANTRCV_TRCVMODE_SLEEP):
		  if (TJA1145FD_setModeControlReg(TJA1145FD_MC_SLEEP_MODE) != NXP_UJA11XX_SUCCESS){
			  ret = E_NOT_OK;
		  }
		  break;
	  case (CANTRCV_TRCVMODE_STANDBY):
		  if (TJA1145FD_setModeControlReg(TJA1145FD_MC_STANDBY_MODE) != NXP_UJA11XX_SUCCESS){
			  ret = E_NOT_OK;
		  }
		  break;
	  default:
		  if (TJA1145FD_setModeControlReg(TJA1145FD_MC_NORMAL_MODE) != NXP_UJA11XX_SUCCESS){
			  ret = E_NOT_OK;
		  }
		  break;         
	}

	return ret;
}