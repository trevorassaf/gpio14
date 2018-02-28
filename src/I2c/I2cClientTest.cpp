#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/MockI2cIoctlOps.h"
#include "I2c/I2cClient.h"
#include "Utils/MockFdOps.h"

#include <iostream>

using I2c::I2cClient;
using I2c::MockI2cIoctlOps;
using Utils::Fd;
using Utils::MockFdOps;

class I2cClientTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
			m_failOps = MockFdOps::MakeFailOps();
	}

	virtual void TearDown() {}

public:
	std::unique_ptr<Fd> MakeFailFd()
	{
			return std::make_unique<Fd>(&m_failOps, I2cClientTest::SLAVE_ADDRESS);
	}

	std::unique_ptr<Fd> MakeCloseCounterFd(size_t *closeCounter)
	{
			Utils::close_handler_t closeHandlerCounter = [=] (int fd) { ++(*closeCounter); };
			m_failOps.SetCloseHandler(closeHandlerCounter);
			return std::make_unique<Fd>(&m_failOps, I2cClientTest::FD);
	}

public:
	static constexpr size_t SLAVE_ADDRESS = 0x30;
	static constexpr size_t FD = 0x20;

public:
	MockI2cIoctlOps m_ioctlOps;
	MockFdOps m_failOps;
};

constexpr size_t I2cClientTest::SLAVE_ADDRESS;
constexpr size_t I2cClientTest::FD;

TEST_F(I2cClientTest, DefaultInitialization)
{
		I2cClient client{&m_ioctlOps};
		EXPECT_FALSE(client.HasSlave());
		EXPECT_FALSE(client.IsOpen());
}

TEST_F(I2cClientTest, SlaveAddressInitialization)
{
		I2cClient client{
			&m_ioctlOps,
			I2cClientTest::SLAVE_ADDRESS};
		EXPECT_TRUE(client.HasSlave());
		EXPECT_FALSE(client.IsOpen());
}

TEST_F(I2cClientTest, FdInitialization)
{
		I2cClient client{
			&m_ioctlOps,
			std::make_unique<Fd>(&m_failOps, I2cClientTest::FD)};
		EXPECT_FALSE(client.HasSlave());
		EXPECT_TRUE(client.IsOpen());
}

TEST_F(I2cClientTest, SlaveAndFdInitialization)
{
		m_ioctlOps.SetSlaveAddressLambda([&] (int fdNum, uint8_t slaveAddress)
		{
				EXPECT_EQ(fdNum, FD);
				EXPECT_EQ(slaveAddress, SLAVE_ADDRESS);
		});
		I2cClient client{
			&m_ioctlOps,
			SLAVE_ADDRESS,
			std::make_unique<Fd>(&m_failOps, I2cClientTest::FD)};
		EXPECT_TRUE(client.HasSlave());
		EXPECT_TRUE(client.IsOpen());
}

TEST_F(I2cClientTest, I2cClientRaiiDestructor)
{
		size_t numCloseCalls = 0;
		auto fd = MakeCloseCounterFd(&numCloseCalls);
		EXPECT_EQ(numCloseCalls, 0);

		{
				I2cClient client{&m_ioctlOps, std::move(fd)};
				EXPECT_TRUE(client.IsOpen());
		}

		EXPECT_EQ(numCloseCalls, 1);
}

TEST_F(I2cClientTest, I2cClientMoveConstructor)
{
		size_t closeCounter = 0;
		auto fd = MakeCloseCounterFd(&closeCounter);
		I2cClient client1{&m_ioctlOps, I2cClientTest::SLAVE_ADDRESS, std::move(fd)};
	
		EXPECT_EQ(closeCounter, 0);
		EXPECT_TRUE(client1.IsOpen());
		EXPECT_TRUE(client1.HasSlave());
		EXPECT_EQ(client1.GetSlave(), I2cClientTest::SLAVE_ADDRESS);

		I2cClient client2{&m_ioctlOps};
		EXPECT_FALSE(client2.IsOpen());
		EXPECT_FALSE(client2.HasSlave());

		client2 = std::move(client1);
		EXPECT_EQ(closeCounter, 0);
		EXPECT_TRUE(client2.IsOpen());
		EXPECT_TRUE(client2.HasSlave());
		EXPECT_EQ(client2.GetSlave(), I2cClientTest::SLAVE_ADDRESS);
}

TEST_F(I2cClientTest, I2cSetSlave)
{
		auto fd = MakeFailFd();
		int failFdNum = fd->Get();
		uint8_t slaveAddress2 = I2cClientTest::SLAVE_ADDRESS + 1;
		m_ioctlOps.SetSlaveAddressLambda([&] (int fdNum, uint8_t slaveAddress)
		{
				EXPECT_EQ(fdNum, failFdNum);
				EXPECT_EQ(slaveAddress, I2cClientTest::SLAVE_ADDRESS);
		});

		I2cClient client{&m_ioctlOps, I2cClientTest::SLAVE_ADDRESS, std::move(fd)};
		EXPECT_TRUE(client.HasSlave());
		EXPECT_EQ(client.GetSlave(), I2cClientTest::SLAVE_ADDRESS);

		m_ioctlOps.SetSlaveAddressLambda([&] (int fdNum, uint8_t slaveAddress)
		{
				EXPECT_EQ(fdNum, failFdNum);
				EXPECT_EQ(slaveAddress, slaveAddress2);
		});
		client.SetSlave(slaveAddress2);
		EXPECT_TRUE(client.HasSlave());
		EXPECT_EQ(client.GetSlave(), slaveAddress2);
}

TEST_F(I2cClientTest, I2cClose)
{
		size_t closeCounter = 0;
		auto fd = MakeCloseCounterFd(&closeCounter);
		I2cClient client{&m_ioctlOps, I2cClientTest::SLAVE_ADDRESS, std::move(fd)};

		EXPECT_EQ(closeCounter, 0);
		client.Close();
		EXPECT_EQ(closeCounter, 1);
}

TEST_F(I2cClientTest, I2cWrite)
{
		auto fd = MakeFailFd();
		int expectedFdNum = fd->Get();

		const char *buf = "writewritewrite";
		size_t bufLen = strlen(buf);
		size_t numWriteExecutions = 0;

		m_failOps.SetWriteHandler([=, &numWriteExecutions] (int fdNum, const uint8_t *buffer, size_t length)
		{
				EXPECT_EQ(expectedFdNum, fdNum);
				EXPECT_STREQ(buf, (const char *)buffer);
				EXPECT_EQ(bufLen, length);
				++numWriteExecutions;
		});

		I2cClient client{&m_ioctlOps, std::move(fd)};
		client.SetSlave(SLAVE_ADDRESS);
		EXPECT_EQ(numWriteExecutions, 0);

		client.Write((const uint8_t *)buf, bufLen);
		EXPECT_EQ(numWriteExecutions, 1);
}

TEST_F(I2cClientTest, I2cRead)
{
		auto fd = MakeFailFd();
		int expectedFdNum = fd->Get();

		const char *readString = "readreadread";
		size_t readStringLength = strlen(readString) + 1;
		char buf[256];
		size_t numReadExecutions = 0;

		m_failOps.SetReadHandler([=, &numReadExecutions] (int fdNum, uint8_t *buffer, size_t length)
		{
				EXPECT_NE(buffer, nullptr);
				EXPECT_EQ(expectedFdNum, fdNum);
				EXPECT_EQ(readStringLength, length);
				++numReadExecutions;
				memcpy((void *)buffer, readString, readStringLength);
		});

		I2cClient client{&m_ioctlOps, std::move(fd)};
		client.SetSlave(SLAVE_ADDRESS);
		EXPECT_EQ(numReadExecutions, 0);

		client.Read((uint8_t *)buf, readStringLength);
		EXPECT_STREQ(buf, (const char *)readString);
}
