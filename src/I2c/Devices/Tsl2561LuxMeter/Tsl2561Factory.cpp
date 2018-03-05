#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561Factory.h"

namespace I2c
{
Tsl2561Factory::Tsl2561Factory(RpiI2cContext *rpiI2cContext)
	: m_rpiI2cContext{rpiI2cContext} {}

std::unique_ptr<Tsl2561> Tsl2561Factory::MakeBus1Device()
{
		return std::make_unique<Tsl2561>(m_rpiI2cContext->GetBus1I2cClient());
}

std::unique_ptr<Tsl2561> Tsl2561Factory::MakeBus2Device()
{
		return std::make_unique<Tsl2561>(m_rpiI2cContext->GetBus2I2cClient());
}
} // namespace
