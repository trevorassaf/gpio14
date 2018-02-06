#pragma once

#include <cstdint>
#include <cstdlib>

#include "Utils/FdOpResult.h"
#include "Utils/FileDescriptor.h"

namespace Utils
{

class FdOps
{
public:
	virtual FdOpResult Open(const char *path, FileDescriptor *outFd) = 0;
	virtual FdOpResult Write(const FileDescriptor &fd, const uint8_t *buffer, size_t length) = 0;
	virtual FdOpResult Read(const FileDescriptor &fd, uint8_t *buffer, size_t length) = 0;
};

} // namespace Utils
