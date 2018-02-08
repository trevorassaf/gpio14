#include "I2c/I2cClientFactory.h"

#include <memory>
#include <utility>

#include "Utils/Fd.h"

using Utils::FdOps;

namespace I2c
{

I2cClientFactory::I2cClientFactory(FdOps *ops) : m_ops{ops} {}

std::unique_ptr<I2cClient> I2cClientFactory::Make(const std::string &deviceName)
{
		return Make(deviceName.c_str());
}

std::unique_ptr<I2cClient> I2cClientFactory::Make(const char *deviceName)
{
		auto fd = std::make_unique<Utils::Fd>(m_ops, deviceName);
		return std::make_unique<I2cClient>(std::move(fd));
}

} // namespace I2c
