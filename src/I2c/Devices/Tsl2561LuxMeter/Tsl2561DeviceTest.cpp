#include "gtest/gtest.h"

#include <memory>
#include <utility>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561I2cAddress.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561Factory.h"
#include "I2c/RpiI2cContext.h"

using I2c::RpiI2cContext;
using I2c::Tsl2561;
using I2c::Tsl2561I2cAddress;
using I2c::Tsl2561Factory;
using System::RpiSystemContext;

class Tsl2561DeviceTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
			m_rpiI2cContext = std::make_unique<RpiI2cContext>(&m_rpiSystemContext);
			m_tsl2561Factory = std::make_unique<Tsl2561Factory>(m_rpiI2cContext.get());
	}

	virtual void TearDown()
	{
	}

public:
	static constexpr Tsl2561I2cAddress SLAVE_ADDRESS = Tsl2561I2cAddress::I2C0x30;

public:
	RpiSystemContext m_rpiSystemContext;
	std::unique_ptr<RpiI2cContext> m_rpiI2cContext;
	std::unique_ptr<Tsl2561Factory> m_tsl2561Factory;
};

TEST_F(Tsl2561DeviceTest, CheckDeviceConnection)
{
		auto client = m_tsl2561Factory->MakeBus1Device(SLAVE_ADDRESS);
}
