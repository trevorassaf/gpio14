#pragma once

#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Core.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Status.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280HumidityControl.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280MeasurementControl.h"
#include "I2c/I2cClient.h"

namespace I2c
{
class Bme280
{
public:
	struct status_t
	{
			bool measurementInProcess;
			bool imUpdate;
	};

public:
	Bme280(I2cClient *i2c);
	~Bme280();
	Bme280(Bme280 &&other);
	Bme280 &operator=(Bme280 &&other);

	uint8_t ChipId();
	void PowerOnReset();
	Bme280HumidityControl	HumidityControl();
	void SetHumidityControl(Bme280HumidityControl control);
	Bme280Status Status();
	Bme280MeasurementControl MeasurementControl();
	void SetMeasurementControl(Bme280MeasurementControl control);

	// Ctrl measurement


private:
	void p_DoClose(Bme280Core *core);
	void p_DoMove(Bme280 *other);

private:
	Bme280Core m_core;
};
} // namespace I2c
