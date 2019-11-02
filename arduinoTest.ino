/**************************************************************************/
/*!
    @file     andreas.pde
    @author   Andreas Urben
    @license  

    This example will drive an hubmagnet and set paralel an i2c MCP4725 DAC.

    This is an example sketch for the Adafruit MCP4725 breakout board

*/
/**************************************************************************/
#include <Wire.h>
#include <Adafruit_MCP4725.h>

Adafruit_MCP4725 dac;

int dacStatus = 0;
unsigned long dacPreviousMillis = 0;
const long dacInterval = 500;
unsigned long dacCurrentMillis = 0;
uint32_t currentVoltage=0;


int motorStatus = 0;
unsigned long motorPreviousMillis = 0;
const long motorInterval = 5000;
unsigned long motorCurrentMillis = 0;


void setup(void) {
  // unsigned long test;
  
  Serial.begin(9600);
  Serial.println("Hello!");

  // For Adafruit MCP4725A1 the address is 0x62 (default) or 0x63 (ADDR pin tied to VCC)
  dac.begin(0x62);


  // Motor Setup Channel A
  pinMode(12, OUTPUT);
  pinMode(9, OUTPUT);


  Serial.println("Set Voltage");
}

void loop(void) {

  // unsigned long currentMillis = millis(); 
  motorCurrentMillis = millis(); 

  if (motorCurrentMillis - motorPreviousMillis >= motorInterval) { 
    motorPreviousMillis = motorCurrentMillis; 

    if (motorStatus == 0) { 
      motorStatus = 255;
      analogWrite(3, 255);
    } else {
      motorStatus = 0;
      analogWrite(3, 0);
    }
    // analogWrite(3, MotorStatus);
  }


  // unsigned long currentMillis = millis(); 
  dacCurrentMillis = millis(); 

  if (dacCurrentMillis - dacPreviousMillis >= dacInterval) { 
    dacPreviousMillis = dacCurrentMillis; 

    if (dacStatus == 0) { 
      dacStatus = 1;
      currentVoltage=currentVoltage+1;
      if (currentVoltage>=4095) { 
        currentVoltage=4095;
      } 
      dac.setVoltage(currentVoltage, false);
    } else {
      dacStatus = 0;
    }
    // analogWrite(3, MotorStatus);
  }
  
  // DAC 
  // 3.3V  -> 4094
  // 0V    -> 0
  /*
    uint32_t actualVoltage;
    for (actualVoltage=0;actualVoltage<4095;actualVoltage++) {
      dac.setVoltage(actualVoltage, false);
      delay(500);
    }
  */

  // Motor 
  // digitalWrite(12, LOW);
  // digitalWrite(9, HIGH);

  // if ((millis>5000) & (millis<6000)) {
  // if (test<=500) {
    // analogWrite(3, 255);
  // } else {
    // digitalWrite(9, HIGH);
    // analogWrite(3, 0);
  // }

}
