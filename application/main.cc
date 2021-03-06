#include <avr/interrupt.h>

#include <7segtest.hh>
#include <ledblink.hh>
#include <os32u4/gpio/pin.hh>
#include <os32u4/process/procd.hh>
#include <os32u4/process/process.hh>
#include <os32u4/uart/uart.hh>

bool hasBooted = false;

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

inline void startProc(os::process::Process* p) {
    int pid = os::process::scheduler::start(p);

    if (pid != -1) {
        printf("Started process %d\n", pid);
    } else {
        puts("Process failed to start. Too many processes running");
    }
}

void procInit() {
    using namespace os::gpio;
    puts("Starting system processes");

    startProc(new LEDBlinkProc(Pin{PinBank::kDigital, 9}, 500l));
    startProc(new LEDBlinkProc(Pin{PinBank::kDigital, 8}, 250l));

    // Set up 7seg test process
    startProc(new SingleSevenSegTest(Pin{PinBank::kDigital, 14},
                                     Pin{PinBank::kDigital, 15},
                                     Pin{PinBank::kDigital, 16}, 1000l));
}

int main(int argc, char const* argv[]) {
    // Disable USB ints and enable global ints
    USBCON = 0;
    sei();

    // Handle boot wipe
    if (hasBooted) {
        return 0;
    }
    hasBooted = true;

    // Run system init
    sysInit();

    // Set up system processes
    procInit();

    bool ledVal = true;
    for (;;) {
        // Run an interation of the scheduler
        os::process::scheduler::runIteration();
    }

    return 0;
}
