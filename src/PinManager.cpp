#include "PinManager.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <iostream>
#include <cassert>
#include <bitset>
#include <cstring>
#include <stdexcept>
#include <type_traits>
#include <utility>

#include "SysUtils.h"
#include "ScopeGuard.h"

namespace gpio {

PinManager::PinManager(
    std::shared_ptr<MemoryConfig> memory_config,
    std::unique_ptr<MemorySegment> memory_segment
) : memory_config_(std::move(memory_config)),
    memory_segment_(std::move(memory_segment)) {
  // Initialize memory locks for binding pin functions. R^W memory regions do not require
  // locks so long as access is volatile qualified.
  InitSelectPinFunctionMutexes();
}

void PinManager::BindPin(uint8_t pin_index, PinType pin_type) {
  // Start critical section for caching pin type
  std::lock_guard<std::mutex> cache_pin_type_critical_section(pin_type_map_mutex_);
  assert(pin_type_map_.count(pin_index) == 0);
  pin_type_map_[pin_index] = pin_type;

  // Start critical section for informing hw of new pin function
  size_t register_offset = GetSelectPinFunctionRegisterOffset(pin_index);
  size_t mutex_register_offset = register_offset * SELECT_PIN_FUNCTION_BYTES_PER_MUTEX;

  assert(memory_mutex_map_.count(mutex_register_offset) == 1);
  std::lock_guard<std::mutex> hw_bind_pin_function_critical_section(
      memory_mutex_map_[mutex_register_offset]);

  // First, read existing select pin code into temporary. Next, clear current function
  // for desired pin. Then, set new function for desired pin. Finally, write code back
  // to register.
  size_t bit_offset = GetSelectPinFunctionBitOffset(pin_index);
  volatile uint32_t *gpio_memory =
      (volatile uint32_t *)memory_segment_->Get();

  uint32_t select_pin_function_codes = gpio_memory[register_offset];
  select_pin_function_codes &= ~(0b111 << bit_offset);
  select_pin_function_codes |= static_cast<uint32_t>(pin_type) << bit_offset;
  gpio_memory[register_offset] = select_pin_function_codes;
}

void PinManager::ReleasePin(uint8_t pin_index) {
  std::lock_guard<std::mutex> unset_pin_type_critical_section(pin_type_map_mutex_);
  assert(pin_type_map_.count(pin_index) == 1);
  pin_type_map_.erase(pin_index);
}

void PinManager::SetPin(uint8_t pin_index) {
  SetBit(pin_index, memory_config_->GetSetPinByteOffset());
}

void PinManager::ClearPin(uint8_t pin_index) {
  SetBit(pin_index, memory_config_->GetClearPinByteOffset());
}

bool PinManager::ReadPin(uint8_t pin_index) {
  return ReadBit(pin_index, memory_config_->GetReadPinLevelByteOffset());
}

void PinManager::SetBit(uint8_t pin_index, size_t base_byte_offset) {
  size_t byte_offset = CalculateByteOffset(pin_index, base_byte_offset);
  volatile uint32_t *set_pin_ptr =
      (volatile uint32_t *)memory_segment_->Get() + byte_offset;
  *set_pin_ptr = (0b1 << (pin_index % 32));
}

bool PinManager::ReadBit(uint8_t pin_index, size_t base_byte_offset) {
  size_t byte_offset = CalculateByteOffset(pin_index, base_byte_offset);
  volatile uint32_t *read_pin_ptr =
      (volatile uint32_t *)memory_segment_->Get() + byte_offset;
  return *read_pin_ptr & (0b1 << (pin_index % 32));
}

size_t PinManager::GetSelectPinFunctionRegisterOffset(uint8_t pin_index) const {
  return pin_index / CODES_PER_SELECT_PIN_FUNCTION_REGISTER;
}

size_t PinManager::GetSelectPinFunctionBitOffset(uint8_t pin_index) const {
  return (pin_index % CODES_PER_SELECT_PIN_FUNCTION_REGISTER) * BITS_PER_SELECT_PIN_FUNCTION_CODE;
}

void PinManager::InitMutexes(
  size_t leading_byte_offset,
  size_t bytes_per_mutex,
  size_t num_mutexes
) {
  size_t limit = leading_byte_offset + bytes_per_mutex * num_mutexes;
  for (size_t i = leading_byte_offset; i < limit; i += bytes_per_mutex) {
    assert(memory_mutex_map_.count(i) == 0); 
    memory_mutex_map_[i];
  }
}

void PinManager::InitSelectPinFunctionMutexes() {
  InitMutexes(
      memory_config_->GetSelectPinFunctionByteOffset(),
      SELECT_PIN_FUNCTION_BYTES_PER_MUTEX,
      SELECT_PIN_FUNCTION_MUTEX_COUNT);
}

void PinManager::InitPinFunctionMutexes(size_t leading_byte_offset) {
  InitMutexes(
      leading_byte_offset,
      PIN_FUNCTION_BYTES_PER_MUTEX,
      PIN_FUNCTION_MUTEX_COUNT);
}

size_t PinManager::CalculateByteOffset(uint8_t pin_index, size_t base_byte_offset) const {
  return (base_byte_offset / 4) + (pin_index / 32);
}

} // namespace gpio
