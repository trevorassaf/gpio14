#include "Utils/FileDescriptor.h"

namespace Utils
{

constexpr int FileDescriptor::EMPTY_FILE_DESCRIPTOR;

FileDescriptor::FileDescriptor() : m_fd{EMPTY_FILE_DESCRIPTOR} {}

FileDescriptor::FileDescriptor(int fd) : m_fd{fd} {}

FileDescriptor::~FileDescriptor()
{
		Reset();
}

int FileDescriptor::Get() const { return m_fd; }

void FileDescriptor::Reset()
{
		if (m_fd)
		{
			::close(m_fd);
			m_fd = EMPTY_FILE_DESCRIPTOR;
		}
}

FileDescriptor::FileDescriptor(FileDescriptor &&other)
{
		m_fd = other.m_fd;
		other.m_fd = EMPTY_FILE_DESCRIPTOR;
}

FileDescriptor& FileDescriptor::operator=(FileDescriptor &&other)
{
		Reset();
		m_fd = other.m_fd;
		other.m_fd = EMPTY_FILE_DESCRIPTOR;
}

bool FileDescriptor::IsOpen() const
{
		return m_fd != EMPTY_FILE_DESCRIPTOR;
}

} // namespace Utils
