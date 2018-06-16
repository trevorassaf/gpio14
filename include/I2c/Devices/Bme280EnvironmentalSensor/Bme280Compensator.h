#pragma once

#include <cstdint>

#include "I2c/Devices/Bme280EnvironmentalSensor/bme280_calibration.h"

namespace I2c
{
class Bme280Compensator
{
public:
	Bme280Compensator(
			bme280_temp_calib_t temperature,
			bme280_pres_calib_t pressure,
			bme280_hum_calib_t humidity);
	int32_t  CompensateTemperature(int32_t adcT);
	uint32_t CompensatePressure(int32_t adcP);
	uint32_t CompensateHumidity(int32_t adcH);

private:
	bme280_temp_calib_t m_temperature;
	bme280_pres_calib_t m_pressure;
	bme280_hum_calib_t m_humidity;
	int32_t m_tFine;
};
} // namespace I2c
