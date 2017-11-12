#pragma once

#include <cstdint>

namespace I2c
{
class DataLengthRegister
{
public:
	DataLengthRegister(uint16_t length) : m_length{length} {}

	uint16_t GetLength() const { return m_length; }

private:
	const uint16_t m_length;
};

class DataLengthRegisterBuilder
{
public:
	DataLengthRegisterBuilder() : m_length{false} {}

	DataLengthRegisterBuilder &SetLength(uint16_t length)
	{
			m_length = length;
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
