#pragma once

#include <cstdint>

namespace gpio {

enum class PinType : uint8_t {
	INPUT,
	OUTPUT,
	ALT_0,
	ALT_1,
	ALT_2,
	ALT_3,
	ALT_4,
	ALT_5
};

} // namespace gpio
