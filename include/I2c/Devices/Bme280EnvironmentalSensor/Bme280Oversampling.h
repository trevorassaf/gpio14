#pragma once

#include <cstdint>

namespace I2c
{
enum class Bme280Oversampling : uint8_t
{
		SKIPPED          = 0b000,
		OVERSAMPLING_1X  = 0b001,
		OVERSAMPLING_2X  = 0b010,
		OVERSAMPLING_4X  = 0b011,
		OVERSAMPLING_8X  = 0b100,
		OVERSAMPLING_16X = 0b101,
};
} // namespace I2c
