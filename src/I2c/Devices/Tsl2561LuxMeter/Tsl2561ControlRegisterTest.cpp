#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561ControlRegister.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561PowerControl.h"

using I2c::Tsl2561ControlRegister;
using I2c::Tsl2561PowerControl;

TEST(Tsl2561ControlRegisterTest, DefaultInitialization)
{
		Tsl2561ControlRegister reg;
		EXPECT_EQ(reg.GetPowerControl(), Tsl2561PowerControl::POWER_DOWN);
}

TEST(Tsl2561ControlRegisterTest, PowerControlInitialization)
{
		Tsl2561ControlRegister reg1;
		EXPECT_EQ(reg1.GetPowerControl(), Tsl2561PowerControl::POWER_DOWN);

		Tsl2561ControlRegister reg2{Tsl2561PowerControl::POWER_UP};
		EXPECT_EQ(reg2.GetPowerControl(), Tsl2561PowerControl::POWER_UP);
}

TEST(Tsl2561ControlRegisterTest, Set)
{
		Tsl2561ControlRegister reg;
		EXPECT_EQ(reg.GetPowerControl(), Tsl2561PowerControl::POWER_DOWN);

		reg.SetPowerControl(Tsl2561PowerControl::POWER_UP);
		EXPECT_EQ(reg.GetPowerControl(), Tsl2561PowerControl::POWER_UP);

		reg.SetPowerControl(Tsl2561PowerControl::POWER_DOWN);
		EXPECT_EQ(reg.GetPowerControl(), Tsl2561PowerControl::POWER_DOWN);
}

TEST(Tsl2561ControlRegisterTest, IsPoweredOn)
{
		Tsl2561ControlRegister reg;
		EXPECT_FALSE(reg.IsPoweredOn());

		reg.SetPowerControl(Tsl2561PowerControl::POWER_UP);
		EXPECT_TRUE(reg.IsPoweredOn());
}

TEST(Tsl2561ControlRegisterTest, Bits)
{
		Tsl2561ControlRegister reg;
		EXPECT_EQ(reg.Bits(), static_cast<uint8_t>(Tsl2561PowerControl::POWER_DOWN));
		reg.SetPowerControl(Tsl2561PowerControl::POWER_UP);
		EXPECT_EQ(reg.Bits(), static_cast<uint8_t>(Tsl2561PowerControl::POWER_UP));
}
