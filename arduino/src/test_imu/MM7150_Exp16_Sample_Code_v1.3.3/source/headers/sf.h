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
/** @file  sf.h
*   Header file for sensor functions
*****************************************************************************
*   MM7150 with Explorer 16 Development Board Sample Code header file
*
*   Company : Microchip Technology Inc.
*
*   File name : sf.h
*
*   Summary :  Include file for MM7150 demo code 
*
*   Revisions : 0.3 2-04-15 C21674 - added HOST_SF_LIB_HID_Set_Report & HOST_SF_LIB_HID_Get_Report
*             : 0.2 9-20-14 C21674 - modified error codes for improved error handling (err.h)
*             : 0.1 8-4-14 C21674  - 
*             : 0.0 7-1-14 C16368  - Initial version created
******************************************************************************/


#ifndef SF_H
#define	SF_H

#ifdef	__cplusplus
extern "C" {
#endif

//****************************************************************************
//****************************************************************************
//  Section : Defines
//****************************************************************************
//****************************************************************************

#define GET_HID_DESC            1
#define GET_RPT_DESC            2
#define RESET_DEV_CMD           1
#define POWER_ON                2
#define SLEEP                   3
#define HID_GET_RPT_INPT        4
#define HID_GET_RPT_FEAT        5
#define HID_SET_RPT_OUTP        6
#define HID_SET_RPT_FEAT        7

#define HID_DESC_CMD_LSB        01
#define HID_DESC_CMD_MSB        00
#define DESC_CMD_LEN            2
                                 
#define BUF_40                  40                                  //temp buffer size = 40 bytes
#define BUF_30                  30                                  //temp buffer size = 30 bytes
#define BUF_150                 150
#define HID_CNFG_LEN            BUF_30
#define HID_RPT_LEN             3500                                //size of HID Report Descriptor


#define BYTE_ADJ_VAL            3

#define HID_COLLECTION          0xA1
#define HID_PHYSICAL            0x00
#define HID_REPORT_ID           0x85

#define GF_SENS_OFFSET_MSB      7
#define GF_SENS_OFFSET_LSB      6
#define GF_DATR_OFFSET_MSB      4
#define GF_DATR_OFFSET_LSB      3


#define TIMEOUT_11MS            11                                  // set timeout for 11 ms per API spec
#define TIMEOUT_5SEC            5000                                // RESET timeout 5 secs per HID spec
#define NUM_SENS                12                                  // max number of sensors per API spec

#define VREG_MAX_OFFSET         0x3F                                // Maximum VREG offset

#define RESET_CMD_MSB           0x01                                // RESET command bytes
#define RESET_CMD_LSB           0x00
#define CMD_LEN                 0x04

#define POWER_CMD_MSB           0x08                                // POWER command bytes
#define POWER_CMD_LSB           0x00
#define SLEEP_ON_LSB            0x01                                // SLEEP command bytes

#define GET_RPT_CMD_MSB         0x02                                // GET REPORT commmand bytes
#define GET_RRT_INPT            0x10
#define GET_RPT_FEAT            0x30

#define RPT_LEN                 6

#define SET_RPT_OUT             0x20                                // SET REPORT command bytes
#define SET_RPT_FEAT            0x30
#define SET_OPCODE              0x03

#define BYTE_SHIFT              8

// Report Feature Defines
#define RPT_SIZE_LSB            0
#define RPT_REPORT_STATE        4
#define RPT_PWR_STATE           5
#define RPT_SENS_STATE          6
#define RPT_REPORT_INTVAL_LSB   7
#define RPT_REPORT_INTVAL_MSB   8
#define RPT_CHG_SENS_LSB        13
#define RPT_CHG_SENS_MSB        14

// REPORT PARSE MACROS
#define HID_USAGE_SENSOR_PROPERTY_REPORTING_STATE_ALL_EVENTS_ENUM 0x02
#define HID_USAGE_SENSOR_TYPE                   0x09
#define HID_USAGE_SENSOR_PROPERTY               0x0A
#define HID_USAGE_SENSOR_PROPERTY_CONN_TYPE     0x09                //HID byte sequence : 0x0A,0x09,0x03
#define HID_USAGE_SENSOR_PROPERTY_RPT_STATE     0x16                //HID byte sequence : 0x0A,0x16,0x03
#define HID_USAGE_SENSOR_PROPERTY_PWR_STATE     0x19                //HID byte sequence : 0x0A,0x19,0x03
#define HID_USAGE_SENSOR_                       0x0A
#define HID_USAGE_SENSOR_STATE_1                0x01                //HID byte sequence : 0x0A,0x01,0x02
#define HID_USAGE_SENSOR_STATE_2                0x02                //HID byte sequence : 0x0A,0x01,0x02
#define HID_USAGE_SENSOR_EVENT_1                0x02                //HID byte sequence : 0x0A,0x02,0x02
#define HID_USAGE_SENSOR_EVENT_2                0x02                //HID byte sequence : 0x0A,0x02,0x02
#define HID_USAGE_SENSOR_PROPERTY_RPT_INT       0x0E                //HID byte sequence : 0x0A,0x0E,0x03


#define HID_USAGE_SENSOR_DATA_ACCU              0x44                //the sensor data accuracy value is the #define HID_USAGE_SENSOR_DATA(a,b) value (where (a|b)).
                                                                    // For example, for the accelerometer: 	HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_MOTION_ACCELERATION,HID_USAGE_SENSOR_DATA_MOD_ACCURACY)
                                                                    //  HID_USAGE_SENSOR_DATA_MOTION_ACCELERATION | HID_USAGE_SENSOR_DATA_MOD_ACCURACY = 0x04 | 0x40 = 0x44 this is accuracy value for Non-RAW sensors
#define HID_USAGE_SENSOR_DATA_RAW_ACCU          0x45                //the sensor data accuracy value is the #define HID_USAGE_SENSOR_DATA(a,b) value (where (a|b)).
                                                                    // For example, for RAW sensor: 	HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_CUSTOM_VALUE,HID_USAGE_SENSOR_DATA_MOD_ACCURACY),
                                                                    //  HID_USAGE_SENSOR_DATA_CUSTOM_VALUE | HID_USAGE_SENSOR_DATA_MOD_ACCURACY = 0x05 | 0x40 = 0x45 this is accuracy value for RAW sensors

#define HID_USAGE_SENSOR_DATA_RES               0x54                //see above comment for 'HID_USAGE_SENSOR_DATA_ACCU'substituting 'HID_USAGE_SENSOR_DATA_MOD_RESOLUTION' for 'HID_USAGE_SENSOR_DATA_MOD_ACCURACY'
                                                                    //  HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_MOTION_ACCELERATION,HID_USAGE_SENSOR_DATA_MOD_RESOLUTION)
                                                                    //  where #define HID_USAGE_SENSOR_DATA_MOD_RESOLUTION 0x50
#define HID_USAGE_SENSOR_DATA_RAW_RES           0x55                //  HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_CUSTOM_VALUE,HID_USAGE_SENSOR_DATA_MOD_RESOLUTION)

#define HID_USAGE_SENSOR_DATA_MOD_SENS          0x14                //see above comment for 'HID_USAGE_SENSOR_DATA_ACCU'substituting 'HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS' for 'HID_USAGE_SENSOR_DATA_MOD_ACCURACY'
                                                                    // HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_MOTION_ACCELERATION,HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS)
                                                                    // where #define HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS 0x10
#define HID_USAGE_SENSOR_DATA_RAW_MOD_SENS      0x15                // HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_CUSTOM_VALUE,HID_USAGE_SENSOR_DATA_MOD_CHANGE_SENSITIVITY_ABS)

#define HID_USAGE_SENSOR_DATA_MOD_MAX           0x24                //see above comment for 'HID_USAGE_SENSOR_DATA_ACCU'substituting 'HID_USAGE_SENSOR_DATA_MOD_MAX' for 'HID_USAGE_SENSOR_DATA_MOD_ACCURACY'
                                                                    //HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_MOTION_ACCELERATION,HID_USAGE_SENSOR_DATA_MOD_MAX)
                                                                    // where #define HID_USAGE_SENSOR_DATA_MOD_MAX 0x20
#define HID_USAGE_SENSOR_DATA_RAW_MOD_MAX       0x25                //HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_CUSTOM_VALUE,HID_USAGE_SENSOR_DATA_MOD_MAX)

#define HID_USAGE_SENSOR_DATA_MOD_MIN           0x34                //see above comment for 'HID_USAGE_SENSOR_DATA_ACCU'substituting 'HID_USAGE_SENSOR_DATA_MOD_MIN' for 'HID_USAGE_SENSOR_DATA_MOD_ACCURACY'
                                                                    //HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_MOTION_ACCELERATION,HID_USAGE_SENSOR_DATA_MOD_MIN)
                                                                    // where #define HID_USAGE_SENSOR_DATA_MOD_MIN 0x30
#define HID_USAGE_SENSOR_DATA_RAW_MOD_MIN       0x35                //HID_USAGE_SENSOR_DATA(HID_USAGE_SENSOR_DATA_CUSTOM_VALUE,HID_USAGE_SENSOR_DATA_MOD_MIN)

#define HID_UNIT_EXP                            0x55                //  HID_UNIT_EXPONENT = 0x55

#define HID_END_COLLECTION      0xC0

#define ACCEL_VREG_OFFSET       0                                   // SENSOR TYPES (set in order that they are stored in VREGS struct)
#define GYRO_VREG_OFFSET        1
#define CMP_VREG_OFFSET         2
#define ORI_VREG_OFFSET         3
#define INCL_VREG_OFFSET        4
#define RAW_VREG_OFFSET         7           
#define RAW_ACC_VREG_OFFSET     7
#define RAW_MAG_VREG_OFFSET     8
#define RAW_GYR_VREG_OFFSET     9

#define ACCEL_SENSOR_TYPE       0x73
#define GYRO_SENSOR_TYPE        0x76               
#define CMP_SENSOR_TYPE         0x83               
#define ORI_SENSOR_TYPE         0x8A               
#define INCL_SENSOR_TYPE        0x86               
#define RAW_SENSOR_TYPE         0xE1

//****************************************************************************
//****************************************************************************
//  Section : Function Declarations
//****************************************************************************
//****************************************************************************

UINT16 hid_i2c_descriptor_handler(UINT8 );
UINT8 hid_i2c_cmd_process(UINT8 *, UINT8 , UINT8 );
double ret_exponent(UINT8);
UINT8 report_parse(UINT8 *);

UINT8 HOST_SF_LIB_HID_Set_Report(UINT8, UINT8*, UINT8);
UINT8 HOST_SF_LIB_HID_Get_Report(UINT8, UINT8*, UINT8);


//****************************************************************************
//****************************************************************************
//  Section : Structures
//****************************************************************************
//****************************************************************************

typedef struct HID_DESCRIPTOR_TABLE                                 // Struct to store HID descriptor fields
{
    UINT16 wHIDDescLen;                                             // MSB 1; LSB 0
    UINT16 wRepDescLen;                                             // MSB 5; LSB 4
    UINT16 wRepDescReg;                                             // MSB 6; LSB 7
    UINT16 wMaxInpLen;                                              // MSB 11; LSB 10
    UINT16 wCmdReg;                                                 // MSB 17; LSB 16
    UINT16 wDatReg;                                                 // MSB 19; LSB 18
    UINT16 wVenID;                                                  // MSB 21; LSB 20
    UINT16 wProdID;                                                 // MSB 23; LSB 22
    UINT16 wVerID;                                                  // MSB 25; LSB 24
} HID_DESCRIPTOR_TABLE;


#ifdef	__cplusplus
}
#endif

#endif	/* SF_H */

