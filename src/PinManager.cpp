#include "PinManager.h"

#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cassert>
#include <cstring>

#include "SysUtils.h"

namespace gpio {

// TODO: mmap gpio memory
PinManager::PinManager()
	: pin_function_locks_(PIN_FUNCTION_REG_COUNT)
{
	// Map the gpio peripherals into memory
	int fd = open("/dev/mem", O_RDWR | O_SYNC);
}

// TODO: unmap gpio memory
PinManager::~PinManager() {}

PinManager& PinManager::SetFunction(uint8_t pin_index, PinType pin_type) {}

} // namespace gpio
