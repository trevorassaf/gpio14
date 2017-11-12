#pragma once

#include <cassert>
#include <cstdint>
#include <numeric_limits>

namespace
{
constexpr uint8_t MAX_SLAVE_ADDRESS = 128;

void checkSlaveAddress(uint8_t slaveAddress)
{
		::assert(slaveAddress < MAX_SLAVE_ADDRESS);
}
} // namespace

namespace I2c
{
class SlaveAddressRegister
{
public:
	SlaveAddressRegister(uint8_t slaveAddress) : m_slaveAddress{slaveAddress}
	{
			checkSlaveAddress(slaveAddress);
	}

	uint8_t GetAddress() const { return m_slaveAddress; }

private:
	const uint8_t m_slaveAddress; 
};

class SlaveAddressRegisterBuilder
{
public:
	SlaveAddressRegisterBuilder() : m_slaveAddress{0} {}

	SlaveAddressRegisterBuilder &SetAddress(uint8_t address)
	{
			checkSlaveAddress(slaveAddress);
			m_slaveAddress = address;
			return *this;
	}

	SlaveAddressRegister Build() const
	{
			return SlaveAddressRegister{m_slaveAddress};
	}

private:
	uint8_t m_slaveAddress;
};
} // namespace I2c
