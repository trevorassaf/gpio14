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
		const MemoryConfig *memoryConfig
) : m_memoryConfig{memoryConfig} {
  // Map gpio peripherals to memory
  int fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  ScopeGuard<int> closeFileGuard(fd, [] (int& fd) { close(fd); });

  void* memory = mmap(
      nullptr,
      m_memoryConfig->GetMappedBytesCount(),
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      m_memoryConfig->GetPhysicalMemoryByteOffset());

  if (memory == MAP_FAILED) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  m_memory = static_cast<volatile uint8_t*>(memory);
}

MmioBcm2835MemorySegment::~MmioBcm2835MemorySegment() {
  int result = ::munmap((void *)m_memory, m_memoryConfig->GetMappedBytesCount());

  if (result == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }
}

volatile uint8_t* MmioBcm2835MemorySegment::Get() {
  return m_memory;
}

} // namespace gpio
