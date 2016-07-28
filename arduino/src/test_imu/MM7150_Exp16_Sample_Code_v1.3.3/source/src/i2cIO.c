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
/** @file  i2cIO.c
*   I2C functions to I/F PIC24 with SSC7150
*****************************************************************************
*  MM7150 with Explorer 16 Development Board Sample Code i2c i/o file
*
*   Company : Microchip Technology Inc.
*
*   File name : i2cIO.c
*
*   Summary : Module for MM7150 demo code which interfaces 
*           PIC24 (Explorer16 board) to SSC7150 via i2c bus/calls 
*   
*   Functions : i2c_cmd_WrRd
*               gets_I2C1
*               i2cIO_error
*
*   Revisions : 0.2 9-18-14 C21674 - enhanced error handling, added timer2 interrupt 
*                                    to exit for unresponsive i2c, gets_I2C1 check status
*                                    bits on exit with no data 
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
//  Section : Code
//*****************************************************************************
//*****************************************************************************

/** gets_I2C1
* @note	Read bytes from sensor device via i2c1 channel slave
* @param ucRdptr pointer to data buffer from slave
* @param usLength number of bytes to read from slave
* @param bAdjust  first bytes of rx packet has number of bytes returned by read, if =TRUE use this new data length 
* @return 
*/ 
void gets_I2C1(UINT8 *ucRdptr, UINT16 usLength, BOOL bAdjust){

    UINT16 i = 0;                                               
    UINT8 ucSize = 1;                                                // Set return value for size of data read for bAdjust=FALSE
    UINT16 usStat = 0;   


    while (usLength--)
    {
    
        I2C1CONbits.RCEN = 1;                                       // Send read command to slave

        // Wait for a byte to be received from the slave
        MasterWaitForIntrI2C1();                                    // Wait for Master "interrupt" request and then clear interrupt Flag.

        ucRdptr[i++] = I2C1RCV;                                     // Read in the byte received from slave, clearing RBF

        if (usLength)                                               // bytes to be read
        {
            I2C1CONbits.ACKDT= 0;                                   // Set acknowledge bit state for ACK
            I2C1CONbits.ACKEN = 1;                                  // Initiate bus acknowledge sequence

            MasterWaitForIntrI2C1();                                // Wait for Master "interrupt" request and then clear interrupt Flag.
        }

        if (bAdjust && i == 2)                                      // Read first 2 bytes which have the length of the packet
        {
            usLength = ((ucRdptr[1] << BYTE_SHIFT) | ucRdptr[0]) - 2; // Actual length is value of first 2 bytes minus 2 (because we read 2 already)
            ucSize = usLength;
        }
    }

    if (!ucSize)
    {
        usStat = I2C1STAT;                                          //read status register
        StopI2CTimer();                                             //turn off timer2 interrupt

        if (usStat & ACKSTAT_bit)
            i2cIO_error(NOT_ACK);                                   //ACK error (does not return)

        else if (usStat & BCL_bit)
            i2cIO_error(BUS_COLL);                                  //BCL error (does not return)

        else if (usStat & IWOL_bit)
            i2cIO_error(WRITE_COLL);                                //WCL error (does not return)

        else if (usStat & I2COV_bit)
            i2cIO_error(RX_OVRFLO);                                 //Rx OVRFLO error (does not return)
        
        else
            error_handler("i2c ",0, I2C_ERROR);                     //flag as general i2c error (does not return)
    }
    
}
  

/** i2c_cmd_WrRd
* @note	i2c write,read, and combined write/read commands, start timer2 interrupt to exit on unresponsive i2c bus
* @param ucCmd error code
* @param ucBytes_wr Number of bytes to write to slave 
* @param ucData_wr Pointer to data buffer to send to slave 
* @param usBytes_rd Number of bytes to read from slave
* @param ucData_rd Pointer to data buffer from slave
* @param bAdjust Use 1st 2 bytes returned as new length (=TRUE) 
* @return I2C_SUCCESS(=0), I2C_BUF_OVRFLO(=0x22)
*/
UINT8 i2c_cmd_WrRd(UINT8 ucCmd, UINT8 ucBytes_wr,  UINT8 *ucData_wr, UINT16 usBytes_rd,  UINT8 *ucData_rd, BOOL bAdjust)
{
    UINT8 i;                                                       
    

    if (ucBytes_wr > BUF_150)                                       // sanity check for maximum buffer size
        return I2C_BUF_OVRFLO;                                      // return i2c buffer overflow error code to calling routine

    StartI2CTimer();                                                // start timer2 interrupt in case i2c hangs in 'while loop' functions
   
    IdleI2C1();                                                     // Ensure module is idle
    I2C1CONbits.SEN = 1;                                            // Send start bit TO slave
    MasterWaitForIntrI2C1();                                        // Wait for Master interrupt request and then clear interrupt Flag.

    switch(ucCmd)
    {
        case WRITE:
            
            if (MasterWriteI2C1(SLAVE_ADDR))                        // Write slave address with the R/W indicator bit cleared
                i2cIO_error(WRITE_COLL);                            //write collision error display (does not return)

            MasterWaitForIntrI2C1();                                // Wait for Master interrupt request and then clear interrupt Flag.

            if (!I2C1STATbits.ACKSTAT)                               // check for ACK from slave
            {
                for(i = 0; i < ucBytes_wr; i++)                     // Begin a loop writing the tx bytes to the slave
                {
                    if ( MasterWriteI2C1(ucData_wr[i]))             // Write one byte of the tx data to the slave
                        i2cIO_error(WRITE_COLL);                    //write collision error display (does not return)
                    
                    MasterWaitForIntrI2C1();                        // Wait for Master interrupt request and then clear interrupt Flag.

                    if((i + 1) < ucBytes_wr)                        // If this byte is not the last one, check ACK
                    {
                        if (I2C1STATbits.ACKSTAT)                   // check for ACK condition, if received
                           i2cIO_error(NOT_ACK);                    //ACK error (does not return)
                   }    
                }
            }
            
            else
                i2cIO_error(NOT_ACK);                              //ACK error (does not return)

            break;

        case READ:
            
            if (MasterWriteI2C1(SLAVE_ADDR | 1))                    // Write slave address with the R/W indicator bit set
                i2cIO_error(WRITE_COLL);                            //write collision error (does not return)
            
            MasterWaitForIntrI2C1();                                // Wait for Master interrupt request and then clear interrupt Flag.

            if (!I2C1STATbits.ACKSTAT)                              // If ACK received then begin reading data from the slave
            {
                gets_I2C1(ucData_rd, usBytes_rd, bAdjust);          // Read in multiple bytes

                NotAckI2C1();                                       // NACK
                
                MasterWaitForIntrI2C1();                            // Wait for the interrupt request
            }
            else
                i2cIO_error(NOT_ACK);                               //ACK error (does not return)
        
            break;

        case WR_RD:
            
            if (MasterWriteI2C1(SLAVE_ADDR)) 	                    // Write slave address with the R/W indicator bit cleared
                i2cIO_error(WRITE_COLL);                            //write collision (does not return)

            MasterWaitForIntrI2C1();                                // Wait for Master interrupt request and then clear interrupt Flag.

            if (I2C1STATbits.ACKSTAT)                               // check for ACK condition
               i2cIO_error(NOT_ACK);                                // ACK error (does not return)

            for(i = 0; i < ucBytes_wr; i++)                         // Begin a loop writing the tx bytes to the slave
            {
                if (MasterWriteI2C1(ucData_wr[i]))                  // Write one byte of the tx data to the slave
                     i2cIO_error(WRITE_COLL);                       //write collision error (does not return)
                    
                MasterWaitForIntrI2C1();                            // Wait for Master interrupt request and then clear interrupt Flag.

                if ((i + 1) < ucBytes_wr)                           // If this byte is not the last one, check ACK
                {
                    if (I2C1STATbits.ACKSTAT)                       // check for ACK condition, if received
                       i2cIO_error(NOT_ACK);                       //ACK error (does not return)
               }
            }

            if (I2C1STATbits.ACKSTAT)                               // check for ACK condition
                i2cIO_error(NOT_ACK);                               // ACK error (does not return)
               
            RestartI2C1();                                          // Generate I2C bus restart condition
                    
            while (I2C1CONbits.RSEN);                               // Wait until re-start condition is over
                    
            MasterWaitForIntrI2C1();                                // Wait for interrupt request

            if (MasterWriteI2C1(SLAVE_ADDR | 1))    	            // Write slave address with the R/W indicator bit set
                i2cIO_error(WRITE_COLL);                            //write collision error (does not return)

            MasterWaitForIntrI2C1();                                // Wait for Master interrupt request and then clear interrupt Flag.

            if (I2C1STATbits.ACKSTAT)                               // If ACK received then begin reading data from the slave
                i2cIO_error(NOT_ACK);                               // ACK error (does not return)

            gets_I2C1(ucData_rd, usBytes_rd, bAdjust);              // Read in multiple bytes
                          
            NotAckI2C1();                                           // Send NACK 

            MasterWaitForIntrI2C1();                                // Wait for interrupt request

            break;
    }

    StopI2C1();                                                     // Send STOP condition
    
    while (I2C1CONbits.PEN );                                       // Wait until stop condition is over
    
    MasterWaitForIntrI2C1();                                        // Wait for interrupt request
   
    StopI2CTimer();                                                 //turn off timer2 interrupt 

    return I2C_SUCCESS;
}
