#pragma once

#include <cstdint>
#include <cstdlib>

#include "Utils/FdOps.h"
#include "Utils/FileDescriptor.h"

namespace Utils
{

class BasicFdOps : public FdOps
{
public:
	FdOpResult Open(const char *path, FileDescriptor *outFd) override;
	FdOpResult Write(const FileDescriptor &fd, const uint8_t *buffer, size_t length) override;
	FdOpResult Read(const FileDescriptor &fd, uint8_t *buffer, size_t length) override;
};

} // namespace Utils
