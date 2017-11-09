#include "Memory/MemoryStore.h"

#include <utility>

namespace Memory {

MemoryStore::MemoryStore(
		const MemoryConfig *memoryConfig,
    std::unique_ptr<MemorySegment> memorySegment
) : m_memoryConfig{memoryConfig},
    m_memorySegment{std::move(memorySegment)} {}

volatile uint64_t* MemoryStore::GetSelectPinFunctionPtr() {
  return reinterpret_cast<volatile uint64_t*>(
      m_memorySegment->Get() + m_memoryConfig->GetSelectPinFunctionByteOffset());
}

volatile uint64_t* MemoryStore::GetSetPinPtr() {
  return reinterpret_cast<volatile uint64_t*>(
      m_memorySegment->Get() + m_memoryConfig->GetSetPinByteOffset());
}

volatile uint64_t* MemoryStore::GetClearPinPtr() {
  return reinterpret_cast<volatile uint64_t*>(
      m_memorySegment->Get() + m_memoryConfig->GetClearPinByteOffset());
}

volatile uint64_t* MemoryStore::GetReadPinLevelPtr() {
  return reinterpret_cast<volatile uint64_t*>(
      m_memorySegment->Get() + m_memoryConfig->GetReadPinLevelByteOffset());
}

} // namespace Memory
