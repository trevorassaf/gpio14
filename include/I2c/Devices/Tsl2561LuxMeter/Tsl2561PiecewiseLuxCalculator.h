#pragma once

#include <cstdint>

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
