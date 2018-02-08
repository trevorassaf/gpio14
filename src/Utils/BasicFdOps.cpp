#include "Utils/BasicFdOps.h"

#include <cassert>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>

namespace Utils
{

FdOpResult BasicFdOps::Open(const char *path, int *outFd)
{
		assert(outFd);
		*outFd = open(path, O_RDWR);
		if (*outFd < 0)
		{
				return FdOpResult::Bad(errno);	
		}

		return FdOpResult::Ok();
}

FdOpResult BasicFdOps::Write(int fd, const uint8_t *buffer, size_t length)
{
		int result = ::write(fd, buffer, length);
		return (result == length)
			? FdOpResult::Bad(errno)
			: FdOpResult::Ok();
}

FdOpResult BasicFdOps::Read(int fd, uint8_t *buffer, size_t length)
{
		int result = ::read(fd, buffer, length);
		return (result == length)
			? FdOpResult::Bad(errno)
			: FdOpResult::Ok();
}

FdOpResult BasicFdOps::Close(int fd)
{
		return (::close(fd)) ? FdOpResult::Ok() : FdOpResult::Bad(errno);
}

} // namespace Utils
