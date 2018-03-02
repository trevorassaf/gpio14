#pragma once

#include <memory>

#include "I2c/I2cClient.h"
#include "I2c/I2cClientFactory.h"
#include "I2c/BasicI2cIoctlOps.h"
#include "System/RpiSystemContext.h"

namespace I2c
{
class RpiI2cContext
{
public:
	RpiI2cContext(System::RpiSystemContext *rpiSystemContext);
	I2cClient *GetBus1I2cClient();
	I2cClient *GetBus2I2cClient();

private:
	void p_LazyInitializeI2cBus(std::unique_ptr<I2cClient> *i2cClient, const char *busName);

private:
	System::RpiSystemContext *m_rpiSystemContext;
	BasicI2cIoctlOps m_i2cIoctlOps;
	I2cClientFactory m_i2cClientFactory;
	std::unique_ptr<I2cClient> m_bus1I2cClient;
	std::unique_ptr<I2cClient> m_bus2I2cClient;
};
} // namespace I2c
