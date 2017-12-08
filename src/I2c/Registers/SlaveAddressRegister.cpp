#include "I2c/Registers/SlaveAddressRegister.h"

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
SlaveAddressRegister::SlaveAddressRegister(uint8_t slaveAddress) : m_slaveAddress{slaveAddress}
{
		checkSlaveAddress(slaveAddress);
}

SlaveAddressRegister::SlaveAddressRegister(uint32_t bits) : SlaveAddressRegister{static_cast<uint8_t>(bits)} {}

uint8_t SlaveAddressRegister::GetAddress() const { return m_slaveAddress; }

uint32_t SlaveAddressRegister::ToMmioRegister() const { return static_cast<uint32_t>(m_slaveAddress); }

std::ostream &operator<<(std::ostream &stream, const SlaveAddressRegister &reg)
{
		stream << "ADDR: " << std::hex << reg.GetAddress() << " (Slave address register)" << std::endl;
		return stream;
}

SlaveAddressRegisterBuilder::SlaveAddressRegisterBuilder() : m_slaveAddress{0} {}

SlaveAddressRegisterBuilder &SlaveAddressRegisterBuilder::SetAddress(uint8_t address)
{
		checkSlaveAddress(address);
		m_slaveAddress = address;
		return *this;
}

SlaveAddressRegisterBuilder &SlaveAddressRegisterBuilder::FromMmioRegister(uint32_t bits)
{
		SetAddress(static_cast<uint8_t>(bits));
		return *this;
}

SlaveAddressRegister SlaveAddressRegisterBuilder::Build() const
{
		return SlaveAddressRegister{m_slaveAddress};
}

} // namespace I2c
