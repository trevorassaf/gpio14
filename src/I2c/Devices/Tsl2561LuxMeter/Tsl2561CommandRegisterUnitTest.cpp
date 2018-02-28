#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561Address.h"
#include "I2c/Devices/Tsl2561LuxMeter/Tsl2561CommandRegister.h"

using I2c::Tsl2561Address;
using I2c::Tsl2561CommandRegister;

namespace
{
constexpr uint8_t COMMAND_REGISTER_MASK_AND_VALUE = (1 << 7);
constexpr uint8_t CLEAR_INTERRUPT_MASK_AND_VALUE = (1 << 6);
constexpr uint8_t WORD_PROTOCOL_MASK_AND_VALUE = (1 << 5);
constexpr uint8_t BLOCK_PROTOCOL_MASK_AND_VALUE = (1 << 4);
constexpr uint8_t ADDRESS_MASK = 0b00001111;
} // namespace

void ExpectDefaultRegister(const Tsl2561CommandRegister &reg)
{
		EXPECT_FALSE(reg.IsClearInterrupt());
		EXPECT_FALSE(reg.IsWordProtocol());
		EXPECT_FALSE(reg.IsBlockProtocol());

		uint8_t bits = static_cast<uint8_t>(reg.Bits());
		EXPECT_TRUE(bits & COMMAND_REGISTER_MASK_AND_VALUE);
		EXPECT_FALSE(bits & CLEAR_INTERRUPT_MASK_AND_VALUE);
		EXPECT_FALSE(bits & WORD_PROTOCOL_MASK_AND_VALUE);
		EXPECT_FALSE(bits & BLOCK_PROTOCOL_MASK_AND_VALUE);
}

TEST(Tsl2561CommandRegisterTest, DefaultInitialization)
{
		Tsl2561CommandRegister reg;
		ExpectDefaultRegister(reg);
}

TEST(Tsl2561CommandRegisterTest, ValueInitialization)
{
		Tsl2561CommandRegister clearInterruptTest{
			true, false, false, Tsl2561Address::CONTROL};
		EXPECT_TRUE(clearInterruptTest.IsClearInterrupt());
		EXPECT_FALSE(clearInterruptTest.IsWordProtocol());
		EXPECT_FALSE(clearInterruptTest.IsBlockProtocol());
		EXPECT_EQ(clearInterruptTest.GetAddress(), Tsl2561Address::CONTROL);

		Tsl2561CommandRegister wordProtocolTest{
			false, true, false, Tsl2561Address::TIMING};
		EXPECT_FALSE(wordProtocolTest.IsClearInterrupt());
		EXPECT_TRUE(wordProtocolTest.IsWordProtocol());
		EXPECT_FALSE(wordProtocolTest.IsBlockProtocol());
		EXPECT_EQ(wordProtocolTest.GetAddress(), Tsl2561Address::TIMING);

		Tsl2561CommandRegister blockProtocolTest{
			false, false, true, Tsl2561Address::INTERRUPT};
		EXPECT_FALSE(blockProtocolTest.IsClearInterrupt());
		EXPECT_FALSE(blockProtocolTest.IsWordProtocol());
		EXPECT_TRUE(blockProtocolTest.IsBlockProtocol());
		EXPECT_EQ(blockProtocolTest.GetAddress(), Tsl2561Address::INTERRUPT);

		Tsl2561CommandRegister addressTest{
			false, false, false, Tsl2561Address::ID};
		EXPECT_FALSE(addressTest.IsClearInterrupt());
		EXPECT_FALSE(addressTest.IsWordProtocol());
		EXPECT_FALSE(addressTest.IsBlockProtocol());
		EXPECT_EQ(addressTest.GetAddress(), Tsl2561Address::ID);
}

TEST(Tsl2561CommandRegisterTest, AddressInitialization)
{
		Tsl2561CommandRegister controlAddressTest{Tsl2561Address::CONTROL};
		EXPECT_EQ(controlAddressTest, Tsl2561Address::CONTROL);

		Tsl2561CommandRegister data0highAddressTest{Tsl2561Address::DATA0HIGH};
		EXPECT_EQ(data0highAddressTest, Tsl2561Address::DATA0HIGH);
}

TEST(Tsl2561CommandRegisterTest, EqualityComparisonOperator)
{
		Tsl2561CommandRegister reg1{true, false, true, Tsl2561Address::ID};
		Tsl2561CommandRegister reg2 = reg1;
		EXPECT_EQ(reg1, reg2);
}

TEST(Tsl2561CommandRegisterTest, Set)
{
		Tsl2561CommandRegister reg;
		Tsl2561Address address = reg.GetAddress();
		
		reg.SetClearInterrupt(true);
		EXPECT_TRUE(reg.IsClearInterrupt());
		EXPECT_FALSE(reg.IsWordProtocol());
		EXPECT_FALSE(reg.IsBlockProtocol());
		EXPECT_EQ(reg.GetAddress(), address);

		reg.SetClearInterrupt(false);
		ExpectDefaultRegister(reg);
		EXPECT_EQ(reg.GetAddress(), address);

		reg.SetWordProtocol(true);
		EXPECT_FALSE(reg.IsClearInterrupt());
		EXPECT_TRUE(reg.IsWordProtocol());
		EXPECT_FALSE(reg.IsBlockProtocol());
		EXPECT_EQ(reg.GetAddress(), address);

		reg.SetWordProtocol(false);
		ExpectDefaultRegister(reg);
		EXPECT_EQ(reg.GetAddress(), address);

		reg.SetBlockProtocol(true);
		EXPECT_FALSE(reg.IsClearInterrupt());
		EXPECT_FALSE(reg.IsWordProtocol());
		EXPECT_TRUE(reg.IsBlockProtocol());
		EXPECT_EQ(reg.GetAddress(), address);

		reg.SetBlockProtocol(false);
		ExpectDefaultRegister(reg);
		EXPECT_EQ(reg.GetAddress(), address);

		reg.SetAddress(Tsl2561Address::THRESHHIGHHIGH);
		EXPECT_FALSE(reg.IsClearInterrupt());
		EXPECT_FALSE(reg.IsWordProtocol());
		EXPECT_FALSE(reg.IsBlockProtocol());
		EXPECT_EQ(reg.GetAddress(), Tsl2561Address::THRESHHIGHHIGH);

		reg.SetAddress(address);
		EXPECT_FALSE(reg.IsClearInterrupt());
		EXPECT_FALSE(reg.IsWordProtocol());
		EXPECT_FALSE(reg.IsBlockProtocol());
		EXPECT_EQ(reg.GetAddress(), address);
}

TEST(Tsl2561CommandRegisterTest, Bits)
{
		Tsl2561CommandRegister reg;
		uint8_t address = static_cast<uint8_t>(reg.GetAddress());

		uint8_t defaultBits = reg.Bits();
		EXPECT_TRUE(defaultBits & COMMAND_REGISTER_MASK_AND_VALUE);
		EXPECT_FALSE(defaultBits & CLEAR_INTERRUPT_MASK_AND_VALUE);
		EXPECT_FALSE(defaultBits & WORD_PROTOCOL_MASK_AND_VALUE);
		EXPECT_FALSE(defaultBits & BLOCK_PROTOCOL_MASK_AND_VALUE);
		EXPECT_EQ(defaultBits & ADDRESS_MASK, address);

		reg.SetClearInterrupt(true);
		uint8_t clearInterruptBits = reg.Bits();
		EXPECT_TRUE(clearInterruptBits & COMMAND_REGISTER_MASK_AND_VALUE);
		EXPECT_TRUE(clearInterruptBits & CLEAR_INTERRUPT_MASK_AND_VALUE);
		EXPECT_FALSE(clearInterruptBits & WORD_PROTOCOL_MASK_AND_VALUE);
		EXPECT_FALSE(clearInterruptBits & BLOCK_PROTOCOL_MASK_AND_VALUE);
		EXPECT_EQ(clearInterruptBits & ADDRESS_MASK, address);

		reg.SetClearInterrupt(false);
		ExpectDefaultRegister(reg);
		EXPECT_EQ(clearInterruptBits & ADDRESS_MASK, address);

		reg.SetWordProtocol(true);
		uint8_t wordProtocolBits = reg.Bits();
		EXPECT_TRUE(wordProtocolBits & COMMAND_REGISTER_MASK_AND_VALUE);
		EXPECT_FALSE(wordProtocolBits & CLEAR_INTERRUPT_MASK_AND_VALUE);
		EXPECT_TRUE(wordProtocolBits & WORD_PROTOCOL_MASK_AND_VALUE);
		EXPECT_FALSE(wordProtocolBits & BLOCK_PROTOCOL_MASK_AND_VALUE);
		EXPECT_EQ(wordProtocolBits & ADDRESS_MASK, address);

		reg.SetWordProtocol(false);
		ExpectDefaultRegister(reg);
		EXPECT_EQ(clearInterruptBits & ADDRESS_MASK, address);

		reg.SetBlockProtocol(true);
		uint8_t blockProtocolBits = reg.Bits();
		EXPECT_TRUE(blockProtocolBits & COMMAND_REGISTER_MASK_AND_VALUE);
		EXPECT_FALSE(blockProtocolBits & CLEAR_INTERRUPT_MASK_AND_VALUE);
		EXPECT_FALSE(blockProtocolBits & WORD_PROTOCOL_MASK_AND_VALUE);
		EXPECT_TRUE(blockProtocolBits & BLOCK_PROTOCOL_MASK_AND_VALUE);
		EXPECT_EQ(blockProtocolBits & ADDRESS_MASK, address);

		reg.SetBlockProtocol(false);
		ExpectDefaultRegister(reg);
		EXPECT_EQ(clearInterruptBits & ADDRESS_MASK, address);

		reg.SetAddress(Tsl2561Address::DATA1LOW);
		ExpectDefaultRegister(reg);
		uint8_t data1LowAddressBits = static_cast<uint8_t>(reg.Bits());
		EXPECT_EQ(data1LowAddressBits & ADDRESS_MASK,
			 	static_cast<uint8_t>(Tsl2561Address::DATA1LOW));

		reg.SetAddress(Tsl2561Address::DATA1HIGH);
		ExpectDefaultRegister(reg);
		uint8_t data1HighAddressBits = static_cast<uint8_t>(reg.Bits());
		EXPECT_EQ(data1HighAddressBits & ADDRESS_MASK,
				static_cast<uint8_t>(Tsl2561Address::DATA1HIGH));
}
