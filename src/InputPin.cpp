#include "InputPin.h"

#include <utility>

namespace gpio {

InputPin::InputPin(Pin pin) : pin_(std::move(pin)) {}

InputPin::~InputPin() {}

const Pin& InputPin::GetPin() const {
  return pin_;
}

} // namespace gpio
