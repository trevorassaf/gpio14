#pragma once

#include <cstdint>

namespace I2c
{

enum class Tsl2561Address : uint8_t
{
		CONTROL = 0x0,
		TIMING = 0x1,
		THRESHLOWLOW = 0x2,
		THRESHLOWHIGH = 0x3,
		THRESHHIGHLOW = 0x4,
		THRESHHIGHHIGH = 0x5,
		INTERRUPT = 0x6,
		ID = 0xA,
		DATA0LOW = 0xC,
		DATA0HIGH = 0xD,
		DATA1LOW = 0xE,
		DATA1HIGH = 0xF,
};

} // namespace I2c
