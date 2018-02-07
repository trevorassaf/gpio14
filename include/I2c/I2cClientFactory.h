#pragma once

#include <memory>
#include <string>
#include <utility>

#include "I2c/I2cClient.h"
#include "Utils/FdOps.h"

namespace I2c
{

class I2cClientFactory
{
public:
	I2cClientFactory(Utils::FdOps *ops);
	std::unique_ptr<I2cClient> Make(const std::string &deviceName);
	std::unique_ptr<I2cClient> Make(const char *deviceName);

private:
	Utils::FdOps *m_ops;
};

} // namespace I2c
