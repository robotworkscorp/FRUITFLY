// Library for IMU MM 7150
// Kmenezes July 27 2016

//include library

#include <Wire.h>

// i2C address
// is it 0x80, 0xC0, or 0xE0 ??
#define MM7150_ADDRESS (0x80)

// HID Descriptors

#define wHIDDescLength 0x001E
#define bodVersion 0x0100
#define wReportDescLength 0x0C8D
#define wReportDescRegister 0x0002
#define wInputRegister 0x0003
#define wMaxInputLength 0x000D
#define wOutputRegistert 0x0000
#define wMaxOutputLength 0x0000
#define wCommandRegister 0x0005
#define wDataRegister 0x0006
#define wVendorID 0x04D8
#define wProductID 0x0F01
#define wVersionID 0x7150
#define RESERVED 0x0


class{
	public:
	
	MM7150();
	
	void begin(uint8_t addr = MM7150_ADDRESS);
	// Accelerometer Data
	int16_t sAccelXValue();
	int16_t sAccelYValue();
	int16_t sAccelZValue();
	
	// Compass Data
	int16_t sHeadingCompensatedMagneticNorthValue();
	int16_t sFluxXValue();
	int16_t sFluxYValue();
	int16_t sFluxZValue();
	
	// Gyro
	int16_t sGyroValue();
	int16_t sGyroYValue();
	int16_t sGyroZValue();
	
	// Incline
	int16_t sIncXValue();
	int16_t sIncYValue();
	int16_t sIncZValue();

	// Orientation
	int16_t sOriXValue(); 
	int16_t sOriYValue();  
	int16_t sOriZValue(); 
	int16_t sOriWValue(); 

  private:
	uint8_t i2c_address;

}


