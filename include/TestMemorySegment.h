#pragma once

#include <memory>

#include "MemorySegment.h"
#include "MemoryConfig.h"

namespace gpio {

class TestMemorySegment : public MemorySegment {
 public:
  TestMemorySegment(std::shared_ptr<MemoryConfig> memory_config);
  volatile uint8_t* Get() override;

 private:
  std::shared_ptr<MemoryConfig> memory_config_;
  std::unique_ptr<volatile uint8_t[]> memory_segment_ptr_;
};

} // namespace gpio
