#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561AdcHalfWord.h"

constexpr uint16_t HALF_WORD_MAGIC_VALUE = 0XFFFF;

using I2c::Tsl2561AdcHalfWord;

TEST(Tsl2561AdcHalfWordTest, DefaultInitialization)
{
		Tsl2561AdcHalfWord halfWord;
		EXPECT_EQ(halfWord.GetHalfWord(), 0);
}

TEST(Tsl2561AdcHalfWordTest, Get)
{
		Tsl2561AdcHalfWord halfWord{HALF_WORD_MAGIC_VALUE};
		EXPECT_EQ(halfWord.GetHalfWord(), HALF_WORD_MAGIC_VALUE);
}

TEST(Tsl2561AdcHalfWordTest, Set)
{
		Tsl2561AdcHalfWord halfWord{};
		halfWord.SetHalfWord(HALF_WORD_MAGIC_VALUE);
		EXPECT_EQ(halfWord.GetHalfWord(), HALF_WORD_MAGIC_VALUE);
}
