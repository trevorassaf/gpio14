#include "Gpio/OutputPin.h"

#include <utility>

namespace Gpio {

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

bool OutputPin::Read() const {
  return pin_.Read();
}

} // namespace Gpio
