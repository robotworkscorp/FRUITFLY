#include <Servo.h>
#include "EscMotor.h"

// Define drone motor pin numbers
#define MOTOR_FL        11
#define MOTOR_FR        10
#define MOTOR_BL         6
#define MOTOR_BR         9

int pwm_val = 1100, incomingByte = 'd';

EscMotor fruitfly;


void setup() {
  Serial.begin(9600);

  Serial.println("Starting drone...");
  
  // Define esc and motors
  fruitfly.detachMotors();
  fruitfly.attachMotors(MOTOR_FL, MOTOR_FR, MOTOR_BL, MOTOR_BR);  
  
}

void loop() {
  if (Serial.available() > 0) {
      incomingByte = Serial.read(); 
      if (incomingByte == 'a') {
        Serial.println("Arming fruitfly...");
        pwm_val = fruitfly.armDrone(pwm_val);
      }
      else if (incomingByte == 'd') {
        Serial.println("Disarming fruitfly...");
        pwm_val = fruitfly.disarmDrone(pwm_val);
      }
  }
}
