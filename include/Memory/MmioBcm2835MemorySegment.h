#pragma once

#include <memory>

#include "Memory/MemorySegment.h"
#include "Memory/MmioConfig.h"

namespace Memory
{

class MmioBcm2835MemorySegment : public MemorySegment
{
 public:
  MmioBcm2835MemorySegment(const MmioConfig *mmioConfig);
  ~MmioBcm2835MemorySegment() override;

  volatile uint8_t* Get() override;
  volatile const uint8_t* Get() const override;

 private:
	const MmioConfig *m_mmioConfig;
  volatile uint8_t* m_memory;
};

} // namespace Memory
