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

#ifndef __TJA1145VX_Application_Specific_Functions_h
#define __TJA1145VX_Application_Specific_Functions_h

#include "NXP_TJA1145FD_Sim.h" 

// Max. number of task in TJA1145FD_ApplTask queue
#define MAXTASKNO 256

// Max. number of error entries in failure memory
#define MAXERRENTR 256

// Sleep mode configuration on input ports
#define PORTMASK_SLEEP 0x10

// Normal mode configuration on input ports
#define PORTMASK_NORMAL 0x40

// Cylic wake configuration on input ports
#define PORTMASK_STANDBY 0x20

// Supported pending tasks in application queue
typedef enum PendingTask {
	NO_OPERATION = 0,
	CHANGE_TO_SLEEP = 1,
	CHANGE_TO_STANDBY = 2,
	CHANGE_TO_NORMAL = 3,     
	EVENT_HANDLING = 4,
	POLL_TRCV_STATUS = 6,
	POLL_WAKE = 7,
	PORT_SUPERVISION = 8,
	CFG_PARTIAL_NETWORKING = 9
} PendingTask_t;

// Supported error entries in failure memory
typedef enum FailureEntries {                    // to be updated
	EMPTY = 0,
	DIAGNOSTIC_WAKEUP_SLEEP = 1,
	LEAVING_OVERLOAD = 4,
	SPI_FAILURE = 8,
	OVERTEMP_WARNING = 9,
	BUFFER_OVERFLOW = 10,
	CAN_FAILURE = 18	
} FailureEntry_t;

// Supported device types
typedef enum DeviceIdentification {
	NXP_TJA1145 = 1,
	NXP_TJA1145FD = 2,
	NXP_UJA1164 = 3,
	NXP_UJA1167 = 4,
	NXP_UJA1167VX = 5,
	NXP_UJA1168 = 6,
	NXP_UJA1168FD = 7,
	NXP_UJA1168FDVX = 8,
	NXP_UJA1168VX = 9,
	NXP_UNKNOWN = 0,              	                                                 
} Device_t;

// be care of INCLUDE_FROM_EXTERNAL_TJA1145FD_APPLICATION_SPECIFIC_FUNCTIONS
#if defined(INCLUDE_FROM_EXTERNAL_TJA1145FD_APPLICATION_SPECIFIC_FUNCTIONS)
#define StdReturn_t Std_ReturnType 
#else
// Supported standard return values
typedef enum {
	E_OK = 0,
	E_NOT_OK = 1
} StdReturn_t;

/**** types related to PN Autosar R4.1 ****/
typedef enum CanTrcv_TrcvWakeupReason {
	CANTRCV_WU_ERROR = 0,
        CANTRCV_WU_BY_BUS = 1,
	CANTRCV_WU_BY_PIN = 2,
	CANTRCV_WU_INTERNALLY = 3,
	CANTRCV_WU_NOT_SUPPORTED = 4,
	CANTRCV_WU_POWER_ON = 5,
	CANTRCV_WU_RESET = 6,
	CANTRCV_WU_BY_SYSERR = 7, 
	CANTRCV_WU_BY_BUS_WUF = 8,
	CANTRCV_WU_BY_BUS_WUP = 9,
} CanTrcv_TrcvWakeupReasonType;

typedef enum CanTrcv_TrcvMode {
	CANTRCV_TRCVMODE_NORMAL,
	CANTRCV_TRCVMODE_SLEEP,
	CANTRCV_TRCVMODE_STANDBY
} CanTrcv_TrcvModeType;
#endif

typedef enum CanTrcv_PNActivation {
	PN_DISABLED = 0,
	PN_ENABLED = 1,
} CanTrcv_PNActivationType;


// see TJA1145_Application_Specific_Functions.c for documentation
void SchedulerOnTimerOverflow(Byte CanTrcvIndex); 

// see TJA1145_Application_Specific_Functions.c for documentation
Device_t GetDeviceType(Byte CanTrcvIndex);            

// see TJA1145_Application_Specific_Functions.c for documentation
void InitApplication(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t StartupOperation(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t InitTJA1145(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t CheckFsmStatus(Byte CanTrcvIndex); 

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t ChangeToSleepOperation(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t ChangeToStandbyOperation(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t ChangeToNormalOperation(Byte CanTrcvIndex);        

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t EventHandling(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t RxdLowHandling(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void PollTransceiverStatus(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void PortSupervisor(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void WakeSupervisor(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_SetPnIdentifier(Byte CanTrcvIndex, Word id, TJA1145FD_Identifier_Format_t idFormat);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_SetPnIdMask(Byte CanTrcvIndex, Word mask, TJA1145FD_Identifier_Format_t idFormat);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t ConfigurePartialNetworking(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_SPIF_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_OTW_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_PO_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_PNFDE_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_CW_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_CF_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_CBS_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_WPF_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_WPR_ServiceRoutine(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void RXDLow_ISR(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void Timer_ISR(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void StopCAN_TX(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void ResumeCAN_TX(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
Byte EnterFlashOperation(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void AddToTJA1145FD_FailureMemory(Byte CanTrcvIndex, FailureEntry_t data);          

// see TJA1145_Application_Specific_Functions.c for documentation
void InitScheduler(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
void AddTaskToScheduler(Byte CanTrcvIndex, PendingTask_t);

// see TJA1145_Application_Specific_Functions.c for documentation
PendingTask_t GetNextTask(Byte CanTrcvIndex);



/**** APIs related to PN Autosar R4.1 ****/

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_GetWuReason(Byte CanTrcvIndex, CanTrcv_TrcvWakeupReasonType* pReason);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_ClearTrcvWufFlag(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_ReadTrcvTimeoutFlag(Byte CanTrcvIndex, TJA1145FD_CAN_Bus_Active_t* pCbs);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_ClearTrcvTimeoutFlag(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_ReadTrcvSilenceFlag(Byte CanTrcvIndex, TJA1145FD_CAN_Bus_Status_t* pCbss);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_CheckWakeFlag(Byte CanTrcvIndex);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_SetPNActivationState(Byte CanTrcvIndex, CanTrcv_PNActivationType actState);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_SetOpMode(Byte CanTrcvIndex, CanTrcv_TrcvModeType Mode);

// see TJA1145_Application_Specific_Functions.c for documentation
StdReturn_t TJA1145_GetOpMode(Byte CanTrcvIndex, CanTrcv_TrcvModeType* pMode);

#endif

