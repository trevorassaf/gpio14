#pragma once

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561LuxValues.h"

namespace I2c
{
class Tsl2561PiecewiseLuxCalculator
{
public:
 Tsl2561LuxValues ComputeLux(
     uint32_t iGain,
     uint32_t tInt,
     uint16_t rawAdc0Value,
     uint16_t rawAdc1Value,
     int iType) const;
};
} // namespace I2c
