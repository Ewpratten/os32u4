#if !defined(_STDAVR_UART_UART_HH)
#define _STDAVR_UART_UART_HH

#include <stdio.h>

namespace stdavr {
namespace uart {

// Baud rate
enum class BaudRate { k2400, k9600, k38400 };

void init(BaudRate rate);

// Get and Put
void putc(char c, FILE *stream);
void getc(FILE *stream __attribute__((unused)));

// alternate streams to use for serial io
namespace streams {
FILE output;
FILE input;
}  // namespace streams

}  // namespace uart
}  // namespace stdavr

#endif  // _STDAVR_UART_UART_HH
