#include <os32u4/gpio/pin.hh>

namespace os {
namespace gpio {
namespace pin {

unsigned char toArduinoPin(PinBank bank, unsigned int id) {
    if (bank == PinBank::kAnalog) {
        return A0 + id;
    } else {
        return id;
    }
}

}  // namespace pin
}  // namespace gpio
}  // namespace os