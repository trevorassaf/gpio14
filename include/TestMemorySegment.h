#pragma once

#include <memory>

#include "MemorySegment.h"
#include "MemoryConfig.h"

namespace gpio {

class TestMemorySegment : public MemorySegment {
 public:
  TestMemorySegment(const MemoryConfig *memoryConfig);
  volatile uint8_t* Get() override;

 private:
	const MemoryConfig *m_memoryConfig;
  std::unique_ptr<volatile uint8_t[]> m_memorySegmentPtr;
};

} // namespace gpio
