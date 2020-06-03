#include <avr/io.h>

#include <stdavr/uart/uart.hh>

static void _init_uart_2400() {
#undef BAUD  // avoid compiler warning
#define BAUD 2400
#include <util/setbaud.h>

    UBRR1H = UBRRH_VALUE;
    UBRR1L = UBRRL_VALUE;

#if USE_2X
    UCSR1A |= _BV(U2X1);
#else
    UCSR1A &= ~(_BV(U2X1));
#endif

    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); /* 8-bit data */
    UCSR1B = _BV(RXEN1) | _BV(TXEN1);   /* Enable RX and TX */
}

static void _init_uart_9600() {
#undef BAUD  // avoid compiler warning
#define BAUD 9600
#include <util/setbaud.h>

    UBRR1H = UBRRH_VALUE;
    UBRR1L = UBRRL_VALUE;

#if USE_2X
    UCSR1A |= _BV(U2X1);
#else
    UCSR1A &= ~(_BV(U2X1));
#endif

    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); /* 8-bit data */
    UCSR1B = _BV(RXEN1) | _BV(TXEN1);   /* Enable RX and TX */
}

static void _init_uart_38400() {
#undef BAUD  // avoid compiler warning
#define BAUD 38400
#include <util/setbaud.h>

    UBRR1H = UBRRH_VALUE;
    UBRR1L = UBRRL_VALUE;

#if USE_2X
    UCSR1A |= _BV(U2X1);
#else
    UCSR1A &= ~(_BV(U2X1));
#endif

    UCSR1C = _BV(UCSZ11) | _BV(UCSZ10); /* 8-bit data */
    UCSR1B = _BV(RXEN1) | _BV(TXEN1);   /* Enable RX and TX */
}

namespace stdavr {
namespace uart {

void init(BaudRate rate) {
    // Call appropriate UART init function
    switch (rate) {
        case BaudRate::k2400: {
            _init_uart_2400();
            break;
        }
        case BaudRate::k9600: {
            _init_uart_9600();
            break;
        }
        case BaudRate::k38400: {
            _init_uart_38400();
            break;
        }
    }

    // Configure streams
    streams::output.put = (int (*)(char, __file*))putc;
    streams::output.get = nullptr;
    streams::output.flags = _FDEV_SETUP_WRITE;
    streams::input.put = nullptr;
    streams::input.get = getc;
    streams::input.flags = _FDEV_SETUP_READ;
}

}  // namespace uart
}  // namespace stdavr
