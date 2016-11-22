#pragma once

#include <cstdint>
#include <mutex>
#include <vector>

#include "PinType.h"
#include "Pin.h"

namespace gpio {

class PinManager {
	public:
    // Initializes gpio pin runtime context.
    //
    // @throw runtime_error: fail to map gpio hardware into memory
		PinManager();
		~PinManager();

    // Configures pin for designated function.
		Pin BindFunction(uint8_t pin_index, PinType pin_type);

  private:
    inline uint32_t MakeClearFunctionValue(size_t shift_value) const;
    inline uint32_t MakeSetFunctionValue(size_t shift_value, PinType pin_type) const;
    inline size_t MakeShiftValue(uint8_t pin_index) const;
    inline size_t MakeFunctionRegisterIndex(uint8_t pin_index) const;

	private:
    // BCM2835 maps gpio peripherals into this address in physical memory. We will access this region
    // of physical memory by applying mmap() to /dev/mem
    static constexpr uint64_t GPIO_PHYSICAL_MEMORY_OFFSET = 0x2200000;

    // We will map an entire page into memory.
    static constexpr size_t PAGE_SIZE = 4096;

    // There are 5 memory locations that modulate the functions of the gpio pins. We protect address
    // with a mutex.
		static constexpr size_t PIN_FUNCTION_REGISTER_COUNT = 5;
    static constexpr size_t PINS_PER_FUNCTION_REGISTER = 10;
		std::vector<std::mutex> pin_function_locks_;

    static constexpr size_t BITS_PER_FUNCTION = 3;

    volatile uint32_t*  gpio_base_;
};

} // namespace gpio
