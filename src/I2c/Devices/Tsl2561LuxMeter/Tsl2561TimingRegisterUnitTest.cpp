#include "gtest/gtest.h"

#include <iostream>

#include <cstdint>
#include <bitset>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561IntegrationTime.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561TimingRegister.h"

using I2c::Tsl2561TimingRegister;
using I2c::Tsl2561IntegrationTime;

namespace
{
constexpr Tsl2561IntegrationTime DEFAULT_INTEGRATION_TIME =
	Tsl2561IntegrationTime::INTEGRATION_TIME_13_7_MS;
} // namespace

void ExpectDefaultInitialization(const Tsl2561TimingRegister &reg)
{
		EXPECT_FALSE(reg.IsLowGain());
		EXPECT_FALSE(reg.IsStartManualIntegrationCycle());
		EXPECT_EQ(reg.GetIntegrationTime(), DEFAULT_INTEGRATION_TIME);
}

TEST(Tsl2561TimingRegisterTest, DefaultInitialization)
{
		Tsl2561TimingRegister reg;
		ExpectDefaultInitialization(reg);
}

TEST(Tsl2561TimingRegisterTest, ValueInitialization)
{
		Tsl2561TimingRegister reg1{true, false, DEFAULT_INTEGRATION_TIME};

		EXPECT_TRUE(reg1.IsLowGain());
		EXPECT_FALSE(reg1.IsStartManualIntegrationCycle());
		EXPECT_EQ(reg1.GetIntegrationTime(), DEFAULT_INTEGRATION_TIME);

		Tsl2561TimingRegister reg2{false, true, DEFAULT_INTEGRATION_TIME};
		EXPECT_FALSE(reg2.IsLowGain());
		EXPECT_TRUE(reg2.IsStartManualIntegrationCycle());
		EXPECT_EQ(reg2.GetIntegrationTime(), DEFAULT_INTEGRATION_TIME);

		auto integrationTime = Tsl2561IntegrationTime::INTEGRATION_TIME_101_MS;
		Tsl2561TimingRegister reg3{false, false, integrationTime};
		EXPECT_FALSE(reg3.IsLowGain());
		EXPECT_FALSE(reg3.IsStartManualIntegrationCycle());
		EXPECT_EQ(reg3.GetIntegrationTime(), integrationTime);
}

TEST(Tsl2561TimingRegisterTest, Set)
{
		Tsl2561TimingRegister reg;
		ExpectDefaultInitialization(reg);
		reg.SetIsLowGain(true);
		EXPECT_TRUE(reg.IsLowGain());
		EXPECT_FALSE(reg.IsStartManualIntegrationCycle());
		EXPECT_EQ(reg.GetIntegrationTime(), DEFAULT_INTEGRATION_TIME);

		reg.SetIsLowGain(false);
		ExpectDefaultInitialization(reg);

		reg.SetStartManualIntegrationCycle(true);
		EXPECT_FALSE(reg.IsLowGain());
		EXPECT_TRUE(reg.IsStartManualIntegrationCycle());
		EXPECT_EQ(reg.GetIntegrationTime(), DEFAULT_INTEGRATION_TIME);

		reg.SetStartManualIntegrationCycle(false);
		ExpectDefaultInitialization(reg);

		auto integrationTime = Tsl2561IntegrationTime::INTEGRATION_TIME_402_MS;
		reg.SetIntegrationTime(integrationTime);
		EXPECT_EQ(reg.GetIntegrationTime(), integrationTime);

		reg.SetIntegrationTime(DEFAULT_INTEGRATION_TIME);
		ExpectDefaultInitialization(reg);
}
