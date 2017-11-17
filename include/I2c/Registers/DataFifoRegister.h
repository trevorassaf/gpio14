#pragma once

#include <cstdint>

namespace I2c
{
class DataFifoRegister
{
public:
	explicit DataFifoRegister(uint8_t data) : m_data{data} {}

	explicit DataFifoRegister(uint32_t bits) : DataFifoRegister{static_cast<uint8_t>(bits)} {}

	uint8_t GetData() const { return m_data; }

private:
	const uint8_t m_data;
};
} // namespace I2c
