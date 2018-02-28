#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561InterruptControlMode.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561InterruptControlRegister.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561InterruptPersistenceLevel.h"

using I2c::Tsl2561InterruptControlMode;
using I2c::Tsl2561InterruptControlRegister;
using I2c::Tsl2561InterruptPersistenceLevel;

namespace
{
constexpr uint8_t CONTROL_MODE_MASK          = 0b00110000;
constexpr uint8_t PERSISTENCE_LEVEL_MASK     = 0b00001111;
constexpr size_t CONTROL_MODE_BIT_SHIFT      = 4;
constexpr size_t PERSISTENCE_LEVEL_BIT_SHIFT = 0;
} // namespace

void ExpectDefaultInitialization(const Tsl2561InterruptControlRegister &reg)
{
		EXPECT_EQ(reg.Bits(), 0);
		EXPECT_EQ(reg.GetControlMode(), Tsl2561InterruptControlMode::INTERRUPT_OUTPUT_DISABLED);
		EXPECT_EQ(reg.GetPersistenceLevel(), Tsl2561InterruptPersistenceLevel::EVERY_CYCLE);
}

TEST(Tsl2561InterruptControlRegisterTest, DefaultInitialization)
{
		Tsl2561InterruptControlRegister reg;
		ExpectDefaultInitialization(reg);
}

TEST(Tsl2561InterruptControlRegisterTest, ValueInitialization)
{
		auto controlMode = Tsl2561InterruptControlMode::TEST_MODE;
		auto persistenceLevel = Tsl2561InterruptPersistenceLevel::EVERY_2_CYCLES_OUT_OF_RANGE;

		Tsl2561InterruptControlRegister reg{controlMode, persistenceLevel};
		EXPECT_EQ(reg.GetControlMode(), controlMode);
		EXPECT_EQ(reg.GetPersistenceLevel(), persistenceLevel);
}

TEST(Tsl2561InterruptControlRegisterTest, BitsInitialization)
{
		uint8_t bits = 0xff;
		Tsl2561InterruptControlRegister reg{bits};
		EXPECT_EQ(reg.Bits(), bits);
}

TEST(Tsl2561InterruptControlRegisterTest, Set)
{
		Tsl2561InterruptControlRegister reg;
		ExpectDefaultInitialization(reg);

		auto controlMode = Tsl2561InterruptControlMode::SMB_ALERT_COMPLIANT;
		reg.SetControlMode(controlMode);

		EXPECT_EQ(reg.GetControlMode(), controlMode);
		EXPECT_EQ(reg.GetPersistenceLevel(), Tsl2561InterruptPersistenceLevel::EVERY_CYCLE);

		reg.SetControlMode(Tsl2561InterruptControlMode::INTERRUPT_OUTPUT_DISABLED);
		ExpectDefaultInitialization(reg);

		auto persistenceLevel = Tsl2561InterruptPersistenceLevel::EVERY_CYCLE_OUT_OF_RANGE;
		reg.SetPersistenceLevel(persistenceLevel);
		EXPECT_EQ(reg.GetControlMode(), Tsl2561InterruptControlMode::INTERRUPT_OUTPUT_DISABLED);
		EXPECT_EQ(reg.GetPersistenceLevel(), persistenceLevel);

		reg.SetPersistenceLevel(Tsl2561InterruptPersistenceLevel::EVERY_CYCLE);
		ExpectDefaultInitialization(reg);
}

TEST(Tsl2561InterruptControlRegisterTest, Bits)
{
		Tsl2561InterruptControlRegister reg;

		auto controlMode = Tsl2561InterruptControlMode::LEVEL_INTERRUPT;
		reg.SetControlMode(controlMode);

		EXPECT_EQ(reg.Bits() >> CONTROL_MODE_BIT_SHIFT, static_cast<uint8_t>(controlMode));
		EXPECT_FALSE(reg.Bits() & PERSISTENCE_LEVEL_MASK);

		reg.SetControlMode(Tsl2561InterruptControlMode::INTERRUPT_OUTPUT_DISABLED);
		ExpectDefaultInitialization(reg);

		auto persistenceLevel = Tsl2561InterruptPersistenceLevel::EVERY_2_CYCLES_OUT_OF_RANGE;
		reg.SetPersistenceLevel(persistenceLevel);
		EXPECT_FALSE(reg.Bits() & CONTROL_MODE_MASK);
		EXPECT_EQ(reg.Bits() >> PERSISTENCE_LEVEL_BIT_SHIFT, static_cast<uint8_t>(persistenceLevel));

		reg.SetPersistenceLevel(Tsl2561InterruptPersistenceLevel::EVERY_CYCLE);
		ExpectDefaultInitialization(reg);
}
