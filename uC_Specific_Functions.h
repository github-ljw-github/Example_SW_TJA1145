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

#ifndef __uC_Specific_Functions_h
#define __uC_Specific_Functions_h  

#include "NXP_UJA11XX_defines.h"

/**
*	\brief Enable interrupts 
*	\todo implement this function with your microcontroller specific code
*	- Enable Interrupts (Assemby command)
*/
#define __EI() {}

/**
*	\brief Disable interrupts 
*	\todo implement this function with your microcontroller specific code
*	- Disable Interrupts (Assemby command)
*/
#define __DI() {}    

// see uC_Specific_Functions.c for documentation
NXP_UJA11XX_Error_Code_t SPI_Send(Byte CanTrcvIndex, Byte* data, NXP_UJA11XX_SPI_Msg_Length_t length, Byte mask ,NXP_UJA11XX_Access_t type);

// see uC_Specific_Functions.c for documentation
void InitMicrocontroller(Byte CanTrcvIndex); 

// see uC_Specific_Functions.c for documentation
void EnterMcuStopMode(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte FlashProgramming(Byte CanTrcvIndex);   

// see uC_Specific_Functions.c for documentation
Byte AbortTransmissionCAN(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte CANStopMode(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte CANSleepMode(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte EnableTransmissionCAN(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte ScanPort(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte Scheduler_Disable(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte Scheduler_Enable(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte RXDC_GetValue(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte MtpvnProgStart(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
Byte WdEmulation(Byte CanTrcvIndex);   

// see uC_Specific_Functions.c for documentation
void SetNormalModeLed(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
void ClearNormalModeLed(Byte CanTrcvIndex);

// see uC_Specific_Functions.c for documentation
void ToggleWdTriggerLed(Byte CanTrcvIndex);

#endif
