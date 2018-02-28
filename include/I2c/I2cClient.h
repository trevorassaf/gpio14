#pragma once

#include <cstdint>
#include <memory>
#include <string>
#include <utility>

#include "I2c/I2cIoctlOps.h"
#include "Utils/Fd.h"

namespace I2c
{

class I2cClient
{
public:
	I2cClient(I2cIoctlOps *ioctlOps);
	I2cClient(I2cIoctlOps *ioctlOps, uint8_t slaveAddress);
	I2cClient(I2cIoctlOps *ioctlOps, std::unique_ptr<Utils::Fd> fd);
	I2cClient(I2cIoctlOps *ioctlOps, uint8_t slaveAddress, std::unique_ptr<Utils::Fd> fd);

	~I2cClient();

	I2cClient(I2cClient &&other);
	I2cClient& operator=(I2cClient &&other);

	bool IsOpen() const;
	void SetSlave(uint8_t slaveAddress);
	bool HasSlave() const;
	uint8_t GetSlave() const;
	void Close();
	void Write(const uint8_t *buffer, size_t size);
	void Read(uint8_t *buffer, size_t size);

private:
	I2cClient(const I2cClient &other) = delete;
	I2cClient& operator=(const I2cClient &other) = delete;

private:
	I2cIoctlOps *m_ioctlOps;
	uint8_t m_slaveAddress;
	std::unique_ptr<Utils::Fd> m_fd;
};

} // namespace I2c
