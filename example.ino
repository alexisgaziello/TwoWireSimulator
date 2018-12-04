// I2C Slave

// Include the required Wire library for I2C
#include "TwoWireSimulator.h"

//0-7, 120-127 I2C addresses reserved

//init
TwoWireSimulator WireSim;

void setup() {
  char addresses[3] = {0x8, 0x9, 0xA};
  //Addresses are: 0b 0000 1000, 0b 0000 1001 and 0b 0000 1010 which means the mask will be: 0b 0000 0011
  WireSim.begin(addresses[0], 3);
  // Attach a function to trigger when something is received.
  WireSim.onReceive(receiveEvent);
  WireSim.onRequest(requestEvent);
}

void loop() {
  delay(100);
}

int simulador(int max, int min, int last, bool up, int percentage){
  return up ? last + int((max-min)*percentage/100) : last - int((max-min)*percentage/100);
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
      WireSim.write(6);
      break;

    case (0xA):
      WireSim.write("Requesting from address 10");
      break;

    default:
      break;
  }
}
