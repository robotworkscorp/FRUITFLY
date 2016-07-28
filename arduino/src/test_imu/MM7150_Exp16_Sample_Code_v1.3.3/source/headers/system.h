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
/** @file  system.h
*   Header file for Explorer16 + PIC24 system level functions
*****************************************************************************
*   MM7150 with Explorer 16 Development Board Sample Code header file
*
*   Company : Microchip Technology Inc.
*
*   File name : System.h
*
*   Summary :  Include file for MM7150 demo code 
*
*   Revisions : 0.3 C21674 - added DEBUG_MODE for toggling signal
*             : 0.2 9-30-14 C21674 - timer & uart global params added
*             : 0.1 8-4-14 C21674  - 
*             : 0.0 7-1-14 C16368  - Initial version created
******************************************************************************/


#ifndef SYSTEM_H
#define	SYSTEM_H

#ifdef	__cplusplus
extern "C" {
#endif

//****************************************************************************
//****************************************************************************
//  Section : Defines
//****************************************************************************
//****************************************************************************

#define SW_S3 TRISDbits.TRISD6                                      //push-button switch S3
#define SW_S6 TRISDbits.TRISD7                                      //push-button switch S6
#define SW_S5 TRISAbits.TRISA7                                      //push-button switch S5
#define SW_S4 TRISDbits.TRISD13                                     //push-button switch S4

#define SW_S3_LOW !PORTDbits.RD6                                    //active low state for push buttons
#define SW_S6_LOW !PORTDbits.RD7
#define SW_S5_LOW !PORTAbits.RA7
#define SW_S4_LOW !PORTDbits.RD13

#define _SW_S3_UP       0                                           //UP button
#define _SW_S6_DWN      1                                           //DOWN button
#define _SW_S5_SLCT     2                                           //SELECT button
#define _SW_S4_RST      3                                           //RESET (return to main menu) button

#define INPUT           1

#define LED_D10         (1<<7)                                      // LED macros
#define LED_D09         (1<<6)
#define LED_D08         (1<<5)
#define LED_D07         (1<<4)
#define LED_D06         (1<<3)
#define LED_D05         (1<<2)
#define LED_D04         (1<<1)
#define LED_D03         (1<<0)
#define CLEAR           0
#define DELAY1          100
#define DELAY2          250

#define UART2_EN            1

#define TIMER_ON        (1<<15)
#define FCY_VAL         4000000
#define UART2_CFG_EN    (1<<15)
#define UART2_TX_EN     (1<<10)

//****************************************************************************
//****************************************************************************
//  Section : Function Declarations
//****************************************************************************
//****************************************************************************

void sys_init(void);
void u2out (char *str);
void lcd_put_data(double, double, double, double, UINT8, double);   // Sends data to LCD
void uart_put_data(double, double, double, double, UINT8);          // Sends data to UART2
UINT8 isPressed(void);
void LED_init(void);
void buttons_init(void);
void UART2_init (UINT32);
void Wake_init(void);
void Wake_signal(void);


#ifdef DEBUG_MODE
void debug_toggle_init(void);
void debug_toggle(int state);
#endif



#ifdef	__cplusplus
}
#endif

#endif	/* SYSTEM_H */

