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

// $id:$
// XML Version: V1.1  Software Version: V1.1  Date: 04/19/2013  Time: 15:12

//--------------------------------------------------------------------------------
// pre-processor directive
#ifndef NXP_UJA11XX_DEFINES_H
#define NXP_UJA11XX_DEFINES_H

#define TRUE 1
#define FALSE 0
#define MAXTJA11XXNO 1

//--------------------------------------------------------------------------------
// general enumerations
//--------------------------------------------------------------------------------
// Data type which enables exchangeability of code with simulation environment
typedef unsigned char Byte;
typedef unsigned int Word;
typedef unsigned char bool;

//---------------------------------------------------
// access identificator (used for address generation and SPI function)
typedef enum
{
	NXP_UJA11XX_WRITE     = 0,
	NXP_UJA11XX_READ      = 1,
	NXP_UJA11XX_INTERRUPT = 2
}NXP_UJA11XX_Access_t;
//---------------------------------------------------
// function error code return value
typedef enum
{
	NXP_UJA11XX_ERROR_WRITE_FAIL,
	NXP_UJA11XX_ERROR_READ_FAIL,
	NXP_UJA11XX_ERROR_SPI_HW_FAIL,
	NXP_UJA11XX_SUCCESS
}NXP_UJA11XX_Error_Code_t;
//---------------------------------------------------
// SPI transmission length
typedef enum
{
	NXP_UJA11XX_SPI_MSG_LENGTH_16 = 2,
	NXP_UJA11XX_SPI_MSG_LENGTH_24 = 3,
	NXP_UJA11XX_SPI_MSG_LENGTH_32 = 4,
}NXP_UJA11XX_SPI_Msg_Length_t;

//--------------------------------------------------------------------------------
#endif

