#include "PinFactory.h"

#include <utility>

#include "PinType.h"

namespace gpio {

PinFactory::PinFactory(PinManager *pinManager)
    : m_pinManager{pinManager} {}

std::unique_ptr<InputPin> PinFactory::BindInputPin(uint8_t pinIndex) {
  m_pinManager->BindPin(pinIndex, PinType::INPUT);
  Pin pin(m_pinManager, pinIndex);
  return std::make_unique<InputPin>(std::move(pin));
}

std::unique_ptr<OutputPin> PinFactory::BindOutputPin(uint8_t pinIndex) {
  m_pinManager->BindPin(pinIndex, PinType::OUTPUT);
  Pin pin(m_pinManager, pinIndex);
  return std::make_unique<OutputPin>(std::move(pin));
}

} // namespace gpio
