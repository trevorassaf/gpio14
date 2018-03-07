#pragma once

#include <memory>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561.h"
#include "I2c/RpiI2cContext.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561I2cAddress.h"

namespace I2c
{
class Tsl2561Factory
{
public:
	Tsl2561Factory(RpiI2cContext *rpiI2cContext);
	std::unique_ptr<Tsl2561> MakeBus1Device(Tsl2561I2cAddress address);
	std::unique_ptr<Tsl2561> MakeBus2Device(Tsl2561I2cAddress address);

private:
	RpiI2cContext *m_rpiI2cContext;
};
} // namespace I2c
