#include "I2c/DataDelayRegisterBits.h"

namespace
{
constexpr size_t FALLING_EDGE_DELAY_OFFSET = 16;
constexpr size_t RISING_EDGE_DELAY_OFFSET = 0;
} // namespace

namespace I2c
{
size_t DataDelayRegisterBits::GetFallingEdgeDelayOffset() const
{
		return FALLING_EDGE_DELAY_OFFSET;
}

size_t DataDelayRegisterBits::GetRisingEdgeDelayOffset() const
{
		return RISING_EDGE_DELAY_OFFSET;
}
} // namespace I2c
