#pragma once

#include <cstdint>

#include "I2c/Registers/MmioRegister.h"

namespace
{
constexpr uint16_t DEFAULT_DIVISOR_CODE = 0x05DC;
} // namespace

namespace I2c
{
class ClockDivideRegister : public MmioRegister
{
public:
	ClockDivideRegister() : m_divisor{DEFAULT_DIVISOR_CODE} {}

	ClockDivideRegister(uint16_t divisor) : m_divisor{divisor} {}

	ClockDivideRegister(uint32_t bits) : ClockDivideRegister{static_cast<uint16_t>(bits)} {}

	uint16_t GetDivisor() const { return m_divisor; }

	uint32_t ToMmioRegister() const override { return static_cast<uint32_t>(m_divisor); }

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

	ClockDivideRegisterBuilder &FromMmioRegister(uint32_t bits)
	{
			SetDivisor(static_cast<uint16_t>(bits));
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
