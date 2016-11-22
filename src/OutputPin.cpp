#include "OutputPin.h"

#include <utility>

namespace gpio {

OutputPin::OutputPin(Pin pin) : pin_(std::move(pin)) {}

OutputPin::~OutputPin() {}

uint8_t OutputPin::GetPinIndex() const {
  return pin_.GetIndex();
}

} // namespace gpio
