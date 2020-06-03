#if !defined(_STDAVR_UART_UART_HH)
#define _STDAVR_UART_UART_HH

#include <stdio.h>

namespace stdavr {
namespace uart {

// Baud rate
enum class BaudRate { k2400, k9600, k38400 };

void init(BaudRate rate);
void redirectSTDIO();

// Get and Put
void putch(char c);
char getch();

// alternate streams to use for serial io
namespace stream {
void putch(char c, FILE *stream);
char getch(FILE *stream __attribute__((unused)));
}  // namespace streams

}  // namespace uart
}  // namespace stdavr

#endif  // _STDAVR_UART_UART_HH
