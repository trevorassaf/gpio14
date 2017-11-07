#pragma once

#include <cstdint>
#include <memory>

#include "MemoryConfig.h"
#include "MemorySegment.h"

namespace gpio {

class MemoryStore {
  public:
   MemoryStore(
			 const MemoryConfig *memoryConfig,
       std::unique_ptr<MemorySegment> m_memorySegment);

   volatile uint64_t* GetSelectPinFunctionPtr();
   volatile uint64_t* GetSetPinPtr();
   volatile uint64_t* GetClearPinPtr();
   volatile uint64_t* GetReadPinLevelPtr();

  private:
   // Offsets for accessing gpio memory registers.
	 const MemoryConfig *m_memoryConfig;

   // Pointer to the memory segment that controls gpio peripherals.
   std::unique_ptr<MemorySegment> m_memorySegment;
};

} // namespace gpio
