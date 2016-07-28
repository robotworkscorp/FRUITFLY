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

/** @file  vregs.h
*   Header file for virtual register functions
*****************************************************************************
*  MM7150 with Explorer 16 Development Board Sample Code header file
*
*   Company : Microchip Technology Inc.
*
*   File name : vregs.h
*
*   Summary :  VREG include header file for MM7150 demo code 
*
*   Revisions : 0.3 10-17-14 C21674 - added and remapped VREG registers for MAG FLUX
*             : 0.2 9-30-14 C21674 - modified VREG names to be more descriptive
*             : 0.1 8-4-14 C21674  - 
*             : 0.0 7-1-14 C16368  - Initial version created
******************************************************************************/

#ifndef VREGS_H
#define	VREGS_H

#ifdef	__cplusplus
extern "C" {
#endif

//****************************************************************************
//****************************************************************************
//  Section : Defines
//****************************************************************************
//****************************************************************************

#define VREG_RESET_INIT                 1
#define VREG_RESET_SUCCESS              0
#define VREG_SH_AWAKE                   1
#define VREG_SH_ASLEEP                  0

#define VREG_SHSTART_SUCCESS            1                           //status codes
#define VREG_SHSTART_FAIL               3
#define ARB_ID                          1                           // Arbitrary report ID to be used for POWER_ON and RESET commands (these commands do not require a specific ID)
#define MAX_RETRIES                     3                           // as per SF API spec

#define FULL_POWER                      0x02
#define LOW_POWER                       0x03

#define VREG_RST_CMD_SUCCESS            1
#define VREG_RESET_CMD_FAIL             3

#define VREG_WAKE_SUCCESS               2
#define VREG_WAKE_FAIL                  6
#define VREG_SLEEP_SUCCESS              1
#define VREG_SLEEP_FAIL                 5

#define VREG_ENABLE_SUCCESS             1
#define VREG_DISABLE_SUCCESS	        2
#define VREG_ENA_DIS_FAIL               3

#define VREG_UPDATE_SENS_SUCCESS        1
#define VREG_UPDATE_SENS_FAIL           5
#define VREG_UPDATE_DATARATE_SUCCESS    2
#define VREG_UPDATE_DATARATE_FAIL       6

//****************************************************************************
//****************************************************************************
//  Section : Structures
//****************************************************************************
//****************************************************************************
/*****************************************************************************
			   VIRTUAL REGISTER - VREGs      			 
******************************************************************************/

/*********************SENSOR HUB CONFIG REGISTER*****************************/

#define VREG_SHC                    0x00                            //Sensor Hub Configuration : VREG 0x00
#define VREG_SHC_WAKE_BIT           (1<<0)
#define VREG_SHC_SLP_BIT            (1<<1)
#define VREG_SHC_START_BIT          (1<<2)
#define VREG_SHC_RST_BIT            (1<<3)
#define VREG_SHC_ACC_EN             (1<<4)
#define VREG_SHC_GYRO_EN            (1<<5)
#define VREG_SHC_CMP_EN             (1<<6)
#define VREG_SHC_ORI_EN             (1<<7)
#define VREG_SHC_INC_EN             (1<<8)
#define VREG_SHC_RAWACC_EN          (1<<11)
#define VREG_SHC_RAWMAG_EN          (1<<12)
#define VREG_SHC_RAWGYR_EN          (1<<13)

#define VREG_SHC_ACC_EN_VAL         4
#define VREG_SHC_RAWACC_EN_VAL      11
#define VREG_SHC_RAWMAG_EN_VAL      12
#define VREG_SHC_RAWGYR_EN_VAL      13


struct SENSOR_HUB_CONFIG                                       
{
    unsigned SHwake:1;                                              // Set when device is awake
    unsigned sleep:1;                                               // Set to enter sleep; clears shWAKE bit
    unsigned SHstart:1;                                             // HID cannot be enabled unless set
    unsigned reset:1;                                               // Set to start HID reset and set all VREGS to POR
    unsigned AccelEnable:1;                                         // Set to enable accelerometer
    unsigned GyroEnable:1;                                          // Set to enable gyrometer
    unsigned CmpEnable:1;                                           // Set to enable compass
    unsigned OriEnable:1;                                           // Set to enable orientation sensor
    unsigned InclEnable:1;                                          // Set to enable inclinometer
    unsigned BarEnable:1;                                           // Set to enable BAR sensor
    unsigned AlsEnable:1;                                           // Set to enable ALS sensor
    unsigned RawAccelEnable:1;                                      // Set to enable user to read raw accelerometer data
    unsigned RawMagEnable:1;                                        // Set to enable user to read raw magnometer data
    unsigned RawGyroEnable:1;                                       // Set to enagle user to read raw gryrometer data
    unsigned :2;
};

/*************************SENSOR LIST REGISTER***************************
The list of available sensors can be acquired by parsing the report
descriptor table. Set bit when a sensor is foud to be availble.
************************************************************************/
#define VREG_SL         0x01                                        //Sensor List: VREG 0x01
struct SENSOR_LIST
{
    unsigned accel:1;                                               //sensor available bit
    unsigned gyro:1;           
    unsigned cmp:1;
    unsigned ori:1;
    unsigned incl:1;
    unsigned res:11;
};

/*********************SENSIVITY REGISTERS*******************************
 Sensitivities of each sensor can be found by running GetFeature for
 each of the sensors and retrieving that parameter
************************************************************************/
#define VREG_ACSEN      0x02                                        //Acc Sensitivity: VREG 0x02
#define VREG_GYSEN      0x03                                        //Gyro Sensitivity: VREG 0x03
#define VREG_CMSEN      0x04                                        //Cmp Sensitivity: VREG 0x04
#define VREG_ORSEN      0x05                                        //Ori Sensitivity: VREG 0x05
#define VREG_INSEN      0x06                                        //Incl Sensitivity: VREG 0x06
#define VREG_RES07      0x07                                        //Reserved: VREG 0x07
#define VREG_RES08      0x08                                        //Reserved: VREG 0x08
#define VREG_RACSEN     0x09                                        //Raw Acc Sensitivity: VREG 0x09
#define VREG_RMGSEN     0x0A                                        //Raw Mag Sensitivity: VREG 0x0A
#define VREG_RGYSEN     0x0B                                        //Raw Gyro Sensitivity: VREG 0x0B

struct SENSIT_REGS
{
    UINT16 ACSEN;                                                   // Acc Sensitivity : VREG 0x02
    UINT16 GYSEN;                                                   // Gyro Sensitivity : VREG 0x03
    UINT16 CMSEN;                                                   // Cmp Sensitivity : VREG 0x04
    UINT16 ORSEN;                                                   // Ori Sensitivity : VREG 0x05
    UINT16 INSEN;                                                   // Incl Sensitivity : VREG 0x06
    UINT16 RES_VREG07;                                              // Reserved : VREG 0x07
    UINT16 RES_VREG08;                                              // Reserved : VREG 0x08
    UINT16 RACSEN;                                                  // Raw Acc Sensitivity : VREG 0x09
    UINT16 RMGSEN;                                                  // Raw MAg Sensitivity : VREG 0x0A
    UINT16 RGYSEN;                                                  // Raw Gyro Sensitivity : VREG 0x0B
};
/*************************DATA RATE REGISTERS***************************
 Data rates of each sensor can be found by running get feature for
 each of the sensors and retrieving that parameter
************************************************************************/
#define VREG_ACDXR      0x0C                                        //Acc DataRate: VREG 0x0C
#define VREG_GYDR       0x0D                                        //Gyro DataRate: VREG 0x0D
#define VREG_CMDR       0x0E                                        //Cmp DataRate: VREG 0x0E
#define VREG_ORDR       0x0F                                        //Ori DataRate: VREG 0x0F
#define VREG_INDR       0x10                                        //Incl DataRate: VREG 0x10
#define VREG_RES11      0x11                                        //Reserved: VREG 0x11
#define VREG_RES12      0x12                                        //Reserved: VREG 0x12
#define VREG_RACDR      0x13                                        //Raw Acc DataRate: VREG 0x13
#define VREG_RMGDR      0x14                                        //Raw Mag DataRate: VREG 0x14
#define VREG_RGYDR      0x15                                        //Raw Gyro DataRate: VREG 0x15

struct DATA_RT_REGS
{
    UINT16 ACDXR;                                                   // Acc DataRate : VREG 0x0C
    UINT16 GYDR;                                                    // Gyro DataRate : VREG 0x0D
    UINT16 CMDR;                                                    // Cmp DataRate : VREG 0x0E
    UINT16 ORDR;                                                    // Ori DataRate : VREG 0x0F
    UINT16 INDR;                                                    // Incl DataRate : VREG 0x10
    UINT16 RES_VREG11;                                              // Reserved : VREG 0x11
    UINT16 RES_VREG12;                                              // Reserved : VREG 0x12
    UINT16 RACDR;                                                   // Raw Acc DataRate : VREG 0x13
    UINT16 RMGDR;                                                   // Raw Mag DataRate : VREG 0x14
    UINT16 RGYDR;                                                   // Raw Gyro DataRate : VREG 0x15
};

/***************************DATA REGISTERS*******************************
 These registers should be updated with relevant data as it comes in
 during interrupts.
************************************************************************/
#define VREG_ACXD       0x16                                        //AccX Data: VREG 0x16
#define VREG_ACYD       0x17                                        //AccY Data: VREG 0x17
#define VREG_ACZD       0x18                                        //AccZ Data: VREG 0x18
#define VREG_RACXD      0x19                                        //Raw AccX Data: VREG 0x19
#define VREG_RACYD      0x1A                                        //Raw AccY Data: VREG 0x1A
#define VREG_RACZD      0x1B                                        //Raw AccZ Data: VREG 0x1B
#define VREG_GYXD       0x1C                                        //GyroX Data: VREG 0x1C
#define VREG_GYYD       0x1D                                        //GyroY Data: VREG 0x1D
#define VREG_GYZD       0x1E                                        //GyroZ Data: VREG 0x1E
#define VREG_RGYXD      0x1F                                        //Raw GyroX Data: VREG 0x1F
#define VREG_RGYYD      0x20                                        //Raw GyroY Data: VREG 0x20
#define VREG_RGYZD      0x21                                        //Raw GyroZ Data: VREG 0x21
#define VREG_CMD        0x22                                        //Cmp Data: VREG 0x22
#define VREG_MGFXD      0x23                                        //Mag FluxX Data: VREG 0x23
#define VREG_MGFYD      0x24                                        //Mag FluxY Data: VREG 0x24
#define VREG_MGFZD      0x25                                        //Mag FluxZ Data: VREG 0x25
#define VREG_RMGXD      0x26                                        //Raw MagX Data: VREG 0x26
#define VREG_RMGYD      0x27                                        //Raw MagY Data: VREG 0x27
#define VREG_RMGZD      0x28                                        //Raw MagZ Data: VREG 0x28
#define VREG_ORXD       0x29                                        //OriX Data: VREG 0x29
#define VREG_ORYD       0x2A                                        //OriY Data: VREG 0x2A
#define VREG_ORZD       0x2B                                        //OriZ Data: VREG 0x2B
#define VREG_ORWD       0x2C                                        //OriW Data: VREG 0x2C
#define VREG_INXD       0x2D                                        //InclX Data: VREG 0x2D
#define VREG_INYD       0x2E                                        //InclY Data: VREG 0x2E
#define VREG_INZD       0x2F                                        //InclZ Data: VREG 0x2F
#define VREG_RES30      0x30                                        //Reserved: VREG 0x30
#define VREG_RES31      0x31                                        //Reserved: VREG 0x31
#define VREG_RES32      0x32                                        //Reserved: VREG 0x32
#define VREG_RES33      0x33                                        //Reserved: VREG 0x33
#define VREG_RES34      0x34                                        //Reserved: VREG 0x34
#define VREG_RES35      0x35                                        //Reserved: VREG 0x35

struct DATA_REGS
{
    UINT16 ACXD;                                                    // AccX Data : VREG 0x16
    UINT16 ACYD;                                                    // AccY Data : VREG 0x17
    UINT16 ACZD;                                                    // AccZ Data : VREG 0x18
    UINT16 RACXD;                                                   // Raw AccX Data : VREG 0x19
    UINT16 RACYD;                                                   // Raw AccY Data : VREG 0x1A
    UINT16 RACZD;                                                   // Raw AccZ Data : VREG 0x1B
    UINT16 GYXD;                                                    // GyroX Data : VREG 0x1C
    UINT16 GYYD;                                                    // GyroY Data : VREG 0x1D
    UINT16 GYZD;                                                    // GyroZ Data : VREG 0x1E
    UINT16 RGYXD;                                                   // Raw GyroX Data : VREG 0x1F
    UINT16 RGYYD;                                                   // Raw GyroY Data : VREG 0x20
    UINT16 RGYZD;                                                   // Raw GyroZ Data : VREG 0x21
    UINT16 CMD;                                                     // Cmp Data : VREG 0x22
    UINT16 MGFXD;                                                   // Mag FluxX Data: VREG 0x23
    UINT16 MGFYD;                                                   // Mag FluxY Data: VREG 0x24
    UINT16 MGFZD;                                                   // Mag FluxZ Data: VREG 0x25
    UINT16 RMGXD;                                                   // Raw MagX Data : VREG 0x26
    UINT16 RMGYD;                                                   // Raw MagY Data : VREG 0x27
    UINT16 RMGZD;                                                   // Raw MagZ Data : VREG 0x28
    UINT16 ORXD;                                                    // OriX Data : VREG 0x29
    UINT16 ORYD;                                                    // OriY Data : VREG 0x2A
    UINT16 ORZD;                                                    // OriZ Data : VREG 0x2B
    UINT16 ORWD;                                                    // OriW Data : VREG 0x2C
    UINT16 INXD;                                                    // InclX Data : VREG 0x2D
    UINT16 INYD;                                                    // InclY Data : VREG 0x2E
    UINT16 INZD;                                                    // InclZ Data : VREG 0x2F
    UINT16 RES_VREG30;                                              // Reserved : VREG 0x30
    UINT16 RES_VREG31;                                              // Reserved : VREG 0x31
    UINT16 RES_VREG32;                                              // Reserved : VREG 0x32
    UINT16 RES_VREG33;                                              // Reserved : VREG 0x33
    UINT16 RES_VREG34;                                              // Reserved : VREG 0x34
    UINT16 RES_VREG35;                                              // Reserved : VREG 0x35
};

//**********************************ID Registers****************************************
#define VREG_PID        0x36                                        //Product ID: VREG 0x36
#define VREG_VID        0x37                                        //Vendor ID: VREG 0x37
#define VREG_DID        0x38                                        //Device ID: VREG 0x38

struct IDS
{
    UINT16 PID;                                                     //ProductID : VREG 0x36   Note:  The product ID can be retrieved from the HID descriptor table
    UINT16 VID;                                                     //VendorID : VREG 0x37  Note: The vendor ID can be retrieved from the HID descriptor table
    UINT16 DID;                                                     //DeviceID : VREG 0x38 Note: The device ID can be retrieved from the HID descriptor table
};

/*************************EXPONENT REGISTERS***************************
**********************************************************************/
#define VREG_EXP1       0x39                                        //Exponent1: VREG 0x39
struct EXPONENT1                    
{
    unsigned expA:4;
    unsigned expG:4;
    unsigned expC:4;
    unsigned expO:4;
};

#define VREG_EXP2       0x3A                                        //Exponent2: VREG 0x3A
struct EXPONENT2                     
{
    unsigned expIN:4;
    unsigned expB:4;
    unsigned expAL:4;
    unsigned expRA:4;
};

#define VREG_EXP3       0x3B                                        //Exponent3: VREG 0x3B
struct EXPONENT3                     
{
    unsigned expRM:4;
    unsigned expRG:4;
    unsigned res:8;
};

//**********************Structure of the Exponents ************************
struct EXPONENT
{
    struct EXPONENT1 exp1;
    struct EXPONENT2 exp2;
    struct EXPONENT3 exp3;
};

#define VREG_EXPCSS1    0x3C                                        //ExponentCS1: VREG 0x3C
struct EXPONENTCS1                   
{
    unsigned expCSA:4;
    unsigned expCSG:4;
    unsigned expCSC:4;
    unsigned expCSO:4;
};

#define VREG_EXPCSS2    0x3D                                        //ExponentCS2: VREG 0x3D
struct EXPONENTCS2
{
    unsigned expSCIN:4;
    unsigned expCSB:4;
    unsigned expCSAL:4;
    unsigned expCSRA:4;
};

#define VREG_EXPCSS3    0x3E                                        //ExponentCS3: VREG 0x3E
struct EXPONENTCS3                   
{
    unsigned expCSRM:4;
    unsigned expCSRG:4;
    unsigned res:8;
};

//**********************Structure of the Exponents ************************
struct EXPONENTCS
{
    struct EXPONENTCS1 expCS1;
    struct EXPONENTCS2 expCS2;
    struct EXPONENTCS3 expCS3;
};

//***********************Structure for Status******************************
#define VREG_STAT1      0x3F                                        //Status 1: VREG 0x3F
struct STATUS1                       
{
    unsigned Accstatus:2;
    unsigned GyroStatus:2;
    unsigned CmpStatus:2;
    unsigned OriStatus:2;
    unsigned IncStatus:2;
    unsigned ResStatus1:2;
    unsigned ResStatus2:2;
    unsigned RawAccStatus:2;
};

#define VREG_STAT2      0x40                                        //Status 2 VREG 0x40
#define STATUS1_MASK    0x03
#define STATUS2_MASK    0x07
struct STATUS2                       
{
    unsigned RawMagStatus:2;
    unsigned RawGyroStatus:2;
    unsigned AccCSData:3;
    unsigned GyroCSData:3;
    unsigned CmpCSData:3;
    unsigned OriCSData:3;
};

#define VREG_STAT3      0x41                                        //Status 3: VREG 0x41
struct STATUS3                       
{
    unsigned InclCSData:3;
    unsigned resCSData1:3;
    unsigned resCSData2:3;
    unsigned RawAccCSData:3;
    unsigned RawMagCSData:3;
    unsigned res:1;
};

#define VREG_STAT4      0x42                                        //Status 4: VREG 0x42
struct STATUS4                       
{
    unsigned RawGyroCSDAta:3;
    unsigned SHStartStatus:2;
    unsigned ResetStatus:2;
    unsigned ShSleepWakeStatus:3;
    unsigned res:6;
};

struct STATUS
{
    struct STATUS1 stat1;
    struct STATUS2 stat2;
    struct STATUS3 stat3;
    struct STATUS4 stat4;
};


typedef struct SF_VREGS                                             // The entire set of virtual registers
{
    struct SENSOR_HUB_CONFIG SHC;
    struct SENSOR_LIST SL;
    struct SENSIT_REGS sensitivity;
    struct DATA_RT_REGS data_rt;
    struct DATA_REGS data;
    struct IDS IDs;
    struct EXPONENT expo;
    struct EXPONENTCS expCS;
    struct STATUS stat;
} SF_VREGS;


typedef struct SENSOR                                               // parameters for individual sensors
{
   UINT8 id;
   UINT8 type;
   UINT8 DatRtOffset;
   UINT8 SensOffset;
   UINT8 SensExp;
   UINT8 DatOffset;
   UINT8 DatExp;
} SF_SENSOR, SF_TEMP;

typedef struct GET_SET_PARAMS
{
    unsigned char ucid;
    unsigned char ucPowerState;
    unsigned short usSensitivityVal;
    BOOL bSensitivityValid;
    unsigned short usDataRateVal;
    BOOL bDataRateValid;
} GET_SET_PARAMS;

//****************************************************************************
//****************************************************************************
//  Section : Function Declarations
//****************************************************************************
//****************************************************************************

UINT8 VREG_init();
UINT8 HOST_SF_LIB_VREG_read(UINT8, UINT16 *);
UINT8 HOST_SF_LIB_VREG_write(UINT8, UINT16 );
void parse_update_VREG_data (UINT8, UINT8 *);

#ifdef	__cplusplus
}
#endif

#endif	/* VREGS_H */


