#include "Utils/MockFdOps.h"

#include "gtest/gtest.h"

namespace Utils
{

open_handler_t MockFdOps::openHandlerFail = [] (const char *path, int *outFd)
{
		FAIL();
};

write_handler_t MockFdOps::writeHandlerFail = [] (int fd, const uint8_t *buffer, size_t length)
{
		FAIL();
};

read_handler_t MockFdOps::readHandlerFail = [] (int fd, uint8_t *buffer, size_t length)
{
		FAIL();
};

close_handler_t MockFdOps::closeHandlerFail = [] (int fd) { FAIL(); };

MockFdOps MockFdOps::MakeFailOps()
{
		MockFdOps ops;
		ops.SetOpenHandler(openHandlerFail);
		ops.SetWriteHandler(writeHandlerFail);
		ops.SetReadHandler(readHandlerFail);
		return ops;
}

MockFdOps::MockFdOps()
	: m_openHandler{},
		m_writeHandler{},
		m_readHandler{},
		m_closeHandler{} {}

MockFdOps::MockFdOps(
			open_handler_t openHandler,
			write_handler_t writeHandler,
			read_handler_t readHandler,
			close_handler_t closeHandler)
	: m_openHandler{std::move(openHandler)},
		m_writeHandler{std::move(writeHandler)},
		m_readHandler{std::move(readHandler)},
	  m_closeHandler{std::move(closeHandler)}	{}

void MockFdOps::SetOpenHandler(open_handler_t open) { m_openHandler = std::move(open); }
void MockFdOps::SetWriteHandler(write_handler_t write) { m_writeHandler = std::move(write); }
void MockFdOps::SetReadHandler(read_handler_t read) { m_readHandler = std::move(read); }
void MockFdOps::SetCloseHandler(close_handler_t close) { m_closeHandler = std::move(close); }

FdOpResult MockFdOps::Open(const char *path, int *outFd)
{
		if (m_openHandler)
		{
			m_openHandler(path, outFd);
		}
		return FdOpResult::Ok();
}

FdOpResult MockFdOps::Write(int fd, const uint8_t *buffer, size_t length)
{
		if (m_writeHandler)
		{
			m_writeHandler(fd, buffer, length);
		}
		return FdOpResult::Ok();
}

FdOpResult MockFdOps::Read(int fd, uint8_t *buffer, size_t length)
{
		if (m_readHandler)
		{
			m_readHandler(fd, buffer, length);
		}
		return FdOpResult::Ok();
}

FdOpResult MockFdOps::Close(int fd)
{
		if (m_closeHandler)
		{
			m_closeHandler(fd);
		}
		return FdOpResult::Ok();
}

} // namespace Utils
