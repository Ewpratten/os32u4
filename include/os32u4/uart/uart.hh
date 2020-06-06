#if !defined(_OS_UART_UART_HH)
#define _OS_UART_UART_HH

#include <stdio.h>

namespace os {
namespace uart {

// Baud rate / 100
enum class BaudRate { k2400 = 24, k9600 = 96, k38400 = 384 };

void init(BaudRate rate);
void redirectSTDIO();

// Get and Put
void putch(char c);
char getch();

// alternate streams to use for serial io
namespace stream {
int putch(char c, FILE *stream);
int getch(FILE *stream __attribute__((unused)));  // namespace stream

}  // namespace stream
}  // namespace uart
}  // namespace os

#endif  // _STDAVR_UART_UART_HH
