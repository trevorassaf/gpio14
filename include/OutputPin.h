#pragma once

#include <cstdint>

#include "Pin.h"

namespace gpio {

class OutputPin {
public:
  OutputPin(Pin pin);
  ~OutputPin();

  uint8_t GetIndex() const;

  // Asserts this pin.
  void Set();

  // Deasserts this pin.
  void Clear();

  OutputPin(OutputPin&& other) = default;
  OutputPin& operator=(OutputPin&& other) = default;

private:
  OutputPin(const OutputPin& other) = delete;
  OutputPin& operator=(const OutputPin& other) = delete;

private:
  Pin pin_;
};

} // namespace gpio
