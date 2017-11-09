#pragma once

#include <cstdint>
#include <mutex>
#include <vector>
#include <unordered_map>
#include <memory>

#include "Gpio/PinType.h"
#include "Memory/MemorySegment.h"
#include "Memory/MemoryConfig.h"

namespace Gpio {

class PinManager {
public:
  // Initializes gpio pin runtime context.
  //
  // @throw runtime_error: fail to map gpio hardware into memory
  PinManager(
			const Memory::MemoryConfig *memoryConfig,
      std::unique_ptr<Memory::MemorySegment> memorySegment);

  // Configures pin for designated function.
  //
  // Reconfigure the pin by calling ReleasePin() and then BindPin() with the
  // new function type.
  void BindPin(uint8_t pinIndex, PinType pinType);

  // Reverts pin to 'unused' state.
  void ReleasePin(uint8_t pinIndex);

  // Asserts specified pin.
  void SetPin(uint8_t pinIndex);

  // Deasserts specified pin.
  void ClearPin(uint8_t pinIndex);

  // Returns true if pin is asserted.
  bool ReadPin(uint8_t pinIndex);

private:
  // Asserts the specified bit.
  void SetBit(uint8_t pinIndex, size_t baseByteOffset);

  // Returns true if specified bit is set.
  //
  // This function is not thread-safe. Protect with mutex if necessary.
  bool ReadBit(uint8_t pinIndex, size_t baseByteOffset);

  // Returns offset for register that controls pin function.
  //
  // Note: this does not return the byte offset, but the register offset.
  //    To get the byte offset, simply multiply by WORD_SIZE.
  size_t GetSelectPinFunctionRegisterOffset(uint8_t pinIndex) const;

  // Returns offset for first bit in select function code for specified pin.
  size_t GetSelectPinFunctionBitOffset(uint8_t pinIndex) const;

  // Initialize mutexes in 'memory_mutex_map_ 'that will protect access to specified
  // registers.
  //
  // @param leadingByteOffset: Offset of first protected byte.
  // @param bytesPerMutex: Number of bytes protected by each mutex.
  // @param numMutexes: Number of mutexes to emplace. Each mutex is keyed on a byte offset.
  //    The byte offsets are separated by "bytes_per_mutex."
  //
  // Ex. InitMutexes(0, 4, 3) yields 3 mutexes at indices 0, 4, and 8.
  //
  // @pre-condition: No collisiions with existing mutexes.
  void InitMutexes(
      size_t leadingByteOffset,
      size_t bytesPerMutex,
      size_t numMutexes);

  void InitSelectPinFunctionMutexes();
  void InitPinFunctionMutexes(size_t leading_byte_offset);

  // Returns the byte offset for the specified pin relative to 'base_byte_offset'
  size_t CalculateByteOffset(uint8_t pinIndex, size_t base_byte_offset) const;

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
  std::unordered_map<size_t, std::mutex> m_memoryMutexMap;

  // Map of function type for each pin currently in use.
  // TODO(bozkurtus): replace with lock free map
  std::unordered_map<uint8_t, PinType> m_pinTypeMap;

  // Lock protecting the 'pin_type_map_'
  std::mutex m_pinTypeMapMutex;

  // Memory offsets for accessing mmio registers in the gpio peripherals
  // memory segment.
	const Memory::MemoryConfig *m_memoryConfig;

  // Gpio peripherals mmio memory segment.
  std::unique_ptr<Memory::MemorySegment> m_memorySegment;
};

} // namespace Gpio
