#pragma once

#include <cstdint>

#include "Pin.h"

namespace gpio {

class InputPin {
 public:
  InputPin(Pin pin);
  ~InputPin();

  uint8_t GetPinIndex() const;

 private:
  Pin pin_;
};

} // namespace gpio
