/*


*/

#ifndef ESC_h
#define ESC_h
#define LIBRARY_VERSION	1.0.0

#include "Arduino.h"
#include <Servo.h>

class EscMotor
{
    public:
        EscMotor();
	void attachMotors(int, int, int, int);
        void detachMotors();
	int armDrone(int);
	int disarmDrone(int);
	void goUp(int, int);
	void goDown(int, int);

    private:
	struct esc {
	  Servo esc1;
	  Servo esc2;
	  Servo esc3;
	  Servo esc4;
	}ffesc;

	// PWM values in microseconds for a calibrated ESC
	int PWM_ARM     =  1140;   
	int PWM_DISARM  =  1120;
        int PWM_MAX     =  1900;
        int PWM_MIN     =  1100;  
};

#endif
