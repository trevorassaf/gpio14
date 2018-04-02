#pragma once

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561LuxValues.h"

namespace I2c
{
class Tsl2561QuantizedLuxCalculator
{
public:
	Tsl2561QuantizedLuxCalculator();
	Tsl2561LuxValues ComputeQuantizedLux(
			 uint32_t iGain,
			 uint32_t tInt,
			 uint16_t ch0,
			 uint16_t ch1,
			 int iType) const;

	Tsl2561LuxValues ComputeLux(
			 uint32_t iGain,
			 uint32_t tInt,
			 uint16_t ch0,
			 uint16_t ch1,
			 int iType) const
	{
			return Tsl2561LuxValues{};
	}
private:
	uint32_t stuff;
};
} // namespace I2c
