#pragma once

#include <cstdlib>
#include <unistd.h>

namespace Utils
{

class FileDescriptor
{
public:
	FileDescriptor() : m_fd{EMPTY_FILE_DESCRIPTOR} {}

	FileDescriptor(int fd) : m_fd{fd} {}

	~FileDescriptor()
	{
			Reset();
	}

	int Get() const { return m_fd; }

	void Reset()
	{
			if (m_fd)
			{
				::close(m_fd);
				m_fd = EMPTY_FILE_DESCRIPTOR;
			}
	}

	FileDescriptor(FileDescriptor &&other)
	{
			m_fd = other.m_fd;
			other.m_fd = EMPTY_FILE_DESCRIPTOR;
	}

	FileDescriptor& operator=(FileDescriptor &&other)
	{
			Reset();
			m_fd = other.m_fd;
			other.m_fd = EMPTY_FILE_DESCRIPTOR;
	}

	bool IsOpen() const
	{
			return m_fd != EMPTY_FILE_DESCRIPTOR;
	}

private:
	FileDescriptor(const FileDescriptor &other) = delete;
	FileDescriptor& operator=(const FileDescriptor &other) = delete;

private:
	static constexpr int EMPTY_FILE_DESCRIPTOR = -1;

private:
	int m_fd;
};

} // namespace Utils
