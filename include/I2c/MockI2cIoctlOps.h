#pragma once

#include <functional>
#include <iostream>

#include "I2c/I2cIoctlOps.h"

namespace I2c
{

typedef std::function<void(int, uint8_t)> set_slave_t;

class MockI2cIoctlOps : public I2cIoctlOps
{
public:
	MockI2cIoctlOps() : m_setSlaveLambda{nullptr} {}

	MockI2cIoctlOps(set_slave_t setSlaveAddressLambda)
		: m_setSlaveLambda{setSlaveAddressLambda} {}

	void SetSlaveAddressLambda(set_slave_t setSlaveAddressLambda)
	{
			m_setSlaveLambda = setSlaveAddressLambda;
	}

	void SetSlaveAddress(int fd, uint8_t slaveAddress) override
	{
			if (m_setSlaveLambda)
			{
					m_setSlaveLambda(fd, slaveAddress);
			}
	}

private:
	set_slave_t m_setSlaveLambda;
};

} // namespace I2c
