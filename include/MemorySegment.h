#pragma once

#include <cstdint>

namespace gpio {

class MemorySegment {
 public:
  virtual volatile uint8_t* Get() = 0;
  virtual ~MemorySegment() {}
};

} // namespace gpio
