#pragma once

#include <cstdint>
#include <string>

namespace Gpio {

enum class PinType : uint8_t {
	INPUT		= 0b000,
	OUTPUT	= 0b001,
	ALT_0		= 0b100,
	ALT_1		= 0b101,
	ALT_2		= 0b110,
	ALT_3		= 0b111,
	ALT_4		= 0b011,
	ALT_5		= 0b010
};

const char *ToString(PinType type);

} // namespace Gpio
