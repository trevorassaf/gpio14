#pragma once

#include <cstdint>

#include "Pin.h"

namespace gpio {

class InputPin {
 public:
  InputPin(Pin pin);
  ~InputPin();

  uint8_t GetIndex() const;

  // Returns true iff pin is asserted.
  bool Read() const;

 private:
  Pin pin_;
};

} // namespace gpio
