#include <ledblink.hh>


LEDBlinkProc::LEDBlinkProc(const os::gpio::Pin &pin, unsigned long delay_msec) {
    this->pin = pin;
    this->delay = delay_msec;

}

void LEDBlinkProc::init()  {
    // Configure pin
    printf("Configuring %s pin %d for output\n",
           (this->pin.bank == os::gpio::PinBank::kAnalog) ? "analog" : "digital",
           this->pin.channel);
    os::gpio::pin::configure(this->pin, os::gpio::PinMode::kOutput);

    // Pull the pin HIGH
    printf("Pulling pin %d HIGH\n", this->pin.channel);
    os::gpio::pin::binaryWrite(this->pin, true);
    this->value = true;
}

void LEDBlinkProc::runIteration(unsigned long dt)  {
    // Update the current time
    this->timeNow += dt;

    // Only blink if we have passed the delay time
    if (this->timeNow - this->lastBlinkTime < this->delay) {
        return;
    }

    // Set the last blink time
    this->lastBlinkTime = this->timeNow;

    // FLip the LED value
    this->value = !this->value;

    // Log
    printf("Pin %d set %s\n", this->pin.channel, (this->value) ? "HIGH" : "LOW");

    // Write to pin
    os::gpio::pin::binaryWrite(this->pin, this->value);
}