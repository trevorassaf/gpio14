#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280HumidityControl.h"

#include <iostream>

#include "I2c/I2cException.h"

namespace I2c
{

bool Bme280HumidityControl::IsValid(uint8_t reg)
{
		return reg <= static_cast<uint8_t>(Bme280Oversampling::OVERSAMPLING_16X);
}

Bme280HumidityControl Bme280HumidityControl::Skipped()
{
		return Bme280HumidityControl{Bme280Oversampling::SKIPPED};
}

Bme280HumidityControl Bme280HumidityControl::Oversampling1x()
{
		return Bme280HumidityControl{Bme280Oversampling::OVERSAMPLING_1X};
}

Bme280HumidityControl Bme280HumidityControl::Oversampling2x()
{
		return Bme280HumidityControl{Bme280Oversampling::OVERSAMPLING_2X};
}

Bme280HumidityControl Bme280HumidityControl::Oversampling4x()
{
		return Bme280HumidityControl{Bme280Oversampling::OVERSAMPLING_4X};
}

Bme280HumidityControl Bme280HumidityControl::Oversampling8x()
{
		return Bme280HumidityControl{Bme280Oversampling::OVERSAMPLING_8X};
}

Bme280HumidityControl Bme280HumidityControl::Oversampling16x()
{
		return Bme280HumidityControl{Bme280Oversampling::OVERSAMPLING_16X};
}

Bme280HumidityControl::Bme280HumidityControl(Bme280Oversampling oversampling)
	: m_oversampling{oversampling} {}

Bme280HumidityControl::Bme280HumidityControl(uint8_t reg)
{
		if (!IsValid(reg))
		{
				std::cerr << "Bme280HumidityControl: Invalid reg: " << reg << std::endl;
				throw I2cException{"Bme280HumidityControl: Invalid humidity control reg"};
		}
}

Bme280Oversampling Bme280HumidityControl::Oversampling() const
{
		return m_oversampling;
}

uint8_t Bme280HumidityControl::Register() const
{
		return static_cast<uint8_t>(m_oversampling);
}

} // namespace I2c
