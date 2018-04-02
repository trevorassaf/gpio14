#include "gtest/gtest.h"

#include <chrono>
#include <memory>
#include <thread>
#include <utility>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561I2cAddress.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561Factory.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561IntegrationTime.h"
#include "I2c/RpiI2cContext.h"

using I2c::RpiI2cContext;
using I2c::Tsl2561;
using I2c::Tsl2561I2cAddress;
using I2c::Tsl2561Factory;
using I2c::Tsl2561IntegrationTime;
using System::RpiSystemContext;

namespace
{
constexpr Tsl2561I2cAddress SLAVE_ADDRESS = Tsl2561I2cAddress::I2C0x39;
constexpr size_t PART_NUMBER = 5;
constexpr size_t REVISION_ID = 0;
} // namespace


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
	RpiSystemContext m_rpiSystemContext;
	std::unique_ptr<RpiI2cContext> m_rpiI2cContext;
	std::unique_ptr<Tsl2561Factory> m_tsl2561Factory;
};

TEST_F(Tsl2561DeviceTest, CheckDeviceConnection)
{
		auto device = m_tsl2561Factory->MakeBus1Device(SLAVE_ADDRESS);
}

TEST_F(Tsl2561DeviceTest, ReadId)
{
		auto device = m_tsl2561Factory->MakeBus1Device(SLAVE_ADDRESS);
    auto id = device->ReadId();
    EXPECT_EQ(id.GetPartNumber(), PART_NUMBER);
    EXPECT_EQ(id.GetRevisionId(), REVISION_ID);
}

TEST_F(Tsl2561DeviceTest, BasicAdc)
{
		auto device = m_tsl2561Factory->MakeBus1Device(SLAVE_ADDRESS);
//    device->SetHighGain();
//    device->SetLowGain();
//    device->SetIntegrationTime(Tsl2561IntegrationTime::INTEGRATION_TIME_402_MS);
    device->SetIntegrationTime(Tsl2561IntegrationTime::INTEGRATION_TIME_101_MS);
//    device->SetIntegrationTime(Tsl2561IntegrationTime::INTEGRATION_TIME_13_7_MS);
    std::this_thread::sleep_for(std::chrono::milliseconds{500});
    auto lux = device->ReadLux();
    std::cout << "IR spectrum: " << lux.irSpectrumLux << std::endl;
    std::cout << "Visible spectrum: " << lux.visibleSpectrumLux << std::endl;
}


