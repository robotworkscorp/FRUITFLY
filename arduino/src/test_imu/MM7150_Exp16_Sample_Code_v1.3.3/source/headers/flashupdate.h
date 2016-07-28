/*****************************************************************************
* © 2014 Microchip Technology Inc. and its subsidiaries.
* You may use this software and any derivatives exclusively with
* Microchip products.
* THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".
* NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE,
* INCLUDING ANY IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY,
* AND FITNESS FOR A PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP
* PRODUCTS, COMBINATION WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION.
* IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE,
* INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND
* WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS
* BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.
* TO THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL
* CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF
* FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
* MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE
* OF THESE TERMS.
*****************************************************************************/

/** @file  flashupdate.h
*   Header file for flasupdate functions
*****************************************************************************
*   MM7150 with Explorer 16 Development Board Sample Code header file
*
*   Company : Microchip Technology Inc.
*
*   File name : flashupdate.h
*
*   Summary :  Include header file for MM7150 demo code 
*
*   Revisions : 0.0 2-04-15 C21674  - Initial version created
******************************************************************************/

#ifndef FLASHUPDATE_H
#define	FLASHUPDATE_H

#ifdef	__cplusplus
extern "C" {
#endif

//****************************************************************************
//****************************************************************************
//  Section : Defines
//****************************************************************************
//****************************************************************************

#define GET_OPCODE                  0x02
#define FLASH_UPDATE_RPT_ID         0xE
#define FLASH_UPDATE_RESET_CMD      0x55
#define FLASH_UPDATE_BLDR_INFO_CMD  0xAA
#define LABEL_INFO_INDEX            15
#define FLASH_GET_INFO_CMD			0x0
#define FLASH_INFO_CMD              0x1
#define FLASH_WRITE_CMD             0x3
#define FLASH_READ_CMD              0x4
#define FLASH_WRITE_SECTOR_CMD      0x5
#define FLASH_READ_SECTOR_CMD		0x6

#define CFG_CRC_LSB					0x4C
#define CFG_CRC_MSB					0x4D
#define PAD_FF						137
#define PACKET_LSB					138
#define PACKET_MSB					139
#define CFG_SECT_LSB				140
#define CFG_SECT_LSB_1				141
#define CFG_SECT_LSB_2				142
#define CFG_SECT_MSB				143


#define TOTAL_64BYTE_PKTS           1636                            //(SF memory area to be 102400 bytes, hence 104448/64 + 4 pkts added during encryption)
#define PACKET_LENGTH               128
#define FLSH_WR_DATA_INDEX          9                               // during flash write actual data starts from index 9
#define MAX_ERRORS                  20


//****************************************************************************
//****************************************************************************
//  Section : Structures
//****************************************************************************
//****************************************************************************

//****************************************************************************
//****************************************************************************
//  Section : Function Declarations
//****************************************************************************
//****************************************************************************
UINT8 flash_info_command(UINT8*, UINT8);
UINT8 flash_write_command(UINT8*, UINT8);
UINT8 flash_verify_command(UINT8 *);
UINT8 flash_write_sector_command(UINT8 *, UINT8 );
UINT8 flash_read_sector_command(UINT8 *);

#ifdef	__cplusplus
}
#endif

#endif	/* FLASHUPDATE_H */


