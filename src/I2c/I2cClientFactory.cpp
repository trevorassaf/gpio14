#include "I2c/I2cClientFactory.h"

#include <memory>
#include <utility>

#include "Utils/Fd.h"

using Utils::FdOps;

namespace I2c
{

I2cClientFactory::I2cClientFactory(
		I2cIoctlOps *ioctlOps,
		FdOps *fdOps)
	: m_ioctlOps{ioctlOps},
	  m_fdOps{fdOps} {}

std::unique_ptr<I2cClient> I2cClientFactory::Make(const std::string &deviceName)
{
		return Make(deviceName.c_str());
}

std::unique_ptr<I2cClient> I2cClientFactory::Make(const char *deviceName)
{
		auto fd = std::make_unique<Utils::Fd>(m_fdOps, deviceName);
		return std::make_unique<I2cClient>(m_ioctlOps, std::move(fd));
}

} // namespace I2c
