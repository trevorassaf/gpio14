#pragma once

#include <cstdint>
#include <functional>

#include "gtest/gtest.h"

#include "Utils/FdOps.h"
#include "Utils/FdOpResult.h"

namespace Utils
{

typedef std::function<void(const char *path, int *outFd)> open_handler_t;
typedef std::function<void(int fd, const uint8_t *buffer, size_t length)> write_handler_t;
typedef std::function<void(int fd, uint8_t *buffer, size_t length)> read_handler_t;
typedef std::function<void(int)> close_handler_t;

class MockFdOps : public FdOps
{
public:
	static open_handler_t openHandlerFail;
	static write_handler_t writeHandlerFail;
	static read_handler_t readHandlerFail;
	static close_handler_t closeHandlerFail;

public:
	static MockFdOps MakeFailOps();

public:
	MockFdOps();

	MockFdOps(
			open_handler_t openHandler,
			write_handler_t writeHandler,
			read_handler_t readHandler,
			close_handler_t closeHandler);

	void SetOpenHandler(open_handler_t open);
	void SetWriteHandler(write_handler_t write);
	void SetReadHandler(read_handler_t read);
	void SetCloseHandler(close_handler_t close);

	FdOpResult Open(const char *path, int *outFd) override;
	FdOpResult Write(int fd, const uint8_t *buffer, size_t length) override;
	FdOpResult Read(int fd, uint8_t *buffer, size_t length) override;
	FdOpResult Close(int fd) override;

private:
	open_handler_t m_openHandler;
	write_handler_t m_writeHandler;
	read_handler_t m_readHandler;
	close_handler_t m_closeHandler;
};

} // namespace Utils
