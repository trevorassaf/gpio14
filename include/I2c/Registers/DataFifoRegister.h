#pragma once

#include <cstdint>
#include <sstream>

#include "I2c/Registers/DataFifoRegister.h"

namespace I2c
{
class DataFifoRegister : public MmioRegister
{
public:
	explicit DataFifoRegister(uint8_t data) : m_data{data} {}

	explicit DataFifoRegister(uint32_t bits) : DataFifoRegister{static_cast<uint8_t>(bits)} {}

	uint8_t GetData() const { return m_data; }

	uint32_t ToMmioRegister() const override { return static_cast<uint32_t>(m_data); }

private:
	uint8_t m_data;
};

std::ostream &operator<<(std::ostream &stream, const DataFifoRegister &reg)
{
		stream << "DATA: " << reg.GetData() << " (Fifo data byte)" << std::endl;
		return stream;
}

} // namespace I2c
