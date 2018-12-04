// I2C Slave

// Include the required Wire library for I2C
#include "TwoWireSimulator.h"

//0-7, 120-127 I2C addresses reserved

//init
TwoWireSimulator WireSim;

void setup() {
  //For printing purposes
  Serial.begin(9600);
  // Addresses we have chosen:
  char addresses[3] = {0x8, 0x9, 0xA};
  // Addresses are: 0b 0000 1000, 0b 0000 1001 and 0b 0000 1010 so the resultant mask will be: 0b 0000 0011
  // This means that the address 0b 0000 1011 will also be active.
  WireSim.begin(addresses[0], 3);
  // Attach a function to trigger when something is received.
  WireSim.onReceive(receiveEvent);
  WireSim.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

void requestEvent (){
  switch (WireSim.lastAddress()) {
    case (0x9): //Acelerador
      char bufferSend[2];
      bufferSend[0] = 100;
      bufferSend[1] = 55;
      WireSim.write(bufferSend,2);
      break;

    case (0x8): //T1
      Serial.print("Sending a 6 from I2C device number 8");
      WireSim.write(6);
      break;

    case (0xA):
      WireSim.write("Requesting from address 10");
      break;

    default:
      break;
  }
}

void receiveEvent(int howMany) {
  while (1 < Wire.available()) { // loop through all but the last
    char c = Wire.read(); // receive byte as a character
    Serial.print(c);         // print the character
  }
  int x = Wire.read();    // receive byte as an integer
  Serial.println(x);         // print the integer
}
