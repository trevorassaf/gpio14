#pragma once

#include <cstdint>
#include <mutex>
#include <vector>
#include <unordered_map>

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
		Pin BindPinFunction(uint8_t pin_index, PinType pin_type);

    // Asserts specified pin.
    void SetPin(const Pin& pin);

  private:
    // Asserts the specified bit.
    void SetBit(uint8_t pin_index, size_t base_offset);

    // Deasserts the specified bit.
    void ClearBit(uint8_t pin_index, size_t base_offset);

    // Returns offset for register that controls pin function.
    //
    // Note: this does not return the byte offset, but the register offset.
    //    To get the byte offset, simply multiply by WORD_SIZE.
    size_t GetSelectPinFunctionRegisterOffset(uint8_t pin_index) const;

    // Returns offset for first bit in select function code for specified pin.
    size_t GetSelectPinFunctionBitOffset(uint8_t pin_index) const;

    // Initialize mutexes in 'memory_mutex_map_ 'that will protect access to specified
    // registers.
    //
    // @param offset: The key of the first mutex stored in the map. Keys for mutexes
    //    initialized in batch increment.
    // @param register_count: The number of registers to protect. Each register
    //    is protected by its own mutex.
    //
    // Ex. offset = 0 and register_count = 3 will initialize three mutexes at keys 0, 1, and 2.
    //
    // @pre-condition: There may be no collisiions with existing mutexes.
    void InitMutexes(size_t offset, size_t register_count);

    // Returns pointer to register of interest.
    volatile uint32_t* GetRegisterPtr(uint8_t pin_index, size_t base_offset) const;

    // Returns bit offset corresponding to desired pin.
    size_t GetBitOffset(uint8_t pin_index) const;

	private:
    // BCM2835 maps gpio peripherals into this address in physical memory. This region of
    // of physical memory is accessed by applying mmap() to /dev/mem.
    static constexpr size_t GPIO_PHYSICAL_MEMORY_BYTE_OFFSET = 0x2200000;

    // Used to map an entire page into memory.
    static constexpr size_t PAGE_SIZE = 4096;

    // Number of bytes in a word of memory on the BCM2835.
    static constexpr size_t WORD_SIZE = 4;

    // Select pin function constants.
    static constexpr size_t SELECT_PIN_FUNCTION_BASE_BYTE_OFFSET = 0;
    static constexpr size_t BITS_PER_SELECT_PIN_FUNCTION_CODE = 3;
    static constexpr size_t CODES_PER_SELECT_PIN_FUNCTION_REGISTER = 10;
    static constexpr size_t SELECT_PIN_FUNCTION_REGISTER_COUNT = 6;

    // Base byte offset for pin assertion.
    static constexpr size_t SET_PIN_BASE_BYTE_OFFSET = 0x1C;

    // Map of register offset to mutex protecting register in question.
    std::unordered_map<size_t, std::mutex> memory_mutex_map_;

    // Pointer to base register of peripheral address space.
    volatile uint32_t*  gpio_base_;
};

} // namespace gpio
