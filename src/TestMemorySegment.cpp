#include "TestMemorySegment.h"

#include <utility>

namespace gpio {

TestMemorySegment::TestMemorySegment(
    std::shared_ptr<MemoryConfig> memory_config
) : memory_config_(std::move(memory_config)) {
  memory_segment_ptr_ = std::make_unique<volatile uint8_t[]>(
      memory_config_->GetMappedBytesCount());
}

volatile uint8_t* TestMemorySegment::Get() {
  return memory_segment_ptr_.get();
}

} // namespace gpio
