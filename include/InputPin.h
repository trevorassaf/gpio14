#pragma once

#include <cstdint>

#include "Pin.h"

namespace gpio {

class InputPin {
 public:
  InputPin(Pin pin);
  ~InputPin();

  InputPin(InputPin&& other) = default;
  InputPin& operator=(InputPin&& other) = default;

  uint8_t GetIndex() const;

  // Returns true iff pin is asserted.
  bool Read() const;

private:
  InputPin(const InputPin& other) = delete;
  InputPin& operator=(const InputPin& other) = delete;

 private:
  Pin pin_;
};

} // namespace gpio
