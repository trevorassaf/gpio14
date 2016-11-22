#pragma once

#include <cstdint>
#include <mutex>
#include <vector>

#include "PinType.h"

namespace gpio {

class PinManager {
	public:
		PinManager();
		~PinManager();

		PinManager& SetFunction(uint8_t pin_index, PinType pin_type);
	private:
		static constexpr size_t PIN_FUNCTION_REG_COUNT = 5;
		std::vector<std::mutex> pin_function_locks_;
};

} // namespace gpio
