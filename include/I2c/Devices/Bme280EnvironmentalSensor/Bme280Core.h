#pragma once

#include <cstdint>

#include "I2c/I2cClient.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/bme280_bulk_readout.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/bme280_calibration.h"

namespace I2c
{
class Bme280Core
{
public:
	Bme280Core(I2cClient *i2c);
	~Bme280Core();
	Bme280Core(Bme280Core &&other);
	Bme280Core &operator=(Bme280Core &&other);
	bool ReadIdRegister(uint8_t *outReg);
	bool WriteResetRegister(uint8_t reg);
	bool ReadHumidityControlRegister(uint8_t *outReg);
	bool WriteHumidityControlRegister(uint8_t reg);
	bool ReadStatusRegister(uint8_t *outReg);
	bool ReadMeasurementControlRegister(uint8_t *outReg);
	bool WriteMeasurementControlRegister(uint8_t reg);
	bool ReadConfigRegister(uint8_t *outReg);
	bool WriteConfigRegister(uint8_t reg);
	bool ReadTemperatureCalibrationData(bme280_temp_calib_t *outData);
	bool ReadPressureCalibrationData(bme280_pres_calib_t *outData);
	bool ReadHumidityCalibrationData(bme280_hum_calib_t *outData);

	bool ReadPressure(uint32_t *outData);
	bool ReadTemperature(uint32_t *outData);
	bool ReadHumidity(uint16_t *outData);
	bool ReadAllSensorData(bme280_bulk_readout_t *outData);

private:
	void p_DoMove(Bme280Core *other);
	bool p_Read(uint8_t regAddr, uint8_t *buffer, size_t size);
	bool p_Write(uint8_t regAddr, const uint8_t *buffer, size_t size);

private:
	I2cClient *m_i2c;
};
} // namespace I2c
