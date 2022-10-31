#include <Arduino.h>
#include "BerryIMU_v3.h"

BerryIMU_v3 BerryIMU;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  delay(1000);
  
  while (true) {
    BerryIMU.IMU_read();
    Serial.println(BerryIMU.alt);

    delay(100);
  } 
}

void loop() {

}