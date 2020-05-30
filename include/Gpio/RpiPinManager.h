#pragma once

#include <memory>

#include "Gpio/MemoryConfig.h"
#include "Gpio/OutputPin.h"
#include "Gpio/PinManager.h"
#include "Gpio/PinFactory.h"
#include "Memory/MmioBcm2835MemorySegment.h"
#include "Memory/MmioConfig.h"
#include "Memory/MemorySegment.h"

namespace Gpio
{
class RpiPinManager
{
public:
  RpiPinManager();

  // Designates specified pin as input pin.
  //
  // @pre-condition: Pin is not currently in use.
  std::unique_ptr<InputPin> BindInputPin(uint8_t pin_index);

  // Designates specified pin as output pin.
  //
  // @pre-condition: Pin is not currently in use.
  std::unique_ptr<OutputPin> BindOutputPin(uint8_t pin_index);

private:
  std::unique_ptr<Memory::MmioConfig> mmio_config_;
  std::unique_ptr<Gpio::MemoryConfig> memory_config_;
  std::unique_ptr<PinManager> pin_manager_;
  std::unique_ptr<PinFactory> pin_factory_;
};
}  // namespace Gpio
