#include "gtest/gtest.h"

#include <cstdint>

#include "I2c/I2cClient.h"
#include "Utils/MockFdOps.h"

/*
using I2c::I2cClient;
using Utils::FileDescriptor;
using Utils::MockFdOps;
using Utils::open_handler_t;
using Utils::write_handler_t;
using Utils::read_handler_t;

namespace
{

open_handler_t openHandlerFail =
	[] (const char *path, FileDescriptor *outFd) { FAIL(); };

write_handler_t writeHandlerFail =
	[] (const FileDescriptor &fd, const uint8_t *buffer, size_t length) { FAIL(); };

read_handler_t readHandlerFail =
	[] (const FileDescriptor &fd, uint8_t *buffer, size_t length) { FAIL(); };

} // namespace

constexpr const char *testPath = "testPath";

constexpr int FD = 10;

open_handler_t openHandler =
	[] (const char *path, FileDescriptor *outFd)
	{
			ASSERT_STREQ(testPath, path);
	};

TEST(I2cClientTest, TestOpen)
{
		MockFdOps ops{openHandler, writeHandlerFail, readHandlerFail};
		I2cClient client{&ops, testPath};
}

TEST(I2cClientTest, TestWrite)
{
		write_handler_t writeHandler =
			[] (const FileDescriptor &fd, const uint8_t *buffer, size_t length)
			{
					
			};
}
*/
