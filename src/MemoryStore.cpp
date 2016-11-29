#include "MemoryStore.h"

#include <utility>

namespace gpio {

MemoryStore::MemoryStore(
    std::shared_ptr<MemoryConfig> memory_config,
    std::unique_ptr<MemorySegment> memory_segment
) : memory_config_(std::move(memory_config)),
    memory_segment_(std::move(memory_segment)) {}

volatile uint64_t* MemoryStore::GetSelectPinFunctionPtr() {
  return reinterpret_cast<volatile uint64_t*>(
      memory_segment_->Get() + memory_config_->GetSelectPinFunctionByteOffset());
}

volatile uint64_t* MemoryStore::GetSetPinPtr() {
  return reinterpret_cast<volatile uint64_t*>(
      memory_segment_->Get() + memory_config_->GetSetPinByteOffset());
}

volatile uint64_t* MemoryStore::GetClearPinPtr() {
  return reinterpret_cast<volatile uint64_t*>(
      memory_segment_->Get() + memory_config_->GetClearPinByteOffset());
}

volatile uint64_t* MemoryStore::GetReadPinLevelPtr() {
  return reinterpret_cast<volatile uint64_t*>(
      memory_segment_->Get() + memory_config_->GetReadPinLevelByteOffset());
}

} // namespace gpio
