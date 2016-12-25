#include "PinFactory.h"

#include <utility>

#include "PinType.h"

namespace gpio {

PinFactory::PinFactory(std::shared_ptr<PinManager> pin_manager)
    : pin_manager_(std::move(pin_manager)) {}

std::unique_ptr<InputPin> PinFactory::BindInputPin(uint8_t pin_index) {
  pin_manager_->BindPin(pin_index, PinType::INPUT);
  Pin pin(pin_manager_, pin_index);
  return std::make_unique<InputPin>(std::move(pin));
}

std::unique_ptr<OutputPin> PinFactory::BindOutputPin(uint8_t pin_index) {
  pin_manager_->BindPin(pin_index, PinType::OUTPUT);
  Pin pin(pin_manager_, pin_index);
  return std::make_unique<OutputPin>(std::move(pin));
}

} // namespace gpio
