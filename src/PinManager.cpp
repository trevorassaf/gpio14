#include "PinManager.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cassert>
#include <cstring>
#include <stdexcept>
#include <type_traits>

#include "SysUtils.h"
#include "ScopeGuard.h"

namespace gpio {

PinManager::PinManager()
	: pin_function_locks_(PIN_FUNCTION_REGISTER_COUNT)
{
	// Map gpio peripherals into memory
	int fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  ScopeGuard<int> close_file_guard(fd, [] (int& fd) -> void {
    close(fd);
  });

  void* memory = mmap(
      nullptr,
      PAGE_SIZE,
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      GPIO_PHYSICAL_MEMORY_OFFSET);

  if (memory == MAP_FAILED) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  gpio_base_ = static_cast<volatile uint32_t*>(memory);
}

// TODO: unmap gpio memory
PinManager::~PinManager() {}

Pin PinManager::BindFunction(uint8_t pin_index, PinType pin_type) {
  // Start critical section for editing gpio function register
  size_t function_register_index = MakeFunctionRegisterIndex(pin_index);
  std::lock_guard<std::mutex> lock(pin_function_locks_[function_register_index]);

  // First, clear existing function. Then, set new function.
  size_t shift_value = MakeShiftValue(pin_index);
  gpio_base_[function_register_index] &= MakeClearFunctionValue(shift_value);
  gpio_base_[function_register_index] |= MakeSetFunctionValue(shift_value, pin_type);

  return Pin(pin_index);
}

uint32_t PinManager::MakeClearFunctionValue(size_t shift_value) const {
  return ~(0b111 << shift_value); 
}

uint32_t PinManager::MakeSetFunctionValue(size_t shift_value, PinType pin_type) const {
  return static_cast<size_t>(pin_type) << shift_value;
}

size_t PinManager::MakeShiftValue(uint8_t pin_index) const {
  return (pin_index % PINS_PER_FUNCTION_REGISTER) * BITS_PER_FUNCTION;
}

size_t PinManager::MakeFunctionRegisterIndex(uint8_t pin_index) const {
  return pin_index / PINS_PER_FUNCTION_REGISTER;
}

} // namespace gpio
