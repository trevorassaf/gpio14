#pragma once

#include <cstdint>
#include <sstream>

#include "I2c/Registers/MmioRegister.h"

namespace I2c
{
class DataFifoRegister : public MmioRegister
{
public:
	explicit DataFifoRegister(uint8_t data);

	explicit DataFifoRegister(uint32_t bits);

	uint8_t GetData() const;

	uint32_t ToMmioRegister() const;

private:
	uint8_t m_data;
};

std::ostream &operator<<(std::ostream &stream, const DataFifoRegister &reg);

} // namespace I2c
