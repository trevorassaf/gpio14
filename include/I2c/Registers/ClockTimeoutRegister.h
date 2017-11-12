#pragma once

#include <cstdint>

namespace
{
constexpr uint16_t TIMEOUT_RESET_VALUE = 0x40;
} // namespace

namespace I2c
{
class ClockTimeoutRegister
{
public:
	ClockTimeoutRegister() : m_timeoutValue{TIMEOUT_RESET_VALUE} {}

	ClockTimeoutRegister(uint16_t timeoutValue)
		: m_timeoutValue{timeoutValue} {}

	uint16_t GetTimeoutValue() const
	{
			return m_timeoutValue;
	}

private:
	const uint16_t m_timeoutValue;
};
} // namespace I2c
