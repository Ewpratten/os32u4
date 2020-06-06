#include <stdavr/gpio/pin.hh>
#include <stdavr/uart/uart.hh>
#include <stdavr/util/delay.hh>


void sysInit() {
    // Init UART registers on-board
    stdavr::uart::init(stdavr::uart::BaudRate::k9600);

    // Set up stream redirection
    stdavr::uart::redirectSTDIO();

    // Log header
    puts("Started os32u4");
    puts("Begining serial communication");
    puts("Hooked into STDIO");
}

int main(int argc, char const* argv[]) {
    // Run system init
    sysInit();

    // Configure a pin
    puts("Configuring board pin 9 for output");
    stdavr::gpio::pin::configure(stdavr::gpio::PinBank::kDigital, 9,
                                 stdavr::gpio::PinMode::kOutput);

    // Write voltage to pin
    puts("Pulling pin 9 HIGH");
    stdavr::gpio::pin::binaryWrite(stdavr::gpio::PinBank::kDigital, 9, true);

    bool ledVal = true;
    for (;;) {
        stdavr::util::delay::delayMS(500);
        ledVal = !ledVal;
        printf("Pin 9 set %s\n", (ledVal) ? "HIGH" : "LOW");
        stdavr::gpio::pin::binaryWrite(stdavr::gpio::PinBank::kDigital, 9,
                                       ledVal);
    }

    // Do nothing (this is just to keep the system running)
    puts("System idle");
    for (;;) {
    }
    return 0;
}
