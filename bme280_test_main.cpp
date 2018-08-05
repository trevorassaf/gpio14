#include <chrono>
#include <iostream>
#include <thread>

#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Compensator.h"
#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Manager.h"
#include "I2c/I2cException.h"
#include "I2c/I2cClient.h"
#include "I2c/RpiI2cContext.h"
#include "System/RpiSystemContext.h"
#include "Utils/BitUtils.h"

namespace
{
constexpr size_t BME280_I2C_ADDRESS = 0x76;
} // namespace

using I2c::bme280_bulk_readout_t;
using I2c::Bme280;
using I2c::Bme280Compensator;
using I2c::Bme280HumidityControl;
using I2c::Bme280MeasurementControl;
using I2c::Bme280Oversampling;
using I2c::I2cClient;
using I2c::RpiI2cContext;
using System::RpiSystemContext;

int main(int argc, const char **argv)
{
		RpiSystemContext systemContext;
		RpiI2cContext i2cContext{&systemContext};
		I2cClient *client1 = i2cContext.GetBus1I2cClient();
		client1->SetSlave(BME280_I2C_ADDRESS);
		Bme280 bme280{client1};
    bme280.PowerOnReset();
    std::this_thread::sleep_for(std::chrono::seconds{1});
		std::cout << "Bme280 chip id: " << std::hex << static_cast<int>(bme280.GetChipId()) << std::dec << std::endl;

    // Transition sensor from "sleep" mode to "forced" mode and read all environmental data
    // with 1x oversampling
    Bme280HumidityControl humidityControl{Bme280Oversampling::SKIPPED};
    bme280.SetHumidityControl(humidityControl);

    std::this_thread::sleep_for(std::chrono::milliseconds{100});

    Bme280Compensator compensator{
        bme280.ReadTemperatureCalibration(),
        bme280.ReadPressureCalibration(),
        bme280.ReadHumidityCalibration()};

    Bme280Oversampling temperatureOversampling = Bme280Oversampling::OVERSAMPLING_1X;
    Bme280Oversampling pressureOversampling = Bme280Oversampling::SKIPPED;
    Bme280MeasurementControl::Mode forcedMode = Bme280MeasurementControl::Mode::FORCED_1;
    Bme280MeasurementControl forcedModeControl{
        temperatureOversampling,
        pressureOversampling,
        forcedMode};
    bme280.SetMeasurementControl(forcedModeControl);
    std::this_thread::sleep_for(std::chrono::milliseconds{1000});

    uint32_t rawTemp = bme280.ReadTemperature();

    double tempC = compensator.CompensateTemperature(rawTemp);
    double tempF = 9.0/5.0 * tempC + 32;

    std::cout << "Raw Temperature readout: 0x" << std::hex << rawTemp << std::dec << std::endl;
    std::cout << "Raw Temperature readout: 0b" << Utils::BitUtils::ToBitString(rawTemp) << std::endl;
    std::cout << "Compensated temperature (C): " << tempC << std::endl;
    std::cout << "Compensated temperature (F): " << tempF << std::endl;

    // Read sensor data
    /*
    bme280_bulk_readout_t sensor = bme280.ReadSensor();
    std::cout << "Uncompensated pressure: 0x" << std::hex << sensor.pressure
              << std::dec << std::endl;
    std::cout << "Uncompensated temperature: 0x" << std::hex << sensor.temperature
              << std::dec << std::endl;
    std::cout << "Uncompensated humidity: 0x" << std::hex << sensor.humidity
              << std::dec << std::endl;

    Bme280Compensator compensator{
        bme280.ReadTemperatureCalibration(),
        bme280.ReadPressureCalibration(),
        bme280.ReadHumidityCalibration()};

    std::cout << "Compensated pressure: " << compensator.CompensatePressure(sensor.pressure) << std::endl;
    std::cout << "Compensated temperature: " << compensator.CompensateTemperature(sensor.temperature) << std::endl;
    std::cout << "Compensated humidity: " << compensator.CompensateHumidity(sensor.humidity) << std::endl;
    */
		return 0;
}
