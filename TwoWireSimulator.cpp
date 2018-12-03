#include <Wire.h>
#include "TwoWireSimulator.h"

///////////////////////// wire.cpp /////////////////////////

TwoWireSimulator::TwoWireSimulator(){
  
}

void TwoWireSimulator::begin(uint8_t address, uint8_t mask)
{ 
 /*
  * ATmega datasheet section 26.9.6:
  * The TWAMR can be loaded with a 7-bit Slave Address mask.
  * Each of the bits in TWAMR can mask (disable) the corresponding
  * address bits in the TWI Address Register (TWAR). If the mask bit
  * is set to one then the address match logic ignores the compare
  * between the incoming address bit and the corresponding bit in TWAR.
  */
  // set mask address
  TWAMR = mask << 1;
  TwoWire::begin(address);
}

void TwoWireSimulator::begin(int address, int mask)
{
  TwoWireSimulator::begin((uint8_t)address, (uint8_t)mask);
}

void TwoWireSimulator::begin(const uint8_t *addresses, const uint8_t sizeAddresses)
{
  uint8_t mask = 0;
  // get all bits that change between each address
  for(int i=1; i<sizeAddresses; ++i){
    mask |= (addresses[0] ^ addresses[i]);
  }
  // set twi mask address
  TWAMR = mask << 1;
  TwoWire::begin(addresses[0]);
}

void TwoWireSimulator::begin(const uint8_t *addressesArray, const int sizeAddressesArray)
{
  TwoWireSimulator::begin(addressesArray, (uint8_t)sizeAddressesArray);
}

char TwoWireSimulator::lastAddress(void){
  return TWDR >> 1; // retrieve address from last byte on the bus
}
