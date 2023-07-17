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

#include "uC_Specific_Functions.h"
#include "NXP_UJA11XX_defines.h"
#include "NXP_TJA1145FD_functions.h"          

extern void InitScheduler(void);

/**
* \brief SPI transmission routine
* \todo implement this function with your microcontroller specific code
*	- Disable interrupts
*	- SPI_DATA_REG = tx;
*	- Wait until transition is done
*	- tx = SPI_DATA_REG
*	- Enable interrupts
* Remark: Furthermore, this function should not only send data via SPI, it should also check, if the SPI access was successful. 
* Therefore, after the 1st SPI access, a 2nd SPI read access is performed to ensure that the configurations has been 
* changed or rather the 1st read values have been correct.  
*
* \param data A pointer to the data which shall be transmitted by the SPI interface
* \param length Number of data Bytes which shall be transmitted by the SPI interface
* \param mask Mask of Bits interesting for the consistency check
* \param type Type (write/read/interrupt) of the SPI access 
* \return <b>NXP_UJA11XX_Error_Code_t</b> possible values: NXP_UJA11XX_ERROR_WRITE_FAIL = 0, NXP_UJA11XX_ERROR_READ_FAIL = 1, NXP_UJA11XX_ERROR_SPI_HW_FAIL = 2, NXP_UJA11XX_SUCCESS = 3
*/
NXP_UJA11XX_Error_Code_t SPI_Send(Byte* data, NXP_UJA11XX_SPI_Msg_Length_t length, Byte mask, NXP_UJA11XX_Access_t type) {

	// Insert your microcontroller specific code here
	// e.g.
	// First SPI access:
	// - Disable interrupts
	// - SPI_DATA_REG = tx;
	// - Wait until transision done
	// - tx = SPI_DATA_REG
	// - Enable interrupts
	// If no MTP register is accessed, read a second time:
	// - Disable interrupts
	// - SPI_DATA_REG = tx;
	// - Wait until transision done
	// - tx = SPI_DATA_REG
	// - Enable interrupts	
	// Check of consistency:
	// - In case of a write access: 
	// -- If address bytes of both SPI accesses and the data byte(s) sent in 1st and read back in 2nd SPI access are similar, SPI access was successful (NXP_UJA11XX_SUCCESS).
	// -- Else if address and data byte(s) read back are '0x00' or '0xFF', NXP_UJA11XX_ERROR_SPI_HW_FAIL is returned.
	// -- Else SPI write access was not succesful and NXP_UJA11XX_ERROR_WRITE_FAIL is returned. 
	// - In case of an read access: 
	// -- If address bytes and the data byte(s) of both SPI read accesses are similar, SPI access was successful (NXP_UJA11XX_SUCCESS).
	// -- Else SPI read access was not succesful and NXP_UJA11XX_ERROR_READ_FAIL is returned.
	// - In case of an access to an interrupt register:
	// -- If address bytes of both SPI accesses are similar and the according interrupt bit(s) are cleared in 2nd SPI access data, SPI access was successful.
	// -- Else SPI write access was not succesful and NXP_UJA11XX_ERROR_WRITE_FAIL is returned.

	return 3;
}

/**
* \brief Init routine of the microcontroller
* \todo implement this function with your microcontroller specific code
*	- Configure SPI with MSB first, shifting on rising and sampling on falling edge
*	- Configure timer interrupt
*	- Configure external interrupt, edge sensitive, interrupt on falling edge
*	- Configure internal CAN Protocol Engine (PE)
*	- Configure Serial Communication Interfaces for LIN communication
*	- Configure internal Analog/Digital Converter (ADC)
*/
void InitMicrocontroller(void){
	// Insert your microcontroller specific code here
	// e.g.
	// Configure SPI with 16 Bit, MSB first, shifting on rising and sampling on falling edge
	// Configure timer interrupt
	// Configure external interrupt, edge sensitive, interrupt on falling edge
	// Configure CAN PE
	// Configure ADC

}

/**
* \brief Check if a flash request is pending
* \todo implement this function with your microcontroller specific code
*	- Read dedicated register in Flash Memory Controller
* \return indicates if a flash update request is pending
*	- 1 = A Flash update is required
*	- 0 = No Flash update request pending
*/
Byte FlashProgramming(void){    
	// Insert your microcontroller specific code here
	// e.g.
	// Read dedicated register in Flash Memory Controller etc.

	return 0;
}

/**
* \brief Disable microcontroller oscillator
* \todo implement this function with your microcontroller specific code
*	- stop asm command 
*/
void EnterMcuStopMode(void)
{
	// Insert your microcontroller specific code here
	// e.g. stop asm command
} 


/**
* \brief Stop CAN transmission in application 
* \todo implement this function with your microcontroller specific code
*	- abort all tasks sending data via CAN
* \return indicates if Abort Transmission was successful
*	- 1 = All CAN transmission aborted
*	- 0 = Abort of all CAN transmissions failed
*/
Byte AbortTransmissionCAN(void){
	// Insert your microcontroller specific code here

	return 0;
}

/**
* \brief CAN PE is stopped (wake-up disabled)
* \todo implement this function with your microcontroller specific code
*	- Disable CAN PE completely
* \return indicates if Abort Transmission was successful
*	- 1 = CAN PE entered Stop Mode
*	- 0 = CAN PE has not entered Stop Mode
*/
Byte CANStopMode(void){
	// Insert your microcontroller specific code here
	// e.g. Disable CAN PE  with wake-up disabled

	return 0;
}

/**
* \brief CAN PE enters Sleep Mode (wake-up enabled)
* \todo implement this function with your microcontroller specific code
*	- Disable CAN PE completely or abort transmission
* \return indicates if Abort Transmission was successful
*	- 1 = CAN PE entered Sleep Mode
*	- 0 = CAN PE has not entered Sleep Mode
*/
Byte CANSleepMode(void){
	// Insert your microcontroller specific code here
	// e.g. Disable CAN PE  with wake-up enabled

	return 0;
}

/**
* \brief Enable transmissions of the CAN PE
* \todo implement this function with your microcontroller specific code
*	- Enable CAN PE completely or enable transmission path
* \return indicates if Enable Transmission was successful
*	- 1 = CAN PE is now able to transmit new messages
*	- 0 = Enabling of transmissions failed
*/
Byte EnableTransmissionCAN(void){
	// Insert your microcontroller specific code here
	// e.g. Enable CAN PE

	return 0;
}



/**
* \brief Read GPIO port configured as input port
* \todo implement this function with your microcontroller specific code
*	- Read GPIO port
* \return Port input value
*/
Byte ScanPort(void){
	// Insert your microcontroller specific code here
	// e.g. Read GPIO port and return value
	return 1;
}

/**
* \brief Disable global timebase
* \todo implement this function with your microcontroller specific code
*	- Disable timer
* \return indicates if Scheduler Disable was successful
*	- 1 = Timer disabled
*	- 0 = Timer disable failed
*/
Byte Scheduler_Disable(void){
	// Insert your microcontroller specific code here
	// e.g. disable global timer 

	return 0;
}

/**
* \brief Enable global time base
* \todo implement this function with your microcontroller specific code
*	- Enable timer
* \return indicates if Scheduler Enable was successful
*	- 1 = Timer enabled
*	- 0 = Timer enable failed
*/
Byte Scheduler_Enable(void){
	// Insert your microcontroller specific code here

	return 0;
}

/**
* \brief Get RXD CAN value
* \todo implement this function with your microcontroller specific code
* \return RXD CAN value
*	- 1 = RXD CAN is high
*	- 0 = RXD CAN is low
*/
Byte RXDC_GetValue(){
	// Insert your microcontroller specific code here
	// e.g. return value of port pin connected to UJA1164 RXD pin 
	return 1;
}


/**
* \brief Read Port Pin that gives the start signal for MTP programmg  
* \todo implement this function with your microcontroller specific code
* \return Port pin value
*	- 1 = port pin is high (default): wait for start signal
*	- 0 = port pin is low: start programming MTP
*/
Byte MtpvnProgStart(void){
	// Insert your microcontroller specific code here

	return 1;
}


/**
* \brief Read Port Pin used for control SDMC configuration during MTP programming and watchdog triggering during normal operation  
* \todo implement this function with your microcontroller specific code
* \return Port pin value
*	- 1 = port pin is high (default): During MTP programming, SDMC = 0; During Normal Operation: "Normal" WD triggering requested
*	- 0 = port pin is low: During MTP programming, SDMC = 1; During Normal Operation: "Debug" WD triggering requested (autonomous mode) 
*/
Byte WdEmulation(void){
	// Insert your microcontroller specific code here

	return 1;
}


/**
* \brief Set Port Pin on high level used for control a LED that shows, if SBC is in Normal Mode or not 
* \todo implement this function with your microcontroller specific code
*/
void SetNormalModeLed(void) {
	// Insert your microcontroller specific code here

}


/**
* \brief Set Port Pin on low level used for control a LED that shows, if SBC is in Normal Mode or not 
* \todo implement this function with your microcontroller specific code
*/
void ClearNormalModeLed(void) {
	// Insert your microcontroller specific code here

}


/**
* \brief Toggle Port Pin used for signalling a Watchdog trigger
* \todo implement this function with your microcontroller specific code
*/
void ToggleWdTriggerLed(void) {
	// Insert your microcontroller specific code here

}