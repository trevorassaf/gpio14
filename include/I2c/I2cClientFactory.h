#pragma once

#include <memory>
#include <string>
#include <utility>

#include "I2c/I2cClient.h"
#include "I2c/I2cIoctlOps.h"
#include "Utils/FdOps.h"

namespace I2c
{

class I2cClientFactory
{
public:
	I2cClientFactory(I2cIoctlOps *ioctlOps, Utils::FdOps *fdOps);
	std::unique_ptr<I2cClient> Make(const std::string &deviceName);
	std::unique_ptr<I2cClient> Make(const char *deviceName);

private:
	I2cIoctlOps *m_ioctlOps;
	Utils::FdOps *m_fdOps;
};

} // namespace I2c
