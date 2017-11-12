#include "I2c/Registers/BscMasterRegisters.h"

#include <utility>

using Memory::MmioBcm2835MemorySegment;

namespace I2c
{
BscMasterRegisters::BscMasterRegisters(
		std::unique_ptr<MmioBcm2835MemorySegment> mmioSegment,
		const MemoryConfig *memoryConfig)
	: m_mmioSegment{std::move(mmioSegment)},
		m_memoryConfig{memoryConfig} {}

volatile uint32_t * BscMasterRegisters::GetControlRegister()
{
  return reinterpret_cast<volatile uint32_t *>(m_mmioSegment->Get() + m_memoryConfig->GetControlOffset());
}

volatile uint32_t * BscMasterRegisters::GetStatusRegister()
{
  return reinterpret_cast<volatile uint32_t *>(m_mmioSegment->Get() + m_memoryConfig->GetStatusOffset());
}

volatile uint32_t * BscMasterRegisters::GetDataLengthRegister()
{
  return reinterpret_cast<volatile uint32_t *>(m_mmioSegment->Get() + m_memoryConfig->GetDataLengthOffset());
}

volatile uint32_t * BscMasterRegisters::GetSlaveAddressRegister()
{
  return reinterpret_cast<volatile uint32_t *>(m_mmioSegment->Get() + m_memoryConfig->GetSlaveAddressOffset());
}

volatile uint32_t * BscMasterRegisters::GetDataFifoRegister()
{
  return reinterpret_cast<volatile uint32_t *>(m_mmioSegment->Get() + m_memoryConfig->GetDataFifoOffset());
}

volatile uint32_t * BscMasterRegisters::GeClockDividerRegister()
{
  return reinterpret_cast<volatile uint32_t *>(m_mmioSegment->Get() + m_memoryConfig->GetClockDividerOffset());
}

volatile uint32_t * BscMasterRegisters::GetDataDelayRegister()
{
  return reinterpret_cast<volatile uint32_t *>(m_mmioSegment->Get() + m_memoryConfig->GetDataDelayOffset());
}

volatile uint32_t * BscMasterRegisters::GetClockStretchTimeoutRegister()
{
  return reinterpret_cast<volatile uint32_t *>(m_mmioSegment->Get() + m_memoryConfig->GetClockStretchTimeoutOffset());
}

} // namespace I2c
