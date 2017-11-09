#include "Memory/TestMemorySegment.h"

#include <utility>

namespace Memory {

TestMemorySegment::TestMemorySegment(
		const MemoryConfig *memoryConfig
) : m_memoryConfig{memoryConfig} {
  m_memorySegmentPtr = std::make_unique<volatile uint8_t[]>(
      m_memoryConfig->GetMappedBytesCount());
}

volatile uint8_t* TestMemorySegment::Get() {
  return m_memorySegmentPtr.get();
}

} // namespace Memory
