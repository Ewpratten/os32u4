#include <ledblink.hh>
#include <os32u4/gpio/pin.hh>
#include <os32u4/process/procd.hh>
#include <os32u4/process/process.hh>
#include <os32u4/uart/uart.hh>

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

void startProc(os::process::Process* p) {
    int pid = os::process::scheduler::start(p);

    if (pid != -1) {
        printf("Started process %d\n", pid);
    }else{
        puts("Process failed to start. Too many processes running");
    }
}

void procInit() {
    puts("Starting system processes");

    startProc(new LEDBlinkProc(os::gpio::PinBank::kDigital, 9, 0.5));
}

int main(int argc, char const* argv[]) {
    // Run system init
    sysInit();

    // Set up system processes
    procInit();

    bool ledVal = true;
    for (;;) {
        // os::util::delay::delayMS(500);
        // ledVal = !ledVal;
        // printf("Pin 9 set %s\n", (ledVal) ? "HIGH" : "LOW");
        // os::gpio::pin::binaryWrite(os::gpio::PinBank::kDigital, 9, ledVal);

        // Run an interation of the scheduler
        os::process::scheduler::runIteration();
    }

    // Do nothing (this is just to keep the system running)
    puts("System idle");
    for (;;) {
    }
    return 0;
}
