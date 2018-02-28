#pragma once

#include <cstdint>
#include <cstdlib>

namespace I2c
{
class I2cIoctlOps
{
public:
	virtual void SetSlaveAddress(int fd, uint8_t slaveAddress) = 0;
};
} // namespace I2c
