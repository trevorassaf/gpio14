#pragma once

#include <cstdint>

namespace Memory {

class MemorySegment {
 public:
  virtual volatile uint8_t* Get() = 0;
  virtual volatile const uint8_t* Get() const = 0;
  virtual ~MemorySegment() {}
};

} // namespace Memory
