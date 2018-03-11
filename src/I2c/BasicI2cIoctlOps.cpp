#include "I2c/BasicI2cIoctlOps.h"

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

#include <cassert>

#include "I2c/I2cException.h"
#include "Utils/SysUtils.h"

#include <iostream>

using Utils::SysUtils;

namespace I2c
{

void BasicI2cIoctlOps::SetSlaveAddress(int fd, uint8_t slaveAddress)
{
		if (ioctl(fd, I2C_SLAVE, slaveAddress) < 0)
		{
        std::cout << "Failed to set slave address" << std::endl;
				throw I2cException(SysUtils::GetErrorMessage());
		}
}

} // namespace I2c
