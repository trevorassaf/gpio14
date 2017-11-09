#pragma once

#include <memory>

#include "Gpio/PinManager.h"
#include "Gpio/InputPin.h"
#include "Gpio/OutputPin.h"

namespace Gpio {

class PinFactory {
 public:
  PinFactory(PinManager *pin_manager);

  // Designates specified pin as input pin.
  //
  // @pre-condition: Pin is not currently in use.
  std::unique_ptr<InputPin> BindInputPin(uint8_t pin_index);

  // Designates specified pin as output pin.
  //
  // @pre-condition: Pin is not currently in use.
  std::unique_ptr<OutputPin> BindOutputPin(uint8_t pin_index);

 private:
	PinManager *m_pinManager;
};

} // namespcae gpio
