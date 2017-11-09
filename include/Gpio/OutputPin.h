#pragma once

#include <cstdint>

#include "Gpio/Pin.h"

namespace Gpio {

class OutputPin {
public:
  OutputPin(Pin pin);
  ~OutputPin();

  uint8_t GetIndex() const;

  // Asserts this pin.
  void Set();

  // Deasserts this pin.
  void Clear();

  // Returns true iff pin is hot.
  bool Read() const;

  OutputPin(OutputPin&& other) = default;
  OutputPin& operator=(OutputPin&& other) = default;

private:
  OutputPin(const OutputPin& other) = delete;
  OutputPin& operator=(const OutputPin& other) = delete;

private:
  Pin pin_;
};

} // namespace Gpio
