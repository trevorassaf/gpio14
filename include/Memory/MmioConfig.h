#pragma once

#include <cstdint>
#include <cstdlib>

namespace Memory
{

class MmioConfig
{
public:
	static MmioConfig MakeGpioConfig() noexcept;
	static MmioConfig MakeI2c1Config() noexcept;
	static MmioConfig MakeI2c2Config() noexcept;

public:
	MmioConfig(size_t physicalMemoryByteOffset, size_t mappedBytesCount) noexcept;

	size_t GetPhysicalMemoryByteOffset() const noexcept;
	size_t GetMappedBytesCount() const noexcept;

private:
	size_t m_physicalMemoryByteOffset;
	size_t m_mappedBytesCount;
};

} // namespace Memory
