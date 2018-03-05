#include "I2c/I2cClientFactory.h"

#include <memory>
#include <utility>

#include "Utils/Fd.h"
#include "Utils/FdException.h"
#include "Utils/FdOps.h"
#include "I2c/I2cException.h"

using Utils::FdOps;
using Utils::Fd;
using Utils::FdException;

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
		std::unique_ptr<Fd> fd;
		try
		{
			fd = std::make_unique<Fd>(m_fdOps, deviceName);
		}
		catch (const FdException &e)
		{
			throw I2cException{e.what()};
		}

		return std::make_unique<I2cClient>(m_ioctlOps, std::move(fd));
}

} // namespace I2c
