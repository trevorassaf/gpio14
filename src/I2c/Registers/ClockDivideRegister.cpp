#include "I2c/Registers/ClockDivideRegister.h"

namespace
{
constexpr uint16_t DEFAULT_DIVISOR_CODE = 0x05DC;
} // namespace

namespace I2c
{
ClockDivideRegister::ClockDivideRegister() : m_divisor{DEFAULT_DIVISOR_CODE} {}

ClockDivideRegister::ClockDivideRegister(uint16_t divisor) : m_divisor{divisor} {}

ClockDivideRegister::ClockDivideRegister(uint32_t bits) : ClockDivideRegister{static_cast<uint16_t>(bits)} {}

uint16_t ClockDivideRegister::GetDivisor() const { return m_divisor; }

uint32_t ClockDivideRegister::ToMmioRegister() const { return static_cast<uint32_t>(m_divisor); }

std::ostream &operator<<(std::ostream &stream, const ClockDivideRegister &reg)
{
		stream << "CDIV : " << reg.GetDivisor() << " (Clock divisor)" << std::endl;
		return stream;
}

ClockDivideRegisterBuilder::ClockDivideRegisterBuilder() : m_divisor{DEFAULT_DIVISOR_CODE} {}

ClockDivideRegisterBuilder &ClockDivideRegisterBuilder::SetDivisor(uint16_t divisor)
{
		m_divisor = divisor;
		return *this;
}

ClockDivideRegisterBuilder &ClockDivideRegisterBuilder::ResetDivisor()
{
		m_divisor = DEFAULT_DIVISOR_CODE;
		return *this;
}

ClockDivideRegisterBuilder &ClockDivideRegisterBuilder::FromMmioRegister(uint32_t bits)
{
		SetDivisor(static_cast<uint16_t>(bits));
		return *this;
}

ClockDivideRegister ClockDivideRegisterBuilder::Build() const
{
		return ClockDivideRegister{m_divisor};
}

} // namespace I2c
