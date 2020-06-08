#if !defined(_APP_7SEGTEST_HH)
#define _APP_7SEGTEST_HH

#include <stdio.h>

#include <os32u4/drivers/7segment.hh>
#include <os32u4/gpio/pin.hh>
#include <os32u4/process/process.hh>

// A test process that flashes a light
class SingleSevenSegTest : public os::process::Process {
   public:
    SingleSevenSegTest(const os::gpio::Pin &, const os::gpio::Pin &,
                       const os::gpio::Pin &, unsigned long);
    void init() override;
    void runIteration(unsigned long) override;
    bool isFinished() override { return false; }
    void end() override {}

   private:
    // Display
    os::drivers::SingleSevenSegment *display;

    // Pins
    os::gpio::Pin dataPin;
    os::gpio::Pin clkPin;
    os::gpio::Pin latchPin;

    // Data
    unsigned long delay;
    unsigned long timeNow = 0l;
    unsigned long lastWriteTime = 0l;
    uint8_t counter = 0;
};

#endif  // _APP_7SEGTEST_HH
