#include "I2c/Registers/DataLengthRegister.h"

namespace I2c
{
DataLengthRegister::DataLengthRegister(uint16_t length) : m_length{length} {}

uint16_t DataLengthRegister::GetLength() const { return m_length; }

uint32_t DataLengthRegister::ToMmioRegister() const { return static_cast<uint32_t>(m_length); }

std::ostream &operator<<(std::ostream &stream, const DataLengthRegister &reg)
{
		stream << "DLEN: " << reg.GetLength() << std::endl;
		return stream;
}

DataLengthRegisterBuilder::DataLengthRegisterBuilder() : m_length{false} {}

DataLengthRegisterBuilder &DataLengthRegisterBuilder::SetLength(uint16_t length)
{
		m_length = length;
		return *this;
}

DataLengthRegisterBuilder &DataLengthRegisterBuilder::FromMmioRegister(uint32_t bits)
{
		SetLength(static_cast<uint16_t>(bits));
		return *this;
}

DataLengthRegister DataLengthRegisterBuilder::Build() const
{
		return DataLengthRegister{m_length};
}

} // namespace I2c
