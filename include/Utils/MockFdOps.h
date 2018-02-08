#pragma once

#include <cstdint>
#include <functional>

#include "Utils/FdOps.h"
#include "Utils/FdOpResult.h"

namespace Utils
{

typedef std::function<void(const char *path, Fd *outFd)> open_handler_t;
typedef std::function<void(const Fd &fd, const uint8_t *buffer, size_t length)> write_handler_t;
typedef std::function<void(const Fd &fd, uint8_t *buffer, size_t length)> read_handler_t;

class MockFdOps : public FdOps
{
public:
	MockFdOps(
			open_handler_t openHandler,
			write_handler_t writeHandler,
			read_handler_t readHandler)
	: m_openHandler{std::move(openHandler)},
		m_writeHandler{std::move(writeHandler)},
		m_readHandler{std::move(readHandler)} {}

	FdOpResult Open(const char *path, Fd *outFd)
	{
			m_openHandler(path, outFd);
			return FdOpResult::Ok();
	}

	FdOpResult Write(const Fd &fd, const uint8_t *buffer, size_t length)
	{
			m_writeHandler(fd, buffer, length);
			return FdOpResult::Ok();
	}

	FdOpResult Read(const Fd &fd, uint8_t *buffer, size_t length)
	{
			m_readHandler(fd, buffer, length);
			return FdOpResult::Ok();
	}

private:
	open_handler_t m_openHandler;
	write_handler_t m_writeHandler;
	read_handler_t m_readHandler;
};

} // namespace Utils
