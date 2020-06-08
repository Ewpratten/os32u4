#if !defined(_OS_DRIVERS_7SEGMENT_HH)
#define _OS_DRIVERS_7SEGMENT_HH

#include <stdint.h>

#include <os32u4/gpio/pin.hh>

// Mapping from hex to register
const uint8_t digits[] = {
    0b00000000,  // 0
    0b00011000,  // 1
    0b01101101,  // 2
    0b00111101,  // 3
    0b00011011,  // 4
    0b00110111,  // 5
    0b01110111,  // 6
    0b00011100,  // 7
    0b01111111,  // 8
    0b00111111,  // 9
    0b01011111,  // A
    0b01110011,  // b
    0b01100110,  // C
    0b01111001,  // d
    0b01100111,  // E
    0b01000111,  // F
};

namespace os {
namespace drivers {

/**
 * A class for driving a single-digit 7-segment display from a shift
 * register.
 */
class SingleSevenSegment {
   public:
    SingleSevenSegment(const gpio::Pin &, const gpio::Pin &, const gpio::Pin &);

    // Display methods
    void setDecimal(bool);
    void setNumber(uint8_t);
    void setHex(uint8_t);
    void setRaw(uint8_t);

    // Getters
    bool getDecimal() { return this->decimal; }
    uint8_t getNumber() { return this->number; }
    uint8_t getRaw() { return this->raw; }

   private:
    // This method actually does the work
    void updateDisplay();

    // Pins
    gpio::Pin dataPin;
    gpio::Pin clkPin;
    gpio::Pin latchPin;

    // Data
    bool decimal;
    uint8_t number;
    uint8_t raw;
};

}  // namespace drivers
}  // namespace os

#endif  // _OS_DRIVERS_&SEGMENT_HH
