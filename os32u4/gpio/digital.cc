#include "os32u4/gpio/pin.hh"
#include <os32u4/util/fixes.hh>

namespace os {
namespace gpio {
namespace pin {

void configure(PinBank bank, unsigned int id, PinMode mode) {
    unsigned char pin = toArduinoPin(bank, id);
    unsigned char bit = digitalPinToBitMask(pin);
    unsigned char port = digitalPinToPort(pin);
    volatile unsigned char *reg, *out;

    if (port == 0) return;

    // JWS: can I let the optimizer do this?
    reg = portModeRegister(port);
    out = portOutputRegister(port);

    if (mode == PinMode::kInput) {
        unsigned char oldSREG = SREG;
        cli();
        *reg &= ~bit;
        *out &= ~bit;
        SREG = oldSREG;
    } else if (mode == PinMode::kInputPullup) {
        unsigned char oldSREG = SREG;
        cli();
        *reg &= ~bit;
        *out |= bit;
        SREG = oldSREG;
    } else {
        unsigned char oldSREG = SREG;
        cli();
        *reg |= bit;
        SREG = oldSREG;
    }
}

void binaryWrite(PinBank bank, unsigned int id, bool enabled) {
    unsigned char pin = toArduinoPin(bank, id);
    unsigned char timer = digitalPinToTimer(pin);
    unsigned char bit = digitalPinToBitMask(pin);
    unsigned char port = digitalPinToPort(pin);
    volatile unsigned char *out;

    if (port == 0) return;

    // If the pin that support PWM output, we need to turn it off
    // before doing a digital write.
    // TODO: Implement PWM before this
    // if (timer != 0) turnOffPWM(timer);

    out = portOutputRegister(port);

    unsigned char oldSREG = SREG;
    cli();

    if (enabled == false) {
        *out &= ~bit;
    } else {
        *out |= bit;
    }

    SREG = oldSREG;
}

bool binaryRead(PinBank bank, unsigned int id) {
    unsigned char pin = toArduinoPin(bank, id);
    unsigned char timer = digitalPinToTimer(pin);
    unsigned char bit = digitalPinToBitMask(pin);
    unsigned char port = digitalPinToPort(pin);

    if (port == 0) return false;

    // If the pin that support PWM output, we need to turn it off
    // before getting a digital reading.
    // TODO: Implement PWM before this
    // if (timer != NOT_ON_TIMER) turnOffPWM(timer);

    if (*portInputRegister(port) & bit) return true;
    return false;
}

}  // namespace pin
}  // namespace gpio
}  // namespace os
