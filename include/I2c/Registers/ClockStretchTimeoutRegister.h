#pragma once

#include <cstdint>
#include <sstream>

#include "I2c/Registers/MmioRegister.h"

namespace I2c
{
class ClockStretchTimeoutRegister : public MmioRegister
{
public:
	ClockStretchTimeoutRegister();

	ClockStretchTimeoutRegister(uint16_t timeoutValue);

	uint16_t GetTimeoutValue() const;

	uint32_t ToMmioRegister() const;

private:
	uint16_t m_timeoutValue;
};

class ClockStretchTimeoutRegisterBuilder
{
public:
	ClockStretchTimeoutRegisterBuilder();

	ClockStretchTimeoutRegisterBuilder &SetTimeout(uint16_t timeout);
	ClockStretchTimeoutRegisterBuilder &ResetTimeout();
	ClockStretchTimeoutRegisterBuilder &FromMmioRegister(uint32_t bits);

	ClockStretchTimeoutRegister Build() const;

private:
	uint16_t m_timeoutValue;
};
} // namespace I2c
