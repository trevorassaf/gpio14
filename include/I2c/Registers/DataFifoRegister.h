#pragma once

#include <cstdint>

namespace I2c
{
class DataFifoRegister
{
public:
	DataFifoRegister(uint8_t data) : m_data{data} {}

	uint8_t GetData() const { return m_data; }

private:
	const uint8_t m_data;
};
} // namespace I2c
