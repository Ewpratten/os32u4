#if !defined(_APP_LEDBLINK_HH)
#define _APP_LEDBLINK_HH

#include <os32u4/process/process.hh>
#include <os32u4/gpio/pin.hh>
#include <stdio.h>

// A test process that flashes a light
class LEDBlinkProc: public os::process::Process {
    public:
     LEDBlinkProc(os::gpio::PinBank, unsigned int, unsigned long);
     void init() override;
     void runIteration(unsigned long) override;
     bool isFinished() override { return false; }
     void end() override {}

    private:
     os::gpio::PinBank bank;
     unsigned int pin;
     bool value;
     double delay;
     double lastBlinkTime = 0.0;
     unsigned long timeNow = 0.0;
};

#endif // _APP_LEDBLINK_HH
