#include "InputPin.h"

#include <utility>

namespace gpio {

InputPin::InputPin(Pin pin) : pin_(std::move(pin)) {}

InputPin::~InputPin() {}

uint8_t InputPin::GetPinIndex() const {
  return pin_.GetIndex();
}

} // namespace gpio
