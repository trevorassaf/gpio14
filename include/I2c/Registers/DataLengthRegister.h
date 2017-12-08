#pragma once

#include <cstdint>
#include <sstream>

#include "I2c/Registers/DataLengthRegister.h"

namespace I2c
{
class DataLengthRegister : public MmioRegister
{
public:
	DataLengthRegister(uint16_t length) : m_length{length} {}

	uint16_t GetLength() const { return m_length; }

	uint32_t ToMmioRegister() const override { return static_cast<uint32_t>(m_length); }

private:
	uint16_t m_length;
};

std::ostream &operator<<(std::ostream &stream, const DataLengthRegister &reg)
{
		stream << "DLEN: " << reg.GetLength() << std::endl;
		return stream;
}

class DataLengthRegisterBuilder
{
public:
	DataLengthRegisterBuilder() : m_length{false} {}

	DataLengthRegisterBuilder &SetLength(uint16_t length)
	{
			m_length = length;
			return *this;
	}

	DataLengthRegisterBuilder &FromMmioRegister(uint32_t bits)
	{
			SetLength(static_cast<uint16_t>(bits));
			return *this;
	}

	DataLengthRegister Build() const
	{
			return DataLengthRegister{m_length};
	}

private:
	uint16_t m_length;
};
} // namespace I2c
