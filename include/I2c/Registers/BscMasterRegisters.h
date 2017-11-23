#pragma once

#include <memory>
#include <utility>

#include "I2c/MemoryConfig.h"
#include "Memory/MmioBcm2835MemorySegment.h"

namespace I2c
{
class BscMasterRegisters
{
public:
	BscMasterRegisters(
			std::unique_ptr<Memory::MmioBcm2835MemorySegment> mmioSegment,
			const MemoryConfig *memoryConfig);

	volatile const uint32_t *GetControlRegister() const;
	volatile const uint32_t *GetStatusRegister() const;
	volatile const uint32_t *GetDataLengthRegister() const;
	volatile const uint32_t *GetSlaveAddressRegister() const;
	volatile const uint32_t *GetDataFifoRegister() const;
	volatile const uint32_t *GetClockDivideRegister() const;
	volatile const uint32_t *GetDataDelayRegister() const;
	volatile const uint32_t *GetClockStretchTimeoutRegister() const;

	volatile uint32_t *GetControlRegister();
	volatile uint32_t *GetStatusRegister();
	volatile uint32_t *GetDataLengthRegister();
	volatile uint32_t *GetSlaveAddressRegister();
	volatile uint32_t *GetDataFifoRegister();
	volatile uint32_t *GetClockDivideRegister();
	volatile uint32_t *GetDataDelayRegister();
	volatile uint32_t *GetClockStretchTimeoutRegister();

private:
	std::unique_ptr<Memory::MmioBcm2835MemorySegment> m_mmioSegment;
	const MemoryConfig *m_memoryConfig;
};

} // namespace I2c
