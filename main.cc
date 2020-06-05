#include <stdavr/gpio/pin.hh>
#include <stdavr/uart/uart.hh>
#include <util/delay.h>

// void sysInit() {
//     // Init UART registers on-board
//     stdavr::uart::init(stdavr::uart::BaudRate::k9600);

//     // Write out system boot header
//     const char *bootMSG = "Started os32u4\nBegining serial communication";
//     for (int i = 0; i < sizeof(bootMSG) / sizeof(bootMSG[0]); i++) {
//         stdavr::uart::putch(bootMSG[i]);
//     }

//     // Set up stream redirection
//     stdavr::uart::redirectSTDIO();
//     printf("Hooked into STDIO\n");
// }

// #define DELAY_CYCLES 2000000
// int i = 0;
// bool ledval = true;
// void cycle() {
//     if (i >= DELAY_CYCLES) {
//         i = 0;

//         ledval = !ledval;

//         stdavr::gpio::pin::binaryWrite(stdavr::gpio::PinBank::kDigital, 9,
//                                        ledval);
//     }

//     i++;
// }

int main(int argc, char const* argv[]) {
    // Run system init
    // sysInit();

    // Configure a pin
    // printf("Configuring board pin 9 for output");
    stdavr::gpio::pin::configure(stdavr::gpio::PinBank::kDigital, 9,
                                 stdavr::gpio::PinMode::kOutput);

    // // Write voltage to pin
    // printf("Pulling pin 9 HIGH");
    stdavr::gpio::pin::binaryWrite(stdavr::gpio::PinBank::kDigital, 9, true);

    // // Do nothing
    // printf("System idle");
    bool ledVal = true;
    for (;;) {
        _delay_ms(1000);
        ledVal = !ledVal;
        stdavr::gpio::pin::binaryWrite(stdavr::gpio::PinBank::kDigital, 9, ledVal);
    }

    return 0;
}
