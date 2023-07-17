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

/** \mainpage NXP TJA1145FD Example Application
*   This example project, attached to the TJA1145 Application Hints, reflects the software flow discussed 
*   in the Applications Hints. Moreover, it shows how to program the TJA1145 in more detail.
*   It demonstrates how to:
*   - Program the TJA1145 MTP
*   -	Initialize the TJA1145
*   -	Change operation modes 
*   -	Handle events etc.
*
*   On the other hand this example project includes some application specific code which should build the frame
*   for the TJA1145 related actions. Furthermore, it includes a microcontroller abstraction layer that makes 
*   this example code platform (microcontroller) independent. For that reason this example project consists 
*   of three main parts:
*   - NXP TJA1145FD specific functions. See File \link NXP_TJA1145FD_Functions.c \endlink for details. This file contains the TJA1145FD
*   low level drivers and can be used as it is, even for different applications.
*   - Example application specific functions. See File \link TJA1145FD_Application_Specific_Functions.c \endlink for details. 
*   This file includes application specific code and is for demonstration purpose only.
*   - Microcontroller specific functions (Microcontroller abstraction layer). See File \link uC_Specific_Functions.h \endlink for details. 
*   This file must be implemented with the microcontroller specific code.
*/     

#include "TJA1145FD_Application_Specific_Functions.h"

/// This variable indicates if an Event is pending
/** 
*   - 0 No event pending
*   - 1 Event pending
*/
volatile bool PendingEvent;

/// This variable indicates if a check of the transceiver status is required
/**
*   - 0 everything fine
*   - 1 check of transceiver status required
*/
volatile Byte CheckTrcvStatus;

/// This is the data structure/scheduler for requested application tasks
/** 
* CHANGE_TO_SLEEP, CHANGE_TO_STANDBY, CHANGE_TO_NORMAL, EVENT_HANDLING, TRIGGER_WATCHDOG,
*	POLL_TRCV_STATUS, PORT_SUPERVISION can be scheduled
*/
PendingTask_t ApplTask[MAXTASKNO];

/// This variable indicates the write pointer variable of application task queue
volatile int ApplTaskPt_write;

/// This variable indicates the read pointer variable of application task queue
volatile int ApplTaskPt_read;

/// This is the data strcuture storing the failure entries
enum FailureEntries FailureMemory[MAXERRENTR];

/// This variable indicates the write pointer variable of failure memory
volatile int FailMemPt_write;

/// The variable indicates the device type	
/**
* NXP_TJA1145 = 1, NXP_TJA1145FD = 2, NXP_UJA1164 = 3, NXP_UJA1167 = 4, NXP_UJA1167VX = 5, NXP_UJA1168 = 6,
* NXP_UJA1168FD = 7, NXP_UJA1168FDVX = 8, NXP_UJA1168VX = 9, NXP_UNKNOWN = 0,  
*/ 
volatile Device_t DeviceType;

/// Global timer overflow counter variable. Increases every 1ms. Counts up to 3 and starts from the beginning
volatile int OverflowCnt;

/// This variable indicates, if the Startup operation has been finished
/** 
*   - FALSE Startup Operation not finished
*   - TRUE Startup operation finished
*/
volatile bool StartupReady;

/// Reason for last wake-up
/**
* CANTRCV_WU_BY_BUS = 0, CANTRCV_WU_BY_PIN = 1, CANTRCV_WU_ERROR = 2, CANTRCV_WU_INTERNALLY = 3, CANTRCV_WU_NOT_SUPPORTED = 4,
*	CANTRCV_WU_POWER_ON = 5, CANTRCV_WU_RESET = 6, CANTRCV_WU_BY_SYSERR = 7
*/
volatile CanTrcv_TrcvWakeupReasonType WuReason;


/// TJA1145 Main Function - Entry point of the application
/** 
*   At first the Main function sets up the operation (StartupOperation()). Afterwards it is decided, 
*   which application shall be started (Default, SW Development Mode, Diagnostic Mode in case of an error during startup).
*   In this example the Default and the SDM application	permanently check, if a new task is scheduled in the 
*	application task queue, which should be started. Possible tasks are: change to sleep mode, change to standby mode, 
*	change to normal mode, event handling, WD triggering, poll transceiver status, poll uC port status, poll Wake pin, 
*	trigger watchdog and reconfigure partial networking. 
*   If a task is pending, the according function is processed. 
*   The example software is build in that way that every operation is performed within the main
*   task context. That means that e.g. events will only schedule a Event Handling Task
*   in the application task queue and the application task queue is processed within the main task. 
*
* \author	jh
* \version	1.0 
* \date		2013/06/05
*/
void main(){
	/* Write your local variable definition here */
	StdReturn_t ret; 
	PendingTask_t task;

	// Operation set-up   
	ret = StartupOperation(); 

	if (ret == E_OK) {
		// Default Application Mode
		// Main loop --> process tasks in scheduler queue
		while (TRUE) {

			// If en event has occured in Low Power Mode, this is handled immediately
			if (PendingEvent == TRUE){
				PendingEvent = FALSE;
				(void) RxdLowHandling();
			}

			task = GetNextTask();    	  
			switch (task){      
			case CHANGE_TO_SLEEP:
				(void) ChangeToSleepOperation();
				break;     

			case CHANGE_TO_STANDBY:
				(void) ChangeToStandbyOperation();
				break;  

			case CHANGE_TO_NORMAL:
				(void) ChangeToNormalOperation();
				break;

			case EVENT_HANDLING:
				(void) EventHandling();				
				break;

			case POLL_TRCV_STATUS:
				(void) PollTransceiverStatus();
				break;

			case PORT_SUPERVISION:
				(void) PortSupervisor();
				break;

			case POLL_WAKE:
				(void) WakeSupervisor();
				break;

			case CFG_PARTIAL_NETWORKING:
				(void) ConfigurePartialNetworking();
				break;		  

			default:
				break;
			}
		}  	

	} else {
		// start Diagnostic Application Mode  
		for(;;){}        
	}   
} 

