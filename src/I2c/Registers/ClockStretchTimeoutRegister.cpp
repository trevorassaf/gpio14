#include "I2c/Registers/ClockStretchTimeoutRegister.h"

namespace
{
constexpr uint16_t TIMEOUT_RESET_CODE = 0x40;
} // namespace

namespace I2c
{
ClockStretchTimeoutRegister::ClockStretchTimeoutRegister() : m_timeoutValue{TIMEOUT_RESET_CODE} {}

ClockStretchTimeoutRegister::ClockStretchTimeoutRegister(uint16_t timeoutValue)
	: m_timeoutValue{timeoutValue} {}

uint16_t ClockStretchTimeoutRegister::GetTimeoutValue() const { return m_timeoutValue; }

uint32_t ClockStretchTimeoutRegister::ToMmioRegister() const { return static_cast<uint32_t>(m_timeoutValue); }

std::ostream &operator<<(std::ostream &stream, const ClockStretchTimeoutRegister &reg)
{
		stream << "TOUT: " << reg.GetTimeoutValue() << " (Clock stretch timeout value)" << std::endl;
		return stream;
}

ClockStretchTimeoutRegisterBuilder::ClockStretchTimeoutRegisterBuilder() : m_timeoutValue{TIMEOUT_RESET_CODE} {}

ClockStretchTimeoutRegisterBuilder &ClockStretchTimeoutRegisterBuilder::SetTimeout(uint16_t timeout)
{
		m_timeoutValue = timeout;
		return *this;
}

ClockStretchTimeoutRegisterBuilder &ClockStretchTimeoutRegisterBuilder::ResetTimeout()
{
		m_timeoutValue = TIMEOUT_RESET_CODE;
		return *this;
}

ClockStretchTimeoutRegisterBuilder &ClockStretchTimeoutRegisterBuilder::FromMmioRegister(uint32_t bits)
{
		SetTimeout(static_cast<uint16_t>(bits));
		return *this;
}

ClockStretchTimeoutRegister ClockStretchTimeoutRegisterBuilder::Build() const
{
		return ClockStretchTimeoutRegister{m_timeoutValue};
}

} // namespace I2c
