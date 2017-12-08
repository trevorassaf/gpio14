#pragma once

#include <cstdint>
#include <sstream>

#include "I2c/Registers/MmioRegister.h"

namespace I2c
{
class ClockDivideRegister : public MmioRegister
{
public:
	ClockDivideRegister();

	ClockDivideRegister(uint16_t divisor);

	ClockDivideRegister(uint32_t bits);

	uint16_t GetDivisor() const;

	uint32_t ToMmioRegister() const override;

private:
	uint16_t m_divisor;
};

std::ostream &operator<<(std::ostream &stream, const ClockDivideRegister &reg);

class ClockDivideRegisterBuilder
{
public:
	ClockDivideRegisterBuilder();

	ClockDivideRegisterBuilder &SetDivisor(uint16_t divisor);
	ClockDivideRegisterBuilder &ResetDivisor();
	ClockDivideRegisterBuilder &FromMmioRegister(uint32_t bits);
	ClockDivideRegister Build() const;

private:
	uint16_t m_divisor;
};
} // namespace I2c
