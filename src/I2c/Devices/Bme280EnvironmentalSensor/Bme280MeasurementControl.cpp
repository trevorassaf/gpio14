#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280MeasurementControl.h"

#include "Utils/BitUtils.h"

namespace
{
using Utils::BitUtils;
} // namespace I2c

namespace
{
constexpr size_t  TEMPERATURE_OVERSAMPLING_OFFSET = 5;
constexpr size_t  PRESSURE_OVERSAMPLING_OFFSET = 2;
constexpr size_t  MODE_OFFSET = 0;
constexpr uint8_t TEMPERATURE_OVERSAMPLING_MASK = 0b111 << TEMPERATURE_OVERSAMPLING_OFFSET;
constexpr uint8_t PRESSURE_OVERSAMPLING_MASK = 0b111 << PRESSURE_OVERSAMPLING_OFFSET;
constexpr uint8_t MODE_MASK = 0b11 << MODE_OFFSET;
} // namespace

namespace I2c
{
Bme280MeasurementControl::Bme280MeasurementControl(
		Bme280Oversampling temperature,
		Bme280Oversampling pressure,
		Mode mode)
	: m_reg{0}
{
		p_SetTemperatureOversampling(temperature);
		p_SetPressureOversampling(pressure);
		p_SetMode(mode);
}

Bme280MeasurementControl::Bme280MeasurementControl(uint8_t reg) : m_reg{reg} {}

Bme280Oversampling Bme280MeasurementControl::GetTemperatureOversampling() const
{
		return static_cast<Bme280Oversampling>(
				BitUtils::GetBits(m_reg, TEMPERATURE_OVERSAMPLING_MASK, TEMPERATURE_OVERSAMPLING_OFFSET));
}

Bme280Oversampling Bme280MeasurementControl::GetPressureOversampling() const
{
		return static_cast<Bme280Oversampling>(
				BitUtils::GetBits(m_reg, PRESSURE_OVERSAMPLING_MASK, PRESSURE_OVERSAMPLING_OFFSET));
}


Bme280MeasurementControl::Mode Bme280MeasurementControl::GetMode() const
{
		return static_cast<Mode>(
				BitUtils::GetBits(m_reg, MODE_MASK, MODE_OFFSET));
}

uint8_t Bme280MeasurementControl::GetBits() const
{
		return m_reg;
}

void Bme280MeasurementControl::p_SetTemperatureOversampling(Bme280Oversampling sampling)
{
		m_reg = BitUtils::SetByteWithMask(
				m_reg,
				static_cast<uint8_t>(sampling),
				TEMPERATURE_OVERSAMPLING_MASK,
				TEMPERATURE_OVERSAMPLING_OFFSET);
}

void Bme280MeasurementControl::p_SetPressureOversampling(Bme280Oversampling sampling)
{
		m_reg = BitUtils::SetByteWithMask(
				m_reg,
				static_cast<uint8_t>(sampling),
				PRESSURE_OVERSAMPLING_MASK,
				PRESSURE_OVERSAMPLING_OFFSET);
}

void Bme280MeasurementControl::p_SetMode(Mode mode)
{
		m_reg = BitUtils::SetByteWithMask(
				m_reg,
				static_cast<uint8_t>(mode),
				MODE_MASK,
				MODE_OFFSET);
}

} // namespace I2c
