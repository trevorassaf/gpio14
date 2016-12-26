#pragma once

#include <cstdint>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <memory>

#include "PinType.h"
#include "MemorySegment.h"
#include "MemoryConfig.h"

namespace gpio {

class PinManager {
public:
  // Initializes gpio pin runtime context.
  //
  // @throw runtime_error: fail to map gpio hardware into memory
  PinManager(
      std::shared_ptr<MemoryConfig> memory_config,
      std::unique_ptr<MemorySegment> memory_segment);

  // Configures pin for designated function.
  //
  // Reconfigure the pin by calling ReleasePin() and then BindPin() with the
  // new function type.
  void BindPin(uint8_t pin_index, PinType pin_type);

  // Reverts pin to 'unused' state.
  void ReleasePin(uint8_t pin_index);

  // Asserts specified pin.
  void SetPin(uint8_t pin_index);

  // Deasserts specified pin.
  void ClearPin(uint8_t pin_index);

  // Returns true if pin is asserted.
  bool ReadPin(uint8_t pin_index);

private:
  // Asserts the specified bit.
  void SetBit(uint8_t pin_index, size_t base_byte_offset);

  // Returns true if specified bit is set.
  //
  // This function is not thread-safe. Protect with mutex if necessary.
  bool ReadBit(uint8_t pin_index, size_t base_byte_offset);

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
  // @param leading_byte_offset: Offset of first protected byte.
  // @param bytes_per_mutex: Number of bytes protected by each mutex.
  // @param num_mutexes: Number of mutexes to emplace. Each mutex is keyed on a byte offset.
  //    The byte offsets are separated by "bytes_per_mutex."
  //
  // Ex. InitMutexes(0, 4, 3) yields 3 mutexes at indices 0, 4, and 8.
  //
  // @pre-condition: No collisiions with existing mutexes.
  void InitMutexes(
      size_t leading_byte_offset,
      size_t bytes_per_mutex,
      size_t num_mutexes);

  void InitSelectPinFunctionMutexes();
  void InitPinFunctionMutexes(size_t leading_byte_offset);

  // Returns the byte offset for the specified pin relative to 'base_byte_offset'
  size_t CalculateByteOffset(uint8_t pin_index, size_t base_byte_offset) const;

private:
  // Mutex information for select pin operations.
  static constexpr size_t SELECT_PIN_FUNCTION_BYTES_PER_MUTEX = 4;
  static constexpr size_t SELECT_PIN_FUNCTION_MUTEX_COUNT = 6;

  // Mutex information for non-select pin operations
  static constexpr size_t PIN_FUNCTION_BYTES_PER_MUTEX = 1;
  static constexpr size_t PIN_FUNCTION_MUTEX_COUNT = 8;

  // Register information for select pin operations
  static constexpr size_t CODES_PER_SELECT_PIN_FUNCTION_REGISTER = 10;
  static constexpr size_t BITS_PER_SELECT_PIN_FUNCTION_CODE = 3;

  // Map of register offset to mutex protecting register in question.
  std::unordered_map<size_t, std::mutex> memory_mutex_map_;

  // Map of function type for each pin currently in use.
  // TODO(bozkurtus): replace with lock free map
  std::unordered_map<uint8_t, PinType> pin_type_map_;

  // Lock protecting the 'pin_type_map_'
  std::mutex pin_type_map_mutex_;

  // Memory offsets for accessing mmio registers in the gpio peripherals
  // memory segment.
  std::shared_ptr<MemoryConfig> memory_config_;

  // Gpio peripherals mmio memory segment.
  std::unique_ptr<MemorySegment> memory_segment_;
};

} // namespace gpio
