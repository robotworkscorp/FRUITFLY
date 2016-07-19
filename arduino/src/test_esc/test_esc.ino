#include <Servo.h>
#include "esc_test.h"

// Global variables
int pwm_val = 1100, incomingByte = 0, throttle = 1100, change = 0;
bool flag = 0;


pwmVal pwm;

// Define ESC servo objects
Servo ESC1;
Servo ESC2;
Servo ESC3;
Servo ESC4;

// Define drone motor pin numbers
#define MOTOR_FL        11
#define MOTOR_FR        10
#define MOTOR_BL         6
#define MOTOR_BR         9

// Minimum, middle and maximum ESC value in microseconds
#define ESC_MIN      1100
#define ESC_MID      1500
#define ESC_MAX      1900
#define ESC_ARM    1135

void attachMotors() {
  ESC1.attach(MOTOR_FL);
  ESC2.attach(MOTOR_FR);
  ESC3.attach(MOTOR_BL);
  ESC4.attach(MOTOR_BR);
  delay(10); 
}


void arm(int pwm_val) {
  for (int i = pwm_val; i <= ESC_ARM; i += 5) {
    ESC1.writeMicroseconds(i);
    ESC2.writeMicroseconds(i);
    ESC3.writeMicroseconds(i);
    ESC4.writeMicroseconds(i);
    delay(5);     
  }
}

void disarm(int pwm_val) {
  for (int i = pwm_val; i >= ESC_MIN; i -= 5) {
    ESC1.writeMicroseconds(i);
    ESC2.writeMicroseconds(i);
    ESC3.writeMicroseconds(i);
    ESC4.writeMicroseconds(i);
    delay(5);    
  }
}

void speedup(int fromVal, int toVal) {
  for (int i = fromVal; i <= toVal; i += 5) {
    ESC1.writeMicroseconds(i);
    ESC2.writeMicroseconds(i);
    ESC3.writeMicroseconds(i);
    ESC4.writeMicroseconds(i);
    delay(5);     
  }
}

void speeddown(int fromVal, int toVal) {
  for (int i = fromVal; i >= toVal; i -= 5) {
    ESC1.writeMicroseconds(i);
    ESC2.writeMicroseconds(i);
    ESC3.writeMicroseconds(i);
    ESC4.writeMicroseconds(i);
    delay(5);    
  }
}


//void hover(pwmVal pwm, int toVal) {
//  flag = 0;
//  while (flag == 0) {
//    if (pwm.maxVal > toVal) {
//      pwm.maxVal -= 5;
//    }
//    else if (pwm.maxVal < toVal) {
//      pwm.maxVal += 5;
//    }
//    else {
//      pwmVal.maxVal = toVal
//    }
//
//    if (pwm.minVal > toVal) {
//      pwm.minVal -= 5;
//    }
//    else if (pwm.minVal < toVal) {
//      pwm.minVal += 5;
//    }
//    else {
//      pwmVal.minVal = toVal
//    }
//
//    if (pwm.maxVal == toVal & pwm.minVal == toVal) {
//      ESC1.writeMicroseconds(toVal);
//      ESC2.writeMicroseconds(toVal);
//      ESC3.writeMicroseconds(toVal);
//      ESC4.writeMicroseconds(toVal);
//      delay(5);
//      
//      flag = 1;
//    }
//    else {
//      ESC1.writeMicroseconds(pwm.maxVal);
//      ESC2.writeMicroseconds(pwm2.maxVal);
//      ESC3.writeMicroseconds(pwm2.minVal);
//      ESC4.writeMicroseconds(pwm1.minVal);
//      delay(5);
//    }
//  }  
//}

pwmVal forward(int fromVal, int changeVal) {
  Serial.println("Pitching in front to move forward...");

  flag = 0;
  pwmVal pwm = {fromVal, fromVal};

  Serial.println("Total pwm value");
  Serial.println(fromVal);
  Serial.println(change);
  Serial.println("====");
  
  while (flag == 0) {
    pwm.maxVal += 5;
    pwm.minVal -= 5;

    Serial.println(pwm.maxVal);
    Serial.println(pwm.minVal);

    if (pwm.maxVal >= (fromVal + changeVal)) {
      pwm.maxVal = fromVal + changeVal;
      pwm.minVal = fromVal - changeVal;
      
      ESC1.writeMicroseconds(pwm.maxVal);
      ESC2.writeMicroseconds(pwm.maxVal);
      ESC3.writeMicroseconds(pwm.minVal);
      ESC4.writeMicroseconds(pwm.minVal);
      delay(5);

      flag = 1; 
    }
    else {
      ESC1.writeMicroseconds(pwm.maxVal);
      ESC2.writeMicroseconds(pwm.maxVal);
      ESC3.writeMicroseconds(pwm.minVal);
      ESC4.writeMicroseconds(pwm.minVal);
      delay(5);
    }
  }

  return pwm; 
}


void setup()
{
  Serial.begin(9600);

  attachMotors();

  // Set ESC/Motors to minimum value
  ESC1.writeMicroseconds(ESC_MIN);
  ESC2.writeMicroseconds(ESC_MIN);
  ESC3.writeMicroseconds(ESC_MIN);
  ESC4.writeMicroseconds(ESC_MIN);
  delay(10);

  // Set global variable pwm_val to ESC_MIN
  pwm_val = ESC_MIN;
} 

void loop() {
  if (Serial.available() > 0) {
    incomingByte = Serial.read(); 
    if (incomingByte == 'a') {
      Serial.println("Arming fruitfly...");
      arm(pwm_val);
      pwm_val = ESC_ARM;
    }
    else if (incomingByte == 'd') {
      Serial.println("Disarming fruitfly...");
      disarm(pwm_val);
      pwm_val = ESC_MIN;
    }
    else if (incomingByte == 'f') {
      Serial.println("Move forward...");
      throttle = 1200;
      speedup(pwm_val, throttle);
      delay(10000);
      pwm_val = throttle;
      change = 100;
      pwm = forward(pwm_val, change);
      Serial.println(pwm.minVal);
      Serial.println(pwm.maxVal);
    }
  }
}
  
//  pwm_val = 1250;
//  change_val = 80;
//   
//  ESC1.writeMicroseconds(pwm_val);
//  ESC2.writeMicroseconds(pwm_val);
//  ESC3.writeMicroseconds(pwm_val);
//  ESC4.writeMicroseconds(pwm_val);
//  
//  delay(4000);
//
//
//  flag = 0;
//  pwm1 = pwm_val;
//  pwm2 = pwm_val;
//  while (flag == 0) {
//    pwm1 += 5;
//    pwm2 -= 5;
//
//    Serial.println(pwm1);
//    Serial.println(pwm2);
//
//    if (pwm1 >= pwm_val + change_val) {
//      flag = 1; 
//    }
//    else {
//      ESC1.writeMicroseconds(pwm1);
//      ESC2.writeMicroseconds(pwm2);
//      ESC3.writeMicroseconds(pwm2);
//      ESC4.writeMicroseconds(pwm1);
//      delay(10);
//    }
//  }
//
//  
//  
//  flag = 0;
//  while (flag == 0) {
//    pwm1 = pwm1 - 5;
//    pwm2 = pwm2 - 5;
//
//    Serial.println(pwm1);
//    Serial.println(pwm2);
//    
//    if (pwm1 <= ESC_MIN & pwm2 <= ESC_MIN) {
//      flag = 1; 
//    }
//    else {
//      ESC1.writeMicroseconds(pwm1);
//      ESC2.writeMicroseconds(pwm2);
//      ESC3.writeMicroseconds(pwm2);
//      ESC4.writeMicroseconds(pwm1);
//      delay(5);
//    }
//  }
//      
////  for (i = pwm_val; i >= ESC_MIN; i -= 5) {
////    ESC1.writeMicroseconds(i);
////    ESC2.writeMicroseconds(i);
////    ESC3.writeMicroseconds(i);
////    ESC4.writeMicroseconds(i);
////    delay(10);
////  }
// 
////  for (i = 1000; i <= 1450; i += 5) {
////    //ESC1.writeMicroseconds(i);
////    ESC2.writeMicroseconds(i);
////    ESC3.writeMicroseconds(i);
////    ESC4.writeMicroseconds(i);
////    delay(10);
////  }
////
////  delay(4000);
////  
////  for (i = 1450; i >= 1000; i -= 5) {
////    //ESC1.writeMicroseconds(i);
////    ESC2.writeMicroseconds(i);
////    ESC3.writeMicroseconds(i);
////    ESC4.writeMicroseconds(i);
////    delay(10);
////  }
//
//}
//
//void loop()
//{
//  
//  //ESC2.writeMicroseconds(pwm);
//  //ESC3.writeMicroseconds(pwm);
//  //ESC4.writeMicroseconds(pwm);
//}
