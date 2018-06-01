#pragma once

#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Core.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Status.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280HumidityControl.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280MeasurementControl.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Config.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/bme280_bulk_readout.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/bme280_calibration.h"
#include "I2c/I2cClient.h"

namespace I2c
{
class Bme280
{
public:
	Bme280(I2cClient *i2c);
	~Bme280();
	Bme280(Bme280 &&other);
	Bme280 &operator=(Bme280 &&other);

	uint8_t GetChipId();
	void PowerOnReset();
	Bme280HumidityControl	GetHumidityControl();
	void SetHumidityControl(Bme280HumidityControl control);
	Bme280Status GetStatus();
	Bme280MeasurementControl GetMeasurementControl();
	void SetMeasurementControl(Bme280MeasurementControl control);
	Bme280Config GetConfig();
	void SetConfig(Bme280Config config);
	bme280_bulk_readout_t ReadSensor();
	bme280_temp_calib_t ReadTemperatureCalibration();
	bme280_pres_calib_t ReadPressureCalibration();
	bme280_hum_calib_t ReadHumidityCalibration();

private:
	void p_DoClose(Bme280Core *core);
	void p_DoMove(Bme280 *other);

private:
	Bme280Core m_core;
};
} // namespace I2c
