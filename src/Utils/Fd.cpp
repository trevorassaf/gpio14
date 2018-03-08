#include "Utils/Fd.h"

#include <cassert>
#include <iostream>
#include <sstream>

#include "Utils/FdException.h"

namespace Utils
{

constexpr int Fd::EMPTY_FILE_DESCRIPTOR;

Fd::Fd() : Fd{nullptr} {}

Fd::Fd(FdOps *ops) : m_ops{ops}, m_fd{EMPTY_FILE_DESCRIPTOR} {}

Fd::Fd(FdOps *ops, int fd) : m_ops{ops}, m_fd{fd} {}

Fd::Fd(FdOps *ops, const char *fileName) : Fd{ops}
{
		auto result = m_ops->Open(fileName, &m_fd);
		if (!result.IsOk())
		{
			std::ostringstream ss;
			ss << "Failed to open file " << fileName;
			throw FdException{ss.str()};
		}
}

Fd::~Fd()
{
		Close();
}

int Fd::Get() const { return m_fd; }

FdOpResult Fd::Write(const uint8_t *buffer, size_t length)
{
		assert(IsOpen());
		return m_ops->Write(m_fd, buffer, length);
}

FdOpResult Fd::Read(uint8_t *buffer, size_t length)
{
		assert(IsOpen());
		return m_ops->Read(m_fd, buffer, length);
}

FdOpResult Fd::Close()
{
		if (!IsOpen())
		{
				return FdOpResult::Ok();
		}

		auto result = m_ops->Close(m_fd);
		m_fd = EMPTY_FILE_DESCRIPTOR;
		return result;
}

Fd::Fd(Fd &&other)
{
		m_ops = other.m_ops;
		other.m_ops = nullptr;

		m_fd = other.m_fd;
		other.m_fd = EMPTY_FILE_DESCRIPTOR;
}

Fd& Fd::operator=(Fd &&other)
{
		Close();

		m_ops = other.m_ops;
		other.m_ops = nullptr;
		m_fd = other.m_fd;
		other.m_fd = EMPTY_FILE_DESCRIPTOR;

		return *this;
}

bool Fd::IsOpen() const
{
		return m_fd != EMPTY_FILE_DESCRIPTOR;
}

} // namespace Utils
