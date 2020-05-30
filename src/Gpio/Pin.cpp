#include "Gpio/Pin.h"

#include <cassert>
#include <utility>

#include "glog/logging.h"

namespace Gpio {

Pin::Pin(
		PinManager *pinManager,
    uint8_t index)
  : m_pinManager{pinManager},
    m_index{index} {}

Pin::~Pin()
{
  CloseResources();
}

Pin::Pin(Pin &&other)
{
  StealResources(&other);
}

Pin &Pin::operator=(Pin &&other)
{
  if (this != &other)
  {
    CloseResources();
    StealResources(&other);
  }
  return *this;
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

void Pin::CloseResources()
{
  LOG(ERROR) << "Pin::CloseResources() -- call: index=" << (int)m_index;
  if (m_pinManager) {
    LOG(ERROR) << "Pin::CloseResources() -- m_pinManager->ReleasePin()";
    m_pinManager->ReleasePin(m_index);
    m_pinManager = nullptr;
  }
  LOG(ERROR) << "Pin::CloseResources() -- end";
}

void Pin::StealResources(Pin *other)
{
  assert(other);
  m_index = other->m_index;
  m_pinManager = other->m_pinManager;
  other->m_pinManager = nullptr;
}

} // namespace Gpio
