#include "Memory/TestMemorySegment.h"

#include <utility>

namespace Memory {

TestMemorySegment::TestMemorySegment(
		const MmioConfig *mmioConfig
) : m_mmioConfig{mmioConfig} {
  m_memorySegmentPtr = std::make_unique<volatile uint8_t[]>(
      m_mmioConfig->GetMappedBytesCount());
}

volatile uint8_t* TestMemorySegment::Get() {
  return m_memorySegmentPtr.get();
}

} // namespace Memory
