#pragma once

#include <cstdint>
#include <cstdlib>

namespace gpio {

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
