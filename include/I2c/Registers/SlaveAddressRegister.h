#pragma once

#include <cassert>
#include <cstdint>
#include <limits>
#include <sstream>

#include "I2c/Registers/MmioRegister.h"

namespace
{
constexpr uint8_t MAX_SLAVE_ADDRESS = 128;

void checkSlaveAddress(uint8_t slaveAddress)
{
		assert(slaveAddress < MAX_SLAVE_ADDRESS);
}
} // namespace

namespace I2c
{
class SlaveAddressRegister : public MmioRegister
{
public:
	SlaveAddressRegister(uint8_t slaveAddress) : m_slaveAddress{slaveAddress}
	{
			checkSlaveAddress(slaveAddress);
	}

	SlaveAddressRegister(uint32_t bits) : SlaveAddressRegister{static_cast<uint8_t>(bits)} {}

	uint8_t GetAddress() const { return m_slaveAddress; }

	uint32_t ToMmioRegister() const override { return static_cast<uint32_t>(m_slaveAddress); }

private:
	const uint8_t m_slaveAddress; 
};

std::ostream &operator<<(std::ostream &stream, const SlaveAddressRegister &reg)
{
		stream << "ADDR: " << std::hex << reg.GetAddress() << " (Slave address register)" << std::endl;
		return stream;
}

class SlaveAddressRegisterBuilder
{
public:
	SlaveAddressRegisterBuilder() : m_slaveAddress{0} {}

	SlaveAddressRegisterBuilder &SetAddress(uint8_t address)
	{
			checkSlaveAddress(address);
			m_slaveAddress = address;
			return *this;
	}

	SlaveAddressRegisterBuilder &FromMmioRegister(uint32_t bits)
	{
			SetAddress(static_cast<uint8_t>(bits));
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
