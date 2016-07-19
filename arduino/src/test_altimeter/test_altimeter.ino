/**************************************************************************/
/*
    Test code for MPL3115A2 altimeter sensor.
*
/**************************************************************************/

#include <Wire.h>
#include <Adafruit_MPL3115A2.h>
	

Adafruit_MPL3115A2 baro = Adafruit_MPL3115A2();

void setup() {
  Serial.begin(9600);
  Serial.println("MPL3115A2 altimeter test!");
}


void loop() {
  if (! baro.begin()) {
    Serial.println("Couldnt find sensor");
    return;
  }
  
  float pascals = baro.getPressure();
  Serial.print(pascals/3377); Serial.println(" Inches (Hg)");

  float altm = baro.getAltitude();
  Serial.print(altm); Serial.println(" meters");

  float tempC = baro.getTemperature();
  Serial.print(tempC); Serial.println("*C");

  delay(250);
}
