#pragma once

#include <cstdint>

namespace I2c
{
class Bme280HumidityControl
{
public:
	enum class oversampling_t : uint8_t
	{
			SKIPPED = 0b000,
			OVERSAMPLING_1X  = 0b001,
			OVERSAMPLING_2X  = 0b010,
			OVERSAMPLING_4X  = 0b011,
			OVERSAMPLING_8X  = 0b100,
			OVERSAMPLING_16X = 0b101,
	};

public:
	bool IsValid(uint8_t reg);

public:
	Bme280HumidityControl Skipped();
	Bme280HumidityControl Oversampling1x();
	Bme280HumidityControl Oversampling2x();
	Bme280HumidityControl Oversampling4x();
	Bme280HumidityControl Oversampling8x();
	Bme280HumidityControl Oversampling16x();

public:
	Bme280HumidityControl(oversampling_t oversampling);
	Bme280HumidityControl(uint8_t reg);
	oversampling_t Oversampling() const;
	uint8_t Register() const;

private:
	oversampling_t m_oversampling;
};
} // namespace I2c
