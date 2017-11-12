#pragma once

#include <cstdlib>

namespace I2c
{
class ClockTimeoutRegisterBits
{
public:
	size_t GetClockStretchTimeoutOffset() const;
};
} // namespace I2c
