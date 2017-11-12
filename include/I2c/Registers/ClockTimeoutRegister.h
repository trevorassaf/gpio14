#pragma once

#include <cstdint>

namespace
{
constexpr uint16_t TIMEOUT_RESET_CODE = 0x40;
} // namespace

namespace I2c
{
class ClockTimeoutRegister
{
public:
	ClockTimeoutRegister() : m_timeoutValue{TIMEOUT_RESET_CODE} {}

	ClockTimeoutRegister(uint16_t timeoutValue)
		: m_timeoutValue{timeoutValue} {}

	uint16_t GetTimeoutValue() const
	{
			return m_timeoutValue;
	}

private:
	const uint16_t m_timeoutValue;
};

class ClockTimeoutRegisterBuilder
{
public:
	ClockTimeoutRegisterBuilder() : m_timeoutValue{TIMEOUT_RESET_CODE} {}

	ClockTimeoutRegisterBuilder &SetTimeout(uint16_t timeout)
	{
			m_timeoutValue = timeout;
			return *this;
	}

	ClockTimeoutRegisterBuilder &ResetTimeout()
	{
			m_timeoutValue = TIMEOUT_RESET_CODE;
			return *this;
	}

	ClockTimeoutRegister Build() const
	{
			return ClockTimeoutRegister{m_timeoutValue};
	}

private:
	uint16_t m_timeoutValue;
};
} // namespace I2c
