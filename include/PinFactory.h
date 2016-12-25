#pragma once

#include <memory>

#include "PinManager.h"
#include "InputPin.h"
#include "OutputPin.h"

namespace gpio {

class PinFactory {
 public:
  PinFactory(std::shared_ptr<PinManager> pin_manager);

  // Designates specified pin as input pin.
  //
  // @pre-condition: Pin is not currently in use.
  std::unique_ptr<InputPin> BindInputPin(uint8_t pin_index);

  // Designates specified pin as output pin.
  //
  // @pre-condition: Pin is not currently in use.
  std::unique_ptr<OutputPin> BindOutputPin(uint8_t pin_index);

 private:
  std::shared_ptr<PinManager> pin_manager_;
};

} // namespcae gpio
