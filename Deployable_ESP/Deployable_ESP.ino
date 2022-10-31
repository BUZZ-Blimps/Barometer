//#include "UDPComm.h"
#include "BerryIMU_v3.h"
#include <Wire.h> //I2C Library

BerryIMU_v3* BerryIMU;
//UDPComm udp;

void setup() {
  delay(1000);
  BerryIMU = new BerryIMU_v3();
  Serial.println("Success!");
  
  Serial.begin(115200);
  // Leonardo: wait for serial port to connect
  while (!Serial) 
    {
    }

  Serial.println ();
  Serial.println ("I2C scanner. Scanning ...");
  byte count = 0;
  
  Wire.begin();
  for (byte i = 8; i < 120; i++)
  {
    Wire.beginTransmission (i);
    if (Wire.endTransmission () == 0)
      {
      Serial.print ("Found address: ");
      Serial.print (i, DEC);
      Serial.print (" (0x");
      Serial.print (i, HEX);
      Serial.println (")");
      count++;
      delay (1);  // maybe unneeded?
      } // end of good response
  } // end of for loop
  Serial.println ("Done.");
  Serial.print ("Found ");
  Serial.print (count, DEC);
  Serial.println (" device(s).");
  
  Serial.println("Hi!");
  delay(500);
  //udp.init(); 
  //udp.establishComm();

  delay(1000);
}

void loop() {
  Serial.println("Ok!");
  //BerryIMU.IMU_read();
  //Serial.println(BerryIMU.alt);
  //udp.send("0","BB",String(BerryIMU.alt));
  delay(100);
}
