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
/** @file  i2cIO.h
*   Header file for i2c functions
*****************************************************************************
*   MM7150 with Explorer 16 Development Board Sample Code header file
*
*   Company : Microchip Technology Inc.
*
*   File name : i2cIO.h
*
*   Summary :  Include file for MM7150 demo code 
*
*   Revisions : 0.2 9-30-14 C21674 - error handling params moved to err.h
*             : 0.1 8-4-14 C21674  - 
*             : 0.0 7-1-14 C16368  - Initial version created
******************************************************************************/
#ifndef I2CIO_H
#define	I2CIO_H

#ifdef	__cplusplus
extern "C" {
#endif
//****************************************************************************
//****************************************************************************
//  Section : Defines
//****************************************************************************
//****************************************************************************


#define CONFIG_I2C_VAL  0x8000
#define CONFIG_BRG_VAL  8
#define WRITE           1
#define READ            2
#define WR_RD           3
#define SLAVE_ADDR      0x80
#define I2C_POR_TIMEOUT 2000				//i.e. 2 seconds @ 1ms
//****************************************************************************
//****************************************************************************
//  Section : Function Declarations
//****************************************************************************
//****************************************************************************

void gets_I2C1(UINT8 *, UINT16, BOOL);
UINT8 i2c_cmd_WrRd(UINT8, UINT8,  UINT8 *, UINT16,  UINT8 *, BOOL);

#ifdef	__cplusplus
}
#endif

#endif	/* I2CIO_H */

