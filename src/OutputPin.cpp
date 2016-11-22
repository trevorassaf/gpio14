#include "OutputPin.h"

#include <utility>

namespace gpio {

OutputPin::OutputPin(Pin pin) : pin_(std::move(pin)) {}

OutputPin::~OutputPin() {}

const Pin& OutputPin::GetPin() const {
  return pin_;
}

} // namespace gpio
