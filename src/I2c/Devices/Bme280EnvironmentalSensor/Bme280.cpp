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

Bme280HumidityControl Bme280::HumidityControl()
{
		uint8_t reg;
		if (!m_core.ReadHumidityControlRegister(&reg))
		{
				throw I2cException{"Bme280: Failed to read humidity control register"};
		}
		return Bme280HumidityControl{reg};
}

void Bme280::SetHumidityControl(Bme280HumidityControl control)
{
		if (!m_core.WriteHumidityControlRegister(control.Register()))
		{
				throw I2cException{"Bme280: Failed to write humidity control reg"};
		}
}

Bme280Status Bme280::Status()
{
		uint8_t reg;
		if (!m_core.ReadStatusRegister(&reg))	
		{
				throw I2cException{"Bme280: Failed to read status register"};
		}
		return Bme280Status{reg};
}

Bme280MeasurementControl Bme280::MeasurementControl()
{
		uint8_t reg;
		if (!m_core.ReadMeasurementControlRegister(&reg))
		{
				throw I2cException{"Bme280: Failed to read measurement control register"};
		}
		return Bme280MeasurementControl{reg};
}

void Bme280::SetMeasurementControl(Bme280MeasurementControl control)
{
		if (!m_core.WriteMeasurementControlRegister(control.GetBits()))
		{
				throw I2cException{"Bme280: Failed to write measurement control register"};
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
