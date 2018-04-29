#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280.h"

#include <cstdlib>
#include <iostream>
#include <utility>

#include "I2c/I2cException.h"

namespace
{
constexpr size_t POWER_ON_RESET_CODE = 0xB6;
} // namespace

namespace I2c
{
Bme280::Bme280(I2cClient *i2c) : m_core{i2c} {}

Bme280::~Bme280()
{
		p_DoClose(&m_core);
}

Bme280::Bme280(Bme280 &&other) : m_core{nullptr}
{
		p_DoMove(&other);
}

Bme280 &Bme280::operator=(Bme280 &&other)
{
		p_DoClose(&m_core);
		p_DoMove(&other);
		return *this;
}

uint8_t Bme280::ChipId()
{
		uint8_t chipId;
		if (!m_core.ReadIdRegister(&chipId))
		{
				throw I2cException{"Bme280: Failed to read chip id"};
		}
		return chipId;
}

void Bme280::PowerOnReset()
{
		if (!m_core.WriteResetRegister(POWER_ON_RESET_CODE))
		{
				throw I2cException{"Bme280: Failed to perform power on reset"};
		}
}

void Bme280::p_DoClose(Bme280Core *other)
{
		if (other)
		{
				std::cerr << "Bme280::p_DoClose() -- TODO(bozkurtus): unsupported close operation"
									<< std::endl;
		}
}

void Bme280::p_DoMove(Bme280 *other)
{
		m_core = std::move(other->m_core);
}

} // namespace I2c
