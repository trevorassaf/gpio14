#include "PinManager.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <cassert>
#include <cstring>
#include <stdexcept>
#include <type_traits>

#include "SysUtils.h"
#include "ScopeGuard.h"

namespace gpio {

PinManager::PinManager()
{
	// Map gpio peripherals into memory
	int fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  ScopeGuard<int> close_file_guard(fd, [] (int& fd) -> void { close(fd); });

  void* memory = mmap(
      nullptr,
      PAGE_SIZE,
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      GPIO_PHYSICAL_MEMORY_BYTE_OFFSET);

  if (memory == MAP_FAILED) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  gpio_base_ = static_cast<volatile uint32_t*>(memory);

  // Initialize memory locks
  InitMutexes(SELECT_PIN_FUNCTION_BASE_BYTE_OFFSET, SELECT_PIN_FUNCTION_REGISTER_COUNT);
}

// TODO: unmap gpio memory
PinManager::~PinManager() {}

Pin PinManager::BindPinFunction(uint8_t pin_index, PinType pin_type) {
  // Start critical section for editing gpio function register
  size_t register_offset = GetSelectPinFunctionRegisterOffset(pin_index);
  assert(memory_mutex_map_.count(register_offset) == 1);
  std::lock_guard<std::mutex> lock(memory_mutex_map_[register_offset]);

  // First, read existing select pin code into temporary. Next, clear current function
  // for desired pin. Then, set new function for desired pin. Finally, write code back
  // to register.
  size_t bit_offset = GetSelectPinFunctionBitOffset(pin_index);
  uint32_t select_pin_function_codes = static_cast<uint32_t>(gpio_base_[register_offset]);
  select_pin_function_codes &= ~(0x111 << bit_offset);
  select_pin_function_codes |= static_cast<uint32_t>(pin_type) << bit_offset;
  gpio_base_[register_offset] = select_pin_function_codes;

  return Pin(pin_index);
}

void PinManager::SetPin(const Pin& pin) {
  volatile uint32_t* reg = GetRegisterPtr(pin.GetIndex(), SET_PIN_BASE_BYTE_OFFSET);
  *reg |= 0x1 << GetBitOffset(pin.GetIndex());
}

void PinManager::SetBit(uint8_t pin_index, size_t base_offset) {
  volatile uint32_t* reg = GetRegisterPtr(pin_index, base_offset);
  *reg |= 0x1 << GetBitOffset(pin_index);
}

void PinManager::ClearBit(uint8_t pin_index, size_t base_offset) {
  volatile uint32_t* reg = GetRegisterPtr(pin_index, base_offset);
  *reg &= ~(0x1 << GetBitOffset(pin_index));
}

size_t PinManager::GetSelectPinFunctionRegisterOffset(uint8_t pin_index) const {
  return pin_index / CODES_PER_SELECT_PIN_FUNCTION_REGISTER;
}

size_t PinManager::GetSelectPinFunctionBitOffset(uint8_t pin_index) const {
  return (pin_index % CODES_PER_SELECT_PIN_FUNCTION_REGISTER) * BITS_PER_SELECT_PIN_FUNCTION_CODE;
}

void PinManager::InitMutexes(size_t offset, size_t register_count) {
  size_t limit = offset + register_count * WORD_SIZE;
  for (int i = offset; i < limit; i += WORD_SIZE) {
    assert(memory_mutex_map_.count(i) == 0);
    memory_mutex_map_[i]; // initialize new std::mutex
  }
}

volatile uint32_t* PinManager::GetRegisterPtr(uint8_t pin_index, size_t base_byte_offset) const {
  return gpio_base_ + base_byte_offset / WORD_SIZE + pin_index / (WORD_SIZE * 8);
}

size_t PinManager::GetBitOffset(uint8_t pin_index) const {
  return pin_index / (WORD_SIZE * 8);
}

} // namespace gpio
