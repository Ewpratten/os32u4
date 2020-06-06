#if !defined(_OS_UART_BAUDUTIL_HH)
#define _OS_UART_BAUDUTIL_HH

namespace os {
namespace uart {
namespace baudutil {

int calcUBRR(unsigned long baud);

}  // namespace baudutil
}  // namespace uart
}  // namespace oi

#endif  // _OS_UART_BAUDUTIL_HH
