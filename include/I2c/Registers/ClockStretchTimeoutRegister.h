#pragma once

#include <cstdint>

namespace
{
constexpr uint16_t TIMEOUT_RESET_CODE = 0x40;
} // namespace

namespace I2c
{
class ClockStretchTimeoutRegister
{
public:
	ClockStretchTimeoutRegister() : m_timeoutValue{TIMEOUT_RESET_CODE} {}

	ClockStretchTimeoutRegister(uint16_t timeoutValue)
		: m_timeoutValue{timeoutValue} {}

	uint16_t GetTimeoutValue() const
	{
			return m_timeoutValue;
	}

private:
	const uint16_t m_timeoutValue;
};

class ClockStretchTimeoutRegisterBuilder
{
public:
	ClockStretchTimeoutRegisterBuilder() : m_timeoutValue{TIMEOUT_RESET_CODE} {}

	ClockStretchTimeoutRegisterBuilder &SetTimeout(uint16_t timeout)
	{
			m_timeoutValue = timeout;
			return *this;
	}

	ClockStretchTimeoutRegisterBuilder &ResetTimeout()
	{
			m_timeoutValue = TIMEOUT_RESET_CODE;
			return *this;
	}

	ClockStretchTimeoutRegisterBuilder &FromMmioRegister(uint32_t bits)
	{
			SetTimeout(static_cast<uint16_t>(bits));
			return *this;
	}

	ClockStretchTimeoutRegister Build() const
	{
			return ClockStretchTimeoutRegister{m_timeoutValue};
	}

private:
	uint16_t m_timeoutValue;
};
} // namespace I2c
