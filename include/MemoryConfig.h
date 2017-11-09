#pragma once

#include <cstdint>
#include <cstdlib>

namespace gpio {

/**
 * Defines memory addresses and offsets that are pertinent to GPIO peripherals.
 *
 * TODO(bozkurtus): This file actually blends Bcm2835 memory parameters and GPIO-specific
 * Bcm2835 parameters. Separate these out into two files.
 *
 * Note: RPi 1 starts peripheral memory at 0x20000000, but RPi 2/3 starts at 0x3F000000
 */
class MemoryConfig {
 public:
  size_t GetPhysicalMemoryByteOffset() const {
    return PHYS_MEM_BYTE_OFFSET;
  }

  size_t GetMappedBytesCount() const {
    return MAPPED_BYTES_COUNT;
  }

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
  // Offset in physical memory at which peripheral gpio register region begins.
  static constexpr size_t PHYS_MEM_BYTE_OFFSET = 0x3F200000;

  // Number of mapped bytes. Map a full page into memory.
  // TODO(bozkurtus): maybe we don't need to map the full page...
  static constexpr size_t MAPPED_BYTES_COUNT = 4096;

  // Byte offset for selecting pin function (offset relative to PHYS_MEM_BYTE_OFFSET).
  static constexpr size_t SELECT_PIN_FUNCTION_BYTE_OFFSET = 0x0;

  // Byte offset for asserting pin (offset relative to PHYS_MEM_BYTE_OFFSET).
  static constexpr size_t SET_PIN_BYTE_OFFSET = 0x1C;

  // Byte offset for deasserting pin (relative to PHYS_MEM_BYTE_OFFSET).
  static constexpr size_t CLEAR_PIN_BYTE_OFFSET = 0x28;

  // Byte offset for read pin level (relative to PHYS_MEM_BYTE_OFFSET).
  static constexpr size_t READ_PIN_LEVEL_BYTE_OFFSET = 0x34;
};

} // namespace gpio
