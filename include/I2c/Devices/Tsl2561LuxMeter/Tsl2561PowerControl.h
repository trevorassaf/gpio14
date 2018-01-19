#pragma once

#include <cstdint>

namespace I2c
{
enum class Tsl2561PowerControl : uint8_t
{
		POWER_DOWN = 0x0,
		POWER_UP = 0x3,
};

} // namespace I2c
