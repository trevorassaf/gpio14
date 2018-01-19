#pragma once

#include <cstdint>

#include "Tsl2561Register.h"

namespace I2c
{

class Tsl2561ThresholdRegister : public Tsl2561Register
{
public:
	Tsl2561ThresholdRegister(uint8_t byte);
	uint8_t Bits() const override;

private:
	uint8_t m_bits;
};

} // namespace I2c
