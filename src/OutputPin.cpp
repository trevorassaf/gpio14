#include "OutputPin.h"

#include <utility>

namespace gpio {

OutputPin::OutputPin(Pin pin) : pin_(std::move(pin)) {}

OutputPin::~OutputPin() {}

uint8_t OutputPin::GetIndex() const {
  return pin_.GetIndex();
}

void OutputPin::Set() {
  pin_.Set();
}

void OutputPin::Clear() {
  pin_.Clear();
}

} // namespace gpio
