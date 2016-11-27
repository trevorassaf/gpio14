#include "PinFactory.h"

#include <utility>

#include "PinType.h"

namespace gpio {

PinFactory::PinFactory(std::shared_ptr<PinManager> pin_manager)
    : pin_manager_(std::move(pin_manager)) {}

InputPin PinFactory::BindInputPin(uint8_t pin_index) {
  pin_manager_->BindPin(pin_index, PinType::INPUT);
  Pin pin(pin_manager_, pin_index);
  return InputPin(std::move(pin));
}

OutputPin PinFactory::BindOutputPin(uint8_t pin_index) {
  pin_manager_->BindPin(pin_index, PinType::OUTPUT);
  Pin pin(pin_manager_, pin_index);
  return OutputPin(std::move(pin));
}

} // namespace gpio
