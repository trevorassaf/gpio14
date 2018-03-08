#include "gtest/gtest.h"

#include <cstdint>

#include "Utils/Fd.h"
#include "Utils/MockFdOps.h"

using Utils::open_handler_t;
using Utils::write_handler_t;
using Utils::read_handler_t;
using Utils::close_handler_t;
using Utils::Fd;
using Utils::MockFdOps;

constexpr int fdNum = 0xff;

class FdTest : public ::testing::Test
{
protected:
	virtual void SetUp()
	{
			m_numCloseOps = 0;
			m_countingCloseFailOps = MockFdOps::MakeFailOps();
			m_countingCloseFailOps.SetCloseHandler([=] (int fd) { ++m_numCloseOps; });
	}

	virtual void TearDown()
	{
	}

public:
	MockFdOps m_countingCloseFailOps;

protected:
	int m_numCloseOps = 0;
};

TEST_F(FdTest, DefaultInitialization)
{
		Fd fd;
		EXPECT_FALSE(fd.IsOpen());
}

TEST_F(FdTest, OpsInitialization)
{
		auto failOps = MockFdOps::MakeFailOps();
		Fd fd{&failOps};
		EXPECT_FALSE(fd.IsOpen());
}

TEST_F(FdTest, OpsAndFdInitialization)
{
		auto failOps = MockFdOps::MakeFailOps();
		Fd fd{&failOps, fdNum};
		EXPECT_TRUE(fd.IsOpen());
}

TEST_F(FdTest, CloseOnDestruct)
{
		{
				Fd fd{&m_countingCloseFailOps, fdNum};
		}

		EXPECT_EQ(m_numCloseOps, 1);
}

TEST_F(FdTest, MoveConstructor)
{
		{
			Fd fd1{&m_countingCloseFailOps, fdNum};
			EXPECT_TRUE(fd1.IsOpen());
			EXPECT_EQ(fd1.Get(), fdNum);
			
			Fd fd2{std::move(fd1)};
			EXPECT_FALSE(fd1.IsOpen());
			EXPECT_TRUE(fd2.IsOpen());
			EXPECT_EQ(fd2.Get(), fdNum);
	 }

		EXPECT_EQ(m_numCloseOps, 1);
}

TEST_F(FdTest, MoveAssignment)
{
		int fdNum1 = 0x1;
		int fdNum2 = 0x2;

		{
			Fd fd1{&m_countingCloseFailOps, fdNum1};
			Fd fd2{&m_countingCloseFailOps, fdNum2};

			EXPECT_TRUE(fd1.IsOpen());
			EXPECT_EQ(fd1.Get(), fdNum1);

			EXPECT_TRUE(fd2.IsOpen());
			EXPECT_EQ(fd2.Get(), fdNum2);
		
			fd2 = std::move(fd1);

			EXPECT_EQ(m_numCloseOps, 1);

			EXPECT_FALSE(fd1.IsOpen());
			EXPECT_TRUE(fd2.IsOpen());
			EXPECT_EQ(fd2.Get(), fdNum1);
	 }

	 EXPECT_EQ(m_numCloseOps, 2);
}

TEST_F(FdTest, Write)
{
		const char *testBuffer = "test";
		size_t testLength = sizeof(testBuffer);

		write_handler_t writeHandler = [=] (int fd, const uint8_t *buffer, size_t length)
		{
				EXPECT_EQ(fdNum, fd);
				EXPECT_STREQ(testBuffer, (const char *)buffer);
				EXPECT_EQ(testLength, length);
		};

		auto fdOps = MockFdOps::MakeFailOps();
		fdOps.SetWriteHandler(writeHandler);

		Fd fd{&fdOps, fdNum};
		fd.Write((const uint8_t *)testBuffer, testLength);
}

TEST_F(FdTest, Read)
{
		const char *testBuffer = "test";
		constexpr size_t testLength = sizeof(testBuffer) + 1;

		char inputTestBuffer[testLength];

		read_handler_t readHandler = [=] (int fd, uint8_t *buffer, size_t length)
		{
				EXPECT_EQ(fdNum, fd);
				EXPECT_EQ(testLength, length);

				::memcpy(buffer, testBuffer, length);
		};

		auto fdOps = MockFdOps::MakeFailOps();
		fdOps.SetReadHandler(readHandler);

		Fd fd{&fdOps, fdNum};
		fd.Read((uint8_t *)inputTestBuffer, testLength);

		EXPECT_STREQ(testBuffer, inputTestBuffer);
}

TEST_F(FdTest, Close)
{
		auto fdOps = MockFdOps::MakeFailOps();
		Fd fd{&fdOps, fdNum};
		EXPECT_TRUE(fd.IsOpen());
		fd.Close();
		EXPECT_FALSE(fd.IsOpen());
}
