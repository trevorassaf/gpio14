#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Compensator.h"

#include <algorithm>

namespace I2c
{

Bme280Compensator::Bme280Compensator(
		bme280_temp_calib_t temperature,
		bme280_pres_calib_t pressure,
		bme280_hum_calib_t humidity)
	: m_temperature{temperature},
		m_pressure{pressure},
		m_humidity{humidity},
		m_tFine{0}
{}

int32_t Bme280Compensator::CompensateTemperature(int32_t adcT)
{
		int32_t var1 = ((((adcT >> 3) - (static_cast<int32_t>(m_temperature.dig1) << 1)))
				* static_cast<int32_t>(m_temperature.dig2)) >> 11;
		int32_t var2 = (((((adcT >> 4) - static_cast<int32_t>(m_temperature.dig1))
						* ((adcT >> 4) - static_cast<int32_t>(m_temperature.dig1))) >> 12)
					  * static_cast<int32_t>(m_temperature.dig3)) >> 14;
		m_tFine = var1 + var2;
		int32_t temp = (m_tFine * 5 + 128) >> 8;
		return temp;
}

uint32_t Bme280Compensator::CompensatePressure(int32_t adcP)
{
		int64_t var1 = static_cast<int64_t>(m_tFine) - 128000;
		int64_t var2 = var1 * var1 * static_cast<int64_t>(m_pressure.dig6);
		var2 = var2 + ((var1 * static_cast<int64_t>(m_pressure.dig5)) << 17);
		var2 = var2 + (static_cast<int64_t>(m_pressure.dig4) << 35);
		var1 = ((var1 * var1 * static_cast<int64_t>(m_pressure.dig3)) >> 8) + ((var1 * static_cast<int64_t>(m_pressure.dig2)) << 12);
		var1 = (((static_cast<int64_t>(1) << 47) + var1)) * static_cast<int64_t>(m_pressure.dig1) >> 33;
		if (var1 == 0)
		{
				return 0;
		}
		int64_t pressure = 1048576 - adcP;
		pressure = (((pressure << 31) - var2) * 3125) / var1;
		var1 = (static_cast<int64_t>(m_pressure.dig9) * (pressure >> 13) * (pressure >> 13)) >> 25;
		var2 = (static_cast<int64_t>(m_pressure.dig8) * pressure) >> 19;
		pressure = ((pressure + var1 + var2) >> 8) + (static_cast<int64_t>(m_pressure.dig7) << 4);
		return static_cast<uint32_t>(pressure);
}

uint32_t Bme280Compensator::CompensateHumidity(int32_t adcH)
{
		int32_t x1 = m_tFine - static_cast<int32_t>(76800);	
		x1 = (((((adcH << 14) - (static_cast<int32_t>(m_humidity.bottom.dig4) << 20) - (static_cast<int32_t>(m_humidity.bottom.dig5) * x1))
				+ static_cast<int32_t>(16384)) >> 15) * (((((((x1 * static_cast<int32_t>(m_humidity.bottom.dig6)) >> 10)
				* (((x1 * static_cast<int32_t>(m_humidity.bottom.dig3)) >> 11) + static_cast<int32_t>(32768))) >> 10) + static_cast<int32_t>(2097152))
				* static_cast<int32_t>(m_humidity.bottom.dig2) + 8192) >> 14));
		x1 = x1 - (((((x1 >> 15) * (x1 >> 15)) >> 7) * static_cast<int32_t>(m_humidity.top.dig1)) >> 4);
		x1 = std::max(x1, 0);
		x1 = std::min(x1, 419430400);
		return static_cast<uint32_t>(x1 >> 12);
}
} // namespace I2c
