#include <ledblink.hh>


LEDBlinkProc::LEDBlinkProc(os::gpio::PinBank bank, unsigned int pin, unsigned long delay_msec) {
    this->bank = bank;
    this->pin = pin;
    this->delay = delay_msec;

}

void LEDBlinkProc::init()  {
    // Configure pin
    printf("Configuring %s pin %d for output\n",
           (this->bank == os::gpio::PinBank::kAnalog) ? "analog" : "digital",
           this->pin);
    os::gpio::pin::configure(this->bank, this->pin, os::gpio::PinMode::kOutput);

    // Pull the pin HIGH
    printf("Pulling pin %d HIGH\n", this->pin);
    os::gpio::pin::binaryWrite(this->bank, this->pin, true);
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
    printf("Pin %d set %s\n", this->pin, (this->value) ? "HIGH" : "LOW");

    // Write to pin
    os::gpio::pin::binaryWrite(this->bank, this->pin, this->value);
}