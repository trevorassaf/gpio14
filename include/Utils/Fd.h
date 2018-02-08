#pragma once

#include <cstdint>
#include <cstdlib>
#include <unistd.h>

#include "Utils/FdOps.h"

namespace Utils
{

class Fd
{
public:
	Fd();
	Fd(FdOps *ops);
	Fd(FdOps *ops, int fd);
	Fd(FdOps *ops, const char *fileName);
	~Fd();

	Fd(Fd &&other);
	Fd& operator=(Fd &&other);

	int Get() const;
	bool IsOpen() const;

	FdOpResult Write(const uint8_t *buffer, size_t length);
	FdOpResult Read(uint8_t *buffer, size_t length);
	FdOpResult Close();

private:
	Fd(const Fd &other) = delete;
	Fd& operator=(const Fd &other) = delete;

private:
	static constexpr int EMPTY_FILE_DESCRIPTOR = -1;

private:
	FdOps *m_ops;
	int m_fd;
};

} // namespace Utils
