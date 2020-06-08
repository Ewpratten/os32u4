#if !defined(_OS_GPIO_SHIFTREGISTER_HH)
#define _OS_GPIO_SHIFTREGISTER_HH

#include <stdint.h>

namespace os {
namespace gpio {
namespace shiftregister {

void send();
uint8_t recv();

}  // namespace shiftregister
}  // namespace gpio
}  // namespace os

#endif  // _OS_GPIO_SHIFTREGISTER_HH
