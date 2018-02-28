#pragma once

#include "I2c/I2cIoctlOps.h"

namespace I2c
{
class BasicI2cIoctlOps : public I2cIoctlOps
{
public:
	void SetSlaveAddress(int fd, uint8_t slaveAddress) override;
};
} // namespace I2c
