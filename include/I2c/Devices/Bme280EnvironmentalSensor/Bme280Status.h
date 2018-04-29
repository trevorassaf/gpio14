#pragma once

#include <cstdint>

namespace I2c
{
class Bme280Status
{
public:
	Bme280Status(uint8_t byte);
	bool MeasurementInProgress();
	bool ImageRegistersUpdating();

private:
	uint8_t m_byte;
};
} // namespace I2c
