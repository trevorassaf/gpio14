#pragma once

#include <memory>

#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Compensator.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280.h"
#include "I2c/I2cClient.h"

namespace I2c
{
class Bme280Manager
{
public:
	Bme280Manager(I2cClient *i2c);
	~Bme280Manager();

private:
	void p_Init();

private:
	Bme280 m_bme280;
	std::unique_ptr<Bme280Compensator> m_compensator;
};
} // namespace I2c
