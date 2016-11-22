#pragma once

#include <cstdint>

#include "Pin.h"

namespace gpio {

class OutputPin {
 public:
  OutputPin(Pin pin);
  ~OutputPin();

  uint8_t GetPinIndex() const;

  void Set();
  void Clear();

 private:
  Pin pin_;
};

} // namespace gpio
