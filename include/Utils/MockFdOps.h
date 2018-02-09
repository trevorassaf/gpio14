#pragma once

#include <cstdint>
#include <functional>

#include "Utils/FdOps.h"
#include "Utils/FdOpResult.h"

namespace Utils
{

typedef std::function<void(const char *path, int *outFd)> open_handler_t;
typedef std::function<void(int fd, const uint8_t *buffer, size_t length)> write_handler_t;
typedef std::function<void(int fd, uint8_t *buffer, size_t length)> read_handler_t;
typedef std::function<void(int)> close_handler_t;

open_handler_t openHandlerFail = [] (const char *path, int *outFd)
{
		FAIL();
};

write_handler_t writeHandlerFail = [] (int fd, const uint8_t *buffer, size_t length)
{
		FAIL();
};

read_handler_t readHandlerFail = [] (int fd, uint8_t *buffer, size_t length)
{
		FAIL();
};

close_handler_t closeHandlerFail = [] (int fd) { FAIL(); };

class MockFdOps : public FdOps
{
public:
	static MockFdOps MakeFailOps()
	{
			MockFdOps ops;
			ops.SetOpenHandler(openHandlerFail);
			ops.SetWriteHandler(writeHandlerFail);
			ops.SetReadHandler(readHandlerFail);
			return ops;
	}

	MockFdOps()
		: m_openHandler{},
			m_writeHandler{},
			m_readHandler{},
			m_closeHandler{} {}

	MockFdOps(
			open_handler_t openHandler,
			write_handler_t writeHandler,
			read_handler_t readHandler,
			close_handler_t closeHandler)
	: m_openHandler{std::move(openHandler)},
		m_writeHandler{std::move(writeHandler)},
		m_readHandler{std::move(readHandler)},
	  m_closeHandler{std::move(closeHandler)}	{}

	void SetOpenHandler(open_handler_t open) { m_openHandler = std::move(open); }
	void SetWriteHandler(write_handler_t write) { m_writeHandler = std::move(write); }
	void SetReadHandler(read_handler_t read) { m_readHandler = std::move(read); }
	void SetCloseHandler(close_handler_t close) { m_closeHandler = std::move(close); }

	FdOpResult Open(const char *path, int *outFd) override
	{
			if (m_openHandler)
			{
				m_openHandler(path, outFd);
			}
			return FdOpResult::Ok();
	}

	FdOpResult Write(int fd, const uint8_t *buffer, size_t length) override
	{
			if (m_writeHandler)
			{
				m_writeHandler(fd, buffer, length);
			}
			return FdOpResult::Ok();
	}

	FdOpResult Read(int fd, uint8_t *buffer, size_t length) override
	{
			if (m_readHandler)
			{
				m_readHandler(fd, buffer, length);
			}
			return FdOpResult::Ok();
	}

	FdOpResult Close(int fd) override
	{
			if (m_closeHandler)
			{
				m_closeHandler(fd);
			}
			return FdOpResult::Ok();
	}

private:
	open_handler_t m_openHandler;
	write_handler_t m_writeHandler;
	read_handler_t m_readHandler;
	close_handler_t m_closeHandler;
};

} // namespace Utils
