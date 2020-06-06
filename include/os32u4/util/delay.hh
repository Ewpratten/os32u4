#if !defined(_OS_UTIL_DELAY_HH)
#define _OS_UTIL_DELAY_HH

#include <util/delay.h>

namespace os {
namespace util {
namespace delay {

void delayMS(unsigned int ms);
void delayS(unsigned int s);

}  // namespace delay
}  // namespace util
}  // namespace os

#endif  // _STDAVE_UTIL_DELAY_HH
