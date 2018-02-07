#include "I2c/I2cClientFactory.h"

using Utils::FdOps;

namespace I2c
{

I2cClientFactory::I2cClientFactory(FdOps *ops) : m_ops{ops} {}

std::unique_ptr<I2cClient> I2cClientFactory::Make(const std::string &deviceName)
{
		return std::make_unique<I2cClient>(m_ops, deviceName.c_str());
}

std::unique_ptr<I2cClient> I2cClientFactory::Make(const char *deviceName)
{
		return std::make_unique<I2cClient>(m_ops, deviceName);
}

} // namespace I2c
