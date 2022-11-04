#include "UDPComm.h"
//#include <SoftwareSerial.h> //Imported EspSoftwareSerial library by Dirk Kaar - https://github.com/plerup/espsoftwareserial/

#define RXD2 16
#define TXD2 17

UDPComm udp;

String msg = "";

void setup(){
    
  Serial.begin(115200);
  Serial2.begin(115200, SERIAL_8N1, RXD2, TXD2);
  
  udp.init();
  udp.establishComm();
}

void loop(){
  //Maybe switch while loop to if statement
  while(Serial2.available() > 0){
    
    char readIn = Serial2.read();
    
    if (readIn != '#') {
      //Add char to message
      msg += String(readIn);
      
    }else{
      //End of message, send it!
      Serial.println(msg);
      udp.send("0","BB",msg);
      msg = "";
      
    }
  }
}
