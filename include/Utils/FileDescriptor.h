#pragma once

#include <cstdlib>
#include <unistd.h>

namespace Utils
{

class FileDescriptor
{
public:
	FileDescriptor();
	FileDescriptor(int fd);
	~FileDescriptor();

	FileDescriptor(FileDescriptor &&other);
	FileDescriptor& operator=(FileDescriptor &&other);

	int Get() const;
	void Reset();
	bool IsOpen() const;

private:
	FileDescriptor(const FileDescriptor &other) = delete;
	FileDescriptor& operator=(const FileDescriptor &other) = delete;

private:
	static constexpr int EMPTY_FILE_DESCRIPTOR = -1;

private:
	int m_fd;
};

} // namespace Utils
