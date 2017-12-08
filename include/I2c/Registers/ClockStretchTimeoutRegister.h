#pragma once

#include <cstdint>
#include <sstream>

#include "I2c/Registers/ClockStretchTimeoutRegister.h"

namespace
{
constexpr uint16_t TIMEOUT_RESET_CODE = 0x40;
} // namespace

namespace I2c
{
class ClockStretchTimeoutRegister : public MmioRegister
{
public:
	ClockStretchTimeoutRegister() : m_timeoutValue{TIMEOUT_RESET_CODE} {}

	ClockStretchTimeoutRegister(uint16_t timeoutValue)
		: m_timeoutValue{timeoutValue} {}

	uint16_t GetTimeoutValue() const { return m_timeoutValue; }

	uint32_t ToMmioRegister() const override { return static_cast<uint32_t>(m_timeoutValue); }

private:
	uint16_t m_timeoutValue;
};

std::ostream &operator<<(std::ostream &stream, const ClockStretchTimeoutRegister &reg)
{
		stream << "TOUT: " << reg.GetTimeoutValue() << " (Clock stretch timeout value)" << std::endl;
		return stream;
}

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
