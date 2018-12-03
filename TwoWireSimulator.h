// https://stackoverflow.com/questions/34691478/arduino-as-slave-with-multiple-i2c-addresses
// https://www.mouser.com/pdfdocs/Gravitech_ATMEGA328_datasheet.pdf

#ifndef TwoWireSimulator_h
#define TwoWireSimulator_h

///////////////////////// wire.h /////////////////////////
#include <Wire.h>

class TwoWireSimulator: public TwoWire {
  public:
    TwoWireSimulator();
    void begin(const uint8_t address, const uint8_t mask);
    void begin(const int address, const int mask);
    void begin(const uint8_t *addressesArray, const uint8_t sizeAddressesArray);
    void begin(const uint8_t *addressesArray, const int sizeAddressesArray);
  
    char lastAddress(void);
};

#endif //TwoWireSimulator_h
