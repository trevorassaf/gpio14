#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561IdRegister.h"

using I2c::Tsl2561IdRegister;

namespace
{
constexpr uint8_t PART_NUMBER_MASK = 0b11110000;
constexpr uint8_t REVISION_ID_MASK = 0b00001111;
constexpr size_t PART_NUMBER_BIT_SHIFT = 4;
constexpr size_t REVISION_ID_BIT_SHIFT = 0;
} // namespace

void ExpectDefaultInitialization(const Tsl2561IdRegister &reg)
{
		EXPECT_EQ(reg.Bits(), 0);
		EXPECT_EQ(reg.GetPartNumber(), 0);
		EXPECT_EQ(reg.GetRevisionId(), 0);
}

TEST(Tsl2561IdRegisterTest, DefaultInitialization)
{
		Tsl2561IdRegister reg;
		ExpectDefaultInitialization(reg);
}

TEST(Tsl2561IdRegisterTest, ValueInitialization)
{
		uint8_t partNumber = 4;
		uint8_t revisionId = 5;

		Tsl2561IdRegister reg{partNumber, revisionId};
		EXPECT_EQ(partNumber, reg.GetPartNumber());
		EXPECT_EQ(revisionId, reg.GetRevisionId());
}

TEST(Tsl2561IdRegisterTest, BitsInitialization)
{
		uint8_t bits = 0xFF;
		Tsl2561IdRegister reg{bits};
		EXPECT_EQ(reg.Bits(), bits);
}

TEST(Tsl2561IdRegisterTest, Set)
{
		uint8_t partNumber = 6;
		uint8_t revisionId = 7;

		Tsl2561IdRegister reg;
		reg.SetPartNumber(partNumber);
		EXPECT_EQ(reg.GetPartNumber(), partNumber);
		EXPECT_EQ(reg.GetRevisionId(), 0);

		reg.SetPartNumber(0);
		ExpectDefaultInitialization(reg);

		reg.SetRevisionId(revisionId);
		EXPECT_EQ(reg.GetPartNumber(), 0);
		EXPECT_EQ(reg.GetRevisionId(), revisionId);

		reg.SetRevisionId(0);
		ExpectDefaultInitialization(reg);
}

TEST(Tsl2561IdRegisterTest, Bits)
{
		uint8_t partNumber = 8;
		uint8_t revisionId = 9;

		Tsl2561IdRegister reg;
		EXPECT_EQ(reg.Bits(), 0);

		reg.SetPartNumber(partNumber);
		EXPECT_EQ(reg.Bits() >> PART_NUMBER_BIT_SHIFT, partNumber);
		EXPECT_FALSE(reg.Bits() & REVISION_ID_MASK);

		reg.SetPartNumber(0);
		EXPECT_EQ(reg.Bits(), 0);

		reg.SetRevisionId(revisionId);
		EXPECT_EQ(reg.Bits() & REVISION_ID_MASK, revisionId);
		EXPECT_FALSE(reg.Bits() & PART_NUMBER_MASK);

		reg.SetRevisionId(0);
		EXPECT_EQ(reg.Bits(), 0);
}
