#pragma once

#include <cstdint>

namespace
{
constexpr uint16_t REGISTER_RESET_VALUE = 0x30;
} // namespace

namespace I2c
{
class DataDelayRegister
{
public:
	DataDelayRegister()
		: m_fallingEdgeDelay{REGISTER_RESET_VALUE},
			m_risingEdgeDelay{REGISTER_RESET_VALUE} {}

	DataDelayRegister(
			uint16_t fallingEdgeDelay,
			uint16_t risingEdgeDelay)
		: m_fallingEdgeDelay{fallingEdgeDelay},
			m_risingEdgeDelay{risingEdgeDelay} {}

	uint16_t GetFallingEdgeDelay() const { return m_fallingEdgeDelay; }
	uint16_t GetRisingEdgeDelay() const { return m_risingEdgeDelay; }

private:
	const uint16_t m_fallingEdgeDelay;
	const uint16_t m_risingEdgeDelay;
};

class DataDelayRegisterBuilder
{
public:
	DataDelayRegisterBuilder()
		: m_fallingEdgeDelay{REGISTER_RESET_VALUE},
			m_risingEdgeDelay{REGISTER_RESET_VALUE} {}

	DataDelayRegisterBuilder &SetFallingEdgeDelay(uint16_t delay)
	{
			m_fallingEdgeDelay = delay;
			return *this;
	}

	DataDelayRegisterBuilder &SetRisingEdgeDelay(uint16_t delay)
	{
			m_risingEdgeDelay = delay;
			return *this;
	}

	DataDelayRegister Build() const
	{
			return DataDelayRegister{m_fallingEdgeDelay, m_risingEdgeDelay};
	}

private:
	uint16_t m_fallingEdgeDelay;
	uint16_t m_risingEdgeDelay;
};
} // namespace I2c
