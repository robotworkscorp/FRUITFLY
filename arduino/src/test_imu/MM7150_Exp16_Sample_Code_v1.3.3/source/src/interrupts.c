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
/** @file  interrupts.c
*   PIC24 interrupt handler functions
*****************************************************************************
*   MM7150 with Explorer 16 Development Board Sample Code system file
*
*   Company : Microchip Technology Inc.
*
*   File name : interrupts.c
*
*   Summary : Interrupt functions module for MM7150 demo code
*
*   Functions : interrupts_init
*               delay
*               _T1Interrupt
*               _T2Interrupt
*               _INT1Interrupt
*               _CNInterrupt
*               _U2RXInterrupt
*
*   Revisions : 0.3 2-004-15 C21674 - _U2RXInterrupt added to support vendor command for
*                                       flash update
*             : 0.2 9-30-14 C21674 - added timer2 interrupt for i2c transactions, global
*                                    param added for OpenTimerX
*             : 0.1 8-4-14 C21674
*             : 0.0 7-1-14 C16368  - Initial version created
******************************************************************************/
//****************************************************************************
//****************************************************************************
//  Section : Included files
//****************************************************************************
//****************************************************************************

#include "..\headers\app.h"

//*****************************************************************************
//*****************************************************************************
//  Section : File scope variables and functions
//*****************************************************************************
//*****************************************************************************

volatile BOOL TIMER_1MS_FLG;                                        // 1 msec timer interrupt flag
volatile UINT16 I2C_TIMEOUT_1MS_CNTR;                               // 1 msec timer2 interrupt counter
volatile BOOL EC_DATA_AVAIL = FALSE;                                // EC data available for read flag
volatile UINT8 PB_EVT = 0xFF;                                       // Push Button press event
volatile BOOL DEBOUNCE = FALSE;                                     // Debounce flag (initially set to FALSE, ie. NOT currently debouncing a switch closure)
volatile BOOL I2C_BUMP = FALSE;

UINT8 ucDWNLD_IDX = 0;
UINT8 HOST_DWNLOAD_BUF[138] = {0};
BOOL process_packet = FALSE;
extern UINT8 FLASH_BUF[];
extern UINT32 POR_TIMER;
//*****************************************************************************
//*****************************************************************************
//  Section : Code
//*****************************************************************************
//*****************************************************************************

/** interrupts_init
* @note	configures the INT1, timer1, timer2, and button interrupts
* @param
* @return
*/
void interrupts_init()
{

    ConfigIntTimer1(T1_INT_PRIOR_1 & T1_INT_ON);                    // Config Timer1
    OpenTimer1(TIMER_ON,0x0FA0);                                    // set Timer1 period to 1 msec

    ConfigIntTimer2(T2_INT_PRIOR_1 & T2_INT_ON);                    // Config Timer2 used for i2c timeouts 
    OpenTimer2(0,0x0FA0);                                           // set Timer2 period to 1 msec

    // Configure external INT1 for HIDI2C_HOST_INT interrupts
    AD1PCFG = 0xFFFF;                                               // no analog set the filter to digital input
    TRISE = 0xFFFF;                                                 // config all PortE is an input
  
    IFS1bits.INT1IF = 0;                                            // clear INT1 flag
    IPC5bits.INT1IP = 1;                                            // assign INT1 priority
    INTCON2bits.INT1EP = 1;                                         // INT1 Edge set to interrupt on falling edge initially
    IEC1bits.INT1IE = 1;                                            // enable INT1

    // Config push-button press interrupts
    IFS1bits.CNIF = 0;                                              // clear IF bit
    IPC4bits.CNIP0 = 1;                                             // set to highest priority
    IPC4bits.CNIP1 = 1;                                             // priority bit2
    IPC4bits.CNIP2 = 1;                                             // priority bit3
    IEC1bits.CNIE = 1;                                              // enable the cn interrupt request
    CNEN1bits.CN15IE = 1;                                           // button0 : push-button S3
    CNEN2bits.CN16IE = 1;                                           // button1 : push-button S6
    CNEN2bits.CN19IE = 1;                                           // button3 : push-button S4

}

/** delay
* @note	Millisecond delay function based on Timer1 (1ms interrupts)
* @param usMs Number of milliseconds to wait
* @return
*/
void delay(UINT16 usMs)
{

    TIMER_1MS_FLG = 0;                                          //clear global TIMER flag
    
    while (usMs)
    {
        if (TIMER_1MS_FLG)
        {
            usMs--;
            TIMER_1MS_FLG = 0;
        }
    }
    return;
}


/** _T1Interrupt
* @note	timer1 interrupt handler, global TIMER_1MS_FLG flag will be set
* @param
* @return
*/
void __attribute__ ((__interrupt__)) _T1Interrupt (void);
void __attribute__ ((__interrupt__,no_auto_psv)) _T1Interrupt (void)
{
  
    IFS0bits.T1IF = 0;                                              //clear IF bit
    TIMER_1MS_FLG= 1;                                               // 1 ms flag
    POR_TIMER++;													//increment POR time cnt
}


/** _T2Interrupt
* @note	timer2 interrupt handler used to recover from unresponsive i2c transactions
* @param
* @return
*/
void __attribute__ ((__interrupt__)) _T2Interrupt (void);
void __attribute__ ((__interrupt__,no_auto_psv)) _T2Interrupt (void)
{
  
    IFS0bits.T2IF = 0;                                              //clear IF bit
    
    I2C_TIMEOUT_1MS_CNTR++;                                         //increment global count val
    
    if (I2C_TIMEOUT_1MS_CNTR >= I2_TIMEOUT_PERIOD)                  
    {                                                               //looks like i2c taking too long
        T2CONbits.TON = 0;                                          //turn off timer
        error_handler("i2c ",0, I2C_TIMEOUT_ERR);                   //displays to LCD and uart **does not return***
    }

}

/** _INT1Interrupt
* @note	external INT1 interrupt interrupt handler, init on falling edge (global EC_DATA_AVAIL flag set), then switch to rising edge to signal end of interrupt from HOST  
* @param 
* @return
*/
void __attribute__((__interrupt__)) _INT1Interrupt(void);
void __attribute__((__interrupt__, no_auto_psv)) _INT1Interrupt (void)
{
   
    if (IFS1bits.INT1IF)                                            // Check the HID_I2C_ALERT (INT1) interrupt : indicates data from EC available
    {
        if (!EC_DATA_AVAIL)                                         // If a falling edge occurred (data is available from EC)
        {
            INTCON2bits.INT1EP = 0;                                 // INT1 Edge configured to interrupt on rising edge (wait for end of data)
            EC_DATA_AVAIL = TRUE;                                   // Toggle EC_DATA_AVAIL flag to notify data received
        }
        else
        {
            INTCON2bits.INT1EP = 1;                                 // INT1 Edge configured to interrupt on falling edge (data is no longer available)
            EC_DATA_AVAIL = FALSE;                                  // interrupt de-asserted
        }
	
	IFS1bits.INT1IF = 0;                                        //clear int flag
    }
}


/** _CNInterrupt
* @note	CN interrupt interrupt handler, used for push-button switch closures
* @param
* @return
*/
void __attribute__((__interrupt__)) _CNInterrupt(void);
void __attribute__ ((__interrupt__, no_auto_psv )) _CNInterrupt(void)
{

    IFS1bits.CNIF = 0;                                              //clear IF bit
    
    if (SW_S3_LOW && !DEBOUNCE)                                     // (s3) button press caused interrupt & not currently debouncing switch closure
    {
        PB_EVT = _SW_S3_UP;                                         // set the press variable
        DEBOUNCE = TRUE;                                            // begin the debounce period
    }
    
    if (SW_S6_LOW && !DEBOUNCE)                                     // (s6) button press caused interrupt & not currently debouncing switch closure
    {
        PB_EVT = _SW_S6_DWN;                                        // set the press variable
        DEBOUNCE = TRUE;                                            // begin the debounce period
    }
    
    if (SW_S4_LOW && !DEBOUNCE)                                     // (s6) button press caused interrupt & not currently debouncing switch closure
    {
        PB_EVT = _SW_S4_RST;                                        // set the press variable
        DEBOUNCE = TRUE;                                            // begin the debounce period
    }
}

/** _U2RXInterrupt
* @note	UART2 Receive interrupt handler, receive input file from HOST for flash update through UART2  
* @param 
* @return
*/
void __attribute__((__interrupt__)) _U2RXInterrupt(void);
void __attribute__((__interrupt__, no_auto_psv)) _U2RXInterrupt(void)
{

    
    IFS1bits.U2RXIF = 0;                                            // clear IF bit

    HOST_DWNLOAD_BUF[ucDWNLD_IDX++] = (char) U2RXREG;               //read byte from HOST via UART2
    
    if ( ucDWNLD_IDX >= PACKET_LENGTH )                             // accumulated one packet (128 bytes)of data from HOST
    {
        ucDWNLD_IDX = 0;                                            //reset offset index
        
        memcpy(FLASH_BUF, HOST_DWNLOAD_BUF, PACKET_LENGTH);
        process_packet = TRUE;                                      //flag to let flash write to transfer the data to the SSC7150
    }

}
