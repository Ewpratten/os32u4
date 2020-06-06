/**
 * Wrappers for running safe, and mostly-reliable delays.
 * These wrappers solve an LTO issue with the avr delay library
 *
 * Reference:
 *  - https://efundies.com/accurate-delays-with-avr-in-c/
 */

#include <os32u4/util/delay.hh>

namespace os {
namespace util {
namespace delay {

void delayMS(unsigned int ms) {
    unsigned int i;
    for (i = 0; i < ms; i++) {
        _delay_ms(1);
    }
}

void delayS(unsigned int s) { delayMS(s * 1000); }

}  // namespace delay
}  // namespace util
}  // namespace os