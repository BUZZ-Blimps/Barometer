#include <Arduino.h>
#include "UDPComm.h"
#include <WiFi.h>
#include <WiFiUdp.h>
//#include <sstream>
//#include <iostream>
//#include <String>


using namespace std;

int numMessageTypes = 4;
enum messageType {controllerInput, parameters, debug, newBlimp};
String flags[] = { "I", "P", "D", "N" };
String managerID = "0";


void UDPComm::init() {
    Serial.begin(115200);
//    Serial.setTimeout(50);
    Serial.println();
    Serial.println("====================================");

    Serial.println("Attempting to connect to WiFi.");
  
    int status = WiFi.begin(ssid, password);
    int tries = 0;
    while (status != WL_CONNECTED) { //Keep trying to connect every 5 seconds
        Serial.print("Not connected yet. Current status: ");
        Serial.print(status);
        Serial.println(". Waiting 5 seconds.");
        delay(5000);
        status = WiFi.status();
        tries++;
        if (tries > 6) { //After 6 tries (30 seconds), retry connection
            tries = 0;
            status = WiFi.begin(ssid, password);
        }
    }

    Serial.println("Connected to Wifi.");
    //Serial.println(WiFi.macAddress());
    Serial.println(WiFi.localIP());
    Serial.println();

    Serial.println("Attempting to connect to UDP Multicast.");
    udp.beginMulticast(udpAddress, udpPort);
    udp.flush();
    Serial.println("Connected to UDP Multicast.");
}

void UDPComm::establishComm(){
    //Get Blimp ID
    Serial.println("Sending ID request");
    blimpID = "N";
    while (true) {
        readPackets();
        if (!packets[newBlimp].isEmpty()) {
            blimpID = packetGetMessage(packets[newBlimp].extractBottom());
            break;
        }
        Serial.println("Sending ID request");
        send(managerID, flags[newBlimp], "N");
        delay(500);
    }
    String confirm = "Blimp " + blimpID + " identified.";
    Serial.println(confirm);
    send(managerID,flags[debug],confirm);
}

//Message format: identifier+targetID+,+sourceID+:+flag+:+message
//NewBlimp:       :)0,N:N:N

void UDPComm::send(String message) {
    udp.beginPacket(udpAddress, udpPort);
    String configuredOut = identifier + message;
    udp.print(configuredOut);
    udp.endPacket();
}

void UDPComm::send(String targetID, String flag, String message) {
    send(targetID + "," + blimpID + ":" + flag + ":" + message);
}

//Returns true when it received a message
//Sets *packet to message if valid, otherwise ""
bool UDPComm::readPacket(String* packet){
    int parsed = udp.parsePacket();
    int avail = udp.available();
    if (avail < 1) return false; //If nothing available

    char buffChar;
    char buff[avail + 1];
    for (int i = 0; i < avail; i++) {
        udp.read(&buffChar, 1);
        buff[i] = buffChar;
    }
    udp.flush();

    buff[avail] = '\0';
    String input = String(buff);

    bool valid = true;
    if (input.substring(0, identifier.length()) != identifier) valid = false;
    input = input.substring(identifier.length());
    int comma = input.indexOf(',');
    if (comma == -1 || input.substring(0, comma) != blimpID) valid = false;

    if (valid) {
        *packet = input;
    }else {
        *packet = "";
    }
    return true;
}

void UDPComm::readPackets() {
    String packet = "";
    while (readPacket(&packet)) {
        if (packet == "") continue; //If invalid message, skip it

        String flag = packetGetFlag(packet);
        flag.trim();
        if (flag.equals("B")) continue;
        
          for (int i = 0; i < numMessageTypes; i++) { //Iterate through flags
              if (flag == flags[i]){
              packets[i].pushTop(packet); //Push packet to quack
              }
          }
          
        packetMove = packet; //move the packet to be read as inputs
    }
}

//Message format: identifier+targetID+,+sourceID+:+flag+:+message
String UDPComm::packetGetTargetID(String packet) {
    int comma = packet.indexOf(',');
    return packet.substring(0, comma);
}

String UDPComm::packetGetSourceID(String packet) {
    int comma = packet.indexOf(',');
    int firstColon = packet.indexOf(':');
    return packet.substring(comma + 1, firstColon);
}

String UDPComm::packetGetFlag(String packet) {
    int firstColon = packet.indexOf(':');
    int secondColon = packet.indexOf(':', firstColon+1);
    return packet.substring(firstColon+1,secondColon);
}

String UDPComm::packetGetMessage(String packet) {
    int firstColon = packet.indexOf(':');
    int secondColon = packet.indexOf(':', firstColon+1);
    return packet.substring(secondColon+1);
}
