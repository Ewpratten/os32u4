#include "stdavr/gpio/pin.hh"

// TODO: PWM requires a lot of other board features to be implemented first

// Board internal ref voltage
uint8_t analog_reference = (uint8_t)stdavr::gpio::ReferenceVoltage::kDefault;

namespace stdavr {
namespace gpio {
namespace pin {

void setBoardReference(ReferenceVoltage voltage) {
    analog_reference = (uint8_t)voltage;
}

void analogWrite(PinBank bank, unsigned int id, int output) {
    // Currently, we don't support board timers, so PWM is not possible
    // TODO: Add PWM once timers are available

    if (output == 0) {
        binaryWrite(bank, id, false);
    } else {
        binaryWrite(bank, id, true);
    }
}

int analogRead(PinBank bank, unsigned int id) { return 0; }

}  // namespace pin
}  // namespace gpio
}  // namespace stdavr