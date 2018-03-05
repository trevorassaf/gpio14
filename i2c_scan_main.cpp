#include <cstdint>

#include <iostream>

#include "I2c/I2cException.h"
#include "I2c/I2cClient.h"
#include "I2c/RpiI2cContext.h"
#include "System/RpiSystemContext.h"

using I2c::I2cException;
using I2c::I2cClient;
using I2c::RpiI2cContext;
using System::RpiSystemContext;

constexpr uint8_t I2C_MAX_ADDRESS = 0x7F;

void scan_i2c_bus(I2cClient *client)
{
	for (int i = 0; i < I2C_MAX_ADDRESS; ++i)
	{
		try
		{
			client->SetSlave(i);
		}
		catch (const I2cException &e)
		{
				std::cout << "No I2c slave exists at address " << i
									<< ". Error message: " << e.what() << std::endl;
		}
	}
}

int main(int argc, const char **argv)
{
		RpiSystemContext rpiSystemContext;
		RpiI2cContext rpiI2cContext{&rpiSystemContext};

		try
		{
				I2cClient *client1 = rpiI2cContext.GetBus1I2cClient();
				scan_i2c_bus(client1);
		}
		catch (const I2cException &e)
		{
				std::cout << "Failed to initialize I2cBus 1" << std::endl;
		}

		try
		{
				I2cClient *client2 = rpiI2cContext.GetBus2I2cClient();
				scan_i2c_bus(client2);
		}
		catch (const I2cException &e)
		{
				std::cout << "Failed to initialize I2cBus 2" << std::endl;
		}

		return 0;
}
