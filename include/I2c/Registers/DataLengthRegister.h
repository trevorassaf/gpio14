#pragma once

#include <cstdint>
#include <sstream>

#include "I2c/Registers/MmioRegister.h"

namespace I2c
{
class DataLengthRegister : public MmioRegister
{
public:
	DataLengthRegister(uint16_t length);

	uint16_t GetLength() const;

	uint32_t ToMmioRegister() const;

private:
	uint16_t m_length;
};

std::ostream &operator<<(std::ostream &stream, const DataLengthRegister &reg);

class DataLengthRegisterBuilder
{
public:
	DataLengthRegisterBuilder();

	DataLengthRegisterBuilder &SetLength(uint16_t length);

	DataLengthRegisterBuilder &FromMmioRegister(uint32_t bits);

	DataLengthRegister Build() const;

private:
	uint16_t m_length;
};
} // namespace I2c
