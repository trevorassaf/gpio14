#pragma once

#include <cstdint>
#include <cstdlib>

namespace Gpio {

/**
 * Defines memory addresses and offsets that are pertinent to GPIO peripherals.
 *
 * Note: RPi 1 starts peripheral memory at 0x20000000, but RPi 2/3 starts at 0x3F000000
 */
class MemoryConfig {
 public:
  size_t GetSelectPinFunctionByteOffset() const {
    return SELECT_PIN_FUNCTION_BYTE_OFFSET; 
  }

  size_t GetSetPinByteOffset() const {
    return SET_PIN_BYTE_OFFSET; 
  }

  size_t GetClearPinByteOffset() const {
    return CLEAR_PIN_BYTE_OFFSET; 
  }

  size_t GetReadPinLevelByteOffset() const {
    return READ_PIN_LEVEL_BYTE_OFFSET;
  }

 private:
  // Byte offset for selecting pin function (offset relative to PHYS_MEM_BYTE_OFFSET).
  static constexpr size_t SELECT_PIN_FUNCTION_BYTE_OFFSET = 0x0;

  // Byte offset for asserting pin (offset relative to PHYS_MEM_BYTE_OFFSET).
  static constexpr size_t SET_PIN_BYTE_OFFSET = 0x1C;

  // Byte offset for deasserting pin (relative to PHYS_MEM_BYTE_OFFSET).
  static constexpr size_t CLEAR_PIN_BYTE_OFFSET = 0x28;

  // Byte offset for read pin level (relative to PHYS_MEM_BYTE_OFFSET).
  static constexpr size_t READ_PIN_LEVEL_BYTE_OFFSET = 0x34;
};

} // namespace Gpio
