#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Config.h"

#include <cstdlib>

#include "Utils/BitUtils.h"

namespace
{
using Utils::BitUtils;
} // namespace

namespace
{
constexpr size_t STANDBY_DURATION_OFFSET = 5;
constexpr size_t FILTER_OFFSET = 2;
constexpr size_t SPI_3_ENABLED_OFFSET = 0;
constexpr uint8_t STANDBY_DURATION_MASK = 0b111 << STANDBY_DURATION_OFFSET;
constexpr uint8_t FILTER_MASK = 0b111 << FILTER_OFFSET;
constexpr uint8_t SPI_3_ENABLED_MASK = 0b1;
} // namespace

namespace I2c
{
Bme280Config::Bme280Config() : m_bits{0} {}

Bme280Config::Bme280Config(uint8_t bits) : m_bits{bits} {}

Bme280Config::Bme280Config(StandbyDuration duration, Filter filter, bool spi3Enabled) : m_bits{0}
{
		p_SetStandbyDuration(duration);
		p_SetFilter(filter);
		p_SetSpi3Enabled(spi3Enabled);
}

uint8_t Bme280Config::GetBits() const
{
		return m_bits;
}

Bme280Config::StandbyDuration Bme280Config::GetStandbyDuration() const
{
		return static_cast<Bme280Config::StandbyDuration>(
				BitUtils::GetBits(m_bits, STANDBY_DURATION_MASK, STANDBY_DURATION_OFFSET));
}

Bme280Config::Filter Bme280Config::GetFilter() const
{
		return static_cast<Bme280Config::Filter>(
				BitUtils::GetBits(m_bits, FILTER_MASK, FILTER_OFFSET));
}

bool Bme280Config::GetSpi3Enabled() const
{
		return static_cast<bool>(BitUtils::GetBits(m_bits, SPI_3_ENABLED_MASK, SPI_3_ENABLED_OFFSET));
}

void Bme280Config::p_SetStandbyDuration(Bme280Config::StandbyDuration duration)
{
		m_bits = BitUtils::SetByteWithMask(
				m_bits,
				static_cast<uint8_t>(duration),
				STANDBY_DURATION_MASK,
				STANDBY_DURATION_OFFSET);
}

void Bme280Config::p_SetFilter(Bme280Config::Filter filter)
{
		m_bits = BitUtils::SetByteWithMask(
				m_bits,
				static_cast<uint8_t>(filter),
				FILTER_MASK,
				FILTER_OFFSET);
}

void Bme280Config::p_SetSpi3Enabled(bool enabled)
{
		m_bits = BitUtils::SetBitWithMask(
				m_bits,
				enabled,
				SPI_3_ENABLED_MASK,
				SPI_3_ENABLED_OFFSET);
}
} // namespace I2c
