#include "Memory/MmioConfig.h"

/**
 * Note: RPi 1 starts peripheral memory at 0x20000000, but RPi 2/3 starts at 0x3F000000
 */
constexpr size_t GPIO_PHYSICAL_MEMORY_BYTE_OFFSET = 0x3F200000;

// Exported on pins 27/28
constexpr size_t I2C_MASTER_1_PHYSICAL_MEMORY_BYTE_OFFSET = 0x3F205000;

// Exported on pins 3/5
constexpr size_t I2C_MASTER_2_PHYSICAL_MEMORY_BYTE_OFFSET = 0x3F804000;

constexpr size_t PAGE_SIZE = 4096;

namespace Memory
{

MmioConfig MmioConfig::MakeGpioConfig() noexcept
{
		return MmioConfig{GPIO_PHYSICAL_MEMORY_BYTE_OFFSET, PAGE_SIZE};
}

MmioConfig MmioConfig::MakeI2c1Config() noexcept
{
		return MmioConfig{I2C_MASTER_1_PHYSICAL_MEMORY_BYTE_OFFSET, PAGE_SIZE};
}

MmioConfig MmioConfig::MakeI2c2Config() noexcept
{
		return MmioConfig{I2C_MASTER_2_PHYSICAL_MEMORY_BYTE_OFFSET, PAGE_SIZE};
}

MmioConfig::MmioConfig(size_t physicalMemoryBytesOffset, size_t mappedBytesCount) noexcept
	: m_physicalMemoryByteOffset{physicalMemoryBytesOffset},
		m_mappedBytesCount{mappedBytesCount} {}

size_t MmioConfig::GetPhysicalMemoryByteOffset() const noexcept { return m_physicalMemoryByteOffset; }
size_t MmioConfig::GetMappedBytesCount() const noexcept { return m_mappedBytesCount; }

} // namespace Memory
