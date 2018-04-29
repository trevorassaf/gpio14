#pragma once

#include <cstdint>

#include "I2c/I2cClient.h"

namespace I2c
{
class Bme280Core
{
public:
	struct data_readout_t
	{
			uint8_t presMsb;
			uint8_t presLsb;
			uint8_t presXlsb;

			uint8_t tempMsb;
			uint8_t tempLsb;
			uint8_t tempXlsb;

			uint8_t humMsb;
			uint8_t humLsb;
	} __attribute__((packed));

	struct temp_calib_readout_t
	{
			uint16_t dig1;
			int16_t  dig2;
			int16_t  dig3;
	} __attribute__((packed));

	struct pres_calib_readout_t
	{
			uint16_t dig1;
			int16_t  dig[8];
	} __attribute__((packed));

	struct hum_calib_top_half_t
	{
			uint8_t dig1;
	} __attribute__((packed));

	struct hum_calib_bottom_half_t
	{
			int16_t dig2;
			uint8_t dig3;
			int16_t dig4;
			int16_t dig5;
			int8_t  dig6;
	} __attribute__((packed));

	struct hum_calib_readout_t
	{
			hum_calib_top_half_t top;
			hum_calib_bottom_half_t bottom;
	} __attribute__((packed));

	struct sensor_bulk_readout_t
	{
			uint32_t pressure;
			uint32_t temperature;
			uint16_t humidity;
	} __attribute__((packed));

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
	bool ReadTemperatureCalibrationData(temp_calib_readout_t *outData);
	bool ReadPressureCalibrationData(pres_calib_readout_t *outData);
	bool ReadHumidityCalibrationData(hum_calib_readout_t *outData);

	bool ReadPressure(uint32_t *outData);
	bool ReadTemperature(uint32_t *outData);
	bool ReadHumidity(uint16_t *outData);
	bool ReadAllSensorData(sensor_bulk_readout_t *outData);

private:
	void p_DoMove(Bme280Core *other);
	bool p_Read(uint8_t regAddr, uint8_t *buffer, size_t size);
	bool p_Write(uint8_t regAddr, const uint8_t *buffer, size_t size);

private:
	I2cClient *m_i2c;
};
} // namespace I2c
