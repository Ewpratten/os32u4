#include <7segtest.hh>

SingleSevenSegTest::SingleSevenSegTest(const os::gpio::Pin& dataPin,
                                       const os::gpio::Pin& clkPin,
                                       const os::gpio::Pin& latchPin,
                                       unsigned long delay) {
    // Set up pins
    this->dataPin = dataPin;
    this->clkPin = clkPin;
    this->latchPin = latchPin;

    // Set delay
    this->delay = delay;

    // Set up display
    this->display =
        new os::drivers::SingleSevenSegment(dataPin, clkPin, latchPin);
}

void SingleSevenSegTest::init() {
    using namespace os::gpio;

    printf("Configuring pins [%d, %d, %d] for output\n", this->dataPin.channel,
           this->clkPin.channel, this->latchPin.channel);

    // Configure all pins
    pin::configure(this->dataPin, PinMode::kOutput);
    pin::configure(this->clkPin, PinMode::kOutput);
    pin::configure(this->latchPin, PinMode::kOutput);
}

void SingleSevenSegTest::runIteration(unsigned long dt) {
    // Update the current time
    this->timeNow += dt;

    // Only blink if we have passed the delay time
    if (this->timeNow - this->lastWriteTime < this->delay) {
        return;
    }

    // Set the last write time
    this->lastWriteTime = this->timeNow;

    printf("Writing %x to display\n", this->counter);

    // Write the current digit
    this->display->setHex(this->counter);

    // Incr the counter (and wrap at 15)
    this->counter++;
    this->counter %= 16;
}