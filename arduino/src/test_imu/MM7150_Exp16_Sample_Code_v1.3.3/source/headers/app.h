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

/** @file  app.h
*   Generic include header file
***************************************************************************
*   MM7150 with Explorer 16 Development Board Sample Code header file
*
*   Company : Microchip Technology Inc.
*
*   File name : app.h
*
*   Summary :  Top level include header file for MM7150 demo code 
*
*   Revisions : 0.3 2-04-15 C21674 - added wake, sleep, flash_update, reset support
*			  : 0.2 9-30-14 C21674 - relocated error handling params to err.h
*             : 0.1 8-4-14 C21674  - 
*             : 0.0 7-1-14 C16368  - Initial version created
******************************************************************************/
#ifndef APP_H
#define	APP_H

#ifdef	__cplusplus
extern "C" {
#endif
//****************************************************************************
//****************************************************************************
//  Section : Included files
//****************************************************************************
//****************************************************************************

#define __GENERIC_TYPE_DEFS_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <stdint.h>
#include <stdbool.h>
#include <float.h>

#include <i2c.h>
#include <p24FJ128GA010.h>
#include <timer.h>
#include <xc.h>
#include <uart.h>

typedef unsigned char UINT8;        // 8-bit variables
typedef unsigned char BOOL;
   
typedef unsigned short UINT16;      // 16-bit variables
typedef unsigned long UINT32;
#define TRUE 1
#define FALSE 0

//  Peripheral Include Files
#include "System.h"
#include "lcd.h"
#include "interrupts.h"
#include "VREGS.h"
#include "i2cIO.h"
#include "sf.h"
#include "flashupdate.h"
#include "err.h"

//****************************************************************************
//****************************************************************************
//  Section : Defines
//****************************************************************************
//****************************************************************************

//menu selection 

#define MENU_ITEMS          16

#define MENU_STR_LEN        19
#define MIN_MENU_SLCT	    2


#define MAX_MENU_SLCT	    14       
#define MAX_LINE_NUM	    15

#define ACCEL_MENU_SLCT     2       //accelerometer
#define GYRO_MENU_SLCT      3       //gyrometer
#define COMP_MENU_SLCT      4       //compass
#define ORI_MENU_SLCT       5       //orientation
#define INCL_MENU_SLCT      6       //inclinometer
#define RAW_ACC_MENU_SLCT   7       //raw accelerometer
#define RAW_MAG_MENU_SLCT   8       //raw magnometer
#define RAW_GYRO_MENU_SLCT  9       //raw gyrometer
#define SLP_MENU_SLCT		10		//sleep 
#define WAKE_MENU_SLCT		11		//wake
#define FLASH_UPDATE_MENU_SLCT  12  //flash update
#define CALI_MENU_SLCT		13		//calibration mode
#define FLASH_CONF_MENU_SLCT	14	//flash configuration mode



#define DBNCE_VAL           300     // Debounce timer value (empirically derived)
#define MAX_SENSITIVITY		0
#define MAX_DATA_RATE		10


#ifdef	__cplusplus
}
#endif

#endif	/* APP_H */