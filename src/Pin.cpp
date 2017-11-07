#include "Pin.h"

#include <utility>

namespace gpio {

Pin::Pin(
		PinManager *pinManager,
    uint8_t index)
  : m_pinManager{std::move(pinManager)},
    m_index{index} {}

Pin::~Pin() {
  if (m_pinManager) {
    m_pinManager->ReleasePin(m_index);
  }
}

uint8_t Pin::GetIndex() const {
  return m_index;
}

void Pin::Set() {
  m_pinManager->SetPin(m_index);
}

void Pin::Clear() {
  m_pinManager->ClearPin(m_index);
}

bool Pin::Read() const {
  return m_pinManager->ReadPin(m_index);
}

} // namespace gpio
