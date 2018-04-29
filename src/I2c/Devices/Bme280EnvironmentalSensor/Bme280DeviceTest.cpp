#include "gtest/gtest.h"

#include <chrono>
#include <ios>
#include <iostream>
#include <memory>
#include <thread>
#include <utility>

#include "I2c/Devices/Bme280EnvironmentalSensor/Bme280Core.h"
#include "I2c/RpiI2cContext.h"

using I2c::Bme280Core;
using I2c::RpiI2cContext;
using System::RpiSystemContext;

class Bme280CoreDeviceTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
			m_rpiI2cContext = std::make_unique<RpiI2cContext>(&m_rpiSystemContext);
			m_core = std::make_unique<Bme280Core>(m_rpiI2cContext->GetBus1I2cClient());
	}

	virtual void TearDown() {}

public:
	RpiSystemContext m_rpiSystemContext;
	std::unique_ptr<RpiI2cContext> m_rpiI2cContext;
	std::unique_ptr<Bme280Core> m_core;
};

TEST_F(Bme280CoreDeviceTest, BasicTest)
{
		assert(m_core->WriteResetRegister(0xB6));
		uint8_t id;
		assert(m_core->ReadIdRegister(&id));

		std::cout << "Bme280Core: id register: 0x" << std::hex << id << std::endl;
}
