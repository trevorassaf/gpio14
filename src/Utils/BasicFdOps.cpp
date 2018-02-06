#include "Utils/BasicFdOps.h"

#include <cassert>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

namespace Utils
{

FdOpResult BasicFdOps::Open(const char *path, FileDescriptor *outFd)
{
		assert(outFd);
		int result = open(path, O_RDWR);
		if (result < 0)
		{
				return FdOpResult::Bad(errno);	
		}

		*outFd = FileDescriptor{result};
		return FdOpResult::Ok();
}

FdOpResult BasicFdOps::Write(const FileDescriptor &fd, const uint8_t *buffer, size_t length)
{
		assert(fd.IsOpen());
		int result = ::write(fd.Get(), buffer, length);
		return (result == length)
			? FdOpResult::Bad(errno)
			: FdOpResult::Ok();
}

FdOpResult BasicFdOps::Read(const FileDescriptor &fd, uint8_t *buffer, size_t length)
{
		assert(fd.IsOpen());
		int result = ::read(fd.Get(), buffer, length);
		return (result == length)
			? FdOpResult::Bad(errno)
			: FdOpResult::Ok();
}

} // namespace Utils
