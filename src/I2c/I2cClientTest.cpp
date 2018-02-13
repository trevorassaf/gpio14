#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/I2cClient.h"
#include "Utils/MockFdOps.h"

using I2c::I2cClient;
using Utils::Fd;
using Utils::MockFdOps;


class I2cClientTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
			m_failOps = MockFdOps::MakeFailOps();
	}

	virtual void TearDown()
	{
	}

public:
	std::unique_ptr<Fd> MakeFailFd()
	{
			return std::make_unique<Fd>(&m_failOps, I2cClientTest::SLAVE_ADDRESS);
	}

public:
	static constexpr size_t SLAVE_ADDRESS = 0x30;

public:
	MockFdOps m_failOps;
};

TEST(I2cClientTest, DefaultInitialization)
{
		I2cClient client;
		EXPECT_FALSE(client.HasSlave());
		EXPECT_FALSE(client.IsOpen());
}

TEST(I2cClientTest, SlaveAddressInitialization)
{
		I2cClient client{I2cClientTest::SLAVE_ADDRESS};
		EXPECT_TRUE(client.HasSlave());
		EXPECT_FALSE(client.IsOpen());
}

TEST(I2cClientTest, FdInitialization)
{
		I2cClient client{};
}
