#pragma once

#include <cstdint>
#include <mutex>
#include <vector>

#include "PinType.h"

namespace gpio {

class PinManager {
	public:
    // Initializes gpio pin runtime context.
    //
    // @throw runtime_error: fail to map gpio hardware into memory
		PinManager();
		~PinManager();

		PinManager& SetFunction(uint8_t pin_index, PinType pin_type);
	private:
    static constexpr uint64_t GPIO_MEMORY_OFFSET = 0xF2200000;
    static constexpr size_t PAGE_SIZE = 4096;
		static constexpr size_t PIN_FUNCTION_REG_COUNT = 5;
		std::vector<std::mutex> pin_function_locks_;

    volatile uint64_t*  gpio_base_;
};

} // namespace gpio
