#pragma once

#include <cstdlib>

namespace I2c
{
class MemoryConfig
{
public:
	size_t GetControlOffset() const;
	size_t GetStatusOffset() const;
	size_t GetDataLengthOffset() const;
	size_t GetSlaveAddressOffset() const;
	size_t GetDataFifoOffset() const;
	size_t GetClockDivideOffset() const;
	size_t GetDataDelayOffset() const;
	size_t GetClockStretchTimeoutOffset() const;
};
} // namespace I2c
