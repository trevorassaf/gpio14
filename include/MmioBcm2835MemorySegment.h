#pragma once

#include <memory>

#include "MemorySegment.h"
#include "MemoryConfig.h"

namespace gpio {

class MmioBcm2835MemorySegment : public MemorySegment {
 public:
  MmioBcm2835MemorySegment(std::shared_ptr<MemoryConfig> memory_config);
  ~MmioBcm2835MemorySegment() override;

  volatile uint8_t* Get() override;

 private:
  std::shared_ptr<MemoryConfig> memory_config_;
  volatile uint8_t* memory_segment_ptr_;
};

} // namespace gpio
