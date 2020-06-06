#if !defined(_STDAVR_UART_BAUDUTIL_HH)
#define _STDAVR_UART_BAUDUTIL_HH

namespace stdavr {
namespace uart {
namespace baudutil {

int calcUBRR(unsigned long baud);

}  // namespace baudutil
}  // namespace uart
}  // namespace stdavr

#endif  // _STDAVR_UART_BAUDUTIL_HH
