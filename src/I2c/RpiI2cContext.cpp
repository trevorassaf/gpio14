#include "I2c/RpiI2cContext.h"

using System::RpiSystemContext;

namespace
{
constexpr const char *I2C_BUS_1 = "/dev/i2c-1";
constexpr const char *I2C_BUS_2 = "/dev/i2c-2";
} // namespace

namespace I2c
{
RpiI2cContext::RpiI2cContext(RpiSystemContext *rpiSystemContext)
	: m_rpiSystemContext{rpiSystemContext},
		m_i2cIoctlOps{},
		m_i2cClientFactory{&m_i2cIoctlOps, m_rpiSystemContext->GetFdOps()},
		m_bus1I2cClient{nullptr},
		m_bus2I2cClient{nullptr}
{}

I2cClient *RpiI2cContext::GetBus1I2cClient()
{
	p_LazyInitializeI2cBus(&m_bus1I2cClient, I2C_BUS_1);
	return m_bus1I2cClient.get();
}

I2cClient *RpiI2cContext::GetBus2I2cClient()
{
	p_LazyInitializeI2cBus(&m_bus2I2cClient, I2C_BUS_2);
	return m_bus2I2cClient.get();
}

void RpiI2cContext::p_LazyInitializeI2cBus(
		std::unique_ptr<I2cClient> *i2cClient,
		const char *busName)
{
	if (*i2cClient == nullptr)
	{
			*i2cClient = m_i2cClientFactory.Make(busName);
	}
}

} // namespace I2c
