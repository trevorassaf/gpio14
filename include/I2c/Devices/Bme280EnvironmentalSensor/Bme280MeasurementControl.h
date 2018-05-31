#pragma once

#include <cstdint>

#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Oversampling.h"

namespace I2c
{
// Note: Changes take effect after writing ctrl_hum
class Bme280MeasurementControl
{
public:
	enum class Mode : uint8_t
	{
			SLEEP    = 0b00,
			FORCED_1 = 0b01,
			FORCED_2 = 0b10,
			NORMAL   = 0b11,
	};

public:
	Bme280MeasurementControl(
			Bme280Oversampling temperature,
			Bme280Oversampling pressure,
			Mode mode);
  Bme280MeasurementControl(uint8_t reg);
  Bme280Oversampling GetTemperatureOversampling() const;
  Bme280Oversampling GetPressureOversampling() const;
  Mode GetMode() const;
  uint8_t GetBits() const;

private:
	void p_SetTemperatureOversampling(Bme280Oversampling sampling);
	void p_SetPressureOversampling(Bme280Oversampling sampling);
	void p_SetMode(Mode mode);

private:
	uint8_t m_reg;
};
} // namespace I2c
