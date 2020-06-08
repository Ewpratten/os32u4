#include <os32u4/gpio/pin.hh>

namespace os {
namespace gpio {
namespace pin {

unsigned char toArduinoPin(const Pin &pin) {
    if (pin.bank == PinBank::kAnalog) {
        return A0 + pin.channel;
    } else {
        return pin.channel;
    }
}

}  // namespace pin
}  // namespace gpio
}  // namespace os