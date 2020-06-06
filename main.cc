#include <os32u4/gpio/pin.hh>
#include <os32u4/uart/uart.hh>
#include <os32u4/util/delay.hh>


void sysInit() {
    // Init UART registers on-board
    os::uart::init(os::uart::BaudRate::k9600);

    // Set up stream redirection
    os::uart::redirectSTDIO();

    // Log header
    puts("\nStarted os32u4");
    puts("Begining serial communication");
    puts("Hooked into STDIO");
}

int main(int argc, char const* argv[]) {
    // Run system init
    sysInit();

    // Configure a pin
    puts("Configuring board pin 9 for output");
    os::gpio::pin::configure(os::gpio::PinBank::kDigital, 9,
                                 os::gpio::PinMode::kOutput);

    // Write voltage to pin
    puts("Pulling pin 9 HIGH");
    os::gpio::pin::binaryWrite(os::gpio::PinBank::kDigital, 9, true);

    bool ledVal = true;
    for (;;) {
        os::util::delay::delayMS(500);
        ledVal = !ledVal;
        printf("Pin 9 set %s\n", (ledVal) ? "HIGH" : "LOW");
        os::gpio::pin::binaryWrite(os::gpio::PinBank::kDigital, 9,
                                       ledVal);
    }

    // Do nothing (this is just to keep the system running)
    puts("System idle");
    for (;;) {
    }
    return 0;
}
