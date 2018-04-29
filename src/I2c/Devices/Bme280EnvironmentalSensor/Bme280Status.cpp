#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Status.h"

#include <cstdlib>

namespace
{
constexpr size_t MEASUREMENT_IN_PROGRESS_BIT_IDX = 3;
constexpr size_t IMAGE_REGISTER_UPDATING_BIT_IDX = 0;
} // namespace

namespace I2c
{
Bme280Status::Bme280Status(uint8_t byte) : m_byte{byte} {}

bool Bme280Status::MeasurementInProgress()
{
		return (1 << MEASUREMENT_IN_PROGRESS_BIT_IDX) & m_byte;
}

bool Bme280Status::ImageRegistersUpdating()
{
		return (1 << IMAGE_REGISTER_UPDATING_BIT_IDX) & m_byte;
}
} // namespace I2c
