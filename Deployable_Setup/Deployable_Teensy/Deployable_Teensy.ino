#include <Arduino.h>
#include "BerryIMU_v3.h"

BerryIMU_v3 BerryIMU;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  Serial1.begin(115200);

}

void loop() {
    BerryIMU.IMU_read();
    Serial.println(BerryIMU.alt);

    Serial1.print(BerryIMU.alt);
    Serial1.print("#");
    delay(50);
}
