#include <os32u4/drivers/7segment.hh>
#include <os32u4/gpio/shiftregister.hh>
#include <os32u4/util/math.hh>

namespace os {
namespace drivers {

SingleSevenSegment::SingleSevenSegment(const gpio::Pin &dataPin,
                                       const gpio::Pin &clkPin,
                                       const gpio::Pin &latchPin) {
    this->dataPin = dataPin;
    this->clkPin = clkPin;
    this->latchPin = latchPin;
}

void SingleSevenSegment::setDecimal(bool on) {
    this->decimal = on;
    this->updateDisplay();
}

void SingleSevenSegment::setNumber(uint8_t number) {
    this->number = os::util::math::min(number, (uint8_t)9);
    this->updateDisplay();
}

void SingleSevenSegment::setHex(uint8_t hex) {
    this->number = os::util::math::min(hex, (uint8_t)15);
    this->updateDisplay();
}

void SingleSevenSegment::setRaw(uint8_t data) {
    this->raw = raw;

    // Send data to shift register
    os::gpio::shiftregister::send(this->dataPin, this->clkPin,
                                  os::gpio::shiftregister::ByteOrder::kMSB,
                                  this->raw);
}

void SingleSevenSegment::updateDisplay(){

    // Get the appropriate bitmask for the number
    uint8_t mask = digits[this->number];

    // Set the decimal if needed
    if(this->decimal){
        mask |= 0b10000000;
    }

    // Call the raw setter
    this->setRaw(mask);
}

}  // namespace drivers
}  // namespace os