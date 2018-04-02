#pragma once

#include <cstdint>

namespace I2c
{

struct Tsl2561LuxValues
{
		uint32_t irSpectrumLux;
		uint32_t visibleSpectrumLux;
};

} // namespace I2c
