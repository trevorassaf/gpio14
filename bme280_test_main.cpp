#include <iostream>

#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Manager.h"
#include "I2c/I2cException.h"
#include "I2c/I2cClient.h"
#include "I2c/RpiI2cContext.h"
#include "System/RpiSystemContext.h"

namespace
{
constexpr size_t BME280_I2C_ADDRESS = 0x76;
} // namespace

using I2c::Bme280;
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
		std::cout << "Bme280 chip id: " << static_cast<int>(bme280.GetChipId()) << std::endl;
		return 0;
}
