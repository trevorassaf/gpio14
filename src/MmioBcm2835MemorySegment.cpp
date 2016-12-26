#include "MmioBcm2835MemorySegment.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <utility>
#include <stdexcept>

#include "SysUtils.h"
#include "ScopeGuard.h"

namespace gpio {

MmioBcm2835MemorySegment::MmioBcm2835MemorySegment(
    std::shared_ptr<MemoryConfig> memory_config
) : memory_config_(std::move(memory_config)) {
  // Map gpio peripherals into memory
  int fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  ScopeGuard<int> close_file_guard(fd, [] (int& fd) { close(fd); });

  void* memory = mmap(
      nullptr,
      memory_config_->GetMappedBytesCount(),
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      memory_config_->GetPhysicalMemoryByteOffset());

  // Handle error
  if (memory == MAP_FAILED) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  memory_segment_ptr_ = static_cast<volatile uint8_t*>(memory);
}

MmioBcm2835MemorySegment::~MmioBcm2835MemorySegment() {
  int result = ::munmap((void *)memory_segment_ptr_, memory_config_->GetMappedBytesCount());

  // Handle error
  // TODO(bozkurtus): log here
  if (result == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }
}

volatile uint8_t* MmioBcm2835MemorySegment::Get() {
  return memory_segment_ptr_;
}

} // namespace gpio
