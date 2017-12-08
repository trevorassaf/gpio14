#pragma once

#include <cstdint>
#include <sstream>

#include "I2c/Registers/MmioRegister.h"

namespace I2c
{
class DataDelayRegister : public MmioRegister
{
public:
	DataDelayRegister();
	DataDelayRegister(uint16_t fallingEdgeDelay, uint16_t risingEdgeDelay);

	uint16_t GetFallingEdgeDelay() const;
	uint16_t GetRisingEdgeDelay() const;

	uint32_t ToMmioRegister() const override;

private:
	uint16_t m_fallingEdgeDelay;
	uint16_t m_risingEdgeDelay;
};

std::ostream &operator<<(std::ostream &stream, const DataDelayRegister &reg);

class DataDelayRegisterBuilder
{
public:
	DataDelayRegisterBuilder();

	DataDelayRegisterBuilder &SetFallingEdgeDelay(uint16_t delay);
	DataDelayRegisterBuilder &ResetFallingEdgeDelay();
	DataDelayRegisterBuilder &SetRisingEdgeDelay(uint16_t delay);
	DataDelayRegisterBuilder &ResetRisingEdgeDelay();
	DataDelayRegisterBuilder &FromMmioRegister(uint32_t bits);

	DataDelayRegister Build() const;

private:
	uint16_t m_fallingEdgeDelay;
	uint16_t m_risingEdgeDelay;
};
} // namespace I2c
