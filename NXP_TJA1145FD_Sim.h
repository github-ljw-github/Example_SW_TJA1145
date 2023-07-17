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
#ifndef NXP_TJA1145FD_SIM_H
#define NXP_TJA1145FD_SIM_H

//--------------------------------------------------------------------------------
// function header include
#include "NXP_TJA1145FD_Functions.h"

//--------------------------------------------------------------------------------
// register depending structures
//--------------------------------------------------------------------------------
// register 0x01
typedef struct
{
	TJA1145FD_Mode_Control_t	TJA1145FD_MC;
}TJA1145FD_Mode_Control_Reg_t;
//---------------------------------------------------
// register 0x03
typedef struct
{
	TJA1145FD_Forced_Sleep_Mode_Status_t	TJA1145FD_FSMS;
	TJA1145FD_Over_Temperature_Warning_Status_t	TJA1145FD_OTWS;
	TJA1145FD_Normal_Mode_Status_t	TJA1145FD_NMS;
}TJA1145FD_Main_Status_Reg_t;
//---------------------------------------------------
// register 0x04
typedef struct
{
	TJA1145FD_Over_Temperature_Warning_Enable_t	TJA1145FD_OTWE;
	TJA1145FD_SPI_Failure_Detect_Enable_t	TJA1145FD_SPIFE;
}TJA1145FD_System_Event_Enable_Reg_t;
//---------------------------------------------------
// register 0x06
typedef struct
{
	TJA1145FD_RAM_Memory_0700_t	TJA1145FD_GPM0;
}TJA1145FD_Memory_0_Reg_t;
//---------------------------------------------------
// register 0x07
typedef struct
{
	TJA1145FD_RAM_Memory_0815_t	TJA1145FD_GPM1;
}TJA1145FD_Memory_1_Reg_t;
//---------------------------------------------------
// register 0x08
typedef struct
{
	TJA1145FD_RAM_Memory_1623_t	TJA1145FD_GPM2;
}TJA1145FD_Memory_2_Reg_t;
//---------------------------------------------------
// register 0x09
typedef struct
{
	TJA1145FD_RAM_Memory_2431_t	TJA1145FD_GPM3;
}TJA1145FD_Memory_3_Reg_t;
//---------------------------------------------------
// register 0x0A
typedef struct
{
	TJA1145FD_Lock_Control_6_t	TJA1145FD_LK6C;
	TJA1145FD_Lock_Control_5_t	TJA1145FD_LK5C;
	TJA1145FD_Lock_Control_4_t	TJA1145FD_LK4C;
	TJA1145FD_Lock_Control_3_t	TJA1145FD_LK3C;
	TJA1145FD_Lock_Control_2_t	TJA1145FD_LK2C;
	TJA1145FD_Lock_Control_1_t	TJA1145FD_LK1C;
	TJA1145FD_Lock_Control_0_t	TJA1145FD_LK0C;
}TJA1145FD_Lock_Control_Reg_t;
//---------------------------------------------------
// register 0x20
typedef struct
{
	TJA1145FD_CAN_FD_tolerance_t	TJA1145FD_CFDC;
	TJA1145FD_Partial_Network_Config_t	TJA1145FD_PNCOK;
	TJA1145FD_CAN_Selective_WakeUp_t	TJA1145FD_CPNC;
	TJA1145FD_CAN_Mode_Selection_t	TJA1145FD_CMC;
}TJA1145FD_CAN_Control_Reg_t;
//---------------------------------------------------
// register 0x22
typedef struct
{
	TJA1145FD_CAN_Transmitter_Status_t	TJA1145FD_CTS;
	TJA1145FD_Partial_Network_Error_t	TJA1145FD_CPNERR;
	TJA1145FD_Partial_Network_Config_Error_t	TJA1145FD_CPNS;
	TJA1145FD_Partial_Network_Osc_t	TJA1145FD_COSCS;
	TJA1145FD_CAN_Bus_Status_t	TJA1145FD_CBSS;
	TJA1145FD_VCAN_Status_t	TJA1145FD_VCS;
	TJA1145FD_Dominant_Timeout_Event_t	TJA1145FD_CFS;
}TJA1145FD_Transceiver_Status_Reg_t;
//---------------------------------------------------
// register 0x23
typedef struct
{
	TJA1145FD_CAN_Bus_Silence_Detect_t	TJA1145FD_CBSE;
	TJA1145FD_CAN_Failure_Detect_t	TJA1145FD_CFE;
	TJA1145FD_CAN_WakeUp_Detect_t	TJA1145FD_CWE;
}TJA1145FD_Transceiver_Event_Enable_Reg_t;
//---------------------------------------------------
// register 0x26
typedef struct
{
	TJA1145FD_CAN_Data_Rate_t	TJA1145FD_CDR;
}TJA1145FD_Data_Rate_Reg_t;
//---------------------------------------------------
// register 0x27
typedef struct
{
	TJA1145FD_CAN_ID0700_t	TJA1145FD_ID0700;
}TJA1145FD_CAN_Identifier_0_Reg_t;
//---------------------------------------------------
// register 0x28
typedef struct
{
	TJA1145FD_CAN_ID1508_t	TJA1145FD_ID1508;
}TJA1145FD_CAN_Identifier_1_Reg_t;
//---------------------------------------------------
// register 0x29
typedef struct
{
	TJA1145FD_CAN_ID2318_t	TJA1145FD_ID2318;
	TJA1145FD_CAN_ID1716_t	TJA1145FD_ID1716;
}TJA1145FD_CAN_Identifier_2_Reg_t;
//---------------------------------------------------
// register 0x2A
typedef struct
{
	TJA1145FD_CAN_ID2824_t	TJA1145FD_ID2824;
}TJA1145FD_CAN_Identifier_3_Reg_t;
//---------------------------------------------------
// register 0x2B
typedef struct
{
	TJA1145FD_CAN_M0700_t	TJA1145FD_M0700;
}TJA1145FD_CAN_Mask_0_Reg_t;
//---------------------------------------------------
// register 0x2C
typedef struct
{
	TJA1145FD_CAN_M1508_t	TJA1145FD_M1508;
}TJA1145FD_CAN_Mask_1_Reg_t;
//---------------------------------------------------
// register 0x2D
typedef struct
{
	TJA1145FD_CAN_M2318_t	TJA1145FD_M2318;
	TJA1145FD_CAN_M1716_t	TJA1145FD_M1716;
}TJA1145FD_CAN_Mask_2_Reg_t;
//---------------------------------------------------
// register 0x2E
typedef struct
{
	TJA1145FD_CAN_M2824_t	TJA1145FD_M2824;
}TJA1145FD_CAN_Mask_3_Reg_t;
//---------------------------------------------------
// register 0x2F
typedef struct
{
	TJA1145FD_Identifier_Format_t	TJA1145FD_IDE;
	TJA1145FD_Partial_Network_Data_Mask_t	TJA1145FD_PNDM;
	TJA1145FD_CAN_Data_Length_t	TJA1145FD_DLC;
}TJA1145FD_Frame_Control_Reg_t;
//---------------------------------------------------
// register 0x4B
typedef struct
{
	TJA1145FD_Wake_Pin_Status_t	TJA1145FD_WPVS;
}TJA1145FD_Wake_Status_Reg_t;
//---------------------------------------------------
// register 0x4C
typedef struct
{
	TJA1145FD_Wake_Pin_Rising_Edge_Detect_t	TJA1145FD_WPRE;
	TJA1145FD_Wake_Pin_Falling_Edge_Detect_t	TJA1145FD_WPFE;
}TJA1145FD_Wake_Pin_Enable_Reg_t;
//---------------------------------------------------
// register 0x60
typedef struct
{
	TJA1145FD_Wake_Pin_Event_t	TJA1145FD_WPE;
	TJA1145FD_Transceiver_Event_t	TJA1145FD_TRXE;
	TJA1145FD_System_Event_t	TJA1145FD_SYSE;
}TJA1145FD_Global_Event_Status_Reg_t;
//---------------------------------------------------
// register 0x61
typedef struct
{
	TJA1145FD_Power_On_t	TJA1145FD_PO;
	TJA1145FD_Over_Temperature_Warning_t	TJA1145FD_OTW;
	TJA1145FD_SPI_Failure_t	TJA1145FD_SPIF;
}TJA1145FD_System_Event_Status_Reg_t;
//---------------------------------------------------
// register 0x63
typedef struct
{
	TJA1145FD_Partial_Network_Frame_Detect_t	TJA1145FD_PNFDE;
	TJA1145FD_CAN_Bus_Active_t	TJA1145FD_CBS;
	TJA1145FD_CAN_Failure_t	TJA1145FD_CF;
	TJA1145FD_CAN_WakeUp_t	TJA1145FD_CW;
}TJA1145FD_Transceiver_Event_Status_Reg_t;
//---------------------------------------------------
// register 0x64
typedef struct
{
	TJA1145FD_Rising_Wake_Pin_Event_t	TJA1145FD_WPR;
	TJA1145FD_Falling_Wake_Pin_Event_t	TJA1145FD_WPF;
}TJA1145FD_Wake_Pin_Event_Reg_t;
//---------------------------------------------------
// register 0x68
typedef struct
{
	TJA1145FD_Data_Mask_0_Config_t	TJA1145FD_DM0;
}TJA1145FD_Data_Mask_0_Reg_t;
//---------------------------------------------------
// register 0x69
typedef struct
{
	TJA1145FD_Data_Mask_1_Config_t	TJA1145FD_DM1;
}TJA1145FD_Data_Mask_1_Reg_t;
//---------------------------------------------------
// register 0x6A
typedef struct
{
	TJA1145FD_Data_Mask_2_Config_t	TJA1145FD_DM2;
}TJA1145FD_Data_Mask_2_Reg_t;
//---------------------------------------------------
// register 0x6B
typedef struct
{
	TJA1145FD_Data_Mask_3_Config_t	TJA1145FD_DM3;
}TJA1145FD_Data_Mask_3_Reg_t;
//---------------------------------------------------
// register 0x6C
typedef struct
{
	TJA1145FD_Data_Mask_4_Config_t	TJA1145FD_DM4;
}TJA1145FD_Data_Mask_4_Reg_t;
//---------------------------------------------------
// register 0x6D
typedef struct
{
	TJA1145FD_Data_Mask_5_Config_t	TJA1145FD_DM5;
}TJA1145FD_Data_Mask_5_Reg_t;
//---------------------------------------------------
// register 0x6E
typedef struct
{
	TJA1145FD_Data_Mask_6_Config_t	TJA1145FD_DM6;
}TJA1145FD_Data_Mask_6_Reg_t;
//---------------------------------------------------
// register 0x6F
typedef struct
{
	TJA1145FD_Data_Mask_7_Config_t	TJA1145FD_DM7;
}TJA1145FD_Data_Mask_7_Reg_t;
//---------------------------------------------------
// register 0x7E
typedef struct
{
	TJA1145FD_Device_ID_t	TJA1145FD_IDS;
}TJA1145FD_Identification_Reg_t;
//---------------------------------------------------
#endif

