#if !defined(_STDAVE_UTIL_DELAY_HH)
#define _STDAVE_UTIL_DELAY_HH

#include <util/delay.h>

namespace stdavr {
namespace util {
namespace delay {

void delayMS(unsigned int ms);
void delayS(unsigned int s);

}  // namespace delay
}  // namespace util
}  // namespace stdavr

#endif  // _STDAVE_UTIL_DELAY_HH
