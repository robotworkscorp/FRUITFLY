
#include "Arduino.h"
#include "EscMotor.h"


EscMotor::EscMotor() 
{
}


void EscMotor::attachMotors(int fl, int fr, int bl, int br)
{
  // Attach motors to electronic speed controllers
  if (ffesc.esc1.attached() == false){
     ffesc.esc1.attach(fl);
  }

  if (ffesc.esc2.attached() == false){
     ffesc.esc2.attach(fr);
  }
 
  if (ffesc.esc3.attached() == false){
     ffesc.esc3.attach(bl);
  }

  if (ffesc.esc4.attached() == false){
     ffesc.esc4.attach(br);
  }

  delay(10);

  // Set to disarm state
  ffesc.esc1.writeMicroseconds(PWM_MIN);
  ffesc.esc2.writeMicroseconds(PWM_MIN); 
  ffesc.esc3.writeMicroseconds(PWM_MIN);
  ffesc.esc4.writeMicroseconds(PWM_MIN);
}


void EscMotor::detachMotors()
{
  // Detach motors from esc
  if (ffesc.esc1.attached() == true){
     ffesc.esc1.detach();
  }

  if (ffesc.esc2.attached() == true){
     ffesc.esc2.detach();
  }
	
  if (ffesc.esc3.attached() == true){	
     ffesc.esc3.detach();
  }

  if (ffesc.esc4.attached() == true){
     ffesc.esc4.detach();
  }

  delay(10);
}


int EscMotor::armDrone(int pwmVal) {
  if (pwmVal < PWM_ARM) {
     for (int i = pwmVal; i <= PWM_ARM; i += 5) {
	ffesc.esc1.writeMicroseconds(i);
	ffesc.esc2.writeMicroseconds(i);
	ffesc.esc3.writeMicroseconds(i);
	ffesc.esc4.writeMicroseconds(i);

	delay(5);
     }   	
  }
  return PWM_ARM;		
}


int EscMotor::disarmDrone(int pwmVal) {
  if (pwmVal > PWM_DISARM) {
     for (int i = pwmVal; i >= PWM_DISARM; i -= 5) {
	ffesc.esc1.writeMicroseconds(i);
	ffesc.esc2.writeMicroseconds(i);
	ffesc.esc3.writeMicroseconds(i);
	ffesc.esc4.writeMicroseconds(i);

	delay(5);
     }   	
  }
  return PWM_DISARM;		
}


void EscMotor::goUp(int fromPwmVal, int toPwmVal) {
  if (toPwmVal > fromPwnVal) {
     if (toPwmVal > PWM_MAX) {
	toPwmVal = PWM_MAX;	
     }
 		
     for (int i = fromPwmVal; i <= toPwmVal; i += 5) {
	ffesc.esc1.writeMicroseconds(i);
	ffesc.esc2.writeMicroseconds(i);
	ffesc.esc3.writeMicroseconds(i);
	ffesc.esc4.writeMicroseconds(i);

	delay(5);
     }   	
  } 
}


void EscMotor::goDown(int fromPwmVal, int toPwmVal) {
  if (toPwmVal < fromPwnVal) {
     if (toPwmVal < PWM_ARM) {
	toPwmVal = PWM_ARM;	
     }
 		
     for (int i = fromPwmVal; i >= toPwmVal; i -= 5) {
	ffesc.esc1.writeMicroseconds(i);
	ffesc.esc2.writeMicroseconds(i);
	ffesc.esc3.writeMicroseconds(i);
	ffesc.esc4.writeMicroseconds(i);

	delay(5);
     }   	
  } 
}


void goForward(int fromPwmVal, chgPwmVal) {
  bool flag = 0;
  int pwmPlus = fromPwmVal, pwmMinus = fromPwmVal;

  while (flag == false) {
     pwmPlus  += 5;
     pwmMinus -= 5;

     if (pwmPlus > PWM_MAX) {
        pwmPlus = PWM_MAX;
     }

     if (pwmMinus < PWM_ARM) {
        pwmMinus = PWM_ARM;
     }

     if ( ((pwmPlus >= toPwmVal + chgPwmVal) || (pwmPlus >= PWM_MAX)) && ()) {
        pwmPlus =  toPwmVal + chgPwmVal;
        pwmMinus = toPwmVal - chgPwmVal;

        ffesc.esc1.writeMicroseconds(pwmPlus);
	ffesc.esc2.writeMicroseconds(pwmPlus);
	ffesc.esc3.writeMicroseconds(pwmMinus);
	ffesc.esc4.writeMicroseconds(pwmMinus);

        delay(5);
        flag = 1;
     }
     else {
        ffesc.esc1.writeMicroseconds(pwmPlus);
	ffesc.esc2.writeMicroseconds(pwmPlus);
	ffesc.esc3.writeMicroseconds(pwmMinus);
	ffesc.esc4.writeMicroseconds(pwmMinus);

        delay(5);
     } 	
  }
}
