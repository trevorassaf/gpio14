#include "I2c/Registers/DataFifoRegister.h"

namespace I2c
{
DataFifoRegister::DataFifoRegister(uint8_t data) : m_data{data} {}

uint8_t DataFifoRegister::GetData() const { return m_data; }

uint32_t DataFifoRegister::ToMmioRegister() const { return static_cast<uint32_t>(m_data); }

std::ostream &operator<<(std::ostream &stream, const DataFifoRegister &reg)
{
		stream << "DATA: " << (int)reg.GetData() << " (Fifo data byte)" << std::endl;
		return stream;
}

} // namespace I2c
