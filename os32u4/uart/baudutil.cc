#include <os32u4/uart/baudutil.hh>

#ifndef F_CPU
#define F_CPU 16000000
#endif

namespace os {
namespace uart {
namespace baudutil {

int calcUBRR(unsigned long baud) {
    return (((F_CPU) + 8 * (baud)) / (16 * (baud)) - 1);
}

}  // namespace baudutil
}  // namespace uart
}  // namespace os