#include "I2c/I2cClient.h"

#include <linux/i2c-dev.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <cassert>
#include <iostream>
#include <utility>

#include "I2c/I2cException.h"
#include "Utils/SysUtils.h"
#include "Utils/FdOpResult.h"

namespace
{
constexpr uint8_t EMPTY_SLAVE_ADDRESS = 0xFF;
} // namespace

using Utils::Fd;
using Utils::FdOpResult;
using Utils::SysUtils;

namespace I2c
{

I2cClient::I2cClient()
	: I2cClient{EMPTY_SLAVE_ADDRESS} {}

I2cClient::I2cClient(uint8_t slaveAddress)
	: I2cClient{slaveAddress, nullptr} {}

I2cClient::I2cClient(std::unique_ptr<Fd> fd)
	: I2cClient{EMPTY_SLAVE_ADDRESS, nullptr} {}

I2cClient::I2cClient(uint8_t slaveAddress, std::unique_ptr<Fd> fd)
  :	m_fd{std::move(fd)},
		m_slaveAddress{slaveAddress} {}

I2cClient::~I2cClient() {}

I2cClient::I2cClient(I2cClient &&other)
{
		*this = std::move(other);
}

I2cClient& I2cClient::operator=(I2cClient &&other)
{
		m_fd = std::move(other.m_fd);

		m_slaveAddress = other.m_slaveAddress;
		other.m_slaveAddress = EMPTY_SLAVE_ADDRESS;
}

void I2cClient::Close()
{
		m_fd.reset();
		m_slaveAddress = EMPTY_SLAVE_ADDRESS;
}

bool I2cClient::IsOpen() const
{
		return m_fd && m_fd->IsOpen(); 
}

void I2cClient::SetSlave(uint8_t slaveAddress)
{
		assert(m_fd->IsOpen());

		m_slaveAddress = slaveAddress;
		if (ioctl(m_fd->Get(), I2C_SLAVE, slaveAddress) < 0)
		{
				std::cout << "Failed to set I2c slave address. Slave: 0x"
					<< std::hex << slaveAddress << std::endl;
				throw I2cException(SysUtils::GetErrorMessage());
		}
}

uint8_t I2cClient::GetSlave() const
{
		return m_slaveAddress;
}

bool I2cClient::HasSlave() const
{
		return m_slaveAddress != EMPTY_SLAVE_ADDRESS;
}

void I2cClient::Write(const uint8_t *buffer, size_t size)
{
		assert(m_slaveAddress != EMPTY_SLAVE_ADDRESS);
		auto result = m_fd->Write(buffer, size);
		if (!result.IsOk())
		{
				std::cout << "I2c write operation failed"
					<< ". Slave: 0x" << std::hex << m_slaveAddress
					<< ". Buffer size: " << std::dec << size
					<< std::endl;
				throw I2cException(SysUtils::GetErrorMessage());
		}
}

void I2cClient::Read(uint8_t *buffer, size_t size)
{
		assert(m_slaveAddress != EMPTY_SLAVE_ADDRESS);
		auto result = m_fd->Read(buffer, size);
		if (!result.IsOk())
		{
				std::cout << "I2c read operation failed"
					<< ". Slave: 0x" << std::hex << m_slaveAddress
					<< ". Buffer size: " << std::dec << size
					<< std::endl;
				throw I2cException(SysUtils::GetErrorMessage());
		}
}

} // namespace I2c
