#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Core.h"

#include <bitset>
#include <cassert>
#include <iostream>

#include "I2c/I2cException.h"

namespace
{
constexpr uint8_t TEMP_CALIB_BASE_REG = 0x88;
constexpr uint8_t PRES_CALIB_BASE_REG = 0x8E;
constexpr uint8_t HUM_CALIB_BASE_1_REG = 0xA1;

constexpr uint8_t ID_REG = 0xD0;
constexpr uint8_t RESET_REG = 0xE0;
constexpr uint8_t CTRL_HUM_REG = 0xF2;
constexpr uint8_t STATUS_REG = 0xF3;
constexpr uint8_t CTRL_MEAS_REG = 0xF4;
constexpr uint8_t CONFIG_REG = 0xF5;
constexpr uint8_t PRES_MSB_REG = 0xF7;
constexpr uint8_t PRES_LSB_REG = 0xF8;
constexpr uint8_t PRES_XLSB_REG = 0xF9;
constexpr uint8_t TEMP_MSB_REG = 0xFA;
constexpr uint8_t TEMP_LSB_REG = 0xFB;
constexpr uint8_t TEMP_XLSB_REG = 0xFC;
constexpr uint8_t HUM_MSB_REG = 0xFD;
constexpr uint8_t HUM_LSB_REG = 0xFE;

constexpr uint8_t HUM_CALIB_BASE_2_REG = 0xE1;

constexpr size_t TEMP_READOUT_SIZE = 3;
} // namespace

namespace I2c
{
Bme280Core::Bme280Core(I2cClient *i2c) : m_i2c{i2c} {}

Bme280Core::~Bme280Core() {}

Bme280Core::Bme280Core(Bme280Core &&other)
{
		p_DoMove(&other);
}

Bme280Core &Bme280Core::operator=(Bme280Core &&other)
{
		p_DoMove(&other);
		return *this;
}

bool Bme280Core::ReadIdRegister(uint8_t *outId)
{
		assert(outId);
		return p_Read(ID_REG, outId, sizeof(uint8_t));
}

bool Bme280Core::WriteResetRegister(uint8_t reg)
{
		if (!p_Write(RESET_REG, &reg, sizeof(reg)))
		{
				std::cerr << "Bme280Core: Failed to write reset register" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadHumidityControlRegister(uint8_t *outReg)
{
		assert(outReg);
		if (!p_Read(CTRL_HUM_REG, outReg, sizeof(*outReg)))
		{
				std::cerr << "Bme280Core: Failed to read humidity control register" << std::endl;
				return false;
		}
		return false;
}

bool Bme280Core::WriteHumidityControlRegister(uint8_t reg)
{
		if (!p_Write(CTRL_HUM_REG, &reg, sizeof(reg)))
		{
				std::cerr << "Bme280Core: Failed to write humidity control register" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadStatusRegister(uint8_t *outReg)
{
		assert(outReg);
		if (!p_Read(STATUS_REG, outReg, sizeof(*outReg)))
		{
				std::cerr << "Bme280Core: Failed to read status register" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadMeasurementControlRegister(uint8_t *outReg)
{
		assert(outReg);
		if (!p_Read(CTRL_MEAS_REG, outReg, sizeof(outReg)))
		{
				std::cerr << "Bme280Core: Failed to read measurement control register" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::WriteMeasurementControlRegister(uint8_t reg)
{
		if (!p_Write(CTRL_MEAS_REG, &reg, sizeof(reg)))
		{
				std::cerr << "Bme280Core: Failed to write measurement control register" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadConfigRegister(uint8_t *outReg)
{
		assert(outReg);
		if (!p_Read(CONFIG_REG, outReg, sizeof(*outReg)))
		{
				std::cerr << "Bme280Core: Failed to read config register" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::WriteConfigRegister(uint8_t reg)
{
		if (!p_Write(CONFIG_REG, &reg, sizeof(reg)))
		{
				std::cerr << "Bme280Core: Failed to write config register" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadTemperatureCalibrationData(bme280_temp_calib_t *outData)
{
		assert(outData);
		if (!p_Read(TEMP_CALIB_BASE_REG, reinterpret_cast<uint8_t *>(outData), sizeof(*outData)))
		{
				std::cerr << "Bme280Core: Failed to read temperature calibration data" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadPressureCalibrationData(bme280_pres_calib_t *outData)
{
		assert(outData);
		if (!p_Read(PRES_CALIB_BASE_REG, reinterpret_cast<uint8_t *>(outData), sizeof(*outData)))
		{
				std::cerr << "Bme280Core: Failed to read pressure calibration data" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadHumidityCalibrationData(bme280_hum_calib_t *outData)
{
		assert(outData);
		if (!p_Read(
					HUM_CALIB_BASE_1_REG,
					reinterpret_cast<uint8_t *>(&outData->top),
					sizeof(outData->top)))
		{
				std::cerr << "Bme280Core: Failed to read top half of humidity calibration data"
					        << std::endl;
				return false;
		}

		if (!p_Read(
					HUM_CALIB_BASE_2_REG,
					reinterpret_cast<uint8_t *>(&outData->bottom),
					sizeof(outData->bottom)))
		{
				std::cerr << "Bme280Core: Failed to read bottom half of humidity calibration data"
									<< std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadPressure(uint32_t *outData)
{
		assert(outData);
		if (!p_Read(PRES_MSB_REG, reinterpret_cast<uint8_t *>(outData), sizeof(*outData)))
		{
				std::cerr << "Bme280Core: Failed to read pressure data" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadTemperature(uint32_t *outData)
{
		assert(outData);
    *outData = 0;
		if (!p_Read(TEMP_MSB_REG, reinterpret_cast<uint8_t *>(outData), 4))
		{
				std::cerr << "Bme280Core: Failed to read temperature data" << std::endl;
				return false;
		}

		return true;
}

bool Bme280Core::ReadHumidity(uint16_t *outData)
{
		assert(outData);
		if (!p_Read(HUM_MSB_REG, reinterpret_cast<uint8_t *>(outData), sizeof(*outData)))
		{
				std::cerr << "Bme280Core: Failed to read humidity data" << std::endl;
				return false;
		}
		return true;
}

bool Bme280Core::ReadAllSensorData(bme280_bulk_readout_t *outData)
{
		assert(outData);
		if (!p_Read(PRES_MSB_REG, reinterpret_cast<uint8_t *>(outData), sizeof(*outData)))
		{
				std::cerr << "Bme280Core: Failed to perform bulk sensor data read" << std::endl;
				return false;
		}
		return true;
}

void Bme280Core::p_DoMove(Bme280Core *other)
{
		m_i2c = other->m_i2c;
		other->m_i2c = nullptr;
}

bool Bme280Core::p_Read(uint8_t regAddr, uint8_t *buffer, size_t size)
{
		try
		{
				m_i2c->Write(&regAddr, 1);
		}
		catch (const I2cException &e)
		{
				std::cerr << "Bme280Core: Failed to set I2c register address when performing read"
									<< std::endl;
				return false;
		}

		try
		{
				m_i2c->Read(buffer, sizeof(size));
		}
		catch (const I2cException &e)
		{
				std::cerr << "Bme280Core: Failed to perform I2c read" << std::endl;
				return false;
		}

		return true;
}

bool Bme280Core::p_Write(uint8_t regAddr, const uint8_t *buffer, size_t size)
{
		size_t physicalBufferSize = 2 * size;
		auto physicalBuffer = std::make_unique<uint8_t[]>(physicalBufferSize);
		uint8_t *physicalBufferPtr = physicalBuffer.get();

		for (int i = 0; i < size; ++i)
		{
				*physicalBufferPtr++ = regAddr;
				*physicalBufferPtr++ = buffer[i];
		}
	
		try
		{
				m_i2c->Write(physicalBuffer.get(), physicalBufferSize);
		}
		catch (const I2cException &e)
		{
				std::cerr << "Bme280Core: Failed to write" << std::endl;
				return false;
		}

		return true;
}

} // namespace I2c
