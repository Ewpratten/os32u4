#include "os32u4/gpio/pin.hh"

// TODO: PWM requires a lot of other board features to be implemented first

// Board internal ref voltage
uint8_t analog_reference = (uint8_t)os::gpio::ReferenceVoltage::kDefault;

namespace os {
namespace gpio {
namespace pin {

void setBoardReference(ReferenceVoltage voltage) {
    analog_reference = (uint8_t)voltage;
}

void analogWrite(Pin *pin, int output) {
    // Currently, we don't support board timers, so PWM is not possible
    // TODO: Add PWM once timers are available

    if (output == 0) {
        binaryWrite(pin, false);
    } else {
        binaryWrite(pin, true);
    }
}

int analogRead(Pin *pin) { return 0; }

}  // namespace pin
}  // namespace gpio
}  // namespace os