/**
 * The following documents help a lot with porting my os328 UART code to 32u4
 * boards:
 *
 *  - https://appelsiini.net/2011/simple-usart-with-avr-libc/
 *  -
 * https://arduino.stackexchange.com/questions/19355/uart-error-can-not-compile-on-arduino-yun-atmega32u4
 *  - https://cache.amobbs.com/bbs_upload782111/files_22/ourdev_508497.html
 *  - https://www.avrfreaks.net/forum/fdevsetupstream-c
 *  - https://www.avrfreaks.net/forum/atmega32u4-serial-communication-question
 */

#include <avr/io.h>
#include <vendor/promicro/pins_arduino.h>

#include <os32u4/uart/baudutil.hh>
#include <os32u4/uart/uart.hh>

namespace os {
namespace uart {

void init(BaudRate rate) {
    // Configure BAUD
    // NOTE: the BaudRate enum contains baud/100. Must multiply to get baud
    unsigned long ubrr = os::uart::baudutil::calcUBRR((int)rate * 100);
    UBRR1H = (unsigned char)(ubrr >> 8);
    UBRR1L = (unsigned char)ubrr;

    // Allow RX and TX
    UCSR1B = (1 << TXEN1) | (1 << RXEN1);

    // Set data format
    // 8b of data + 2b stop
    UCSR1C = (1 << USBS1) | (3 << UCSZ10);

    // Init I/O leds
    TX_RX_LED_INIT;
    TXLED1;
    RXLED1;
}

void redirectSTDIO() {
    // Configure streams
    FILE *io;
    // io.put = (int (*)(char, __file *))stream::putch;
    // io.get = (int (*)(__file *))stream::getch;
    // io.flags = _FDEV_SETUP_WRITE | _FDEV_SETUP_READ;

    io = fdevopen(stream::putch, stream::getch);

    // Overwrite default streams
    stdout = stdin = io;
}

void putch(char c) {
    if (c == '\n') {
        putch('\r');
    }

    // Handle LED
    TXLED0;
    if (c == '\n') {
        TXLED1;
    }

    // Wait for data
    loop_until_bit_is_set(UCSR1A, UDRE1);
    UDR1 = c;
}

char getch() {
    // Wait for data
    loop_until_bit_is_set(UCSR1A, RXC1);

    char c = UDR1;

    // Handle LED
    RXLED0;
    if (c == '\n') {
        RXLED1;
    }

    return c;
}

namespace stream {

int putch(char c, FILE *stream) {
    os::uart::putch(c);
    return 1;
}

int getch(FILE *stream __attribute__((unused))) {
    return os::uart::getch();
}

}  // namespace stream
}  // namespace uart
}  // namespace stdavr
