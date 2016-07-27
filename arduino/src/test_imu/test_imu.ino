// Kmenezes July 27th 2016
// Code to output IMU - MM 7150 Motion Module

//include library

#include <Wire.h>
#include <test_imu.h>

MM7150 monitor;

void setup() {
  Serial.begin(9600);
  // monitor the i2c bus
  monitor.begin(128);
  Serial.println("Testing IMU Motion Module");
}

void loop(){
  Serial.print("Accelerometor: x,y,z ");
  Serial.println(monitor.sAccelXValue();
  Serial.println(monitor.sAccelYValue();
  Serial.println(monitor.sAccelZValue();
  
  Serial.println("******************");

  Serial.print("Compass: x,y,z ");
  Serial.println(monitor.sFluxXValue();
  Serial.println(monitor.sFluxYValue();
  Serial.println(monitor.sFluxZValue();

  Serial.println("******************");

  Serial.print("Gyro: x,y,z ");
  Serial.println(monitor.sGyroValue();
  Serial.println(monitor.sGyroYValue();
  Serial.println(monitor.sGyroZValue();

  Serial.println("******************");
  Serial.print("Orientation: x,y,z,w ");
  Serial.println(monitor.sOriXValue();
  Serial.println(monitor.sOriYValue();
  Serial.println(monitor.sOriZValue();
  Serial.println(monitor.sOriWValue();

  
}

