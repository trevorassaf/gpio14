#pragma once

#include <cstdint>

namespace I2c
{

struct Tsl2561LuxValues
{
		uint16_t irSpectrumLux;
		uint16_t visibleSpectrumLux;
};

} // namespace I2c
