#include <stdavr/gpio/pin.hh>

namespace stdavr {
namespace gpio {
namespace pin {

uint8_t toArduinoPin(PinBank bank, unsigned int id) { 
    if (bank == PinBank::kAnalog){
        return A0 + id;
    }else{
        return id;
    }
}

}  // namespace pin
}  // namespace gpio
}  // namespace stdavr