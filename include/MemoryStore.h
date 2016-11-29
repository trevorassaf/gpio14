#pragma once

#include <cstdint>
#include <memory>

#include "MemoryConfig.h"
#include "MemorySegment.h"

namespace gpio {

class MemoryStore {
  public:
   MemoryStore(
       std::shared_ptr<MemoryConfig> memory_config,
       std::unique_ptr<MemorySegment> memory_segment);

   volatile uint64_t* GetSelectPinFunctionPtr();
   volatile uint64_t* GetSetPinPtr();
   volatile uint64_t* GetClearPinPtr();
   volatile uint64_t* GetReadPinLevelPtr();

  private:
   // Offsets for accessing gpio memory registers.
   std::shared_ptr<MemoryConfig> memory_config_;

   // Pointer to the memory segment that controls gpio peripherals.
   std::unique_ptr<MemorySegment> memory_segment_;
};

} // namespace gpio
