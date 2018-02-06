#pragma once

#include <cstdint>
#include <string>

#include "Utils/FileDescriptor.h"
#include "Utils/FdOps.h"

namespace I2c
{

class I2cClient
{
public:
	I2cClient(Utils::FdOps *fdOps, const char *devicePath);
	~I2cClient();
	I2cClient(I2cClient &&other);
	I2cClient& operator=(I2cClient &&other);
	void SetSlave(uint8_t slaveAddress);
	void Close();
	void Write(const uint8_t *buffer, size_t size);
	void Read(uint8_t *buffer, size_t size);

private:
	I2cClient(const I2cClient &other) = delete;
	I2cClient& operator=(const I2cClient &other) = delete;

private:
	Utils::FdOps *m_fdOps;
	Utils::FileDescriptor m_fd;
	uint8_t m_slaveAddress;
};

} // namespace I2c
