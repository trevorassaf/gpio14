#include "PinManager.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

#include <cassert>
#include <cstring>
#include <stdexcept>

#include "SysUtils.h"
#include "ScopeGuard.h"

namespace gpio {

PinManager::PinManager()
	: pin_function_locks_(PIN_FUNCTION_REG_COUNT)
{
	// Map gpio peripherals into memory
	int fd = open("/dev/mem", O_RDWR | O_SYNC);

  if (fd == -1) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  ScopeGuard<int> close_file_guard(fd, [] (int& fd) -> void {
    close(fd);
  });

  void* memory = mmap(
      nullptr,
      PAGE_SIZE,
      PROT_READ | PROT_WRITE,
      MAP_SHARED,
      fd,
      GPIO_MEMORY_OFFSET);

  if (memory == MAP_FAILED) {
    throw std::runtime_error(SysUtils::GetErrorMessage());
  }

  gpio_base_ = static_cast<volatile uint64_t*>(memory);
}

// TODO: unmap gpio memory
PinManager::~PinManager() {}

PinManager& PinManager::SetFunction(uint8_t pin_index, PinType pin_type) {}

} // namespace gpio
