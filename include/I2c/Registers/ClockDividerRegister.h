#pragma once

namespace I2c
{
class ClockDivideRegister
{
public:
	ClockDivideRegister(uint16_t divisor) : m_divisor{divisor} {}

	uint16_t GetDivisor() const { return m_divisor; }

private:
	uint16_t m_divisor;
};
} // namespace I2c
