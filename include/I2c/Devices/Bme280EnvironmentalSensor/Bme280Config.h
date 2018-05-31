#pragma once

#include <cstdint>

namespace I2c
{

class Bme280Config
{
public:
	enum class StandbyDuration : uint8_t
	{
			DURATION_0_5_MS  = 0b000,
			DURATION_62_5_MS = 0b001,
			DURATION_125_MS  = 0b010,
			DURATION_250_MS  = 0b011,
			DURATION_500_MS  = 0b100,
			DURATION_1000_MS = 0b101,
			DURATION_10_MS   = 0b110,
			DURATION_20_MS   = 0b111,
	};

	enum class Filter : uint8_t
	{
			OFF = 0b000,
			COEF_2 = 0b001,
			COEF_4 = 0b010,
			COEF_8 = 0b011,
			COEF_16 = 0b100,
	};

public:
	Bme280Config();
	Bme280Config(uint8_t bits);
	Bme280Config(StandbyDuration duration, Filter filter, bool spi3Enabled);
	uint8_t GetBits() const;
	StandbyDuration GetStandbyDuration() const;
	Filter GetFilter() const;
	bool GetSpi3Enabled() const;

private:
	void p_SetStandbyDuration(StandbyDuration duration);
	void p_SetFilter(Filter filter);
	void p_SetSpi3Enabled(bool enabled);

private:
	uint8_t m_bits;
};
} // namespace I2c
