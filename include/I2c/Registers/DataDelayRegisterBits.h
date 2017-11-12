#pragma once

#include <cstdlib>

namespace I2c
{
class DataDelayRegisterBits
{
public:
	size_t GetFallingEdgeDelayOffset() const;
	size_t GetRisingEdgeDelayOffset() const;
};
} // namespace I2c
