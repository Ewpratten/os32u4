#include <os32u4/gpio/shiftregister.hh>

namespace os {
namespace gpio {
namespace shiftregister {

void send(const Pin &dataPin, const Pin &clkPin, ByteOrder order,
          uint8_t data) {
    // Send each byte over the data pin
    for (uint8_t i = 0; i < 8; i++) {
        // Handle byte ordering
        if (order == ByteOrder::kLSB) {
            pin::binaryWrite(dataPin, data & 1);
            data >>= 1;
        } else {
            pin::binaryWrite(dataPin, (data & 128) != 0);
            data <<= 1;
        }

        // Flip-flop the clock pin
        pin::binaryWrite(clkPin, true);
        pin::binaryWrite(clkPin, false);
    }
}

uint8_t recv(const Pin &dataPin, const Pin &clkPin, ByteOrder order) {
    // Data buffer
    uint8_t buf = 0;

    // Read 8 bits into buffer
    for (uint8_t i = 0; i < 8; ++i) {
        // Set the clock to READ
        pin::binaryWrite(clkPin, true);

        // Handle byte ordering
        if (order == ByteOrder::kLSB) {
            buf |= pin::binaryRead(dataPin) << i;
        } else {
            buf |= pin::binaryRead(dataPin) << (7 - i);
        }

        // Pull down the clock
        pin::binaryWrite(clkPin, false);
    }

    return buf;
}

}  // namespace shiftregister
}  // namespace gpio
}  // namespace os