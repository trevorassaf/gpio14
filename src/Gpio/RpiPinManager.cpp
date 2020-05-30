#include "Gpio/RpiPinManager.h"

#include <cassert>
#include <memory>
#include <utility>

#include "Gpio/MemoryConfig.h"
#include "Gpio/OutputPin.h"
#include "Gpio/PinManager.h"
#include "Gpio/PinFactory.h"
#include "Memory/MmioBcm2835MemorySegment.h"
#include "Memory/MemorySegment.h"

namespace
{
using Memory::MemorySegment;
using Memory::MmioConfig;
using Memory::MmioBcm2835MemorySegment;
}  // namespace

namespace Gpio
{

RpiPinManager::RpiPinManager()
  : mmio_config_{std::make_unique<MmioConfig>(MmioConfig::MakeGpioConfig())},
    memory_config_{std::make_unique<MemoryConfig>()},
    pin_manager_{std::make_unique<PinManager>(
        mmio_config_.get(),
        memory_config_.get(),
        std::make_unique<MmioBcm2835MemorySegment>(mmio_config_.get()))},
    pin_factory_{std::make_unique<PinFactory>(pin_manager_.get())} {}

std::unique_ptr<InputPin> RpiPinManager::BindInputPin(uint8_t pin_index)
{
  return std::move(pin_factory_->BindInputPin(pin_index));
}

std::unique_ptr<OutputPin> RpiPinManager::BindOutputPin(uint8_t pin_index)
{
  return std::move(pin_factory_->BindOutputPin(pin_index));
}

}  // namespace Gpio
