#pragma once

#include <memory>

#include "Memory/MemorySegment.h"
#include "Memory/MmioConfig.h"

namespace Memory {

class TestMemorySegment : public MemorySegment {
 public:
  TestMemorySegment(const MmioConfig *mmioConfig);
  volatile uint8_t* Get() override;

 private:
	const MmioConfig *m_mmioConfig;
  std::unique_ptr<volatile uint8_t[]> m_memorySegmentPtr;
};

} // namespace Memory
