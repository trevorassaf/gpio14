#pragma once

#include <cstdint>
#include <cstdlib>

#include "Utils/FdOpResult.h"

namespace Utils
{

class FdOps
{
public:
	virtual FdOpResult Open(const char *path, int *outFd) = 0;
	virtual FdOpResult Write(int fd, const uint8_t *buffer, size_t length) = 0;
	virtual FdOpResult Read(int fd, uint8_t *buffer, size_t length) = 0;
	virtual FdOpResult Close(int fd) = 0;
};

} // namespace Utils
