#pragma once

#include <cstdint>

#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Oversampling.h"

namespace I2c
{
class Bme280HumidityControl
{
public:
	bool IsValid(uint8_t reg);

public:
	Bme280HumidityControl Skipped();
	Bme280HumidityControl Oversampling1x();
	Bme280HumidityControl Oversampling2x();
	Bme280HumidityControl Oversampling4x();
	Bme280HumidityControl Oversampling8x();
	Bme280HumidityControl Oversampling16x();

public:
	Bme280HumidityControl(Bme280Oversampling oversampling);
	Bme280HumidityControl(uint8_t reg);
	Bme280Oversampling Oversampling() const;
	uint8_t Register() const;

private:
	Bme280Oversampling m_oversampling;
};
} // namespace I2c
