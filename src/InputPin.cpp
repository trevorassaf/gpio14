#include "InputPin.h"

#include <utility>

namespace gpio {

InputPin::InputPin(Pin pin) : pin_(std::move(pin)) {}

InputPin::~InputPin() {}

uint8_t InputPin::GetIndex() const {
  return pin_.GetIndex();
}

bool InputPin::Read() const {
  return pin_.Read();
}

} // namespace gpio
