/**
 * The following documents help a lot with porting my os328 UART code to 32u4
 * boards:
 * 
 *  - https://appelsiini.net/2011/simple-usart-with-avr-libc/
 *  - https://arduino.stackexchange.com/questions/19355/uart-error-can-not-compile-on-arduino-yun-atmega32u4
 *  - https://cache.amobbs.com/bbs_upload782111/files_22/ourdev_508497.html
 *  - https://www.avrfreaks.net/forum/fdevsetupstream-c
 */

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
    streams::output.put = (int (*)(char, __file *))putc;
    streams::output.get = nullptr;
    streams::output.flags = _FDEV_SETUP_WRITE;
    streams::input.put = nullptr;
    streams::input.get = getc;
    streams::input.flags = _FDEV_SETUP_READ;

    // Overwrite default streams
    stdout = &uart_output;
    stdin = &uart_input;
}

void putc(char c, FILE *stream) {
    if (c == '\n') {
        uart_putchar('\r', stream);
    }

    // Wait for data
    loop_until_bit_is_set(UCSR0A, UDRE0);
    UDR0 = c;
}

void getc(FILE *stream __attribute__((unused))) {
    // Wait for data
    loop_until_bit_is_set(UCSR0A, RXC0);
    return UDR0;
}

}  // namespace uart
}  // namespace stdavr
