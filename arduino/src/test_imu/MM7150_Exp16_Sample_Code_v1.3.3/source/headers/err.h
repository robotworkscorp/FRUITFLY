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
/** @file  err.h
*   Header file for error handling functions
*****************************************************************************
*   MM7150 with Explorer 16 Development Board Sample Code header file
*
*   Company : Microchip Technology Inc.
*
*   File name : err.h
*
*   Summary :  Include file for MM7150 demo code 
*
*   Revisions : 0.0 9-30-14 C21674 - initial version, error handling, timeout 
*                           interrupt for unresponsive i2c transactions
*             : 0.1 8-4-14 C21674  - 
*             : 0.0 7-1-14 C16368  - Initial version created
******************************************************************************/
#ifndef ERR_H
#define	ERR_H

#ifdef	__cplusplus
extern "C" {
#endif

//****************************************************************************
//****************************************************************************
//  Section : Defines
//****************************************************************************
//****************************************************************************


// Error code definitions 
#define SUCCESS             0 

//i2c definitions
#define I2_TIMEOUT_PERIOD 500                                       //500 ms

#define I2C_SUCCESS     0
#define I2C_ERROR       (0x21)
#define I2C_BUF_OVRFLO  (0x22)
#define WRITE_COLL      (0x23)
#define NOT_ACK         (0x24)
#define BUS_COLL        (0x25)
#define RX_OVRFLO       (0x26)
#define HID_DESC_RET    (0x27)
#define REP_DESC_RET    (0x28)
#define I2C_TIMEOUT_ERR (0x29)

#define ACKSTAT_bit     (1<<15)
#define BCL_bit         (1<<10)
#define IWOL_bit        (1<<7)
#define I2COV_bit       (1<<6)

//sf.h error definitions
//error codes
#define ID_FAIL                 (0x10)
#define HID_DESC_FAIL           (0x11)
#define RPT_DESC_FAIL           (0x12)
#define REP_PARS_FAIL           (0x14)
#define NO_EOC_FAIL             (0x15)
#define GET_FEAT_FAIL           (0x16)
#define SET_FEAT_FAIL           (0x17)
#define RESET_FAIL              (0x18)
#define SET_RPT_FAIL            (0x19)
#define POWER_ON_FAIL           (0x1A)
#define SLEEP_CMD_FAIL          (0x1B)
#define HID_GET_RPT_INPT_FAIL   (0x1C)
#define HID_GET_RPT_FEAT_FAIL   (0x1D)
#define WAKE_CMD_FAIL           (0x1E)
   
#define HID_INT_FAIL            (0x31)
#define VREG_ACCESS_ERR         (0x32)
#define VREG_OFFSET_ERR         (0x33)

#define FLSH_INFO_ERR           (0x41)
#define FLSH_WRITE_ERR          (0x42)
#define FLSH_VERIFY_ERR         (0x43)
#define FLSH_CRC_ERR            (0x44)
//****************************************************************************
//****************************************************************************
//  Section : Function Declarations
//****************************************************************************
//****************************************************************************

void i2cIO_error(UINT8);
void error_handler( char *, UINT8, UINT8);
void StartI2CTimer();                                               //use timer2 interrupt to recover from unresponsive i2c transactions
void StopI2CTimer();

#ifdef	__cplusplus
}
#endif

#endif	/* ERR_H */

