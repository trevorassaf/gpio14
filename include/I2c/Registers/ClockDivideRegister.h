#pragma once

#include <cstdint>

namespace
{
constexpr uint16_t DEFAULT_DIVISOR_CODE = 0x05DC;
} // namespace

namespace I2c
{
class ClockDivideRegister
{
public:
	ClockDivideRegister() : m_divisor{DEFAULT_DIVISOR_CODE} {}

	ClockDivideRegister(uint16_t divisor) : m_divisor{divisor} {}

	uint16_t GetDivisor() const { return m_divisor; }

private:
	uint16_t m_divisor;
};

class ClockDivideRegisterBuilder
{
public:
	ClockDivideRegisterBuilder() : m_divisor{DEFAULT_DIVISOR_CODE} {}

	ClockDivideRegisterBuilder &SetDivisor(uint16_t divisor)
	{
			m_divisor = divisor;
			return *this;
	}

	ClockDivideRegisterBuilder &ResetDivisor()
	{
			m_divisor = DEFAULT_DIVISOR_CODE;
			return *this;
	}

	ClockDivideRegister Build() const
	{
			return ClockDivideRegister{m_divisor};
	}

private:
	uint16_t m_divisor;
};
} // namespace I2c
