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
/** @file  system.c
*   Explorer16 + PIC24 board level functions 
*****************************************************************************
*   MM7150 with Explorer 16 Development Board Sample Code system file
*
*   Company : Microchip Technology Inc.
*
*   File name : system.c
*
*   Summary : Explorer 16 Development board with PIC24FJ128GA010 processor 
*           peripheral modules initialization and setup for MM7150 demo code 
*           for LEDs, LCD, UART2, push-buttons
*
*   Functions : sys_init
*               LED_init
*               buttons_init
*               UART2_init
*               Wake_init
*               Wake_signal
*               u2out
*               isPressed
*               lcd_put_data
*               uart_put_data
*
*   Revisions : 0.3 2-04-15 C21674 - wake_init & wake_signal added
*                                  - UART2 speed change to 19200
*             : 0.2 9-30-14 C21674 - Openi2c1 and UART2_init global params added
*             : 0.1 8-4-14 C21674  - 
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

extern volatile UINT8 PB_EVT;
extern volatile BOOL DEBOUNCE;
UINT32 POR_TIMER;													// amount of elapsed time (in ms) since POR 

//****************************************************************************
//****************************************************************************
//  Section : Code 
//****************************************************************************
//****************************************************************************

/** sys_init
* @note	initializes LEDs, push-buttons, LCD, i2c, and UART communication
* @param 
* @return 
*/
void sys_init()
{

    POR_TIMER = 0;					//reset POR timer
#ifdef DEBUG_MODE
	debug_toggle_init();
#endif
    interrupts_init();                                              // initialize all interrupts
    
    OpenI2C1(CONFIG_I2C_VAL, CONFIG_BRG_VAL);                       // Initialize I2C communication

    LED_init();

    Wake_init();
	
    buttons_init();

#ifdef UART2_EN
   UART2_init(19200);                                             // Initialize UART2 baud rate of 19200
#endif

    LCD_Initialize();

}

#ifdef DEBUG_MODE
void debug_toggle_init()
{
	LATBbits.LATB0 = 1;
	TRISBbits.TRISB0=0;												//config PortB sig 0 (RB0) as an output
	asm volatile("nop"); 
}

void debug_toggle(int state)
{
	LATBbits.LATB0 = state;											//toggle RB0 as a scope trigger for debugging timing events

}
#endif

/** Wake_init
* @note	config wake on RE9 as output, set HIGH initially
* @param 
* @return 
*/ 
void Wake_init()
{
    
    LATEbits.LATE9 = 1;                                             //HIGH
    ODCEbits.ODE9 = 0;                                              //push-pull
    TRISEbits.TRISE9 = 0;                                           //RE9 is an output (wake signal to SSC7150

}

/** Wake_signal
* @note	assert wake signal on RE9, wait 1 ms, deassert
* @param 
* @return 
*/ 
void Wake_signal()
{

    LATEbits.LATE9 = 0;                                             //assert wake signal
    delay(2);                                                       //spec says 3µs assertion, let's use ms delay and wait ~2 ms
    LATEbits.LATE9 = 1;                                             //de-assert wake signal

}

/** LED_init
* @note	config LED pins as outputs, turn on LEDs, dance display
* @param 
* @return 
*/ 
void LED_init()
{


    TRISA = 0xFF00;                                                 // Set LED pins to be outputs

    PORTA = LED_D10;                                                // Turn on LED
    delay(DELAY1);                                                  // Delay 100 msec
    PORTA = LED_D09;
    delay(DELAY1);
    PORTA = LED_D08;
    delay(DELAY1);
    PORTA = LED_D07;
    delay(DELAY1);
    PORTA = LED_D06;
    delay(DELAY1);
    PORTA = LED_D05;
    delay(DELAY1);
    PORTA = LED_D04;
    delay(DELAY1);
    PORTA = LED_D03;
    delay(DELAY1);
    PORTA = CLEAR;
    delay(DELAY1);

    PORTA = LED_D10|LED_D09|LED_D08|LED_D07|LED_D06|LED_D05|LED_D04|LED_D03; // Flash all LEDs once
    delay(DELAY2);                                                  // Delay 250 msec
    PORTA = CLEAR;                                                  // Turn off all LEDS

    return;
}


/** buttons_init
* @note	push-buttons configured as inputs. NOTE:To use SW_S5, LED_D10 must be disabled as they share RA7 
* @param 
* @return 
*/ 
void buttons_init()
{
    
    SW_S3 = INPUT;                                                  // Initialize the buttons' I/O ports as inputs
    SW_S6 = INPUT;
    SW_S5 = INPUT;                                                  // **NOTE: THIS BUTTON MUST NOT BE SET TO INPUT WHILE USING LED0 (they are tied together)**
    SW_S4 = INPUT;
}

/** UART2_Init
* @note	UART2 Initialization function (non-interrupt mode)
* @param ulBaud determines baud speed
* @return 
*/
void UART2_init (UINT32 ulBaud)
{
    UINT8 i;
    unsigned int uiBaud_scaled;
    char clear_line[] = "\n\r\0";
   

    ulBaud *= 16;
    uiBaud_scaled = FCY_VAL/ulBaud - 1;
    
    OpenUART2(UART2_CFG_EN , UART2_TX_EN, uiBaud_scaled);           //initialize the UART2 port @ 19.2K Baud
    IFS1bits.U2RXIF = 0;                                            // clear interrupt flag of rx
    IEC1bits.U2RXIE = 1;                                            // enable rx recieved data interrupt

     for (i = 0; i < 25; i++)                                       //clear UART2 screen
       u2out(clear_line);

}


/** u2out
* @note	Output string to UART2
* @param cStr input string 
* @return 
*/
void u2out (char *cStr)
{

#ifdef UART2_EN 
    putsUART2((unsigned int *)cStr);
#endif
}


/** isPressed
* @note	Push buttons debounced (if interrupt driven), PB_EVT Global set = 0xFF 
* @param 
* @return button value or fail (=0xFF)
*/ 
UINT8 isPressed (void)
{

    if (PB_EVT != 0xFF)                                             // button pressed, check the global button press flag value
    {
        switch(PB_EVT)
        {
            case _SW_S3_UP:
                delay(DBNCE_VAL);                                   // 220 msec debouncing delay (interrupt blackout period)
                DEBOUNCE = FALSE;                                   // done debouncing switch closure (allow interrupts to occur once again)
                PB_EVT = 0xFF;                                      // reset the button event flag
                return _SW_S3_UP;                                   // return UP button value
                
            case _SW_S6_DWN:
                delay(DBNCE_VAL);                                   // 220 msec debouncing delay (interrupt blackout period)
                DEBOUNCE = FALSE;                                   // done debouncing switch closure (allow interrupts to occur once again)
                PB_EVT = 0xFF;                                      // reset the button event flag
                return _SW_S6_DWN;                                  // return DOWN button value
            
            case _SW_S5_SLCT:                                       // push-button S5 does not have interrupt associated with it
                PB_EVT = 0xFF;                                      // reset the button event flag
                return _SW_S5_SLCT;                                 // return SELECT button value

            case _SW_S4_RST:
                delay(DBNCE_VAL);                                   // 220 msec debouncing delay (interrupt blackout period)
                DEBOUNCE = FALSE;                                   // done debouncing switch closure (allow interrupts to occur once again)
                PB_EVT = 0xFF;                                      // reset the button event flag
                
                u2out("\n\nReturning to main menu\n\n\r\0");        //output to COM port on UART2              
                return _SW_S4_RST;                                  //return RESET button value
        }
    }

    return 0xFF;
}


/** lcd_put_data
* @note	Display data to LCD
* @param dDx new X data
* @param dDy new Y data
* @param dDz new Z data
* @param dDw new W data
* @param ucCount number of data elements 
* @param dMult scaling value
* @return 
*/ 
void lcd_put_data(double dDx, double dDy, double dDz, double dDw, UINT8 ucCount, double dMult)
{
    char str[40];


    // The 2 cases below implement different formatting to allow the LCD to display neatly
    if (dMult == .1)
    {
        if (ucCount == 1) 
            sprintf(str, "     %.1f", dDx);                         // Create a string that includes the new data
        if (ucCount == 3) 
            sprintf(str, "X% .1f   Y% .1f       Z% .1f", dDx, dDy, dDz);
        if (ucCount == 4) 
           sprintf(str, "X% .1f Y% .1f Z% .1f W% .1f", dDx, dDy, dDz, dDw);
    }

    else if (dMult == .01 || dMult == .001)
    {
        if(ucCount == 1) 
            sprintf(str, "% .2f", dDx);                             // Create a string that includes the new data
        if(ucCount == 3) 
            sprintf(str, "X% .2f  Y% .2f      Z% .2f", dDx, dDy, dDz);
        if(ucCount == 4) 
            sprintf(str, "X% .2f  Y% .2f  Z% .2f W% .2f", dDx, dDy, dDz, dDw);
   }

    else            
    {
        if (ucCount == 1)
            sprintf(str, "      %.0f", dDx);                         // Create a string that includes the new data
        if (ucCount == 3)
            sprintf(str, "X% 05.0f  Y% 05.0f      Z% 05.0f", dDx, dDy, dDz);
        if (ucCount == 4)
            sprintf(str, "X% .0f Y% .0f Z% .0f W% .0f", dDx, dDy, dDz, dDw);
    }
    
    LCD_ClearScreen();                                              // Clear LCD before setting output
    LCD_PutString(str, sizeof(str));                                // Set data string to the LCD screen

}

/** uart_put_data
* @note	Display data to terminal emulator connected to UART2 on Explorer 16 board
* @param dDx new X data
* @param dDy new Y data
* @param dDz new Z data
* @param dDw new W data
* @param ucCount number of data elements 
* @return 
*/ 
void uart_put_data(double dDx, double dDy, double dDz, double dDw, UINT8 ucCount)
{
    char str[60];


    if (ucCount == 1) 
        sprintf(str, "% 3.0f\n\r", dDx);                             // Create a string that includes the new data
    
    if (ucCount == 3) 
      sprintf(str, "X:% 4.3f Y:% 4.3f Z:% 4.3f\n\r", dDx, dDy, dDz);

    if (ucCount == 4)
        sprintf(str, "X:% 4.3f Y:% 4.3f Z:% 4.3f W: %4.3f\n\r", dDx, dDy, dDz, dDw);
    
    u2out(str);                                                     //output to UART2

}

