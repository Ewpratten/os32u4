# os32u4
A Kernel for use on 32u4 AVR chips

## Timers

The following timers are used by os32u4:

| Timer   | Resolution | Usage       |
|---------|------------|-------------|
| `TCCR0` | 8bit       | Timekeeping |
| `TCCR3` | 8bit       | PWM         |

## Documentation

 - [AVRASM2](http://ww1.microchip.com/downloads/en/devicedoc/40001917a.pdf)
 - [32u4 datasheet](http://ww1.microchip.com/downloads/en/devicedoc/atmel-7766-8-bit-avr-atmega16u4-32u4_datasheet.pdf)
 - [Interrupts guide](https://www.avrfreaks.net/sites/default/files/Interrupt.pdf)
 - [avr-libc](https://www.nongnu.org/avr-libc)
 - [32u4 timers](http://medesign.seas.upenn.edu/index.php/Guides/MaEvArM-timers)
 - [Arduino Core](https://github.com/arduino/ArduinoCore-avr)
 - [MCUdude](https://github.com/MCUdude)