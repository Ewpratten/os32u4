#if !defined(_OS_GPIO_SHIFTREGISTER_HH)
#define _OS_GPIO_SHIFTREGISTER_HH

#include <stdint.h>

#include <os32u4/gpio/pin.hh>

namespace os {
namespace gpio {
namespace shiftregister {

enum class ByteOrder {
    kMSB,
    kLSB
}

void send(const Pin &dataPin, const Pin &clkPin, ByteOrder order, uint8_t data);
uint8_t recv(const Pin &dataPin, const Pin &clkPin, ByteOrder order);

}  // namespace shiftregister
}  // namespace gpio
}  // namespace os

#endif  // _OS_GPIO_SHIFTREGISTER_HH
