#if !defined(_OS_GPIO_PIN_HH)
#define _OS_GPIO_PIN_HH

#include <avr/common.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <vendor/promicro/pins_arduino.h>

// These are derived from Arduino.h
#define digitalPinToPort(P) (pgm_read_byte(digital_pin_to_port_PGM + (P)))
#define digitalPinToBitMask(P) \
    (pgm_read_byte(digital_pin_to_bit_mask_PGM + (P)))
#define digitalPinToTimer(P) (pgm_read_byte(digital_pin_to_timer_PGM + (P)))
#define analogInPinToBit(P) (P)
#define portOutputRegister(P) \
    ((volatile uint8_t *)(pgm_read_word(port_to_output_PGM + (P))))
#define portInputRegister(P) \
    ((volatile uint8_t *)(pgm_read_word(port_to_input_PGM + (P))))
#define portModeRegister(P) \
    ((volatile uint8_t *)(pgm_read_word(port_to_mode_PGM + (P))))


namespace os {
namespace gpio {

// Pin data
enum class PinMode { kInput = 0x00, kOutput = 0x01, kInputPullup = 0x02 };
enum class PinBank { kAnalog = 0, kDigital = 1 };

// Reference voltages
enum class ReferenceVoltage {
    kDefault = 0,
    kExternal = 1,
    kInternal1v1 = 2,
    kInternal = 2
};

namespace pin {

/**
 * Configure pin's mode
 *
 * @param type Pin I/O type
 * @param id Pin id
 * @param mode Pin I/O mode
 */
void configure(PinBank bank, unsigned int id, PinMode mode);

// Binary I/O
void binaryWrite(PinBank bank, unsigned int id, bool enabled);
bool binaryRead(PinBank bank, unsigned int id);

// Analog I/O
void setBoardReference(ReferenceVoltage voltage);
void analogWrite(PinBank bank, unsigned int id, int output);
int analogRead(PinBank bank, unsigned int id);

// Convert pin numbers to arduino-style pins
unsigned char toArduinoPin(PinBank bank, unsigned int id);

}  // namespace pin
}  // namespace gpio
}  // namespace os

#endif  // _OS_GPIO_PIN_HH
