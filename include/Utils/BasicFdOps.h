#pragma once

#include <cstdint>
#include <cstdlib>

#include "Utils/FdOps.h"

namespace Utils
{

class BasicFdOps : public FdOps
{
public:
	FdOpResult Open(const char *path, int *outFd) override;
	FdOpResult Write(int fd, const uint8_t *buffer, size_t length) override;
	FdOpResult Read(int fd, uint8_t *buffer, size_t length) override;
	FdOpResult Close(int fd);
};

} // namespace Utils
