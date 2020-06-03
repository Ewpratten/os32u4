#include <stdavr/gpio/pin.hh>

int main(int argc, char const *argv[]) {
    // Configure a pin
    stdavr::gpio::pin::configure(stdavr::gpio::PinBank::kDigital, 9,
                                 stdavr::gpio::PinMode::kOutput);

    // Write voltage to pin
    stdavr::gpio::pin::binaryWrite(stdavr::gpio::PinBank::kDigital, 9, true);

    // Do nothing
    for (;;) {
    }
    return 0;
}
