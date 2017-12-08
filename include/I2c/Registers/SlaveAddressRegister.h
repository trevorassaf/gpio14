#pragma once

#include <cassert>
#include <cstdint>
#include <limits>
#include <sstream>

#include "I2c/Registers/MmioRegister.h"

namespace I2c
{
class SlaveAddressRegister : public MmioRegister
{
public:
	SlaveAddressRegister(uint8_t slaveAddress);

	SlaveAddressRegister(uint32_t bits);

	uint8_t GetAddress() const;

	uint32_t ToMmioRegister() const override;

private:
	uint8_t m_slaveAddress; 
};

std::ostream &operator<<(std::ostream &stream, const SlaveAddressRegister &reg);

class SlaveAddressRegisterBuilder
{
public:
	SlaveAddressRegisterBuilder();

	SlaveAddressRegisterBuilder &SetAddress(uint8_t address);

	SlaveAddressRegisterBuilder &FromMmioRegister(uint32_t bits);

	SlaveAddressRegister Build() const;

private:
	uint8_t m_slaveAddress;
};
} // namespace I2c
