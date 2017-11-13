#include "Memory/MmioBcm2835MemorySegment.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <utility>
#include <stdexcept>

#include "Utils/SysUtils.h"
#include "Utils/ScopeGuard.h"

using Utils::ScopeGuard;
using Utils::SysUtils;

namespace Memory {

MmioBcm2835MemorySegment::MmioBcm2835MemorySegment(
		const MmioConfig *mmioConfig
) : m_mmioConfig{mmioConfig} {
  // Map gpio peripherals to memory
  int fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  ScopeGuard<int> closeFileGuard(fd, [] (int& fd) { close(fd); });

  void* memory = mmap(
      nullptr,
      m_mmioConfig->GetMappedBytesCount(),
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      m_mmioConfig->GetPhysicalMemoryByteOffset());

  if (memory == MAP_FAILED) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  m_memory = static_cast<volatile uint8_t*>(memory);
}

MmioBcm2835MemorySegment::~MmioBcm2835MemorySegment() {
  int result = ::munmap((void *)m_memory, m_mmioConfig->GetMappedBytesCount());

  if (result == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }
}

volatile uint8_t* MmioBcm2835MemorySegment::Get() {
  return m_memory;
}

} // namespace Memory
