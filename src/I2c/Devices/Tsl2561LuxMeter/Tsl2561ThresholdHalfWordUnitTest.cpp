#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561ThresholdHalfWord.h"

using I2c::Tsl2561ThresholdHalfWord;

TEST(Tsl2561ThresholdHalfWordTest, DefaultInitialization)
{
		Tsl2561ThresholdHalfWord halfWord;
		EXPECT_EQ(halfWord.GetHalfWord(), 0);
}

TEST(Tsl2561ThresholdHalfWordTest, ValueInitialization)
{
		uint16_t value = 0xffff;
		Tsl2561ThresholdHalfWord halfWord{value};
		EXPECT_EQ(halfWord.GetHalfWord(), value);
}

TEST(Tsl2561ThresholdHalfWordTest, Set)
{
		uint16_t value = 0xeeee;
		Tsl2561ThresholdHalfWord halfWord;
		halfWord.SetHalfWord(value);
		EXPECT_EQ(halfWord.GetHalfWord(), value);
		halfWord.SetHalfWord(0);
		EXPECT_EQ(halfWord.GetHalfWord(), 0);
}
