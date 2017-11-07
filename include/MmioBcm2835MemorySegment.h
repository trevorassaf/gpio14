#pragma once

#include <memory>

#include "MemorySegment.h"
#include "MemoryConfig.h"

namespace gpio
{

class MmioBcm2835MemorySegment : public MemorySegment
{
 public:
  MmioBcm2835MemorySegment(const MemoryConfig *memoryConfig);
  ~MmioBcm2835MemorySegment() override;

  volatile uint8_t* Get() override;

 private:
	const MemoryConfig *m_memoryConfig;
  volatile uint8_t* m_memory;
};

} // namespace gpio
