#include "I2c/Registers/DataDelayRegister.h"

namespace
{
constexpr uint16_t REGISTER_RESET_CODE = 0x30;
} // namespace

namespace Bits
{
namespace Mmio
{
constexpr uint16_t FALLING_EDGE_DELAY = 16;
constexpr uint16_t RISING_EDGE_DELAY = 0;
} // namespace Mmio
} // namespace Bits

namespace I2c
{
DataDelayRegister::DataDelayRegister()
	: m_fallingEdgeDelay{REGISTER_RESET_CODE},
		m_risingEdgeDelay{REGISTER_RESET_CODE} {}

DataDelayRegister::DataDelayRegister(
		uint16_t fallingEdgeDelay,
		uint16_t risingEdgeDelay)
	: m_fallingEdgeDelay{fallingEdgeDelay},
		m_risingEdgeDelay{risingEdgeDelay} {}

uint16_t DataDelayRegister::GetFallingEdgeDelay() const
{
		return m_fallingEdgeDelay;
}

uint16_t DataDelayRegister::GetRisingEdgeDelay() const
{
		return m_risingEdgeDelay;
}

uint32_t DataDelayRegister::ToMmioRegister() const
{
		uint32_t mmioBits = 0;
		mmioBits |= m_fallingEdgeDelay << Bits::Mmio::FALLING_EDGE_DELAY;
		mmioBits |= m_risingEdgeDelay << Bits::Mmio::RISING_EDGE_DELAY;
		return mmioBits;
}

DataDelayRegisterBuilder::DataDelayRegisterBuilder()
		: m_fallingEdgeDelay{REGISTER_RESET_CODE},
			m_risingEdgeDelay{REGISTER_RESET_CODE} {}

DataDelayRegisterBuilder &DataDelayRegisterBuilder::SetFallingEdgeDelay(uint16_t delay)
{
		m_fallingEdgeDelay = delay;
		return *this;
}

DataDelayRegisterBuilder &DataDelayRegisterBuilder::ResetFallingEdgeDelay()
{
		m_fallingEdgeDelay = REGISTER_RESET_CODE;
		return *this;
}

DataDelayRegisterBuilder &DataDelayRegisterBuilder::SetRisingEdgeDelay(uint16_t delay)
{
		m_risingEdgeDelay = delay;
		return *this;
}

DataDelayRegisterBuilder &DataDelayRegisterBuilder::ResetRisingEdgeDelay()
{
		m_risingEdgeDelay = REGISTER_RESET_CODE;
		return *this;
}

DataDelayRegisterBuilder &DataDelayRegisterBuilder::FromMmioRegister(uint32_t bits)
{
		// First 16 bits define rising-edge delay. Last 16 bits define falling-edge delay.
		SetRisingEdgeDelay(static_cast<uint16_t>(bits));
		SetFallingEdgeDelay(static_cast<uint16_t>(bits >> 16));
		return *this;
}

DataDelayRegister DataDelayRegisterBuilder::Build() const
{
		return DataDelayRegister{m_fallingEdgeDelay, m_risingEdgeDelay};
}

} // namespace I2c
