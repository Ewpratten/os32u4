#include "os32u4/gpio/pin.hh"

namespace os {
namespace gpio {
namespace pin {

void configure(PinBank bank, unsigned int id, PinMode mode) {
    uint8_t pin = toArduinoPin(bank, id);
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *reg, *out;

    if (port == 0) return;

    // JWS: can I let the optimizer do this?
    reg = portModeRegister(port);
    out = portOutputRegister(port);

    if (mode == PinMode::kInput) {
        uint8_t oldSREG = SREG;
        cli();
        *reg &= ~bit;
        *out &= ~bit;
        SREG = oldSREG;
    } else if (mode == PinMode::kInputPullup) {
        uint8_t oldSREG = SREG;
        cli();
        *reg &= ~bit;
        *out |= bit;
        SREG = oldSREG;
    } else {
        uint8_t oldSREG = SREG;
        cli();
        *reg |= bit;
        SREG = oldSREG;
    }
}

void binaryWrite(PinBank bank, unsigned int id, bool enabled) {
    uint8_t pin = toArduinoPin(bank, id);
    uint8_t timer = digitalPinToTimer(pin);
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);
    volatile uint8_t *out;

    if (port == 0) return;

    // If the pin that support PWM output, we need to turn it off
    // before doing a digital write.
    // TODO: Implement PWM before this
    // if (timer != 0) turnOffPWM(timer);

    out = portOutputRegister(port);

    uint8_t oldSREG = SREG;
    cli();

    if (enabled == false) {
        *out &= ~bit;
    } else {
        *out |= bit;
    }

    SREG = oldSREG;
}

bool binaryRead(PinBank bank, unsigned int id) {
    uint8_t pin = toArduinoPin(bank, id);
    uint8_t timer = digitalPinToTimer(pin);
    uint8_t bit = digitalPinToBitMask(pin);
    uint8_t port = digitalPinToPort(pin);

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
