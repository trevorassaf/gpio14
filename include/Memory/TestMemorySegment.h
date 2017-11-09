#pragma once

#include <memory>

#include "Memory/MemorySegment.h"
#include "Memory/MemoryConfig.h"

namespace Memory {

class TestMemorySegment : public MemorySegment {
 public:
  TestMemorySegment(const MemoryConfig *memoryConfig);
  volatile uint8_t* Get() override;

 private:
	const MemoryConfig *m_memoryConfig;
  std::unique_ptr<volatile uint8_t[]> m_memorySegmentPtr;
};

} // namespace Memory
